 http://www.computer.org/sevocab

**Real-time**. (1) problem, system, or application that is concurrent and has timing constraints whereby incoming events must be processed within a given timeframe (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary) (2) pertaining to a system or mode of operation in which computation is performed during the actual time that an external process occurs, in order that the computation results can be used to control, monitor, or respond in a timely manner to the external process (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary)

**Latency**. (1) time interval between the instant at which an instruction control unit issues a call for data and the instant at which the transfer of data is started (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary)." Copyright©, 2018, IEEE. Used by permission."

**Throughput**. (1) amount of work that can be performed by a computer system or component in a given period of time (ISO/IEC/IEEE 24765:2017 Systems and software engineering-Vocabulary) (2) rate (i.e., the average number per time unit with respect to the rating interval) of all tasks of a task type submitted to the SUT (ISO/IEC 14756:1999 Information technology -- Measurement and rating of performance of computer-based software systems, 4.24) Note: Usually throughput is defined by the rate of terminated tasks during a period of time. " Copyright©, 2018, IEEE. Used by permission."

**jitter**: Is the variation in time, or the uncernainity on the time between the expected time at which an event should take place and the real time at which it takes place... It can be expressed as an average, or as a maximum variation.



What is known as a real-time system:
=====================================

In everyday life, a real-time system can be thought, quite obviously, as a system that performs in real-time... However,
in the domain of embedded systems, this definition is lacking a bit... A real-time system is defined as a system that
can react and perform inside a defined time-window or elapsed time, might be that time, seconds, milli-seconds, micro-senconds or
minutes or any time ... what is the key-point is inside a defined time period. That comes to mean, that whatever function, it
will be done, inside a bounded time.

It is usually seen as reat-time systems are death-line oriented insted of throught-put oriented (like servers).

Under the name of real-time systems, sometimes more details are defined.

- hard real-time system: that system in case it misses a death-line it results in risk of lifes, damage to propierties, significant financial loss. For example a flight control system.
- soft real-time system: that system in case it misses a death-line it results in a loss of the service or quality of the service. For example: video or audio streaming


DETERMINISTIC SYSTEMS:
=====================
A deterministic system is a system in which no randomness is involved in the development of future states of the system. A deterministic
model will thus always produce the same output from a given starting condition or initial state. A system is deterministic when it 
is always possible to know in advance what will be the next state of the sytem, for the given state, the action and the enviroment of
the system. 

The time peridod, after which the scheduling pattern repits itself is known as: hyperperiod (H)

To define and work with a deterministic system, is what we want when developing real-time systems, that is due that if we are 
sure how the system is going to behave, then it is easier to proof that it is real-time system with bounded response times.

The opposite of a deterministic system is knwons as a non-deterministic system or also as a stocastic system, and in it the outcome of 
the next system state is modeled as a probabilistic distribution function.
 
 
What makes algorithms non-deterministic?
========================================

A variety of factors can cause an algorithm to behave in a way which is not deterministic, or non-deterministic:

 - If it uses external state other than the input, such as user input, a global variable, a hardware timer value, a random value,
or stored disk data.
 - If it operates in a way that is timing-sensitive, for example if it has multiple processors writing to the same data at the same time. In this case, the precise order in which each processor writes its data will affect the result.
 - If a hardware error causes its state to change in an unexpected way.
 
Although real programs are rarely purely deterministic, it is easier for humans as well as other programs to reason about programs
that are. For this reason, most programming languages and especially functional programming languages make an effort to prevent
the above events from happening except under controlled conditions.

The prevalence of multi-core processors has resulted in a surge of interest in determinism in parallel programming and challenges
of non-determinism have been well documented. A number of tools to help deal with the challenges have been
proposed to deal with deadlocks and race conditions.

As a side note to this topic, many times the use of cache memories in real-time systems in not encoraged due they make more difficult to
calculate the memory access time, and then make all the system much harder to consider as deterministic and repeateable. As a workaround, 
you can always identify the worst case scenario, that in this case means, that no memory cache is used, in that case you are not
taking into account the advantage of the cache memory when identifing memory access/read/write times. Also the dynamic allocation
of memory is non-deterministic (the use of malloc(), new(), free() and delete()...) this is due depending on the amount of free memory
the memory algorithm allocation can take and indefined time to find a big enought memory position. 


Morfology of tasks
==================

A defined function is defined by a Task. The tasks consists on some data, and a continuos execution of a process, usually this is named
a Job.

```
function Task()
{
 int data;
 int period=1000; //ms.
 int job_number=0;
 while(1)
  {
    Job(data);
    job_number++;
    sleep(period);
  }
}
```

there are some tasks definitions:

- P: period of the task - the time it takes between two consecutive executions of the taks
- e: execution time of the task.- how long does it take the job execution of a task.
- D: Dead-line of the task - the time goal at which the task must be finished.
- r: release time of a task- the time point at which a task can be scheduled for execution. 
Any previous time point to r, is suppoused that the given task cannot be executed for whatever reason.

The term: "hyper-period" is the name give to the smallest common multiple of all the tasks periods.

the term: "feasability window" is the time between the release time of a task, and its dead-line.

the term: "jitter", is the variation in time, or the uncernainity on the time between the expected time at which an event should take place and the real time
at which it takes place... It can be expressed as an average, or as a maximum variation.


Scheduling tasks for real-time systems:
======================================

We want to comply with time constrictions and functionality constrictions.

A schedule algorithm, is the method used to make a decision on the execution order of taks. In real time systems the goal of the
scheduling method it to handle all the tasks of the system in such a way that all the dead-lines for each task are met.

According to this concept, several task statuses can be defined:

- READY STATE: It's not executed at the moment, it is in standby, ready to start execution, when the squedule, signals it.
  
- RUNNING STATE: When the squedule task is Ready, and is selected for execution, it start its action, and now is Running. (it can be 
Blocked, like when it need to way for some data)

- BLOCKED STATE: When a Running Task is running, it can be blocked for several reasons. That means that this task is not running any
more, and cannot be squeduled at the next squeduling point. This can happen, when that Task is in a delay, waiting data to be send, or
receiving data. When the delay runs out, then the Task, moves its state to Ready Task, and it can be scheduled again.

- SUSPENSION STATE: If the logic of the system evaluates that this task should not be scheduled again. 


WHAT IS A FEASEABLE SCHEDULE:
==============================


A schedule that never loses a death line is called FEASEABLE, this depends on its schedule algorithm.

a set of tasks is said to be scheaduable if at least it is possible to implement a feaseble schedule for that group of tasks.

A scheduling algorithm is OPTIMUN SCHEDULING ALGORITHM it if always generates a FEASEABLE schedule.

Scheduling example:

```
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->

0     1     2     3     4     5     6     7     8     9     10
```

And three tasts: T1, T2 and T3:


T - task
T1 -task 1. time(T1) = 1
T2 -task 2. time(T2) = 0.5
T3 -task 3. time(T3) = 3

```
 ____    __     ________________
|    |  |  |   |                |
| T1 |  |T2|   |      T3        |
|____|  |__|   |________________|
```

With the deathlines acording to the figure below:


D - death-line
D1 -death-line task1 = 2
D2 -death-line tast2 = 2.5
D3 -death-line tast3 = 5

```
           D1 D2             D3
            |  |              |
            V  V              V
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0     1     2     3     4     5     6     7     8     9     10
```

The schedule may want to allocate the T3, the first, because it might be the most important one:


```
           D1 D2             D3
            |  |              |
            V  V              V
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0     1     2     3     4     5     6     7     8     9     10
 ________________ ____ __  
|                |    |  |
|      T3        | T1 |T2|  
|________________|____|__|

```

- but, by doing so, we make the Task1, and Task2, miss their death lines.

This squeduler is not feaseble, even thougth Task3, might be the most important task.

But if we change the squedule, so it choose first T1, and then T2, and then T3, we see:

```
           D1 D2             D3
            |  |              |
            V  V              V
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0     1     2     3     4     5     6     7     8     9     10
 __________________________ 
|    |  |                  |
| T1 |T2|        T3        |          
|____|__|__________________|
```
 
Then all three task meet their deathlines. 

So now our sistem has became feasible!!  

In many systems, is not just order of the next possible task, but you have to take into account the relationship between tasks, because 
ones can be dependent of the results of others tasks.- This states the problem of priority of tasks, - and sometimes we found the 
problem of priority inversion, if we are not careful.


inter-TASKS DEPENDENCE:

Sometimes, is usual, that some tasks (jobs) depend on others, because the need to keep a precedence, or because, the
need some data to be processed by previous tasks. This is expressed as: Ja > Jb > Jc. 

a note of caution: When this tasks dependences is not-handled properly, in the worst case, the system may fail due what it is known 
as race conditions, or priority inversions ... this is a topic to be aware of, an to handle with care, its efects might results 
cathastrophyc... as reference check for the famous error with the priority-inversion of the Mars rover.


NON-PREENTIVE SYSTEMS:
======================

A system which runs jobs until its completion and then schedules the next job, is refered as NON-PREENTIVE system


PRE-EMPTIVE SYSTEMS:
====================

 In a Job is running, and is stopped, for running another job, and then it is call again, and it continues, where it have stoped, then
 this schedule type is known as a pre-emptive system.
 
 So a PRE-EMPTIVE SYSTEM is that one that can stop the current process, perfom another second process, and then again, continue the fist
 process, where it was left.
 
 For a scheduler to be pre-emptive, the scheduler must be able to save the current status (state) of the actual task, and then switch to another
 another task. 
 
 To be able to switch to another tasks, and afterwards retake the original task, some data is needed to be stored... the PC (program counter)
 (the line of the code), the status of the processor, and the value of the variables (registers).
 
 The process of switching context, usually is triggered by a timer, provided by de OS, when the timer triggers the interrupt, this makes
 the OS, run a routine call, __IRS__(), (ISR stands for Interruption Routine Service), first thing it does is block the interrupts, so nothing can change its process. Then it stores
 the regitsters, to the task stack -using architecture specific, assembly code- 
 
 ```
 Void __ISR__(){
 cli(); //disable interrupts - clear interrupts
 stores_context(); 
 next_job();
 load_context();
 sei(); //enable interrupts - set interrupts
 reti(); //return - return from isr
 }
 ```
 
 Then the schedule algorithm decides on what will be the next task, and then loads the context back to the new task, because this
 was saved last time the task was interrumped. Now the system is ready to continue executing. The OS enables interrupts again, and 
 then returns from the ISR.
 
 A side note to this topic: This procedure of context switch, takes some time, and is refered as the "Context Switch overhead",
 and must be taken into account, when planning a real-time system and its timeline. Too much context switching may also cause a
 penalty in the system performance. Also note, that preentive systems, will need at least a little bit more of memory with regard with 
 a non-preentive systems, due they need to store the state and the context in the switching of the tasks.
 
 
 
 SCHEDULER TYPES:
 ===============
 
 According to the factor that drives the scheduler, there is two tipes:
 
 - STATIC DRIVEN SCHEDULERS: The tasks are scheduled according to system clock. The schedule is inmutable, it means is always the same.
 
 - EVENT DRIVEN SCHEDULERS: The tasks are scheduled according to events, like: a timer timeout, the end of a task, an interruption...
 
Some schedulers perform better that others depending on the given tasks. To decide what scheduler is the best option, you 
have to understand the differences between each scheduler strategies and how they work.

Event driven scheduled, or dynamic schedulers have some advantes, like they can react and adjust to aperiodic jobs, or they can allocate 
the right amount of CPU in data-driven systems, or jobs can be re-scheduled according to a change in priorities.


STATIC SCHEDULER (aka CLOCK DRIVEN SCHEDULER):
==============================================

An static scheduler, is simple and predictable, and these are two very appropiated and desirable properties for real-time systems.

The scheduling of the tasks is defined off-line, this means there is no over-head time when switching the tasks. On the other hand
the static scheduler is not flexible, as the schedule is fixed, so it is not possible to remove or add tasks to the system. Also,
if the code of a task is modified, the scheduler must be re-calculated, because the execution time of the task, has been modifed.

The static scheduler is defined in a table, with 't' and 'T'. 

```
t - is the scheduling time (trigger time of the job)
T - is the Task
D - dead-lines
```

The scheduling policy is the one that defines the tasks in the timeline in a way that no dead-line is violated. 

A drawback of this scheudling policy, is that the tasks order, cannot be modified in execution time. 

An easy test to verify that a schedulig policy is feaseble, this is done by means of calculating the utilization of the system: that 
is: to calculate how much time the CPU needs to for each task, whith how much time is left without performing tasks, (this is known
as 'holes' in the scheduling timeline). For this, we need to know, the execution time of each task, and how often the tasks re-occour, 
that is the period of the task.

the utilization is the sum of all the task's execution times (e) , divided by their periods (P):

U = S(1->n) e_i/P_i

This is an exclusion rule: in the case the utilization is bigger or equal to 1, then we can conclude that the system is NOT feaseble. In that case, a task
should be removed, and a new schedule must be develop. But in the case the utilization is lower than one, that doesn't prove that
the schedule is feaseable, because for example, some tasks can collide, or the death-lines cannot be fulfilled.

Example:

```
 ·    P      e      D
 
 T1   3      1      3
 T2   4      1      4
 T3   10     2      10

- P: perido of the task. How often it has to be run
- e: execution time. How long does it take to run the task
- D: dead-line
 
```

 So the Utilization is:   U = 1/3 + 1/4  + 2/10 = 0.78
 
 Remember, what this means is that we cannot guarantee that this schedule is NOT feaseable, ... but this cannot also
 guarantee us that the schedule is feaseable.
 
 To clarify, the utilization test can prove that a schedule is not feasible, ... but it cannot prove
 that a schedule is feasible... there may be cases, that make the schedule also unfeasible. 

- Advantage: Its very effective
- Disadvange: It is not flexible.

TICK SCHEDULER
==============

The system, recalculates the best task to be run, at constant intervals, fixed when a given timer runs-out, so an interruption 
is triggered, and the next job, that fits the task with the highest priority, can be launched. The period of interruption and 
scheduling is named as the 'tick' of the system. So the tasks are always scheduled at regular times when the 'tick' interrups
the execution flow. 

The drawback of this scheme, is that with frequent context and task switches, the scheduling overhead is
increased. If a high priority task is running and it is interrupted at the 'tick' time, but as it is the highest priority task
and it is not blocked, it will be selected again as the task to be executed, so in this event, the context switch caused by
the scheduling policy was completelly unnecesary.

There is another drawback, a 'ready' task, must wait for a new 'tick' to be scheduled, so this also can cause a delay on
the system. In the worst case, the whole 'tick' period. How ever, this scheduling method is very popular (i.e: it is used in
FreeRTOS)

 
ROUND-ROBIN SCHEDULING
======================

Round-robin scheduling is based on the time-sharing policy. The tasks are ordered in a FIFO fashion, and the tasks are removed
when they are executed, the tasks is run for a given fixed time, and if the task wasn't finished, 
then it is put back at the last place in the FIFO queue. So, the response time to schedule a task, depends on the lenght 
of the task queue, but not on the needed execution time of each task.

As a downside is that this policy don't uses priorities to consider the schedule of tasks, so a low priority tasks, actually gets the
same exection time as a high priority task. this can be improved, taking into account the 'weigths' of each tasks, so the tasks
will take more or less execution time, depending into it's execution time.

- Disadvantage: It doesn't take into account priorities. Although there are implementations of schedulers based on priorities queues with round-robin schemes.


CYCLIC SCHEDULING
=================

The cyclic structure scheduler, aims to get the best of the flexibility of a tick scheduler, with the performance of the 
static scheduler. This policy uses fix periods for schedule the tasks, so it removes all the unnecesary interruptions not needed,
it removes all the no needed ticks, and the remaining interruption periods is known as a frame, only at this points, the scheduling
will take place. At the beginning of the frame, the scheduler decides the jobs to be done in the NEXT frame. It can also try to
predict dead-line misses at the beginning of the frame, an try to have an error correction action or mitigation. 

So the key question, is to define the best frame length. If the frame is too short, the context switch overhead will penalice the system
performance, on the other hand a small frame is better to ensure the feaseability of the system. If the frame too big, will mean less scheduling points, this reduces the penalty of the context switch, but the death-lines
might not be guaranteed. So the goal, is to get the largest frame possible that can guarantee the dead-lines for the jobs.

Calculation of the frame size:

The Hiper-period (H) (this is the time at witch the schedule starts to repeat it-self), is divided in equal sizes 'f'.
So the number of frames (F) in  the hiper-period: H; this is F = H/f

      HyperPeriod (H)  = frame number (F) * frame size(f) 

the goal is to get the biggest frame size (f) that complies with:

1- All the jobs must be able to fit into one frame so: f >= max(ei) forall i

2- In case the size of the frame (f) divides the hiperperiod (H) evenly, we don't need to consider other sizes, due all tasks
will fit in every frame period.

3- We think of: candidate frames: which are all the possible frame sizes that comply whit the previous rule (2), one of this
candidate frames will be the best fitted for our schedule.

 
FIXED PRIORITY SCHEDULING
========================

In the fixed priority schedule, the priority of the taks is what drives the scheduling policy

There are many tipes to schedule taks, some strategies are:
 - FIFO: first in first out
 - LIFO: last in first out
 - SETF: shortest execution time first
 - LETF: longest execution time first
 - Priority based
 
 
MONOTONIC SCHEDULING
====================

Monotonic scheduling has the advantage when scheduling periodic jobs, becase they  base the selection of tasks executions, 
on the time to death line or periods. That implies that is easier to systematically plan the system. So monotonic schedulers
are simple jet effective because they can addapt the priorities of the tasks implicity during runtime.

The advantage of monotonic scheduling systems is the system verification. There are verification methods that allows us to say if
a monotonic scheduling is feasible, based on periods, execution time, and tasks deadlines.

two monotonic scheduler will be covered:
- the rate monotonic scheduler (RM).
- the deadline monotonic scheduler (DM).

### LIMITATIONS IN THE RATE MONOTONIC THEORY

- requires that the priorities are fixed
- doesn't consider the importace of auxiliar service in addition to or instead of their request frequency or priority
- Simplification of the model assuming T=D
- Not considering additional resources needs, like shared memory neeeded at the same time as the CPU.
- assuming that real-time services will be required on a peridic basis

RATE MONOTONIC SCHEDULER:
=========================

The Rate Monotonic policy states that a service implementation with the highest frequency should have the highest priority. 

The rate monotonic scheduler sets the priority of the tasks acording to the period (P) of the tasks, so those tasks with a shorten period,
have a higher priority.

```
P - Periods
e - execution time
D - relative deadline

|          |   P     |    e    |   D     |  
------------------------------------------
|   T1     |   4     |    1    |   4     |        
------------------------------------------
|   T2     |   5     |    2    |   3     |        
------------------------------------------
|   T3     |   20    |    5    |   20    |        
------------------------------------------
```

In the table, T1, would get the highest priority, because his period is the shortest (P=4)

reference: https://en.wikipedia.org/wiki/Rate-monotonic_scheduling

### RM assumptions and constrains

 - A1: All services requested on periodic basis, and the period is constant.
 - A2: Completion-time < Period
 - A3: Service requests are independent (no known phasing) 
 - A4: Run-time is known and deterministic (WCET (worst case execution time) may be used)
 - C1: As simplification is assumed: Deadline = Period by definition - NOTE: Deadline monotonic (DM) is not dynamic priority policy. ALSO is diferent from Deadline driven (like EDF (earliest Deadline First) and LLF (Least Laxity Fist)), those are dynamic policies.
 - C2: Fixed priority, preemptive, run-to-completion scheduling
 - Critical Instant: longest response time for a service occurs when all system services are requested simultaneously (maximum interference case for lowest priority services)
 - No other shared resources. This is assumed im paper, but in real live, jobs share memory, input/outpus througputs ...
 
About EDF and LLF

EDF (Earliest Deadline Fist) aka Deadline driven scheduling: when the ready queue is updated, the scheduler must reassign all priorities according to each service's time remaining to deadline. (TTD: time to deadline) 

LLF (Least Laxity Fist): when the ready queue is updated, the scheduler must re-assign all priorities acording to each service's (time remaining to deadline - execution time remaining) (TTD - TR (time remaining) 

### Disadvantages of dynamic priorities scheduling policies.

- Can have big overhead. 
- Failure mode is not deterministic
- remaining execution time may be difficult to determine
- difficult to debug dynamic priority when deadlines are missed

DEADLINE MONOTONIC SCHEDULER:
============================

In the deadline monotonic scheduler the shortest deadline have the highiest priority. Note we don't say the "earliest" deadline because that would implie some dynamic priorities, and thats not the case for monotinc scheduling policies.

In the deadline monotonic scheduler, the task with the smaller relative deadline has the highest priority, in the table, that would
be T2, because its realtive deadline is the smallest (D=3).

NOTE:
> In case no deadline is set for a task, the DM algorithm is the same as the RM algorithm, because the period is the implicit deadline
> if nothing else is said.

DM has also a feasiability test:

Considering the nomenclature of S_1 is the highies priority service and S_n is the lowest priority service

For all services, if the deadline interval (D) is long enough to contain the service execution time interval (C) plus all the 
interfering execution time intervals. Then the service is feasible. If all services are feasible the the system is feasible: 

∀ i: 1 =< i =< n: (C_i / D_i) + (I_i / D_i) =< 1.0 

The interference is from services of higher priority.

I_i = Sum(j=1 ... i-1) \[ D_i / T_i \] * C_j

The interference to service S_i is due the preemption by all highier priority services from S_1 to S_i-1, and the total 
interference time is the number of releases of S_j over the deadline interval D_i for S_i multiplied by S_j  execution time C_j
for all S_j which have greater priority that S_i 

D_i / T_j  <- Worst case number of releases of S_j over deadline intervals for S_i

This test is an overestimation, due it considers that all the interferences are full, when they could be partial. But is useful as a feasibility test.  
 
EXAMPLE RM (rate monotonic) SCHEDULING:
======================================

We have the following preemptive system:

```
P - Periods
e - execution time
D - relative deadline


|          |   P     |    e    |   D     |  
------------------------------------------
|   T1     |   4     |    1    |   4     |        
------------------------------------------
|   T2     |   5     |    2    |   5     |        
------------------------------------------
|   T3     |   20    |    5    |   20    |        
------------------------------------------
```

Note that all the deadlines are identical to periods.

We want to schedule the tasks in the period [0,20]. Can we assure that all the tasks will meet the deadline?

First we look and the table, and check which task have the highest priority.- It's Task1, due it have the shortest period (P=4), it
has the highest priority. As T1, has the highest priority, it will be executed inmediatly when it's released.

```
 _____                   _____                   _____                   _____                   _____                                                
|     |                 |     |                 |     |                 |     |                 |     |          
|  T1 |                 | T1  |                 | T1  |                 | T1  |                 | T1  |           
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15   16     17    18    19    20       time
```

The following task in priority is T2, because it has the second shortest period (P=5). So we allocate all the T2 Jobs, but they have
to respect the T1 task scheduling:

```
 _____ ___________       _____ ___________       _____       ___________ _____             _____ _____ _____                                             
|     |           |     |     |           |     |     |     |           |     |           |     |     |     |
|  T1 |     T2    |     | T1  |    T2     |     | T1  |     |     T2    | T1  |           |  T2 | T1  | T2  |
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15   16     17    18    19    20       time
```

Finally Task T3 has the lowest priority, so Jobs of task3, have to be schedule only where there are space left in the timeline.

```
 _____ ___________ ____  _____ ___________ ____  _____ ____  ___________ _____ ___________ _____ _____ _____                                             
|     |           |     |     |           |     |     |     |           |     |           |     |     |     |
|  T1 |     T2    | T3  | T1  |    T2     |  T3 | T1  | T3  |     T2    | T1  |    T3     |  T2 | T1  | T2  |
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15   16     17    18    19    20       time
```

And in this case we obtain a feaseble schedule, because no task ever miss its deadline.

EXAMPLE DM (dead-line monotonic) SCHEDULING:
============================================

Consider the following setup, in a preemptive system:
```
P - Periods
e - execution time
D - relative deadline


|          |   phase  |   P     |    e     |   D    |  
----------------------------------------------------
|   T1     |    50    |   50    |    25    |  100   |        
----------------------------------------------------
|   T2     |    0     |   62.5  |    10    |   20   |        
----------------------------------------------------
|   T3     |    0     |   125   |    25    |   50   |        
----------------------------------------------------
```

We want to schedule the tasks in the interval [0,250], and also want to know if the tasks will meet the deadline.

T1, has phase of 50, so that means that the first Job in T1, it will be shifted 50 ms.

Which is the task with the highest priority? It's T2, because is the task with the closest deadline. Therefore, the jobs, from T2,
will freely allocate.

```
 T           T           T           T           T 
 2           2           2           2           2
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0           62.5        125         187.5       250              time(ms)
```

The task with the second highest priority, is task T3, because its relative deadline is 50, which is the second lowest deadline, thus
the second one in priority.

```
 T T T      T           T T T        T           T 
 2 3 3      2           2 3 3        2           2
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0           62.5        125         187.5       250              time(ms)
```

Finally comes T1, which has the lowest priority because it has the latest deadline.

```
 T  T     T  T T     T T T T T    T T T T T      T 
 2  3     1  2 1     1 1 2 3 3    1 1 2 1 1      2
|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----->
0           62.5        125         187.5       250              time(ms)
```

As we see, all the tasks, are done before the deadlines. :v:

COMPARATION BETWEEN DM AND RM:
=============================




VERIFIED MONOTONIC SCHEDULERS:
=============================

We must assume that the number of tasks is constant, that jobs are independent, periodic and preemptable and all the jobs are 
schedulable at their release time.

The feasability of a schedule can be exhaustivily proven by simulating a timeline of: 2H + max{Pi} + max{Di}. We must simulate
two hyper-periods (H) because the system can be feaseble in the first hyper-period, but if the deadline of the last task is
inside the second hyper-period, this must be also taken into account.

RM test : LEAST UPPER BOUND (LUB)
=================================

RM test can verify and guarantee timeline with the previous stated assumptions of the tasks. We define a limit called URM, as
the utilization limit under which the system is guaranteed to be feaseble. The feaseability can be proven by comparing the total
utilization (U) to the URM function. An the system is guaranteed to be feaseble if:

U =< URM(n) =< n*(2^(1/n) - 1) //n: number of tasks

n*(2^(1/n)1) is knwon as the Rate Monotonic Least Upper Bound. (RM LUB).

Consider the following task set:

```
P - Periods
e - execution time
D - relative deadline

|          |   P     |    e     |   D     |  
------------------------------------------
|   T1     |   5     |    1     |   5     |        
------------------------------------------
|   T2     |   4     |    0.5   |   4     |        
------------------------------------------
|   T3     |   6     |    1.2   |   6     |        
------------------------------------------
```

So the total utilization of the system (U) is:

U = 1 / 5 + 0.5 / 4 + 1.2 / 6 = 0.525

URM(3) = 3 * (2^(1/3) -1) = 0.779

As U < URM, thus the system is guaranteed to be feaseble.

Consider now, the following tasks set:

```
P - Periods
e - execution time
D - relative deadline

|          |   P     |    e     |   D     |  
------------------------------------------
|   T1     |   5     |    1.9   |   5     |        
------------------------------------------
|   T2     |   4     |    1.5   |   4     |        
------------------------------------------
|   T3     |   6     |    2.2   |   6     |        
------------------------------------------
```

U = 1.9 / 5 + 1.5 / 4 + 2.2 / 6 = 1.12

URM(3) = 3 * (2^(1/3) -1) = 0.779

Since U >= URM and 1, the system is not feaseble.


Last example, consider the following taks set:

```
P - Periods
e - execution time
D - relative deadline

|          |   P     |    e   |   D     |  
------------------------------------------
|   T1     |   4     |    1   |   4     |        
------------------------------------------
|   T2     |   6     |    1   |   6     |        
------------------------------------------
|   T3     |   2     |    1   |   2     |        
------------------------------------------
```

U = 1 / 4 + 1 / 6 + 1 / 2 = 0.917 

URM(3) = 3 * (2^(1/3) -1) = 0.779

Since U>= URM, but U =< 1, neither feaseability nor overloading can be guaranteed. We should apply more tests to verify the system.

### Is it possible to achieve 100% utilization with RM?

Yes, for harmonic cases and slack stealers (jobs designed to run in spare slots). 


RATE MONOTIC (RM) THEORY AND LEAST UPPER BOUND (LUB) AND CRITICAL TIME ZONE (CTZ)
=================================================================================

The utilization of a system is defined by the sum of each task computing times (C) times its period (T)

Utilization: U = Sum (1..m) (C_i/T_i)  

this has an upper limit that is: m * ( 2^(1/m) -1) # m is the number of services. 

U = Sum (1..n) (C_i/T_i)  =<  m * ( 2^(1/m) -1)

so for m = 2

U = C1/T1 + C2/T2 =< 2 (2^(1/2)-1) = 0.83

and for bigger values of m, this function limits to 70%. 

U = 0.7 =< 2 (2^(1/2) -1)  =< 0.83 

The LUB is a limit that asures feasibility, so if U < LUB, the system is guaranteed to be feasible. 
But the LUB is an overestimation. It is possible system that go over the LUB and work. But further
calculations need to be done to ensure that the systems would work.

RM LUB is a SUFFICIENT feasibility test, but RM LUB is not a NECESSARY and SUFFICIENT feasibility test. 
For example systems with harmonic periods can often have U=1.0 and be feasible. 

lets see an example of a two services, that complies with LUB:

```
  S1:  T1 = 2, C1 = 1
  S2:  T2 = 5, C2 = 1
  
  U  = C1/T1 + C2/T2 = 0.7  < 0.83 = LUB =  2 (2^(1/2) -1)
  
  The time analisys has to be done over the Least common multiple (LCM) of the periods: 2 and 5, which is 10
  
   time    |___S1___|___S2___|___S1___|___  ___|___S1___|___S2___|___S1___|___  ___|___S1___|___  ___|
   
   T2      |<---   -  -  -  -  T2  -  -  -  -  -  -  -->|<---  -  -  -  -  T2  -  -  -  -  -  -   -->|
   T1      |<---  - T1 - --->|<---  - T1 - --->|<---  - T1 - --->|<---  - T1 - --->|<---  - T1 - --->|
   
           0        1        2        3        4        5        6        7        8        9        10
 ```
 
An example of two services that doesn't comply wit LUB but works:

```
  S1:  T1 = 2, C1 = 1
  S2:  T2 = 5, C2 = 2
 
  U = C1/T1 + C2/T2 = 0.9  > 0.83 = LUB ... but the systems works
 
 The time analisys has to be done over the Least common multiple (LCM) of the periods: 2 and 5, which is 10
  
   time    |___S1___|___S2___|___S1___|___S2___|___S1___|___S2___|___S1___|___S2___|___S1___|___  ____|
   
   T2      |<---   -  -  -  -  T2  -  -  -  -  -  -  -->|<---   -  -  -  -  T2  -  -  -  -  -  -   -->|
   T1      |<---  - T1 - --->|<---  - T1 - --->|<---  - T1 - --->|<---  - T1 - --->|<---  - T1 -  --->|
   
           0        1        2        3        4        5        6        7        8        9        10
```

## RM failure mode

In case that RM fails a deadline, the failure mode, is that the tasks with lower priorities fail first. 
Actually this is a very safe way to fail, because in RM the lowest priority, are supposed to be the less
critical tasks. This makes this failure mode has a lower impact, that if the case would be that the most
critical task missed their deadlines. 



EXAMPLE: COMPARATION RM with RR/FAIR 
====================================

RR/Fair scheudling can fail, when RM can succed. 

**note:** RR stands for Round Robin.

```
we have an harmonic example 

      Service  Period  WCET   frequency   f0_multiple  Utility
          S1    2       1     0.5            5           50%
	  S2    5       1     0.2            2           20%
	  S3    10      2     0.1            1           30%
	  
 Total Utility: 100%
 LCM: 10
 LUB: 77.96%


 time    |___1___|___2___|___3___|___4___|___5___|___6___|___7___|___8___|___9___|___10__|
																  
 RM        
 
 S1      |.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|
 S2      |..   ..|.. S2..|..   ..|..   ..|..   ..|..S2 ..|..   ..|..   ..|..   ..|..   ..|
 S3      |..   ..|..   ..|..   ..|.. S3..|..   ..|..   ..|..   ..|.. S3..|..   ..|.. S3..|
																 
																 
 RR/Fair
 
 S1      |.. S1..|..   ..|..   ..|.. s1..|..   ..|.. S1..|..   ..|.MISS!.|.. S1..|..   ..|
 S2      |..   ..|.. S2..|..   ..|..   ..|..   ..|..   ..|.. S2..|..   ..|..   ..|..   ..|
 S3      |..   ..|..   ..|.. s3..|..   ..|.. S3..|..   ..|..   ..|.. S3..|..   ..|..   ..|	
                                                                                    ^^^^-and THIS IS FREE! 
										
```

Real-time scheduling policies are superior than RR/fair scheduling policies... the more tast there are, the bigger the chance a RR/fair
scheduler misses the task. On the other hand RR/fair scheduling, for example never starve services, that could happen with real-time
policies...and also doesn't suffer from unbounded priority inversion.



EDF:  EARLIEST DEADLINE FIRST SCHEDULER:
========================================

### LIMITATIONS IN THE RATE MONOTONIC THEORY

- requires that the priorities are fixed
- doesn't consider the importace of auxiliar service in addition to or instead of their request frequency or priority
- Simplification of the model assuming T=D
- Not considering additional resources needs, like shared memory neeeded at the same time as the CPU.
- assuming that real-time services will be required on a peridic basis

### EDF description

EDF is almost a dynamic priority scheduling policy. It is based in the TTD (time to deadline), which encodes the sense
of urgency of the task. The task with the smallest TTD is the one, with the highiest priority. 

This has been proved to be an optimal strategy. EDF actually works in systems where RM fails to meet the deadlines.

Also EDF is a scheduling policy that can achieve highier utilizations that RM. EDF also is adaptative, so services in the background are better supported
than for RM. 

So every time the task queue changes, that is to say: "an execution slice is ran", the priorities have to be calculated again, 
that is check the TTD of the systems tasks, to know what will be the next task. This calculation actually it makes more
complicated the system, and makes the switch to the next task, more "expensive" that in the RM scheduler. This is a small disadvantage compared to RM. 

```
      Service  Period  WCET   frequency   f0_multiple  Utility
          S1    2       1    0.5            3.5         50%
	  S2    5       1    0.2            1.4         20%
	  S3    7       2    0.14286        1           28.57%
	  
EDF                                                               |
 S1      |.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|.. S1..||..   ..|..   ..|
 S2      |..   ..|.. S2..|..   ..|..   ..|..   ..|..   ..|..   ..||.. S2..|..   ..|
 S3      |..   ..|..   ..|..   ..|.. S3..|..   ..|.. S3..|..   ..||..   ..|..   ..|  
			
TTD: time to dead-line //   -> X means: doesn't care, it has comply with the scheduler for its period														  
TTD : urgency                                                           
 S1      |.. 2 ..|.. X ..|.. 2 ..|.. X ..|.. 2 ..|.. X ..|.. 2 ..||.. X ..|.. 2 ..| 
 S2      |.. 5 ..|.. 4 ..|.. X ..|.. X ..|.. X ..|.. 5 ..|.. 4 ..||.. 3 ..|.. X ..|
 S3      |.. 7 ..|.. 6 ..|.. 5 ..|.. 4 ..|.. 3 ..|.. 2 ..|.. X ..||.. 7 ..|.. 6 ..|
	
```

EDF is recommended to be used in soft-realtime systems. Systems in which failing a deadline is not critical. 

**Note** for systems that have harmonic tasks, EDF and RM result always in the same scheduling, so actually, it is
best to go for RM system, because it doesn't have the overhead of calculating the TTD, so that will result in saving
computation time. 

### EDF failure mode

The big downside of EDF, is what is known as the "domino failure", this type of failure can be seen, in those
systems in which the TTD calculation of the tasks produces the same values for more than one task, that may lead
to a domino failure. 

Also, there is the issue, that there is no really a warning, or hint, that the scheduling is going to fail. In case
of an overload. Also, in case of a failure, which task would fail, is not guaranteed, so the first task to fail, could
be the most critical one, that makes this scheduling policy much more riscky in case of failure. 

This severe failure mode, is the reason why EDF is preferred as a policy for soft-real-time systems, in which missing a
deadline have not catastrophic consequences. 

Reference: Buttazzo, Giorgio C. "Rate monotonic vs. EDF: judgment day." Real-Time Systems 29.1 (2005): 5-26.  

### references for EDF

Stankovic, John A., et al. "Fundamentals of EDF scheduling." Deadline Scheduling for Real-Time Systems. Springer, Boston, MA, 1998. 27-65.  

Students at University of Colorado who are on the Colorado.edu domain or loggegd in via VPN should be able to download the PDF text.

Papers on deadline driven scheduling that may also be interesting:

Golatowski, Frank, et al. "Framework for validation, test and analysis  of real-time scheduling algorithms and scheduler implementations." Proceedings 13th IEEE International Workshop on Rapid System Prototyping. IEEE, 2002.  

Wilding, Matthew. "A machine-checked proof of the optimality of a real-time scheduling policy." International Conference on Computer Aided Verification. Springer, Berlin, Heidelberg, 1998.  

Baek, Hyeongboo, Hoon Sung Chwa, and Jinkyu Lee. "Beyond  Implicit-Deadline Optimality: A Multiprocessor Scheduling Framework for  Constrained-Deadline Tasks." 2017 IEEE Real-Time Systems Symposium (RTSS). IEEE, 2017.  

Mok, Aloysius Ka-Lau. Fundamental design problems of distributed systems for the hard-real-time environment. Dissertation. Massachusetts Institute of Technology, 1983.



## LSF: Least Slack First or LST: Least Slack Time Scheduling or LLF: Least Laxity first


This scheduling strategy prioritizes the job with the least slack time. As a dynamic scheduling algorithm, this priority is evaluated at each tick.

The remaining slack time is calculated as:

```
slack_time = death_line_time -  current_time - remaining_execution_time = TTD - TR

Laxity = TTD - TR
TTD: time to deadline
TR: remaining execution time
```

In case the job has not been executed yet, then the slack time equals the execution time.

One advantage of LSF over EDF, is that while EDF fails, whithout warning, in LSF, as we are coputing the lack time, the scheduler,
knows, beforehand, if it is going to fail a dead-line. So the failure mode is better that EDF. 

One disadvantage regarding LFS compared with EDF, is that the remaining time, is hard to compute.   

In some scenarios LSF, can switch tasks innecesarly, doing innecesary context switches (thrasing). This has resulted in other scheduilng policy: 
ELLF, enhaced least laxity first, 


-------

Example LST:

Consider the following taks set:

with dependecies: J1 -> J2, Je

-Please, schedule tasks in the interval [0,8].
```
r - release time
e - execution time
D - relative deadline

|          |   r     |    e   |   D     |  
------------------------------------------
|   T1     |   0     |    3   |   6     |        
------------------------------------------
|   T2     |   5     |    2   |   8     |        
------------------------------------------
|   T3     |   2     |    2   |   7     |        
------------------------------------------
```
- - - - - - - - - - -- - -- - -- - -- - --

```
We start marcking all the death-lines of the job:

                                    D1    D3    D2
                                    |     |     |
                                    V     V     V
|-----|-----|-----|-----|-----|-----|-----|-----|--------->
0     1     2     3     4     5     6     7     8      time
```
... TODO:


### References for LLF

The Least Laxity First (or Least Slack First) was described by the following paper as a more optimal alternative to EDF, which was originally described by Liu and Layland and called "Deadline Driven" scheduling.

Dertouzos, Michael L., and Aloysius K. Mok. "Multiprocessor online scheduling of hard-real-time tasks." IEEE Transactions on software engineering 15.12 (1989): 1497-1506.  

The LLF policy suffers from thrashing that looks like RR (Round Robin) in certain scenarios, so an enhanced algorithm has been suggested that detects this condition and recovers by using EDF to avoid thrashing.  The enhancement is describe in the following paper.

Hildebrandt, Jens, Frank Golatowski, and Dirk Timmermann. "Scheduling  coprocessor for enhanced least-laxity-first scheduling in hard real-time  systems." Proceedings of 11th Euromicro Conference on Real-Time Systems. Euromicro RTS'99. IEEE, 1999.  




EXAMPLE: COMPARATION RM, EDF and LLF
====================================

```
      Service  Period  WCET   frequency   f0_multiple  Utility
          S1    2       1    0.5            3.5         50%
	  S2    5       1    0.2            1.4         20%
	  S3    7       2    0.14286        1           28.57%
	  
 Total Utility: 98.57%
 LCM: 70
 LUB: 77.98%


 time    |___1___|___2___|___3___|___4___|___5___|___6___|___7___||___8___|___9___|___...___
																  
 RM                                                               |
 S1      |.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|.. S1..||..   ..|.. S1..|
 S2      |..   ..|.. S2..|..   ..|..   ..|..   ..|..S2?..|..   ..||..   ..|..   ..|
 S3      |..   ..|..   ..|..   ..|.. S3..|..   ..|..   ..|..   ..||.LATE!.|..   ..|  -> RM misses S3. S3 needs 2 times every 7 time units.
																  
																  
EDF                                                               |
 S1      |.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|.. S1..||..   ..|..   ..|
 S2      |..   ..|.. S2..|..   ..|..   ..|..   ..|..   ..|..   ..||.. S2..|..   ..|
 S3      |..   ..|..   ..|..   ..|.. S3..|..   ..|.. S3..|..   ..||..   ..|..   ..|   -> EDF complies
			
TTD: time to dead-line															  
TTD : urgency                                                           |
 S1      |.. 2 ..|.. X ..|.. 2 ..|.. X ..|.. 2 ..|.. X ..|.. 2 ..||.. X ..|.. 2 ..|   -> X means: doesn't care, it has comply with the scheduler for its period.
 S2      |.. 5 ..|.. 4 ..|.. X ..|.. X ..|.. X ..|.. 5 ..|.. 4 ..||.. 3 ..|.. X ..|
 S3      |.. 7 ..|.. 6 ..|.. 5 ..|.. 4 ..|.. 3 ..|.. 2 ..|.. X ..||.. 7 ..|.. 6 ..|
																  
LLF                                                               |
 S1      |.. S1..|..   ..|.. S1..|..   ..|.. S1..|..   ..|.. S1..||..   ..|..   ..|
 S2      |..   ..|.. S2..|..   ..|..   ..|..   ..|..   ..|..   ..||.. S2..|..   ..|
 S3      |..   ..|..   ..|..   ..|.. S3..|..   ..|.. S3..|..   ..||..   ..|..   ..|   -> EDF complies
																  
TT																  
TTD- TR : laxity    / TTD (time to dead-line) TR (time remaining)                                                    
 S1      |.. 1 ..|.. X ..|.. 1 ..|.. X ..|.. 1 ..|.. X ..|.. 1 ..||.. X ..|.. 1 ..|
 S2      |.. 4 ..|.. 3 ..|.. X ..|.. X ..|.. X ..|.. 4 ..|.. 3 ..||.. 2 ..|.. X ..|
 S3      |.. 5 ..|.. 4 ..|.. 3 ..|.. 2 ..|.. 2 ..|.. 1 ..|.. X ..||.. 5 ..|.. 3 ..|
 
```

Other example:

```
For this example: - Non-Harmonic, RM Failure, EDF and LLF Success

| TASK  | PERIOD |  FREQ  | MULT. FREQ |  WCET | UTILITY |
|  S1   |    3   |   0.33 |    3       |   1   |   33.3% |
|  S2   |    6   |   0.16 |    1.5     |   2   |   33.3% |
|  S3   |    9   |   0.11 |    1       |   3   |   33.3% |


LUB = 77.98
LCM = 18       // period for repetition
U_tot = 100%


RM schedule:

0ms    10ms   20ms   30ms   40     50     60    70      80     90     100    110    120    130    140    150    160    170    180   [ms]
|--S1--|--S2--|--S2--|--S1--|--S3--|--S3--|--S1--|--S2--|--S2--|--S1--|--MISSED-S3--|--S1--|--S2--|--S2--|--S1--|--S1--|--S3--|--S3--|
                                                              ^^^ Here S2 misses the deadline, doesn't manage to do 3 computation slices in the 9 slices period!!
<--------T1----------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1--------->
<--------------------T2-------------------><--------------------T2------------------><--------------------T2------------------> ...          
<------------------------------T3------------------------------><------------------------------T3------------------------------> ...

          
EDF schedule:

    0ms    10ms   20ms   30ms   40     50     60    70      80     90     100    110    120    130    140    150    160    170    180   [ms]
    |--S1--|--S2--|--S2--|--S1--|--S3--|--S3--|--S1--|--S3--|--S2--|--S1--|--S2--|--S3--|--S1--|--S2--|--S2--|--S1--|--S3--|--S3--| ...

    <--------T1----------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1--------->
    <--------------------T2-------------------><--------------------T2------------------><--------------------T2------------------> ...          
    <------------------------------T3------------------------------><------------------------------T3------------------------------> ...

Urgency table (TTD: TIME TO DEADLINE)

 S1:    3      X      X      3     X      X       3      X      X       3     X      X      3       X     X      3     X      X
 S2:    6      5      4      X     X      X       6      5      4       3     2      X      6       5     4      X     X      X
 S3:    9      8      7      6     5      4       3      2      X       9     8      7      6       5     4      3     2      x


LFF schedule: 
 
    0ms    10ms   20ms   30ms   40     50     60    70      80     90     100    110    120    130    140    150    160    170    180   [ms]
    |--S1--|--S2--|--S2--|--S1--|--S3--|--S3--|--S1--|--S3--|--S2--|--S1--|--S2--|--S3--|--S1--|--S2--|--S3--|--S1--|--S2--|--S3--| ...

    <--------T1----------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1--------->
    <--------------------T2-------------------><--------------------T2------------------><--------------------T2------------------> ...          
    <------------------------------T3------------------------------><------------------------------T3------------------------------> ...

Laxity table (TTD-TR)

 S1:   2      X      X      2      X      X      2      X      X      2      X      X       2      X      X     2      X      X    
 S2:   4      3      3      X      X      X      4      3      2      2      1      X       4      3      3     2      1      X    
 S3:   6      5      4      3      2      2      2      1      X      6      5      4       4      3      2     2      1      0    
 
NOTE: In this last example notice the thrasing, in which the tasks rotate doing unnecessary context sutiches: S1 -> S2 -> S3 -> S1 -> S2 -> S3

```



# REFERENCES:


 C.L. Liu, and J.W. Layland. Scheduling algorithms for multiprogramming in a hard-real-time
environment. Journal of the Association for Computing Machinery, vol.20, (no.1), Jan. 1973. p.
46-61.
- http://citeseer.ist.psu.edu/liu73scheduling.html

‣ J. Lehoczky, L. Sha, and Y. Ding. The rate monotonic scheduling algorithm: exact
characterization and average case behavior. Proceedings of Real Time Systems Symposium, p.
166-171, Dec. 1989.

‣ Enrico Bini, Giorgio Buttazzo and Giuseppe Buttazzo, "Rate Monotonic Analysis: The Hyperbolic
Bound", IEEE Transactions on Computers, Vol. 52, No. 7, pp. 933-942, July 2003.
- http://feanor.sssup.it/~giorgio/paps/2003/ieeetc-hb.pdf

- Buttazzo, Giorgio C. "Rate monotonic vs. EDF: judgment day." Real-Time Systems 29.1 (2005): 5-26.  

http://retis.sssup.it/~giorgio/paps/2005/rtsj05-rmedf.pdf

references: https://www.amazon.com/-/es/Mark-Klein/dp/0792393619

https://www.iiitd.edu.in/~amarjeet/EmSys2013/UCLA-EE202a-L05-RateMonotonic.pdf

The evolution of real-time linux: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.151.6125&rep=rep1&type=pdf



# HOW TO SCHEDULE LINUX REALTIME:

A Checklist for Writing Linux Real-Time Applications - John Ogness, Linutronix - https://www.youtube.com/watch?v=NrjXEaTSyrw 

https://ogness.net/ese2020/ese2020_johnogness_rtchecklist.pdf

https://wiki.linuxfoundation.org/realtime/rtl/blog#the_real-time_endgame_is_moving_quickly_now

a complete guide on linux scheduling: https://trepo.tuni.fi/bitstream/handle/10024/96864/GRADU-1428493916.pdf

https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/start

https://www.kernel.org/doc/html/latest/scheduler/sched-deadline.html

https://www.kernel.org/doc/html/latest/scheduler/sched-rt-group.html

https://m.youtube.com/watch?v=BKkX9WASfpI

https://m.youtube.com/watch?v=BxJm-Ujipcg

https://lwn.net/Articles/743740/

https://lwn.net/Articles/743946/

https://lwn.net/Articles/821578/

https://www.kernel.org/doc/Documentation/scheduler/sched-deadline.txt

Using KernelShark to analyze the real-time scheduler https://lwn.net/Articles/425583/


check this below:

http://www.embeddedlinux.org.cn/rtconforembsys/5107final/toc.html

https://en.wikibooks.org/wiki/The_Linux_Kernel/Processing

https://man7.org/linux/man-pages/man7/nptl.7.html

https://computing.llnl.gov/tutorials/pthreads/

linux-kernel-in-a-nutshell: https://bootlin.com/doc/books/lkn.pdf





## What really happened on Mars Rover Pathfinder

reference: http://www.cs.cornell.edu/courses/cs614/1999sp/papers/pathfinder.html

```
Mike Jones <mbj@MICROSOFT.com>
Sunday, December 07, 1997 6:47 PM

The Mars Pathfinder mission was widely proclaimed as "flawless" in the early days after its July 4th, 1997 landing on the Martian surface.
Successes included its unconventional "landing" -- bouncing onto the Martian surface surrounded by airbags, deploying the Sojourner rover,
and gathering and transmitting voluminous data back to Earth, including the panoramic pictures that were such a hit on the Web. But a few
days into the mission, not long after Pathfinder started gathering meteorological data, the spacecraft began experiencing total system resets,
each resulting in losses of data. The press reported these failures in terms such as "software glitches" and "the computer was trying to do 
too many things at once".

This week at the IEEE Real-Time Systems Symposium I heard a fascinating keynote address by David Wilner, Chief Technical Officer of Wind River
Systems. Wind River makes VxWorks, the real-time embedded systems kernel that was used in the Mars Pathfinder mission. In his talk, he explained
in detail the actual software problems that caused the total system resets of the Pathfinder spacecraft, how they were diagnosed, and how they
were solved. I wanted to share his story with each of you.

VxWorks provides preemptive priority scheduling of threads. Tasks on the Pathfinder spacecraft were executed as threads with priorities that were
assigned in the usual manner reflecting the relative urgency of these tasks.

Pathfinder contained an "information bus", which you can think of as a shared memory area used for passing information between different 
components of the spacecraft. A bus management task ran frequently with high priority to move certain kinds of data in and out of the 
information bus. Access to the bus was synchronized with mutual exclusion locks (mutexes).

The meteorological data gathering task ran as an infrequent, low priority thread, and used the information bus to publish its data.
When publishing its data, it would acquire a mutex, do writes to the bus, and release the mutex. If an interrupt caused the information
bus thread to be scheduled while this mutex was held, and if the information bus thread then attempted to acquire this same mutex in 
order to retrieve published data, this would cause it to block on the mutex, waiting until the meteorological thread released the mutex
before it could continue. The spacecraft also contained a communications task that ran with medium priority.

Most of the time this combination worked fine. However, very infrequently it was possible for an interrupt to occur that caused the 
(medium priority) communications task to be scheduled during the short interval while the (high priority) information bus thread 
was blocked waiting for the (low priority) meteorological data thread. In this case, the long-running communications task, having 
higher priority than the meteorological task, would prevent it from running, consequently preventing the blocked information bus 
task from running. After some time had passed, a watchdog timer would go off, notice that the data bus task had not been executed 
for some time, conclude that something had gone drastically wrong, and initiate a total system reset.

This scenario is a classic case of priority inversion.

HOW WAS THIS DEBUGGED?

VxWorks can be run in a mode where it records a total trace of all interesting system events, including context switches, uses
of synchronization objects, and interrupts. After the failure, JPL engineers spent hours and hours running the system on the 
exact spacecraft replica in their lab with tracing turned on, attempting to replicate the precise conditions under which they
believed that the reset occurred. Early in the morning, after all but one engineer had gone home, the engineer finally reproduced
a system reset on the replica. Analysis of the trace revealed the priority inversion.

HOW WAS THE PROBLEM CORRECTED?

When created, a VxWorks mutex object accepts a boolean parameter that indicates whether priority inheritance should be performed
by the mutex. The mutex in question had been initialized with the parameter off; had it been on, the low-priority meteorological
thread would have inherited the priority of the high-priority data bus thread blocked on it while it held the mutex, causing it
be scheduled with higher priority than the medium-priority communications task, thus preventing the priority inversion. Once 
diagnosed, it was clear to the JPL engineers that using priority inheritance would prevent the resets they were seeing.

VxWorks contains a C language interpreter intended to allow developers to type in C expressions and functions to be executed on 
the fly during system debugging. The JPL engineers fortuitously decided to launch the spacecraft with this feature still enabled.
By coding convention, the initialization parameter for the mutex in question (and those for two others which could have caused the
same problem) were stored in global variables, whose addresses were in symbol tables also included in the launch software, and 
available to the C interpreter. A short C program was uploaded to the spacecraft, which when interpreted, changed the values of
these variables from FALSE to TRUE. No more system resets occurred.

ANALYSIS AND LESSONS

First and foremost, diagnosing this problem as a black box would have been impossible. Only detailed traces of actual system 
behavior enabled the faulty execution sequence to be captured and identified.

Secondly, leaving the "debugging" facilities in the system saved the day. Without the ability to modify the system in the field,
the problem could not have been corrected.

Finally, the engineer's initial analysis that "the data bus task executes very frequently and is time-critical -- we shouldn't
spend the extra time in it to perform priority inheritance" was exactly wrong. It is precisely in such time critical and important
situations where correctness is essential, even at some additional performance cost.

HUMAN NATURE, DEADLINE PRESSURES

David told us that the JPL engineers later confessed that one or two system resets had occurred in their months of pre-flight 
testing. They had never been reproducible or explainable, and so the engineers, in a very human-nature response of denial, 
decided that they probably weren't important, using the rationale "it was probably caused by a hardware glitch".

Part of it too was the engineers' focus. They were extremely focused on ensuring the quality and flawless operation of the 
landing software. Should it have failed, the mission would have been lost. It is entirely understandable for the engineers
to discount occasional glitches in the less-critical land-mission software, particularly given that a spacecraft reset was a
viable recovery strategy at that phase of the mission.

THE IMPORTANCE OF GOOD THEORY/ALGORITHMS

David also said that some of the real heroes of the situation were some people from CMU who had published a paper he'd heard
presented many years ago who first identified the priority inversion problem and proposed the solution. He apologized for not
remembering the precise details of the paper or who wrote it. Bringing things full circle, it turns out that the three authors
of this result were all in the room, and at the end of the talk were encouraged by the program chair to stand and be acknowledged.
They were Lui Sha, John Lehoczky, and Raj Rajkumar. When was the last time you saw a room of people cheer a group of computer
science theorists for their significant practical contribution to advancing human knowledge? :-) It was quite a moment.

POSTLUDE

For the record, the paper was:

L. Sha, R. Rajkumar, and J. P. Lehoczky. Priority Inheritance Protocols: An Approach to Real-Time Synchronization. 
In IEEE Transactions on Computers, vol. 39, pp. 1175-1185, Sep. 1990.
```

reference: https://www.cs.unc.edu/~anderson/teach/comp790/papers/mars_pathfinder_long_version.html

```
From: Glenn E Reeves[SMTP:Glenn.E.Reeves@jpl.nasa.gov]
Sent: Monday, December 15, 1997 10:28 AM

What really happened on Mars ?
By now most of you have read Mike’s (mbj@microsoft.com) summary of Dave Wilner’s comments given at the IEEE Real-Time Systems Symposium. I don’t know Mike and I didn’t attend the symposium (though I really wish I had now) and I have not talked to Dave Wilner since before the talk. However, I did lead the software team for the Mars Pathfinder spacecraft. So, instead of trying to find out what was said I will just tell you what happened. You can make your own judgments.

I sent this message out to everyone who was a recipient of Mike’s original that I had an email address for. Please pass it on to anyone you sent the first one to. Mike, I hope you will post this wherever you posted the original.

Since I want to make sure the problem is clearly understood I need to step through each of the areas which contributed to the problem.

THE HARDWARE
The simplified view of the Mars Pathfinder hardware architecture looks like this. A single CPU controls the spacecraft. It resides on a VME bus which also contains interface cards for the radio, the camera, and an interface to a 1553 bus. The 1553 bus connects to two places : The "cruise stage" part of the spacecraft and the "lander" part of the spacecraft. The hardware on the cruise part of the spacecraft controls thrusters, valves, a sun sensor, and a star scanner. The hardware on the lander part provides an interface to accelerometers, a radar altimeter, and an instrument for meteorological science known as the ASI/MET. The hardware which we used to interface to the 1553 bus (at both ends) was inherited from the Cassini spacecraft. This hardware came with a specific paradigm for its usage : the software will schedule activity at an 8 Hz rate. This **feature** dictated the architecture of the software which controls both the 1553 bus and the devices attached to it.

THE SOFTWARE ARCHITECTURE
The software to control the 1553 bus and the attached instruments was implemented as two tasks. The first task controlled the setup of transactions on the 1553 bus (called the bus scheduler or bc_sched task) and the second task handled the collection of the transaction results i.e. the data. The second task is referred to as the bc_dist (for distribution) task. A typical timeline for the bus activity for a single cycle is shown below. It is not to scale. This cycle was constantly repeated.

    |< ------------- .125 seconds ------------------------>|
    |<***************|                    |********|   |**>|
                     |<- bc_dist active ->|    bc_sched active
    |< -bus active ->|                             |<->|
----|----------------|--------------------|--------|---|---|-------
    t1               t2                   t3       t4  t5  t1
The *** are periods when tasks other than the ones listed are executing. Yes, there is some idle time.

t1 - bus hardware starts via hardware control on the 8 Hz boundary. The transactions for the this cycle had been set up by the previous execution of the bc_sched task.
t2 - 1553 traffic is complete and the bc_dist task is awakened.
t3 - bc_dist task has completed all of the data distribution
t4 - bc_sched task is awakened to setup transactions for the next cycle
t5 - bc_sched activity is complete

The bc_sched and bc_dist tasks check each cycle to be sure that the other had completed its execution. The bc_sched task is the highest priority task in the system (except for the vxWorks "tExec" task). The bc_dist is third highest (a task controlling the entry and landing is second). All of the tasks which perform other spacecraft functions are lower. Science functions, such as imaging, image compression, and the ASI/MET task are still lower.

Data is collected from devices connected to the 1553 bus only when they are powered. Most of the tasks in the system that access the information collected over the 1553 do so via a double buffered shared memory mechanism into which the bc_dist task places the latest data. The exception to this is the ASI/MET task which is delivered its information via an interprocess communication mechanism (IPC). The IPC mechanism uses the vxWorks pipe() facility. Tasks wait on one or more IPC "queues" for messages to arrive. Tasks use the select() mechanism to wait for message arrival. Multiple queues are used when both high and lower priority messages are required. Most of the IPC traffic in the system is not for the delivery of real-time data. However, again, the exception to this is the use of the IPC mechanism with the ASI/MET task. The cause of the reset on Mars was in the use and configuration of the IPC mechanism.

THE FAILURE
The failure was identified by the spacecraft as a failure of the bc_dist task to complete its execution before the bc_sched task started. The reaction to this by the spacecraft was to reset the computer. This reset reinitializes all of the hardware and software. It also terminates the execution of the current ground commanded activities. No science or engineering data is lost that has already been collected (the data in RAM is recovered so long as power is not lost). However, the remainder of the activities for that day were not accomplished until the next day.

The failure turned out to be a case of priority inversion (how we discovered this and how we fixed it are covered later). The higher priority bc_dist task was blocked by the much lower priority ASI/MET task that was holding a shared resource. The ASI/MET task had acquired this resource and then been preempted by several of the medium priority tasks. When the bc_sched task was activated, to setup the transactions for the next 1553 bus cycle, it detected that the bc_dist task had not completed its execution. The resource that caused this problem was a mutual exclusion semaphore used within the select() mechanism to control access to the list of file descriptors that the select() mechanism was to wait on.

The select mechanism creates a mutual exclusion semaphore to protect the "wait list" of file descriptors for those devices which support select. The vxWorks pipe() mechanism is such a device and the IPC mechanism we used is based on using pipes. The ASI/MET task had called select, which had called pipeIoctl(), which had called selNodeAdd(), which was in the process of giving the mutex semaphore. The ASI/ MET task was preempted and semGive() was not completed. Several medium priority tasks ran until the bc_dist task was activated. The bc_dist task attempted to send the newest ASI/MET data via the IPC mechanism which called pipeWrite(). pipeWrite() blocked, taking the mutex semaphore. More of the medium priority tasks ran, still not allowing the ASI/MET task to run, until the bc_sched task was awakened. At that point, the bc_sched task determined that the bc_dist task had not completed its cycle (a hard deadline in the system) and declared the error that initiated the reset.

HOW WE FOUND IT
The software that flies on Mars Pathfinder has several debug features within it that are used in the lab but are not used on the flight spacecraft (not used because some of them produce more information than we can send back to Earth). These features were not "fortuitously" left enabled but remain in the software by design. We strongly believe in the "test what you fly and fly what you test" philosophy.

One of these tools is a trace/log facility which was originally developed to find a bug in an early version of the vxWorks port (Wind River ported vxWorks to the RS6000 processor for us for this mission). This trace/log facility was built by David Cummings who was one of the software engineers on the task. Lisa Stanley, of Wind River, took this facility and instrumented the pipe services, msgQ services, interrupt handling, select services, and the tExec task. The facility initializes at startup and continues to collect data (in ring buffers) until told to stop. The facility produces a voluminous dump of information when asked.

After the problem occurred on Mars we did run the same set of activities over and over again in the lab. The bc_sched was already coded so as to stop the trace/log collection and dump the data (even though we knew we could not get the dump in flight) for this error. So, when we went into the lab to test it we did not have to change the software.

In less that 18 hours we were able to cause the problem to occur. Once we were able to reproduce the failure the priority inversion problem was obvious.

HOW WAS THE PROBLEM CORRECTED
Once we understood the problem the fix appeared obvious : change the creation flags for the semaphore so as to enable priority inheritance. The Wind River folks, for many of their services, supply global configuration variables for parameters such as the "options" parameter for the semMCreate used by the select service (although this is not documented and those who do not have vxWorks source code or have not studied the source code might be unaware of this feature). However, the fix is not so obvious for several reasons :

1) The code for this is in the selectLib() and is common for all device creations. When you change this global variable all of the select semaphores created after that point will be created with the new options. There was no easy way in our initialization logic to only modify the semaphore associated with the pipe used for bc_dist task to ASI/MET task communications.
2) If we make this change, and it is applied on a global basis, how will this change the behavior of the rest of the system ?

3) The priority inheritance option was deliberately left out by Wind River in the default selectLib() service for optimum performance. How will performance degrade if we turn priority inheritance on ?

4) Was there some intrinsic behavior of the select mechanism itself that would change if priority inheritance was enabled ?

We did end up modifying the global variable to include the priority inheritance option. This corrected the problem. We asked Wind River to analyze the potential impacts for (3) and (4). They concluded that the performance impact would be minimal and that the behavior of select() would not change so long as there was always only one task waiting for any particular file descriptor. This is true in our system. I believe that the debate at Wind River still continues on whether the priority inheritance option should be on as the default. For (1) and (2) the change did alter the characteristics of all of the select semaphores. We concluded, both by analysis and test, that there was no adverse behavior. We tested the system extensively before we changed the software on the spacecraft.

HOW WE CHANGED THE SOFTWARE ON THE SPACECRAFT
No, we did not use the vxWorks shell to change the software (although the shell is usable on the spacecraft). The process of "patching" the software on the spacecraft is a specialized process. It involves sending the differences between what you have onboard and what you want (and have on Earth) to the spacecraft. Custom software on the spacecraft (with a whole bunch of validation) modifies the onboard copy. If you want more info you can send me email.

WHY DIDN’T WE CATCH IT BEFORE LAUNCH ?
The problem would only manifest itself when ASI/MET data was being collected and intermediate tasks were heavily loaded. Our before launch testing was limited to the "best case" high data rates and science activities. The fact that data rates from the surface were higher than anticipated and the amount of science activities proportionally greater served to aggravate the problem. We did not expect nor test the "better than we could have ever imagined" case.

HUMAN NATURE, DEADLINE PRESSURES
We did see the problem before landing but could not get it to repeat when we tried to track it down. It was not forgotten nor was it deemed unimportant. Yes, we were concentrating heavily on the entry and landing software. Yes, we considered this problem lower priority. Yes, we would have liked to have everything perfect before landing. However, I don’t see any problem here other than we ran out of time to get the lower priority issues completed.

We did have one other thing on our side; we knew how robust our system was because that is the way we designed it.

We knew that if this problem occurred we would reset. We built in mechanisms to recover the current activity so that there would be no interruptions in the science data (although this wasn’t used until later in the landed mission). We built in the ability (and tested it) to go through multiple resets while we were going through the Martian atmosphere. We designed the software to recover from radiation induced errors in the memory or the processor. The spacecraft would have even done a 60 day mission on its own, including deploying the rover, if the radio receiver had broken when we landed. There are a large number of safeguards in the system to ensure robust, continued operation in the event of a failure of this type. These safeguards allowed us to designate problems of this nature as lower priority.

We had our priorities right.

ANALYSIS AND LESSONS
Did we (the JPL team) make an error in assuming how the select/pipe mechanism would work ? Yes, probably. But there was no conscious decision to not have the priority inheritance option enabled. We just missed it. There are several other places in the flight software where similar protection is required for critical data structures and the semaphores do have priority inversion protection. A good lesson when you fly COTS stuff - make sure you know how it works.

Mike is quite correct in saying that we could not have figured this out **ever** if we did not have the tools to give us the insight. We built many of the tools into the software for exactly this type of problem. We always planned to leave them in. In fact, the shell (and the stdout stream) were very useful the entire mission. If you want more detail send me a note.

SETTING THE RECORD STRAIGHT
First, I want to make sure that everyone understands how I feel in regard to Wind River. These folks did a fantastic job for us. They were enthusiastic and supported us when we came to them and asked them to do an affordable port of vxWorks. They delivered the alpha version in 3 months. When we had a problem they put some of the brightest engineers I have ever worked with on the problem. Our communication with them was fantastic. If they had not done such a professional job the Mars Pathfinder mission would not have been the success that it is.

Second, Dave Wilner did talk to me about this problem before he gave his talk. I could not find my notes where I had detailed the description of the problem. So, I winged it and I sure did get it wrong. Sorry Dave.

...


```










<hr>

<hr>



Poor-mans profiler:
-------------------

Profile a program, means to measure its performance, that is to say, it time execution (mostly)

CPU time measurement:
---------------------

CPU Time, is the CPU used time relative to a process, that is the amount of time that a certain process is using, of the CPU;
take into account, that if several process, are running in parallel, each one will use the CPU certain amount of time, that
depends on the operating system process squeduler.

If you want to check the time it takes a function from begining to end; then you can use the following `stdlib` function:

With the header file **'times.h'** or **'sys/times.h'**, you can use the function **`'clock()'`**, this will return a struct with the 
number of ticks of the clock for the current proces: 'clock_t', it really is another name for a 'long integer'.
For using this function, you have to call it at the start of the period
that  you want to measure, and at the end of it; Then, substract the **'start'** and **'end'** clocks, and ,divide it by the number of 
clock ticks per second (defined in the macro: **`CLOCKS_PER_SEC`**, or the 'sysconf' **`_SC_CLK_TCK_`**), to get the processor time.

Example:

```C
#include <time.h> //needed for: CLOCKS_PER_SEC, clock().

printf("debug: init: CLOCKS_PER_SEC: %d\n", CLOCK_PER_SEC); //safety check

. . .

clock_t start_tick= (clock_t)(-1), end_tack=(clock_t)(-1); //tick(start) & tack(end) CPU-time-ticks.
double cpu_time_used = 0; //measured used time. (check accuracy for the system)

...

start_tick = clock();

... // process data or else...

end_tack = clock();

if( start_tick != (clock_t)(-1) || end_tack != (clock_t)(-1) )
{
   cpu_time_used = ((double)(end_tack-start_tick)/(double)CLOCKS_PER_SEC);
   printf("debug:function %s cpu_time: %d sec\n",__FUNCTION__, cpu_time_used);  //info we want.
}
else
{  printf("error: function %s; clock() function error: \ntick: %d\ntack: %d",__FUNCTION__, start_tick, end_tack);}

```

Watch out!: 

Take into account, that different computers, and operating systems have different resolutions, and different methods to 
track time.`'clock()'` doesn't usually have more than some ms accuracy depending on the system.

If the clock() cant give you a result or it is not available, it returns the value '(clock_t)(-1)'.

There is an old macro: `'int **CLK_TCK**'` - don't use it. Use a newer one.

You should check the value of the clock_per_second constant that you system defines... just in case.

Portability Note: The clock function described in CPU Time is specified by the ISO C standard. 
clock() is standard C; it works "everywhere". There are system-specific functions, such as getrusage() on Unix-like systems.

reference: </br>
https://www.gnu.org/software/libc/manual/html_node/Time-Basics.html#Time-Basics </br>
https://www.gnu.org/software/libc/manual/html_node/CPU-Time.html#CPU-Time </br>
http://stackoverflow.com/questions/5248915/execution-time-of-c-program </br>

time interval measurement:
-------------------------

With the header file **'sys/times.h'**, watch out: not **'time.h'!!**, if you want to measure some time interval, you can use the function:

>'clock_t **times(struct tms *buffer)**'

The times function stores the processor time information for the calling process in buffer. Remeber 'clock_t' are the clock ticks.

the tms struct, contains at least the following fields:

- **clock_t tms_utime** - This is the total processor time the calling process has used in executing the instructions of its program.

- **clock_t tms_stime** - This is the processor time the system has used on behalf of the calling process.

- **clock_t tms_cutime** -In other words, it represents the total processor time used in executing the instructions of all the terminated child processes of the
calling process, excluding child processes which have not yet been reported by `'wait'` or `'waitpid'`.

- **clock_t tms_cstime** - This is similar to tms_cutime, but represents the total processor time the system has used on behalf of all the terminated child processes of the calling process.
terminated child processes of the calling process, excluding child processes which have not yet been reported by wait or waitpid.

**Macros**: defined in the macros: **`CLOCKS_PER_SEC`**, or the 'sysconf' **`_SC_CLK_TCK_`**. There is an old macro: `'int **CLK_TCK**'` - don't use it. Use a newer one.

**Portability Note**: The clock function described in CPU Time is specified by the ISO C standard. The times function is a feature of POSIX.1.
On GNU systems, the CPU time is defined to be equivalent to the sum of the tms_utime and tms_stime fields returned by times.

references:
https://www.gnu.org/software/libc/manual/html_node/Time-Basics.html#Time-Basics </br>
https://www.gnu.org/software/libc/manual/html_node/Processor-Time.html#Processor-Time </br>

Supervision of programs in Linux:
---------------------------------

It is easy to use an 'watchdog' daemon. The term 'watchdog' is usually refered and used to a mechanism that reset/reboots the
process/program/system if it detects that someahow is not running correctly or have stall at some point. Its a safe measurement.


references:
https://linux.die.net/man/8/watchdog <br>
https://linux.die.net/man/8/wd_keepalive <br>
https://linux.die.net/man/8/checkquorum <br>
https://linux.die.net/man/8/wdmd <br>
https://linux.die.net/man/8/wdmd_selinux <br>


Other tools in linux:
--------------------

You can use the Cyclictest program, it is used to measure performance of a system. Reference: https://rt.wiki.kernel.org/index.php/Cyclictest
Also you can monitor system calls with the **ltrace** and **strace** commands.
Also, please, review the testing Real time best practices: http://elinux.org/Realtime_Testing_Best_Practices




INiT ScRiPT DEF:
----------------

printf("CLOCKS_PER_SEC: %d\n", CLOCK_PER_SEC); //safety check





TOOLS:

 logration:  https://www.shellhacks.com/logrotate-force-log-rotation/
 


TODO:

 [ ] https://www.gnu.org/software/libc/manual/html_node/Overview-of-Syslog.html#Overview-of-Syslog  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Sysconf-Definition.html#Sysconf-Definition  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Backtraces.html#Backtraces  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Consistency-Checking.html#Consistency-Checking  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Error-Messages.html#Error-Messages  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Null-Pointer-Constant.html#Null-Pointer-Constant  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/index.html#toc-The-Basic-Program_002fSystem-Interface  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/index.html#toc-Debugging-support  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Error-Recovery.html#Error-Recovery  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html#Memory_002dmapped-I_002fO  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Resource-Usage-And-Limitation.html#Resource-Usage-And-Limitation  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Realtime-Scheduling.html#Realtime-Scheduling  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Basic-Scheduling-Functions.html#Basic-Scheduling-Functions  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Traditional-Scheduling.html#Traditional-Scheduling  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Program-Basics.html#Program-Basics  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Environment-Variables.html#Environment-Variables  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Processes.html#Processes  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Backtraces.html#Backtraces  <br>
 [ ] http://www.list.org/mailman-member/node13.html  <br>
 [ ] https://www.gnu.org/software/libc/  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Processes.html#Processes  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html#Program-Arguments  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-Syntax  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Auxiliary-Vector.html#Auxiliary-Vector  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Environment-Variables.html#Environment-Variables  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Environment-Access.html#Environment-Access  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/Standard-Environment.html#Standard-Environment  <br>
 [ ] https://linux.die.net/man/8/wd_keepalive  <br>
 [ ] https://linux.die.net/man/8/checkquorum  <br>
 [ ] https://gcc.gnu.org/ml/gcc-help/2015-06/msg00071.html  <br>
 [ ] https://solarianprogrammer.com/2012/10/14/cpp-11-timing-code-performance/  <br>
 [ ] http://www.thegeekstuff.com/2012/08/gprof-tutorial  <br>
 [ ] https://rusty.ozlabs.org/?p=330  <br>
 [ ] http://www.drdobbs.com/embedded-systems/measuring-execution-time-and-real-time-p/193502123  <br>
 [ ] http://stackoverflow.com/questions/5248915/execution-time-of-c-program  <br>
 [ ] MinGW compiler. –/ decent libc library. /   Windows XP with cygwin gcc & Linux Ubuntu.  <br>
 [ ] http://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c  <br>
 [ ] http://courseweb.stthomas.edu/resmith/c/cisc130/c9sp/gcc-timing.html  <br>
 [ ] https://www.gnu.org/software/libc/  <br>
 [ ] https://gcc.gnu.org/onlinedocs/gcc-4.6.4/gcc/Optimize-Options.html#Optimize-Options  <br>
 [ ] https://paolozaino.wordpress.com/2015/06/13/c-code-snippet-to-measure-function-execution-time-for-both-linux-and-mac-os-x/  <br>
 [ ] http://stackoverflow.com/questions/5644730/c-measuring-computing-time  <br>
 [ ] http://stackoverflow.com/questions/5644730/c-measuring-computing-time  <br>
 [ ] http://stackoverflow.com/questions/68907/how-do-you-measure-the-time-a-function-takes-to-execute  <br>
 [ ] http://stackoverflow.com/questions/68907/how-do-you-measure-the-time-a-function-takes-to-execute  <br>
 [ ] https://www.gnu.org/software/libc/manual/html_node/CPU-Time.html  <br>
 [ ] http://pcc.ludd.ltu.se/internals/  <br>
 [ ] http://www.tldp.org/LDP/Bash-Beginners-Guide/Bash-Beginners-Guide.pdf  <br>
 [ ] http://www.tldp.org/LDP/tlk/tlk.html  <br>
 [ ] preguntar documentación del último kernel  <br>
 [ ] https://kukuruku.co/post/writing-a-file-system-in-linux-kernel/  <br>
 [ ] http://stackoverflow.com/questions/4714056/how-to-implement-a-very-simple-filesystem  <br>
 [ ] https://en.wikipedia.org/wiki/MINIX_file_system  <br>
 [ ] http://linuxseekernel.blogspot.com.es/2014/06/create-simple-file-system.html  <br>
 [ ] http://www.linuxjournal.com/article/4335?page=0,0  <br>
 [ ]  http://www.linuxjournal.com/article/4395?page=0,0  <br>
 [ ] http://unix.stackexchange.com/questions/67462/linux-kernel-is-not-finding-the-initrd-correctly  <br>
 [ ] http://tr.opensuse.org/MicroSUSE_System_Builder's_Guide  <br>
 [ ] https://github.com/libfuse/libfuse  <br>
 [ ] http://elm-chan.org/fsw/ff/00index_e.html  <br>
 [ ] http://www.minix3.org/theses/gerofi-minix-vfs.pdf  <br>
 [ ] https://msdn.microsoft.com/en-us/library/aa363858(v=vs.85).aspx  <br>
 [ ] https://cboard.cprogramming.com/linux-programming/122773-simple-file-system-c.html  <br>
 [ ] http://www.flipcode.com/archives/Programming_a_Virtual_File_System-Part_I.shtml  <br>
 [ ] http://www.flipcode.com/archives/articles.shtml  <br>
 [ ] http://www.boost.org/doc/libs/1_57_0/libs/filesystem/doc/tutorial.html  <br>
 [ ] http://www.nobius.org/~dbg/practical-file-system-design.pdf  <br>
 [ ] https://developer.apple.com/library/content/documentation/FileManagement/Conceptual/FileSystemProgrammingGuide/Introduction/Introduction.html  <br>
 [ ] https://www.le.ac.uk/users/rjm1/cotter/page_77.htm  <br>
 [ ] http://www.geocities.ws/ravikiran_uvs/articles/rkfs-old.html  <br>
 [ ] https://www.codeproject.com/Tips/1005166/A-Simple-File-System  <br>
 [ ] https://www.quora.com/How-do-I-implement-a-basic-file-system-implementation-in-C-programming-using-inodes  <br>
 [ ] https://psankar.blogspot.com.es/2013/08/introducing-simplefs-ridiculously.html  <br>
 [ ] https://cboard.cprogramming.com/c-programming/95819-file-system-implementation.html  <br>
 [ ] https://en.wikipedia.org/wiki/Unix_File_System  <br>
 [ ] http://www.cs.cornell.edu/courses/cs4410/2010fa/CS4411/slides/project6/project6.pdf  <br>
 [ ] http://www.geocities.ws/ravikiran_uvs/articles/rkfs-old.html  <br>
 [ ] http://haifux.org/lectures/120/writing-linux-2.4-fs/writing-linux-2.4-fs.html  <br>
 [ ] https://github.com/psankar/simplefs  <br>
 [ ] http://www.cs.ucsb.edu/~chris/teaching/cs170/projects/proj5.html  <br>
 [ ] http://web.mit.edu/6.033/1997/handouts/html/04sfs.html  <br>
 [ ] http://pages.cs.wisc.edu/~remzi/OSTEP/file-implementation.pdf  <br>
 [ ] http://www.tldp.org/pub/Linux/docs/ldp-archived/linuxfocus/Castellano/September2001/article198.shtml <br>
 [ ] https://rt.wiki.kernel.org/index.php/Cyclictest <br>
 [ ] Real-Time Linux Wiki: https://rt.wiki.kernel.org/index.php/Main_Page
 [ ] comment on linux panic!!
 
    NPTL (Native POSIX Threads Library) is the GNU C library POSIX
       threads implementation that is used on modern Linux systems.
       
https://man7.org/linux/man-pages/man7/nptl.7.html

REFERENCE: https://www.gnu.org/software/libc/manual/html_node/index.html#Top


C and C++ programming notes:
==============================


> A nice way to hardcore a string is the following. It should compute and allocate the memory automatically.

```c
char *str = "Hello World!";
```

... but this is not accepted after C++ 11; ... 


> never ever write an infinite loop, without a break condition- it may be loop forever.

> always include system identification (hw and sw) methods.

> always include parameters files

> in switch-case loops always include a default condition, for fallback, and getting errors.

> in switch-case loop always include a break condition, the only excetpion is when doing 'cases' fall.

> in a 'for' loop (and in the 'while' loop if needed) never ever modify the counter varible inside the loop.

> Error-detection methods must be handledn inside the called function. If w r using c++ include always a try-catch clause.

> error-handling methods should be handled by a custom function, because it take less space in the cache, thus increasing the memory usage performance. 

> watch out for asignations as conditions (ex: if(x=0) ) -- in most cases this is an semantic error (the desired instruction would be: if(i==0) ) 

> functions should never return 'void', ... at least, if not a result the can return a 0 if the funtion was OK, or !0 if an error,
also a numeric value could represent the kind of error, that way, the error could be handled like:

```c
if( my_function() ) {
  error_my_function();
}
```

Notes on various time functions:
===============================

    The current (2008/13) POSIX recommendation to find the calendar
    time is to call clock_gettime(), defined in <time.h>.  This may
    also be used to find the time since some unspecified starting
    point (e.g. machine reboot), but is not currently so used in R.
    It returns in second and nanoseconds, although not necessarily to
    more than clock-tick accuracy.

    C11 adds 'struct timespec' to <time.h>.  And timespec_get() which
    can get the current time or interval after a base time.

    The previous POSIX recommendation was gettimeofday(), defined in
    <sys/time.h>.  This returns in seconds and microseconds (with
    unspecified granularity).

    Many systems (including AIX, FreeBSD, Linux, Solaris) have
    clock_gettime(): it appeared in macOS 10.12.  macOS and Cygwin
    have gettimeofday().

    Function time() is C99 and defined in <time.h>.  C99 does not
    mandate the units, but POSIX does (as the number of seconds since
    the epoch: although not mandated, time_t seems always to be an
    integer type).

    Function clock() is C99 and defined in <time.h>.  It measures CPU
    time at CLOCKS_PER_SEC: there is a small danger of integer
    overflow.

    Function times() is POSIX and defined in <sys/times.h>.  It
    returns the elapsed time in clock ticks, plus CPU times in a
    struct tms* argument (also in clock ticks).

    More precise information on CPU times may be available from the
    POSIX function getrusage() defined in <sys/resource.h>.  This
    returns the same time structure as gettimeofday() and on some
    systems offers millisecond resolution.
    It is available on Cygwin, FreeBSD, macOS, Linux and Solaris.




Challenges:

find the bug in this c++ code:
```c++
vector<int> v;   //vector of integers
for(int i; cin>>i; )   //get values
    v.push_back(i);
for(int i; i<=v.size(); ++)  //print values
    cout<<"v["<<i<<"]== "<<v[i]<<'\n'; 
```

LAMDA EXPRESSIONS 
=================

Lamda expressions is a way to pass code as an argument.
Parts:

[capture] - identifies externals variables that will be possible to read. also if those variables will be passed by value or by 
reference.

(parameters) - parameters passed to the lambda function

-> returntype declaration -- this specifies the return type

{ lambda_function_statements; }


you most probably want to store the function, the easyest way is to use the 'auto' keyword, to automatically asing the type to
the lambda expression return



const and constexpression:
=========================

const: stands for constands, that forces those values cannot be overwrittens, so, its a kind of READ_ONLY flag.
constexprex: ... can to be evaluated at compile time. When this is defined, the compiler will attemp to calculate the value, and 
substitute it in the final code of the program.

pointers and arrays- declarator operators: *,[],&:
=====================================================

the declarator operators, are unary operators, and are: *, [], &.
*: pointer
[]:array
&: reference to


* is the derefencing operator, used for defining pointers, also '&' is the address operator that returns the address of a variable.

given a certain data type, named 'mytype'

mytype myvar; //this is a defined variable of type 'mytype'
mytype* myvar; //this is a pointer to a variable of type 'mytype'
mytype myvar[n];  //this is an array of elements of type 'mytype'. the index starts in '0'. so it goes from '0' to 'n-1', that is 'n' elements in total.
mytype& myvar; // & is the address operator. this is a reference to a 'type' variable; 

Watch out the pointers aritmetic!!

nullptr: this is keyword for an empty pointer. Sometimes it is represented as the NULL macro. 

void* : this is a special pointer, that returns a pointer with no type, or that makes no asumption about the returning type.


to initialize an array, it is easy to use the {} initialization.
type myarray[]={1,2,3,4, ... ,n};

there is other operator, the field derefenced pointer, used to access the members of a class or structure:

struct person {
 const char* name;
 int age;
 char gender;
 }
 
 this can be initialized with {}:
 
 person John{"John Smith", 32, "M"};
 
 person* him;
 him->age = 33; //this is equal to (*him).age = 33;
 
 sor for a member; p->m is equivalente expresion as p.m 



flow-control sctructures:
===========================

for loops:
----------

for(init_estatement; condition; loop_iteration) {}
for(int i=0; i<10; i++) {}

range-for-statements:
-----------------------

for(type x: v) this is read as: "for each element x in the range of v". So v must be a type with a given interator, that is exists, v.begin() and v.end().

```c
int v[]={1,2,3,4,5,6,7,8,9};
for(auto x:v)
{
   cout<< x << endl;  //for each element x in 'v', do the loop
}
```

```
int v[]={1,2,3,5,7,11,113,17,19,23,29,31,27,41,43,47}; //primes below 50.
for(auto x:v)
{
   cout<< 'prime:' << x << endl;  //for each element of 'v', do the loop
}
```

key words for function definitions:

 - inline : function is inlined at each call
 - void : no return type
 - contsexpr: the function will be a const expression at compile time if contexpr parameters are given
 - noexcept: the function may not throw any exception
 - virtual: it can be overwritten by a subclass
 - override: it must be overwritten by a subclass
 - final: it cannot be overwritten by a subclass
 
 
 
 TODO: pointers to functions.
 TODO: arguments as value, as refence.
 
 signals how to:   https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/signal.h.html
 
 Static Functions in C:
 in C by a function that is declared as Static, can only be used in the file in wich it is defines, so a kind of making it privat.
so those function cannot be accessed from other files. 
 
 
 
 
 CODE SNIPPETS:
 
 factorization:
 
 ```c++
 inline int fact(int n)
 {
     return (n<2)?1:n*fact(n-1);
 }
 ```
 
 ```c++
 void swap(int*, int*);
 
 void swap(int* a, int* b);
 {
     int c =  *a;
     *b = *a;
     *a = c;
 }
 ```
 
```c++
int& max(int&, int&, int&);
 
int& max(int& a, int& b, int& c);
{
    return (a>b)?((a>c)?a:c):((b>c)?b:a);
}
 ```

```c++
// friendly code to CLEAR a bit in a byte
// in this example is the third (3º) bit 0x0100 = 0x4

	ByteData &= ~0x04; 
```
```c++
// friendly code to SET a bit in a byte
// in this example is the third (3º) bit 0x0100 = 0x4

	ByteData |= 0x04; 
```

```c++
for(;;) //this is forever... a naughty way to write: while(1)
```

error macro:
```C
   #define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                               } while (0)
```





ref: Ralston and Rabinowitz: A First Course in Numerical Analysis.

ref: Computer Approximations, John Fraser Hart
