# Notes on Linux kernel synchronization

## Concurrency 

Concurrency is the ability to handle multiple tasks/process with the illusioin or reallyti of simulatanety

In single core enviroments, concurrency is achieved via a process called contex-switching, e.g. at a particular time period only a single task 
gets executed, but tasks run interleaving between them very fasts given the illusion of running simultaneoulsy.

IN a multi-core enviroment (parallelism) every core can execute different tasks.

Reference: Concurrency is not Parallelism by Rob Pike: https://www.youtube.com/watch?v=oV9rvDllKEg

To find the number of processors in the system, use:

```
grep -c ^processor /proc/cpuinfo
nproc
lshw
```

To find the processor in which a task/process is running: 

```
ps -eaF | less
```

The PSR colummn reports in which CPU is the process running.

### Multiprocessors systems

There are different arrangements to work in multi-processor systems

#### Each CPU has its own operating system.

 The simples way way to orginize a multi-processor system, is that every CPU has its OS. Statically 
divide the memory into as many partitions as CPUs and give each CPU is own private memory, and its own
private copy of the operating system, and private copy of the data.
 
There are some downsides to this approach: 
- When a process makes a system call, the system call is caught and handled on its won CPU using the data structures in the operating system tables.
- Since each operating system has its own tables, it also has its own set of process that it schedules by itself. There is 
no sharing of processes. As a consecuence, it can happen that CPU 1 is idle while CPU 2 is loaded with work.
- There is no sharing of memory pages. It can happen that CPU 1 has pages to spare while CPU 2 is paging continuously. There
is no way for CPU 2 to borrow some pages from CPU 1 since the memory allocation is fixed and not shared. 
- If the operating system mantains a buffer cache of recently used disk blocks, each operating system does 
this indepedentrly of the rest. So it may be possible that a certain disk block is present and dirty in multiple
buffer caches at the same time, leading to inconsistent results.

#### Master-slave model

In this arragement, one copy of the operating system and its tables are present on CPU 1 and not on any of
the other cores. All system calls are redirected to CPU 1 for processing there. CPU 1 may also run user 
processes if there is CPU time left over. 

The problems with regards of the arrangement in which each CPU had its own operating system are solved in 
this arragement: 

- There is a single data structure (e.g, one list or set of prioritized lists) that keeps track of ready 
processes. When a CPU goes idle, itt asks the opoerating system for a process to run and it is assigned one. 
Thus, in is not possible that one CPU is idle while other CPU is overloaded. 
- Similary, memory pages can be allocated among all the processes dynamically and there is only one buffer 
cache, so inconsisteces will not happen.

On the other hand there are still downsides in this arragement:
- The problem is that with many CPUs, the master will become a bottleneck, due it mus handle all system calls 
from all CPUs.
- If, let's say that 10% of all time is spent handling system calls, then 10 CPUs will pretty much saturate
the master, and with 20 CPUs it will be totally overloaded.
 
So this model is simple and workable for small multi-processors, but it will fall sort for large multi-processor systems.

#### Simetric Multriprocesors (SMP)

There is one copy os the operating system in memory but any cpu can run it. This is the model of the linux kernel intiially.

The advantage of this model is that it removes the bottleneck of the previous models.

But it still has some downsides:

- Imagine two CPUs simultaneously pick the same process to run or claiming the same free memory page.
The solution to the problem is to use a lock (or mutex or semaphore) wit the operating system, making the
whole system one big critical section.

 When a CPU wants to run the operating system code, it must first adquire the lock. If the lock is taken 
then it just waits. In this way, any CPU can run the operating system, but only one at a time. But with

 But in the case of having many CPUs, for example 20 CPUs, there will be long queues of CPUs wainting to get in.
Fortunately, it is easy to improve. Many parts of the operating system are independent of one another. For
example, there is no proble wit one CPU running the scheduler wihle another CPU si handling a file system
call and a thrird one wi processing a page fault.

 This observation leads to splitting the operating system nto independen critical regiions that don not interact
with one another. Each critical region is protected by its own mutex, son only one CPU at a time can execute it.
 
### Preemtion and context switching in Linux kernel

#### What is preemption?

Preemption means forcefully taking away of the processor from one process and allocating it to another process.  Switching

Switching from one running task/process to anothe process is known as contex switch. 

In the linux kernel, the scheduler is called after each timer interrupt (that is, quite a few times per second).
It determines what process si to run next on a variety of factors, including prioriy, time already run, scheduling policy...

The difference betwwen preemption and context switching?

- Preemption : firing of a timer interrupt is preemting the current running process and running the interrupt service 
routing of timer interrupts.
- Context switch: what happens when the kernel alters the state of the processors (the registers, mode and stack) between one process thread's context and another. 
`context_switch()` function is called in the kernel. 






 



