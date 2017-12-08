<hr>
>> Reference: man pages:

 >> User commands: [:link:](http://man7.org/linux/man-pages/dir_section_1.html)
 
 >> System calls: [:link:](http://man7.org/linux/man-pages/dir_section_2.html)
 
 >> Library standard C: [:link:](http://man7.org/linux/man-pages/dir_section_3.html)
  
 >> Devices [:link:](http://man7.org/linux/man-pages/dir_section_4.html)
  
 >> Files systems [:link:](http://man7.org/linux/man-pages/dir_section_5.html)
  
 >> Conventions & miscellaneous [:link:](http://man7.org/linux/man-pages/dir_section_7.html)
  
 >> system Administration [:link:](http://man7.org/linux/man-pages/dir_section_8.html)
  
<hr>

In case something is not working properly, always have a go with with the following:

> sudo apt-get update

> sudo apt-get upgrade



REFERENCES:
>> Of course the master reference will be: https://linux.die.net/man/  </br>
>> And certanly our battle-horse the HOWTOs: https://linux.die.net/HOWTO/HOWTO-INDEX/ </br>
>> at Linux Documentation Project: https://github.com/tLDP/LDP/tree/master/LDP </br>
>> For the linux kernel: https://www.kernel.org/ </br>
>> and for github:https://git.kernel.org/cgit/ </br>
>> also check: https://github.com/google/ktsan </br>
>> check the HOWTOs: http://tldp.org/en/Traffic-Control-HOWTO/
>> also: http://www.linux-tutorial.info/modules.php?name=MContent&pageid=224
>> the linux device drivers book 3rd edition, is at: https://lwn.net/Kernel/LDD3/ 
>> Embedded linux website: http://www.elinux.org/
>> Buildroot manual: https://buildroot.org/downloads/manual/manual.html
>> https://www.linux.com/ <br>
>> https://www.linux.com/tutorials <br>
>> to made an USB live LINUX, check: http://www.linuxliveusb.com/en/features <br>
GNU ARM embedded toolchain:  https://launchpad.net/gcc-arm-embedded

C library for embedded systems:  https://sourceware.org/newlib/

binutils:  http://www.gnu.org/software/binutils/

GNU ARM TOOLCHAIN: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm

developers: https://launchpad.net/~gcc-arm-embedded-developers

gcc: http://gcc.gnu.org/

journal: http://www.linuxjournal.com





  

The analysis of the memory in the linux system, can be checked using the commands:

1)
Remember that the '/proc' filesystem is a pseudo-filesystem whose files provide an interface to kernel data structures.

reading the file: /proc/meminfo

```bash
>> less /proc/meminfo
or
>> cat /proc/meminfo

MemTotal:        8169924 kB<br>
MemFree:         7274872 kB<br>
Buffers:          154784 kB<br>
Cached:           213312 kB<br>
SwapCached:            0 kB<br>
Active:           265184 kB<br>
Inactive:         233264 kB<br>
Active(anon):     131196 kB<br>
Inactive(anon):     2956 kB<br>
Active(file):     133988 kB<br>
Inactive(file):   230308 kB<br>
Unevictable:           0 kB<br>
Mlocked:               0 kB<br>
SwapTotal:       1046524 kB<br>
SwapFree:        1046524 kB<br>
Dirty:                60 kB<br>
Writeback:             0 kB<br>
AnonPages:        129588 kB<br>
Mapped:            47324 kB<br>
Shmem:              3804 kB<br>
Slab:             288172 kB<br>
SReclaimable:     251312 kB<br>
SUnreclaim:        36860 kB<br>
KernelStack:        4192 kB<br>
PageTables:        12756 kB<br>
NFS_Unstable:          0 kB<br>
Bounce:                0 kB<br>
WritebackTmp:          0 kB<br>
CommitLimit:     5131484 kB<br>
Committed_AS:    1010244 kB<br>
VmallocTotal:   34359738367 kB<br>
VmallocUsed:      174216 kB<br>
VmallocChunk:   34359550136 kB<br>
HardwareCorrupted:     0 kB<br>
AnonHugePages:     26624 kB<br>
HugePages_Total:       0<br>
HugePages_Free:        0<br>
HugePages_Rsvd:        0<br>
HugePages_Surp:        0<br>
Hugepagesize:       2048 kB<br>
DirectMap4k:       91968 kB<br>
DirectMap2M:     3053568 kB<br>
DirectMap1G:     7340032 kB<br>
```

If you also need to check your CPU, then you can read the file as:
<br>
```bash
>> cat /proc/cpuinfo
```
<br>

Or also there is the command: lscpu

ref: http://man7.org/linux/man-pages/man1/lscpu.1.html

2)
using the 'free' command:

Note: free command, only gives you info about the RAM memory.

Opertators:

-b : gives you the memory in bytes
-k : (default) gives you the memory in kibibytes (KiB)
-m : gives you the memory in mebibytes (MiB)
-t : displays a line containing the totals RAM + swap
-s : update every [delay] seconds. So if you command: >>free -s 5 ; this will update the results everty 5 seconds.
-c : use old format (no -/+buffers/cache line)
-l : shows low and high memory statistics
-V : displays version information.

```bash
>>:/$ free -m
             total       used       free     shared    buffers     cached
Mem:          7978        877       7100          3        151        208
-/+ buffers/cache:        517       7460
Swap:         1021          0       1021

>>/$ free -t -m
             total       used       free     shared    buffers     cached
Mem:          7978        883       7094          3        151        212
-/+ buffers/cache:        519       7458
Swap:         1021          0       1021
Total:        9000        883       8116
```


3)
using the `vmstat -s`

```bash
>>:/$ vmstat -s
      8169924 K total memory
       904828 K used memory
       272112 K active memory
       235444 K inactive memory
      7265096 K free memory
       155472 K buffer memory
       217684 K swap cache
      1046524 K total swap
            0 K used swap
      1046524 K free swap
        83855 non-nice user cpu ticks
            0 nice user cpu ticks
        24432 system cpu ticks
      1546417 idle cpu ticks
          452 IO-wait cpu ticks
            0 IRQ cpu ticks
          173 softirq cpu ticks
            0 stolen cpu ticks
       377179 pages paged in
        30568 pages paged out
            0 pages swapped in
            0 pages swapped out
      2092237 interrupts
      4823867 CPU context switches
   1486027825 boot time
       147016 forks
```


4)
Use the **top** programm.
There are also the **atop**, and **htop** programs, that have increased functionalities, but they don't usually come preinstalled in linux distros.



CHECKING WHAT IS IN YOUR CACHE AND BUFFER:

Use 'linux-ftools', to check what files are in your CACHE.

`>> fincore [options] files ...`

Options:

   --pages=false  Do no print pages.
   --sumarize     Prints a summary report
   --only-cached  Only prints stats, for files that actually are on the cache.
   
TODO: make example

TODO:  complete with: -- > http://unix.stackexchange.com/questions/87908/how-do-you-empty-the-buffers-and-cache-on-a-linux-system


5) 
If you want to know how much free memory you have in your hard disk, you have to use the commands:

· **df** command
· **du** command

TODO: COMPLETE




- If you want to have updated all the references to yor database repository, you should install mlocate, it will update the db once a day.

> sudo apt-get install mlocate

if it fails at start, try to 

> sudo updatedb

> sudo apt-get update

> sudo apt-get upgrade


## HOW DO I KNOW WHAT MODULES HAS MY LINUX

You can use the **lsmod** command, and it will give you the status of the present linux.

It reads from the file `proc/modules`, so you can also read it as: `cat /proc/modules`.

more on: https://www.computerhope.com/unix/lsmod.htm




Links:

http://www.linux.org/ <br>
http://www.debian.org/<br>
http://www.debian.org/<br>
http://www.ssc.com/lj/index.html<br>
http://www.amazon.com/The-Linux-Programming-Interface-Handbook/dp/1593272200<br>
https://lwn.net/<br>
http://www.linuxtoday.com/<br>
http://www.ssc.com/lg/<br>
https://buildroot.org/downloads/manual/manual.html<br>
http://www.tldp.org/LDP/LGNET/archives.html<br>
https://www.tux.org/<br>
http://www.dit.upm.es/~jmseyas/linux/kernel/hackers-docs.html<br>
https://www.gnu.org/manual/blurbs.html<br>
POSIX_SPEC: https://www2.opengroup.org/ogsys/catalog/t101<br>
POSIX_SPEC: http://pubs.opengroup.org/onlinepubs/9699919799/     <br>
http://www.linuxhowtos.org    <br>

<hr>
<br>
# UTILITIES.

https://www.gnu.org/software/gnu-c-manual/    <br>
https://www.gnu.org/software/indent/    <br>
https://www.gnu.org/software/inetutils/    <br>
https://www.gnu.org/software/libc/    <br>
https://gnupg.org/related_software/libgcrypt/    <br>
https://www.gnu.org/software/make/    <br>
http://www.gnu.org.ua/software/pies/    <br>
http://sqltutor.fsv.cvut.cz/cgi-bin/sqltutor    <br>
https://www.gnu.org/software/termutils/    <br>
https://www.gnu.org/software/time/    <br>
https://www.gnu.org/software/alive/    <br>
https://www.gnu.org/software/automake/    <br>
https://www.gnu.org/software/bash/    <br>
https://www.gnu.org/software/binutils/    <br>
https://www.gnu.org/software/c-graph/    <br>
http://twysf.users.sourceforge.net/    <br>
https://www.dwheeler.com/flawfinder/    <br>
https://www.gnu.org/software/cflow/    <br>
https://www.gnu.org/software/cgicc/    <br>
https://www.gnu.org/software/coreutils/coreutils.html    <br>
https://www.linux.com/learn/limit-cpu-usage-process-linux-cpulimit-tool    <br>

GNU ARM embedded toolchain:  https://launchpad.net/gcc-arm-embedded

C library for embedded systems:  https://sourceware.org/newlib/

binutils:  http://www.gnu.org/software/binutils/

GNU ARM TOOLCHAIN: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm

developers: https://launchpad.net/~gcc-arm-embedded-developers

gcc: http://gcc.gnu.org/

high-performance network programming in c.  http://www.linuxjournal.com/article/9815

FIO : flexible I/o testing: https://linux.die.net/man/1/fio

Linux Drivers for ADIC ICs: https://wiki.analog.com/resources/tools-software/linux-drivers-all

Independent magazine for Ubuntu users: https://fullcirclemagazine.org/













