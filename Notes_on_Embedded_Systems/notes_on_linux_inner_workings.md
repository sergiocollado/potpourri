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

the fair scheduling in linux is based on a round robin scheme, with some improvements as priority decay and other things, but you can even use a total round robin with SCHED_RR.

But for real-time systems fair schedulers are not appropiate.

So for linux, we have the POSIX RT extensions. 
In multi-core systems, as we want determinism and simplicity, AMP (Asymetric Multi-processing) is preferred to SMP (Symetric Multi-processing), because SMP tends to load bance the cores, and this is not optimal for determinims. 

For linux, the preferredy scheudling policy is SCHED_FIFO, because it is the policy priority preentive run to completion. Also basic synchronization mechanisms are needed, it can induce blocking but sometimes synchronization is needed. Also linux has included another scheduling policy EDF.

In linux a NPLT thread stands as the structure of a service. https://man7.org/linux/man-pages/man7/nptl.7.htm

https://en.wikipedia.org/wiki/Native_POSIX_Thread_Library

https://man7.org/linux/man-pages/man7/sched.7.html

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

references:

https://man7.org/linux/man-pages/man7/sched.7.html

https://wiki.linuxfoundation.org/realtime/rtl/blog#the_real-time_endgame_is_moving_quickly_now

https://en.wikibooks.org/wiki/The_Linux_Kernel/Processing

https://bootlin.com/doc/books/lkn.pdf

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



