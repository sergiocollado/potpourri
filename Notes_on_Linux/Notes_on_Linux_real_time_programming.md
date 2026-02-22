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


## Fundamentals of Linux

Core function of the Linux Kernel_ 
 - **Process management**: create, schedule and terminate processess (running programs). It decides which CPUs run which programs, when and for how long, using the scheduler.
 - **Memory management**: Keeps track of all memory (RAM) It allocates memorey to process and efficently handles swapping data to disk when RAM is full (virtual memory)
 - **Device maangment**: Act as and intermediary between hardware devices (disks, keyboards, USB devices ...) and processes. This is done by device drivers.
 - **System call interface**: Provides a well defined and secure API (System calls) for applications to request services from the kernel. This is how user programs interact with the hardware.
 - **Filesystem management**: Handles and organizes how data is stored and retrieved on disks (eg. ext4, Btrfs, XFS). It handles reading, writing and managing fiiles and directories.
 - **Networking**: Handles networking communicantion, sending and receiving data pacakges in different protocols.


### Processes, scheduling and priorities

#### What is a process?
A **process** is a running instance of a program. it is more than just the program code (which is static). It is a dynamic entity that includes:
 - the executable code itself
 - data: the variables and data structures the program is working on
 - Resources: allocated by the OS (memory, opened files, network connections (sockets), et
 - Execution context: the state of the process at any point in time (e.g. values in the CPU registers, the program counter ...)

The kernel represents each process with a data structure called **Process Control Block (PCB)** or in the Linux, **task_struct**. This structure holds all the informtion the kernel needs to manage and track the process. 

#### the Scheduler

The scheduler is the core part resposible for deciding which process runs on the CPU and for how long. Its main goals are: 
 - Fairness: give every process a fair share of the CPU time.
 - Efficiency: Keep the CPU as busy as possible
 - Responsiveness: Ensure the system is responsive to user interaction.

Since there are typically more processes than CPUs, the schueduler rapidly switches the CPU between processes. This creates the illusion of simultaneous execution and is called **preemptive multitasking**.





## Setting up a real-time Linux system

Selecting the correct Linux Kernel version is critical when building or deploying a PREEMPT_RT based realt-time system. It affects to **stability**, **latency**, **hardware support** and **long-term maintenance**. 

For Linux kernels there are: 
 - Mainline kernel - the latest development version
 - Long Term Support (LTS) kernel - they are more stable that the lastest dev version, but may have less features.

To use PREEMPT_RT, the version must be greater than < 4.x, in this case PREEMPT_RT is a patch and must be externally patched and build.

In versions 5.4 - 5.10, is a mature patch set, it is used commonly in embedded RT systems

5.15 LTS is widely used, stable RT support

6.1 LTS it has an enhaced RT merging into  mainline, recommended for new real-time projects

6.6+ versions, PREEMPT_RT merged upstream, real time now part of mainline kernel - no external patching needed. 

### Patching, applying and compiling PREEMPT_RT

```batch
$ uname -r # confirm the current kernel version

#install the build dependency
$ sudo apt update
$ sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev dwarves -y

#download the kernel source - version 6.1.156 for example
$ mkdir home/rtlinux
$ cd home/rtlinux
$ wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.156.tar.xz

# extract it
$ tar -xvf linux-6.1.156.tar.xz

# download the RT patch - a version that is compatible with the kernel i just downloaded
# got to: https://cdn.kernel.org/pub/linux/kernel/projects/rt/6.1/older/

$ wget https://cdn.kernel.org/pub/linux/kernel/projects/rt/6.1/older/patch-6.1.156-rt56.patch.xz
$ xzcat patch-6.1.156-rt56-patch.xz | patch -p 1

$ make menuconfig

# look for the preemption model - select fully preemptible kernel
# in the timer subsystem - activate the high resolution timers support
# in the processor type and features check for the timer frequency, and use 1000 Hz.

$ make -j$(nproc) # compile the kernel

$ sudo make modules_install # instal modules
$ sudo make install # install the kernel
$ sudo update-grub # update the bootloader

$ sudo reboot # reboot the system

# check the version
$ uname -r
# the rt(version) should appear now in the name.

$ cat /sys/kernel/realtime # check if the realtime is enabled.

# check the latency installing the tool rt-tests
$ sudo apt install rt-tests
$ sudo cyclictest --smp --priority=80 --interval=1000 --distance=0 # launch the test

```

### Boot parameters for RT

Even with the PREEMPT_RT kernel, your system's boot-time configuration can make or break real-time performance. 

Boot parameters can control: interrupt routing, CPU isolation, power management and timing behaviour at the kernel level. 

The essentinal boot parameters for RT performance: 

 - **threadirqs**: converts hardware interrupts int threads, enabling priority control
 - **isolcpus=**: Excludes certain CPUs from the scheduler. Those excluded CPUs can be used for RT-tasks (example: `isolcpus=2-3`)
 - **nohz_full=**: disables the scheduler ticks on specific CPUs for full isolation (example: `nohz_full=2-3`)
 - **rcu_nocbs=**: offloads RCU callbacks from RT CPUs (example: `rcu_nocbs=2-3`)
 - **Irqaffinity=**: assigns interrutps to specific cores (avoid RT cores), example: `irqaffinity=0-1`
 - **intel_pstate=disable**: disables intel's dynamic frequency scaling
 - **processor.max_cstate=1**: restricts CPUs sleeps states to reduce latency
 - **idle=poll**: keeps CPUs active (no deep idle states)


check the boot paremeters, with: `cat /proc/cmdline`. 

you can edit the boot line, with: `sudo nano /etc/default/grub`

check for the grub command line default: GRUB_CMD_LINE_LINUX_DEFAULT. check the number of cpus with `$ nproc`

```
GRUB_CMD_LINE_LINUX_DEFAULT = "quiet isolcpus=2-3 nohz_full=2-3 rcu_nocbs=2-3 threadirqs idle=poll irqaffinity=0-1 intel_pstate=disabled" 
```

Update grub: `sudo update grub` and reboot `sudo reboot`, you can validate some of the boot parameters and check that those parameters have persisted.

```
$ cat /sys/devices/system/cpu/isolated
$ cat /sys/devices/system/cpu/nohz_full
```





