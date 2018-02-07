 # Reference: man pages:

 - User commands: [:link:](http://man7.org/linux/man-pages/dir_section_1.html)
 - System calls: [:link:](http://man7.org/linux/man-pages/dir_section_2.html)
 - Library standard C: [:link:](http://man7.org/linux/man-pages/dir_section_3.html)
 - Devices [:link:](http://man7.org/linux/man-pages/dir_section_4.html)
 - Files systems [:link:](http://man7.org/linux/man-pages/dir_section_5.html)
 - Conventions & miscellaneous [:link:](http://man7.org/linux/man-pages/dir_section_7.html)
 - system Administration [:link:](http://man7.org/linux/man-pages/dir_section_8.html)
  
<hr>

At the console, is easy to get help if needed, checking the manual pages: for it the 'man' command is used:

```bash
> man pwd
```

well, this is actually a method from long ago, ... today it might just be easier to google it : )



In case something is not working properly, always have a go with with the following:

```bash
> sudo apt-get update
> sudo apt-get upgrade
```

maybe even re-index inmediatetly use:

```bash
>sudo updatedb
```

if you want to identify your system, you can try for:

```bash
> uname -a
```

or with:

```bash
>which wich
>/usr/bin/which
``` 

this at least tells us that the command is there and finds itself : )

If you want to be sure that a module is or isn't insalled you can use the following:

```bash
> cat /proc/modules | grep "gcc"
>
```

Actually the no-response, means, it is not present in the system.



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

## Starting with a Linux System.

Most commonly you would use an already designed Linux system, there are many chances that lenguage is set to english, and you must change it to you keyboard cofingurations. Just for reference: u should  run the following command:

```bash
$> del lang=es
```

You should change the 'es' to your langauge code. And rememember than in an english keyboard, the 'equal sign' is next to the back space key.

## Linux File System

The linux file system usually has the following file hierarchy structure:

 - **/** (top level directory, that is referenced as **'backslash'**)
    - **/bin** user binaries
    - **/sbin** system binaries
    - **/etc** configuration files
    - **/dev** device files*
    - **/proc** processes information
    - **/var** variable files (as logs)
    - **/tmp** temporary files
    - **/usr** user programms
    - **/home** home directorie
    - **/boot** bootloader files
    - **/lib** system libraries
    - **/opt** optional add-ons
    - **/mnt** mount directories
    - **/media** removable devices
    - **/srv** service data
    

Depending on the linux version, the list of the filesystem, may be different. 
    
### Commands to navigate through the file system.

- **pwd** command: identifie what is the current working directory.
- **cd** commands: it stands for 'change directory'. If 'cd' is used without arguments, it changes to the home/defaul directory. To move one step up in the file system hierarchy, the command 'cd ..' is used.
- **ls** command: it is teh 'listing' command, it enumerates all the files inside the current directory. When used with the parameter '-l', that stands for "long", it will define the files, with a lot of information about them ( permission, creation date, last used date ...) There are many options, for getting info about them, just type: 'man ls'. 
- **mkdir** command: creates a directory. (Make directory)
- **rmdir** command: removes a directory. (remove directory). **Note** rmdir only works, if the directory is empty. This is as a safety mechanisms.
- **cat** command: Output a file to the terminal.
- **head** command: Prints to the terminal the first 10 lines of a file.
- **last** and **tail** commands: print the last 10 lines of a file to the terminal.
- **cp** command: It copies a file.
- **mv** command: It moves a file (to another directory), also can be used to change the name of a file.

### Permisions

Files have owners (the user who created the file), and also access permissions.
 - read **r**
 - write **w**
 - execute **x**
 
So different permissions are defined for different users, or groups of users, so there are the following scope of permissions.
- user
- groups
- others (all users)

To view the permissions, usually the **ls -l** command is used.

```bash
$> ls -l 
file1  rwxr-x^-x 
```

- The first 3 characters are the user permissions: rwx
- The following 3 characters are the group permissions: r-x
- the last 3 characters are the permissions for all users.

### Root user

- the root account has the highest permission level, and it has access to everything.

- Sometimes it is needed to get all the permissions, for example when we want to install a program. For doing this we use the **sudo** command, it stands for "Switch User DO". To be possible to used the **sudo** command, the user must belong to the group: 'sudoers'.


### Processes

To view the processes that are running, the command **ps** is used. Using **ps** alone, will report the processes that are running from that shell. To check all the processes running in the machine, it is used: **ps -a**. Each proces can be identified by a PID (Process Identinfication Number). In case of need to abort a certain process, the command **kill** can be used.



  
### Memory análisis in linux systems
 
The analysis of the memory in the linux system, can be checked using the commands:

1)
Remember that the '/proc' filesystem is a pseudo-filesystem whose files provide an interface to kernel data structures.

reading the file: /proc/meminfo

```bash
>> less /proc/meminfo
or
>> cat /proc/meminfo

MemTotal:        8169924 kB
MemFree:         7274872 kB
Buffers:          154784 kB
Cached:           213312 kB
SwapCached:            0 kB
Active:           265184 kB
Inactive:         233264 kB
Active(anon):     131196 kB
Inactive(anon):     2956 kB
Active(file):     133988 kB
Inactive(file):   230308 kB
Unevictable:           0 kB
Mlocked:               0 kB
SwapTotal:       1046524 kB
SwapFree:        1046524 kB
Dirty:                60 kB
Writeback:             0 kB
AnonPages:        129588 kB
Mapped:            47324 kB
Shmem:              3804 kB
Slab:             288172 kB
SReclaimable:     251312 kB
SUnreclaim:        36860 kB
KernelStack:        4192 kB
PageTables:        12756 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     5131484 kB
Committed_AS:    1010244 kB
VmallocTotal:   34359738367 kB
VmallocUsed:      174216 kB
VmallocChunk:   34359550136 kB
HardwareCorrupted:     0 kB
AnonHugePages:     26624 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
DirectMap4k:       91968 kB
DirectMap2M:     3053568 kB
DirectMap1G:     7340032 kB
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
using the **'free'** command:

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


## Checking what is in your Cache and buffer

Use **'linux-ftools'**, to check what files are in your CACHE.

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


## How do I know what modules my linux system has:

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

bactraces:   https://www.gnu.org/software/libc/manual/html_node/Backtraces.html

For building distros:

HLFS - Hardened Linux From Scratch.
CLFS - Cross Linux From Scratch.
BLFS - Beyond Linux From Scratch.
LFS - Linux From Scratch. [http://www.linuxfromscratch.org/]










