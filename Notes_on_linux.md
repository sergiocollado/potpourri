# Reference: man pages:

 - User commands: [:link:](http://man7.org/linux/man-pages/dir_section_1.html)
 - System calls: [:link:](http://man7.org/linux/man-pages/dir_section_2.html)
 - Library standard C: [:link:](http://man7.org/linux/man-pages/dir_section_3.html)
 - Devices [:link:](http://man7.org/linux/man-pages/dir_section_4.html)
 - Files systems [:link:](http://man7.org/linux/man-pages/dir_section_5.html)
 - Conventions & miscellaneous [:link:](http://man7.org/linux/man-pages/dir_section_7.html)
 - system Administration [:link:](http://man7.org/linux/man-pages/dir_section_8.html)
  
<hr>

In the case there are reference to several of the previous chapters, those references are indicated within a parenthesis, ie:

swapoff(8) and swapoff(2)

https://linux.die.net/man/8/swapoff

https://linux.die.net/man/2/swapoff

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
>> https://linuxgazette.net/archives.html <br>
GNU ARM embedded toolchain:  https://launchpad.net/gcc-arm-embedded <br>
https://linuxgazette.net/archives.html <br>
kernel parameters: https://www.mjmwired.net/kernel/Documentation/kernel-parameters.txt <br>

secure programming: https://dwheeler.com/secure-programs/Secure-Programs-HOWTO.pdf

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

-  /etc/passwd   - users account informations
-  /etc/shadow   - secure info account for user
-  /etc/group    - group account information.
-  /etc/gshadow  - secure group account information.
-  /etc/shells   - shells defined in the system.
-  /etc/nologin  - If the file /etc/nologin exists and is readable, login(1) will allow access only to root.  Other users will be shown the contents of this file and their logins will be refused.  This provides a simple way of temporarily disabling all unprivileged logins.
-  /etc/services  - The /etc/services file is used by applications to translate human-readable service names into port numbers when connecting to a machine across a network. 
-  /etc/fstab     - the information required to specify mount points, options, devices, etc.

### Commands to navigate through the file system.

- **pwd** command: Stands for 'print working directory', and it prints the name the current working directory.
- **cd** commands: it stands for 'change directory'. If 'cd' is used without arguments, it changes to the home/defaul directory. To move one step up in the file system hierarchy, the command 'cd ..' is used. It can be used with absulute paths (all the path is defined related to root directory (/)) or relative paths (relative direction from the current directory).
- **ls** command: it is the 'listing' command, it enumerates all the files inside the current directory. When used with the parameter '-l', that stands for "long", it will define the files, with a lot of information about them ( permission, creation date, last used date ...) There are many options, for getting info about them, just type: 'man ls'. 
- **mkdir** command: creates a directory. (**M**a**k**e **dir**ectory)
- **rmdir** command: removes a directory. (remove directory). **Note** rmdir only works, if the directory is empty. This is as a safety mechanisms.
- **cp** command: It copies a file.
- **mv** command: It moves a file (to another directory), also can be used to change the name of a file.
- **touch** command: creates a new file or updates it last edition time.


special directory names: 

- /  : root directory
- ~  : (tilde) user home directory
- .  : current directory
- .. : directory above current directory


**NOTE**: A path which begins with **/** is considered absolute because it specifies the exact filesystem location. Otherwise, it is considered relative and it is implicitly assumed your current directory is prepended.


### Commands for working with files.

- **touch**: creates a new file or updateds the edition time of the file
- **output redirection: >**: it redirects, ex: echo "hello-world" > mytextfile.txt
- **output append >>**: it appends: echo "hello again!" >> mytextfile.txt
- **echo**: prints text. Usually is used with the redirecton and append operators: **>** and **>>**. the **-e** option is used so special character can be used, as: \t for tabulation or \n for a new line. It is very useful also to print the value of enviromental variables, like: echo $USERNAME.
- **file**: report information about a file.
- **wc**: counts the number of lines, words and characters in a file.
- **more**: prints a screen from a text file.
- **less**: prints a screen from a text file. Less has more options that the **more** command, following the saying: *less is more*
- **grep**: search text through files and match patterns. [https://linux.die.net/man/1/grep]
- **file**: to find the location of files.
- **diff** and **sdiff**: identify differences between files. usually use: **diff -Nur**
- **md5**: computes the md5 hash of a file.
- **shasum**: compute the SHA-1 of a file.
- **cat** command: print a file to the terminal. -although it is intended to con**cat**enate files. It will print the concatenation of all files passed to it. 
- **tac** this is **cat** spelled backwards. prints the lines of a file in reverse order : )
- **head** command: Prints to the terminal the firsts lines of a file.
- **tail** command: prits the last lines from a file. It is really usefull to check files that update in real time, as system logs or alike. Usually using *tail -f filename*. this will print all the new lines into the file, and the monitor the activity in the file.
- **last** and **tail** commands: print the last 10 lines of a file to the terminal.
- **sed**: stands for *stream editor*. it takes a file or a stream through a pipe as an input. and it is a really powerful text processor utility
- **awk**: it is an extractor utility
- **zcat, zless, zdiff, zgrep**: working with compressed files. those commands are designed to work with compressed files, in the same what that their regular commands counterparts.
- **grep, egrep, fgrep** - print lines that match patterns http://man7.org/linux/man-pages/man1/grep.1.html
- **sort**  - sort lines of text files  http://man7.org/linux/man-pages/man1/sort.1.html
- **uniq**  - report or omit repeated lines http://man7.org/linux/man-pages/man1/uniq.1.html
- **paste** - merge lines of files  http://man7.org/linux/man-pages/man1/paste.1.html
- **join** - join lines of two files on a common field  http://man7.org/linux/man-pages/man1/join.1.html
- **split** - split a file into pieces http://man7.org/linux/man-pages/man1/split.1.html
- **cut** - extracts columns frot text data files. It is used for manipulating column-based files and is designed to extract specific columns. http://man7.org/linux/man-pages/man1/cut.1.html


### types of files in linux

It is possible to check the types of files with the command **ls -l**. Also with the command **file**

- -: regular file as text, images, or shared libraries...
- d: directory
- c: caracter device file
- b: block device file
- s: local socket file
- p: named pipe-. this are FIFOS and used for interprocess communications.
- l: symbolic link

caracter device files and block device files are two different data structures that represents periphericals or hardware devices or IO ports. Those are almost always placed in the devices folder: **/dev**.

TODO: add info about stiky  bits

the **file** utility can be used to get more information about the data type of a file

NOTE! in linux extensions dont define the utility or type of a file.

### Permisions

Files have owners (the user who created the file), and also access permissions.

So different permissions are defined for different users, or groups of users:
- user
- groups
- others (all users)

the permission model that linux follows is known as DAC, Direct Acess Control.

Permissions can be expressed in numeric for with octal notation, so values are given with digits from 0 to 7.

 - read **r**     (1)
 - write **w**    (2)
 - execute **x**  (4)
 
 
To view the permissions, usually the **ls -l** command is used.

```bash
$> ls -l 
file1  rwxr-x^-x 
```

- The first character will be a **d** in that case, it is a directory. or a **b** or **c** in case of a external device.
- The following 3 characters are the user permissions: rwx
- The following 3 characters are the group permissions: r-x
- the last 3 characters are the permissions for all users.


### Root user aka Superuser

- the root account has the highest permission level, and it has access to everything.

- Sometimes it is needed to get all the permissions, for example when we want to install a program. For doing this we use the **sudo** command, it stands for "Switch User DO". To be possible to used the **sudo** command, the user must belong to the group: 'sudoers'.


### Other users

  Using the commands **who** or **users** reports the current users logged into the system. the current users can be printed with the command **whoami**. 
  
  The command **su** (**switch user**)lets you borrow the permissions from another user to run commands, if no user is especified, it defaults to use the **root** user.
  
  Every user in a linux system is defined by a user ID and also a group ID. For most linux flavors, the first user is defined as user ID = 1000 and the following defined user follow that number. The super user has a user ID of 0.
  
  for handling user, relevant files are _**/etc/passwd**_ and _**/etc/group**_. 
  
  Groups are groups of users that share common privileges in folder and files.
 
  For a given user all his files will be kept in the folder _**/home/user_name**_.
  
  To create a new user, the **useradd** command is used, and to remove one the **userdel** command is used, to modify a user account the **usermod** command is used. (-p flag to change a password). 
  
  
  - useradd - create a new user or update default new user information. the password must be added with other command - https://linux.die.net/man/8/useradd
  - userdel - delete a user account and related files - https://linux.die.net/man/8/userdel
  - usermod - modify a user account - http://man7.org/linux/man-pages/man8/usermod.8.html
  - passwd  - add or changes the password to a user - http://man7.org/linux/man-pages/man1/passwd.1.html
  
  Each user is identified by a uid (user identification).
  
  Users are added to groups with the **usermod** command, with the **-g** or **-G** options.
  
  To check the users in a system, you can check with: 'sudo cat _**/etc/password'**_. If you want to edit that file, it will need to use the command **'vipw'**, that will lock that file for other users. Also is possible that it will be necessary to exit the file _**/etc/shadow**_ for consistency, and that can be done with the command **'vipw -s'**.
  
  
#### User directories

In most linux distributions, the directories for the different users are placed in: _**/home/my_user**_

Any user can change his enviroment variable HOME, so it points to whereever he wants, as his root directorie

The _**tilde**_: **~**,  represents the home directorie for any user in the terminal.

#### groups

groups allow users to be part of a groups. groups in linux allow to have different rights or permitions over given files or resources.

- groupadd - create a new group http://man7.org/linux/man-pages/man8/groupadd.8.html
- groupdel - delete a group http://man7.org/linux/man-pages/man8/groupdel.8.html
- groupmod - modify a group definition on the system http://man7.org/linux/man-pages/man8/groupmod.8.html

to add a given user to a group, is done:

```bash
> sudo usermod -a -G groupname username
```

### Sudoers and sudo

The **sudo** command lets users to run priviliged commands. But that user must be first allowed to use the **sudo** command.

if a user needs to run a command with root privileges, it has to be added to the list of sudoes, so it can execute the **sudo** command, and then it will be able to use privileged commands. So with **sudo** it is possible for a user to run programs with the privileges of another user, tipically the superuser (root)

This is done through the sudoers file.

In linux distributions you have to go to the file _**/etc/sudoers.d**_ directorie and create a file, with the name of the user who needs to be granted access. 

In linux distributions, you had to use the **visudo** program to add a line at the file /etc/sudoers. The sudoers file, cannot or must not be edited with a normal text editor.

ref: https://linux.die.net/man/5/sudoers
ref: https://linux.die.net/man/8/visudo

**NOTE**: The default command line prompt is dollar **$** for normal users and **#** for the root or superuser.

the command sudo:
 - keeps a log of every time it has been used
 - which user used the command
 - timestamp
 - directory in which it was ran.



### commands to change permissions and ownership

- **chmod** change permissions of a file
- **chown** change ownership of a file
- **chgrp** change group ownership

the possible values are:

- 1 execute permission
- 2 write permision
- 4 read permission

and from summing up the previous ones:

- 5 read/execute permissions
- 6 read/write permissions
- 7 read/write/execute permision

so the command:

- _**chmod 755**_, give the user read/write/execute permissions, and to the group and rest of the world read/execute permissions.
- _**chmod 666**_, gives read write permissions for everybody.
- _**chmod 744**_, the user can read/write/execute, and the rest on user can only read the file.

### how to check users and groups

one option is to chech the files:

 - /etc/passwd
 - /etc/group

```bash
>sudo cat /etc/passwd
>sudo cat /etc/group
```

### default permissions: umask

ref: http://man7.org/linux/man-pages/man1/umask.1p.html

New files are created with a default set of permissions. Specifically, a new file's permissions may be restricted in a specific way by applying a permissions "mask" called the **umask**. The umask command is used to set this mask, or to show you its current value.

to get the default permissions, just type the command: umask

```bash
>umask
0002
``` 
to change the default permissions to read/write permissions for everybody.

```bash
>umask 0666
```

## Commands for monitoring the performance, memory

- top - prints the proceses : top(1) http://man7.org/linux/man-pages/man1/top.1.html
- uptime - how long has the system been running and its load. uptime(1) https://linux.die.net/man/1/uptime
- ps - information about the processes - http://man7.org/linux/man-pages/man1/ps.1.html
- pstree - ps in a tree http://man7.org/linux/man-pages/man1/pstree.1.html
- mpstat - statistics for multiple processors http://man7.org/linux/man-pages/man1/mpstat.1.html
- iostat - cpu info and statistics
- trace - info about system call and traces
- pmap - info about process memory stats http://man7.org/linux/man-pages/man1/pmap.1.html
- vmstats -info about the virtual memory statistics, and block I/O. http://man7.org/linux/man-pages/man1/pmap.1.html
- free  - info about meomry usage: free(1) http://man7.org/linux/man-pages/man1/free.1.html
- uname - print system information, like kernel version, hardware, operating systen. https://linux.die.net/man/1/uname
- iostat - cpu utilization and I/O statistics. iostat(1) http://man7.org/linux/man-pages/man1/iostat.1.html
- iotop - I/O statistics including per process iotop(8) http://man7.org/linux/man-pages/man8/iotop.8.html
- sar - system activity. sar(1) http://man7.org/linux/man-pages/man1/sar.1.html
- vmstat - detail of the virtual memory statistics and IO. vmstat(8) http://man7.org/linux/man-pages/man8/vmstat.8.html
- systemctl: report the system programs. http://man7.org/linux/man-pages/man1/systemctl.1.html

### MOUNTING FILE SYSTEMS

In linux all the files are under the tree that starts in **/**

to mount a partition, it is possible to use the command: **mount**  https://linux.die.net/man/8/mount
it follows:

```bash
$ sudo mount [-t type] [-o options] device dir
```
executing **mount** without options, prints a list of the current mounted filesystems.

In the file:  /etc/fstab - is stated the information required to specify mount points, options, devices, etc.

### physical volumes

the command **pvdisplay** allows you to see the attributes of one or more physical volumes like size, physical extent size, space used for the volume group descriptor area and so on.


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
 
 you can use: 'rpm -qa' (query all) for a list of all the packages in the system.

#### YUM (RedHat)

It uses /etc/yum.repos.d/ to list which servers to download the packages from.

The first step is to update the sources

 1- yum update
 2- yum install "package_name"


### shells

there are several shells /command lines / terminals available in linux. 

http://man7.org/linux/man-pages/man1/bash.1.html


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

http://man7.org/linux/man-pages/man1/login.1.html

their initialization depends in:

if            _**/etc/profile**_ exists,    then it runs the shell

else if       _**~/.bash_profile**_ exists, then it runs the shell

else if       _**~/.bash_login**_ exists,   then it runs the shell

else if       _**~/.profile**_ exists,      then it runs the shell

on exit, if   _**~/.bash_logout**_ exists,  then it runs the shell

In non-login shells, like bash, it checks just if  _**~/.bashrc**_ exists, then it runs the shell

**NOTE**: The default command line prompt is dollar **$** for normal users and **#** for the root or super-user.


### Enviromental Variables

these are definitions that might be used for several goals. Many applications use them to define default settings.

Most common are:  HOST, HOME, PATH, PS1, CDPATH, CWD, USERNAME, VISUAL

They can be set like: 'PATH=$HOME/BIN:$PATH'

To check all defined enviroment variables, you can type: env, or export.

to make abailable the env var in other directories, they must be exported.

```bash
MYVAR=value;
export VAR;
``` 
PATH, is the enviromental varible that defines the order in which directories will be checked for looking for programs. those directories will be checked from the begining to the end.

you can check its value, with:

```bach
>echo $PATH
>echo $USERNAME
```

#### Bash configuration

The bash console has a copy of the history of the commands we have issued, the comands are at: ~/.bash_history

Other useful file for the command console (terminal) is: ~/.bash_profile. This file keeps a serie of commands that runs everytime that
the terminal is launched

### Customizing the prompt

This can be done through the enviromental varialbe PS1

### Open-terminal

It is a programm that lets you open a terminal in any window from the desktop manager.

you can istall it with:

```bash
$ sudo yum install nautilus-open-terminal
$ sudo apt-get install Nautilus-open-terminal
```

## BASH SCRIPTING

ref: http://linuxcommand.org/lc3_learning_the_shell.php

### LAUNCH A BASH SCRIPT

there are two ways

- run the command:'bash myscript.sh'
- run the commmand: './myscript.sh'

of course, for running that script, the required execution permissions are needed. It not, the permmissions need to be changed with 'chmod'

```bash
chmod +x myscript.sh
```

### SHABANG

The scripts must start by a line, that points to the interpreter of that file. That file is known as shabang.

```bash
#!/bin/sh
```
It is possible to define an option to verify that your script is running, for this use:

```bash
#!/bin/sh +x 
```
then the script will be printed in the screen as it is executed.


### SCRIPT ARGUMENTS

there are special enviroment variables for the script

- $0 the command name
- $1 the first argument
- $2 the second time
- $* represents all the arguments 
- "$@" represents all the argumemts keeping the grouping of quoted argumets
- $# represents the number of arguments given
- $? retains the value of the last executed command

## BASH COMMANDS

### comments

all that follows a # is a comment

### variables

variables are defined with the equal operator (=), and its value is returned, with the dolar simbol operator $.
And to print its value, is common to use a echo $variable.

```bash
myname="Sergio"
echo "hello $myname !"
```

### expr and bc

expr evaluates mathematicals expressions

a more powerfull program is bc, for Bench Calculator https://linux.die.net/man/1/bc

```bash
expr 5 +1 
expr 25 / 5
expr 33 % 5
echo "27/35" | bc -l
```
### user inputs

The command 'read' can be used to get user input.

```bash
#!/usr/bin/env bash

echo "Whats your name"
read -n  yourname
echo "hello $yourname"


that "-n" given to the echo command causes it to keep the cursor on the same line; i.e., it does not output a linefeed at the end of the prompt.


```bash
#!/bin/bash

number=0

echo -n "Enter a number > "
read number
```

### script flow control

### ifS

if commands; then
commands
[elif commands; then
commands...]
[else
commands]
fi

### tests

The test command is used most often with the if command to perform true/false decisions. The command is unusual in that it has two different syntactic forms:

#### First form

test expression

#### Second form

[ expression ]
       
The test command works simply. If the given expression is true, test exits with a status of zero; otherwise it exits with a status of 1.


#### conditional executions

the result status of the last command or program is always stored in the variable '$?'

so a true condition returns 0, and a false condition returns 1.

AND operator is &&. the term at the right will only be executed if the term in the left is true.

OR operator is ||.  the term at the right will only be executed if the term in the left is false.


#### conditional expressions

Conditionals expressions are indicated a condition inside double brackets. 

the possible operators are:

| condition value operator| text | 
| :---         |     :---:      |  
| -gt  | greater than     | 
| -ge   | greater than or equal    | 
| -eq   | equal   | 
| -neq  | not equal     | 
| -le   | less than or equal     | 
| -lt   | a file exits     |
| -e   | a directory exits  | 
| -d   | length of a String is zero    |
| -z   | Length of a string is non-zero     | 


| condition file evaluations| text | 
| :---         |     :---:      |  
| -e file | file exists?   | 
| -d file  | file is a directory?   | 
| -f file   | file is a regular file?   | 
| -L file   | file is a symbolic link file?   | 
| -s file | file has a non-zero size?| 
| -g file    | has file  a sgid defined? | 
| -u file   | has file a guid defined?    |
| -r file  | is file readable by you?  | 
| -w file   | is file writeable by you? |
| -x file   | is file executable by you?   | 
| file1 -nt file2  | file1 is newer than file2?  | 
| file1 -ot file2  | file1 is newer than file2?  | 
| -w file   | is file writeable by you? |
| -x file   | is file executable by you?   | 



| condition for string evaluations| text | 
| :---         |     :---:      |  
| string | is it non empty? | 
| string1 == string2 | equals?  | 
| string1 != string2   | different?   | 
| -n string | not null or empty?| 
| -z string    | is the string null? | 



### Processes

To view the processes that are running, the command **ps** is used. Using **ps** alone, will report the processes that are running from that shell. To check all the processes running in the machine, it is used: **ps -a**. Each proces can be identified by a PID (Process Identinfication Number). In case of need to abort a certain process, the command **kill** can be used.

### NETWORKING

**ifconfig** - presents the current network configuration

normally ethernet intefaces are named as eth0,eth1... and wireless interfeaces as wlan0,wlan1... although nowadays, the diferent distros use to use the **Predictable Network inteface Device Names**

https://www.freedesktop.org/wiki/Software/systemd/PredictableNetworkInterfaceNames/

the configuration file is: _**/etc/sysconfig/network-scripts/ifcfg-exnoXXXX**_

statistical info is in the file:  _**/proc/net/dev**_ and also in the files: _**sys/class/net/ethX/statistics**_


enoXXXX - ethernet onboard

lo -- loopback adress

to change the ip address, you must command:

```bash
sudo ifconig enoXXXXX 192.1new_ip_address netmask 255.255.255.0
```

to check the route - (shows the way to the next hub)

```bash
route
```
to change the route, you have to command:

```bash
route add 192.34X.xxx.xxx enoXXXX
```

to check everything is ok. you can ping adresses

```bash
ping 192.xxx.xxx.xx
```

```bash
ping google.com
```

to configure the network interface to be persistant, you have to edit the file _**/etc/sysconfig/network-scripts/ifcfg-enoXXX**_

so we can change the BOOTPROT (ocol) to static, and add the address information and netmask.

```
BOOTPROTO=
IPADDR=192.168.XXX.XXX
NETMASK=255.255.255.xxx
```

to launch a network connection and attach it to a ip address, you do like:

```bash
$ sudo /sbin/ifconfig eth0 up 192.168.1.123
```

if you want to request a dynamic IP is done like

```bash
$ sudo /sbin/ifconfig eth0 up
$ sudo /sbin/dhclient eth0
```

the usual command used to be 'ifconfig', although nowadays the new utility 'ip' seems to be an improved version and is more efficient

https://linux.die.net/man/7/netlink

https://linux.die.net/man/2/ioctl


the ip command can be used for many tasks like: manipulate routing, devices, policy routing and tunnels

https://linux.die.net/man/8/ip

its basic sintaxis is: 

ip [ OPTIONS ] OBJECT { COMMAND | help }

so, if you need to print all the network interfaces:

```bash
 ip link
``` 
 to check the info of one network interface.

```bash
$ ip -s link show ethX
```
 
to define the ip for a newtork interface
```bash
$ sudo ip addr add 192.168.1.7 dev ethX
```
 
to bring down a network interface
```bash
$ sudo ip link set eth0 down
```
 
to set the MTU (Maximun Transmision Unit) for a given network interface
```bash
$ sudo ip link set eth0 mtu 1480
```

to define a network route:
```bash
$ sudo ip route add 172.16.1.0/24 via 192.168.1.5
```



Some playbook options are:

### with 'ip'

get basic info about connection eth0

```bash
$ ip addr show eth0
```
change its address
Bring down eth0 and reconfigure to use a static address instead of DCHP,
```bash
$ sudo ip link set eth0 down 
$ sudo ip addr add 192.168.1.200 dev eth0 
$ sudo ip link set eth0 up
```

Bring the interface back up.
```bash
$ sudo ip link set eth0 up 
$ sudo dhclient eth0
```
check everything works as expected  after reboot
```bash
$ sudo reboot
```

### with ifconfig

get knowledge about the connection
```bash
 $ ifconfig eth0
```

change its address
```bash
$ sudo ifconfig eth0 down 
$ sudo ifconfig eth0 up 192.168.1.100
```

define a dhcp into it
```bash
$ sudo ifconfig eth0 up 
$ sudo dhclient eth0
```

test if it works after reboot.
```bash
$ sudo reboot
```

#### more about networking

 - netstat: network statistics - https://linux.die.net/man/8/netstat
 - iptraf: info about network interfaces - Interactive Colorful IP LAN Monitor - https://linux.die.net/man/8/iptraf
 - tcpdump & wireshark analysys of network and traffic


### check system file system

to verify the system file system:

```bash
cat /proc/filesystem | less
```



### Memory analisys in linux systems

 https://akkadia.org/drepper/cpumemory.pdf
 
 **free** - Display amount of free and used memory in the system - https://linux.die.net/man/1/free
 **df** - report file system disk space usage  https://linux.die.net/man/1/df
 
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

Or also there is the command: **lscpu**

ref: http://man7.org/linux/man-pages/man1/lscpu.1.html

2)
using the **'free'** command:

Note: free command, only gives you info about the RAM memory.

command options:

 - b : gives you the memory in bytes
 - k : (default) gives you the memory in kibibytes (KiB)
 - m : gives you the memory in mebibytes (MiB)
 - t : displays a line containing the totals RAM + swap
 - s : update every [delay] seconds. So if you command: >>free -s 5 ; this will update the results everty 5 seconds.
 - c : use old format (no -/+buffers/cache line)
 - l : shows low and high memory statistics
 - V : displays version information.

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

the cache can be released, writting into the 

```bash
>sudo su
>echo 3 > /proc/sys/vm/drop_caches
>exit
```

to view what the system is usign the swap areas for:

```
cat /proc/swaps
```

more swap commands:

**mkswap**, **swpaon**, **swapoff**.-

https://linux.die.net/man/8/swapoff

https://linux.die.net/man/2/swapoff

https://opensource.com/article/18/9/swap-space-linux-systems


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

https://akkadia.org/drepper/cpumemory.pdf


## system monitoring

- uname - print system information, like kernel version, hardware, operating systen. https://linux.die.net/man/1/uname
- sar:Collect, report, or save system activity information.  https://linux.die.net/man/1/sar
- iotop - simple top-like I/O monitor  https://linux.die.net/man/1/iotop
- vmstat - Report virtual memory statistics https://linux.die.net/man/8/vmstat
- iostat - Report Central Processing Unit (CPU) statistics and input/output statistics for devices, partitions and network filesystems (NFS). https://linux.die.net/man/1/iostat
- top- display Linux tasks
- ps - report a snapshot of the current processes - https://linux.die.net/man/1/ps
- pstree - display a tree of processes  - https://linux.die.net/man/1/pstree
- pmap - report memory map of a process - https://linux.die.net/man/1/pmap
- systemctl -


### system logs

 system logs are usually in the folder _**/var/log/messages**_. Usually those files are handled  by the syslogd daemon. the program **logrotate** usually hadles the rotation of those logs, so they dont keep on getting bigger without limits. Its configuration file is in **/etc/logrotate.conf**. the boot related messages are in _**/var/log/boot.log**_, the security related are in _**/var/log/secure.log**_
 
 ```bash
 tail -f /var/log/messages
 ```
 
 kernel messages are printed with: 

```bash
dmesg -w
```



## How do I know what modules my linux system has:

You can use the **lsmod** command, and it will give you the status of the present linux.

you usually command:

```bash
> lsmod | less
```

It reads from the file `proc/modules`, so you can also read it as: `cat /proc/modules`.

```
sudo cat /proc/modules
```

more on: https://www.computerhope.com/unix/lsmod.htm

Also the commmand **modinfo** shows information about the kernel modules: https://linux.die.net/man/8/modinfo

other module-related commands are: **insmod**, **modprobe**, 

- lsmod - program to show the status of modules in the Linux Kernel. https://linux.die.net/man/8/lsmod
- modinfo - presents info about the modules the kernel is using. https://linux.die.net/man/8/modinfo
- modprobe - program to add and remove modules from the Linux Kernel. https://linux.die.net/man/8/modprobe
- insmod - simple program to insert a module into the Linux Kernel. https://linux.die.net/man/8/insmod

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

## for Real time

 - ionice - get/set program io scheduling class and priority https://linux.die.net/man/1/ionice
 - heartbeat - Heartbeat subsystem for High-Availability Linux https://linux.die.net/man/8/heartbeat
 - uptime - Tell how long the system has been running.
 
 http://www.admin-magazine.com/Articles/Law-of-Averages-Load-Averaging <br>
 https://people.seas.harvard.edu/~apw/stress/   <br>
 http://smackerelofopinion.blogspot.com/2014/06/stress-ng-updated-system-stress-test.html   <br>
  watchdog: https://mmonit.com/monit/   <br>
  
#### how to create timers:

 timer_create - create a POSIX per-process timer  http://man7.org/linux/man-pages/man2/timer_create.2.html
 
 timerfd_create, timerfd_settime, timerfd_gettime--timers that notify  via file descriptors, http://man7.org/linux/man-pages/man2/timerfd_create.2.html 

 
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

# kernel messages

kernel messages are printed with: 

```bash
dmesg -w
```

# system logs

you can use the following command:

```bash
$ sudo tail -f /var/log/messages
```

also syslogs: https://linux.die.net/man/3/syslog
also: https://linux.die.net/man/5/syslog-ng.conf

# kernel panic 

kernel panic is the name of the error known in witch the OS has a hard time recovering.

reference: https://searchdatacenter.techtarget.com/definition/Linux-kernel-panic


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

# HOW TO INSTALL GIT

to know if it is already installed

```bash
$ which git
```

```bash
$ sudo apt-get install git-core git-gui gitweb cgit gitk git-daemon-run \
                       git-cvs git-svn
```

```bash
$ sudo yum list git*
$ sudo yum install git* cgit
```

## git commands

- git --version
- git
- git --help [command]
- git help --all
- git status
- git init
- git add (file)
- git config user.name
- git config user.email
- git commit -m (message)
- git log
- git diff
- git rm
- git mv
- git ls-files
- git revert
- git reset
- git gc
- git fsck
- git prune
- git blame
- git bisect
- git branch
- git merge
- git clone
- git push
- git fetch
- git pull
- git show-branch
- git checkout
- git rebase
- git show
- git tag
- git daemon
- git format-patch
- git am


# GERRIT

ref: https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html

# BUILDROOT

http://buildroot.net/downloads/manual/manual.html#_advanced_usage

# GRUB

Its basic configuration file is at: /boot/grub/grub.cfg or /boot/grub2/grub.cfg, those are related to /etc/grub.d and /etc/default/grub
Those file will generate the ones under /boot, when is run update-grub or grub2-mkconfig

 - vmlinuz-xxx - this is the compressed kernel.
 
 - initrams/initrd - a initial root file system loaded as a ramdisk. this is the initial ram filesystem, which contains essential drivers for hardware and filesystems.
 
 - System.map - the kernel symbolic table.
 
 
 # SYSTEM INITIALIZATION:
 
 /sbin/init - is the first program to run, is identified with process id = 1. It launches the rest of processes

the first thing the init process do is to read the /etc/inittab command, in that file each line represents an action:  

"id:runlevel(s):action:process"

Old distros where based in **SysVinit**. More updated distros use: **systemd**

https://www.freedesktop.org/wiki/Software/systemd/


runlevel go from 0 to 6:


| Run Level | description |
| :---:       |     :---:      |  
| 0  | shut down and turn power off     | 
| 1   | single user mode    |
| S,s  | equal that runlevel 1   | 
| 2 | multiple user, no NFS, only text login     | 
| 3   | multiple user, with NFS and network, only text  | 
| 4   | Not used    |
| 5  |  multiple user, wit NFS, visual login |
| 6  |  reboot  | 


to verify the runlevel, can be done with the 'runlevel' command.

to change the runlevel, use the 'teleinit' command.

http://man7.org/linux/man-pages/man1/systemd.1.html

http://man7.org/linux/man-pages/man1/systemctl.1.html


Start apache service at boot:  sudo systemctl enable httpd.service

Links:

http://www.linux.org/ <br>
http://www.debian.org/<br>
http://www.debian.org/<br>
http://www.ssc.com/lj/index.html<br>
http://www.amazon.com/The-Linux-Programming-Interface-Handbook/dp/1593272200<br>
https://lwn.net/<br>
http://www.linuxtoday.com/<br>
http://www.ssc.com/lg/<br>
https://www.linuxhowtos.org <br>
https://www.tldp.org/HOWTO/HOWTO-INDEX/howtos.html <br>
https://buildroot.org/downloads/manual/manual.html<br>
http://www.tldp.org/LDP/LGNET/archives.html<br>
https://www.tux.org/<br>
http://www.dit.upm.es/~jmseyas/linux/kernel/hackers-docs.html<br>
https://www.gnu.org/manual/blurbs.html<br>
POSIX_SPEC: https://www2.opengroup.org/ogsys/catalog/t101<br>
POSIX_SPEC: http://pubs.opengroup.org/onlinepubs/9699919799/     <br>
http://www.linuxhowtos.org    <br>
https://distrowatch.com/ <br>
https://www.linuxjournal.com/article/3184 <br>
https://lwn.net/Articles/734694/ <br>

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
https://fedoraproject.org/wiki/SysVinit_to_Systemd_Cheatsheet   <br>
http://linuxcommand.org/lc3_learning_the_shell.php <br>
https://linux.die.net/HOWTO/HOWTO-INDEX/howtos.html 
https://linuxconfig.org/

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

https://akkadia.org/drepper/cpumemory.pdf


For building distros:

HLFS - Hardened Linux From Scratch.
CLFS - Cross Linux From Scratch.
BLFS - Beyond Linux From Scratch.
LFS - Linux From Scratch. [http://www.linuxfromscratch.org/]


## ABOUT OPEN SOURCE SOFTWARE LICENSES.

Mainly there are two types of licenses: restrictive and permisive

restrictive licenses: derivative works are intended to remain open, and changes must be made availables. Example: GPL (general public license) (aka copyleft)

permisive licenses: like BSD or Apache licenses. - dont need to be make public.

## tips for hardening linux

 Keep boot dir as read-only	# vi /etc/fstab	then, Add the following line at the bottom "LABEL=/boot/boot ext2 defaults,ro 1 2"	in case of upgrade we need to reset the change 

2. Review Logs Regularly 	in our case we have a log server that will be easy to modify local logs.	For example this is the dafault log files name and their usage: /var/log/message – Where whole system logs or current activity logs are available.	/var/log/auth.log – Authentication logs.	/var/log/kern.log – Kernel logs. /var/log/cron.log – Crond logs (cron job).	/var/log/maillog – Mail server logs.	/var/log/boot.log – System boot log. /var/log/mysqld.log – MySQL database server log file. /var/log/secure – Authentication log.	/var/log/utmp or /var/log/wtmp : Login records file.	/var/log/yum.log: Yum log files.

3. Monitor User Activity with psacct	Installing psacct Packages # yum install psacct	Starting psacct or acct service # chkconfig psacct on	# /etc/init.d/psacct start Display Statistics of Users Connect Time # ac	Display Statistics of Users Day-wise # ac -d	Display Time Totals for each User # ac -p	Display Individual User Time # ac username	Print All Account Activity Information # sa Search Logs for Commands # lastcomm ls

4. Disable SSH Login via Root

# useradd username	add password 
# passwd username	provide sudo permissions to the newly added use

r # echo 'username ALL=(ALL) ALL'

>> /etc/sudoers	now it's time to disable root login 	
 
  1. open the sshd configuration file # vi /etc/ssh/sshd_conf	
  2. uncomment the line 'PermitRootLogin no'	
  3. save and restart # service sshd restart

Search for the authentication options and change the root login permission by setting it to no like below.

PermitRootLogin no

Afterwards just save the file and exit the text editor.
Making changes to the SSH configuration file will require you to restart the service, on CentOS cloud servers use the following.
sudo systemctl restart sshd
On systems running Ubuntu, the service is simply called SSH, the same will work with Debian.
sudo service ssh restart

In order to disable anyone logging in via SSH, you should access the file that is responsible for the configuration of SSH. The file has the following location:
 /etc/ssh/sshd_config

After you have found this file, open it with the text editor app and fine the following line of code and when you do, remove the # symbol from it:
PermitRootLogin no

5-Password policies
If your server has more remote users than just yourself, implement and enforce reasonable password policies with Linux PAM module called pam_cracklib. The module will check user passwords against dictionary words to help prevent weak password usage. You can also use it to set the minimum requirements for a new password like length and complexity.

6.-Restrict SSH to specific user group
OpenSSH server can limit user connections by cross-checking that they belong to the allowed group. This can be useful if you have multiple users of which some should not need to remote with SSH, or you just want the added security for example when running web service or database with separate users to your own.

7. Change the default SSH Port	Open the /etc/ssh/sshd_config file	replace default Port 22 with different port number say 1110 save & exit from the file # service sshd restart	Now to login define the port No # ssh username@IP -p 1110

8. SSH-keys	to generate keys # ssh-keygen - t rsa	Copy your public SSH key , then add the same in the server


9. Monitor authentification

Install Fail2Ban

Fail2Ban is a program that monitors the authentication logs of various programs. When too many attempts are detected, it blocks the source IP address. First, we'll need to install it:

sudo apt-get install fail2ban

To configure, open up the configuration file in a text editor, find the services you want to have it watch (for example, SSH), and then restart the service.

10. Turn Off IPv6	# vi /etc/sysconfig/network	add the following lines "NETWORKING_IPV6=no	IPV6INIT=no"8. Lockdown Cronjobs	# echo ALL >>/etc/cron.deny

11. - - Check for open ports

If a service is listening on a port, it leaves the door open for possible exploit.

We can see what ports currently have services listening on them by running a quick command:

sudo netstat -tulpn

12. Disable USB Mount
One crucial method by which you can ensure higher security, especially against someone who can physically tamper with your computer is to ban them from using USB to attack it. There are many sophisticated USB-based malware which is activated automatically when the pen drive is inserted in your USB port, so this is a crucial tip to strengthen your Linux security. The only price you have to pay is to quit using USB drives all the time and find another method to safely transfer data. Here is how to do it:

Step 1: Open any text editor and write:

→ install usb-storage /bin/true

Step 2: Save the file as a .conf type of file and save in the following location:

→ /etc/modprobe.d/

Step 3: Restart your computer and test if you are able to mount a USB drive.

13. Enable Your Firewall
Basically, this is one thing that every self-respecting Linux user should do when they install a Linux distribution. It more of a security ethic advise, primarily because, even with the firewall disabled, Linux has all the ports locked down either way. But, you never know, if your computer will be targeted sooner or later, because someone with hardened security obviously has something to hide and people quickly realize this. To enable your Linux firewall, you must run the Linux Terminal after which type:

sudo apt-get install guf


GUFW stands for “Graphical Uncomplicated Fire Wall”. The command will install it and after it has finished doing so, you should open it, by typing in your terminal it’s abbreviation and hitting Enter


gufw

After you open GUFW you will see it’s simple user interface. From there simply click on the slider button next to Status to turn it from OFF to ON

14.Make your BIOS More Secure
This tip may not be directly Linux related but it is considered as a general security risk for most Linux distributions. After installing Linux on your computer, it is a good idea to disable any possibility of your computer to boot via USB, CD/DVD or other external drives. This means that nobody can overwrite your Linux and hence damage it or even try to access your drive by booting a Live OS. And this is just the tip of the iceberg of security threats when external boot is enabled. This is why, you should access BIOS on your system start up and go to the Boot tab from which disable the booting option from external drives:
Image: https://sensorstechforum.com/wp-content/uploads/2017/07/bios-boot-tab-sensorstechforum.jpg

In addition to these measures, add a BIOS password, which will stop someone with a physical access to your computer to enter the BIOS

15. Limit your pings or disable responding to pings

As lots of bots find your server by pinging, turning off pings is one way to help hide it (though this really only helps servers that you aren't driving the public to)

16. Use Firejail Sandboxing When You Try New Applications

In general, Linux operating systems are designed in order to be secure by default. But this does not mean that your online browsing is not exposed against any sniffing or phishing attacks – the main reason why you need to secure yourself against new browser extensions or apps that may be unwanted on your Linux machine. Firejail is one security app that is very simple to set up and works on the latest Linux distros. Here is how to set it up on 16.04 LTS Ubuntu:
 sudo apt-get update
sudo apt-get install firejail
ls /etc/firejail

Now you have successfully entered a page where you should see the profiles of all the programs installed on your computer. They should look somewhat like the following:
skype.profile
dropbox.profile
icedove.profile
Tor.profile

If we would like to secure Tor web browser, for example, we can use the “firejail” command in the following syntax:

 firejail firefox
 
17. Encrypt your Drive (Full Disk Encryption) -like with Bitlocker??


18. servers connectiosn

The easiest way to create a secure connection between two servers is through the use of the secure shell command (ssh), which uses SSL to create a telnet-style connection between two servers.
This command creates a public and a private key pair in the /root/.ssh/ directory:
•	id_rsa.pub
•	id_rsa
Authorizing the server to trust itself
Now that we have a keypair, we can authorize the server to trust itself. This may seem odd but we can script commands that reference the server itself as well as the other server in the pair. Moreover, we can replicate this trust to the other server and this makes distribution of the trust simple. Run the following:
cat /root/.ssh/id_rsa.pub >> /root/.ssh/authorized_keys
To validate this works, ssh to the local server using the hostname you specified in the /etc/hosts file:
ssh root@primary
After accepting the fingerprint, it should log you on without specifying a password.
Copying trust to the target server
This next step assumes that the trust is limited between the servers you are trusting. We will send all of these files to the other server and for this we will have to supply the password for once. Copy the files to the other server by running the following:
scp -r /root/.ssh* backup:/root/

19. Define firewalls- 

Nevertheless, we can create such a slightly secure workstation as possible as we can, using firewalld. 
1.	To start the service and enable FirewallD on boot:
2.	sudo systemctl start firewalld
3.	sudo systemctl enable firewalld
To stop and disable it:
sudo systemctl stop firewalld
sudo systemctl disable firewalld
4.	Check the firewall status. The output should say either running or not running.
5.	sudo firewall-cmd --state
6.	To view the status of the FirewallD daemon:
7.	sudo systemctl status firewalld

8.	To reload a FirewallD configuration:
9.	sudo firewall-cmd --reload
Configuring FirewallD
Firewalld is configured with XML files. Except for very specific configurations, firewall-cmd should be used instead.
Configuration files are located in two directories:
•	/usr/lib/FirewallD holds default configurations like default zones and common services. Avoid updating them because those files will be overwritten by each firewalld package update.
•	/etc/firewalld holds system configuration files. These files will overwrite a default configuration.
Configuration Set
Firewalld uses two configuration sets: Runtime and Permanent. Runtime configuration changes are not retained on reboot or upon restarting FirewallD whereas permanent changes are not applied to a running system.
By default, firewall-cmd commands apply to runtime configuration but using the --permanent flag will establish a persistent configuration. To add and activate a permanent rule, there are two methods.
1.	Add the rule to both the permanent and runtime sets.
2.	sudo firewall-cmd --zone=public --add-service=http --permanent
3.	sudo firewall-cmd --zone=public --add-service=http
4.	Add the rule to the permanent set and reload FirewallD.
5.	sudo firewall-cmd --zone=public --add-service=http --permanent
6.	sudo firewall-cmd --reload
Note
The reload command drops all runtime configurations and applies a permanent configuration. Because firewalld manages the ruleset dynamically, it won’t break an existing connection and session.
Firewall Zones
Zones are pre-constructed rule sets for various trust levels you would likely have for a given location or scenario (e.g. home, public, trusted, etc.). Different zones allow different network services and incoming traffic types while denying everything else. After enabling FirewallD for the first time, Public will be the default zone.
Zones can also be applied to different network interfaces. For example, with separate interfaces for both an internal network and the Internet, you can allow DHCP on an internal zone but only HTTP and SSH on external zone. Any interface not explicitly set to a specific zone will be attached to the default zone.
To view the default zone:
sudo firewall-cmd --get-default-zone
To change the default zone:
sudo firewall-cmd --set-default-zone=internal
To see the zones used by your network interface(s):
sudo firewall-cmd --get-active-zones


?? The main web server should be deployed on a dedicated host in the demilitarized zone (DMZ). It’s ports must be firewalled: only 80 (http) and 443 (https) ports must be opened for external connections. 
