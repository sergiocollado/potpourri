========================
Deadline Task Scheduling
========================

=========================
Gestor de tareas Deadline
=========================


.. CONTENTS

    0. WARNING
    1. Overview
    2. Scheduling algorithm
      2.1 Main algorithm
      2.2 Bandwidth reclaiming
    3. Scheduling Real-Time Tasks
      3.1 Definitions
      3.2 Schedulability Analysis for Uniprocessor Systems
      3.3 Schedulability Analysis for Multiprocessor Systems
      3.4 Relationship with SCHED_DEADLINE Parameters
    4. Bandwidth management
      4.1 System-wide settings
      4.2 Task interface
      4.3 Default behavior
      4.4 Behavior of sched_yield()
    5. Tasks CPU affinity
      5.1 SCHED_DEADLINE and cpusets HOWTO
    6. Future plans
    A. Test suite
    B. Minimal main()


0. WARNING
==========

0. ADVERTENCIA
==============

 Fiddling with these settings can result in an unpredictable or even unstable
 system behavior. As for -rt (group) scheduling, it is assumed that root users
 know what they're doing.

 Jugeterar con esto ajustes puede resultar en un comportamiento del sistema
 inpredecible o inestable. Como con la gestión de -rt (grupos), se asume que
 los usuarios raíz saben lo que están haciendo. 


1. Overview
===========

1. Generalidades.
=================

 The SCHED_DEADLINE policy contained inside the sched_dl scheduling class is
 basically an implementation of the Earliest Deadline First (EDF) scheduling
 algorithm, augmented with a mechanism (called Constant Bandwidth Server, CBS)
 that makes it possible to isolate the behavior of tasks between each other.

 La política SCHED_DEADLINE contenida dentro de la clase de gestión de tareas
 sched_dl es básicamente una implementación del algoritmo de gestión de tareas
 del "siguiente tiempo límite" (en inglés EDF, Earliest Deadline First),
 mejorado con un mecanismo (llamado "servidor de ancho de banda constante", en 
 inglés "Constant Bandwidth Server", CBS) que hace posible aislar el 
 comportamiento de las tareas entre ellas. 


2. Scheduling algorithm
=======================

2. Algoritmo del gestor de tareas
=================================


2.1 Main algorithm
------------------

2.1 Algoritmo principal
-----------------------

 SCHED_DEADLINE [18] uses three parameters, named "runtime", "period", and
 "deadline", to schedule tasks. A SCHED_DEADLINE task should receive
 "runtime" microseconds of execution time every "period" microseconds, and
 these "runtime" microseconds are available within "deadline" microseconds
 from the beginning of the period.  In order to implement this behavior,
 every time the task wakes up, the scheduler computes a "scheduling deadline"
 consistent with the guarantee (using the CBS[2,3] algorithm). Tasks are then
 scheduled using EDF[1] on these scheduling deadlines (the task with the
 earliest scheduling deadline is selected for execution). Notice that the
 task actually receives "runtime" time units within "deadline" if a proper
 "admission control" strategy (see Section "4. Bandwidth management") is used
 (clearly, if the system is overloaded this guarantee cannot be respected).

 SCHED_DEADLINE [18] usa tres parámetros para gestionar las tareas, 
 denominados "runtime", "period" y "deadline". Una tarea de SCHED_DEADLINE
 deberia recibir "runtime" microsegundos de tiempo de ejecución cada
 "period" microsegundos, y esos "runtime" microsegundos estan disponibles 
 en los "deadline" microsegunods desde el comienzo del periodo. Para
 implementar este comportamiento cada vez que una tarea se despierta,
 el gestor de tareas calcula un "tiempo límite" que cumple esa garantía
 (usando el algoritmo CBS[2,3]). Las tareas son gestionadas usando EDF[1]
 sobre esos tiempos límites (la tarea con el siguente tiempo límite es
 seleccionada para su ejecución). Notese que la tarea realmente recibe
 "runtime" unidades de tiempo dentro de "deadline" si se ha seguido una
 estrategia correcta de "control de admisión (lea la sección
 "4. Bandwidth management") (claramente, si el sistem está sobrecargado
 esta garantia no se puede respetar).


 Summing up, the CBS[2,3] algorithm assigns scheduling deadlines to tasks so
 that each task runs for at most its runtime every period, avoiding any
 interference between different tasks (bandwidth isolation), while the EDF[1]
 algorithm selects the task with the earliest scheduling deadline as the one
 to be executed next. Thanks to this feature, tasks that do not strictly comply
 with the "traditional" real-time task model (see Section 3) can effectively
 use the new policy.

 Resumiendo el algoritmo CBS[2,3] asigna tiempos límites de ejecución a las
 tareas para que cada tarea pueda ejecutarse en su mayor parte cada periodo,
 evitando cualquier interferencia entre las distintas tareas (aislamiento de
 ancho de banda), mientras que el algoritmo EDF[1] selecciona la tarea con 
 el tiempo límite de ejecución más próximo como la siguiente tarea a ser 
 ejecutada. Gracias a esta característica, las teras que no cumplen 
 estrictamente con el modelo "tradiconal" de tarea en tiempo real (ver
 sección 3) pueden usar efectivamente la nueva política. 


 In more details, the CBS algorithm assigns scheduling deadlines to
 tasks in the following way:

 En más detalle, el algoritmo CBS asigna los tiempos límites para 
 las tareas de la siguiente forma: 

  - Each SCHED_DEADLINE task is characterized by the "runtime",
    "deadline", and "period" parameters;

  - Cada tarea SCHED_DEADLINE está caracterizada por los parámetros
    "runtime", "deadline", y "period".

  - The state of the task is described by a "scheduling deadline", and
    a "remaining runtime". These two parameters are initially set to 0;

  - El estado de una tarea está descrito por un "tiempo de finalización",
    y un "tiempo de ejecución restante". Estos dos parámetros
    inicialmente estan definidos a 0.

  - When a SCHED_DEADLINE task wakes up (becomes ready for execution),
    the scheduler checks if::

  - Cuando una tarea SCHED_DEADLINE se despierta (se convierte en
    disponible para ser ejecutada), el gestor de tareas verifica si::

                 remaining runtime                  runtime
        ----------------------------------    >    ---------
        scheduling deadline - current time           period


           tiempo restante de ejecución             runtime
        ----------------------------------    >    ---------
        tiempo de finalización - tiempo actual      period


    then, if the scheduling deadline is smaller than the current time, or
    this condition is verified, the scheduling deadline and the
    remaining runtime are re-initialized as

    entonces, si el timepo de finalización es menor que el tiempo actual,
    o esta condición se verifica, el tiempo de finalización y el tiempo
    restante de ejecución son re-inicializados como

         scheduling deadline = current time + deadline
         remaining runtime = runtime

         tiempo de finalización = tiempo actual + tiempo límite
         tiempo restante = runtime

    otherwise, the scheduling deadline and the remaining runtime are
    left unchanged;

    de otro modo, el tiempo de finalización y el tiempo restante 
    se dejan sin cambiar. 

  - When a SCHED_DEADLINE task executes for an amount of time t, its
    remaining runtime is decreased as::

  - Cuando una tarea  SCHED_DEADLINE se ejecuta por una cantidad
    de tiempo t, su tiempo de ejecución restate se decrementa como::

         remaining runtime = remaining runtime - t

         tiempo de ejecución restante = tiempo de ejecución restante - t

    (technically, the runtime is decreased at every tick, or when the
    task is descheduled / preempted);

    (técnicamente, el tiempo de ejecución se decrementa en cada tick,
    o cuando la tarea se vuelve a gestionar o es interrupida. 

  - When the remaining runtime becomes less or equal than 0, the task is
    said to be "throttled" (also known as "depleted" in real-time literature)
    and cannot be scheduled until its scheduling deadline. The "replenishment
    time" for this task (see next item) is set to be equal to the current
    value of the scheduling deadline;

  - Cuando el tiempo restante de ejecución llega a ser menor o igual que
    0 la tarea es "frenada" (también se concoe como "agotada" en la 
    literatura sobre tiempo-real). El "tiempo de reabastecimento" para 
    esta tarea (ver el siguiente punto) se ajusta para que sea igual al
    valor actual del tiempo de finalización de la tarea.

  - When the current time is equal to the replenishment time of a
    throttled task, the scheduling deadline and the remaining runtime are
    updated as::

  - cuando el tiempo actual es equivalente al tiempo de reabastecimento
    de una tarea extrangulada, el tiempo de finalización de la tarea y su 
    tiempo restante se actualizan como::

         scheduling deadline = scheduling deadline + period
         remaining runtime = remaining runtime + runtime

         tiempo de finalización = tiempo de finalización + periodo
         tiempo de ejecución restante = tiempo de ejecución restante + tiempo de ejecución 

 The SCHED_FLAG_DL_OVERRUN flag in sched_attr's sched_flags field allows a task
 to get informed about runtime overruns through the delivery of SIGXCPU
 signals.

 La bandera SCHED_FLAG_DL_OVERRUN en sched_attr en el campo sched_flags permite 
 a una tarea ser informada sobre el tiempo que se ha sobre-ejecutado recibiendo 
 una señal SIGXCPU. 


2.2 Bandwidth reclaiming
------------------------

2.2 Reclamación de ancho de banda
---------------------------------

 Bandwidth reclaiming for deadline tasks is based on the GRUB (Greedy
 Reclamation of Unused Bandwidth) algorithm [15, 16, 17] and it is enabled
 when flag SCHED_FLAG_RECLAIM is set.

 Reclamar ancho de banda para tareas con un tiempo de finalización se
 basa en el algoritmo GRUB (Greedy Reclamation of Unused Bandwidth) [15, 16, 17] 
 y se habilita dando valor a la bandera SCHED_FLAG_RECLAIM.

 The following diagram illustrates the state names for tasks handled by GRUB::

 El siguiente diagrama ilustra los nombres de los estados para las tareas
 que gestiona GRUB:: 

                             ------------
                 (d)        |   Active   |
              ------------->|            |
              |             | Contending |
              |              ------------
              |                A      |
          ----------           |      |
         |          |          |      |
         | Inactive |          |(b)   | (a)
         |          |          |      |
          ----------           |      |
              A                |      V
              |              ------------
              |             |   Active   |
              --------------|     Non    |
                 (c)        | Contending |
                             ------------


                             ------------
                 (d)        |   Activa   |
              ------------->|            |
              |             | Disputando |
              |              ------------
              |                A      |
          ----------           |      |
         |          |          |      |
         | Inactiva |          |(b)   | (a)
         |          |          |      |
          ----------           |      |
              A                |      V
              |              ------------
              |             |   Active   |
              --------------|     No    |
                 (c)        | Disputando |
                             ------------


 A task can be in one of the following states:

 Una tarea puede estar en uno de los siguientes estados:

  - ActiveContending: if it is ready for execution (or executing);
  - Activa disputando: si está lista para ejecutarse (o ejecutandose);

  - ActiveNonContending: if it just blocked and has not yet surpassed the 0-lag
    time;
  - Activa no disputando: si solo esta bloqueada y no ha sobrepasado el 
    tiemp de 0-lag

  - Inactive: if it is blocked and has surpassed the 0-lag time.
  - Inactiva: si está bloqueada o ha sobrepasado el tiempo 0-lag.

 State transitions:

 Transiciones de estados:

  (a) When a task blocks, it does not become immediately inactive since its
      bandwidth cannot be immediately reclaimed without breaking the
      real-time guarantees. It therefore enters a transitional state called
      ActiveNonContending. The scheduler arms the "inactive timer" to fire at
      the 0-lag time, when the task's bandwidth can be reclaimed without
      breaking the real-time guarantees.

      The 0-lag time for a task entering the ActiveNonContending state is
      computed as::

                        (runtime * dl_period)
             deadline - ---------------------
                             dl_runtime

      where runtime is the remaining runtime, while dl_runtime and dl_period
      are the reservation parameters.

  (a) Cuando una tarea se bloquea, esta no se vuelve inactiva inmediatamente
      ya que su ancho de banda no puede ser reclamado inmediatamente sin 
      romper las garantias de tiempo real. Por tanto entra en un estado de
      transición llamado 'ActiveNonContending'. El gestor de tareas carga
      el "temporizador de inactivdad" para disparalo en el momento de 0-lag,
      cuando el ancho de banda de la tarea pueda ser reclamado sin romper las
      garantias de tiempo real.

      El momento the 0-lag para una tarea que entra en el estado ActiveNonContending
      se calcula asi::

                                          (tiempo de ejecución * dl_period)
             tiempo de finalización  =  - ----------------------------------
                                                    dl_runtime


  (b) If the task wakes up before the inactive timer fires, the task re-enters
      the ActiveContending state and the "inactive timer" is canceled.
      In addition, if the task wakes up on a different runqueue, then
      the task's utilization must be removed from the previous runqueue's active
      utilization and must be added to the new runqueue's active utilization.
      In order to avoid races between a task waking up on a runqueue while the
      "inactive timer" is running on a different CPU, the "dl_non_contending"
      flag is used to indicate that a task is not on a runqueue but is active
      (so, the flag is set when the task blocks and is cleared when the
      "inactive timer" fires or when the task  wakes up).

  (b) Si la tarea se despierta antes de que se dispare el temporizador de
      inactividad, la tarea vuelve al estado ActiveNonConenteing y el temporizador
      de inactividad es cancelado. Además, si la tarea se despierta en una
      cola de ejecución distinta, la utilización de la tarea debe ser eliminada
      de la utilización de cola de ejecución anterior y añadida a la utilización
      activa de la nueva cola de ejecución. Para evitar carreras entre 
      una tarea despertando y una cola de ejecución mientras el temporizador de
      inactividad está ejecutandose en una CPU distinta, la bandera
      "dl_non_contending" se usa para indicar que una tarea no está en una cola 
      de ejecución pero está activa (asi, que la bandera es definida cuando la
      tarea está bloqueada y se borra cuando el temporizador de actividad 
      se dispara o cuando la tarea despierta).

  (c) When the "inactive timer" fires, the task enters the Inactive state and
      its utilization is removed from the runqueue's active utilization.

  (c) cuando el temporizador de inactividad se dispara, la tarea entra en
      un estado de inactividad y su utilización se elimina de la utilización
      activa de la cola de ejecución.

  (d) When an inactive task wakes up, it enters the ActiveContending state and
      its utilization is added to the active utilization of the runqueue where
      it has been enqueued

  (d) Cuando una tarea inactiva se despierta, esta entra en un estado ActiveContending
      y su utilización se añade a la utilización activa de la cola de ejecución 
      donde se ha encolado.

 For each runqueue, the algorithm GRUB keeps track of two different bandwidths:

 Para cada cola de ejecuión, el algoritmo GRUB monitoriza dos anchos de banda
 distintos:

  - Active bandwidth (running_bw): this is the sum of the bandwidths of all
    tasks in active state (i.e., ActiveContending or ActiveNonContending);

  - Ancho de bnada activo (running_bw): esta es la suma de los anchos de banda
    de todas las tareas en estado activo (i.e., ActiveContending o ActiveNonContending);

  - Total bandwidth (this_bw): this is the sum of all tasks "belonging" to the
    runqueue, including the tasks in Inactive state.

  - Ancho de banda total (this_bw): esta es la suma de todas la tareas que 
    perteneces a la cola de ejecución, incluidas las tareas en estado inactivo.

  - Maximum usable bandwidth (max_bw): This is the maximum bandwidth usable by
    deadline tasks and is currently set to the RT capacity.

  - Máximo ancho de banda usable (max_bw): Este es el máximo ancho de banda usable
    por las tareas con tiempo de finalización y actualmente es defindio a la 
    capacidad RT (tiempo real).


 The algorithm reclaims the bandwidth of the tasks in Inactive state.
 It does so by decrementing the runtime of the executing task Ti at a pace equal
 to

           dq = -(max{ Ui, (Umax - Uinact - Uextra) } / Umax) dt

 where:

  - Ui is the bandwidth of task Ti;
  - Umax is the maximum reclaimable utilization (subjected to RT throttling
    limits);
  - Uinact is the (per runqueue) inactive utilization, computed as
    (this_bq - running_bw);
  - Uextra is the (per runqueue) extra reclaimable utilization
    (subjected to RT throttling limits).

 El algoritmo reclama el ancho de banda de las tareas en estado inactivo.
 ESto lo hace decrementando el timepo de ejecición de la tarea en ejecución Ti 
 a una velocidad igual a: 

           dq = -(max{ Ui, (Umax - Uinact - Uextra) } / Umax) dt

 donde: 

  - Ui ies el ancho de banda de la tarea Ti;
  - Umax es la máxima utilización reclamanbe (sujeta a los límites RT
    de restricción);
  - Uinact es la utilización inactiva (por cola de ejecución), calculada como
    (this_bq - running_bw)
  - Uextra es el utilización extra reclamabel (por cola de ejecución) 
    (sujeta a los límites RT de restricción)
    

 Let's now see a trivial example of two deadline tasks with runtime equal
 to 4 and period equal to 8 (i.e., bandwidth equal to 0.5)::

 Veamos ahora un ejemplo trivial de dos tareas con un tiempo de finalización 
 con un tiempo de ejecución de 4 y un period igual a 8 (i.e., ancho de banda
 igual a 0.5)::

         A            Tarea T1
         |
         |                               |
         |                               |
         |--------                       |----
         |       |                       V
         |---|---|---|---|---|---|---|---|--------->t
         0   1   2   3   4   5   6   7   8


         A            Tarea T2
         |
         |                               |
         |                               |
         |       ------------------------|
         |       |                       V
         |---|---|---|---|---|---|---|---|--------->t
         0   1   2   3   4   5   6   7   8


         A            running_bw
         |
       1 -----------------               ------
         |               |               |
      0.5-               -----------------
         |                               |
         |---|---|---|---|---|---|---|---|--------->t
         0   1   2   3   4   5   6   7   8


  - Time t = 0:

    Both tasks are ready for execution and therefore in ActiveContending state.
    Suppose Task T1 is the first task to start execution.
    Since there are no inactive tasks, its runtime is decreased as dq = -1 dt.

  - Instante t = 0

    Ambas tareas estan listas para ejecutarse y por lo tanto en estado ActiveContending.
    Supongamos que la tarea T1 es la primera tarea en comenzár a ejecutarse.
    y que no hay tareas inactivas, su tiempo de ejecución disminuye según dq = -1 dt.

  - Time t = 2:

    Suppose that task T1 blocks
    Task T1 therefore enters the ActiveNonContending state. Since its remaining
    runtime is equal to 2, its 0-lag time is equal to t = 4.
    Task T2 start execution, with runtime still decreased as dq = -1 dt since
    there are no inactive tasks.

  - Instante t = 2

    Supongamos que la tarea T1 se bloquea.
    Entonces la tarea 1 entra en estado ActiveNonContending. Ya que su tiempo
    de ejecución restante es igual a 2, su tiempo 0-lag es igual a t = 4.
    La tarea T2 empieza a ejecutarse, con un tiempo de ejecución todavia 
    decrementado como dq = -1 dt ya que no hay tareas inactivas. 

  - Time t = 4:

    This is the 0-lag time for Task T1. Since it didn't woken up in the
    meantime, it enters the Inactive state. Its bandwidth is removed from
    running_bw.
    Task T2 continues its execution. However, its runtime is now decreased as
    dq = - 0.5 dt because Uinact = 0.5.
    Task T2 therefore reclaims the bandwidth unused by Task T1.

  - Instante t = 4:

    Este el es instante 0-lag para la tarea T1. ya que no se despertó hasta
    este momento, entra en estado Inactivo. Su ancho de banda es eliminado 
    de running_bw.

  - Time t = 8:

    Task T1 wakes up. It enters the ActiveContending state again, and the
    running_bw is incremented.

  - Instaante t = 8:

    La tarea T1 se despierta. Y entra en un estado ActiveContendig de nuevo,
    y se incrementa running_bw.


2.3 Energy-aware scheduling
---------------------------

2.3 Gestión de tareas según el consumo de energía 

 When cpufreq's schedutil governor is selected, SCHED_DEADLINE implements the
 GRUB-PA [19] algorithm, reducing the CPU operating frequency to the minimum
 value that still allows to meet the deadlines. This behavior is currently
 implemented only for ARM architectures.

 Cuado el útil del gestor de tareas cpfreq se elige, SCHED_DEADLINE implementa
 el algoritmo GRUP-PA [19], reduciendo la frecuencia de operación de las CPUs
 a su mínimo valor que permita alcanzár los tiempo finales de ejecución. Este
 comportamiento es el que está actualmente implementado para las arquitecturas
 ARM.

 A particular care must be taken in case the time needed for changing frequency
 is of the same order of magnitude of the reservation period. In such cases,
 setting a fixed CPU frequency results in a lower amount of deadline misses.

 Se debe tener un cuidado particular en caso de que el tiempo necesario para
 cambiar de frecuencia sea del mismo orden de magnitud que el periodo de 
 reserva. En esos caso, definir una frecuencia de CPU fija tiene como resulato
 una menor cantidad de tiempos de finalización fallidos. 


3. Scheduling Real-Time Tasks
=============================

3. Gestión de tareas en tiempo real
===================================

 ..  BIG FAT WARNING ******************************************************

 ..  GRAN GIGANTE AVISO ******************************************************

 .. warning::

   This section contains a (not-thorough) summary on classical deadline
   scheduling theory, and how it applies to SCHED_DEADLINE.
   The reader can "safely" skip to Section 4 if only interested in seeing
   how the scheduling policy can be used. Anyway, we strongly recommend
   to come back here and continue reading (once the urge for testing is
   satisfied :P) to be sure of fully understanding all technical details.

 .. ************************************************************************

 .. warning::

   Esta seccion contiene un (no exhaustivo) resumen en la teoría clásica
   de gestión de tareas, y como se aplica a SCHED_DEADLINE.
   El lector puede "a salvo" saltar hasta la Sección 4 si únicamente está
   interesado en ver cómo se puede usar las polítitgas de gestión. De todas
   maneras se recomienda volver aqui y continuar leyendo (una vez la
   urgencia por testear ha sido satisfecha :P) para asegurarse que se
   comprende completamente los detalles técnicos. 

 .. ************************************************************************


 There are no limitations on what kind of task can exploit this new
 scheduling discipline, even if it must be said that it is particularly
 suited for periodic or sporadic real-time tasks that need guarantees on their
 timing behavior, e.g., multimedia, streaming, control applications, etc.

 No hay límites en qué tipo de tarea pueda explotar esta nueva disciplina
 de gestión, aunque ha de ser dicho que es particularmente adaptada para
 tareas en tiempo real periódicas o esporádicas que necesiten garantias
 en su comportamiento en el tiempo, e.g., multimedia, streaming, control
 de aplicaciones, etc. 

3.1 Definitions
------------------------

3.1 Definiciones
------------------------

 A typical real-time task is composed of a repetition of computation phases
 (task instances, or jobs) which are activated on a periodic or sporadic
 fashion.
 Each job J_j (where J_j is the j^th job of the task) is characterized by an
 arrival time r_j (the time when the job starts), an amount of computation
 time c_j needed to finish the job, and a job absolute deadline d_j, which
 is the time within which the job should be finished. The maximum execution
 time max{c_j} is called "Worst Case Execution Time" (WCET) for the task.
 A real-time task can be periodic with period P if r_{j+1} = r_j + P, or
 sporadic with minimum inter-arrival time P is r_{j+1} >= r_j + P. Finally,
 d_j = r_j + D, where D is the task's relative deadline.
 Summing up, a real-time task can be described as


 Una tarea en tiempo real típica esta compuesta por una repetición de
 fases de computación (instacias de la tarea o trabajos) los cuales se
 activan a intervalos de tiempo periódicos o de forma esporádica. 
 Cada trabajo J_j (dond J_j es el j-ésimo trabajo de la tarea) está
 caracterizado por un tiempo de llegada r_j (el momento en el que el 
 trabajo empieza), una cantidad de tiempo de computación c_j necesario
 para finalziar el trabajo, y un instante de tiempo de finalización 
 absoluto d_j, el cual es el instante de tiempo en el cual el trabajo
 debería de estar realizado. El máximo tiempo de ejecución max{c_j}
 se llama "El peor caso de tiempo de ejecución"para la tarea (sus 
 siglás en inglés son WCET, "Worst Case Execution Time"). 
 Una tarea en tiempo real puede ser periódica con un period P si
 r_{j+1} = r_j + P, o en el caso de una ejecución esporadica con un
 tiemp mínimo de inter-llegada P es r_{j+1} >= r_j + P. Por último,
 d_j = r_j + D, donde D es el instante final de la tarea relativa. 
 Resuminedo, una tarea puede ser descrita como

	Task = (WCET, D, P)

        Tarea = (WCET, D, P)

 The utilization of a real-time task is defined as the ratio between its
 WCET and its period (or minimum inter-arrival time), and represents
 the fraction of CPU time needed to execute the task.

 La utilización de una tarea en tiempo real esta definida como cociente
 entre su WCET y su periodo (o mínimo tiempo inter-llegada), y representa
 la fracción de tiempo de la CPU que necesita para ejecutar la tarea. 

 If the total utilization U=sum(WCET_i/P_i) is larger than M (with M equal
 to the number of CPUs), then the scheduler is unable to respect all the
 deadlines.
 Note that total utilization is defined as the sum of the utilizations
 WCET_i/P_i over all the real-time tasks in the system. When considering
 multiple real-time tasks, the parameters of the i-th task are indicated
 with the "_i" suffix.
 Moreover, if the total utilization is larger than M, then we risk starving
 non- real-time tasks by real-time tasks.
 If, instead, the total utilization is smaller than M, then non real-time
 tasks will not be starved and the system might be able to respect all the
 deadlines.
 As a matter of fact, in this case it is possible to provide an upper bound
 for tardiness (defined as the maximum between 0 and the difference
 between the finishing time of a job and its absolute deadline).
 More precisely, it can be proven that using a global EDF scheduler the
 maximum tardiness of each task is smaller or equal than

 Si la utilización total U=suma(WCET_i/P_i) es mayor que M (siendo M
 igual al número de CPUs), entonces el gestor de tareas no puede alcanzar
 el tiempo de finalización de las tareas. 
 Note que el teimpo de utilización toatl esta definido como la suma de
 las utilizaciones WCET_i/P_i entre todas las tareas en tiempo real del 
 sistema. Cuando se conideran multiples tareas en tiempo real, los parámetros
 de la i-ésima tarea se indican con el sufijo "_i". 
 Es más, si la utilización total es mayour que M, entonces se tienen el 
 riesgo de extrangular las tareas que no son de tiempo real con las tareas
 que son de tiempo real.
 Es un hecho, que en este caso es posible indicar un límite superior
 para la tardanza (definida como el máximo entre 0 y intervalo de tiempo
 entre la finalización de un trabajo y su tiempo de finalización absoluto).
 Más precisamente, se puede probar que usando un gestor de tareas EDF la
 tardanza máxima de cara tarea es más pequeña o igual que
 

	((M − 1) · WCET_max − WCET_min)/(M − (M − 2) · U_max) + WCET_max

 where WCET_max = max{WCET_i} is the maximum WCET, WCET_min=min{WCET_i}
 is the minimum WCET, and U_max = max{WCET_i/P_i} is the maximum
 utilization[12].

 Donde WCET_max = max{WCET_i} es el máximo WCET, WCET_min=min{WCET_i}
 es el mínimo WCET, y U_max = max{WCET_i/P_i} es la máxima utilización[12].

3.2 Schedulability Analysis for Uniprocessor Systems
----------------------------------------------------

3.2 Análisis de gestión de tareas para sistemas de un único procesador
----------------------------------------------------------------------

 If M=1 (uniprocessor system), or in case of partitioned scheduling (each
 real-time task is statically assigned to one and only one CPU), it is
 possible to formally check if all the deadlines are respected.
 If D_i = P_i for all tasks, then EDF is able to respect all the deadlines
 of all the tasks executing on a CPU if and only if the total utilization
 of the tasks running on such a CPU is smaller or equal than 1.
 If D_i != P_i for some task, then it is possible to define the density of
 a task as WCET_i/min{D_i,P_i}, and EDF is able to respect all the deadlines
 of all the tasks running on a CPU if the sum of the densities of the tasks
 running on such a CPU is smaller or equal than 1:

 Si M=1 (un sistema de un único procesador), o en el caso de una gestíon 
 partida (cada tarea en tiempo real está estadisticamente asignada a una
 y solo úna CPU), es posible verificar formalmente si todas los instantes
 de la finalización de las tareas son respetadas.
 Si D_i = P_i para todas las tareas, entonces EDF es capaz de respetar 
 todas los instantes de finalización de todas las tareas ejecutadas en 
 una CPU si y solo si la utilización toal de las tareas ejecutandose en 
 dicha CPU es menor o igual a 1.
 Si D_i != P_i para alguna tarea, entonces es posible definr la densidad 
 de una tarea como WCET_i/min{D_i,P_i}, y EDF es capaz de respetar todas
 los instantes de finalización de todas las tareas ejecutandose en una
 CPU si la suma de densidades de las tareas ejecutandose en dicha CPU es 
 menor o igual a 1:

	sum(WCET_i / min{D_i, P_i}) <= 1

 It is important to notice that this condition is only sufficient, and not
 necessary: there are task sets that are schedulable, but do not respect the
 condition. For example, consider the task set {Task_1,Task_2} composed by
 Task_1=(50ms,50ms,100ms) and Task_2=(10ms,100ms,100ms).
 EDF is clearly able to schedule the two tasks without missing any deadline
 (Task_1 is scheduled as soon as it is released, and finishes just in time
 to respect its deadline; Task_2 is scheduled immediately after Task_1, hence
 its response time cannot be larger than 50ms + 10ms = 60ms) even if

 Es importante darse cuenta que esta condición es solo suficiente, y no necesaria:
 hay grupos de tareas que son gestionables, pero no respetan la condición.
 Por ejemplo, considere el grupo de tareas {Tarea_1, Tarea_2} compuesto por
 Tarea_1=(50ms,50ms,100ms) y Tarea_2=(10ms,100ms,100ms).
 EDF claramente puede gestionar las dos tareas sin perden ningún tiempo 
 de finalización (Tarea_1 es planificada tan pronto como se ordena, y finaliza
 justo a tiempo para respetar su tiempo de finalización; Tarea_2 es planificada
 justo después de la Tarea_1, y por tanto su tiempo de respuesta no puede
 ser mayour que 50ms + 10ms = 60ms) incluso si

	50 / min{50,100} + 10 / min{100, 100} = 50 / 50 + 10 / 100 = 1.1

 Of course it is possible to test the exact schedulability of tasks with
 D_i != P_i (checking a condition that is both sufficient and necessary),
 but this cannot be done by comparing the total utilization or density with
 a constant. Instead, the so called "processor demand" approach can be used,
 computing the total amount of CPU time h(t) needed by all the tasks to
 respect all of their deadlines in a time interval of size t, and comparing
 such a time with the interval size t. If h(t) is smaller than t (that is,
 the amount of time needed by the tasks in a time interval of size t is
 smaller than the size of the interval) for all the possible values of t, then
 EDF is able to schedule the tasks respecting all of their deadlines. Since
 performing this check for all possible values of t is impossible, it has been
 proven[4,5,6] that it is sufficient to perform the test for values of t
 between 0 and a maximum value L. The cited papers contain all of the
 mathematical details and explain how to compute h(t) and L.
 In any case, this kind of analysis is too complex as well as too
 time-consuming to be performed on-line. Hence, as explained in Section
 4 Linux uses an admission test based on the tasks' utilizations.

 Por supuesto es posible verificar la planificación exacta de tareas con
 D_i != P_i (mirando una condición que es tanto suficiente como necesaria),
 pero esto no se puede hacer mendiante la comparación de la utilización 
 total o la densidad con una constante. En vez de eso, se usa la proximación
 de la "demanda del procesador" calculando la cantidad toal de tiempo de
 CPU h(t) que es necesario por todas las tareas para respetar todas los
 tiempos de finalización en un intervalo de tamaño t, y comparando dicho 
 tiempo con el intervalo de tamaño t. Si h(t) es más pequeño que t (esto es,
 la cantidad de tiempo necesaria por las tareas en un intervalo de tiempo 
 de tamaño t es más pequeño que el tamaño del intervalo) para todas los 
 valores posibles de t, entonces EDF es capaz de planificar las tareas 
 respetando todos sus tiempos de finalización. ya que hacer esta verificación
 para todas los valores posibles de t es imposible, ha sido provado[4,5,6] 
 que es suficietne ejecutar el test para valores de t entre 0 y un máximo
 valor L. Las referencias citadas contienen todos los detalles matemáticos 
 y explican como calcular h(t) y L. 
 En cualquier caso, este tipo de analysys es demasiado complejo com también
 demasiado costoso en teimpo para ser ejecutado en linea. Luego, como se
 ha explicado en la Sección 4 Linux usa un test de admisión basado en la
 utilización de las tareas. 

3.3 Schedulability Analysis for Multiprocessor Systems
------------------------------------------------------

3.3 Análisis de gestión de tareas para sistemas con múltiples procesadores
--------------------------------------------------------------------------

 On multiprocessor systems with global EDF scheduling (non partitioned
 systems), a sufficient test for schedulability can not be based on the
 utilizations or densities: it can be shown that even if D_i = P_i task
 sets with utilizations slightly larger than 1 can miss deadlines regardless
 of the number of CPUs.

 En sistemas con múltiples procesadores con una gestión global de tareas
 EDF (en sistemas no partidos), un test suficiente para ver si es posible
 planificar las tareas no puede estar basado en las utilizaciones o 
 densidades: se puede demostrar que incluso si D_i = P_i los grupos 
 de tareas con utilizaciones ligeramente mayores a 1 pueden fallar en 
 alcanzar su tiempos de finalización objetivos de forma independiente al
 número de CPUs. 

 Consider a set {Task_1,...Task_{M+1}} of M+1 tasks on a system with M
 CPUs, with the first task Task_1=(P,P,P) having period, relative deadline
 and WCET equal to P. The remaining M tasks Task_i=(e,P-1,P-1) have an
 arbitrarily small worst case execution time (indicated as "e" here) and a
 period smaller than the one of the first task. Hence, if all the tasks
 activate at the same time t, global EDF schedules these M tasks first
 (because their absolute deadlines are equal to t + P - 1, hence they are
 smaller than the absolute deadline of Task_1, which is t + P). As a
 result, Task_1 can be scheduled only at time t + e, and will finish at
 time t + e + P, after its absolute deadline. The total utilization of the
 task set is U = M · e / (P - 1) + P / P = M · e / (P - 1) + 1, and for small
 values of e this can become very close to 1. This is known as "Dhall's
 effect"[7]. Note: the example in the original paper by Dhall has been
 slightly simplified here (for example, Dhall more correctly computed
 lim_{e->0}U).

 Consideremos un grupo de tareas {Tarea_1, ... Tarea_{M+1}} en un sistema
 con M CPUs, con la primera tarea Tarea_1=(P,P,P) teniendo un periodo,
 fecha de finalización relativa y WCET igual a P. El resto de las demás
 M tareas Tarea_i=(e,P-1,P-1) tienen de forma arbitraria un WCET ligeramente
 peor (indicado como "e") y un periodo más pequeño que el de la primera
 tarea. Por tanto, si todas las tareas se activan en el mismo instante t,
 el gestor EDF planifica esas M tareas primero (porque sus tiempos de
 finalización absolutos son igual a t + P -1, luego son memores que el 
 tiempo de finalización absoluto de la Tarea_1, que es t + P). Como
 resultado, la Tarea_1 solo puede ser planificada en el momento t + e, 
 y finalizará en el momento t + e + P, posterior a su tiempo de finalización
 absoluto. La utilización total del grupo de tareas es 
 U = M · e / (P - 1) + P / P = M · e / (P - 1) + 1, y para pequeños valores
 de e esta puede ser muy cercana a 1. Esto se conoce comoe el "Dhall's
 effect"[7]. Apunte: el ejemplo en el artículo original de Dhall ha sido
 ligeramente simplificado aqui (por ejemplo, Dhall calculó más precisamente
 lim_{e->0}U). 

 More complex schedulability tests for global EDF have been developed in
 real-time literature[8,9], but they are not based on a simple comparison
 between total utilization (or density) and a fixed constant. If all tasks
 have D_i = P_i, a sufficient schedulability condition can be expressed in
 a simple way:

 Test de planificación más complicados para el gestor global EDF han sido
 desarrollados en la literatura de tiempo-real[8,9], pero no están 
 basado en una simple comparación entre al utilización total (o densidad) 
 y una constante fija. Si todas las tareas tienen D_i = P_i, una condición 
 suficiente para la planificación puede ser expresada de manera sencilla
 como: 

	sum(WCET_i / P_i) <= M - (M - 1) · U_max

 where U_max = max{WCET_i / P_i}[10]. Notice that for U_max = 1,
 M - (M - 1) · U_max becomes M - M + 1 = 1 and this schedulability condition
 just confirms the Dhall's effect. A more complete survey of the literature
 about schedulability tests for multi-processor real-time scheduling can be
 found in [11].

 Donde U_max = max{WCET_i / P_i}[10]. Note que para U_max = 1, 
 M - (M - 1) · U_max es M - M + 1 = 1  y esta es la condición de planificación
 que confirma el efecto Dhall. Una revisión más completa de la literatura
 sobre tests para la gestión de tareas en tiempo-real en sistemas 
 multi-processador puede hallarse en [11].
 

 As seen, enforcing that the total utilization is smaller than M does not
 guarantee that global EDF schedules the tasks without missing any deadline
 (in other words, global EDF is not an optimal scheduling algorithm). However,
 a total utilization smaller than M is enough to guarantee that non real-time
 tasks are not starved and that the tardiness of real-time tasks has an upper
 bound[12] (as previously noted). Different bounds on the maximum tardiness
 experienced by real-time tasks have been developed in various papers[13,14],
 but the theoretical result that is important for SCHED_DEADLINE is that if
 the total utilization is smaller or equal than M then the response times of
 the tasks are limited.

 Como se ha visto, fomentar que la utilización total sea menor que M no
 garantiza que una gestión global EDF planifique las tareas sin puedan 
 fallar en alcanzar sus tiempos límites (en otras palabras, la gestión 
 EDF global no es un algoritmo de planificación de tareas óptimo). De 
 todas maneras una utilización menor que M es suficiente para garantizar que
 todas las tareas que no son de tiempo real no sean extranguladas y que la
 tardanza de las tareas en tiempo real tenga un límite superior[12]
 (como se comentó previamente). Diferentes límites en la tardanza 
 máxima que tienen las tareas en tiempo-real han sido desarrollados en 
 varios artículos[13,14], pero el resultado teórico importante para 
 SCHED_DEADLINE es que la utilización total es más pequeña o igual que M 
 cuando el tiempo de respuesta de las tareas está acotado. 

3.4 Relationship with SCHED_DEADLINE Parameters
-----------------------------------------------

 Finally, it is important to understand the relationship between the
 SCHED_DEADLINE scheduling parameters described in Section 2 (runtime,
 deadline and period) and the real-time task parameters (WCET, D, P)
 described in this section. Note that the tasks' temporal constraints are
 represented by its absolute deadlines d_j = r_j + D described above, while
 SCHED_DEADLINE schedules the tasks according to scheduling deadlines (see
 Section 2).
 If an admission test is used to guarantee that the scheduling deadlines
 are respected, then SCHED_DEADLINE can be used to schedule real-time tasks
 guaranteeing that all the jobs' deadlines of a task are respected.
 In order to do this, a task must be scheduled by setting:

 Finalmente, es importante comprender la relación entre los
 parámetros de SCHED_DEADLINE descritos en la Sección 2 (tiempo de ejecución,
 tiempo límite y periodo) y los parámetros de las tareas en tiempo real
 (WCET, D, P) descritos en esta sección. Notese que las restricciónes
 temporatles de las tareas están representadas por sus tiempos de
 finalización absolutios d_j = r_j + D descritos anteriormente, 
 mientras que SCHED_DEALINE planifica las tareas de acuerdo con los
 tiempos de finalización (ver Sección 2).
 Si un test de admisión se usa para garantizar que los tiempos de
 finalización planificados son respetados, entonces SCHED_DEADLINE puede
 ser usado para planificar las tareas en tiempo real garantiando que 
 todos los tiempos de finalización de las tareas son respetados. 
 Para hacer esto, una tareas debe ser planificado ajustando:

  - runtime >= WCET
  - deadline = D
  - period <= P

  - tiempo de ejecución >= WCET
  - tiempo de finalización = D
  - periodo <= P

 IOW, if runtime >= WCET and if period is <= P, then the scheduling deadlines
 and the absolute deadlines (d_j) coincide, so a proper admission control
 allows to respect the jobs' absolute deadlines for this task (this is what is
 called "hard schedulability property" and is an extension of Lemma 1 of [2]).
 Notice that if runtime > deadline the admission control will surely reject
 this task, as it is not possible to respect its temporal constraints.

 IOw, si tiempo de ejecución >= WAE y si el perido es <= P, entonces 
 los tiempos de finalización planificados y los tiempos de finalización 
 absolutos (d_j) coincidiran, así que un correcto control de admisión 
 permite respetar los tiempos de finalización absolutos de los trabajos
 para esa tarea (esto es lo que se conoce como "propiedad de planificación
 dura" y es una extensión del Lama 1 de [2]). Notese que si el tiempo de
 ejecución > tiempo de finalización el control de admisión seguramente
 rechazará esa tarea, ya que no sería posible repetar sus restriciones 
 temporales.

 References:
 Referencias:

  1 - C. L. Liu and J. W. Layland. Scheduling algorithms for multiprogram-
      ming in a hard-real-time environment. Journal of the Association for
      Computing Machinery, 20(1), 1973.
  2 - L. Abeni , G. Buttazzo. Integrating Multimedia Applications in Hard
      Real-Time Systems. Proceedings of the 19th IEEE Real-time Systems
      Symposium, 1998. http://retis.sssup.it/~giorgio/paps/1998/rtss98-cbs.pdf
  3 - L. Abeni. Server Mechanisms for Multimedia Applications. ReTiS Lab
      Technical Report. http://disi.unitn.it/~abeni/tr-98-01.pdf
  4 - J. Y. Leung and M.L. Merril. A Note on Preemptive Scheduling of
      Periodic, Real-Time Tasks. Information Processing Letters, vol. 11,
      no. 3, pp. 115-118, 1980.
  5 - S. K. Baruah, A. K. Mok and L. E. Rosier. Preemptively Scheduling
      Hard-Real-Time Sporadic Tasks on One Processor. Proceedings of the
      11th IEEE Real-time Systems Symposium, 1990.
  6 - S. K. Baruah, L. E. Rosier and R. R. Howell. Algorithms and Complexity
      Concerning the Preemptive Scheduling of Periodic Real-Time tasks on
      One Processor. Real-Time Systems Journal, vol. 4, no. 2, pp 301-324,
      1990.
  7 - S. J. Dhall and C. L. Liu. On a real-time scheduling problem. Operations
      research, vol. 26, no. 1, pp 127-140, 1978.
  8 - T. Baker. Multiprocessor EDF and Deadline Monotonic Schedulability
      Analysis. Proceedings of the 24th IEEE Real-Time Systems Symposium, 2003.
  9 - T. Baker. An Analysis of EDF Schedulability on a Multiprocessor.
      IEEE Transactions on Parallel and Distributed Systems, vol. 16, no. 8,
      pp 760-768, 2005.
  10 - J. Goossens, S. Funk and S. Baruah, Priority-Driven Scheduling of
       Periodic Task Systems on Multiprocessors. Real-Time Systems Journal,
       vol. 25, no. 2–3, pp. 187–205, 2003.
  11 - R. Davis and A. Burns. A Survey of Hard Real-Time Scheduling for
       Multiprocessor Systems. ACM Computing Surveys, vol. 43, no. 4, 2011.
       http://www-users.cs.york.ac.uk/~robdavis/papers/MPSurveyv5.0.pdf
  12 - U. C. Devi and J. H. Anderson. Tardiness Bounds under Global EDF
       Scheduling on a Multiprocessor. Real-Time Systems Journal, vol. 32,
       no. 2, pp 133-189, 2008.
  13 - P. Valente and G. Lipari. An Upper Bound to the Lateness of Soft
       Real-Time Tasks Scheduled by EDF on Multiprocessors. Proceedings of
       the 26th IEEE Real-Time Systems Symposium, 2005.
  14 - J. Erickson, U. Devi and S. Baruah. Improved tardiness bounds for
       Global EDF. Proceedings of the 22nd Euromicro Conference on
       Real-Time Systems, 2010.
  15 - G. Lipari, S. Baruah, Greedy reclamation of unused bandwidth in
       constant-bandwidth servers, 12th IEEE Euromicro Conference on Real-Time
       Systems, 2000.
  16 - L. Abeni, J. Lelli, C. Scordino, L. Palopoli, Greedy CPU reclaiming for
       SCHED DEADLINE. In Proceedings of the Real-Time Linux Workshop (RTLWS),
       Dusseldorf, Germany, 2014.
  17 - L. Abeni, G. Lipari, A. Parri, Y. Sun, Multicore CPU reclaiming: parallel
       or sequential?. In Proceedings of the 31st Annual ACM Symposium on Applied
       Computing, 2016.
  18 - J. Lelli, C. Scordino, L. Abeni, D. Faggioli, Deadline scheduling in the
       Linux kernel, Software: Practice and Experience, 46(6): 821-839, June
       2016.
  19 - C. Scordino, L. Abeni, J. Lelli, Energy-Aware Real-Time Scheduling in
       the Linux Kernel, 33rd ACM/SIGAPP Symposium On Applied Computing (SAC
       2018), Pau, France, April 2018.


4. Bandwidth management
=======================

4. Gestión del ancho de banda
=============================

 As previously mentioned, in order for -deadline scheduling to be
 effective and useful (that is, to be able to provide "runtime" time units
 within "deadline"), it is important to have some method to keep the allocation
 of the available fractions of CPU time to the various tasks under control.
 This is usually called "admission control" and if it is not performed, then
 no guarantee can be given on the actual scheduling of the -deadline tasks.

 Como se ha mencionado, para que la planificación por tiempo de finalización
 sea efectivo y util (esto es, que sea capaz de proveer un tiempo de ejecución
 dado antes de un tiempo de finalización), es importante tener un método para
 gestionar los fracciones de tiempo de ejecución de la CPU con respecto a 
 las varias tareas bajo control. Esto normalmente se llama "control de 
 admisión" y si no se lleva a cabo, entonces no se puede dar ninguna 
 garantía en el tiempo de finalización de las tareas planificadas. 

 As already stated in Section 3, a necessary condition to be respected to
 correctly schedule a set of real-time tasks is that the total utilization
 is smaller than M. When talking about -deadline tasks, this requires that
 the sum of the ratio between runtime and period for all tasks is smaller
 than M. Notice that the ratio runtime/period is equivalent to the utilization
 of a "traditional" real-time task, and is also often referred to as
 "bandwidth".
 The interface used to control the CPU bandwidth that can be allocated
 to -deadline tasks is similar to the one already used for -rt
 tasks with real-time group scheduling (a.k.a. RT-throttling - see
 Documentation/scheduler/sched-rt-group.rst), and is based on readable/
 writable control files located in procfs (for system wide settings).
 Notice that per-group settings (controlled through cgroupfs) are still not
 defined for -deadline tasks, because more discussion is needed in order to
 figure out how we want to manage SCHED_DEADLINE bandwidth at the task group
 level.

 Como ya se enunció en la Sección 3, una condición necesaria que ha de ser
 repetada para planificar correctamente un conjunto de tareas de tiempo
 real es que la utilizaicón total ha de ser menor que M. Cuando se habla 
 de tareas con tiempo de finalización eso requiere que la suma de el ratio
 entre el tiempo de ejecución y el periodo para todas las tareas sea 
 menor que M. Notese que el ratio tiempo de ejecución/periodo es equivalente
 a la utilización de una tarea en tiempo real "tradicional", y también es
 habitualmente llamado "ancho de banda". 
 La interfaz usada para el controlar el ancho de banda que puede ser
 reservado en una CPU para tareas con tiempo de finalización es similar al
 que se usa ya para grupos de tareas en tiempo real (a.k.a RT-throttling -
 lease Documentation/scheduler/sched-rt-group.rst), y esta basado en
 ficheros de lectura/escritura situados en profs (para ajustos de todo
 el sistema). Notar que los ajustes por-grup (controlados por medio de
 cgroupsfs) todavía no estan definidos para las taréas con tiempo de 
 finalización, porque se necisata aclarar que es necesiario para
 definir como se quiere gestionar el ancho de banda de SCHED_DEADLINE
 en el entorno de grupos de tareas.

 A main difference between deadline bandwidth management and RT-throttling
 is that -deadline tasks have bandwidth on their own (while -rt ones don't!),
 and thus we don't need a higher level throttling mechanism to enforce the
 desired bandwidth. In other words, this means that interface parameters are
 only used at admission control time (i.e., when the user calls
 sched_setattr()). Scheduling is then performed considering actual tasks'
 parameters, so that CPU bandwidth is allocated to SCHED_DEADLINE tasks
 respecting their needs in terms of granularity. Therefore, using this simple
 interface we can put a cap on total utilization of -deadline tasks (i.e.,
 \Sum (runtime_i / period_i) < global_dl_utilization_cap).

 La principal diferencia entre el gestión de ancho de banda con tareas 
 con tiempo de finalización y el RT-throttling es que las tareas con 
 ancho de finalización tieen un ancho de banda propio (mientas que las
 de tiempo real no), y por tanto no se necesita un mecanismo de restricción
 superior para favorecer en ancho de banda deseado. En otras palabras, esto
 significa que los parametros de la interzaz únicamente son usado en el 
 control de admisión (i.e., cuando el usuario llama sched_setattr()).
 La planificación se ejecuta entonces considerando los parámetros de las
 tareas actuales, así que el ancho de banda es reservado para las tareas
 de SCHED_DEADLINE respetando sus necesidades en terminos de granularidad.
 Por tanto usando este simple interfaz se puede limitar la utilización 
 total de las tareas con tiempo de finalización
 (i.e., \Sum (runtime_i / period_i) < global_dl_utilization_cap).


4.1 System wide settings
------------------------

4.1 Ajustes generales del sistema
---------------------------------

 The system wide settings are configured under the /proc virtual file system.

 Los ajustes generales del sistema se configuran en el sistema de archivos
 virtual /proc.
  

 For now the -rt knobs are used for -deadline admission control and the
 -deadline runtime is accounted against the -rt runtime. We realize that this
 isn't entirely desirable; however, it is better to have a small interface for
 now, and be able to change it easily later. The ideal situation (see 5.) is to
 run -rt tasks from a -deadline server; in which case the -rt bandwidth is a
 direct subset of dl_bw.

 Por ahora los ajustes de -rt se usan para la admisión de control de las 
 tareas de tiempo de finalización (-deadline) y se ajusta contra el tiempo
 de las tareas en tiempo real. Nos damos cuenta que esto no es enteramente
 deseable; de todos modos, por ahora es mejor tener una pequeña interfaz, 
 y que sea posible cambiarlo facilmente después. La situación ideal (ver 5)
 es ejecutar las tareas en tiempo real desde un servidor de tareas con tiempo
 de finalización; en ese caso el ancho de banda de las tareas en tiempo real
 es un subgrupo del ancho de banda de las tareas con tiempo de finalización. 

 This means that, for a root_domain comprising M CPUs, -deadline tasks
 can be created while the sum of their bandwidths stays below:

 Esto significa que para un dominio raiz que comprenda M CPUs, las
 tareas con tiempo de finalización pueden ser creadas mientras que la
 suma de sus anchos de banda está por debajo de:

   M * (sched_rt_runtime_us / sched_rt_period_us)

 It is also possible to disable this bandwidth management logic, and
 be thus free of oversubscribing the system up to any arbitrary level.
 This is done by writing -1 in /proc/sys/kernel/sched_rt_runtime_us.

 Esto es tambien posible para desactivar la lógica de gestion del ancho
 de banda, y por tanto liberar de sobre planificación el sistema a 
 un nivel arbitrario. Esto se hace escribiendo -1 en
 /proc/sys/kernel/sched_rt_runtime_us.


4.2 Task interface
------------------

4.2 Interfaz de las tareas
--------------------------

 Specifying a periodic/sporadic task that executes for a given amount of
 runtime at each instance, and that is scheduled according to the urgency of
 its own timing constraints needs, in general, a way of declaring:

 Especificar una tarea periódica/esporádica que se ejecuta por una 
 determinada cantidad de tiempo de ejecución cada vez, y que esta sea
 planificada de acuerdo a la urgencia de sus restricciones de tiempo, 
 en general es una forma de declarar:

  - a (maximum/typical) instance execution time,
  - a minimum interval between consecutive instances,
  - a time constraint by which each instance must be completed.

  - un (máximo/típico) tiempo de ejecución de instancias.
  - un intervalo mínimo entre instancias consecutivas.
  - una restricción de tiempo en la que cada instancia ha de ser completada.

 Therefore:

  * a new struct sched_attr, containing all the necessary fields is
    provided;
  * the new scheduling related syscalls that manipulate it, i.e.,
    sched_setattr() and sched_getattr() are implemented.

 Por tanto:
  * Se provee una nueva estructura sched_attr, con todos los campos 
    necesarios;
  * Las nuevas llamadas al sistema para la planificación de la tarea,
    sched_setattr() y sched_getattr() han sido implementadas.

 For debugging purposes, the leftover runtime and absolute deadline of a
 SCHED_DEADLINE task can be retrieved through /proc/<pid>/sched (entries
 dl.runtime and dl.deadline, both values in ns). A programmatic way to
 retrieve these values from production code is under discussion.

 Para depurar, el restos del tiempo de ejecución y los tiempos de 
 finalización absolutos de una tarea de SCHED_DEADLINE pueden obtenerse
 en /proc/<pid>/sched (los datos de dl.runtime y dl.deadline, ambos
 valores en ns). Un modo programático de obtener esos valores desde
 código en producción se está discutiendo.


4.3 Default behavior
---------------------

4.3 Comportamiento por predeterminado
-------------------------------------

 The default value for SCHED_DEADLINE bandwidth is to have rt_runtime equal to
 950000. With rt_period equal to 1000000, by default, it means that -deadline
 tasks can use at most 95%, multiplied by the number of CPUs that compose the
 root_domain, for each root_domain.
 This means that non -deadline tasks will receive at least 5% of the CPU time,
 and that -deadline tasks will receive their runtime with a guaranteed
 worst-case delay respect to the "deadline" parameter. If "deadline" = "period"
 and the cpuset mechanism is used to implement partitioned scheduling (see
 Section 5), then this simple setting of the bandwidth management is able to
 deterministically guarantee that -deadline tasks will receive their runtime
 in a period.

 El comportamiento predeterminado para el ancho de banda de SCHED_DEADLINE es
 tener rt_runtime igual a 950000. Con rt_period igual a 1000000, por defecto,
 esto significa que las tareas con tiempo de finalización pueden usar casi 
 el 95%, multiplicado por el número de CPUs que compongan el dominio raiz,
 para cada dominio raiz. 
 Esto signifca que las tareas que no sean -dealine reciviran al menos un 5%
 de tiempo de la CU, y que las tareas -deadline recibiran su tiempo de 
 ejecución con un retraso del peor-caso-posible garantizado con respeco al 
 parametro de "deadline". Si "deadline" = "period" y el mecanismo cpuset se 
 usa para implementar una gestion de tarias particionado (ver seccion 5), entonces
 este simple ajuste del ancho de banda es capaz de garantizar deterministicamente
 que  las tareas -dealine recibiran su tiempo de ejecución en un periodo.

 Finally, notice that in order not to jeopardize the admission control a
 -deadline task cannot fork.

 Por último, notar para no amenazar el control de admisión una tarea 
 -deadline no puede hacer `fork`.


4.4 Behavior of sched_yield()
-----------------------------

4.4 comportamiento de sched_yield()
-----------------------------------

 When a SCHED_DEADLINE task calls sched_yield(), it gives up its
 remaining runtime and is immediately throttled, until the next
 period, when its runtime will be replenished (a special flag
 dl_yielded is set and used to handle correctly throttling and runtime
 replenishment after a call to sched_yield()).

 Cuando una tarea SCHED_DEADLINE llama sched_yield(), abandona su 
 tiempo de ejecución restante y es frenada inmediatamente, hasta el 
 próximo periodo, cuando su tiempo de ejecución será renovado (una  
 marca especial dl_yielding se activa y se usa para gestionar 
 correctamente el frenado y la renovación del tiempo de ejecución 
 despúes de la llamada a sched_yield()).

 This behavior of sched_yield() allows the task to wake-up exactly at
 the beginning of the next period. Also, this may be useful in the
 future with bandwidth reclaiming mechanisms, where sched_yield() will
 make the leftoever runtime available for reclamation by other
 SCHED_DEADLINE tasks.

 Este comportamiento de sched_yield permite a la tarea despertase 
 exáctamente al comiendo del siguiente periodo. También, esto puede ser
 útil en el futuro con mecanísmos para reclamar ancho de banda, donde
 sched_yeld() permita disponer del tiempo de ejecución disponible para
 ser reclamado por otras tareas SCHED_DEADLINE. 



5. Tasks CPU affinity
=====================

5. Afinidad de las tareas con los CPU
=====================================

 -deadline tasks cannot have an affinity mask smaller that the entire
 root_domain they are created on. However, affinities can be specified
 through the cpuset facility (Documentation/admin-guide/cgroup-v1/cpusets.rst).

 - Las taread deadline no pueden tener una máscara de afinidad menor
 que el root_domain completo en el que son creadas. De todos modos, 
 las finidades puede ser definidas mediante los grupos de cpu (cpuset)
 (Documentation/admin-guide/cgroup-v1/cpusets.rst).

5.1 SCHED_DEADLINE and cpusets HOWTO
------------------------------------

5.1 CÓMOS de SCHED_DEADLINE y cpusets
--------------------------------------

 An example of a simple configuration (pin a -deadline task to CPU0)
 follows (rt-app is used to create a -deadline task)::

 Un ejemplo de una configuración sencilla (asociación de una tarea
 deadline a CPU0) a continuación (la applicación rt-app se usa para
 crear una tarea -deadline)::

   mkdir /dev/cpuset
   mount -t cgroup -o cpuset cpuset /dev/cpuset
   cd /dev/cpuset
   mkdir cpu0
   echo 0 > cpu0/cpuset.cpus
   echo 0 > cpu0/cpuset.mems
   echo 1 > cpuset.cpu_exclusive
   echo 0 > cpuset.sched_load_balance
   echo 1 > cpu0/cpuset.cpu_exclusive
   echo 1 > cpu0/cpuset.mem_exclusive
   echo $$ > cpu0/tasks
   rt-app -t 100000:10000:d:0 -D5 # it is now actually superfluous to specify
				  # task affinity

   rt-app -t 100000:10000:d:0 -D5 # ahora es superficial especificat la 
				  # afinidad de la tarea

6. Future plans
===============

6. Planes futuros
=================

 Still missing:

 Todavía por hacer:

  - programmatic way to retrieve current runtime and absolute deadline
  - refinements to deadline inheritance, especially regarding the possibility
    of retaining bandwidth isolation among non-interacting tasks. This is
    being studied from both theoretical and practical points of view, and
    hopefully we should be able to produce some demonstrative code soon;
  - (c)group based bandwidth management, and maybe scheduling;
  - access control for non-root users (and related security concerns to
    address), which is the best way to allow unprivileged use of the mechanisms
    and how to prevent non-root users "cheat" the system?

  - una forma programática para obtener el tiempo de ejecución y el instante 
    límite absoulto
  - mejoras en la herencia de los tiempos límites, especialmente el lo 
    relacionado con mantener el aislamiento del ancho de banda entre tareas
    que no interaccionan. Esto se ha estudiado tanto desde el punto de 
    vista teórico como práctico, y se deberiamos ser capaces de presentar 
    código funcional pronto;
  - gestión del ancho de banda basado en groupos y quizás en gestión de tareas.
  - control de accesos para usuarios que no son root (y otras inquietudes
    relativas a la seguridad de las direcciones), ¿cuál es el mejor uso 
    de permitir acceso sin privilegios de los mecanismos y como evitar que
    usuarios que no son root "engañen" al sistema? 

 As already discussed, we are planning also to merge this work with the EDF
 throttling patches [https://lore.kernel.org/r/cover.1266931410.git.fabio@helm.retis] but we still are in
 the preliminary phases of the merge and we really seek feedback that would
 help us decide on the direction it should take.

 Como ya se comentó, estamos planeando unir este trabajo con los parches
 de restricciones [https://lore.kernel.org/r/cover.1266931410.git.fabio@helm.retis]  pro 
 cotinuamos en las fases preliminares de la unión y estamos buscando impresiones 
 que nos puedan ayudar a decidir qué dirección tomar. 


TODO: COMPLETE...!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Appendix A. Test suite
======================

 The SCHED_DEADLINE policy can be easily tested using two applications that
 are part of a wider Linux Scheduler validation suite. The suite is
 available as a GitHub repository: https://github.com/scheduler-tools.

 The first testing application is called rt-app and can be used to
 start multiple threads with specific parameters. rt-app supports
 SCHED_{OTHER,FIFO,RR,DEADLINE} scheduling policies and their related
 parameters (e.g., niceness, priority, runtime/deadline/period). rt-app
 is a valuable tool, as it can be used to synthetically recreate certain
 workloads (maybe mimicking real use-cases) and evaluate how the scheduler
 behaves under such workloads. In this way, results are easily reproducible.
 rt-app is available at: https://github.com/scheduler-tools/rt-app.

 Thread parameters can be specified from the command line, with something like
 this::

  # rt-app -t 100000:10000:d -t 150000:20000:f:10 -D5

 The above creates 2 threads. The first one, scheduled by SCHED_DEADLINE,
 executes for 10ms every 100ms. The second one, scheduled at SCHED_FIFO
 priority 10, executes for 20ms every 150ms. The test will run for a total
 of 5 seconds.

 More interestingly, configurations can be described with a json file that
 can be passed as input to rt-app with something like this::

  # rt-app my_config.json

 The parameters that can be specified with the second method are a superset
 of the command line options. Please refer to rt-app documentation for more
 details (`<rt-app-sources>/doc/*.json`).

 The second testing application is a modification of schedtool, called
 schedtool-dl, which can be used to setup SCHED_DEADLINE parameters for a
 certain pid/application. schedtool-dl is available at:
 https://github.com/scheduler-tools/schedtool-dl.git.

 The usage is straightforward::

  # schedtool -E -t 10000000:100000000 -e ./my_cpuhog_app

 With this, my_cpuhog_app is put to run inside a SCHED_DEADLINE reservation
 of 10ms every 100ms (note that parameters are expressed in microseconds).
 You can also use schedtool to create a reservation for an already running
 application, given that you know its pid::

  # schedtool -E -t 10000000:100000000 my_app_pid

Appendix B. Minimal main()
==========================

 We provide in what follows a simple (ugly) self-contained code snippet
 showing how SCHED_DEADLINE reservations can be created by a real-time
 application developer::

   #define _GNU_SOURCE
   #include <unistd.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <time.h>
   #include <linux/unistd.h>
   #include <linux/kernel.h>
   #include <linux/types.h>
   #include <sys/syscall.h>
   #include <pthread.h>

   #define gettid() syscall(__NR_gettid)

   #define SCHED_DEADLINE	6

   /* XXX use the proper syscall numbers */
   #ifdef __x86_64__
   #define __NR_sched_setattr		314
   #define __NR_sched_getattr		315
   #endif

   #ifdef __i386__
   #define __NR_sched_setattr		351
   #define __NR_sched_getattr		352
   #endif

   #ifdef __arm__
   #define __NR_sched_setattr		380
   #define __NR_sched_getattr		381
   #endif

   static volatile int done;

   struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
   };

   int sched_setattr(pid_t pid,
		  const struct sched_attr *attr,
		  unsigned int flags)
   {
	return syscall(__NR_sched_setattr, pid, attr, flags);
   }

   int sched_getattr(pid_t pid,
		  struct sched_attr *attr,
		  unsigned int size,
		  unsigned int flags)
   {
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
   }

   void *run_deadline(void *data)
   {
	struct sched_attr attr;
	int x = 0;
	int ret;
	unsigned int flags = 0;

	printf("deadline thread started [%ld]\n", gettid());

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = 10 * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	ret = sched_setattr(0, &attr, flags);
	if (ret < 0) {
		done = 0;
		perror("sched_setattr");
		exit(-1);
	}

	while (!done) {
		x++;
	}

	printf("deadline thread dies [%ld]\n", gettid());
	return NULL;
   }

   int main (int argc, char **argv)
   {
	pthread_t thread;

	printf("main thread [%ld]\n", gettid());

	pthread_create(&thread, NULL, run_deadline, NULL);

	sleep(10);

	done = 1;
	pthread_join(thread, NULL);

	printf("main dies [%ld]\n", gettid());
	return 0;
   }
