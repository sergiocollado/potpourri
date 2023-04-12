# Notes on Linux kernel synchronization

reference: https://0xax.gitbooks.io/linux-insides/content/SyncPrim/ <br>
reference: EEC3-4029 Operating Systems: http://gauss.ececs.uc.edu/Courses/c4029/videos.html <br>
reference: linux-kernel-labs: https://linux-kernel-labs.github.io/refs/heads/master/index.html <br>
reference: https://github.com/shemminger/kernel-examples  -Locking and concurrency in Linux kernel examples <br>
reference: https://github.com/PacktPublishing/Linux-Kernel-Programming/blob/master/Linux-Kernel-Programming-(Part-2)/Linux%20Kernel%20Programming%20Part%202%20-%20Char%20Device%20Drivers%20and%20Kernel%20Synchronization_eBook.pdf  <br>
reference: Linux kernel memory model: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0124r6.html <br>


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

reference: https://0xax.gitbooks.io/linux-insides/content/SyncPrim/linux-sync-1.html <br>
reference: https://www.kernel.org/doc/html/latest/locking/locktypes.html <br>
reference: https://www.kernel.org/doc/html/latest/locking/spinlocks.html#lesson-1-spin-locks <br>
reference: https://lwn.net/Kernel/Index/#Spinlocks

The problem wit atomic operations, its that they can only work with CPU work and double work size. Atomics cannot work with shared data structures of custom size. 

In real life, critical regions can be mode that one line. And these code paths should execute atomically to avoid race conditions. To ensure atomicity of suche code blocks, **locks** are used. 

### Spinlocks

The most common lock in the Linux kernel is the spin-lock.

Spin lock are used to protect **short code sections** that comprise just a few C statements and are therefore quickly executed and exited. 

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
#include <linux/uaccess..h>
#include <linux/spinlock.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber; 

static struct class *class = NULL;
static struct device *device = NULL;
static strut cdev mycdev;

#define MAX_SIZE (1024)
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LINCESE("GPL");

DEFINE_SPINLOCK(my_lock);

static int device_open(struct inode *inode, struct file *file)
{
    pr_info("%s trying to acquire spinloc on processor:%d\n", __func__, smp_processor_id());
    spin_lock(&my_lock);
    pr_info(%s: spinlock acquierd on processor: %d\n", __func__, smp_processor_id());
    file_f_pos = 0;
    buffer_index = 0;
    return 0;
}

static int device_release( struct inode *inode, struct file *file)
{
    pr_info("%s\n", __func__);
    pr_info("%s: spinlock released on processor: %d\n", __func__, smp_processor_id());
    spin_unlock(&my_lock);
    return 0;
}

static int test_hello_init(void)
{
    class = class_create(THIS_MODULE, "myclass");
    
    if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
        printk("device number resgistered\n");
	printk("major number received:%d\n", MAJOR(devicenumber));
	
	device = device_create(class, NULL, devicenumber, NULL, device_name);
	cdev_init(&mycdev, &device_fops);
	mycdev.owner = THIS_MODULE;
	cdev_add(&mycdev, devicenumber, count);
    }
    else 
         printk("device number regristration failed!\n");
    return 0;
}

static void test_hello_exit(void)
{
    device_destroy(class, devicenumber);
    class_destroy(class);
    cdev_del(&mycdev);
    unregister_chrdev_region(devicenmber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);

```




