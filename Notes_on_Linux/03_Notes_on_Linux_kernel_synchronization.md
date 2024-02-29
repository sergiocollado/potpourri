# Notes on Linux kernel synchronization

references:
- https://www.makelinux.net/ldd3/?u=chp-5-sect-5.shtml
- https://0xax.gitbooks.io/linux-insides/content/SyncPrim/
- [404] EEC3-4029 Operating Systems: http://gauss.ececs.uc.edu/Courses/c4029/videos.html 
- linux-kernel-labs: https://linux-kernel-labs.github.io/refs/heads/master/index.html 
- https://lwn.net/Kernel/Index/#Locking_mechanisms <br>
- https://github.com/shemminger/kernel-examples  -Locking and concurrency in Linux kernel examples 
- https://github.com/PacktPublishing/Linux-Kernel-Programming/blob/master/Linux-Kernel-Programming-(Part-2)/Linux%20Kernel%20Programming%20Part%202%20-%20Char%20Device%20Drivers%20and%20Kernel%20Synchronization_eBook.pdf  
- Linux kernel memory model: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0124r6.html 
- https://www.cs.bham.ac.uk/~exr/lectures/systems/08_09/docs/kernelAPI/ 
- linux kernel API cheatsheet: https://www.cs.bham.ac.uk/~exr/lectures/systems/08_09/docs/kernelAPI/ 
- https://embetronicx.com/linux-device-driver-tutorials/ 


## CONCURRENCY

Concurrency is the ability to handle multiple tasks/process with the illusion or really of simulatanety

In single core enviroments, concurrency is achieved via a process called context-switching, e.g. at a particular time period only a single task 
gets executed, but tasks run interleaving between them very fasts given the illusion of running simultaneoulsy.

In a multi-core enviroment (parallelism) every core can execute different tasks.

Reference: Concurrency is not Parallelism by Rob Pike: https://www.youtube.com/watch?v=oV9rvDllKEg

To find the number of processors in the system, use:

```
grep -c ^processor /proc/cpuinfo
nproc
lshw
lscpus # info from  /proc/cpuinfo
grep NR_CPUS /boot/config-`uname -r`  # this is the max number of processors that a SMP kernel could support
# For modules: use the function `num_online_cpus()` to get the number of cpus online # you can use it in a module.
# For modules: use the function `smp_processor_id()` to report the current processor number on which the kernel is running.
```

To find the processor in which a task/process is running: 

```
ps -eaF | less
```

The `PSR` colummn reports in which CPU is the process running.

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

There is one copy of the operating system in memory but any cpu can run it. This is the model of the linux kernel intially.

The advantage of this model is that it removes the bottleneck of the previous models.

But it still has some downsides:

- Imagine two CPUs simultaneously pick the same process to run or claiming the same free memory page.
The solution to the problem is to use a lock (or mutex or semaphore) wit the operating system, making the
whole system one big critical section.

 When a CPU wants to run the operating system code, it must first adquire the lock. If the lock is taken 
then it just waits. In this way, any CPU can run the operating system, but only one at a time. But with

 But in the case of having many CPUs, for example 20 CPUs, there will be long queues of CPUs wainting to get in.
Fortunately, it is easy to improve. Many parts of the operating system are independent of one another. For
example, there is no problem wit one CPU running the scheduler wihle another CPU is handling a file system
call and a thrird one wi processing a page fault.

 This observation leads to splitting the operating system into independent critical regions that don't interact
with one another. Each critical region is protected by its own mutex, son only one CPU at a time can execute it.
 
### Preemtion and context switching in Linux kernel

#### What is preemption?

Preemption means forcefully taking away of the processor from one process and allocating it to another process. 

Switching from one running task/process to anothe process is known as contex switch. 

In the linux kernel, the scheduler is called after each timer interrupt (that is, quite a few times per second).
It determines what process si to run next on a variety of factors, including prioriy, time already run, scheduling policy...

#### What is the difference between preemption and context switching?

- Preemption : firing of a timer interrupt is preemting the current running process and running the interrupt service 
routing of timer interrupts.
- Context switch: what happens when the kernel alters the state of the processors (the registers, mode and stack) between one process thread's context and another. 
`context_switch()` function is called in the kernel. 

To search for the `context_switch` in the linux kernel code: 

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
`MM` is the memory management, defined in the struct `mm_struct`

#### Preemtion in user and kernel spaces

In user-space, the programs are always preemptible. The kernel interrupts user-space programs to swithc to other threads, using the regular clock tick.  

So the kernel doesn't wayt fo ruser-space programs to explicity release the processor. This means that
an infinite loop in an user-space program cannot block the system.

In the kernel space, until 2.6 kernel, the kernel itself was not preemptible. As soon as a thread entered the kernel, it could not be preempted to execute another thread. The processor could be used to execute another thread when a `syscall` was terminated, or when the current thread explicitly asked the scheduler to run another thread using the `schedule()`. That meant that an infinete loop in the kernel code would block the entire system.

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
 
 A kernel control path denotes the sequence of instruction executed by the kernel to handle a system call, and exeption or an interrupt.
 
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
- Symetrical multiprocessor (SMP): two or more processors can execute kernel code at exactly the same time. 

### Example module for procesor id of kernel thread

```
static struct task_struct *my_thread;

int thread_function(void *pv)
{
    int i=0;
    while(!kthread_should_stop()) {
        printk(KERN_INFO "Processor id:%d\t In thread function %d\n", smp_processor_id(), i++);
	msleep(1000);
    }
    return 0;
}

static int __init my_driver_init(void)
{
    pr_info("%s: In init NR_CPUS=%d\n", __func__, NR_CPUS);
    pr_info("Number of cpus availables: %d\n", num_online_cpus());
    pr_info("%s: processor id:%d\n", __func__, smp_processor_id());
    my_thread = ktrhead_create(thread_function, NULL, "myThread");
    if (my_thread) {
        wake_up_process(my_thread);
	return 0;
    } else {
        print(KERN_ERR "Cannot crate kthread\n");
	return -1;
    }
}

void __exit my_driver_exit(void)
{
    kthread_stop(my_thread);
}

module_init(my_driver_init);
module_exit(my_driver_exit);
MODULE_LICENSE("GPL");
```

If we run this module, we can see that in a multi-core system, the reported CPUS, will change. Everytime we hit sleep, the
scheduler() will reassign the code to a cpu.

## PER CPU VARIABLES

reference: https://0xax.gitbooks.io/linux-insides/content/Concepts/linux-cpu-1.html

This is the simplest and most efficient synchronization technique consists of declaring kernel variables as per-CPU varialbes.

Basically a per CPU varibles is an aray of data structures, one element per each PCU in the system.

A CPU should not access the elements fo the array corresponding to other CPU.

It can freely read and modify its own element without fera of race conditions, because it is the only CPU entitled to do so.

The elemets of the per-CPU array are aligned in main memory so that each data structure falls on a different line of the hardware cache. 

Example of per-CPU variables:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#incldue <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>

#define COMPANY_NAME "linux"

MODULE_LICENSE("gpl");
static struct proc_dir_entry *file_pde; //pde -rpoc directory entry
unsigned int percpu_data[NR_CPUS]; /* NR_CPU: number of CPUs */

static int cpu_show(strcut seq_file *m, void *v)
{
    int i;
    for (i = 0; i < num_online_cpuss(); i++)
        seq_printf(m, "Processor %d:%u\n", i, percpu_data[i]);
    return 0;
}

static int my_open(struct indoe *inode, strcut file *file)
{
    return single_open(file, cpu_show, NULL);
}

static sszie_t proc_write_cpu(struct file *file, const char *buffer, size_t count, loff_t *data)
{
    unsigned cahr buff[10];
    unsigned int user_val;
    int cpu;
    
    pr_info("%s\n", __func__);
    if (copy_from_user(buff, buffer, count))
    {
        return -EFAULT;
    }
    else 
    {
        buf[count] = '\0';
	user_val = simple_strtoul(buf, NULL, 10);
	
	cpu = get_cpu(); /* get current processor and disable kernel preemption */
	percpu_data[cpu] = user_val;
	printk("percpu_data on cpu=%d is %u\n", cpu, percpu_data[cpu]);
	put_cpu(); /* enable kernel preemption */
    }
    return count;
}

static struct file_operations cpu_ops = {
    .owner = THIS_MODULE,
    .open = my_open, 
    .read = seq_read,
    .llseek = seq_lseek,
    .write = proc_write_cpu,
}; 

static int hello_init(void)
{
    pr_info("%s: In init\n", __func__);
    
    file_pde = proc_create("percpu", 0644, NULL, &cpu_ops);
    if (!file_pde) {
        pr_err("%s: error createing proc file\n", __func__);
	return -1;
    }
    return 0;
}

static void hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
    remove_proc_entry("percpu", NULL);
}

module_init(hello_init);
module_exit(hello_exit);
```

Once loaded the module we can check: `cat /proc/percpu`, then writhe to the file : `sudo chmod 666 /proc/percpu && echo '5' > /proc/percpu`. And check again:`cat /proc/percpu`. And then `watch echo '5' > /proc/percpu`

So, `get_cpu()` on top of returning the current processor number also disables kernel preemption. `put_cpu()` enables kernel preemption. 

Disable kernel preemtion is needed, because if a kernel control path gets the address of its local copy of a per-CPU variable, and then it is preempted and moved to another CPU: the address still refers to the element of the previous CPU. 

After kernel 2.6, a new interfec nknow as percpu, was created. It uses: <linux/percpu.h>. To create a per-CPU variable at compile time use the macro: 

```
DEFINE_PER_CPU(type, name);
```

This creates an instance of variable of type 'type', named 'name', for each CPU on the system. Eg:

```
DEFINE_PER_CPU(int, i);
DEFINE_PER_CPU(int[3], my_array);
```

In case it is needed a decalaration of the variable elsewhere, to avoid compiile warnings, use the macro: 

```
DECLARE_PER_CPU(type, name);
```

You can handle the variables with the `get_cpu_var()` and `put_cpu_var()` routines.

A call to `get_cpu_var()` returns an lvalue for the given variable on the current processor. it also disables preemption, which `put_cpu_var()` correspoindgly enables. 

An `lvalue` (locator value) is a nomeclature, that represents an object that has a given address in memory (for example, any value which is defined). 

Example of the interface:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/percpu.h>

MODULE_LICENSE("GPL");

static DEFINE_PER_CPU (long, percpuvar) = 5;

static int __init test_hello_init(void)
{
     int cpu;
     pr_info("percpuvar=%ld\n", get_cpu_var(percpuvar)++); /* get_cpu_var() will desable kernel preemption */
     cpu = smp_processor_id ();
     printk("current cpu = %d\n", cpu);
     put_cpu_var(percpuvar);                               /* put_cpu_var() will enable back the kernel preemption */
     pr_info("percpuvar=%ld\n", get_cpu_var(percpuvar));
     cpu = smp_processor_id ();
     printk("current cpu = %d\n", cpu);
     put_cpu_var(percpuvar);
     
     return -1;
}

static void __exit test_hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

`smp_processor_id()` returns the current processor number, between 0 and NR_CPUS . These values are not necessarily continuous: to get a number between 0 and smp_num_cpus() (the number of actual processors in this machine), the `cpu_number_map()` function is used to map the processor id to a logical number. `cpu_logical_map()` does the reverse.

reference: https://www.kernel.org/doc/htmldocs/kernel-hacking/routines-processorids.html

If it is needed another processor's copy of the variable, use: `per_cpu(variable, int cpu_id)`. In case to implement code that involves one processor reaching into each other's per-CPU variables, you need to implement a lockging schemer that makes the access safe. 

Example: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/percpu.h>

MODULE_LICENSE("GPL");

DEFINE_PER_CPU(int, counter);

static int __int test_hello_init(void)
{
    int num_cpus = num_online_cpus();
    int i = 0;
    int val; 
    
    pr_info("Number of cpus available:%d\n", num_cpus);
    for (i = 0; i < num_cpus; i++) {
        int value = per_cpu(counter, i);
	pr_info("Value of counter is %d at Processor: %d\n", value, i);
    }
     
    get_cpu_var(counter) = 10;   /* disabling preemption */
    pr_info("Printing counter value of all processor after updateing current processor: %d\n", smp_processor_id());
    put_cpu_var(counter);        /* enabling preemption */
    
    for (i = 0; i< num_cpus; i++) {
        int value = per_cpu(counter, i);
        pr_info("Value of counter is %d at Processor: %d\n", value, i);
    }
    
    return -1;
}

...

```

Example of `for_each_online_cpu()`:

```
... 
static DEFINE_PER_CPU (long, percpuvar) = 5;

static int __int test_hello_init(void)
{
    int i = 0;
    
    for_each_online_cpu(i) {
        int value = per_cpu(counter, i);
	pr_info("Value of counter is %d at Processor: %d\n", value, i);
    }

    get_cpu_var(counter) = 10;
    pr_info("Printing counter value fo all processors after udpateing current processor: %d\n", smp_processor_id());
    put_cpu_var(counter);
    
    for_each_online_cpu(i) {
        int value = per_cpu(counter, i);
	pr_info("Value of counter is %d at Processor: %d\n", value, i);
    }

    return -1;
}
...
```

### Per-CPU data at runtime

Dynaically allocated per-CPU variables are also possible:

```
void *alloc_percpu(type); /* a macro */
void *__alloc_percpu(size_t size, size_t align);
void free_peercpu(const void *);
```

The `alloc_percpu()` macro allocates one instance of an object of the given type for every processor on the system.

It is a wrapper around `__alloc_percpu()`, which takes the actual number of tytes to allocate as parameter and the number of bytes on which to algin the allocation.

```
struct abc = alloc_percpu(struct abc);
```
is the same as:
```
struct abc = __alloc_percpu(sizeof (struct abc), __alignof__ (struct abc)); 
```

A call to `alloc_percpu()` or `__alloc_percpu()` returns a pinter, which is used to indirectly reference the dynamically create pre-CPU data. 

A corresponding call to `free_percpu()` frees the given data on all processors. 

 - `get_cpu_var(ptr)` - returns a void pointer to this processos's copy of ptr
 - `put_cpu_var(ptr)` - done, enable kernel preemptin. 

Example: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/percpu.h>

MODULE_LICENSE("GPL");

static int *dyanmic_counter; 

static int __init test_hello_init(void)
{
    int cpu = get_cpu();                             /* disable preemtion */
    int i;
    dynamic_counter = alloc_percpu(int);             /* dynamic memory allocation */
    pr_info("cpu: %d\n", cpu);
    *per_cpu_ptr(dynamic_counter, cpu) = 1000; 
    put_cpu();                                       /* enable back preemtion */
    for (i = 0; i < num_online_cpus(); i++)
        pr_info("cpu:%d\tcounter:%d\n", i, *per_cpu_ptr(dynamic_counter, i));
    free_percpu(dynamic_counter);                    /* release the dynamic memory */
    return 0;
}

static void __exit test_hell_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

/* sample output
cpu: 3
cpu: 0    counter:0
cpu: 1    counter:0
cpu: 2    counter:0
cpu: 3    counter:1000
cpu: 4    counter:0
cpu: 5    counter:0
*/
```

### Issues with per CPU variables

The problem with per-CPU variables are the interrruts. Whle per-CPU variables provide protection againsts concurrent accesses from serveral CPUs, they don't provide protection againsts accesses from asynchronous functions (interrupt handlers and deferrable funtions). In those cases, additional synchroinzation primitives are required. 

## ATOMIC OPERATIONS

Several assemply language instruction are of the tupe RUW: Read-Update-Write. So they access a given memory location twice: the firs time to read the old value, and the second time to write a new value. 

Suppose that two kernel control paths running on two CPUs try to "read-update-write" the same meory location at the same time, by executing non-atomic operatoins. 

At first, both CPUs try to read the same lcoatin, but the mrmory arbiter (the hardware circuit that serializes accesses to the RAM chips) steps in to grant access to one of them and delay the other.

 However, when the first read operation has completed, the delayed CPU reads exactly the same (old) value from the memory location. 
 
  Both CPUs then try to write the same (new) value to the memory location; again, the bus memory access is serialized by the memory arbiter, and eventually both write oeprations succed. 
  
  However, the global result is incorrct because both CPUs wirte the same (new) value. Ths, the two inter-leaving "read-update-write" operaton act as a sinbgle one.


```
code: i = i+1;

routine 1           routine 2
read i = 0   
                    read i = 0
increment i+1 = 1
                    imcrement i+1 = 1
write 1 
                    write 1 // this overwrites the resulti
```

This code section is known as a **critical section**


### Atomic operations

The easiest way to prevent race conditions due to "read-modify-write" instructions is by ensuring that such operations are atomic at the chip level.

Every such operation must be executed in a single instruction without being interrupted in the middle and avoiding accesses to the same memory location by other CPUs. 

Most CPUs instruction set architectures define instruction opcodes that can perform atomic read-modify-write operations on a memory location. 

In general, special lock instructions are used to prevent the other processors in the system from working until the current processor has completed the next action. 

When you write C code, you cannot guarantee that the compiler will use an atomic instruction for an operation like `a = a +1` or even for `a++`.

Thus, the Linux kernel provides a sepcial atomic_t type (an atomically accessible counter) and some special functions and macros that act on atomic_t variables.

```
Header file: <asm/atomic.h>
typedef struct { volatile int counter; } atomic_t; // take into account the keyworkd "volatile"
```

Because the atomic data types are ultimately implemented with normal C types, the kernel encapsulates standard variables in a structure that can no longer be processes with normal operatos such as ++. 

What happens to atomic variables when the kernel is compilded with SMP support? It works the same way as for normal variables (only atomic_t encapsulation is observed) because there is no interfence from other processors. 

To initialize an use an atomic variable: 

```
atomic_t i; //define i
atomic_t i = ATOMIC_INIT(1); // define and initialize i

void atomic_int(atomic_t *i); // add 1 to *i
void atomic_dec(atomic_t *i); // substract 1 from *i

void atomic_set(atomic_t *i, int j); // atomically set counter i to value specified in j
int atomic_read(atomic_t *i); // read value of the atomic counter i

void atomic_add(int val, atomic_t *i); // atomic add val to atomic counter i
void atomic_sub(int val, atomic_t *i); // atomic substract val from counter i
```

Example: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/atomic.h>

atomic_t val = ATOMIC_INIT(0);
MODULE_LICENSE("GPL");

static int test_hello_init(void)
{
    pr_info("%s: Value after init: %d\n", __func__, atomic_read(&val)); 
    atomic_set(&val, 4);
    pr_info("%s: Value after setting to 4: %d\n", __func__, atomic_read(&val)); 
    atomic_dec("%s: value after decrementing: %d\n", __func__, atomic_read(&val));
    atomic_inc(&val);
    pr_info("%s: VAlue after incrementing:%d\n", __func__, atomic_read(&val)); 
    atomic_add(3, &val);
    pr_info("%s: value after adding 3: %d\n", __func__, atomic_read(&val));
    atomic_sub(2, &val);
    pr_info("%s: value after substracting 2: %d\n", __func__, atomic_read(&val));
    return -1;
}

static_void test_hello_exit(void)
{
    pr_info("%s: in exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);

```

### Atomics API

reference: https://www.cs.bham.ac.uk/~exr/lectures/systems/08_09/docs/kernelAPI/

```
atomic_read --  read atomic variable
atomic_set --  set atomic variable
atomic_add --  add integer to atomic variable
atomic_sub --  subtract the atomic variable
atomic_sub_and_test --  subtract value from variable and test result
atomic_inc --  increment atomic variable
atomic_dec --  decrement atomic variable
atomic_dec_and_test --  decrement and test
atomic_inc_and_test --  increment and test
atomic_add_negative --  add and test if negative
get_unaligned --  get value from possibly mis-aligned location
put_unaligned --  put value to a possibly mis-aligned location
```

### Common uses of atomic operations

The most common use of atomic integer operations is to implement counters. Proctecting a sole counter with a complex locking scheme is an overkill, so instead developers use `atomic_inc()` and `atomic_dec()` which are much lighter in weight. 

### Atomic operation and tests

These operations are architecture dependant:

```
int atomic_dec_and_test(atomic_t *i); // atomic Substract 1 from *i and return 1 if the result is zero; 0 otherwise

int atomic_int_and_test(atomic_t *i); // atomic Add 1 to *i and return 1 if the result is zero; 0 otherwise

// atomically substract val from *i and return 1 if the  result is zero; otherwise 0
int atomic_sub_and_test(int val, atomic_t *i);

// atomically add val to *i and return 1 if the result is negative; otherwise 0
int atomic_add_negative(int val, atomic_t *i);
```

Example: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/atomic.h>

atomic_t val = ATOMIC_INIT(0);
MODULE_LICENSE("GPL"); 
static int test_hello_init(void)
{
    pr_info("%s: value after init: %d\n", __func__, atomic_rad(&val));
    atomic_set(&val, 4);
    pr_info("%s: value after setting to 4:%d\n", __func__, atomic_read(&val));
    pr_info("%s: atomic_sub_and_test(4), %d\n", __func__, atomic_sub_and_test(4, &val));
    pr_info("%s: atomic_add_negative(-1)): %d\n", __func__, atomic_add_negative(-1, &val));
    pr_info("%s: atomic_inc_and_test:%d\n", __func__,  atomic_inc_and_test(&val));
    pr_info("%s: atomic_inc_and_test:%d\n", __func__, atomic_inc_and_test(&val));
    pr_info("%s: atomic_dec_and_test:%d\n", __func__, atomic_dec_and_test(&val));
    pr_info("%s: atomic_dec_and_test:%d\n", __func__, atomic_dec_and_test(&val));
    
    return -1;
}

static_void test_hello_exit(void)
{
    pr_info("%s: in exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);

```

### Atomic add/substract and return 

```
int atomic_add_return(int val, atomic_t *i); // atomically add val to *i and return the result.
int atomic_sub_return(int val, atomic_t *i); // atomically substract val from *i and return the result.
int atomic_inc_return(atomic_t *i); // atomically increment *i by one and return the result.
int atomic_dec_return(atomic_t *i); // atomically decrement *i by one and retturn the result.
```
Example: 


```
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/atomic.h>

atomic_t val = ATOMIC_INIT(0);
MODULE_LICENSE("GPL");

static int test_hello_init(void)
{
    pr_info("%s: value after init: %d\n", __func__, atomic_read(&val));
    atomic_set(&val, 4);
    pr_info("%s: value after setting to 4: %d\n", __func__, atomic_read(&val));
    pr_info("%s: atomic_add_return(3): %d\n", __func__, atomic_add_return(3, &val));
    pr_info("%s: atomic_sub_return(2): %d\n", __func__, atomic_sub_return(2, &val));
    pr_info("%s: atomic_inc_return: %d\n", __func__, atomic_inc_return(&val));
    pr_info("%s: atomic_dec_return: %d\n", __func__, atomic_dec_return(&val));
    
    return -1;
}

static_void test_hello_exit(void)
{
    pr_info("%s: in exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### More atomic operations

```
int atomic_fetch_add(int val, atomic_t *i); // atomically adds val to i and return pre-addition value at i
int atomic_fetch_sub(int val, atomic_t *v); // atomically substract val from i, and return pre-substract value at i

// reads the value at location i, and checkis if it is equal to old, if true swaps value at v with new and always returns value read at i
int atomic_cmpxchg(atomic_t *i, int old, int new); 

// swaps the oldvalue stored at location in with new, and returns old value i
int atomic_xchg(atomic_t *i, int new);
```

### 64 bits atomic operations

Many processor architectues have 64-bit atomic instructions, but we need atomic64_t in order to support the perf_conunter subsystem.

This adds and implementation of 64-bits atomci operations using hashed spinlocks to provide atomicitiy 

```
typedef struct {
    long long counter;
} atomic64_t;
```

This functions have the naming convention `atomic64_*()`.

### Atomic Bitwise operations

The kernel also provides a faimly of functons that operate at the bit level.

Header file: `<asm/bitops.h>` <br>
These functions operate on generic pointer. There i sno equivalent of the atomic integer atomic_t.

Arguments:
 - Bit number: 0 -31 for 32 bit machines and 0 - 64 for 64-bit machines
 - Pointer with valid address

```
void set_bit(int nr, volatile unsigned long *addr); // atomically set the bit nr in location starting from addr
void clear_bit(int nr, volatile unsigned long *addr); // atomically clear the nr-th bit starting from addr.
void change_bit(int nr, volatile unsigned long *addr); // atomicallyy flip the value of the nr-th bit starting from addr. 

// atomically set the bit nr in the lcoation starting form p, and return old value at the nr-th bit.
int test_and_set_bit(unsigned int nr, volatile unsigend long *p);

// atomically clear the bit in nr in the location starting from p, and return old value at the nr-th bit.
int test_and_clear_bit(unsigned int nr, volatile unsigned long *p);

// atomically flip the bit nr in the lcoation starting from p, and return old value at the nr-th bit.
int test_and_change_bit(unsigned int nr, volatile unsigned long *p);

```

### Non atomic Bitwise operations

The kernel also provides non-atomic versions of all the bitwise functions. 

They behave indentically to their atomic siblings, except they do not guarantee atomicity, and their names are prefixed with double undersores. 

For example, the non-atomic form of `test_bit()` is `__test_bit()`

If you do not require atomicity (say, for example, because a lock already protects your dta), these variants of the bitwise functions might be faster. 


## SPINLOCKS

references:
 - https://www.makelinux.net/ldd3/?u=chp-5-sect-5.shtml
 - https://0xax.gitbooks.io/linux-insides/content/SyncPrim/linux-sync-1.html <br>
 - http://gauss.ececs.uc.edu/Courses/c4029/videos/05Feb16_4029.ogv <br>
 - https://www.kernel.org/doc/html/latest/locking/locktypes.html <br>
 - https://www.kernel.org/doc/html/latest/locking/spinlocks.html#lesson-1-spin-locks <br>
 - https://docs.kernel.org/locking/spinlocks.html#lesson-1-spin-locks <br>
 - https://lwn.net/Kernel/Index/#Spinlocks <br>
 - https://embetronicx.com/tutorials/linux/device-drivers/spinlock-in-linux-kernel-1/ <br>

The problem with atomic operations, is that they can only work with CPU words and double words size. Atomics cannot work with shared data structures of custom size. 

In real life, critical regions can be mode that one line. And these code paths should execute atomically to avoid race conditions. To ensure atomicity of suche code blocks, **locks** are used. 

### Spinlocks

The most common lock in the Linux kernel is the spinlock.

Spinlocks are used to protect **short code sections** that comprise just a few C statements and are therefore quickly executed and exited. 

A spin lock is a lock that can be held by at most one thread of execution, that also means at most 1 CPU.

An spin-lock is a low-level sycnhronization mechanism which in simple words, is a variable that represents two states: 
- adquired
- released

When the thread tries to adquire the lock wich is already adquired, the thread loops/spins waiting for the lock to become available. 

When the thread tries to adcquire lock which is available (released), the thread acquires the lock and continues. 

#### Why use spin-locks instead of atomics

Atomics only work for variables of one or two words. But in cases where the critical section is some lines of code, atomics don't solve
the issue. For that spin-locks are used.

### Spin-lock API

To use header locks, the header file needed is: `<linux/spinlock.h>`, and the data structure is: `spinlock_t`.

```
DEFINE_SPINLOCK(my_lock);  // this is equivalent to: spinlock_t my_lock = __SPIN_LOCK_UNLOCED(my_lock);

From <linux/spinlock_types.h>
#define DEFINE_SPINLOCK(x) spinlock_t x = __SPIN_LOCK_UNLOCKED(x)

// to lock a spin lock
void spin_unlock(spinlock_t *lock);

// to unlock a spin lock
void spin_unlock(spinlock_t *lock);

// to initialize a spin lock at run time
void spin_lock_init(spinlock_t *lock);
```

Example: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");

DEFINE_SPINLOCK(my_lock);

static int __init test_hello_init(void)
{
    spin_lock(&my_lock);
    pr_info("Starting critical region\n");
    pr_info("Ending critical region\n");
    spin_unlock(&my_lock);
    return -1
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

To initialize a spin lock at run time use: `void spin_lock_init(spinlock_t *lock);`


```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

spinlock_t *my_lock;

static int __Int test_hello_init(void)
{
    my_lock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
    spin_lock_init(my_lock);    // run time initializing the spin lock.
    spin_lock(my_lock);
    pr_info("Starting critical region\n");
    pr_info("Ending critical region\n");
    spin_unlock(&my_lock);
    kfree(my_Lock)
    return -1
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

Example of two kernel threads: a write thread and a read thread.

```
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/sched.h>

unsigned int counter; /* shared data: */
DEFINE_SPINLOCK(counter_lock);
struct task_struct *read_thread, *write_thread;

static int writer_function(void *data)
{
	while(!kthread_should_stop()) {
		spin_lock(&counter_lock);    // start of the critical section
		counter++;
		spin_unlock(&counter_lock);  // end of critical section
		msleep(500);
	}
	do_exit(0);
	//  do_exit() releases all the logical and physical resources which may remain allocated by 
	// the process to end. Then do_exit() calls schedule() which switchs to a new task to run.
	// it is defined at: https://elixir.bootlin.com/linux/v6.3-rc6/source/kernel/exit.c#L805
}

static int read_function(void *data)
{
	while(!kthread_should_stop()) {
		spin_lock(&counter_lock);    // start of the critical section
		pr_info("counter: %d\n", counter);
		spin_unlock(&counter_lock);  // end of critical section
		msleep(500);
	}
	do_exit(0);
}

static int __init my_mod_init(void)
{
	pr_info("Entering module.\n");
	counter = 0;

	read_thread = kthread_run(read_function, NULL, "read-thread");
	write_thread = kthread_run(writer_function, NULL, "write-thread");

	return 0;
}

static void __exit my_mod_exit(void)
{
	kthread_stop(read_thread);
	kthread_stop(write_thread);
	pr_info("Exiting module.\n");
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");

```

**Watch Out!** in case you try to adquire an spin lock aready adquired by you, you will spin waiting for youself to release the lock, like you are already spinning, thuse you are being efectively in a deadlock. Example, try the following: 


```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");

DEFINE_SPINLOCK(my_lock);

static int __Int test_hello_init(void)
{
    spin_lock(&my_lock);
    pr_info("Starting critical region\n");
    spin_lock(&my_lock);   // YOU WILL SPIN FOREVER! DEADLOCK!!
    pr_info("Ending critical region\n");
    spin_unlock(&my_lock);
    return -1
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

Example of implementing a busyloop using spinlock in a char driver

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

DEFINE_SPINLOCK(my_lock);

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s Trying to acquire spinlock on processor:%d\n", __func__, smp_processor_id());
	spin_lock(&my_lock);
	pr_info("%s: Spinlock Acquired on processor:%d\n", __func__, smp_processor_id());
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	pr_info("%s: Spinlock Released on processor:%d\n", __func__, smp_processor_id());
	spin_unlock(&my_lock);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int test_hello_init(void)
{
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));

		device = device_create(class, NULL, devicenumber, NULL, device_name);
		cdev_init(&mycdev, &device_fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devicenumber, count);

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	device_destroy(class, devicenumber);
        class_destroy(class);
	cdev_del(&mycdev);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);

```

To test it, remember to add permissions to the chardev `sudo chmod 666 /dev/msg`

#### spin_trylock

There is also other call: `int spin_trylock(spinloc_t *lock)`, it returns zero, in case the lock is not available, in case it is available it will adquire it, it returns no zero. 

#### Usage of a spinlock when the resource is shared between a process and an interrupt context

In case a process is executing and it takes a log, and then there is an interrupt, and the interrupt handler, also wants to adquire that lock, then the
interrupt handler will start to spin in the loop, and the process will not be able to continue and release the spin-lock, so it is efectively a dead-lock situation.

The solution to this, is to disable interrupts before adquiring the spin-lock, and enable back the interrupts after releasing the spinlock. 

The functions to do that are:

```
DEFINE_SPINLOCK(mylock);
unsigned long flags;

spin_lock_irqsave(&mylock, flags);
/* critical section */
spin_unlock_irqrestore(&mylock, flags);
```

The flags are needed, because if the interruptions were already disabled before the spinlock, when the spinlock is released, we would restore the interruptins back, when that is not desired. For that the flags, are used to store the state of the interrupts.

In case it is known that the interrupts are enabled, thern there is not need to restore back their status, and then, it can be used: 

```
DEFINE_SPINLOCK(mylock);
unsigned long flags;

spin_lock_irq(&mylock);
/* critical section */
spin_unlock_irq(&mylock);
```

#### Is the kernel preemption disabled when spinlock is acquired?

When the kernel adquires a spin-lock, preepmtion is disabled on the current processor. Otherwise, if the kernel adquires a spin-lock, and it is preempted by a task that also wants that spinlock, then the task will never be able to adquire it, and it would be a dead-lock situation. 

There are methods to lock/unlock kernel preemption.

#### Relevant points to consider when using a spin-lock

 - If a spin-lock is adquired but not released, the system will be rendered unusable. All processors, including the one that adquired the spinlock, will sooner or later arrive at a point where they must enter the critical section. So the CPUs will go in an endless loop, waiting the spin-lock to be released, but the system is in a dead-lock state.

 - Spin-lock should not be adquired for long time, because during that period, all CPUs waiting for the lock to be released are no longer available for other productive tasks. 

 - Code that is protected by spin-locks, must not go so sleep, or use functions that can go to sleep, i.e.: kmalloc. Remember, when the spin-lock is adquired, preemption is disabled on that CPU, but another CPU can try to continue that thread, and then adquire the lock which is already taken, causing then a dead-lock. 

#### spin-locks in single processor systems

There is two situations: 
 - When CONFIG_PREEMPT is not set, that is the kernel preemption is disabled: so spin-lock are deined as `nop` operations, because critical sections cannot be enterd by several CPUSs at the same time. 
 - When CONFIG_PREEMTP is set, then the preemption is disabled when the spin-lock is adquired, and enabled back when the spin-lock is released.

#### Implementation of the spin-lock

reference: https://0xax.gitbooks.io/linux-insides/content/SyncPrim/linux-sync-1.html <br>

A spinlock is a mutual exclusiion device that can have two states: locked & unlocked

It is usually implemented as a single bit. 

The "test and set" operaton must be don in an atomic operaton, so only one thread can obtain the lock, evein if several are spinning in a given time. 

Spinlocks are build on top of hardware-specific atomic instructions. The actual implemetation, thus, changes for every processor architecture. 



## Semaphores

Semaphores in Linux are like sleeping locks.

reference: https://sites.cs.ucsb.edu/~rich/class/cs170/notes/Semaphores/index.html

#### What happens when the semaphore lock is unavailable?

The semaphore places the task onto a wait queue and puts the task to sleep.

The processor is then free to execute other code. 

#### What happens after the semaphore becomes available?

One of the tasks on the wait queue is awakened so that it can then acquire the semaphore. 


### Types of Semaphore

Spin locks allow only one task to hold the lock at a time.

With semaphores, a number of tasks to hold the lock at a time can be specified while initializing/declaring semaphore. This value is called as usage count or simply count.


- Count = 1	--> 	Binary Semaphore, used for mutual exclusion
- Count > 1	-->	Counting Semaphore


Counting semaphores are not used to enforce mutual exclusion because they enable multiple threads of execution in the critical region at once. Couting semaphores have other use-cases, but are not used very much in the kernel code. 

### Semaphore's implementation

It is in `kernel/locking/semaphore.c`

Header file: `<linux/semaphore.h>`

Data structure: `struct semaphore`

```
struct semaphore {
    raw_spinlock_t     lock;
    unsigned int       count;
    struct list_head   wait_list;
}
```

- lock: spinlock for a semaphore data protection
- count: amout available resources
- wait_list: list of processes which are waiting to adquire a lock.

### Semaphore's API


#### Initialization:

- Dynamic: `void sema_init(struct semaphore *sem, int val); // where val is the initial value to assign to the semaphore`
- Static: <br>
```
DEFINE SEMAPHORE(name)

#define DEFINE_SEMAPHORE(name) \
   struct semaphore name = __SEMAPHORE_INITIALIZER(name, 1)
```

- P() 	--> down: decrements the value of the semaphore
- V()   --> up: increments the value of the semaphore


#### Lock and release

```
void down(struct semaphore *sem);
void up(struct semaphore *sem);
```

- `down()` decrements the counter by 1, if `count >= 0` then the task can enter the critical section. Otherwise the task is placed on the wait list and goes to sleep.
- `up()` increments the counter by 1, and releases the critical section.


#### Other calls

```
void up(struct semaphore *sem);
void down(struct semaphore *sem);
int down_interruptible(struct semaphore *sem);
int down_timeout(struct semaphore *sem, long jiffies);
```
- `down()` places the calling process in the `TASK_UNINTERRUMPIBLE` state when it sleeps.
- `down_interrumptible()` places the calling process to sleep in the `TASK_INTERRUMPTIBLE` state. If the task receives a signal while waiting for the semaphore, it is awakaned and down interruptible() returns `-EINTR`. You can check the status of the task with `ps`.
- `down_trylock()` If the semaphore is not available at the time of the call, `down_trylock` returns with a nonzero return value.
- `down_timeout()` Attemps to adquire the semaphore. If no more tasks are allowed the semaphore, calling this function will put the task to sleep. If the semaphore is not released within the specified number of jiffies, this function returns `-ETIME`. It returns 0 if the semaphore is adquired. 


### Example 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct semaphore *mysem;

static int __init test_hello_init(void)
{
    mysem = kmalloc(sizeof(mysem), GFP_KERNEL);
    sema_init(mysem, 4);  // the inital value is 4, so this is
                          // a conting semaphore, and it cannot 
			  // be used for mutual exclusion. 
			  // If the initial value was 1, then it
			  // would be a binary semaphore and could
			  // be used for mutual exclusion.
    pr_info("semaphore count:%d\n", mysem->count);
    down(mysem);
    pr_info("semaphore count:%d\n", mysem->count);
    pr_info("Starting critical region\n");
    pr_info("Ending critical region\n");
    up(mysem);
    pr_info("semaphore count:%d\n", mysem->count);
    return -1;  // this will make fail the module installation
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

`down()` decrements the counter by 1, if `count >= 0` then the task can enter the critical section. Otherwise the task is placed on the wait list and goes to sleep.

`up()` increments the counter by 1, and releases the critical section.


## Mutexes

references:
- https://lwn.net/Articles/164802/
- https://docs.kernel.org/locking/mutex-design.html

Almost all the semaphores found in the Linux kernel are used for mutual exclusion by count of 1 (binary semaphores).

Using semaphores for mutual exclusion is overhead, so kernel provides a new interface: mutex (short for 'mutual exclusion').

The mutex subsystem checks and enforces the following rules:

- Only one task can hold the mutex at a time
- Whoever locked a mutex must unlock it. That is it is not possible to lock a mutex in a context, and unlock it in another context.
- Recursive locks and unlocks are not allowed.
- Process cannot exit while holding a mutex. 
- Mutex cannot be adquired from an interrupt handler. 

### Differences between mutexes and semaphores

The ownership concept, only applies to mutexes, not to semaphores


| Requirement |  Recommended lock|
| -- | -- | 
| Long overhead locking | spinlock |
| short lock hold time | spinlock |
| long lock hold time | mutex |
| need to lock from interrumpible context | spinlock |
| need to sleep while holding lock | mutex | 
| ownership | mutex | 

Unless the strict semantics of mutexes are unsuitable and/or the critical region prevents the lock from being shared, always prefer them to any other locking primitive.

### What happens when a process tries to adquire a mutex lock? 

When adquiring a mutex, there are three possible paths:
 - fast path
 - mid path
 - slow path

The path to be taken depends on the state of mutex:

reference: https://docs.kernel.org/locking/mutex-design.html

#### Fast path
 Taken when no process has adquired the mutex
 
#### Mid path (optimistic spinning)
 When the mutex is not available, it tries to go for mid path. Also called as optimistic spinning.
 
 This path will only be executed if there are no other processes ready to run having high priority 
 and the owner of mutex is **running**.
 
 In this path, tries to spin using MCS lock hoping the owner will release the lock soon. 
 
 Avoid expensive context switch. 
 
 #### Slow path
 
 Last resort. This path acts as a semaphore lock. If the lock is unable to be adquired by the process, 
 the task is added to wait queue. It sleeps until woken up by the unlock path. 
 
 In this path, tries to spin using MCS lock (proposed by Mellor-Crummey and Scott)  hoping the owner will release the lock soon. 
 
 
 ### Mutex implementation

 - reference: https://www.kernel.org/doc/html/latest/locking/mutex-design.html
 
 Mutexes are represented by `struct mutex`, defined in `include/linux/mutex.h` and implemented in `kernel/locking/mutex.c`. These locks use an atomic variable (->owner) to keep track of the lock state during its lifetime. Field owner actually contains `struct task_struct *` to the current lock owner and it is therefore `NULL` if not currently owned.

file: kernel/locking/mutex.c

header file: <linux/mutex.h>

data structure: struct_mutex

```
strutc mutex {
    atomic_long_t    owner;       // using for both, holding lock state, and reference to owner (task_struct) who adquired it.
    spinlock_t       wait_lock;   // used for atomic updating wait_list
    struct list_head wait_list;
}
```

### Mutex API


Statically define the mutex:
```
DEFINE_MUTEX(name);
```

Dynamically initialize the mutex:
```
mutex_init(mutex);
```

Acquire the mutex, uninterruptible:
```
void mutex_lock(struct mutex *lock);
void mutex_lock_nested(struct mutex *lock, unsigned int subclass);
int  mutex_trylock(struct mutex *lock);
```
the `mutex_trylock()` tryes to adquire the  mutex, and returns `1` if successful, or `0` otherwise. 



Acquire the mutex, interruptible:
```
int mutex_lock_interruptible_nested(struct mutex *lock,
                                    unsigned int subclass);
int mutex_lock_interruptible(struct mutex *lock);
```
The `mutex_lock_interruptible()` places the process in the `TASK_UNINTERRUMPIBLE` state when it sleeps. It returns `0` if the mutex is adquired, or `-EINTR` if the task receives a signal while waiting for the mutex. 


```
mutex_lock_killable(struct mutex *lock)
```
`mutex_lock_killable()` places the calling process in the `TASK_KILLABLE` state when it sleeps, only fatal signal can interrupt it. It returns `0` if the mutex is adquired, or `-EINTR` when the task receives a fatal signal while waiting for unlocking the mutex. 


Acquire the mutex, interruptible, if dec to 0:

```
int atomic_dec_and_mutex_lock(atomic_t *cnt, struct mutex *lock);
```

Unlock the mutex:

```
void mutex_unlock(struct mutex *lock);
```

Test if the mutex is taken:

```
int mutex_is_locked(struct mutex *lock); // returns 1 if locked, 0 if unlocked.
```
### Can you sleep in mutexes?

Yes you can sleep in mutexes, where you cannot sleep or call functions that may sleep is in **spinlocks**.

### Mutex example

reference: https://sysprog21.github.io/lkmpg/#mutex

```
/* 
 * example_mutex.c 
 */ 
#include <linux/module.h> 
#include <linux/mutex.h> 
#include <linux/printk.h> 
 
static DEFINE_MUTEX(mymutex); 
 
static int __init example_mutex_init(void) 
{ 
    int ret; 
 
    pr_info("example_mutex init\n"); 
 
    ret = mutex_trylock(&mymutex); 
    if (ret != 0) { 
        pr_info("mutex is locked\n"); 
 
        if (mutex_is_locked(&mymutex) == 0) 
            pr_info("The mutex failed to lock!\n"); 
 
        mutex_unlock(&mymutex); 
        pr_info("mutex is unlocked\n"); 
    } else 
        pr_info("Failed to lock\n"); 
 
    return 0; 
} 
 
static void __exit example_mutex_exit(void) 
{ 
    pr_info("example_mutex exit\n"); 
} 
 
module_init(example_mutex_init); 
module_exit(example_mutex_exit); 
 
MODULE_DESCRIPTION("Mutex example"); 
MODULE_LICENSE("GPL");
```

## Read Write Locks

references:
- https://docs.kernel.org/locking/spinlocks.html#lesson-2-reader-writer-spinlocks


The synchronization techniques discussed till now have one drawback: they don't differenciate between situations in 
which: 
 - data structures are simply read.
 - data structures are actively updated. 

- **Read** (an operation which doesn't change the value of the variable) access can be provided to multiple tasks at concurrent time.
- **Write** access must only be provided to one task at a time. 

The kernel provides additional semaphore and spinlock versions for the previous requirement, as the read operation is perfomed
more often that the write operation. 

1.- read/write spinlocks (the writing is exclusive, only one task at a time)
2.- read/write semaphores (the writing is exclusive, only one task at a time)

Those are also known as shared/exclusive or concurrent/exclusive locks

- shared --> readers
- exclusive --> writers

### read write locks API

Data structure: `struct rwlock_t`

Header file: `<linux/rwlock_types.h>`

Initialization:

- static: `DEFINE_RWLOCK(x)`
- dynamic: `rwlock_init(lock)`

lock/unlock:
 
 - readers:

```
read_lock(&my_rwlock);
/** critical section (read only)**/
read_unlock((&my_rwlock);
```

 - writers:

```
write_lock(&my_rwlock);
/** critical section (read and write)**/
write_unlock(&my_rwlock);
```

### What happens when read lock is called and after it write lock is called?

For example the next code snippet: 

```
read_lock(&mylock);
write_lock(&mylock);
```

Executing this code will cause a deadlock, as write_lock() will spin until all readers have released the lock.

### Recursive read locks

For the same thread, is safe to recursively obtain the same read lock.

### What happens when writer is waiting and reader arrives?

What happens when a read_lock is held and a writer is waiting for exclusive access and a new reader arrives?

Who is given a chance? 

whoever comes first it is served.

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwlock_types.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

DEFINE_RWLOCK(mylock);
static struct task_struct *thread1, *thread2, *thread3, *thread4;

int counter = 0;

static int write_threadfn(void *arg)
{
	pr_info("processor:%d trying to acquire write lock\n", smp_processor_id());
	write_lock(&mylock);
	pr_info("processor:%d acquired write lock\n", smp_processor_id());
	counter++;
	mdelay(3000);
	write_unlock(&mylock);
	pr_info("processor%d released write lock\n", smp_processor_id());
	return 0;
}

static int read_threadfn(void *arg)
{
	pr_info("processor:%d trying to acquire read lock\n", smp_processor_id());
	read_lock(&mylock);
	pr_info("processor:%d acquired read lock\n", smp_processor_id());
	pr_info("processor%d\t counter:%d\n", smp_processor_id(), counter);
	mdelay(2000);
	read_unlock(&mylock);
	pr_info("processor:%d releasing read lock\n", smp_processor_id());
	return 0;
}

static int __init test_hello_init(void)
{
	thread1 = kthread_run(read_threadfn, NULL, "thread1");
	thread2 = kthread_run(write_threadfn, NULL, "thread2");
	thread3 = kthread_run(write_threadfn, NULL, "thread3");
	thread4 = kthread_run(read_threadfn, NULL, "thread4");
	return 0;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```


## Semaphores RWLocks

Header file: <linux/rwsem.h>

Data structure: struct rw_semaphore

Implementation: kernel/locking/rwsem.c

## Semaphores RWLocks API

### Initialization:

Static: `DECLARE_RWSEM(name)`

Dynamic: `init_rwsem(struct rw_semaphore *sem)`

All reader-writer semaphores are mutexes that is, their usage count is 1 (binary semaphores, oposed to counting semaphores).
They enforce mutual exclusion only for writers, not readers. 

Example of initialization: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwsem.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct rw_semaphore *mysem;

static int __init test_hello_init(void)
{
    mysem = kmalloc(sizeof(mysem), GFP_KERNEL);
    init_rwsem(mysem);
    pr_info("count:%ld\n", atomic_long_read(&mysem->count));
    kfree(mysem);
    return -1;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### Lock/Unlock

Readers: 

```
void down_read(struct rw_semaphore *sem);
   // critical section
void up_read(struct rw_semaphore *sem);
```

Writers:


```
void down_write(struct rw_semaphore *sem);
  // critical section
void up_write(struct rw_semaphore *sem);
```

Note: down_read/write may put the calling process into an uninterruptible sleep.


```
int down_read_trylock(struct rw_semaphore *sem);
int down_write_trylock(struct rw_semaphore *sem);
```
**Note**: Both return 1 if the lock is successfully acquired and 0 if it is currently contended. This is the opposite of normal semaphore behavior!



Reader-writer semaphores have a unique method which is not present in a reader-writer spinlocks
```struct rw_semaphore *sem
void downgrade_write(struct rw_semaphore *sem)
```
This function atomically converts an aquired write lock to a read lock.

Where can this be used? Used in situations where write lock is needed for a quick change, followed by a longer period of read-only access. 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwsem.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

DECLARE_RWSEM(mylock);
static struct task_struct *thread1, *thread2, *thread3;

int counter = 0;

static int write_threadfn(void *arg)
{
	while(!kthread_should_stop())
	{
		pr_info("processor:%d trying to acquire write lock\n", smp_processor_id());
		down_write(&mylock);
		pr_info("processor:%d acquired write lock\n", smp_processor_id());
		counter++;
		msleep(5000);
		up_write(&mylock);
		pr_info("processor%d released write lock\n", smp_processor_id());
	}
	return 0;
}

static int read_threadfn(void *arg)
{
	while(!kthread_should_stop())
	{
		pr_info("processor:%d trying to acquire read lock\n", smp_processor_id());
		down_read(&mylock);
		pr_info("processor:%d acquired read lock\n", smp_processor_id());
		pr_info("processor%d\t counter:%d\n", smp_processor_id(), counter);
		msleep(2000);
		up_read(&mylock);
		pr_info("processor:%d releasing read lock\n", smp_processor_id());
	}
	return 0;
}

static int __init test_hello_init(void)
{
    thread1 = kthread_run(read_threadfn, NULL, "thread1");
    thread2 = kthread_run(read_threadfn, NULL, "thread2");
    thread3 = kthread_run(write_threadfn, NULL, "thread2");

    return 0;
}

static void __exit test_hello_exit(void)
{
	kthread_stop(thread1);
	kthread_stop(thread2);
	kthread_stop(thread3);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```


## Sequential locks

reference: https://0xax.gitbooks.io/linux-insides/content/SyncPrim/linux-sync-6.html <br>

Read-write lock is a special lock mechanism which allows concurrent access for read-only operations. An exclusive lock is needed for writing or modifing data. 
A writer process can't adquiere a lock as long as at least one reader process which acquired a lock holds it. This may lead to a problem called starvation, where
writer process may sometimes need to wait long time for the lock. 

A lot of effort has been put into developing synchronization primitives that avoid locks.Lock free and wait free synchronization plays a major role in RTOS, 
where time guarantees must be given. 

Two synchronization mechanisms were added in 2.6 kernel to totally remove locking on the reader side:

- sequence lock
- RCU (read copy update)

## Seqlocks/sequence locks

reference: https://0xax.gitbooks.io/linux-insides/content/SyncPrim/linux-sync-6.html <br>
reference: Driver porting: mutual exclusion with seqlocks: https://lwn.net/Articles/22818/ <br>
reference: The seqcount latch lock type: https://lwn.net/Articles/831540/ <br>

Where added in linux 2.6, to provide a fast and lock-free access to shared resources. 

The difference between a reader-writer lock and a sequence lock , is that the writer lock is given a higher priority when compared to reader lock. And the writer lock 
is allowed to modify the shared data, even when they are reader in critical section. 

The reader locks are in charge to check if the read valid data. If a write access took place while the data was readed, the data is invalid and has to be 
readed again. Identification of write accesses is realized with a counter. 

When a writer lock is already in a critical section and another writer lock arrives, the writer-lock uses an spin-lock for mutual exclusion hence will not 
interfere with the other writer. The lock is present always for writers, but not for readers. 

### When to use a sequence lock 

- When there is a small amount of data to be protected
- the data has a lot of readers or is frequently accessed
- the data has few writers
- It is important that writers not to be starved for access.

### How sequence locks work 

Sequence locks internaly use a sequence counter (an integer type), and a spin-lock.

Data structure: `seqlock_t`

Header file: linux/seqlock.h

```
typedef struct seqcount {
	unsigned sequence;
} seqcount_t;

typedef struct {
	struct seqcount_t seqcount; 	// sequence counter
	spinlock_t lock;		// lock to atomic update in case of writers
} seqlock_t;
```

### sequence lock API

Static : `DEFINE_SEQLOCK(x)`

Dinamic : `seqlock_init()` 


```
static inline unsigned read_seqbegin(const seqlock_t *sl);
static inline unsigned read_seqretry(const seqlock_t *sl, unsigned start);
static inline void write_seqlock(seqlock_t *sl);
static inline void write_sequnlock(seqlock_t *sl);
static inline void write_seqlock_irq(seqlock_t *sl);
static inline void write_sequnlock_irq(seqlock_t *sl);
static inline void read_seqlock_excl(seqlock_t *sl)
static inline void read_sequnlock_excl(seqlock_t *sl)
// for use in interrupts:
write_seqlock_irq(seqlock_t *sl);
write_sequnlock_irq(seqlock_t *sl);
write_seqlock_irqsave(seqlock_t *sl);
write_seqlock_irqrestore(seqlock_t *sl, unsigned long flags);
```

#### Write operation

Writers must take out exclusive access before making changes to the protected data.

```
write_seqlock(&mylock);
/* make changes here*/
write_sequnlock(&mylock);
```

- `write_seqlock(&mylock); ` locks the spinlock and increments the sequence number. 
- `write_sequnlock(&mylock);` increments the sequence number again, then releases the spinlock.

#### Read operation

In the read operation no locking is required when you are using trying to read. 

Each reader must read the sequence number twice.
 - 1. before reading the data
 - 2. after reading the data
  
And verify wether they both are the same or not. 

- When there was no writer during the read operation: then the value of the sequence counter will be the same. 
- When there was writer during the write operation: the value of the sequence counter will not be the same. The
important point here is that while the writer is operating, the sequence number would be odd. 

```
unsigned int seq;

do {
	seq = read_seqbegin(&the_lock);
	/* Make a copy of the data of interest */
} while read_seqretry(&the_lock, seq);
```

`read_seqbegin`  -->     Returns the current sequence number.

`read_seqretry`	-->	Returns 1 if the value of seq local variable is odd.


Example:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/seqlock.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

DEFINE_SEQLOCK(mylock);
static struct task_struct *thread1, *thread2, *thread3, *thread4;

int counter = 0;

static int write_threadfn(void *arg)
{
	pr_info("processor:%d trying to acquire write seq lock\n", smp_processor_id());
	write_seqlock(&mylock);
	pr_info("processor:%d acquired write lock\n", smp_processor_id());
	counter++;
	mdelay(7000);
	write_sequnlock(&mylock);
	pr_info("processor%d released write lock\n", smp_processor_id());
	return 0;
}

static int read_threadfn(void *arg)
{
	unsigned int seq;
	int mycounter;
	pr_info("processor:%d starting seqread\n", smp_processor_id());
	do
	{
		seq = read_seqbegin(&mylock);
		mycounter = counter;
		pr_info("processor%d:seq read mycounter:%d\n", smp_processor_id(), mycounter);
	}while (read_seqretry(&mylock, seq));
	pr_info("processor:%d completed seqread\n", smp_processor_id());
	pr_info("processor%d\t counter:%d\n", smp_processor_id(), mycounter);
	return 0;
}

static int __init test_hello_init(void)
{
	thread1 = kthread_run(read_threadfn, NULL, "thread1");
	thread2 = kthread_run(write_threadfn, NULL, "thread2");
	thread3 = kthread_run(read_threadfn, NULL, "thread3");
	thread4 = kthread_run(write_threadfn, NULL, "thread4");
	return 0;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```
#### Is kernel preemption disabled using sequence locks?

Kernel preemption is disabled in writers, because those adquire an lock

For readers there is kernel preemption. 

#### Limitations of sequence locks

Seqlocks cannot be used with pointers. It can be only used for normal data like integers, booleans ...

The reason, is that the pointer can already be freed, in that case dereferencing that pointer will cause an Oops. 



## RCU (Read Copy Update) Locks

- reference: https://lwn.net/Articles/262464/
- reference: https://www.kernel.org/doc/html/latest/RCU/whatisRCU.html
- reference: https://docs.kernel.org/RCU/Design/Requirements/Requirements.html#a-tour-through-rcu-s-requirements
- reference: CS 134 OS—22: RCU—Intro: https://youtu.be/--f3V-JLHt0
- reference: CS 134 OS—22: RCU—Implementation: https://youtu.be/5964Io_BoL0
- reference: what is RCU 2013 Paul McKenny at IISc: https://youtu.be/obDzjElRj9c?list=PLIlI4QbmdBqH9-L1QOq6O5Yxt-YVjRsFZ
- reference: rcu playlist: https://www.youtube.com/watch?v=obDzjElRj9c&list=PLIlI4QbmdBqH9-L1QOq6O5Yxt-YVjRsFZ
- reference: https://www.linuxfoundation.org/webinars/unraveling-rcu-usage-mysteries
- reference: https://www.linuxfoundation.org/webinars/unraveling-rcu-usage-mysteries-additional-use-cases
- reference: https://www.kernel.org/doc/html/next/RCU/whatisRCU.html
- reference: https://www.kernel.org/doc/html/latest/RCU/
- reference: Kernel Recipes 2019 - RCU in 2019: https://youtu.be/bsyXDAouI6E
- reference: RCU's First-Ever CVE, and How I Lived to Tell the Tale: https://youtu.be/hZX1aokdNiY
- reference: So What Has RCU Done Lately?: https://youtu.be/9rNVyyPjoC4
- reference: Changes in RCU over the past few years - Paul E. McKenney: https://youtu.be/JLhDW7yjp60

About memory barriers reference:
 - http://gauss.ececs.uc.edu/Courses/c4029/videos/15Feb16_4029.ogv
 - http://gauss.ececs.uc.edu/Courses/c4029/videos/17Feb16_4029.ogv
 - https://www.kernel.org/doc/Documentation/memory-barriers.txt
 - https://elinux.org/images/a/ab/Bueso.pdf
 - https://mirrors.edge.kernel.org/pub/linux/kernel/people/paulmck/perfbook/perfbook-1c.2023.06.11a.pdf
 - Memory Barriers: a Hardware View for Software Hackers. https://www.puppetmastertrading.com/images/hwViewForSwHackers.pdf

The RCU was added in version 2.5. 

RCU supports concurrency between single updater(producer) and multiple readers (consumers). Often used to update, 
linked lists, which are used all over the kernel. 

RCU is best used in the scenarios: 
 - Many reads
 - Rare writes
 - Write has priority over read.

The problem with read/write locks is that those are expensive as they use atomic increment/decrement operations for the reader count.

The problem with seq locks is that they cannot be used with pointers, and only work with basic types like integer etc ... 

Readers need the retry operation. 

RCU solves those problems, to have a pointer to a shared resource and no locks in the reader. Avoid reader to retry the operation. 

The constrains of RCU:

- Access to shared resource should be mostly read, with very rare write.
- Cannot sleep into region protected by RCU.
- Protected resource should only be accessed via pointer. 

For RCU the read operation, no locking is required.

For RCU the write operation, locking is required.

RCU allows read access to happen concurrently with write updates. 

Note: RCU updaters/writers cannot block readers or force them to retry their accesses like seqlocks. 

The Linux kernel uses many structures that are readed a lot, but rarely written, thus fitting very well for use with RCU:

- Virtual File system: directory entry caches (dentry)
- Networking: Routing tables. Every outgoing packet requires to check routing table to determine which interface should be used. 

#### How RCU works?

As readers do not check if the data they read is consistent (like seqlocks), writer have to apply all their changes with one atomical operation. 

RCU keeps track of all users of the pointers to the shared data structure: 

When a shared data structure is going to change (being written), it:
 - first create a copy of the structure
 - perform the change
 - After all the readers have finished reading on the old copy, pointer is updated.

#### RCU Design

The core of the RCU is based on two primitives:
- RCU read-side critical section: rcu_read_lock/rcu_write_lock
- RCU synchronization section: sycronize_rcu/call_rcu()

Developers can use RCU read-side critical section and RCU synchronization to build data structures 
that allow concurrent reading during updates. 

Header File: <linux/rcupdate.h> 

#### RCU API

- rcu_read_lock()
- rcu_read_unlock()
- synchronize_rcu() / call_rcu()
- rcu_assign_pointer()
- rcu_dereference()

#### RCU Write operation

It is forbidden to assign a new pointer to a pointer that is protected by RCU. Use the function 	
`rcu_assign_pointer()`. 

For example, we have the following structure: 

```
struct my_data
{
	int key;
	int val;
};

struct my_data *global = NULL;
```
To perform the assign operation: 
```
struct my_data *new_ptr;
new ptr = kmalloc(sizeof(struct my_data), GFP_KERNEL);
new_ptr->key = 1;
new_ptr->data = 12345;
rcu_assign_pointer(global, new_ptr);
```

The reason for this weird assignation, is that a CPU/Compiler can try to perform 
optimizations in the assignation (The CPU or compiler may change the order of 
execution of the lines of code).

```
struct my_data *new_ptr;
new ptr = kmalloc(sizeof(struct my_data), GFP_KERNEL);
new_ptr->key = 1;
new_ptr->data = 12345;
global = ptr;
```
The compiler/CPU may try to perform optimizations in any of the last 3 lines. 

To avoid the optimizations to mess the code, memory barriers must be used. 

#### RCU Read operation

It is forbidden to simply de-reference the pointer, protected by RCU region.

You need to use the `rcu_derefernece()` function.

Additionally, the code that de-references the pointer and uses the result needs to be
embraced by calls to `rcu_read_lock()` and `rcu_read_unlock()`.

- `rcu_read_lock()` - marK the beginning of an RCU read-side critical section.
- `rcu_read_unlock()` - mark the end of an RCU read-side critical section.
- `rcu_derefernece()` - dereferences RCU, must be used between instances of `rcu_read_lock()` and `rcu_read_unlock()`.

```
struct my_data
{
	int key;
	int val;
};

struct my_data *global = NULL;
global = kmalloc(sizeof(struct my_data), GFP_KERNEL);
```

To perform the read operation: 

```
struct my_data *tmp;
rcu_read_lock();

tmp = rcu_dereference(global);
if (tmp != NULL) {
	pr_info("key:%d\tval:%d\n", tmp->key, tmp->val);
}
rcu_read_unlock();
```

The reason to do this dereference in this weird way, is again to avoid posible
optimizations (changes in the order of execution of the lines of code) performend
by CPUs or the compiler. 

`rcu_dereference()` internally uses memory barrier instructions/compiler 
directives to avoid those possible (wrong) optimizations. 

#### freeing memory

RCU should free after waiting for pre-existing RCU readers to complete.

RCU waits on "RCU read-side critical sections". 

```
rcu_read_lock();
...
critical section
...
rcu_read_unlock();

```

The basic idea behind RCU is to split update/write into two phases:
- removal
- reclamation

**Removal**: Replaces references to data items with the latests.

**Reclamation**: freeing the old reference. 

#### RCU synchronize

`synchronize_rcu()`: the calling process is blocked until all pre-existing RCU read-side
critical sections on all CPUs have completed. After the function returns, it is safe to 
free the memory associated with the old pointer. 

- `synchronize_rcu()`: waits until all rcu critical sections have been completed (in other processors). 

Note: `synchronize_rcu()` will not necessarily wait for any subsequent RCU rea-side 
critical sections to complete. 

```
		CPU 0			CPU 1 				CPU 2
1.	rcu_read_lock();
2.				enters `synchronize_rcu()`
3.								rcu_read_lock();
4.	rcu_read_unlock();
5.				exits `synchronize_rcu()`
6.								rcu_read_unlock();
```

#### call_rcu 

Another way to avoid blocking is to register a callback which will be called when all
the read-side critical sections are completed. This is done with the function `call_rcu()`:

```
void call_rcu(struct rcu_head *head, rcu_callback_t func);
```

This requires that an instance of `rcu_head` is embedded. 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/rcupdate.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

struct task_struct *thread1, *thread2, *thread3;

typedef struct my_data
{
	int key;
	int val;
	struct rcu_head rhead;

}my_data;

my_data *global_ptr = NULL;

static void rcu_free(struct rcu_head *head)
{
	my_data *data = container_of(head, my_data, rhead);
        pr_info("%s:processor:%d\tfreeing existing data\n", __func__, smp_processor_id());
        kfree(data);
}

static int write_thread_fn(void *arg)
{
	while(!kthread_should_stop())
	{
		my_data *tmp_ptr = global_ptr;
		my_data *new_ptr = kmalloc(sizeof(my_data), GFP_KERNEL);
		memcpy(new_ptr, global_ptr, sizeof(my_data));
		new_ptr->key++;
		new_ptr->val++;
		rcu_assign_pointer(global_ptr, new_ptr);
		pr_info("%s: processor:%d write complete\n\n", __func__, smp_processor_id());
		call_rcu(&tmp_ptr->rhead, rcu_free);
		msleep(3000);
	}
	return 0;
}

static int read_thread_fn(void *arg)
{
	while(!kthread_should_stop())
	{
		my_data *ptr = NULL;
		rcu_read_lock();
		ptr = rcu_dereference(global_ptr);
		if (ptr != NULL)
			pr_info("%s:processor:%d\tkey:%d\t val:%d\n", __func__, smp_processor_id(), 
						ptr->key, ptr->val);
		else
			pr_info("%s write thread did not yet start\n", __func__);
		rcu_read_unlock();
		msleep(3000);
	}
	return 0;
}

static int __init test_hello_init(void)
{
	global_ptr = kmalloc(sizeof(my_data), GFP_KERNEL);
	global_ptr->key = 1;
	global_ptr->val = 1001;

	thread1 = kthread_run(read_thread_fn, NULL, "read_thread1");
	thread2 = kthread_run(write_thread_fn, NULL, "write_thread1");
	thread3 = kthread_run(read_thread_fn, NULL, "read_thread2");
	return 0;
}

static void __exit test_hello_exit(void)
{
	kthread_stop(thread1);
	kthread_stop(thread2);
	kthread_stop(thread3);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

#### Can RCU nest critical sections? 

Is it correct a code like this?

```
static int read_thread_fn(void *arg)
{
	my_data *ptr = NULL;
	rcu_read_lock();
	ptr = rcu_dereference(global_ptr);
	pr_info("%s:key:%d\t val:%d\n", __func__, ptr->key, ptr->val);
	rcu_read_lock();
	ptr = rcu_dereference(global_ptr);
	pr_info("%s:key:%d\t val:%d\n", __func__, ptr->key, ptr->val);
	rcu_read_unlock();
	rcu_read_unlock();

	return 0;
}
```

Yes. As no locking is being done, it is ok to nest it. But watch out because 
the code cannot explicitly block or sleep.

#### How RCU synchronize internally?

We know RCU read-side critical sections delimited by rcu_read_lock() and rcu_read_unlock() are not permitted to block or sleep. 

Therefore, when a given CPU executes a context switch, we are guaranteed that any prior RCU read-side critical sections will have completed. 

`synchronize_cpu()` returns as soon as all the CPU's have completed one context switch.

#### RCU terminology

**Quiescent state**: Any code that is not in an RCU read-side critical section

Readers could see stale data if they enter the read-side critical section before the writer finished updating.

Writer has to wait until all the readers drop their references to the stale data or they have entered the quiescent state.

**Grace Period**: The above time span is called the grace period

```
		Grace period ends after all CPUs execute a context switch

				------------------	Context Switch
				|	RCU	 |	    |
				V       Reader   V          V
	CPU0		----------------------------------------


	
					------------------	Context Switch
					|	RCU	 |	    |
					V       Reader   V          V
	CPU1		---------------------------------------------------

					Synchronize_rcu()
						|
						V
	CPU2		---------------------------------------------------------
						|	Grace	      |
						|	Period	      |
						-----------------------
```

   
	
#### RCU Variants of linked list API


```
Header File: <linux/rculist.h>

void INIT_LIST_HEAD_RCU(struct list_head *list);

void list_add_rcu(struct list_head *new, struct list_head *head);

void list_add_tail_rcu(struct list_head *new, struct list_head *head);

void list_del_rcu(struct list_head *entry);

list_entry_rcu(ptr, type, member);

list_for_each_entry_rcu(pos, head, member);
```

RCU can have multiple-readers, but in case of multiple writers, then locks must be used (spinlock). 

```
//Is this code concurrency safe
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rculist.h>
#include <linux/slab.h>
#include <linux/spinlock.h>


MODULE_LICENSE("GPL");

DEFINE_SPINLOCK(mylock);

typedef struct my_data
{
	struct list_head list;
	int key;
	int data;

}my_data;

LIST_HEAD(listhead);

void insert(int key, int data)
{
	my_data *ptr;
	spin_lock(&mylock);
	ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
	ptr->key = key;
	ptr->data = data;
	list_add_tail_rcu(&(ptr->list), &listhead);
	spin_unlock(&mylock);
}

my_data *search(int key)
{
	my_data *ptr;

	list_for_each_entry_rcu(ptr, &listhead, list) {
		if (ptr->key == key)
			return ptr;
	}
	return NULL;
}

void delete(int key)
{
	my_data *ptr;
	
	ptr = search(key);
	if (ptr != NULL) {
		list_del_rcu(&(ptr->list));
		kfree(ptr);
	}

}

void print_list(void)
{
	my_data *ptr;

	list_for_each_entry_rcu(ptr, &listhead, list) {
		pr_info("key:%d\t value:%d\n", ptr->key, ptr->data);
	}
}

static int __init test_hello_init(void)
{
	insert(1, 1000);
	insert(2, 1001);
	insert(3, 1002);

	pr_info("printing list\n");
	print_list();
	pr_info("deleting key 2\n");
	delete(2);
	pr_info("printing list\n");
	print_list();
	return 0;
}

static void __exit test_hello_exit(void)
{
    pr_info("%s: In exit\n", __func__);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```
#### Advantages of RCU

- Performance
- Deadlock inmunity (no locks are used)
- Realtime latency (because no locks are used, so there is no blocking)


## Lockdep

reference: https://www.kernel.org/doc/Documentation/locking/lockdep-design.txt






























