# Notes on linux inner workings

Index of Documentation for People Interested in Writing and/or Understanding the Linux Kernel: https://www.kernel.org/doc/html/latest/process/kernel-docs.html

kernel coding style: https://www.kernel.org/doc/html/latest/process/coding-style.html

mentorship series: https://events.linuxfoundation.org/lf-live-mentorship-series/

## Linux networking basics

### Switches
 to connect two computers a switch is needed. (A switch can only serve communication within a network)
 
 To see the interfaces, 
 
```
ip link
```

**ip link** is to display and modify interfaces n a linux host.

if the switch has for example the ip: 192.168.1.0. and the computers (A and B)to communicate have the ips. 192.168.1.10 (A)  and 192.168.1.11 (B) 

we add both ip computers with:

**ip addr** is to display the ips of the interfaces, adn **ip addr add** to add ip addresses to the network interfaces.

```
ip addr add 192.168.1.10/24 dev eth0
```

```
ip addr add 192.168.1.11/24 dev eth0
```

### Routing

For connceting different networks a router in needed. Like the router connects with two networks it has two ip addresses assinged, one in each network.

Imaging another network wit a switch (192.168.2.0) and two computers C (192.168.2.10) and D(192.168.2.11). How can system A communicate with C?

In the first network the router has the ip: 192.168.1.1 and in the second network it is identified with the ip: 192.168.2.1

So to communicate between the networks the **gateway** must be defined:

To display the existing routing configuration in a system, use the **route** command

```
route
```

This will display the kernel's routing table.

The **route** or **ip route** command display the routing table

To configure a gateway, so a computer can reach another computer in another network, use the command: **ip route add**

```
ip route add 192.168.2.0/24 via 192.168.1.1
```
- 192.168.1.1 would be the address of the router
- 192.168.2.0/24 would be the range of addresses requested to be accessed through the router

Other example, one of the computers, need to reach an address in the internet (172.217.194.0), you ask to route to that address through the router

```
ip route add 172.217.194.0/24 via 192.168.1.1
```

For not having to define all the ips, outside the own networ, a default policy can be defined:

```
ip route add default via 192.168.2.1
```

or intead of default, it can be defined also as 0.0.0.0, this means any destination


### How to set a linux host a router (fordwarding packets in a linux host)

By default in linux, packets are not forwarded from one interface to the next. 

Wether a host can fordward packets between interfaces is defined in a setting in the system, at the file:

```
/proc/sys/net/ipv4/ip_fordward
```

by default, the value in this file, is set to 0, that states for **not fordward**. 

if you set this value to one, the system will allow fordwarding packets from one interface to other.

```
echo 1 > /proc/sys/net/ipv4/ip_fordward
```

Only setting this value, will not persist in case the system is rebooted, or turned off. For that you must modify this value in:

```
in the file: /etc/sysctl.conf
net.ipv4.ip_fordward = 1
```

## Linux scheduler

 The linux kernel is multithreaded. The scheduler is the system that decides which task runs at each time. In linux the
scheduling is based in threads, not in processes. 

 The scheduler shares the cpu utilization between the tasks.
 
 It selects the next task to run (on each CPU) when:
 - running tasks ends
 - running task sleeps (or waits for an event)
 - a new task is created or a sleeping task wakes up
 - running task time-slice is over.

 The scheduler has scheduling policies with scheduling classes 
 - The scheduling class with highier priority is served first
 - a task can migrate between cpus, scheduling policies and scheduling classes
 - the scheduling classes are: stop, dl (deadline), rt (real-time), cfs(complete fair scheudling), idle.


  _**_schedule()** is the main scheduler function: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/kernel/sched/core.c#n6127

  static struct task_struct ***pick_next_task()** : https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/kernel/sched/core.c#n5547

  reference: https://oska874.gitbooks.io/process-scheduling-in-linux/content/chapter5.html
 
```
/*
 * Pick up the highest-prio task:
 */
static inline struct task_struct *
__pick_next_task(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	const struct sched_class *class;
	struct task_struct *p;

	/*
	 * Optimization: we know that if all tasks are in the fair class we can
	 * call that function directly, but only if the @prev task wasn't of a
	 * higher scheduling class, because otherwise those lose the
	 * opportunity to pull in more work from other CPUs.
	 */
	if (likely(prev->sched_class <= &fair_sched_class &&
		   rq->nr_running == rq->cfs.h_nr_running)) {

		p = pick_next_task_fair(rq, prev, rf);
		if (unlikely(p == RETRY_TASK))
			goto restart;

		/* Assume the next prioritized class is idle_sched_class */
		if (!p) {
			put_prev_task(rq, prev);
			p = pick_next_task_idle(rq);
		}

		return p;
	}

restart:
	put_prev_task_balance(rq, prev, rf);

	for_each_class(class) {
		p = class->pick_next_task(rq);
		if (p)
			return p;
	}

	/* The idle class should always have a runnable task: */
	BUG();
}
```


 Each task (that represents a thread) is defined with the structure 'struct task_struct' (include/linux/sched.d) 
 
 reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/sched.h?h=v5.4.144#n624

```
struct task_struct {
#ifdef CONFIG_THREAD_INFO_IN_TASK
	/*
	 * For reasons of header soup (see current_thread_info()), this
	 * must be the first element of task_struct.
	 */
	struct thread_info		thread_info;
#endif
	/* -1 unrunnable, 0 runnable, >0 stopped: */
	volatile long			state;

	/*
	 * This begins the randomizable portion of task_struct. Only
	 * scheduling-critical items should be added above here.
	 */
	randomized_struct_fields_start

	void				*stack;
	refcount_t			usage;
	/* Per task flags (PF_*), defined further below: */
	unsigned int			flags;
	unsigned int			ptrace;

#ifdef CONFIG_SMP
	struct llist_node		wake_entry;
	int				on_cpu;
#ifdef CONFIG_THREAD_INFO_IN_TASK
	/* Current CPU: */
	unsigned int			cpu;
#endif
	unsigned int			wakee_flips;
	unsigned long			wakee_flip_decay_ts;
	struct task_struct		*last_wakee;

	/*
	 * recent_used_cpu is initially set as the last CPU used by a task
	 * that wakes affine another task. Waker/wakee relationships can
	 * push tasks around a CPU where each wakeup moves to the next one.
	 * Tracking a recently used CPU allows a quick search for a recently
	 * used CPU that may be idle.
	 */
	int				recent_used_cpu;
	int				wake_cpu;
#endif
	int				on_rq;

	int				prio;
	int				static_prio;
	int				normal_prio;
	unsigned int			rt_priority;

	const struct sched_class	*sched_class;
	struct sched_entity		se;
	struct sched_rt_entity		rt;
#ifdef CONFIG_CGROUP_SCHED
	struct task_group		*sched_task_group;
#endif
	struct sched_dl_entity		dl;
...
```

Each task can have different states (defined also at include/linux/sched.)

reference: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/sched.h?h=v5.4

```
/* Used in tsk->state: */
#define TASK_RUNNING			0x0000
#define TASK_INTERRUPTIBLE		0x0001
#define TASK_UNINTERRUPTIBLE		0x0002
#define __TASK_STOPPED			0x0004
#define __TASK_TRACED			0x0008
/* Used in tsk->exit_state: */
#define EXIT_DEAD			0x0010
#define EXIT_ZOMBIE			0x0020
#define EXIT_TRACE			(EXIT_ZOMBIE | EXIT_DEAD)
/* Used in tsk->state again: */
#define TASK_PARKED			0x0040
#define TASK_DEAD			0x0080
#define TASK_WAKEKILL			0x0100
#define TASK_WAKING			0x0200
#define TASK_NOLOAD			0x0400
#define TASK_NEW			0x0800
#define TASK_STATE_MAX			0x1000
```

### Scheduling classes

There are different scheduling classes, defined at include/linux/sched.h

The scheduling classes are: stop, dl (deadline), rt (real-time), cfs(complete fair scheudling), idle.

They are defined at: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/sched.h?h=v5.4.144#n1802

```
#define for_class_range(class, _from, _to) \
	for (class = (_from); class != (_to); class = class->next)

#define for_each_class(class) \
	for_class_range(class, sched_class_highest, NULL)

extern const struct sched_class stop_sched_class;
extern const struct sched_class dl_sched_class;
extern const struct sched_class rt_sched_class;
extern const struct sched_class fair_sched_class;
extern const struct sched_class idle_sched_class;
```

The following code is the code that represents a scheduling class.

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/sched.h?h=v5.4.144#n1712

```
struct sched_class {

    const struct sched_class *next;
    void (*enqueue_task) (struct rq *rq, struct task_struct *p, int flags);
    void (*dequeue_task) (struct rq *rq, struct task_struct *p, int flags);
    void (*yield_task) (struct rq *rq);
    bool (*yield_to_task) (struct rq *rq, struct task_struct *p, bool preempt);
    void (*check_preempt_curr) (struct rq *rq, struct task_struct *p, int flags);
    struct task_struct * (*pick_next_task) (struct rq *rq);
    void (*put_prev_task) (struct rq *rq, struct task_struct *p);
#ifdef CONFIG_SMP
    int (*select_task_rq)(struct task_struct *p, int sd_flag, int flags);
    void (*pre_schedule) (struct rq *this_rq, struct task_struct *task);
    void (*post_schedule) (struct rq *this_rq);
    void (*task_waking) (struct task_struct *task);
    void (*task_woken) (struct rq *this_rq, struct task_struct *task);
    void (*set_cpus_allowed)(struct task_struct *p, const struct cpumask *newmask);
    void (*rq_online)(struct rq *rq);
    void (*rq_offline)(struct rq *rq);
#endif
    void (*set_curr_task) (struct rq *rq);
    void (*task_tick) (struct rq *rq, struct task_struct *p, int queued);
    void (*task_fork) (struct task_struct *p);
    void (*switched_from) (struct rq *this_rq, struct task_struct *task);
    void (*switched_to) (struct rq *this_rq, struct task_struct *task);
    void (*prio_changed) (struct rq *this_rq, struct task_struct *task,  int oldprio);
    unsigned int (*get_rr_interval) (struct rq *rq,  struct task_struct *task);
#ifdef CONFIG_FAIR_GROUP_SCHED
    void (*task_move_group) (struct task_struct *p, int on_rq);
#endif
};
```
This is a skeleton of function pointers. 

All the scheduling classes in the linux kernel are in a linked list, ordered by highiest priority, and the next pointer, points to the next scheduler class. 

The scheduler walksthrough the highest scheduling class, to the lowest scheduling class. 

```
stop_sched_class → dl_shed_class → rt_sched_class → fair_sched_class → idle_sched_class → NULL
```

Stop and Idle are special scheduling classes. Stop is used to schedule the per-cpu stop task which pre-empts everything and can be pre-empted by nothing. It is used only for maintinance within the kernel, to stop everything and run some kernel specific routines.


Idle is used to schedule the per-cpu idle task (also called swapper task) which is run if no other task is runnable. The other two are for the previously mentioned real time and normal tasks. It is for CPU idle, so no tasks is associated with it

### Scheduling classes and policies

 - Stop
    - no policy
 - Deadline
    - SCHED_DEADLINE
 - Real Time
    - SCHED_FIFO
    - SCHED_RR
 - Fair
   - SCHED_NORMAL
   - SCHED_BATCH
   - SCHED_IDLE
 - Idle
   - no policy

#### stop_sched_class (STOP)

- stop_sched_class is the highiest priority class
- only present in SMP, not in User Plane. Because it is used to stop other CPUs. 
- it can preempt anything, and nothing can preempt it. 
- it is a mechanism to stop running everything else and run a specific function on a CPU.
- it has no scheduling policies
- it is used for tasks migrations, cpu migration, RCU, ftrace, clockevents, etc...

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/stop_task.c?h=v5.4.144#n119

#### dl_sched_class (DEADLINE)

 - Added by Dario Faggioli && Juri Lelli (3.14) (2013). it matches the EDF (Earliest Deadline first) 
 - Higiest priority class task in the system.
 - policy is SCHED_DEADLINE
 - implemented with a red-black tree (self balancing)
 - used for periodic real time tasks 

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/deadline.c?h=v5.4.144#n2436

#### rt_sched_class (REAL TIME)

- this matches the POSIX real-tasks specs
- the priorities go from 0 to 99, being 0 the highest priority in kernel and 99 the lowest priority in user space
- policies
   - SCHED_FIFO: (First In First Out)
   - SCHED_RR:   (Round Robin) by default 100 ms slice time.
- implemented with linked lists
- used for short tasks, latency sensitive.

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/rt.c?h=v5.4.144#n2369


#### fair_sched_class CFS (Completelly Fair Scheduling)

- Scheduling Policies
   - SCHED_NORMAL: for normal task
   - SCHED_BATCH:  for cpu bounded tasks
   - SCHED_IDLE:   for low priority tasks
- Implemented with red-black trees (self-balancing)
- tracks the virtual time of tasks (the amount of time a task has run) 
- Task with shortes vruntime runs first
- the priority affects the weight of the task, and that will affect the runtime
- the task priority is: 120 + nice value (-20 to +19)
- used for all the system tasks. 

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/fair.c?h=v5.4.144#n10529

#### idle_sched_class (Idle)

- lowes priority scheduling tasks
- no scheduling policies
- One thread (idle) per CPU: "swapper/N"
- the idle thread runs when there is nothing else to run
- idle thread may take the CPU to a lower power state.

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/idle.c?h=v5.4.144#n456

### Scheduling Policies

#### SCHED_DEADLINE 

In the Real-time literature SCHED_DEADLINE is the EDF (Earliest Dead-line First) scheduler. It the highes priority

This scheduling is more aggressive that SCHED_FIFO, but is harder to handle, and properly manage.

reference: https://www.kernel.org/doc/html/latest/scheduler/sched-deadline.html


#### SCHED_FIFO (First in First Out)

it is a real time scheduling class, defined by POSIX. It runs to completion the higiest prioririty task, with preemptions. it is deterministic

In general real-time tasks, will run until two causes
- complete and exit
- yield, sleep, activate a higher priority or blocked on secondary resource (system call)
- interrupt raised
 
#### SCHED_RR (Round Robin) 

It is also a real-time scheduling scheme, in order of priority tasks run in a round-robin fashion. If a RT (realtime) task is running no other task will be allowed to have processor times. task priority is defined by its rt_priority. it is deterministic. It uses time slices. 

In general real-time tasks, will run until two causes
- complete and exit
- yield, sleep, activate a higher priority or blocked on secondary resource (system call)
- interrupt raised

#### SCHED_OTHER or SCHED_NORMAL

It is the normal scheduling policy por linux. The CFS (Completely fair scheduler). The priority of this tasks in the "nice priority". The nice values ranges from -20 (highiest) to 19 (lowest priority) 

https://www.skillsire.com/read-blog/180_linux-scheduler-profiling.html

### SCHED_BATCH

It is when we want the task to run for longer, to take advantage of cashes for example. 

### SCHED_IDLE 

sCHED_IDLE is not the same as the schedule class 'idle'. SCHED_IDLE is for really low priority tasks.  

### The main runqueue (rq)

 Per CPU there is a runqueue with is a group of all the runnable tasks. rq is defined at kernel/sched.c. The runqueue (rq) also handles some statistics about the CPU load, and scheduling domains for load balancing between the CPUs. 
 
 - Each CPU has an instance of 'struct rq'. 
 - Each runqueue has DL, RT and CFS runqueues with it
 - Runnable taks are enqueued on those runqueues.
 - Many more information is available in the rq. 

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/sched.h?h=v5.4.144#n842

the rq has inside it references to the runqueues fo the different classes


```
struct rq {
...

	struct cfs_rq		cfs;
	struct rt_rq		rt;
	struct dl_rq		dl;
...

```
 

reference: https://oska874.gitbooks.io/process-scheduling-in-linux/content/chapter2.html

reference: BKK19-TR03 - The Linux Kernel Scheduler - Overview: https://www.youtube.com/watch?v=oOiaRHC9ZDg

reference: https://linutronix.de/videos/2021_A_guided_tour_through_the_Preempt-RT_castle.mp4?m=1625133660&

reference: https://linutronix.de/PDF/2021_A_guided_tour_through_the_Preempt-RT_castle.pdf?m=1625133387&

reference: Real-Time Linux Kernel Scheduler: https://www.linuxjournal.com/article/10165


## Linux for Real time

for linux is possible to use extensions or patches for real-time

Linux uses to run under a fair scheduling system
- CFS completely fair schedule
- CFQ completely fair queue for I/O

the fair scheduling in linux is based on a round robin scheme, with some improvements as priority decay and other things, but you can even use a total round robin with SCHED_RR (round-robin)

But for real-time systems fair schedulers are not appropiate.

So for linux, we have the POSIX RT extensions. 
In multi-core systems, as we want determinism and simplicity, AMP (Asymetric Multi-processing) is preferred to SMP (Symetric Multi-processing), because SMP tends to load bance the cores, and this is not optimal for determinims. 

For linux real-time systems we would preffer AMP policy, because each work/task, can be assigned to each corresponding core. For this we can use thread affinity and by-pass SMP in linux, and emulate then an AMP affinity. AMP makes easier to model the behavior of the system, and then its predicitility. 

For linux real-time, the preferredy scheduling policy is SCHED_FIFO, because it is the policy priority preentive run to completion (this make it deterministic). Also basic synchronization mechanisms are needed, it can induce blocking but sometimes synchronization is needed. Also linux has included another scheduling policy EDF (Earliest Death-time First).

In linux a NPLT thread stands as the structure of a service. https://man7.org/linux/man-pages/man7/nptl.7.htm

https://man7.org/linux/man-pages/man7/pthreads.7.html

https://en.wikipedia.org/wiki/Native_POSIX_Thread_Library

https://man7.org/linux/man-pages/man7/sched.7.html

https://www.kernel.org/doc/html/latest/scheduler/index.html

https://man7.org/linux/man-pages/man7/pthreads.7.html

https://man7.org/linux/man-pages/man7/posixoptions.7.html

https://man7.org/linux/man-pages/man7/standards.7.html


pthreads in user space are mapped into kernel tasks

RTOS on linux kernel dispacher runs:
 - on Entry point into kernel following inintialization
 - loops (idle) until task or tasks ar in the ready queue.
    - dispatches the highest priority task from the ready queue
    - Idle is not a task context, is a kernel context.
 - tasks or threads become ready and are dispatched when:
    - a sequencer or Interrupt Service Routine release ( as: semGive(), or sem_post())
    - as a result of a system call( as: mq_send(), taskActivate(), pthread_create())
    - the return of an ISR


Reference: Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment https://dl.acm.org/doi/10.1145/321738.321743


NPTL provides a framework for:

 - fixed priority preemptive
    - rate monotonic
    - deadline monotonic
 
 - dynamic priority preemptive:
    - edf
    - llf 
  
 - non-preentive cooperation
    - multi-frequency executive
    - dataflow

different scheduling policies, for linux with real-time extensions: n <kernel/sched/rt.c>

https://www.kernel.org/doc/html/latest/scheduler/index.html#

SCHED_FIFO - priority preentive & run to completion. like RTOS. It is unfair and determistic. It is implemented with pthreads. 
And runs at priority until:
- complete and exit
- yield, sleep, activate a higher priority or blocked on secondary resource (system call)
- interrupt raised

SCHED_RR (round-robin) - fixed priority preentive: fair, higher overhed (due the tasks rotation in time slices), and it is deterministic.

SCHED_DEADLINE - dynamic priority alternative: adaptative and harder to model. this scheduler is also refered in the literature as EDF (Earliest death-line First) http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.517.771&rep=rep1&type=pdf

SCHED_OTHER: - CFS (Completelly fair scheduler) fair and hard to model. it is a best effort, scalable scheduler.

there are other schedulers as : SCHED_BATCH or SCHED_IDLE...


for hard real-time is recomended SCHED_FIFO, and for soft-real is recommended SCHED_DEADLINE.



```
                                              ┌───────────────────────────────────────────────────┐
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                                                                                  │
                      ◄─────────────────  EXECUTING   ──────────────►                             │
         Waiting on                                                    YielD anD                  │
           ReSourceS                        ▲   │                          WakeUp                 │
                                            │   │                                                 │
  sigWait()    │                            │   │                            │                    │
               │                            │   │ PREEMTED                   │                    │
mutex_lock()   │                   DipacheD │   │   OR YIELD                 │   usleep()         │   Suspended a in an
               │                            │   │   Sched_yield()            │                    │
               │                            │   │                            │    pauSe()         │   exeption (Division by 0)
               │                            │   │                            │                    │
               │                            │   │                            │                    │
               ▼        mutex_unlock()      │   ▼                            │                    │   sigsuspenD()
                                                                             ▼                    │
            PENDING   ─────────────────►    READY  ◄──────────────────   DELAYED                  │
                                                                                                  │
             │  ▲                            │  ▲                          ▲  │                   │
             │  │                            │  │                          │  │                   │
             │  │                            │  │                          │  │                   │
             │  │                            │  │                          │  │                   │
             │  │                            ▼  │                          │  │                   │
             │  │                                                          │  │                   │
             │  │                         SUPENDED                         │  │                   │
             │  └──────────────────────                ────────────────────┘  │                   │
             │                            + DELAYED                           │                   │
             └────────────────────────►                ◄──────────────────────┘                   │
                                           + PENDING                                              │
                                                                                                  │
                                               ▲                                                  │
                                               │                                                  │
                                               │                                                  │
                                               │                                                  │
                                               └──────────────────────────────────────────────────┘
```



### Linux scheduler profiling

#### ftrace

Ftrace in an interal tracer, which can be used for tracing, debugging and analyzing latencies. 

reference: https://www.youtube.com/watch?v=mlxqpNvfvEQ

#### trace-cmd

trace-cmd in a command that works with ftrace 

#### kernel shark

its a front-end for trace-cmnd 

#### Perf

 perf creates a dump for later analyzing the events. 
 
references: https://www.skillsire.com/read-blog/180_linux-scheduler-profiling.html




linux preempt patch 

what is preempt_rt: https://linuxfoundation.org/blog/intro-to-real-time-linux-for-embedded-developers/

https://rt.wiki.kernel.org/index.php/CONFIG_PREEMPT_RT_Patch

overview: https://lwn.net/Articles/146861/

https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/preemptrt_setup

https://www.kernel.org/doc/html/latest/scheduler/sched-rt-group.html

A realtime developer's checklist:  https://lwn.net/Articles/837019/
 

references:

https://man7.org/linux/man-pages/man7/sched.7.html

https://www.kernel.org/doc/html/latest/scheduler/index.html#

https://bootlin.com/doc/books/lkn.pdf

a complete guide to linux scheduling: https://trepo.tuni.fi/bitstream/handle/10024/96864/GRADU-1428493916.pdf

https://wiki.linuxfoundation.org/realtime/rtl/blog#the_real-time_endgame_is_moving_quickly_now

https://en.wikibooks.org/wiki/The_Linux_Kernel/Processing

https://www.kernel.org/doc/html/latest/scheduler/

https://www.kernel.org/doc/html/latest/scheduler/sched-energy.html

http://www.embeddedlinux.org.cn/rtconforembsys/5107final/toc.html

https://hpc-tutorials.llnl.gov/posix/

http://retis.sssup.it/~giorgio/paps/2005/rtsj05-rmedf.pdf

how to compile PREMPT patch https://www.youtube.com/watch?v=RjTfKF7gcIo

A realtime developer's checklist:  https://lwn.net/Articles/837019/


### Linux posix threads 

https://hpc-tutorials.llnl.gov/posix/

https://en.wikipedia.org/wiki/POSIX

https://www.cs.utexas.edu/~witchel/372/lectures/POSIX_Linux_Threading.pdf

https://www.amazon.com/POSIX-4-Programmers-Guide-Programming-World/dp/1565920740

posix real-time : https://www.ctr.unican.es/publications/mgh-1993a.pdf

https://www.gnu.org/software/libc/manual/html_node/POSIX.html#POSIX


### Time in linux

ref: https://man7.org/linux/man-pages/man7/time.7.html

linux with its posix real-time extension support both: absolute and relative time

Relative time is based in a hardware timer, based on PIT (Programmable Interval Timer) and TSC (Time Stamp Counter) or it is based in SCT (system Clock Time).

https://man7.org/linux/man-pages/man8/hwclock.8.html

Absolute time, that also is at times not really properly addresed as Real-time, is based on a baterry packed clock or in NTP (network time protocol).

Some times it may be interesting using the Julian Calendar instead of the Gregorian calendar (the calendar we use). Because the Julian Calendar increases monotincally. Also is interesting using the UTC.

Other time measurements TAI (Atomic Interantional Time), UTC, GPS ...

https://man7.org/linux/man-pages/man4/rtc.4.html

Posix RT- timer services for timeouts -> sem_timedwait()

https://cyberglory.wordpress.com/2011/08/21/jiffies-in-linux-kernel/

linux kernel in a nutshell: https://bootlin.com/doc/books/lkn.pdf




## preempt_rt

what is preempt_rt: https://linuxfoundation.org/blog/intro-to-real-time-linux-for-embedded-developers/

https://wiki.linuxfoundation.org/realtime/preempt_rt_versions

main website: https://wiki.linuxfoundation.org/realtime/start

https://emlid.com/raspberry-pi-real-time-kernel/

We’ve used cyclictest program to obtain data with the following parameters:

cyclictest -l10000000 -m -n -a0 -t1 -p99 -i400 -h400 -q 



## Linux kernel development process

references:

what is a kernel: https://youtu.be/LLBrBBImJt4

Tim Beale: Linux Kernel Development for Newbies: https://youtu.be/OkhOoBqLb3Y

https://github.com/agelastic/eudyptula

Write and Submit your first Linux kernel Patch: https://youtu.be/LLBrBBImJt4


### Intro

https://www.kernel.org/doc/html/latest/process/development-process.html

Linux kernel releases come every 2+ months (10 or 11 weeks). Releases are time based and not feature based. 

When the new version is released a 2 week window is open for merging new pulls for the next release. so mantainers send signed git pull requests in that merge window. After that period is created the first relesase candidate, known as **rc1**. So new features are only included in this first merge window.

At this point the release cycle goes into bug fixes-only mode. So release candidates are generated till mayor bug fixes and regressions are solved.

When enough confidence on the quality of the code is reached, the stable version is released. 

https://www.kernel.org/category/releases.html

https://www.kernel.org/doc/linux/MAINTAINERS

http://vger.kernel.org/vger-lists.html

https://lore.kernel.org/lists.html

https://git.kernel.org/

#### kernel trees

- linux_mainline: Linus releases mainline kernels and RC releases
- linux_stable: stable releases branches
- linux-next: code from many subsystems gets pulled into the tree and periodically is released for integration testing.


### Patches

linux development is handled with git as a code repository. https://git-scm.com/book/en/v2/Getting-Started-A-Short-History-of-Git

https://git-scm.com/book/en/v2

to generate a patch:

```
git format-patch -1 --pretty=fuller XXXXXXXX
```

the code submitted in patches must be signed off

https://www.kernel.org/doc/html/latest/process/submitting-patches.html#sign-your-work-the-developer-s-certificate-of-origin

https://www.kernel.org/doc/html/latest/process/submitting-patches.html#using-reported-by-tested-by-reviewed-by-suggested-by-and-fixes

https://www.kernel.org/doc/html/latest/process/submitting-patches.html#using-reported-by-tested-by-reviewed-by-suggested-by-and-fixes
 
and the patch prefixes are:  [PATCH], [PATCH RFC] or [RFC PATCH] or [PATCH v4] 


### Codes of conduct

https://www.kernel.org/doc/html/latest/process/code-of-conduct.htm

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/LICENSES/preferred/GPL-2.0

https://www.kernel.org/doc/html/latest/process/kernel-enforcement-statement.html



How to configure the kernel: https://www.kernel.org/doc/Documentation/kbuild/kconfig.txt

kernel documentation: https://www.kernel.org/doc/Documentation/

### Configuration of the development system

https://ubuntu.com/tutorials/create-a-usb-stick-on-ubuntu#1-overview

https://ubuntu.com/tutorials/create-a-usb-stick-on-windows#1-overview

It is recomended 3GB for the boot partition.

The packaget build-essential is needed in the system.


```
sudo apt-get install build-essential vim git cscope libncurses-dev libssl-dev bison flex
sudo apt-get install git-email
```

It is needed to check the minimal requirements to compile the kernel

https://www.kernel.org/doc/html/latest/process/changes.html

git-email is for sending patches through the **sendmail** configuration option once the **smtp** server is configured.

example configuration for gmail: https://gist.github.com/jasonkarns/4354421, https://coderwall.com/p/qcsiew/setting-up-and-using-git-send-email-with-gmail

https://www.kernel.org/doc/html/latest/process/email-clients.html


### Exploring the linux kernel sources

You should create a directory, to git clone the linux repo, for example the mainline: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/ 

```
>> cd /linux_work
>> git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git linux_mainline
>> cd linux_mainline; ls -h

arch          CREDITS                 drivers  ipc      lib          mm       scripts   usr
block    crypto         fs               Kbuild      LICENSES     net      security  virt
certs        cscope.out          include    Kconfig  MAINTAINERS  README      sound
COPYING    Documentation  init     kernel       Makefile          samples  tools
```

or to clone the stables

```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable
```

You can use cregit-linux tool, to explore the code: https://cregit.linuxsources.org/

for example: https://cregit.linuxsources.org/code/5.11/

the most part of the linux kernel, is in the 'drivers' subdirectory.

In 'arch' we can see all the supported architectures: https://cregit.linuxsources.org/code/5.11/arch/

You can also use 'git log' to explore the different commmits. 

```
git format-patch -1 <commit ID>
```

For everyday tinkering with the kernel, take into account the scripts: scripts/get_maintainer.pl and scripts/checkpatch.pl

Also check the linux-kselftest repo


### Writing a kernel patch

$(uname -r) displays the running Kernel version .

 Clone the stable kernel tree
 
```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable
cd linux_stable
git branch -a | grep linux-5
    remotes/origin/linux-5.0.y
    remotes/origin/linux-5.1.y
    remotes/origin/linux-5.2.y
git checkout linux-5.2.y
 ```
 
 Next you have to copy the configuration file from your current kernel, from /proc/config.gz or /boot, and copy it to  linux_stable/.config
 
 for example:
 
 ```
 ls /boot
config-5.0.0-20-generic        memtest86+.bin
config-5.0.0-21-generic        memtest86+.elf  //< this is the latest configuration
efi                            memtest86+_multiboot.bin
grub                           System.map-5.0.0-20-generic
initrd.img-5.0.0-20-generic    System.map-5.0.0-21-generic
initrd.img-5.0.0-21-generic    vmlinuz-5.0.0-20-generic
lost+found                     vmlinuz-5.0.0-21-generic
```

The easy thing to do, is to copy your actual config file (in /boot/) and move it to where the linux source is, and name it as .config.

```
cp /boot/<config-5.0.0-21-generic> .config
```

#### Compiling the kernel 

refence: http://www.kroah.com/lkn/ -linux kernel in a nutshell

the kernel configuration is in the file named .config at the top of the kernel source tree.

you may need to install:  libelf-dev, libelf-devel or elfutils-libelf-devel

Run the following command to generate a kernel configuration file based on the current configuration.

```
make oldconfig
```

'make oldconfig' reads the existing .config file that was used for an old kernel and prompts the user for options in the current kernel source that are not found in the file. This is useful when taking an existing configuration and moving it to a new kernel.

WATCH OUT!: New releases often introduce new configuration variables and, in some cases, rename the configuration symbols. The latter causes problems, and make oldconfig might not generate a new working kernel. Run make listnewconfig after copying the configuration from /boot to the .config file, to see a list of new configuration symbols. 

reference: https://stackoverflow.com/questions/4178526/what-does-make-oldconfig-do-exactly-in-the-linux-kernel-makefile

reference: https://www.kernel.org/doc/html/latest/kbuild/kconfig.html

**Bonuses** make olddefconfig sets every option to their default value without asking interactively. It gets run automatically on make to ensure that the .config is consistent in case you've modified it manually.

Other way to tune the kernel your system is by using **make localmodconfig**. This option creates a configuration file based on the list of modules currently loaded on your system.

```
lsmod > /tmp/my-lsmod
make LSMOD=/tmp/my-lsmod localmodconfig
```

A simpler choice is use **make defconfig**, every kernel has a default configuration, so with the 'defconfig' option that default configuration is used.


otherwise use: 

```
make menuconfig
```

or 

```
make xconfig
```

you can get help:

```
sergio@debian:~/linux_work/linux_stable$ make help
Cleaning targets:
  clean		  - Remove most generated files but keep the config and
                    enough build support to build external modules
  mrproper	  - Remove all generated files + config + various backup files
  distclean	  - mrproper + remove editor backup and patch files

Configuration targets:
  config	  - Update current config utilising a line-oriented program
  nconfig         - Update current config utilising a ncurses menu based program
  menuconfig	  - Update current config utilising a menu based program
  xconfig	  - Update current config utilising a Qt based front-end
  gconfig	  - Update current config utilising a GTK+ based front-end
  oldconfig	  - Update current config utilising a provided .config as base
  localmodconfig  - Update current config disabling modules not loaded
                    except those preserved by LMC_KEEP environment variable
  localyesconfig  - Update current config converting local mods to core
                    except those preserved by LMC_KEEP environment variable
  defconfig	  - New config with default from ARCH supplied defconfig
  savedefconfig   - Save current config as ./defconfig (minimal config)
  allnoconfig	  - New config where all options are answered with no
  allyesconfig	  - New config where all options are accepted with yes
  allmodconfig	  - New config selecting modules when possible
  alldefconfig    - New config with all symbols set to default
  randconfig	  - New config with random answer to all options
  yes2modconfig	  - Change answers from yes to mod if possible
  mod2yesconfig	  - Change answers from mod to yes if possible
  listnewconfig   - List new options
  helpnewconfig   - List new options and help text
  olddefconfig	  - Same as oldconfig but sets new symbols to their
                    default value without prompting
  tinyconfig	  - Configure the tiniest possible kernel
  testconfig	  - Run Kconfig unit tests (requires python3 and pytest)

```


Once this step is complete, it is time to compile the kernel. Using the '-j' option helps the compiles go faster. The '-j' option specifies the number of jobs (make commands) to run simultaneously:

```
make -j3 all
```

the end of compilation should be like ...

```
  ...
  CC      arch/x86/boot/cpu.o
  AS      arch/x86/boot/compressed/efi_thunk_64.o
  CC      arch/x86/boot/compressed/misc.o
  GZIP    arch/x86/boot/compressed/vmlinux.bin.gz
  MKPIGGY arch/x86/boot/compressed/piggy.S
  AS      arch/x86/boot/compressed/piggy.o
  LD      arch/x86/boot/compressed/vmlinux
  ZOFFSET arch/x86/boot/zoffset.h
  OBJCOPY arch/x86/boot/vmlinux.bin
  AS      arch/x86/boot/header.o
  LD      arch/x86/boot/setup.elf
  OBJCOPY arch/x86/boot/setup.bin
  BUILD   arch/x86/boot/bzImage
Kernel: arch/x86/boot/bzImage is ready  (#1)
```
and it should create a 'vmlinux' image.


Once the compilation is done, you can install it

```
su -c "make modules_install install"
```

This command will install the kernel, and execute 'update-grub' to add it to the grub menu. 

Before rebooting the system, we can store some logs to compare it later, and look for regression or new errors

We use the dmesg with the -t option, to not display the timestamps. This will make it easier later for comparation.

```
dmesg -t > dmesg_current
dmesg -t -k > dmesg_kernel
dmesg -t -l emerg > dmesg_current_emerg
dmesg -t -l alert > dmesg_current_alert
dmesg -t -l crit > dmesg_current_crit
dmesg -t -l err > dmesg_current_err
dmesg -t -l warn > dmesg_current_warn
```

It is expected to be clean:  emerg, alert, crit, and err level messages

Before testing the new kernel, that we don't know if it will boot, a couple of safety measures:

By default, grub tries to boot the default kernel, which is the newly installed kernel. We change the default grub configuration file /etc/default/grub to the boot menu, and pause for us to be able to select the kernel to boot.
 
In case dmesg_current length is zero, it is quite possible that the secure boot is enabled.  That will prevent to boot the new kernel as it is not signed. It is possible to disable temporaly the secure boot with the **mokutil** (MOK manager) 

To check if the secure boot is enabled: 

```
mokutil --sb-state
```

https://askubuntu.com/questions/1119734/how-to-replace-or-remove-kernel-with-signed-kernels

to disable validation:

```
sudo mokutil --disable-validation
root password
mok password: 1234567
mok password: 1234567
sudo reboot
```
to re-enable validation:

```
sudo mokutil --enable-validation
root password
mok password: 1234567
mok password: 1234567
sudo reboot
```
NOTE: if the kernel fails, and you need to remove it: https://askubuntu.com/questions/176322/removing-old-kernel-entries-in-grub

```
for kernels build from source: 
The solution is to manually delete all the files related to the old kernels in the /boot folder and run sudo update-grub. The extra entries vanished
```


Booting the Kernel:

Let’s take care of a couple of important steps before trying out the newly installed kernel. There is no guarantee that the new kernel will boot. As a safeguard, we want to make sure that there is at least one good kernel installed and we can select it from the boot menu. By default, grub tries to boot the default kernel, which is the newly installed kernel. We change the default grub configuration file **/etc/default/grub** to the boot menu, and pause for us to be able to select the kernel to boot.

Please note that this option only applies to Ubuntu and Debian, and other distributions might have a different way to specify boot menu options.

Increase the GRUB_TIMEOUT value to 10 seconds, so grub pauses in menu long enough to choose a kernel to boot:

``` 
Uncomment GRUB_TIMEOUT and set it to 10: GRUB_TIMEOUT=10
Comment out GRUB_TIMEOUT_STYLE=hidden
```

If the newly installed kernel fails to boot, it is nice to be able to see the early messages to figure out why the kernel failed to boot.

Enable printing early boot messages to vga using the earlyprintk=vga kernel boot option:

```
GRUB_CMDLINE_LINUX="earlyprintk=vga"
```
For information in grub: **'info -f grub -n 'Simple configuration''**

NOTE!: Run **update-grub** to update the grub configuration in /boot

```
sudo update-grub
```

```
sergio@debian:/etc/default$ sudo update-grub
Generating grub configuration file ...
Found background image: /usr/share/images/desktop-base/desktop-grub.png
Found linux image: /boot/vmlinuz-5.12.10
Found initrd image: /boot/initrd.img-5.12.10
Found linux image: /boot/vmlinuz-4.19.0-16-amd64
Found initrd image: /boot/initrd.img-4.19.0-16-amd64
done
```

Now, it is possibble to restart the system. Once the new kernel comes up, compare the saved dmesg from the old kernel with the new one, and see if there are any regressions. If the newly installed kernel fails to boot, you will have to boot a good kernel, and then investigate why the new kernel failed to boot.

### Submitting patches

https://www.kernel.org/doc/html/latest/process/submitting-patches.html

https://kernelnewbies.org/FirstKernelPatch


All the commits need to be signed-off:   

Create a .gitconfig file in your home directory.
- Name is the full legal author name 
- email is the email address for the commit 
- signoff = true 

reference: https://www.kernel.org/doc/html/latest/process/submitting-patches.html

```
git commit -s
```

To accept a patch, the name, and signed-off-by must match.

https://www.kernel.org/doc/html/latest/process/submitting-patches.html
https://www.kernel.org/doc/html/latest/process/kernel-enforcement-statement.html

Kernel Configuration

The Linux kernel is completely configurable. Drivers can be configured to be installed and completely disabled. Here are three options for driver installation:

- Disabled
- Built into the kernel (vmlinux image) to be loaded at boot time (avoid for long booting times!)
- Built as a module to be loaded as needed using modprobe.

It is a good idea to configure drivers as modules, to avoid large kernel images. Modules (.ko files) can be loaded when the kernel detects hardware that matches the driver. Building drivers as modules allows them to be loaded on demand, instead of keeping them around in the kernel image even when the hardware is either not being used, or not even present on the system.

A good option is generating the new configuration with the old configuration as the starting point. New releases often introduce new configuration variables and, in some cases, rename the configuration symbols. The latter causes problems, and make oldconfig might not generate a new working kernel.

https://www.kernel.org/doc/html/latest/kbuild/kconfig.html

Run 'make listnewconfig' after copying the configuration from '/boot' to the .config file, to see a list of new configuration symbols. Kconfig make config is a good source about Kconfig and make config ( https://www.kernel.org/doc/html/latest/kbuild/kconfig.html ) . Please refer to the Kernel Build System to understand the kernel build framework and the kernel makefiles.

https://www.kernel.org/doc/html/latest/kbuild/kconfig.html

https://www.kernel.org/doc/html/latest/kbuild/index.html

previously to any change create a new branch from the linux_mainline repository you cloned earlier to write your first patch. We will start by adding a remote first to do a rebase (pick up new changes made to the mainline).

```
cd linux_mainline
git branch -a
* master
  remotes/linux/master
  remotes/origin?HEAD -> origin/master
  remotes/origin/master
```

Then  add git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git as the remote named linux. Adding a remote helps us fetch changes and choose a tag to rebase from.

We can pick a tag to rebase to. In this case, there is only one new tag. Let’s hold off on the rebase and start writing a new patch

To check out a branch do:

```
git checkout -b work
master
* work
  remotes/linux/master
  remotes/origin/HEAD -> origin/master
```

now you can make a change, to a driver, for example. You can list the modules with **lsmod**. You can find the .c and .h files for that driver in the linux kernel repository. 
Or even searching through the Makefiles, or even with 'git grep' 

for example with the uvcvideo driver is a USB Video Class (UVC) media driver for video input devices, such as webcams. It supports webcams on laptops. Let’s check the source files for this driver.

you can look for it with:

```
git grep uvcvideo -- '*Makefile'
drivers/media/usb/uvc/Makefile:uvcvideo-objs := uvc_driver.o uvc_queue.o uvc_v4l2.o uvc_video.o uvc_ctrl.o drivers/media/usb/uvc/Makefile:uvcvideo-objs += uvc_entity.o
drivers/media/usb/uvc/Makefile:obj-$(CONFIG_USB_VIDEO_CLASS) += uvcvideo.o
```

kernel code style: https://www.kernel.org/doc/html/latest/process/coding-style.html

https://events.linuxfoundation.org/mentorship-session-kernel-validation-with-kselftest/

KERNEL TESTS 

- The kernel CI: https://kernelci.org/
- issues: https://lists.01.org/hyperkitty/
- linaro QA: https://qa-reports.linaro.org/lkft/
- buildBot: https://kerneltests.org/

APPLYING PATCHES:

 Each Linux patch is a self-contained change to the code that stands on its own, unless explicitly made part of a patch series. New patches are applied as follows:

```
patch -p1 < file.patch
git apply --index file.patch
```

Either command will work; however, when a patch adds a new file and, if it is applied using the patch command, git does not know about the new files, and they will be treated as untracked files. The git diff command will not show the files in its output and the git status command will show the files as untracked. You can use git diff HEAD to see the changes.

For the most part, there are no issues with building and installing kernels; however, the git reset --hard command will not remove the newly created files and a subsequent git pull will fail.

SOLUTION1 
When a patch that adds new files is applied using the patch command, run git clean to remove untracked files before running git reset --hard. For example, git clean -dfx will force the removal of untracked directories and files, ignoring any standard ignore rules specified in the .gitignore file. You could include the -q option to run git clean in quiet mode, if you do not care to know which files are removed.​

SOLUTION2
An alternate approach is to tell git to track the newly added files by running git apply --index file.patch. This will result in git applying the patch and adding the result to the index. Once this is done, git diff will show the newly added files in its output and git status will report the status correctly, tagging these files as newly created files.

CHECK KERNEL LOGS

```
dmesg -t -l emerg
dmesg -t -l crit
dmesg -t -l alert
dmesg -t -l err
dmesg -t -l warn
dmesg -t -k
dmesg -t
```

STRESS TEST,

 lauch several kernel compilations in parallel ... :/
 
 ```
 time make all
 ```
 
DEBUGING KERNEL PANICS 

https://sanjeev1sharma.wordpress.com/tag/debug-kernel-panics/
https://www.opensourceforu.com/2011/01/understanding-a-kernel-oops/

Decode and Analyze the Panic Message
Panic messages can be decoded using the decode_stacktrace.sh tool. Please refer to decode_stacktrace https://lwn.net/Articles/592724/ : make stack dump output useful again for details on how to use the tool.

https://www.kernel.org/doc/html/latest/trace/events.html



HOW TO BUILD THE KERNEL DOCUMENTATION

There is a script which checks if you have all the needed dependencies to build the documentation. This script is called automatically when you run

make htmldocs

Alternatively, you can call the script directly by running:

./scripts/sphinx-pre-install

Once you have all the requirements, you can do the building by running:

make htmldocs > doc_make.log 2>&1

Check for warnings and other errors you might find and see if you can fix them.



TODO: 
- Kernel-bypass techniques for high-speed network packet processing : https://youtu.be/MpjlWt7fvrw
- Kernel-bypass networking for fun and profit : https://youtu.be/noqSZorzooc
- Data plane development kit DPDK: DPDK deep-dive : https://youtu.be/VJ8CVN3oXMw
- Linux Networking - eBPF, XDP, DPDK, VPP - What does all that mean? (by Andree Toonk) : https://youtu.be/hO2tlxURXJ0
- Linux packet journey,napi, hardware queue,skb : https://youtu.be/6Fl1rsxk4JQ
- Introduction to Memory Management in Linux :  https://youtu.be/7aONIVSXiJ8
- Steven Rostedt - Learning the Linux Kernel with tracing : https://youtu.be/JRyrhsx-L5Y
- Design Microservice Architectures the Right Way: https://youtu.be/j6ow-UemzBc
- Mastering Chaos - A Netflix Guide to Microservices : https://youtu.be/CZ3wIuvmHeM
- tcddump: https://www.youtube.com/watch?v=hWc-ddF5g1I

TODO: Linux security implementations - TPM, FDE, LUKS, HSM, etc.

tpm : https://en.wikipedia.org/wiki/Trusted_Platform_Module && https://www.kernel.org/doc/html/latest/security/tpm/index.html

UEFI Secure Boot: https://wiki.debian.org/SecureBoot





## Notes on Linux kernel security overview 

Notes on the talk https://www.youtube.com/watch?v=L7KHvKRfTzc&t=945s  - James Morris
Other reference: https://www.youtube.com/watch?v=McuP1_mvE_g

reference:  https://kernsec.org/

DAC - Discrection Acess control - This was the UNIX security mechanism. Linux is based in UNIX. This was the first approach. 

But UNIX was not desinged for security. DAC is not appropiate for the modern security threads. 

POSIX ACL (Access Control List), are stensions of DACs. https://www.usenix.org/legacy/publications/library/proceedings/usenix03/tech/freenix03/full_papers/gruenbacher/gruenbacher_html/main.html
https://linux.die.net/man/5/acl

There is an audit subsitem in the kernel; check https://linux.die.net/man/8/auditctl. Implemented to comply with goverment certification requirementes (similar to C2 ¿?) 
https://www.tecmint.com/linux-system-auditing-with-auditd-tool-on-centos-rhel/


Other security mechanism is **seccommp** : https://man7.org/linux/man-pages/man2/seccomp.2.html  https://outflux.net/teach-seccomp/  

Other security mechanism are **namespaces**: cgroup, ipc, network, pid, user, mount, uts, 

APIS: clone(2), setns(2), unshare(2), pam_namespace(8) 

In fact, linux containers are namespaces + cgroups, 

- Linux Namespaces: https://medium.com/@teddyking/linux-namespaces-850489d3ccf
- network namespaces: https://www.youtube.com/watch?v=j_UUnlVC2Ss
- Introduction to Linux Network Namespaces: https://www.youtube.com/watch?v=_WgUwUf1d34
- Understanding user namespaces - Michael Kerrisk: https://www.youtube.com/watch?v=83NOk8pmHi8
- Cgroups, namespaces, and beyond: what are containers made from?: https://www.youtube.com/watch?v=sK5i-N34im8


Regarding networking is the: **Netfilter**

Also the **Cryptograpy API**, also the keys managers, key rings, tokens ... In userland: **keyctl(1)**

serveral types of keys:

- per process, session
- trusted keys: TPM generated and sealed
- encrypted keys: kernel generated and encrypted

**LSM** : SELinux framework. Linux Security Modules: Allows, different access control schemes to be plugged into the kernel. https://www.starlab.io/blog/a-brief-tour-of-linux-security-modules

- https://www.kernel.org/doc/html/v5.0/admin-guide/LSM/index.html
- Overview and Recent Developments: seccomp and Small Linux Security Modules - Kees Cooke: https://www.youtube.com/watch?v=hTdXJbnnJ88
- Inside the Linux Security Modules (LSM) - Vandana Salve, Prasme Systems: https://www.youtube.com/watch?v=RKBBPsp-TZ0
- Tutorial: How to Write a Linux Security Module - Casey Schaufler: https://www.youtube.com/watch?v=4rFxZw3USIs

**SELinux** Security Enhanced Linux: 
- All objects & subjects have security labels,
- All relevant security interactions are mediated via fine-graned generalized permissions. 
- flexible security policies: separation of mechanism and policy 
- policy centrally administered, and no overridable by user (include root)
- helps contain breaches via least privilige
- implemented in fedora family, android.

**KSP** kernel Self protection project:(KSPP) hardening the kernel against an attack;

- https://kernsec.org/wiki/index.php/Kernel_Self_Protection_Project
- https://kernsec.org/wiki/index.php/Projects






