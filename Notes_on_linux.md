 # Reference: man pages:

 - User commands: [:link:](http://man7.org/linux/man-pages/dir_section_1.html)
 - System calls: [:link:](http://man7.org/linux/man-pages/dir_section_2.html)
 - Library standard C: [:link:](http://man7.org/linux/man-pages/dir_section_3.html)
 - Devices [:link:](http://man7.org/linux/man-pages/dir_section_4.html)
 - Files systems [:link:](http://man7.org/linux/man-pages/dir_section_5.html)
 - Conventions & miscellaneous [:link:](http://man7.org/linux/man-pages/dir_section_7.html)
 - system Administration [:link:](http://man7.org/linux/man-pages/dir_section_8.html)
  
<hr>

time line of Unix based systems:   https://www.levenez.com/unix/

<hr>

At the console, is easy to get help if needed, checking the manual pages: for it the 'man' command is used:

```bash
> man pwd
```

well, this is actually a method from long ago, ... today it might just be easier to google it : )


there is other way, that is use the command: '**apropos** + topic' that will present you with a list of possible references.

other useful command is '**info** + topic' that presents you with a text with hyperlinks. 

also, in any command you can use the **--help** option: 'rm --help'


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

the local settings of the system can be identified with the command **locale**

```bash
>> locale
```


## Linux File System

The linux file system usually has the following file hierarchy structure:

 - **/** (top level directory, that is referenced as **'backslash'**)
    - **/bin** essential user command binaries
    - **/sbin** essential system binaries
    - **/etc** host specific configuration files
    - **/dev** device and special files
    - **/proc** kernel and processes informative file system: information about the system and running processes
    - **/sys** kernel and system information
    - **/var** variable files (as logs)
    - **/tmp** temporary files
    - **/usr** user programms
    - **/home** home directory
    - **/boot** bootloader files
    - **/lib** system libraries
    - **/opt** optional add-ons
    - **/mnt** mount directories
    - **/media** removable devices
    - **/srv** service data
    

Depending on the linux version, the list of the filesystem, may be different. 
    
The reference to this file structure, is defined at:  https://refspecs.linuxfoundation.org/FHS_3.0/fhs-3.0.pdf

This is known as a FHS: File Hierarchy Standard. - Usually systems want to comply with this standard, so the sowftware can predict the location of installed files and directories.


### Commands to navigate through the file system.

- **pwd** command: Stands for 'print working directory', and it prints the name the current working directory.
- **cd** commands: it stands for 'change directory'. If 'cd' is used without arguments, it changes to the home/defaul directory. To move one step up in the file system hierarchy, the command 'cd ..' is used. It can be used with absulute paths (all the path is defined related to root directory (/)) or relative paths (relative direction from the current directory).
- **ls** command: it is the 'listing' command, it enumerates all the files inside the current directory. When used with the parameter '-l', that stands for "long", it will define the files, with a lot of information about them ( permission, creation date, last used date ...) There are many options, for getting info about them, just type: 'man ls'. 
- **mkdir** command: creates a directory. (**M**a**k**e **dir**ectory)
- **rmdir** command: removes a directory. (remove directory). **Note** rmdir only works, if the directory is empty. This is as a safety mechanisms.
- **cat** command: Output a file to the terminal. -although it is intended to con*cat*enate files. It will print the concatenation of all files passed to it. 
- **head** command: Prints to the terminal the first 10 lines of a file.
- **last** and **tail** commands: print the last 10 lines of a file to the terminal.
- **cp** command: It copies a file.
- **mv** command: It moves a file (to another directory), also can be used to change the name of a file.
- **touch** command: creates a new file.


special directory names: 

- /  : root directory
- ~  : (tilde) user home directory
- .  : current directory
- .. : directory above current directory


### Commands for working with files.

- **touch**: creates a new file
- **output redirection: >**: it redirects, ex: echo "hello-world" > mytextfile.txt
- **output append >>**: it appends: echo "hello again!" >> mytextfile.txt
- **wc**: counts the number of lines, words and characters in a file.
- **grep**: search text through files and match patterns. [https://linux.die.net/man/1/grep]
- **file**: to find the location of files.
- **diff** and **sdiff**: identify differences between files.
- **md5**: computes the md5 hash of a file.
- **shasum**: compute the SHA-1 of a file.

### types of files in linux

It is possible to check the types of files with the command **ls -l**. Also with the command **file**

- -: regular file as text, images, or shared libraries...
- d: directory
- c: caracter device file
- b: block device file
- s: local socket file
- p: named pipe
- l: symbolic link

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

### Root user aka Superuser

- the root account has the highest permission level, and it has access to everything.

- Sometimes it is needed to get all the permissions, for example when we want to install a program. For doing this we use the **sudo** command, it stands for "Switch User DO". To be possible to used the **sudo** command, the user must belong to the group: 'sudoers'.


### Other users

  Using the commands **who** or **users** reports the current users logged into the system. the current users can be printed with the command **whoami**. 
  
  The command **su** lets you borrow the permissions from another user to run commands, if no user is especified, it defaults to use the **root** user.
 
 
### Sudoers

if a user needs to run a command with root privileges, it has to be added to the list of sudoes, so it can execute the **sudo** command.

in latest linux distributions you have to go to the file /etc/sudoers.d directorie and create a file, with the name of the user who needs to be granted access. 

in previous linux distributuions, you had to use the **visudo** program to add a line at the file /etc/sudoers. 

**NOTE**: The default command line prompt is dollar **$** for normal users and **#** for the root or superuser.


### LINUX GRAPHIC SYSTEM

There are three basic layers:

 - x window system (aka x11)
 - window manager
 - desktop manager
 
#### x window system - X11

 its inteded as a remote interface, so it is really a protocol, and it really is a X server. X comes from eXternal. It is supplied in X.org
 
 - x server: is what runs in the local machine.
 - x cliente: is what is being displayed, and can be anywhere.
 
 the basic configuration file used to be at: /etc/X11/xorg.conf
 
A new system that is replacing X11 is Wayland.

#### window manager

it controls the placement of the windows, tabs, controls ...

most commoon are: kwin(in KDE), mutter (in GNOME). Other like: fluxbox or fvwm work really good in systems with limited hardware. fluxbox and fvwm dont even need a desktop manager.

#### desktop managers

provides an visual enviroment, as taskbars, icons and access to applications, controls.

Examples:

- GNOME
- KDE 
- XFCE


### Package managers

package managers are programs that handle the installation, configuration, update or removal of diferent software applications of programs. Depending on the distribuitons, one or other is used.

 - Ubuntu – deb/dpkg
 - Red Hat – RPM and YUM
 - Solaris – pkgadd

#### APT (Advanced Packaging Tool) (Ubuntu)

It uses the file /etc/apt/sources.list to list which servers to download the packages from.

So the first thing is to update that file

 1- apt-get update
 2- apt-get upgrade
 3- apt-get install "package_name" 

#### YUM (RedHat)

It uses /etc/yum.repos.d/ to list which servers to download the packages from.

The first step is to update the sources

 1- yum update
 2- yum install "package_name"


### shells

there are several shells /command lines / terminals available in linux. 

those are defined in the file: /etc/shells


```bash
$ cat /etc/shells
/bin/sh
/bin/bash
/sbin/nologin
/bin/tcsh
/bin/csh
/bin/ksh
/bin/zsh
```

there are login shells (require login) and no-login shells.

their initialization depends in:

if            _**/etc/profile exists**_,    then it runs the shell
if            _**~/.bash_profile exists**_, then it runs the shell
else if       _**~/.bash_login exists**_,   then it runs the shell
else if       _**~/.profile exists**_,      then it runs the shell
on exit, if   _**~/.bash_logout exists**_,  then it runs the shell

In non-login shells, like bash, it checks just if  _**~/.bashrc**_ exists, then it runs the shell

**NOTE**: The default command line prompt is dollar **$** for normal users and **#** for the root or superuser.


#### Bash configuration

The bash console has a copy of the history of the commands we have issued, the comands are at: ~/.bash_history

Other useful file for the command console (terminal) is: ~/.bash_profile. This file keeps a serie of commands that runs everytime that
the terminal is launched


### Open-terminal

It is a programm that lets you open a terminal in any window from the desktop manager.

you can istall it with:

```bash
$ sudo yum install nautilus-open-terminal
$ sudo apt-get install Nautilus-open-terminal
```



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

command options:

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

```
>> fincore [options] files ...
```

Options:

   --pages=false  Do no print pages.
  
   --sumarize     Prints a summary report
   
   --only-cached  Only prints stats, for files that actually are on the cache.
   
TODO: make example

TODO:  complete with: -- > http://unix.stackexchange.com/questions/87908/how-do-you-empty-the-buffers-and-cache-on-a-linux-system


5) 
If you want to know how much free memory you have in your hard disk, you have to use the commands:

-  **df** command (for disk free?): this will report how much free memory has the filesystem. You usually invoque `df -h` the -h flag stands for "human readable".



 - **du** command (for disk usage?): reports an estimation of the file space usage.

TODO: COMPLETE


- If you want to have updated all the references to yor database repository, you should install mlocate, it will update the db once a day.

```
> sudo apt-get install mlocate
```

if it fails at start, try to 

```
> sudo updatedb

> sudo apt-get update

> sudo apt-get upgrade
```


6) **memsusage**: is a script that reports the memory consuption of a given program. http://man7.org/linux/man-pages/man1/memusage.1.html


## How do I know what modules my linux system has:

You can use the **lsmod** command, and it will give you the status of the present linux.

It reads from the file `proc/modules`, so you can also read it as: `cat /proc/modules`.

more on: https://www.computerhope.com/unix/lsmod.htm

# How to evaluate the startup of linux system

Bootchart is a tool for performance analysis and visualization of the GNU/Linux boot process. Resource utilization and process information are collected during the boot process and are later rendered in a PNG, SVG or EPS encoded chart.
http://www.bootchart.org/


# Run a script as a background daemon

it is possible with:

```bash
nohup node myscript.js > /dev/null 2>1 &
```

nohup:  doesn't allow termination of the process even in the event the stty is finished (the console/shell) 
/dev/null : the output of the process goes to the null-device (shinkhole).
2>&1 : stderr is redirected to stdout -- in this case stdout already is redirected to /dev/null --
& : run the process in the background (as a daemon)


# Nmap

Nmap is the abreviation of Net Mapping an is a tool for network explorations, thus I is heavily used also to check network scanning and security.

reference: https://nmap.org/


the following stands for IPv4:

#### for scanning an IP:

```bash
$>nmap 192.168.0.15
```

to identify the OS 

```bash
$>nmap -v -A 192.168.0.15
```
to detect if the host is behind a firewall

```bash
$>nmap -sA 192.168.0.15
```

to 'have a peak' for a host behind a firewall

```bash
$>nmap -PN 192.168.0.15
```

#### for scanning with a host name

```bash
$>nmap -v host_name
```

#### for scanning within an IP range

```bash
$> nmap192.168.0.1-10
```

or using a wild card

```bash
$>nmap 192.168.0*
```
to exclude a given:

```bash
$>nmap 192.168.0*  --exclude 192.168.1.5
```


#### ping discovery

```bash
nmap -sP 192.168.1.0/24
```



# INSTALLING NGINX

```bash
$> sudo apt-get install nginx
... 
$> sudo /etc/init.d/nginx
```
reference for nginx:  http://nginx.org/en/docs/

for nginx configuration check:

https://www.nginx.com/resources/wiki/start

https://www.nginx.com/resources/wiki/start/topics/tutorials/config_pitfalls

https://wiki.debian.org/Nginx/DirectoryStructure


# INSTALLING NODE.JS

```bash
pi@raspberrypi:~ $ sudo apt-get install nodejs
Lleendo llista de paquetes... Fecho
Creando árbol de dependencies
Lleendo información d'estáu... Fecho
nodejs is already the newest version (4.8.2~dfsg-1).
nodejs axustáu como instaláu manualmente.
0 actualizaos, 0 nuevos instalaos, 0 para desaniciar y 1 nun actualizaos.
```

# INSTALLING VIRTUAL ENVIROMENT:

this is like a chroot.- 

```bash
$>sudo apt-get install python-virtualenv
```

then we have to set up the folder for our virtualenv

```bash
$ourpath>virtualevn myvirtualenv
```

```bash
$>sudo pip3 install virtual env
```

to run the virtual enviroment

```bash
$>sudo . /var/www/app/venv/bin/activate
```

# INSTALLING FLASK
```bash
(vevn)$: sudo pip3install flask
```

# INSTALLING uWSGI

reference: https://uwsgi-docs.readthedocs.io/en/latest/


# how to list all installed programs

```bash
$: dpkg -l
```

## How to instal ncurses

```bash
Z>sudo apt-get install libncurses5-dev libncursesw5-dev
```

ref: https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/


## How to install qt4

```bash
$> sudo apt-get install qt4-qmake libqt4-dev
```

http://doc.qt.io/archives/qt-4.8/install-x11.html

or 

https://stackoverflow.com/questions/47465878/install-qt-4-ubuntu-17-04

# BUILDROOT

http://buildroot.net/downloads/manual/manual.html#_advanced_usage


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
https://distrowatch.com/
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

http://linuxfreedom.com
https://distrowatch.com/
https://www.linux.com/news/learn/sysadmin/best-linux-distributions-2017

For building distros:

HLFS - Hardened Linux From Scratch.
CLFS - Cross Linux From Scratch.
BLFS - Beyond Linux From Scratch.
LFS - Linux From Scratch. [http://www.linuxfromscratch.org/]


## ABOUT OPEN SOURCE SOFTWARE LINCESES.

Mainly there are two types of licenses: restrictive and permisive

restrictive licenses: derivative works are intended to remain open, and changes must be made availables. Example: GPL (general public license) (aka copyleft)

permisive licenses: like BSD or Apache licenses. - dont need to be make public.




