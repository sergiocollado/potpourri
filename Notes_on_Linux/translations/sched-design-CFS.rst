=============
CFS Scheduler
=============


1.  OVERVIEW
============

CFS stands for "Completely Fair Scheduler," and is the new "desktop" process
scheduler implemented by Ingo Molnar and merged in Linux 2.6.23.  It is the
replacement for the previous vanilla scheduler's SCHED_OTHER interactivity
code.

CFS viene de las siglas en inglés de "Gestor te tareas totalmente justo"
("Completely Fair Scheduler"), y es el nuevo gesto de tareas de escritorio
implementado por Ingo Molnar e integrado en Linux 2.6.23. Es el sustituto
para el previo gestor de tareas SCHED_OTHER.

80% of CFS's design can be summed up in a single sentence: CFS basically models
an "ideal, precise multi-tasking CPU" on real hardware.

El 80% del diseño de CFS puede ser resumido en una única frase: CFS
básicamente modela una "CPU ideal, precisa y multi-tarea" sobre hardware
real.

"Ideal multi-tasking CPU" is a (non-existent  :-)) CPU that has 100% physical
power and which can run each task at precise equal speed, in parallel, each at
1/nr_running speed.  For example: if there are 2 tasks running, then it runs
each at 50% physical power --- i.e., actually in parallel.

On real hardware, we can run only a single task at once, so we have to
introduce the concept of "virtual runtime."  The virtual runtime of a task
specifies when its next timeslice would start execution on the ideal
multi-tasking CPU described above.  In practice, the virtual runtime of a task
is its actual runtime normalized to the total number of running tasks.

En un hardware real, podemos ejecutar una única tarea a la vez, asi que
se ha usado el concepto the "tiempo de ejecución virtual". El tiempo
de ejecución virtual de una tarea, especifica cuando la siguiente porción
de ejecución podría empezar en la CPU ideal multi-tarea descrita anteriormente.
En la práctica, el tiempo de ejecución virtual de una tarea es el 
tiempo de ejecución real normalizado con repsecto al número total de 
tareas ejecutandose.


2.  FEW IMPLEMENTATION DETAILS
==============================

2. UNOS CUANTOS DETALLES DE IMPLEMENTACIÓN
==========================================

In CFS the virtual runtime is expressed and tracked via the per-task
p->se.vruntime (nanosec-unit) value.  This way, it's possible to accurately
timestamp and measure the "expected CPU time" a task should have gotten.

En CFS, el tiempo de ejecución virtual se expresa y se monitoriza por
cada tarea, en su valor de p->se.vruntime (en unidades de nanosegundos).
De este modo, es posible temporizar con precisión y medir el "tiempo  
de CPU esperado" que una tarea debería tener. 

   Small detail: on "ideal" hardware, at any time all tasks would have the same
   p->se.vruntime value --- i.e., tasks would execute simultaneously and no task
   would ever get "out of balance" from the "ideal" share of CPU time.

   Un pequeño detalle: en hardware "ideal", en cualquier momento todas las 
   tareas pueden tener el mismo valor de p->se.vruntime --- i.e., tareas
   se podrian ejecutar simultaneamente y ninguna tarea podria escaparse del 
   "balance" de la partición "ideal" del tiempo compartido de la CPU.

CFS's task picking logic is based on this p->se.vruntime value and it is thus
very simple: it always tries to run the task with the smallest p->se.vruntime
value (i.e., the task which executed least so far).  CFS always tries to split
up CPU time between runnable tasks as close to "ideal multitasking hardware" as
possible.

La lógica de elección del tareas de CFS se basa en el valor de p->se.vruntime
y por tanto es muy sencialla: siempre intenta ejecutar la tarea con el valor
p->se.vruntime más pequeño (i.e., la tarea que se ha ejecutado menos hasta el
momento). CFS siempre intenta dividir el espacio de tiempo entre tareas 
en ejecución tan próximo a la "ejecución multitarea ideal del hardware" como
sea posible. 

Most of the rest of CFS's design just falls out of this really simple concept,
with a few add-on embellishments like nice levels, multiprocessing and various
algorithm variants to recognize sleepers.

El resto del diseño de CFS simplemente se escapa de este simple concepto, 
con unos cuantos añadidos como los niveles "nice", multi-tarea y varias
variantes del algoritmo para identificar tareas "durmiendo". 


3.  THE RBTREE
==============

4. EL RBTREE
============

CFS's design is quite radical: it does not use the old data structures for the
runqueues, but it uses a time-ordered rbtree to build a "timeline" of future
task execution, and thus has no "array switch" artifacts (by which both the
previous vanilla scheduler and RSDL/SD are affected).

El diseño de CFS es bastante radical: no utiliza las antiguas estructuras
de datos para las colas de ejecución, pero usa un rbtree ordenado
cronológicamente para construir un linea de ejecución en el futuro, y por
eso no tiene ningún artificio de "cambio de tareas" (algo que previamente
era usado por el gestor anterior y RSDL/SD).

CFS also maintains the rq->cfs.min_vruntime value, which is a monotonic
increasing value tracking the smallest vruntime among all tasks in the
runqueue.  The total amount of work done by the system is tracked using
min_vruntime; that value is used to place newly activated entities on the left
side of the tree as much as possible.

CFS también mantiene el valor de rq->cfs.min_vruntime, el cual crece 
monotónicamnte siguiendo el valor más pequeño de vruntime de entre todas
las teras en la cola de ejecución. La cantidad total de trabajo realizado
por el sistema es monitorizado usado min_vruntime; este valor es usado
para situar las nuevas tareas en la parte izquierda del árbol tanto 
como sea posible.

The total number of running tasks in the runqueue is accounted through the
rq->cfs.load value, which is the sum of the weights of the tasks queued on the
runqueue.

El valor total te tareas ejecutandose en la cola de ejecución es  
contabilizado mediate el valor rq->cfs.load, el cual es la suma de los
de esas tareas que estan en la cola de ejecución.

CFS maintains a time-ordered rbtree, where all runnable tasks are sorted by the
p->se.vruntime key. CFS picks the "leftmost" task from this tree and sticks to it.
As the system progresses forwards, the executed tasks are put into the tree
more and more to the right --- slowly but surely giving a chance for every task
to become the "leftmost task" and thus get on the CPU within a deterministic
amount of time.

CFS mantiene un arbol rbtree cronológiamente ordeado, donde todas las 
tareas que pueden ser ejecutadas están ordenadas por la clave 
p->se.vruntime. CFS selecciona la tarea más hacia la izquierda de este
árbol y la mantiene. Según el sistem continua, las taras eejcutadas 
se ponen en este árbol más y más hacia la derecha --- lentamente pero 
de forma continuada dando una oportunidad a cara tarea de ser la que 
está "la más hacia la izquierda" y por tanto obtener la CPU una cantidad
determinista de tiempo.

Summing up, CFS works like this: it runs a task a bit, and when the task
schedules (or a scheduler tick happens) the task's CPU usage is "accounted
for": the (small) time it just spent using the physical CPU is added to
p->se.vruntime.  Once p->se.vruntime gets high enough so that another task
becomes the "leftmost task" of the time-ordered rbtree it maintains (plus a
small amount of "granularity" distance relative to the leftmost task so that we
do not over-schedule tasks and trash the cache), then the new leftmost task is
picked and the current task is preempted.

Resumiendo, CFS funciona así: ejecuta una tarea un tiemo, y cuando la
tarea se gestiona (o suced un tic del gestor de tareas) se considera
que el tiempo de uso de la CPU se ha completado, y se añade a 
p->se.vruntime. Una vez p->se.vruntime ha aumentado lo suficiente como
para que otra tarea sea "la tarea más hacia la izquierda" del árbol 
rbtree ordenado cronológicamente esta manitenen (más una cierta pequeña
cantidad de disancai relativa a la tarea más hacia la izquierda para
que no se sobre reserven tareas y perjudique a la cache), entonces la
nueva tarea "que está a la izquierda del todo", es la que se elige 
para que se ejecute, y la tarea en ejecución es interrupida.

4.  SOME FEATURES OF CFS
========================

4. ALGUNAS CARACTERÍSTICAS DE CFS
=================================

CFS uses nanosecond granularity accounting and does not rely on any jiffies or
other HZ detail.  Thus the CFS scheduler has no notion of "timeslices" in the
way the previous scheduler had, and has no heuristics whatsoever.  There is
only one central tunable (you have to switch on CONFIG_SCHED_DEBUG):

   /sys/kernel/debug/sched/base_slice_ns

CFS usa una granularidad de nanosegundos contando y no depende de ningún
jiffie o detalles como HZ. De este modo el gestor de tareas CFS no tiene
noción de "ventanas de tiempo" de la forma en que tenía el gestor de
tareas previo, y tampoco tiene heuristicos. Unicamente hay un parámetro
central ajustable (se ha de cambiar en CONFIG_SCHED_DEBUG):

   /sys/kernel/debug/sched/base_slice_ns

which can be used to tune the scheduler from "desktop" (i.e., low latencies) to
"server" (i.e., good batching) workloads.  It defaults to a setting suitable
for desktop workloads.  SCHED_BATCH is handled by the CFS scheduler module too.

El cual puede ser usado para afinar desde el gestor de tareas del "escritorio" (i.e.,
bajas latencias)  hacia cargas de "servidor" (i.e., bueno con procesamientos).
Su valor por defecto es adecuado tareas de escritorio. SCHED_BATCH tambien es 
gestionado por el gestor de tareas CFS.

Due to its design, the CFS scheduler is not prone to any of the "attacks" that
exist today against the heuristics of the stock scheduler: fiftyp.c, thud.c,
chew.c, ring-test.c, massive_intr.c all work fine and do not impact
interactivity and produce the expected behavior.

Debido a su diseño, el gestor de tareas CFS no es proclibe a ninguno de los
ataques que existen a dia de hoy contra los heuristicos del gestor de tareas:
fiftyp.c, thud.c, chew.c, ring-test.c, massive_intr.c todos trabajan 
correctamnte y no tienen impacto en la interaccion y se comportan de la forma
esperada.

The CFS scheduler has a much stronger handling of nice levels and SCHED_BATCH
than the previous vanilla scheduler: both types of workloads are isolated much
more aggressively.

El gestor de tareas CFS tiene una gestión mucho más firme de los niveles
"nice" y SCHED_BATCH que los previos gestores de tareas: ambos timpos de
tareas están aisladas de forma más eficiente.

SMP load-balancing has been reworked/sanitized: the runqueue-walking
assumptions are gone from the load-balancing code now, and iterators of the
scheduling modules are used.  The balancing code got quite a bit simpler as a
result.

El balaceo de tareas SMP ha sido rehecho/mejorado: el avance por las
colas de ejecución de tareas ha desaparecido del código de balanceo de
carga, y ahora se usan iteradores en la gestión de modulos. El balanceo
del código a sido simplificado como resultado esto.


5. Scheduling policies
======================

5. Políticas de gestión de tareas
=================================

CFS implements three scheduling policies:

CFS implementa tres políticas de gestion de tareas:

  - SCHED_NORMAL (traditionally called SCHED_OTHER): The scheduling
    policy that is used for regular tasks.

  - SCHED_NORMAL (tradicionalmente llamada SCHED_OTHER): Gestión de
    tareas que se usa para tareas normales.

  - SCHED_BATCH: Does not preempt nearly as often as regular tasks
    would, thereby allowing tasks to run longer and make better use of
    caches but at the cost of interactivity. This is well suited for
    batch jobs.

  - SCHED_BATCH: No interrumpe tareas tan amenudo como las tareas
    normales harian, por eso permite a las tareas ejecutarse durante
    ventanas de tiempo mayores y hace un uso más efectivo de las
    caches pero al coste de la interactividad. Esto es adecuado
    para trabajos de procesado.

  - SCHED_IDLE: This is even weaker than nice 19, but its not a true
    idle timer scheduler in order to avoid to get into priority
    inversion problems which would deadlock the machine.

  - SCHED_IDLE: Esta política es más debil incluso que nice 19, pero
    no es un gestor "idle" para evitar caer en el problema de la 
    inversión de prioridades que causaria un bloqueo de la máquina
    (deadlock).

SCHED_FIFO/_RR are implemented in sched/rt.c and are as specified by
POSIX.

SCHED_FIFO/_RR se implementan en sched/rt.c y son específicos de
POSIX.

The command chrt from util-linux-ng 2.13.1.1 can set all of these except
SCHED_IDLE.

El comando chrt de util-linux-ng 2.13.1.1. puede asignar cualquiera de
estas políticas excepto SCHED_IDLE.


6.  SCHEDULING CLASSES
======================

6. CLASES DE GESTION
====================

The new CFS scheduler has been designed in such a way to introduce "Scheduling
Classes," an extensible hierarchy of scheduler modules.  These modules
encapsulate scheduling policy details and are handled by the scheduler core
without the core code assuming too much about them.

El nuevo gestor de tareas CFS ha sido diseñado de tal modo para introducir
"clases de gestión" una jerarquia ampliable de módulos de gestión. Estos 
módulos encapsulan los detalles de las politicas de gestion y son manejadas
por el núcleo del gestor de areas sin que este tenga que asumir mucho 
sobre estas clases.

sched/fair.c implements the CFS scheduler described above.

sched/fair.c implementa el gestor de tareas CFS descrito arriba. 

sched/rt.c implements SCHED_FIFO and SCHED_RR semantics, in a simpler way than
the previous vanilla scheduler did.  It uses 100 runqueues (for all 100 RT
priority levels, instead of 140 in the previous scheduler) and it needs no
expired array.

sched/rt.c implementa la semántica de SCHED_FIFO y SCHED_RR, de una forma
más sencilla que el gestor de tareas anterior. Usa 100 colas de ejecución
(por todos los 100 niveles de prioridad RT, en vez de las 140 que necesitaba
el gestor de tareas anterior) y no necesita las listas de expiración.

Scheduling classes are implemented through the sched_class structure, which
contains hooks to functions that must be called whenever an interesting event
occurs.

Las clases de gestión de tareas son implementadas por medio de la estructura
sched_class, la cual tiene llamadas a las funciones que debben de llamarse
cuando quiera que ocurra un evento interesante.

This is the (partial) list of the hooks:
Esta es la lista parcial de llamadas:

 - enqueue_task(...)

   Called when a task enters a runnable state.
   It puts the scheduling entity (task) into the red-black tree and
   increments the nr_running variable.

   LLamada cuando una tarea entra en el estado de lista para ejecución.
   Pone la entidad a ser gestionada (la tarea) en el árbol rojo-negro
   e incrementa la variable nr_running.

 - dequeue_task(...)

   When a task is no longer runnable, this function is called to keep the
   corresponding scheduling entity out of the red-black tree.  It decrements
   the nr_running variable.

   Cuando una tarea deja de ser ejecutable, esta función se llama para 
   mantener a la entidad gestionada fuera del árbol rojo-negor. Esto 
   decrementa la variable nr_running.

 - yield_task(...)

   This function is basically just a dequeue followed by an enqueue, unless the
   compat_yield sysctl is turned on; in that case, it places the scheduling
   entity at the right-most end of the red-black tree.

   Esta función es basicamente desecolar seguido por encolar, a menos que 
   sysctl compat_yeld esté activado; en ese caso, situa la entidad a gestionar 
   en la parte más hacia la derecha del árbol rojo-negro.

 - check_preempt_curr(...)

   This function checks if a task that entered the runnable state should
   preempt the currently running task.

   Esta función comprueba si una tarea que ha entrado en el estado de
   poder ser ejecutada, podría remplazar a la tarea que actualmente
   se esté ejecutando.

 - pick_next_task(...)

   This function chooses the most appropriate task eligible to run next.

   Esta función elige la tarea más apropiada para ser ejecutada a continuación.

 - set_curr_task(...)

   This function is called when a task changes its scheduling class or changes
   its task group.

   Esta función se llama cuando una tarea cambia su clase de gestión o 
   cambia su grupo de tareas.

 - task_tick(...)

   This function is mostly called from time tick functions; it might lead to
   process switch.  This drives the running preemption.

   Esta función es llamada la mayoria de las veces desde la función de timepo
   tick; esto puede llevar a un cambio de procesos. Esto dirige el reemplazo
   de las tareas. 




7.  GROUP SCHEDULER EXTENSIONS TO CFS
=====================================

Normally, the scheduler operates on individual tasks and strives to provide
fair CPU time to each task.  Sometimes, it may be desirable to group tasks and
provide fair CPU time to each such task group.  For example, it may be
desirable to first provide fair CPU time to each user on the system and then to
each task belonging to a user.

CONFIG_CGROUP_SCHED strives to achieve exactly that.  It lets tasks to be
grouped and divides CPU time fairly among such groups.

CONFIG_RT_GROUP_SCHED permits to group real-time (i.e., SCHED_FIFO and
SCHED_RR) tasks.

CONFIG_FAIR_GROUP_SCHED permits to group CFS (i.e., SCHED_NORMAL and
SCHED_BATCH) tasks.

   These options need CONFIG_CGROUPS to be defined, and let the administrator
   create arbitrary groups of tasks, using the "cgroup" pseudo filesystem.  See
   Documentation/admin-guide/cgroup-v1/cgroups.rst for more information about this filesystem.

When CONFIG_FAIR_GROUP_SCHED is defined, a "cpu.shares" file is created for each
group created using the pseudo filesystem.  See example steps below to create
task groups and modify their CPU share using the "cgroups" pseudo filesystem::

	# mount -t tmpfs cgroup_root /sys/fs/cgroup
	# mkdir /sys/fs/cgroup/cpu
	# mount -t cgroup -ocpu none /sys/fs/cgroup/cpu
	# cd /sys/fs/cgroup/cpu

	# mkdir multimedia	# create "multimedia" group of tasks
	# mkdir browser		# create "browser" group of tasks

	# #Configure the multimedia group to receive twice the CPU bandwidth
	# #that of browser group

	# echo 2048 > multimedia/cpu.shares
	# echo 1024 > browser/cpu.shares

	# firefox &	# Launch firefox and move it to "browser" group
	# echo <firefox_pid> > browser/tasks

	# #Launch gmplayer (or your favourite movie player)
	# echo <movie_player_pid> > multimedia/tasks
