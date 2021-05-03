# Notes on linux inner workings

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






linux preempt patch 

https://rt.wiki.kernel.org/index.php/CONFIG_PREEMPT_RT_Patch

overview: https://lwn.net/Articles/146861/

https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/preemptrt_setup

https://www.kernel.org/doc/html/latest/scheduler/sched-rt-group.html




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

### Linux posix threads 

https://hpc-tutorials.llnl.gov/posix/

https://en.wikipedia.org/wiki/POSIX

https://www.cs.utexas.edu/~witchel/372/lectures/POSIX_Linux_Threading.pdf

https://www.amazon.com/POSIX-4-Programmers-Guide-Programming-World/dp/1565920740

posix real-time : https://www.ctr.unican.es/publications/mgh-1993a.pdf

https://www.gnu.org/software/libc/manual/html_node/POSIX.html#POSIX


### Time in linux

ref: https://man7.org/linux/man-pages/man7/time.7.html

linux with its posix rea-time extension support both: absolute and relative time

Relative time is based in a hardware timer, based on PIT (Programmable Interval Timer) and TSC (Time Stamp Counter) or it is based in SCT (system Clock Time).

https://man7.org/linux/man-pages/man8/hwclock.8.html

Absolute time, that also is at times not really properly addresed as Real-time, is based on a baterry packed clock or in NTP (network time protocol).

Some times it may be interesting using the Julian Calendar instead of the Gregorian calendar (the calendar we use). Because the Julian Calendar increases monotincally. Also is interesting using the UTC.

Other time measurements TAI (Atomic Interantional Time), UTC, GPS ...

https://man7.org/linux/man-pages/man4/rtc.4.html

Posix RT- timer services for timeouts -> sem_timedwait()

https://cyberglory.wordpress.com/2011/08/21/jiffies-in-linux-kernel/


linux kernel in a nutshell: https://bootlin.com/doc/books/lkn.pdf



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


### Patches

linux development is handled with git as a code repository. https://git-scm.com/book/en/v2/Getting-Started-A-Short-History-of-Git

https://git-scm.com/book/en/v2

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


### Writting a kernel patch

 Clone a stable kernel
 
```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable
cd linux_stable
git branch -a | grep linux-5
    remotes/origin/linux-5.0.y
    remotes/origin/linux-5.1.y
    remotes/origin/linux-5.2.y
​git checkout linux-5.2.y
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

cp /boot/<config-5.0.0-21-generic> .config
```

#### Compiling the kernel 

Run the following command to generate a kernel configuration file based on the current configuration.

```
make oldconfig
```

Other way to tune the kernel your system is by using make localmodconfig. This option creates a configuration file based on the list of modules currently loaded on your system.

```
lsmod > /tmp/my-lsmod
make LSMOD=/tmp/my-lsmod localmodconfig
```

Once this step is complete, it is time to compile the kernel. Using the -j option helps the compiles go faster. The -j option specifies the number of jobs (make commands) to run simultaneously:

```
make -j3 all
```

once the compilation is done, you can install it

```
su -c "make modules_install install"
```

this command will install the kernel, and execute 'update-grub' to add it to the grub menu. 

before rebooting the system, we can store some logs to compare it later, and look for regression or new errors

we use the dmesg with the -t option, to not display the timestamps. This will make it easier later for comparation.

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
 
in case dmesg_current length is zero, it is quite possible that the secure boot is enabled.  That will prevent to boot the new kernel as it is not signed. It is possible to disable temporaly the secure boot with the **mokutil** (MOK manager) 

to check if the secure boot is enabled: 

```
mokutil --sb-state
```
https://askubuntu.com/questions/1119734/how-to-replace-or-remove-kernel-with-signed-kernels

to disable validation:

```
sudo mokutil --disable-validation
root password
mok password: 12345678
mok password: 12345678
sudo reboot
```
to re-enable validation:

```
sudo mokutil --enable-validation
root password
mok password: 12345678
mok password: 12345678
sudo reboot
```
 
Booting the Kernel:

Let’s take care of a couple of important steps before trying out the newly installed kernel. There is no guarantee that the new kernel will boot. As a safeguard, we want to make sure that there is at least one good kernel installed and we can select it from the boot menu. By default, grub tries to boot the default kernel, which is the newly installed kernel. We change the default grub configuration file /etc/default/grub to the boot menu, and pause for us to be able to select the kernel to boot.

Please note that this option only applies to Ubuntu, and other distributions might have a different way to specify boot menu options.

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

Run update-grub to update the grub configuration in /boot

```
sudo update-grub
```

Now, it is possibble to restart the system. Once the new kernel comes up, compare the saved dmesg from the old kernel with the new one, and see if there are any regressions. If the newly installed kernel fails to boot, you will have to boot a good kernel, and then investigate why the new kernel failed to boot.

### Submitting patches

https://www.kernel.org/doc/html/latest/process/submitting-patches.html

all the commits need to be signed-off:   git commit -s

it is needed to create a user-specific configuration file .gitconfig in the home directory with the real legal name.

to accept a patch, the name, and signed-off-by must match.

https://www.kernel.org/doc/html/latest/process/submitting-patches.html
https://www.kernel.org/doc/html/latest/process/kernel-enforcement-statement.html

Kernel Configuration

The Linux kernel is completely configurable. Drivers can be configured to be installed and completely disabled. Here are three options for driver installation:

- Disabled
- Built into the kernel (vmlinux image) to be loaded at boot time
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


