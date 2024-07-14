=====================
CFS Bandwidth Control
=====================

=============================
CFS Control de ancho de banda
=============================

.. note::
   This document only discusses CPU bandwidth control for SCHED_NORMAL.
   The SCHED_RT case is covered in Documentation/scheduler/sched-rt-group.rst

.. note::
   Este documento únicamente trata el control de ancho de banda de CPUs 
   para SCHED_NORMAL. El caso de SCHED_RT se trata en Documentation/scheduler/sched-rt-group.rst

CFS bandwidth control is a CONFIG_FAIR_GROUP_SCHED extension which allows the
specification of the maximum CPU bandwidth available to a group or hierarchy.

El control de ancho de banda es una extension CONFIG_FAIR_GROUP_SCHED que 
permite especificar el máximo uso disponible de CPU para un grupo o una jerarquía.

The bandwidth allowed for a group is specified using a quota and period. Within
each given "period" (microseconds), a task group is allocated up to "quota"
microseconds of CPU time. That quota is assigned to per-cpu run queues in
slices as threads in the cgroup become runnable. Once all quota has been
assigned any additional requests for quota will result in those threads being
throttled. Throttled threads will not be able to run again until the next
period when the quota is replenished.

El ancho de banda permitido para un grupo se especifica usando una cuota y
un periodo. Dentro de cada periodo (microsegundos), un grupo de tareas son 
ejecutadas hasta la cuota de microsegundos de tiempo de CPU. Esa cuota
asignada, en colas por cada cpu, en hilos de ejecución en el que el cgroup 
es ejecutable. Una vez toda la cuota ha sido asignada cualquier petición 
adicional de cuota resultará en esos hilos de ejecución siendo extrangulado.
Los hilos de ejecución acelerados, no serán capaces de ejecutase de nuevo 
hasta el siguiente periodo cuando la cuota sea repuesta.

A group's unassigned quota is globally tracked, being refreshed back to
cfs_quota units at each period boundary. As threads consume this bandwidth it
is transferred to cpu-local "silos" on a demand basis. The amount transferred
within each of these updates is tunable and described as the "slice".

La cuota sin asignar de un grupo es monitorizada globalmente, siendo 
restablecidas cfs_quota unidades al final de cada periodo. Según los
hilos de ejecución van consumiedo este ancho de banda, este se 
transfiere a los "silos" de las cpu-locales en base a la demanda. La
cantidad tranferida en cada una de esas actualizaciones es ajustable y 
es descrito como un "slice". 

// TODO: traducir "silos" como "reservas"??

Burst feature
-------------

Funcionalidad de rafaga
-----------------------

This feature borrows time now against our future underrun, at the cost of
increased interference against the other system users. All nicely bounded.

Esta funcionalidad coge prestado tiempo ahora, que en un futuro tendrá que
devolver, con el coste de una mayor interferecia hacia los otros usuarios
del sistema. Todo acotado perfectamente. 

Traditional (UP-EDF) bandwidth control is something like:

El tradicional control de ancho de banda (UP-EDF) es algo como:

  (U = \Sum u_i) <= 1

La utilización de una CPU (U) es igual a la suma de todas las
utilizaciones de las tareas en esa CPU (u_i), y la utilización 
ha de ser menor o igual que 1 (100% de utilización)

This guaranteeds both that every deadline is met and that the system is
stable. After all, if U were > 1, then for every second of walltime,
we'd have to run more than a second of program time, and obviously miss
our deadline, but the next deadline will be further out still, there is
never time to catch up, unbounded fail.

Esto garantiza dos cosa: que cada tiempo límite de ejecución es cumplido
y que el sistema es estable. De todas formas, si U fuese > 1, entonces
por cada segundo de tiempo de reloj de una tarea, tendríamos que 
ejecutar más de un segundo de tiempo de programa, y obviamente no 
cumpliriamos con el tiempo límite de ejecucion de la tarea, pero en 
el siguiente periodo de ejecución el tiempo límite de la tareá 
estaría todavia más lejos, y nunca se tendría tiempo de alcanzar 
la ejecución, cayendo así en un fallo no acotado. 

The burst feature observes that a workload doesn't always executes the full
quota; this enables one to describe u_i as a statistical distribution.

La funcionalidad de ráfaga vigila que una carga de CPU no se ejecute 
siempre con su máxima cuota; esto permite que se pueda describir u_i
como una distribución estádistica.

For example, have u_i = {x,e}_i, where x is the p(95) and x+e p(100)
(the traditional WCET). This effectively allows u to be smaller,
increasing the efficiency (we can pack more tasks in the system), but at
the cost of missing deadlines when all the odds line up. However, it
does maintain stability, since every overrun must be paired with an
underrun as long as our x is above the average.

Por ejemplo, se tiene u_i = {x,e}_i, donde x es el p(95) y x+e p(100)
(el tradicional WCET (WCET:Worst Case Execcution Time: son las siglas
en inglés para "peor tiempo de ejecución")). Esto efectivamente permite
a u ser más pequeño, aumentando la eficiencia (podemos ejecutar más 
tareas en el sistema), pero al coste de perder el momento límite de 
ejecución de la tarea, cuando coincidan las peores probabilidades. 
De todas formas, si se mantiene la estabilidad, ya que cada 
sobre-ejecución se empareja con una infra-ejecución en tanto x esté 
por encima de la media.

That is, suppose we have 2 tasks, both specify a p(95) value, then we
have a p(95)*p(95) = 90.25% chance both tasks are within their quota and
everything is good. At the same time we have a p(5)p(5) = 0.25% chance
both tasks will exceed their quota at the same time (guaranteed deadline
fail). Somewhere in between there's a threshold where one exceeds and
the other doesn't underrun enough to compensate; this depends on the
specific CDFs.

Es decir, suponganse que se tienen 2 tareas, ambas especificamente 
con p(95), entonces tenemos p(95)*p(95) = 90.25% de probabilidad de
que ambas tareas se ejecuten dentro de su cuota asignada y todo 
salga bien. Al mismo tiempo se tiene que p(5)*p(5) = 0.25% de 
probabilidad que ambas tareas excedan su cuota de ejecución (fallo
garantizado de su tiempo final de ejecucion). En algún punto por 
en medio, hay un umbral donde una tarea excede su tiempo límite de
ejecución y la otra no, de forma que se compensan; esto depende en 
los específicos de CDFs.

At the same time, we can say that the worst case deadline miss, will be
\Sum e_i; that is, there is a bounded tardiness (under the assumption
that x+e is indeed WCET).

Al mismo tiempo, se puede decir que el peor caso de sobrepasar el 
tiempo límite de ejecución será \Sum e_i; esto es una tardanza acotada
(asumiendo que x+e es de hecho el WCET).

The interferenece when using burst is valued by the possibilities for
missing the deadline and the average WCET. Test results showed that when
there many cgroups or CPU is under utilized, the interference is
limited. More details are shown in:
https://lore.kernel.org/lkml/5371BD36-55AE-4F71-B9D7-B86DC32E3D2B@linux.alibaba.com/

La interferencia cuando se usa una ráfaga se evalua por la posibilidades
de fallar en el cumplimiento del tiempo límite y el promedio de WCET.
Los resultados the tests han mostrado que cuando hay muchos cgroups o 
uan CPU esta infra-utilizada, la interferencia es más limitada. Más detalles
se aportan en: https://lore.kernel.org/lkml/5371BD36-55AE-4F71-B9D7-B86DC32E3D2B@linux.alibaba.com/

Management
----------

Gestión:
--------

Quota, period and burst are managed within the cpu subsystem via cgroupfs.

Cuota, periodo y ráfaga se se gestionan dentro del subsitema de cpu por medio 
de cgroupfs.

.. note::
   The cgroupfs files described in this section are only applicable
   to cgroup v1. For cgroup v2, see
   :ref:`Documentation/admin-guide/cgroup-v2.rst <cgroup-v2-cpu>`.

.. note::
   Los archivos cgroupfs descritos en esta seccion solo se aplican a el
   cgroup v1. Para cgroup v2, referirse a :ref:`Documentation/admin-guide/cgroup-v2.rst <cgroup-v2-cpu>`.

- cpu.cfs_quota_us: run-time replenished within a period (in microseconds)
- cpu.cfs_period_us: the length of a period (in microseconds)
- cpu.stat: exports throttling statistics [explained further below]
- cpu.cfs_burst_us: the maximum accumulated run-time (in microseconds)

The default values are::

Los valores por defecto son::

	cpu.cfs_period_us=100ms
	cpu.cfs_quota_us=-1
	cpu.cfs_burst_us=0

A value of -1 for cpu.cfs_quota_us indicates that the group does not have any
bandwidth restriction in place, such a group is described as an unconstrained
bandwidth group. This represents the traditional work-conserving behavior for
CFS.

Un valor de -1 para cpu.cfs_quota_us indica que el grupo no tiene ninguna
restricción de ancho de banda aplicado, ese grupo se describe como un grupo
con ancho de banda sin restringir. Esto representa el comportamiento
tradicional para CFS.

Writing any (valid) positive value(s) no smaller than cpu.cfs_burst_us will
enact the specified bandwidth limit. The minimum quota allowed for the quota or
period is 1ms. There is also an upper bound on the period length of 1s.
Additional restrictions exist when bandwidth limits are used in a hierarchical
fashion, these are explained in more detail below.

Asignar cualquier valor (válido) y positivo no menor que cpu.cfs_burst_us 
definirá el límite del ancho de banda. La cuota mínima permitida para para 
la cuota o periodo es 1ms. Hay también un límite superior en la duración del
periodo de 1s. Existen restricciones adicionales cuando los límites de 
ancho de banda se usan de manera jerárquica, estós se explican en mayor 
detalle más adelante. 

Writing any negative value to cpu.cfs_quota_us will remove the bandwidth limit
and return the group to an unconstrained state once more.

Asignar cualquier valor negatiov a cpu.cfs_quota_us elimiará el límite de
ancho de banda y devolverá de nuevo al grupo a un estádo sin restricciones.

A value of 0 for cpu.cfs_burst_us indicates that the group can not accumulate
any unused bandwidth. It makes the traditional bandwidth control behavior for
CFS unchanged. Writing any (valid) positive value(s) no larger than
cpu.cfs_quota_us into cpu.cfs_burst_us will enact the cap on unused bandwidth
accumulation.

Un valor de 0 para cpu.cfs_burst_us indica que el grupo no puede acumular
ningún ancho de banda sin usar. Esto hace que el control del comportamiento
tradicional del ancho de banda para CFS no cambie. Definir cualquier valor
(valido) positivo no mayor que cpu.cfs_quota_us en cpu.cgs_burst_us definirá
el limite on el ancho de banda acumulado no usado. 

Any updates to a group's bandwidth specification will result in it becoming
unthrottled if it is in a constrained state.

Cualquier actualizacion a las especificaciones del ancho de banda usado
por un grupo resultará en que se deje de limitar si está en un estado 
restringido. 

System wide settings
--------------------

Ajustes globales del sistema
----------------------------

For efficiency run-time is transferred between the global pool and CPU local
"silos" in a batch fashion. This greatly reduces global accounting pressure
on large systems. The amount transferred each time such an update is required
is described as the "slice".

Por eficiencia el tiempo de ejecución es tranferido desde una reserva global 
y el "silo" de una CPU local en lotes. Esto reduce en gran medida la presión 
por la contabilidad en grandes sistemas. La cantidad transferida cada vez
que se requiere una actualización se describe como "slice".

This is tunable via procfs::

Esto es ajustable via procfs::

	/proc/sys/kernel/sched_cfs_bandwidth_slice_us (default=5ms)

Larger slice values will reduce transfer overheads, while smaller values allow
for more fine-grained consumption.

Valores de "slice" más grandes reducirán el costo de transferencia, mientras
que valores más pequeños permitirán un control más fino del consumo. 

Statistics
----------

Estadísticas
------------

A group's bandwidth statistics are exported via 5 fields in cpu.stat.

Las estadisticas del ancho de banda de un grupo se exponen en 5 campos en cpu.stat.

cpu.stat:

- nr_periods: Number of enforcement intervals that have elapsed.
- nr_throttled: Number of times the group has been throttled/limited.
- throttled_time: The total time duration (in nanoseconds) for which entities
  of the group have been throttled.
- nr_bursts: Number of periods burst occurs.
- burst_time: Cumulative wall-time (in nanoseconds) that any CPUs has used
  above quota in respective periods.

- nr_periods: Número de intervalos aplicados que han pasado. 
- nr_throttled: Número de veces que el grupo ha sido restringido/limitado.
- throttled_time: La duración de tiempo total (en nanosegundos) en las
  que las entidades del grupo han sido limitadas.
- nr_bursts: Número de periodos en que ha currido una ráfaga.
- burst_time: Tiempo acumulado (en nanosegundos) en la que una CPU ha
  usado más de su cuota en los respectivos periodos. 


This interface is read-only.

Este interface es de solo lectura.

Hierarchical considerations
---------------------------

Consideraciones jerárquicas
---------------------------

The interface enforces that an individual entity's bandwidth is always
attainable, that is: max(c_i) <= C. However, over-subscription in the
aggregate case is explicitly allowed to enable work-conserving semantics
within a hierarchy:


El interface refuerza que el ancho de banda de una entidad individual
sea siempre conseguible, esto es: max(c_i) <= C. De todas maneras, 
la sobre-subscripción en el caso agregado está explicitamente permitida
para permitir semanticas de conservación de trabajo dentro de una
jerarquia.


  e.g. \Sum (c_i) may exceed C

  e.g. \Sum (c_i) puede superar C

[ Where C is the parent's bandwidth, and c_i its children ]

[ Donde C es el ancho de banda de el padre, y c_i es el hijo ]


There are two ways in which a group may become throttled:

	a. it fully consumes its own quota within a period
	b. a parent's quota is fully consumed within its period

Hay dos formas en las que un grupo puede ser limitado:

        a. este consume totalmete su propia cuota en un periodo.
        b. la quota de padre es consumida totalmente en su periodo.

In case b) above, even though the child may have runtime remaining it will not
be allowed to until the parent's runtime is refreshed.

En el caso b) anterior, incluso si el hijo puediera tener tiempo de 
ejecución restatne, este no le será permitido hasta que el tiempo de 
ejecución del padre sea actualizado. 


CFS Bandwidth Quota Caveats
---------------------------
Once a slice is assigned to a cpu it does not expire.  However all but 1ms of
the slice may be returned to the global pool if all threads on that cpu become
unrunnable. This is configured at compile time by the min_cfs_rq_runtime
variable. This is a performance tweak that helps prevent added contention on
the global lock.

The fact that cpu-local slices do not expire results in some interesting corner
cases that should be understood.

For cgroup cpu constrained applications that are cpu limited this is a
relatively moot point because they will naturally consume the entirety of their
quota as well as the entirety of each cpu-local slice in each period. As a
result it is expected that nr_periods roughly equal nr_throttled, and that
cpuacct.usage will increase roughly equal to cfs_quota_us in each period.

For highly-threaded, non-cpu bound applications this non-expiration nuance
allows applications to briefly burst past their quota limits by the amount of
unused slice on each cpu that the task group is running on (typically at most
1ms per cpu or as defined by min_cfs_rq_runtime).  This slight burst only
applies if quota had been assigned to a cpu and then not fully used or returned
in previous periods. This burst amount will not be transferred between cores.
As a result, this mechanism still strictly limits the task group to quota
average usage, albeit over a longer time window than a single period.  This
also limits the burst ability to no more than 1ms per cpu.  This provides
better more predictable user experience for highly threaded applications with
small quota limits on high core count machines. It also eliminates the
propensity to throttle these applications while simultaneously using less than
quota amounts of cpu. Another way to say this, is that by allowing the unused
portion of a slice to remain valid across periods we have decreased the
possibility of wastefully expiring quota on cpu-local silos that don't need a
full slice's amount of cpu time.

The interaction between cpu-bound and non-cpu-bound-interactive applications
should also be considered, especially when single core usage hits 100%. If you
gave each of these applications half of a cpu-core and they both got scheduled
on the same CPU it is theoretically possible that the non-cpu bound application
will use up to 1ms additional quota in some periods, thereby preventing the
cpu-bound application from fully using its quota by that same amount. In these
instances it will be up to the CFS algorithm (see sched-design-CFS.rst) to
decide which application is chosen to run, as they will both be runnable and
have remaining quota. This runtime discrepancy will be made up in the following
periods when the interactive application idles.

Examples
--------
1. Limit a group to 1 CPU worth of runtime::

	If period is 250ms and quota is also 250ms, the group will get
	1 CPU worth of runtime every 250ms.

	# echo 250000 > cpu.cfs_quota_us /* quota = 250ms */
	# echo 250000 > cpu.cfs_period_us /* period = 250ms */

2. Limit a group to 2 CPUs worth of runtime on a multi-CPU machine

   With 500ms period and 1000ms quota, the group can get 2 CPUs worth of
   runtime every 500ms::

	# echo 1000000 > cpu.cfs_quota_us /* quota = 1000ms */
	# echo 500000 > cpu.cfs_period_us /* period = 500ms */

	The larger period here allows for increased burst capacity.

3. Limit a group to 20% of 1 CPU.

   With 50ms period, 10ms quota will be equivalent to 20% of 1 CPU::

	# echo 10000 > cpu.cfs_quota_us /* quota = 10ms */
	# echo 50000 > cpu.cfs_period_us /* period = 50ms */

   By using a small period here we are ensuring a consistent latency
   response at the expense of burst capacity.

4. Limit a group to 40% of 1 CPU, and allow accumulate up to 20% of 1 CPU
   additionally, in case accumulation has been done.

   With 50ms period, 20ms quota will be equivalent to 40% of 1 CPU.
   And 10ms burst will be equivalent to 20% of 1 CPU::

	# echo 20000 > cpu.cfs_quota_us /* quota = 20ms */
	# echo 50000 > cpu.cfs_period_us /* period = 50ms */
	# echo 10000 > cpu.cfs_burst_us /* burst = 10ms */

   Larger buffer setting (no larger than quota) allows greater burst capacity.
