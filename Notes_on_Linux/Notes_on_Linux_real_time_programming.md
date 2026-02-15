# Notes on Linux real time programming

## Introduction real time computing 

Real time computing, refers to to systems where the corretness of the operations depends on not only the logical results of computations, but also on the time at which the results are produced. The **timeliness** is relevant in a real-time program.

The defining characteristic of a real-time system is compliance with the **timing constrains**. These constrains are called **deadlines**. 
- **Met deadline**: the system operates correctly.
- **Missed deadline**: the system has failed, even if the computed result is mathematical perfect.

Key characteristics of a real-time system:
- **Determinism**: this is the ability of a system to respond to events within  a known, predictable and guaranteed time frame. It's not about being "fast" but about being **predictable**.
- **Predictability**: The system's behaviour must be predictable under all possible conditions, including peak loads. The system should be possible to be analyzed and guarantee all deadlines before the system is even build.
- **Responsiveness**: This involves two factors:
    - **Latency**: The time between an event occurring and the system recognizing it (e.g. an interrupt being serviced)
    - **Jitter**: The variation in latency. For tasks that need to happen periodically. High jitter means the timing is unpredictable. 


### Types of real-time systems

Real time systems are categorized on the severity of missing a deadline.

**Hard real-time system**: Missing a deadline is catasthrophic and considered a total system failure. It can lead to human injury, death, significant material losses or enviromental damages. It is requiered to have absolute predictibillity and 100% guarantee to met all the deadlines. This is achieved by means of mathematical scheduling analisys. Examples of a hard real-time systems: airbag, ABS, aircraft flight control system, nuclear reactor cooling control system.  

**Soft real-time system**: Missing a deadline is undesireable and degrades performance or quality but it is not catastrophic. The system continues to operate , but its utility or effectiveness is reduced. The system strives to meet deadlines and has high predictability, but occasional misses are tolerated. The focus in on high average throughput and low average latency. Examples of soft real-time systems are: video/audio streaming, live video conferency system. 

**Firm real-time system**: Is a sub-set of soft real-time system, missing a deadline is not catastrophic, but the result of the computation has not value after the deadline. There is no point in executing the task late. The consecuence of missing a deadline is that the data is dropped and the system moves into the next step. Examples: radar sweep, stock trading algorithms. 


## Why real-time in Linux

 - Linux provides a solid foundation that specialized real-time operating systems (RTOS) often lack. 
 - It has a wide hardware support: great number of drivers and devices. This shortens development time and costs for writing drivers.
 - Rich software ecosystem: there are lots of development tools as libraries, debuggers, profilers ...
 - performance for non-real time tasks: Linux can handle both real-time and non-real time tasks.
 - The technical challenge, is that Linux is not naturally real-time:
    - Preemption: In standard linux, a low priority running task in the kernel can block a high priority running task.
    - interrupts (IRQs): Hardware interrutps have the highest priority. When an interrupt service arrives, the CPU inmediately stops what it is doing to handle it. This interrupt service routine (ISR) can introduce unpredictable delays, known as **interrupt latency**.
    - Synchronization locks: The kernel uses locks to protect shared data. A high  priority task might have to wait (priority inversion) for a low priority task to finish with a lock, breaking real-time guarantees. 

For all those problems: preemption, IRQs, and synchroniization locks (priority inversion), there is a solution, and that is the PREEMPT_RT patch (The "real-time" patch). 

The PREEMPT_RT patch fundamentally changes the kernel's behaviour to drastically reduce latency and make it deterministic. It's main development are: 
- Kernel preemption: In the standard linux kernel, the tasks can only be preemted at specific points, whith the PREEMT_RT most of the kernel can be preempted and any time. So a high priority task can preempt a low priority task in the kernel reducing the scheduling latency.
- Interrupt latency: In the standard linux kernel, the interrupts are handled by the ISRs (Interrupt Service Routines) but in the PREEMPT_RT all interrupts handles run as kernel threads with a priority, so interrupts can be preempted with highier priority threads. This allows priorization and eliminates one major source of impredictibility.
- Priority inheritance: for standard linux kernel it is limited or not always enabled, but with the PREEMPT_RT patch it is enabled for kernel mutexes. This solves the priority inversion problem, if a low priority task holds a lock needed by a high priority task, the low priority task "inherits" the high priority until it releases the lock.
- Sleeping spinlocks: in the standard linux kernel, the spin locks are busy-wait and cannot sleep, with the PREEMPT_RT patch the spin-locks are converted to sleepable mutexes. This preventes a task holding a lock from blocking the entire CPU, allowing other tasks to run. 
