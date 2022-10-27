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

To search for the context_switch in the linux kernel code: 

```
grep -nr 'context_switch()'
```
It is defined at: https://elixir.bootlin.com/linux/v6.0/source/kernel/sched/core.c#L5131

```
/*
 * context_switch - switch to the new MM and the new thread's register state.
 */
static __always_inline struct rq *
context_switch(struct rq *rq, struct task_struct *prev,
	       struct task_struct *next, struct rq_flags *rf)
{
	prepare_task_switch(rq, prev, next);

	/*
	 * For paravirt, this is coupled with an exit in switch_to to
	 * combine the page table reload and the switch backend into
	 * one hypercall.
	 */
	arch_start_context_switch(prev);

	/*
	 * kernel -> kernel   lazy + transfer active
	 *   user -> kernel   lazy + mmgrab() active
	 *
	 * kernel ->   user   switch + mmdrop() active
	 *   user ->   user   switch
	 */
	if (!next->mm) {                                // to kernel
		enter_lazy_tlb(prev->active_mm, next);

		next->active_mm = prev->active_mm;
		if (prev->mm)                           // from user
			mmgrab(prev->active_mm);
		else
			prev->active_mm = NULL;
	} else {                                        // to user
		membarrier_switch_mm(rq, prev->active_mm, next->mm);
		/*
		 * sys_membarrier() requires an smp_mb() between setting
		 * rq->curr / membarrier_switch_mm() and returning to userspace.
		 *
		 * The below provides this either through switch_mm(), or in
		 * case 'prev->active_mm == next->mm' through
		 * finish_task_switch()'s mmdrop().
		 */
		switch_mm_irqs_off(prev->active_mm, next->mm, next);

		if (!prev->mm) {                        // from kernel
			/* will mmdrop() in finish_task_switch(). */
			rq->prev_mm = prev->active_mm;
			prev->active_mm = NULL;
		}
	}

	rq->clock_update_flags &= ~(RQCF_ACT_SKIP|RQCF_REQ_SKIP);

	prepare_lock_switch(rq, next, rf);

	/* Here we just switch the register state and the stack. */
	switch_to(prev, next, prev);
	barrier();

	return finish_task_switch(prev);
}
```
MM is the memory management, defined in the strcut mm_struct \*mm.

#### Preemtion in user and kernel spaces

In user-space, the programs are always preemptible. The kernel interrupts user-space programs to swithc to other threads, using the regular clock tick.  

So the kernel doesn't wayt fo ruser-space programs to explicity release the processor. This means that
an infinite loop in an user-space program cannot block the system.

In the kernel space, until 2.6 kernel, the kernel itself was not preepmtible. As soon as a thread entered the kernel, it could not be preempted to execute another thread. The processor could be used to execute another thread  when a syscal was terminated, or when the current thread explicitl asked toe scheduler to run another thread using the schedule(). That meant that an infinete loop in the kernel code would block the entire system.

However, this absence of preemption in the kernel caused several problems with regard to latency and scalability. 

The kernel preemption was introduced in the 2.6 kernel, and one can enable or disable it using the CONFIG_PREEMPT option. Thus an infinite loop in the kernel code cannot longer block the entire system.

The kernel was done preemptible to reduce the dispach latency of the user mode processes. the dealay between the time they become runnable and the time they actually beging running. Processes perfonrming timely scheduled tasks (such as external hardware controllers, monitors, ...) really benfit from kernel preemption because it reduces the risk of being delayed by another process running in kernel mode. 

kernel preemption can happen: 
- when returning to kernel-space from an interrupt handler.
- when kernel code becomes preemptible again
- if a task in the kernel sxplicitly calls `schedule()`
- if a task in the kernel blcoks (which results in a cal to `schedule()`.

Example: 
 While a given process A executes and exception handler (necessaly in kernel mode), a higher priority process B comes runnable. 
 
 This could happen, for instance, if an IRQ occurs and the corresponding handler awakens process B.
 As the kernel is preemptive, a forced process switch replaces process A with B.
 The exception handler is left unfinished and will be resumed only when the scheduler selects again process A for execution. 
 
 Kernel pre-emption does not help in the overall throughput of the system. Instead, it seeks for better responsiveness.

The idea here is that normally kernel functions are only interrupted by hardware causes: Either external interrupts, or IO wait cases, where it voluntarily gives away control to the scheduler. A pre-emptive kernel instead also interrupts and suspends kernel functions just like it would interrupt processes in user mode. The system is more responsive, as processes e.g. handling mouse input, are woken up even while heavy work is done inside the kernel.

Pre-emption on kernel level makes things harder for the kernel developer: The kernel function cannot be suspended only voluntarily or by interrupt handlers (which are somewhat a controlled environment), but also by any other process due to the scheduler. Care has to be taken to e.g. avoid deadlocks: A thread locks resource A but needing resource B is interrupted by another thread which locks resource B, but then needs resource A.

 #### Reentrancy
 
 A kernel control path denotes the sequence of instruction executed by the kernel to handle a system call, and execption or an interrupt.
 
 The Linux kernel is reentrant. This means that several processes may be executing in kernel mode at the same time. 
 
 On single-core systems only one process can progress at a time, but many can be blocked in the kernel mode when waiting for the CPU or the completion of some I/O operation. 
 
 Example: 
   After issuing a read to a disk on behalf of a process, the kernel lets the disk controller handle it and resumes executing other processes. 
   An interrupt notifies the kernel when the device has satisfied the read, so the former proces can resume the execution. 
   
The reentrancy functions types in the linux kernel can be: 
 - Reentrant functions: they don't user/modify global data structures
 - Non reentrant functions: functions that modify global data strcutures but use locking mechanisms. 

reference: https://www.quora.com/What-is-meant-by-a-reentrant-kernel <br>
reference: https://teleedu.wordpress.com/2012/11/25/preemptive-and-reentrant-kernel/ <br>
reference: http://www.linfo.org/kernel_mode.html <br> 
reference: https://stackoverflow.com/questions/1163846/what-is-a-reentrant-kernel <br>

A re-entrant kernel enables a process (and it’s threads) to give away the CPU while in kernel mode. They do not hinder other processes from also entering kernel mode. This behavior allows CPU to be shared among multiple processes.

A typical use case is IO wait. The process wants to read a file. It calls a kernel function for this. Inside the kernel function, the disk controller is asked for the data. Getting the data will take some time and the function is blocked during that time.

With a re-entrant kernel, the scheduler will assign the CPU to another process (kernel thread) until an interrupt from the disk controller indicates that the data is available and our thread can be resumed. This process can still access IO (which needs kernel functions), like user input. The system stays responsive and CPU time waste due to IO wait is reduced.

All Unix kernels are reentrant. This means that several processes may be executing in Kernel Mode at the same time. Of course, on uniprocessor systems, only one process can progress, but many can be blocked in Kernel Mode when waiting for the CPU or the completion of some I/O operation.

If a hardware interrupt occurs, a reentrant kernel is able to suspend the current running process even if that process is in Kernel Mode. This capability is very important, because it improves the throughput of the device controllers that issue interrupts.

Ex: The Linux kernel Version 2.6 (which was introduced in late 2003) is preemptive. That is, a process running in kernel mode can be suspended in order to run a different process. This can be an important benefit for real time applications (i.e., systems which must respond to external events nearly simultaneously). Unix-like kernels are also re-entrant, which means that several processes can be in kernel mode simultaneously. However, on a single-processor system, only one process, regardless of its mode, will be progressing in the CPU at any point in time, and the others will be temporarily blocked until their turns.

### Synchronization and critical regions: problems and solutions

Implementing a reentrant kernel requires the use of synchronization. 

If a kernel control path is suspended while acting on a kernel data structure, no other kernel control path should be 
allowed to act on the same data structure unless it has been reset to a consistent state. 

Otherwise, the interaction of the two control paths could corrupt the stored information. 

When the outcome of a computation depends on how two or more processes are scheduled, the code is incorrect. We say that there is a race condition. 
	  
A **race condition** happens when multiple threads/processes/routines try to access and modify the same data. So one overwrites the value of other, resulting in an incorrect value. When race conditions arise, is known in software as **critical-sections** which  are code that fits to **RUW**: `read-update-write`. For example: `i = i+1`.

```
routine 1           routine 2
read i = 0   
                    read i = 0
increment i+1 = 1
                    imcrement i+1 = 1
write 1 
                    write 1 // this overwrites the resulti
```

we would be expecting 2 as a result, but we got 1, because the order of the routines
	   
Any section of code that should be finished by each process that begins it before another process can enter it is called **critical region**. 

The sources of concurrency on the kernel are:
- Interrupts: an interrupt can happen asynchronously at almost any time, interrupting the current executing code
- Softirqs and tasklets: the kernel can raise or schedule a softirq or tasklet at almost any time.
- Sleeping and synchronization with user space: Task in the kernel can sleep and thus invoke the scheduler, resulting in running of a new process
- Symetrical multiprocessor: two or more processors can execute kernel code at exactly the same time. 



