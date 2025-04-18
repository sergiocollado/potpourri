# Notes on linux

According to the official page of the Linux kernel:

Linux is a clone of the operating system Unix, written from scratch by Linus Torvalds with assistance from a loosely-knit team of hackers across the Net. It aims towards POSIX and Single UNIX Specification compliance.

## manual pages, where to find help, and references

 - 1- User commands: [:link:](http://man7.org/linux/man-pages/dir_section_1.html)
 - 2- System calls: [:link:](http://man7.org/linux/man-pages/dir_section_2.html)
 - 3- Library standard C & functions: [:link:](http://man7.org/linux/man-pages/dir_section_3.html)
 - 4- Devices [:link:](http://man7.org/linux/man-pages/dir_section_4.html)
 - 5- Files systems [:link:](http://man7.org/linux/man-pages/dir_section_5.html)
 - 7- Conventions & miscellaneous [:link:](http://man7.org/linux/man-pages/dir_section_7.html)
 - 8-system Administration [:link:](http://man7.org/linux/man-pages/dir_section_8.html)
  
<hr>

Linux information project:  http://www.linfo.org/newbies.html

In the case there are references to several of the previous chapters, those references are indicated within a parenthesis, ie:

swapoff(8) and swapoff(2)

https://linux.die.net/man/8/swapoff

https://linux.die.net/man/2/swapoff

time line of Unix based systems:   https://www.levenez.com/unix/

<hr>

Formal introduction: https://linux.die.net/Intro-Linux/

Administrator guide: https://linux.die.net/sag/index.html

Debian administrator handbook: https://debian-handbook.info/browse/stable/

Learning linux thought challenges: https://overthewire.org/wargames/bandit/

<hr>

For starters, open a terminal, well through a short cut, or in many distros with: **Alt + Ctrl + t**

At the console, is easy to get help if needed, checking the manual pages: for it the 'man' command is used:

```bash
> man pwd
```

well, this is actually a method from long ago, ... today it might just be easier to google it : )


There is other way, that is use the command: '**apropos** + topic' that will present you with a list of possible references.

other useful command is '**info** + topic' that presents you with a text with hyperlinks. 

also, in any command you can use the **--help** option: 'rm --help'

also another option is use the **tldr pages**, tldr stands for 'too long dind't read' actually this pages have a more practical aproach and showcase realcase examples. ref: https://github.com/tldr-pages/tldr

In case something is not working properly, always have a go with with the following:

```bash
> sudo apt-get update
> sudo apt-get upgrade
```

maybe even re-index inmediatetly use:

```bash
>sudo updatedb
```

- If you want to have updated all the references to yor database repository, you should install **mlocate**, it will update the db once a day.

```
> sudo apt-get install mlocate
```

If it fails at start, try to:

```
> sudo updatedb

> sudo apt-get update

> sudo apt-get upgrade
```

if you want to identify your system, the 'uname' command is to be used. It will display the linux version.

```bash
> uname -a
```
or:

```
> cat /etc/os-release 
```

or:

```
> cat /etc/*release* 
```

To know the name of your system, run the command: 

```
> hostname
```

or to get the architecture of you system, run:

```
> arch
``` 

also the command 'lscpu' will report great detail of the system.

```
> lscpu
```

or:

```
cat /proc/cpuinfo
```


if you want to know if a given command is insatalled, or where is installed, the 'which' command is used. It will report where a given command is installed. 

```bash
> which which
> /usr/bin/which
``` 

This at least tells us that the command is there and finds itself : )

If you want to be sure that a module is or isn't insalled you can use the following:

```bash
> cat /proc/modules | grep "gcc"
>
```

Actually the no-response, means that the command is not present in the system.


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

other c library: https://musl.libc.org/

binutils:  http://www.gnu.org/software/binutils/

GNU ARM TOOLCHAIN: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm

developers: https://launchpad.net/~gcc-arm-embedded-developers

gcc: http://gcc.gnu.org/

journal: http://www.linuxjournal.com

## Starting with a Linux System.

you can try the following commands: **whoami, pwd, date, uname -a, hostname**

 - **whoami** names the actual user (you?) http://man7.org/linux/man-pages/man1/whoami.1.html
 - **hostname** show or set the system's host name  http://man7.org/linux/man-pages/man1/hostname.1.html
 - **pwd** print current directory  https://linux.die.net/man/1/pwd
 - **date**  print or set the system date and time  http://man7.org/linux/man-pages/man1/date.1.html
 - **uname** print system information https://linux.die.net/man/1/uname

The local settings of the system can be identified with the command **locale**

```bash
>> locale
```

## Linux File System aka File system tree

The linux file system usually has the following file hierarchy structure:

 - **/** (top level directory, named the root directory)
    - **/bin** Commands needed during bootup that might be used by normal users (probably after bootup).
    - **/sbin** Like /bin, but the commands are not intended for normal users, although they may use them if necessary and allowed. /sbin is not usually in the default path of normal users, but will be in root's default path.
    - **/etc** configuration files
    - **/dev** Device files. These are special files that help the user interface with the various devices on the system.
    - **/proc** kernel and processes informative file system: information about the system and running processes
    - **/sys** kernel and system information
    - **/var** variable files (as logs)
    - **/tmp** temporary files
    - **/usr** user programms
    - **/home** home directory
    - **/boot** bootloader files and the linux kernel - the kernel is the file named: vmlinuz. Here there are files used by the bootstrap loader, (e.g., LILO or GRUB). Kernel images are often kept here instead of in the root directory. If there are many kernel images, the directory can easily grow rather big, and it might be better to keep it in a separate filesystem. 
    - **/lib** Shared libraries needed by the programs on the root filesystem.
    - **/opt** optional add-ons
    - **/mnt** Mount point for temporary mounts 
    - **/media** removable devices or where new volue
    - **/srv** service data
    
reference: https://linux.die.net/sag/root-fs.html

Depending on the linux version, the list of the filesystem, may be different. 
    
The reference to this file structure, is defined at:  https://refspecs.linuxfoundation.org/FHS_3.0/fhs-3.0.pdf

This is known as a **FHS**: **File Hierarchy Standard**. - Usually systems want to comply with this standard, so the sowftware can predict the location of installed files and directories.

-  /etc/passwd   - users account informations
-  /etc/shadow   - secure info account for user
-  /etc/group    - group account information.
-  /etc/gshadow  - secure group account information.
-  /etc/shells   - shells defined in the system.
-  /etc/nologin  - If the file /etc/nologin exists and is readable, login(1) will allow access only to root.  Other users will be shown the contents of this file and their logins will be refused.  This provides a simple way of temporarily disabling all unprivileged logins.
-  /etc/services  - The /etc/services file is used by applications to translate human-readable service names into port numbers when connecting to a machine across a network. 
-  /etc/fstab     - the information required to specify mount points, options, devices, etc.
-  /edc/hosts     - network host names and IPs that are known by the system.
-  /etc/init.d    - contains the scripts that start various system services at the boot time
-  /etc/os-release - identifies the linux version and release identification information
-  /usr/lib   - other place to save dynamic libraries needed by programs.
-  /usr/local/lib   - other place to save dynamic libraries needed by programs.
-  /opt/lib   - other place to save dynamic libraries needed by programs.


### Commands to navigate through the file system.

- **pwd** command: Stands for 'print working directory', and it prints the name the current working directory.
- **cd** commands: it stands for 'change directory'. If 'cd' is used without arguments, it changes to the home/defaul directory. To move one step up in the file system hierarchy, the command 'cd ..' is used. It can be used with absulute paths (all the path is defined related to root directory (/)) or relative paths (relative direction from the current directory).
- **ls** command: it is the 'listing' command, it enumerates all the files inside the current directory. When used with the parameter '-l', that stands for "long", it will define the files, with a lot of information about them ( permission, creation date, last used date ...) There are many options, for getting info about them, just type: 'man ls'. 
- **mkdir** command: creates a directory. (**M**a**k**e **dir**ectory)
- **rmdir** command: removes a directory. (remove directory). **Note** rmdir only works, if the directory is empty. This is as a safety mechanisms.
- **cp** command: It copies a file.
- **mv** command: It moves a file (to another directory), also can be used to change the name of a file.
- **touch** command: creates a new file or updates it last edition time.
- **tree** command:- list contents of directories in a tree-like format https://linux.die.net/man/1/tree
- **file** command: identify and report a file type and information.

special directory names: 

- **/**  : root directory
- **~**  : (tilde) user home directory
- **.**  : current directory
- **..** : directory above current directory


**NOTE**: A path which begins with **/** is considered absolute because it specifies the exact filesystem location. Otherwise, it is considered relative and it is implicitly assumed your current directory is prepended.


### Commands for working with files

- **touch**: creates a new file or updateds the edition time of the file
- **output redirection: >**: it redirects, ex: echo "hello-world" > mytextfile.txt
- **output append >>**: it appends: echo "hello again!" >> mytextfile.txt
- **echo**: prints text. Usually is used with the redirecton and append operators: **>** and **>>**. the **-e** option is used so special character can be used, as: \t for tabulation or \n for a new line. It is very useful also to print the value of enviromental variables, like: echo $USERNAME.
- **file**: reports information about files. https://linux.die.net/man/1/file
- `stat`: reports statistics about a file and its inode number (a number that identifies that file)
- **wc**: counts the number of lines, words and characters in a file.
- **more**: prints a screen from a text file.
- **less**: prints a screen from a text file. Less has more options that the **more** command, following the saying: *less is more*
- **grep**: **g**lobally search a **r**egular **e**xpression and **p**rint. search text through files and match patterns. [https://linux.die.net/man/1/grep]
- **find**: search for files in a directory hierarchy, to find the location of files.  https://linux.die.net/man/1/find
- **locate**: find files by name, based on updatedb.  https://linux.die.net/man/1/locate
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
- **du** - informs about **d**isk **u**sage.
- **df** - informs about **d**isk **f**ilesystem.
- **date** print or set the system date and time, or the last modification of a given file (-r, --reference=FILE) http://man7.org/linux/man-pages/man1/date.1.html
- **scp** - secure copy  https://linux.die.net/man/1/scp (is better to use _rcp_ command)
- **rcp** - remote file copy - copies files between machines https://linux.die.net/man/1/rcp
- **rsync** -- a fast, versatile, remote (and local) file-copying tool https://linux.die.net/man/1/rsync
- **dd** convert and copy a file. (used to do backups) http://man7.org/linux/man-pages/man1/dd.1.html
- **watch** - execute a program periodically, showing output fullscreen  https://linux.die.net/man/1/watch
- **vi** - almost universal text editor
- **vim** - improved vi


### Types of files in linux

It is possible to check the types of files with the command `ls -l`. Also with the command `file`

```
-rw-------   1 me       me            576 Apr 15  2020 weather.txt
drwxr-xr-x   6 me       me           1024 Oct  7  2020 web_page
-rw-rw-r--   1 me       me         276480 Feb 13 20:41 web_site.tar
-rw-------   1 me       me           5743 Dec 13  2019 xmas_file.txt

----------     -------  -------  -------- ------------ -------------
    |             |        |         |         |             |
    |             |        |         |         |         File Name
    |             |        |         |         |
    |             |        |         |         +---  Modification Time
    |             |        |         |
    |             |        |         +-------------   Size (in bytes)
    |             |        |
    |             |        +-----------------------        Group
    |             |
    |             +--------------------------------        Owner
    |
    +----------------------------------------------   File Permissions
```


- -: regular file as text, images, or shared libraries...
- d: directory
- c: caracter device file
- b: block device file
- s: local socket file
- p: named pipe-. this are FIFOS and used for interprocess communications.
- l: symbolic link

caracter device files and block device files are two different data structures that represents periphericals or hardware devices or IO ports. Those are almost always placed in the devices folder: **/dev**.

TODO: add info about stiky  bits

the `file` utility can be used to get more information about the data type of a file. 

**REMARK!** in linux extensions don't define the utility or type of a file.

### Hardlinks and softlinks

- reference: https://www.redhat.com/en/blog/linking-linux-explained#:~:text=A%20hard%20link%20always%20points,information%20on%20a%20storage%20device.

Sometimes you don't need to duplicate a file, but you can create a link to that file, saving then disk space, and the same data
can be accessed from diferent locations and with different names. It also protect the deletion of files, a file will only be
deleted from the filesystem, when all the hardlinks linked to it reaches 0. 

Some remarks: hardlinks only work on files, and only in the same filesystem. 

To create a hard link: `ln <path_to_the_target_file> <path_to_link_the_file>`

The utility `stat` reports statistics about a file, it also reports the inode number and the number of hard links to that file. 

A **softlink** also known as **symbolic links**, it is a file that points to a path. As softlinks are just paths, there is no issue
creating softlinks to directories or other filesystems.

```bash
$> tldr ln
Creates links to files and directories.
More information: https://www.gnu.org/software/coreutils/ln.

 - Create a symbolic link to a file or directory:
   ln -s /path/to/file_or_directory path/to/symlink

 - Overwrite an existing symbolic link to point to a different file:
   ln -sf /path/to/new_file path/to/symlink

 - Create a hard link to a file:
   ln /path/to/file path/to/hardlink
```

### Files permissions

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

A finer or more advanced control of access to files can be managed with the paquet **ACL (Access Control Lists)**

commands associated with permissions are: 
 - `ls -l`: enumerate all files in a directory and all it's permissions.
 - `chgrp`: change group permissions
 - `groups`: enumerate the groups in the system.
 - `chown`: change the user permissions
 - `chmod`: modifiy the permissions (u: user, g: group, o other/ + add/ - remove/ = define perms; r: read; w: write; x: execute)

```
$ tldr chmod

Change the access permissions of a file or directory.
More information: https://www.gnu.org/software/coreutils/chmod.

 - Give the [u]ser who owns a file the right to e[x]ecute it:
   chmod u+x path/to/file

 - Give the [u]ser rights to [r]ead and [w]rite to a file/directory:
   chmod u+rw path/to/file_or_directory

 - Remove e[x]ecutable rights from the [g]roup:
   chmod g-x path/to/file

 - Give [a]ll users rights to [r]ead and e[x]ecute:
   chmod a+rx path/to/file

 - Give [o]thers (not in the file owner's group) the same rights as the [g]roup:
   chmod o=g path/to/file

 - Remove all rights from [o]thers:
   chmod o= path/to/file

 - Change permissions recursively giving [g]roup and [o]thers the ability to [w]rite:
   chmod -R g+w,o+w path/to/directory

 - Recursively give [a]ll users [r]ead permissions to files and e[X]ecute permissions to sub-directories within a directory:
   chmod -R a+rX path/to/directory
```

### Root user aka Superuser

- the root account has the highest permission level, and it has access to everything.

- Sometimes it is needed to get all the permissions, for example when we want to install a program. For doing this we use the **sudo** command, it stands for "Switch User DO". To be possible to used the **sudo** command, the user must belong to the group: 'sudoers'.


### Normal users

  Using the commands **who** or **users** reports the current users logged into the system. the current users can be printed with the command **whoami**. 
  
  The command **su** (**switch user**)lets you borrow the permissions from another user to run commands, if no user is especified, it defaults to use the **root** user.
  
  Every user in a linux system is defined by a user ID and also a group ID. For most linux flavors, the first user is defined as user ID = 1000 and the following defined user follow that number. The super user has a user ID of 0.
  
  for handling user, relevant files are _**/etc/passwd**_ and _**/etc/group**_. 
  
  Groups are groups of users that share common privileges in folder and files.
 
  For a given user all his files will be kept in the folder _**/home/user_name**_.
  
  To create a new user, the **useradd** command is used, and to remove one the **userdel** command is used, to modify a user account the **usermod** command is used. (-p flag to change a password). 
  
  - **useradd** - create a new user or update default new user information. the password must be added with other command - https://linux.die.net/man/8/useradd
  - **userdel** - delete a user account and related files - https://linux.die.net/man/8/userdel
  - **usermod** - modify a user account - http://man7.org/linux/man-pages/man8/usermod.8.html
  - **passwd**  - add or changes the password to a user - http://man7.org/linux/man-pages/man1/passwd.1.html
  
  Each user is identified by a uid (user identification).
  
  Users are added to groups with the **usermod** command, with the **-g** or **-G** options.
  
  To check the users in a system, you can check with: 'sudo cat _**/etc/password'**_. If you want to edit that file, it will need to use the command **'vipw'**, that will lock that file for other users. Also is possible that it will be necessary to exit the file _**/etc/shadow**_ for consistency, and that can be done with the command **'vipw -s'**.
  
  For example, to reate a user named 'sam' on system, and the new user's home directory be /opt/sam. His Login shell be /bin/bash and uid be 2328. And also 'sam' a member of the 'admin' group:
  
  ```
  > useradd -d /opt/sam -s /bin/bash -G admin -u 2328 sam
  ```
    
### Other commands related with users

- **whoami** - displays your user
- **who** - displays the list of current users
- **last** - displays the last time the users were logged in.
- **id** - displays information about users

### How to disable an user account

to update the default shell for the user to a nologin shell. With the nologin shell the user will not be able to login to the system.

```
usermod -s /bin/nologin michael
```

remove the user from its groups

```
id michael      # take note of his groups
deluser michael adminGroup
id michael      # check if the groupt has been removed
userdel michael @ delete the user michael
```

and delete the user with the `userdel` command.


#### User directories

In most linux distributions, the directories for the different users are placed in: _**/home/my_user**_

Any user can change his enviroment variable HOME, so it points to whereever he wants, as his root directorie

The _**tilde**_: **~**,  represents the home directorie for any user in the terminal.

#### groups

Groups allow users to be part of a groups. groups in linux allow to have different rights or permitions over given files or resources.

- groupadd - create a new group http://man7.org/linux/man-pages/man8/groupadd.8.html
- groupdel - delete a group http://man7.org/linux/man-pages/man8/groupdel.8.html
- groupmod - modify a group definition on the system http://man7.org/linux/man-pages/man8/groupmod.8.html
- chgrp - modify a file or folder group ownership 

to add a given user to a group, is done:

```bash
> sudo usermod -a -G groupname username
```

### Control access files for users

the control access files are:

 - /etc/password - contains basic information about the users of the system: user name, uid (user id), gid (group id), home directory, and default terminal. But this file itslef doesn't store any passwords.
 - /etc/shadow   - user's passwords are stored in this file, but hashed.
 - /etc/group    - stores information about all the user's groups

So /etc/password, can look like:

```
root@controlplane:~# cat /etc/passwd 
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
systemd-network:x:101:102:systemd Network Management,,,:/run/systemd/netif:/usr/sbin/nologin
systemd-resolve:x:102:103:systemd Resolver,,,:/run/systemd/resolve:/usr/sbin/nologin
sshd:x:104:65534::/run/sshd:/usr/sbin/nologin
admin:x:1000:1000::/home/admin:/bin/bash
david:x:2323:2323::/home/david:/bin/sh
```

And /etc/shadow, can look like: 

```
root@controlplane:~# cat /etc/shadow
root:$6$xyD2JtAg$18v8Q7.Fj661Tj6xlrq2V1lUwv1gFAo9cGZvip/QCBs6K4xculGxgRxPJrTb4tAcgLqQcI0MVNmxJf84T8OIq/:18828:0:99999:7:::
daemon:*:18810:0:99999:7:::
bin:*:18810:0:99999:7:::
sys:*:18810:0:99999:7:::
sync:*:18810:0:99999:7:::
proxy:*:18810:0:99999:7:::
backup:*:18810:0:99999:7:::
list:*:18810:0:99999:7:::
nobody:*:18810:0:99999:7:::
systemd-network:*:18828:0:99999:7:::
systemd-resolve:*:18828:0:99999:7:::
sshd:*:18828:0:99999:7:::
admin:$6$KhLjsx8m$Fx7SIypRT
david:!:18963:0:99999:7:::
```

And /etc/group, can look like:

```
root@controlplane:~# cat /etc/group 
root:x:0:
daemon:x:1:
bin:x:2:
sys:x:3:
adm:x:4:
tty:x:5:
sudo:x:27:admin
backup:x:34:
shadow:x:42:
users:x:100:
nogroup:x:65534:
systemd-journal:x:101:
systemd-network:x:102:
systemd-resolve:x:103:
ssh:x:106:
admin:x:1000:
david:x:2323:
```

### Sudoers and sudo

The **sudo** command lets users to run priviliged commands. But that user must be first allowed to use the **sudo** command.

by the way, **sudo** stands for "super user do".

So if a user needs to run a command with root privileges, it has to be added to the list of sudoes, so it can execute the **sudo** command, and then it will be able to use privileged commands. So with **sudo** it is possible for a user to run programs with the privileges of another user, tipically the superuser (root)

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

#### chmod

 The permissions of a file can be modified with the chmod command. it uses the following syntaxis
 
|character | description |
| :---:  |  :---: |  
| u | owner of the file | 
| g | group the file belongs to |
| o | everybody else | 
| a | everybody above  | 
 
|character | description |
| :---:  |  :---: |  
| + | add permission| 
| - | remove permission |
| = | set permission | 

|character | description |
| :---:  |  :---: |  
| r | read | 
| w | write  |
| x | execute | 

### how to check users and groups

one option is to chech the files:

 - /etc/passwd
 - /etc/group

```bash
>sudo cat /etc/passwd
>sudo cat /etc/group
```

### Default permissions: umask

 - reference : http://man7.org/linux/man-pages/man1/umask.1p.html

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

### SUID, SGID and stiky bit

references: 
 - https://www.scaler.com/topics/special-permissions-in-linux/
 - https://www.howtogeek.com/656646/how-to-use-suid-sgid-and-sticky-bits-on-linux/

SUID (Set User ID): is a special permission set in a file that allows users to run an executable with the permission of the executable's owner.When the SUID bit is set on a file, an "s" represents the owner's execute permission. If the SUID bit is set on a file that doesn't have executable capabilities, an uppercase "S" denotes this.

SGID (Set Group ID): is a special permission set in a executable or directories that allows groups to access as the owner to that executable and directories

Sticky bit: is a special permission that can be set in directories and it restricts the deletion of that directory. Only the file owner, directory owner or super-user (root) can delete the file. This is useful in shared directories where multiple users can create fiiles but should not be able to delete or modify files created by other people.

To set those permissions use `chmod` but with 4 digits: 

```
sergio@laptop:~$ touch myfile
sergio@laptop:~$ ls -l myfile
-rw-rw-r-- 1 sergio sergio 0 ene 18 09:55 myfile
sergio@laptop:~$ chmod 4664 myfile   # the first digit if for SUID
sergio@laptop:~$ ls -l myfile
-rwSrw-r-- 1 sergio sergio 0 ene 18 09:55 myfile # for the user, there is a 'S', so SUID bit is enabled for this file.
# if anyone were to execute that file, it would be executed as the user 'sergio', instead of his user.
# the capital 'S' means that the SUID is enabled, but no excute permission
sergio@laptop:~$ chmod 4764 myfile
sergio@laptop:~$ ls -l myfile
-rwsrw-r-- 1 sergio sergio 0 ene 18 09:55 myfile
# the 's' in that position means SUID and excute bit are enabled.
```

for SGID: 

```
sergio@laptop:~$ touch myfile
sergio@laptop:~$ ls -l myfile
-rw-rw-r-- 1 sergio sergio 0 ene 18 10:06 myfile
sergio@laptop:~$ chmod 2664 myfile 
sergio@laptop:~$ ls -l myfile
-rw-rwSr-- 1 sergio sergio 0 ene 18 10:06 myfile
sergio@laptop:~$ chmod 2674 myfile
sergio@laptop:~$ ls -l myfile
-rw-rwsr-- 1 sergio sergio 0 ene 18 10:06 myfile
```

to find files whit SGUID or SGID: 

```
> find . -perm /4000  # to find SUID
> find . -perm /2000  # to find SGID
```

to set both SUID and SGID: 

```
sergio@laptop:~$ touch myfile
sergio@laptop:~$ ls -l myfile
-rw-rw-r-- 1 sergio sergio 0 ene 18 10:10 myfile
sergio@laptop:~$ chmod 6664 myfile 
sergio@laptop:~$ ls -l myfile
-rwSrwSr-- 1 sergio sergio 0 ene 18 10:10 myfile
```

for the sticky bit: 

```
sergio@laptop:~$ mkdir myfolder
sergio@laptop:~$ ls -ld myfolder/
drwxrwxr-x 2 sergio sergio 4096 ene 18 10:14 myfolder/
sergio@laptop:~$ chmod 1666 myfolder # or chmod +t myfolder
sergio@laptop:~$ ls -ld myfolder/
drw-rw-rwT 2 sergio sergio 4096 ene 18 10:14 myfolder/ # `T`stands for the sitcky bit.
```


## Commands for monitoring the performance, memory

- top - prints the proceses : top(1) http://man7.org/linux/man-pages/man1/top.1.html
- htop - like top- but with better inteface.
- lscpu - display information about the systems cpus. Also its available in /proc/cpuinfo
- uptime - how long has the system been running and its load. uptime(1) https://linux.die.net/man/1/uptime
- ps - information about the processes - http://man7.org/linux/man-pages/man1/ps.1.html
- pstree - ps in a tree http://man7.org/linux/man-pages/man1/pstree.1.html
- trace - info about system call and traces (also theck strace, ptrace and ltrace).
- perf - perf tools https://es.m.wikipedia.org/wiki/Perf_(Linux)   https://perf.wiki.kernel.org/index.php/Main_Page   https://man7.org/linux/man-pages/man1/perf.1.html   https://www.brendangregg.com/perf.html
- pmap - info about process memory stats http://man7.org/linux/man-pages/man1/pmap.1.html
- vmstats -info about the virtual memory statistics, and block I/O. http://man7.org/linux/man-pages/man1/pmap.1.html
- free  - info about meomry usage: free(1) http://man7.org/linux/man-pages/man1/free.1.html
- uname - print system information, like kernel version, hardware, operating systen. https://linux.die.net/man/1/uname
- vmstat - detail of the virtual memory statistics and IO. vmstat(8) http://man7.org/linux/man-pages/man8/vmstat.8.html
- systemctl: report the system programs. http://man7.org/linux/man-pages/man1/systemctl.1.html
- sysstat: a group of tools to monitor performance: http://sebastien.godard.pagesperso-orange.fr/features.html
  - sar: system activity reporter: statistics about all the system 
  - mpstat - statistics for multiple processors http://man7.org/linux/man-pages/man1/mpstat.1.html
  - iostat - cpu utilization and I/O statistics. iostat(1) http://man7.org/linux/man-pages/man1/iostat.1.html
  - iotop - I/O statistics including per process iotop(8) http://man7.org/linux/man-pages/man8/iotop.8.html
  - sar - system activity. sar(1) http://man7.org/linux/man-pages/man1/sar.1.html
  - pidstats: processes statistics. (like top or htop) 

In the /proc directory thre are lots of info about the system:

 - /proc/cpuinfo : CPU Information
 - /proc/filesystems : File-system Information being used currently.
 - /proc/interrupts : Information about the current interrupts being utilised currently.
 - /proc/ioports : Contains all the Input/Output addresses used by devices on the server.
 - /proc/meminfo : Memory Usages Information.
 - /proc/modules : Currently using kernel module.
 - /proc/mount : Mounted File-system Information.
 - /proc/stat : Detailed Statistics of the current System.
 - /proc/swaps : Swap File Information.


### MOUNTING FILE SYSTEMS

The process of attaching a memory device to the filesytem tree, is known as mounting. So for a device to be available, it must first be mounted.

In linux all the files are under the tree that starts in **/**

to mount a partition, it is possible to use the command: **mount**  https://linux.die.net/man/8/mount
it follows:

```bash
$ sudo mount [-t type] [-o options] device dir
```
executing **mount** without options, prints a list of the current mounted filesystems.

In the file:  **/etc/fstab** - is stated the information required to specify mount points, options, devices, etc.

When the linux system boots, it reads a list of mounting instructions in the **/etc/fstab** file, which describes which device is mounted at which mount point in the directory tree. This takes care of the hard drives, but we may also have devices that are considered temporary, such as optical disks and USB storage devices. Since these are removable, they do not stay mounted all the time. The **/media** directory is used by the automatic device mounting mechanisms found in modern desktop oriented Linux distributions. To see what devices and mount points are used, type **mount**.

### physical volumes

the command **pvdisplay** allows you to see the attributes of one or more physical volumes like size, physical extent size, space used for the volume group descriptor area and so on.


### LINUX GRAPHIC SYSTEM

There are three basic layers:

 - x window system (aka x11)
 - window manager
 - desktop manager
 
#### x window system - X11

 It is inteded as a remote interface, so it is really a protocol, and it really is a X server. X comes from eXternal. It is supplied in X.org
 
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

 - http://man7.org/linux/man-pages/man1/bash.1.html
 - https://linuxcommand.org/index.php

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

### Diference between shell and terminal

  A Shell is the command-line interpreter. The shells can be interactive or non-interactive, for example when a script, calls a give shell to run another script: ' bash -c 'hello world!'".
  
  But the terminal is the interface to the shell. 
  
  To find out what shell you are using you can use the following commands:
  
  ```bash
  echo $0
  ````
  
  ```bash
  echo $SHELL
  ```
  reference: http://www.linusakesson.net/programming/tty/index.php
  
  
### Enviromental Variables

The enviromental variables let you customize the system, and define how it works.
These enviromental variables, are definitions that might be used for several goals. Many applications use them to define default settings.

Most common are:  HOST, HOME, PATH, PS1, CDPATH, CWD, USERNAME, USER, UID, LOGNAME, VISUAL, SHELL, TERM, BASH_VERSION, HOSTNAME, HISTFILE, HISTFILESIZE, HISTSIZE, LANG, EDITOR, DISPLAY, TMOUT,LS_COLORS, CPATH, LIBRARY_PATH.

the commands to work with enviromental variables are:

 - **env**
 - **printenv**
 - **set**
 - **unset**
 - **export**

By convention, all the enviromental variables has a name in upper-case.

They can be set like: 'PATH=$HOME/BIN:$PATH'

Watch out when defining enviromental variables as you cannot use 'spaces' around the '=' equal symbol.

To check all defined enviroment variables, you can type: printenv, env, or export.

```bash
printenv | less
``` 

to make available the env var in other directories, they must be exported.

```bash
MYVAR=value;
export VAR;
``` 
or

```bash
export MYVAR=value;
``` 

WARNING: Please, remeber to not put spaces at the sides of the equal sign.

To check the value of a variable, you can use 'echo' and the value of the variable is read with the dollar simbol '$'

```bash
echo $MYVAR
```

To delete a enviromental variable use the command 'unset'

```
>unset $MYVAR
```

PATH, is the enviromental varible that defines the order in which directories will be checked for looking for programs. those directories will be checked from the begining to the end.

It is common that you want to update your PATH variable, it is done like follows:

```bash
export JAVA_HOME="/path/to/java/home"
export PATH=$PATH:$JAVA_HOME/bin
```

you can check its value, with:

```bach
>echo $PATH
>echo $USERNAME
```

Other enviromental varibles are:  LD_LIBRARY_PATH, MANPATH, INFOPATH, CPPFLAGS HOST, HOME, PATH, PS1, CDPATH, CWD, USERNAME, VISUAL.

In the case you want to have persisten enviromental variables, you need to configure those into the terminal configuration files, for example in the following files:

- /etc/enviroment- here there are system-wide used variables.
- /etc/profile - here this file is loaded whenever the bash terminal is call.
- ~/.bashrc - this file is loaded each time a give user open the bash terminal.


#### Bash configuration

The bash console has a copy of the history of the commands we have issued, the comands are at: ~/.bash_history

Other useful file for the command console (terminal) is: ~/.bash_profile. This file keeps a serie of commands that runs everytime that
the terminal is launched

### Customizing the prompt

This can be done through the enviromental variable PS1

For example, to add the git branch in the prompt, add to the .bashrc:

```
# Git branch in prompt.
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}
export PS1="\u@\h \W\[033[32m\]\$(parse_git_branch)\[033[00m\] $ "
```
Or to create a minimalistic prompt:

```
GREEN="\e[1,92m"
CYAN="\e[1;36m"
NC='\033[0m'
export PS1="${CYAN][\W]${GREEN}>>>${NC} "
```

### Aliases

In the terminal is possible to define short-cuts for our custom made commands. For improved usability. For example:

```
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias k='kubectl'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'
alias python='/usr/bin/python3.8'
```

To define an alias:

```
alias your_alias_name="your_alias_command"
```

To undefine an alias:

```
unalias your_alias_name="your_alias_command"
```

To have the alias always defined, you can define them in the configuration file of the terminal. For example, in bash, in the file .bashrc

### Terminal shortcuts

|shortcut | description |
| :---:  |  :---: |  
| CTRL+a | moves the cursor to the begining of the line| 
| CTRL+e | moves the cursor to the end of the line |
| CTRL+l | clears the screen| 
| CTRL+r| seach in the history of commands | 
| arrows up & down| move up or down in the history of commands | 

 - ref: https://www.linuxjournal.com/content/boost-productivity-bash-tips-and-tricks
 

### Open-terminal

It is a program that lets you open a terminal in any window from the desktop manager. Its very usefull.

You can install it with:

```bash
$ sudo yum install nautilus-open-terminal
$ sudo apt-get install Nautilus-open-terminal
```

### Processes

To view the processes that are running, the command **ps** is used. Using **ps** alone, will report the processes that are running from that shell. To check all the processes running in the machine, it is used: **ps -a**. Each proces can be identified by a PID (Process Identinfication Number). In case of need to abort a certain process, the command **kill** can be used.

To see all the processes in the system, use:

```
ps -aux
```

### Linux booting

Booting a Linux system involves several tasks. The process must mount both virtual and real file systems, initialize devices, activate swap, check file systems for integrity, mount any swap partitions or files, set the system clock, bring up networking, start any daemons required by the system, and accomplish any other custom tasks needed by the user. This process must be organized to ensure the tasks are performed in the correct order but, at the same time, be executed as fast as possible.

#### System V
System V is the classic boot process that has been used in Unix and Unix-like systems such as Linux since about 1983. It consists of a small program, init, that sets up basic programs such as login (via getty) and runs a script. This script, usually named rc, controls the execution of a set of additional scripts that perform the tasks required to initialize the system.

The init program is controlled by the /etc/inittab file and is organized into run levels that can be run by the user:

| status | state |
|    :---:        |     :---:      |  
|0 —| halt|
|1 —| Single user mode|
|2 —| Multiuser, without networking|
|3 —| Full multiuser mode|
|4 —|User definable|
|5 —| Full multiuser mode with display manager|
|6 —| reboot|


The usual default run level is 3 or 5.

##### Advantages

Established, well understood system.

Easy to customize.

##### Disadvantages

Slower to boot. A medium speed base LFS system takes 8-12 seconds where the boot time is measured from the first kernel message to the login prompt. Network connectivity is typically established about 2 seconds after the login prompt.

Serial processing of boot tasks. This is related to the previous point. A delay in any process such as a file system check, will delay the entire boot process.

Does not directly support advanced features like control groups (cgroups), and per-user fair share scheduling.

Adding scripts requires manual, static sequencing decisions.


# SYSTEM INITIALIZATION:
 
 /sbin/init - is the first program to run, is identified with process id = 1. It launches the rest of processes

the first thing the init process do is to read the /etc/inittab command, in that file each line represents an action:  

"id:runlevel(s):action:process"

Old distros where based in **SysVinit**. More updated distros use: **systemd**

https://www.freedesktop.org/wiki/Software/systemd/

https://www.linux.com/training-tutorials/understanding-and-using-systemd/

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

# BUILDROOT

http://buildroot.net/downloads/manual/manual.html#_advanced_usage

# GRUB

Its basic configuration file is at: /boot/grub/grub.cfg or /boot/grub2/grub.cfg, those are related to /etc/grub.d and /etc/default/grub
Those file will generate the ones under /boot, when is run update-grub or grub2-mkconfig

 - vmlinuz-xxx - this is the compressed kernel.
 
 - initrams/initrd - a initial root file system loaded as a ramdisk. this is the initial ram filesystem, which contains essential drivers for hardware and filesystems.
 
 - System.map - the kernel symbolic table.
 
 
# Kernel messages

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

kernel panic is the name of the error known in which the OS has a "hard time recovering".

reference: https://searchdatacenter.techtarget.com/definition/Linux-kernel-panic

reference: https://www.linuxjournal.com/content/oops-debugging-kernel-panics-0


## USER SPACE AND KERNEL SPACE

### user space

user space is the part of the memory where all the user mode application run, and that memory can be swapped at any time, when necessary.

user space processes then run in its own virtual memory addresses space, and unless specifically requested cannot address the memory of other processes. (tring to read a memory out of their space is the famous segmentation faolt error).

### kernel space

kernel space is restricted and exclusively reserverd for running the kernel, kernel extension, modules and drivers.

linux kernel space gives full access to the hardware, 

http://www.ibiblio.org/pub/Linux/docs/faqs/Threads-FAQ/html/Types.html

user application <br>
 V <br>
gnu glibc             ..........user space /\ <br>
 V <br>
system call interface ............kernel space V <br>
 V  <br>
kernel  <br>
 V  <br>
architecture dependant kernel code  <br>
 V  <br>
hardware platform  <br>

## How to set and configure linux networking

The basic data is to define the local IP (in a static or dinamic way) the net mask, and the gateway IP. Also the DNS. 

references: <br>
- https://ubuntu.com/server/docs/network-configuration
- https://wiki.debian.org/NetworkConfiguration

For the configuration, most problably the root user should be user

To check the network interface use the **ifconfig** commmand:'eth0' is the network cable, and 'lo' is the loop-back interface

the netwrok interfaces are defined at: **/etc/network/interfaces.d**

```
#The primary network interface
auto eth0
iface eth0 inet static
address 192.168.100.190
netmask 255.255.255.0
gateway 192.168.100.1
```
'static' is a static definition, in which the addresses will be defined in the file, and not with a DHCP server.

To use a DHCP server:

```
#The primary network interface
auto eth0
iface eth0 inet dhcp

# commented out
#address 192.168.100.190
#netmask 255.255.255.0
#gateway 192.168.100.1
```
to force the changes to take effect

```
service networking restart
```

or 

```
/etc/init.d/networking restart
```

And then we can check again the network interface with the conmmand 'ifconfig'. Even check it doing a ping to the gateway. 

To check the DNS, we read the file **/etc/resolv.conf**, there each line stands for a given DNS. 

Thre is other file, where the names are manually assigned: **/etc/hosts**

To activate a given interface, use: `ifconfig eth0 up/down`. To configure the promiscous mode `ifconfig eth0 promisc' and to remove it
`ifconfig eth0 -promisc`.

## Linux networking commands

 - **tc** traffic control - show/manipulate traffic control settings.
 - **ifconfig** print and manipulation of network interfaces and routes (better use the next command)
 - **ip**  replacement for ipconfig
 - **traceroute** traces pacekt's routes, used for troubleshooting networking issues
 - **tracepath** like traceroute, without root privileges
 - **pintg** for checking conectivity
 - **netstat** reports network information ... its deprecated and the **ss** command should be used instead
 - **ss** replacement for the netstat commmand
 - **dig** report DNS info
 - **host** queries a dns host. example `host google.com`
 - **nslookup** find DNS query
 - **route** reports and edit of the route table
 - **host** reports DNS look ups
 - **arp** edit arp tables
 - **iwconfig** configuration of wireless interface
 - **hostname** identifies network interface
 - **curl** client url
 - **wget**
 - **mtr** ping + tracepath in a single command
 - **whois** report web site whois
 - **ifplugstatus** report cable connnection

## BASH SCRIPTING

ref: https://www.man7.org/linux/man-pages/man1/bash.1.html

ref: https://tldp.org/LDP/abs/html/index.htm

A very good reference is: https://linuxcommand.org/lc3_learning_the_shell.php

ref: https://www.gnu.org/software/bash/manual/html_node/index.html#SEC_Contents

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

- **$0** the command name
- **$1** the first argument
- **$2** the second time
- **$\*** represents all the arguments 
- **"$@"** represents all the argumemts keeping the grouping of quoted argumets
- **$#** represents the number of arguments given
- **$?** retains the value of the last executed command

The arguments of a script go from **$0** to **$9**.

## BASH COMMANDS

### comments

all that follows a '#' is a comment

### variables

variables are defined with the equal operator (=), and its value is returned, with the dolar simbol operator $.
variables can be numbers or character strings.
And to print its value, is common to use a 'echo $variable'. 

Watch out when giving value, as no spaces can be written previous and after the equal sign!

```bash
myname="Sergio"
echo "hello $myname !"
myage=30
echo $myage
```

it is possible to modify the value of variable with the 'let' command

```
let myage=$myage+1
```

the value of a variable is getted with the dollar sign $. You can use it even inside strings to use the variable's value.

```
echo "Hello. I am $myname$, and I am $myage years old"
```

### command substitution

in a script you can use commands in the same way as in the console, but the commands must be wrapped in 
'$( )'. this is called command substitution.

the command is executed, and then it is replaced by the string that results from running that command.

### expr and bc

expr evaluates mathematicals expressions

a more powerfull program is bc, 'bc' stands for **B**ench **C**alculator https://linux.die.net/man/1/bc

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
``` 

that "-n" given to the echo command causes it to keep the cursor on the same line; i.e., it does not output a linefeed at the end of the prompt.


```bash
#!/bin/bash

number=0

echo -n "Enter a number > "
read number
```

It is possible to present options to the user:

```
read -p "Install Software ?? [Y/n]: " answ
 if [ "$answ" == 'n' ]; then
   exit 1
 fi
   echo "Installation starting..."
```

### Conditional execution: script flow control

the return value of a command or program thar exits successfully is 0 otherwise the exit is not successfully.

so the value 'true' is equal to 0, and the value 'false' is equal to not 0.

the returned value of the last exectued command or program is stored in $? so you can retrieve it with 'echo $?'


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


#### Conditional expressions

Conditionals expressions are indicated a condition inside double brackets: [[ ]]

the possible operators are:

| condition value operator| text | 
| :---         |     :---:      |  
| -gt  | greater than     | 
| -ge   | greater than or equal    | 
| -eq   | equal   | 
| -neq  | not equal     | 
| -le   | less than or equal     | 
| -lt   | less than    |
| -e  | a file exits     |
| -d   | a directory exits  | 
| -z   | length of a String is zero    |
| -n   | Length of a string is non-zero     | 
| ~=   | match operator to a regular expression    | 
| !   | NOT operator    | 

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


| logica operators| text | 
| :---         |     :---:      |  
| ~=   | match operator to a regular expression    | 
| $value | is it non empty? | 
| ==  | equals?  | 
|  !=  | different?   | 
| !   | NOT operator    | 

### IF statements

```bash
if [ condition ]
then
    #... commands
else
    #... other commands
fi 
```

or with several branches


```bash
if [ condition]
then
    #... commands
elif [ other condition ]
then
    #... other commands
fi 
```

for example

```bash
if [ -d "$JAVA_HOME/bin" ] 
then
    PATH="$JAVA_HOME/bin:$PATH"
```

### Arrays
arrays are lits of elements.

```bash
weekdays=(monday tuesday wednesday thursday friday saturday sunday)
```

you can retrieve a given element with the parameter expansion ${} and with the '[]' squaded brackets indicator.

Take into account, that arrays are zero-indexed (the first elements starts in zero index)

```bash
${weekdays[0]}
```
to referer to all the elements use a * pattern

```bash
${weekdays[*]}
```
to get only some of the elemnts you can use the start index, followed by the number of elements, separated by colons (:)

```bash
${weekdays[*]:5:2}
# saturday sunday
```

to get the size of the array, use the pound # sign

```bash
${#weekdays[*]}
```
to add an element at the end of the array use the '+=' sign.

```bash
weekdays+= otherday
echo ${weekdays[*]}
```

or you can modify a given element with the square brackets

```bash
weekdays[7]=monday
```

### Brace expansion

brace expansion is a way to create series of strings. it uses curly braquets and two periods to indicate it.

```bash
echo {0..9}
# 0 1 2 3 4 5 6 7 8 9 
```

you can use number or letters
```bash
echo {a..j}
echo {A..J}
```

it is possible to used prefixes to the brace expansion
```bash
echo a{0..9}
# a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 
```

or postfixes

```bash
echo {0..9}z
# 0z 1z 2z 3z 4z 5z 6z 7z 8z 9z 
```

or combine sequences.

```bash
echo {1..3}{A..C}
# 1A 1B 1C 2A 2B 2C 3A 3B 3C
```

or concanete sequences with a comma.
```bash
echo { {1..3},{A..C} }
# 1 2 3 A B C 
```

or use variables with the evaluation 

```bash
start=3
end=7
echo {$start..$end}
eval echo {$start..$end}
```

### FOR loops

```bash
for i in {1..3}
do
    echo "i is equal to $i"
done
```

### WHILE loops

```bash
count=5

while [[ $count -gt 0 ]]
do
  echo "count is equal to $count"
  let count=$count-1
done
```

### Functions

 funtions allow us to reuse code:
 
 the syntaxis of the function definition and invocatios is like follows
 
  ```bash
  function hello {
    echo "hello there $1!"
    # do stuff
  }
  
  hello Sergio
  ```
  
  ```bash
  >> hello there Sergio
  ```
  
  $1, $2, $3 .... are the parameters of the function
  
  $@ is a list of the parameters of the function. This is useful for FOR-LOOPS to iterate over the input arguments. 
  
  If we define some funcions in a file like "functions.sh", we can include it in another file, with the 'source' instruction. 
  
  ```bash
  source functions.sh
 ```
  in case we need to define a local variable inside a function that has the same name as a global varible, we can use the keyword 'local' that way, this will define the variable like a local one, and it will not collide with any global variable.


### Terminal PS1 and colors

It is posible to change the prompt of the terminal

- ref: https://www.maketecheasier.com/8-useful-and-interesting-bash-prompts/
- ref: https://www.howtogeek.com/307701/how-to-customize-and-colorize-your-bash-prompt/#:~:text=To%20change%20your%20Bash%20prompt
- ref: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Controlling-the-Prompt
and also use diferent colors

 - ref: https://misc.flogisoft.com/bash/tip_colors_and_formatting
 - ref: https://linux.die.net/man/4/console_codes
 
check:

```
PS1="[\d \t] \u@\h\n\w\$ "
```

```bash
echo -e "\e[38;5;82mHello \e[38;5;198mWorld"
```

```bash
#!/bin/bash
 
# This program is free software. It comes without any warranty, to
# the extent permitted by applicable law. You can redistribute it
# and/or modify it under the terms of the Do What The Fuck You Want
# To Public License, Version 2, as published by Sam Hocevar. See
# http://sam.zoy.org/wtfpl/COPYING for more details.
 
for fgbg in 38 48 ; do # Foreground / Background
    for color in {0..255} ; do # Colors
        # Display the color
        printf "\e[${fgbg};5;%sm  %3s  \e[0m" $color $color
        # Display 6 colors per lines
        if [ $((($color + 1) % 6)) == 4 ] ; then
            echo # New line
        fi
    done
    echo # New line
done
 
exit 0
```

Example to add the git branch in the prompt (add to .bashrc)

```
# Git branch in prompt.
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}
export PS1="\u@\h \W\[033[32m\]\$(parse_git_branch)\[033[00m\] $ "
```


## Secure Shell (aka ssh)

ssh is the secure shell. SSH is a network prototocol, like telnel, ftp, ...  SSH is a secure protocol, so the comunication is encrypted. SSH can be used for transmitting data, for transmitting commands of files, 

there are ssh clients or server, for mayor system platforms.

to install a ssh server:

to look for the packet: apt-cache search openssh

### How to install a ssh server

to install: 

```
sudo apt-get install openssh-server
```

### How to login to ssh

To connet to a ssh server you command in a terminal as:

```
ssh username@remotelocation
```

remotelocation can be an ip address or a name

if you left out your user name, it will attemp to connect with you local user name .


you will be asked for your password. 

basically almost any command you can run in the terminal you can also run it in the ssh shell

to end the ssh connections you use the command: 'exit'.

otherwise if you just close the terminal the process will still be open, and consumming resources. 


## how to logout ssh

 - CTR+D
 - logout 
 - exit


## SSH authentification

 There is two aproaches: one is password based and the second one is based in cryptographic keys. the later is much more secure.


## How to generate a ssh_key

ref: https://www.ssh.com/ssh/keygen/

run the command: **ssh-keygen**

the keys are stored in the file '.ssh/' 

- id_rsa.pub is your public key and can be shared, while id_rsa is your private key and should be kept secret.

the command **`ssh-add`** will keep the ssh keys if these are stored in the standard places.

And with the command **`ssh-agent`** the passphase will be used automatically.


## How to change the ssh port

you can also change the default port in which ssh is using (for security reasons..)

```bash
sudo vim /etc/ssh/sshd_config
```

and in the port, you can edit and change it. Usually it uses the standard port 22 , but you can choose to change it for security reasons. so it is not easy to guess where you ssh port is.


after that it is needed to restar the ssh server:

```
sudo /etc/init.d/ssh restart
```

you can test the service with: ssh localhost

it should report an error.

but if the newport is tested: ssh -p newportnumber localhost

then it should ask for the password. 

to stop the ssh server:

```
sudo /etc/init.d/ssh stop
```
	
## How to disable ssh root account (for security reasons)

For security reasons is interesting to disable the ssh as root account, following the principle of least privilige
	
The ssh config file must be edited
	
```
vi /etc/ssh/sshd_config
```
add
	
```
PermitRootLogin no
```
also to disable password based access, forcing to use only private keys, add:
	
```
PasswordAuthentifaction no	
```
	
Once done, restart the ssh service with:
	
```
systemctl restart sshd
```


## NETWORKING

**ifconfig** - presents the current network configuration (although is better to use the more updated command **ip**)

Normally ethernet intefaces are named as eth0, eth1... and wireless interfeaces as wlan0, wlan1... although nowadays, the different distros use to use the **Predictable Network inteface Device Names**

https://www.freedesktop.org/wiki/Software/systemd/PredictableNetworkInterfaceNames/

the configuration file is: _**/etc/sysconfig/network-scripts/ifcfg-exnoXXXX**_

statistical info is in the file:  _**/proc/net/dev**_ and also in the files: _**sys/class/net/ethX/statistics**_


**enoXXXX** - stands for **ethernet onboard**

**lo** -- stands for **loopback adress**

To change the ip address, you must command:

```bash
sudo ifconfig enoXXXXX 192.1new_ip_address netmask 255.255.255.0
```

To check the route - (shows the way to the next hub)

```bash
route
```

To change the route, you have to command:

```bash
route add 192.34X.xxx.xxx enoXXXX
```

To check everything is ok. you can ping adresses

```bash
ping 192.xxx.xxx.xx
```

```bash
ping google.com
```

To configure the network interface to be persistant, you have to edit the file _**/etc/sysconfig/network-scripts/ifcfg-enoXXX**_

So we can change the BOOTPROT (ocol) to static, and add the address information and netmask.

```
BOOTPROTO=
IPADDR=192.168.XXX.XXX
NETMASK=255.255.255.xxx
```

To launch a network connection and attach it to a ip address, you do like:

```bash
$ sudo /sbin/ifconfig eth0 up 192.168.1.123
```

if you want to request a dynamic IP is done like

```bash
$ sudo /sbin/ifconfig eth0 up
$ sudo /sbin/dhclient eth0
```

The usual command used to be 'ifconfig', although nowadays the new utility 'ip', it is an improved version and is more efficient

https://linux.die.net/man/8/ip

https://linux.die.net/man/7/netlink

https://linux.die.net/man/2/ioctl


The newer **ip** command can be used for many tasks like: manipulate routing, devices, policy routing and tunnels

https://linux.die.net/man/8/ip

its basic sintaxis is: 

ip [ OPTIONS ] OBJECT { COMMAND | help }

so, if you need to print all the network interfaces:

```bash
 ip link
``` 
or 

```bash
 ip addr show 
``` 

That will display the addresses of all the devices. Or in case a specific device is needed:

```bash
 ip addr show eth0
``` 

To check the info of one network interface.

```bash
$ ip -s link show ethX
```
 
To define the ip for a newtork interface
```bash
$ sudo ip addr add 192.168.1.7 dev ethX
```
 
To bring down a network interface
```bash
$ sudo ip link set eth0 down
```
 
To set the MTU (Maximun Transmision Unit) for a given network interface
```bash
$ sudo ip link set eth0 mtu 1480
```

To define a network route:
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

### How to know what ports are open

Several commands can be used: 

```
sudo lsof -i -P -n | grep LISTEN
sudo netstat -tulpn | grep LISTEN
sudo ss -tulpn | grep LISTEN
sudo lsof -i:22 ## see a specific port such as 22 ##
sudo nmap -sTU -O IP-address-Here
```
the tulpn options stands for

-t : Show only TCP sockets on Linux
-u : Display only UDP sockets on Linux
-l : Show listening sockets. For example, TCP port 22 is opened by SSHD server.
-p : List process name that opened sockets
-n : Don’t resolve service names i.e. don’t use DNS


To check if a port is used, and listening, use a command such: 

```
netstat -an | grep -w LISTEN
```

To know what are those ports used for, in case of an ubunto based distribution, it can be checked in the etc/services file

```
cat /etc/services
```

### more about networking

 - netstat: network statistics - https://linux.die.net/man/8/netstat  (deprecated and is better to use the command **ss**)
 - iptraf: info about network interfaces - Interactive Colorful IP LAN Monitor - https://linux.die.net/man/8/iptraf
 - tcpdump & tshark &  wireshark analysys of network and traffic
  

## UFW - uncomplicated firewall

The internal packet filtering system, (the net filter) can be handled by means of the IP tables. Iptalbes is the most common
took to inteface with the linux firewall, althought it has a learning curve. The UFW, (uncomplicated firewall) is a simpler
solution. 

to install ufw

```
apt-get install ufw
```
once installed enable it

```
systemctl enable ufw
systemctl start ufw
```

the ufw status can be checked as:

```
ufw status
```

to allow outgoing connections

```
ufw default allow outgoing
```

to add a default deny for incoming connections

```
ufw default deny incoming
```

to add an allow rule: 

```
ufw allow from 172.16.0/28 to any port 22 proto tcp
```
to activate the firewall: 

```
ufw enable
```

to check the status of the rules: 
```
ufw status
```

### check system file system

to verify the system file system:

```bash
cat /proc/filesystem | less
```

## SYSCTL

reference: https://www.kernel.org/doc/Documentation/sysctl/README

Sysctl is a means of configuring certain aspects of the kernel
at run-time, and the /proc/sys/ directory is there so that you
don't even need special tools to do it!
In fact, there are only four things needed to use these config
facilities:
- a running Linux system
- root access
- common sense (this is especially hard to come by these days)
- knowledge of what all those values mean

As a quick 'ls /proc/sys' will show, the directory consists of
several (arch-dependent?) subdirs. Each subdir is mainly about
one part of the kernel, so you can do configuration on a piece
by piece basis, or just some 'thematic frobbing'.

The subdirs are about:
 - abi/		execution domains & personalities
 - debug/
 - dev/		device specific information (eg dev/cdrom/info)
 - fs/		specific filesystems, filehandle, inode, dentry and quota tuning
		binfmt_misc <Documentation/admin-guide/binfmt-misc.rst>
 - kernel/	global kernel info / tuning miscellaneous stuff
 - net/		networking stuff, for documentation look in:
		<Documentation/networking/>
 - proc/
 - vm/		memory management tuning
		buffer and cache management
 - user/	Per user per user namespace limits



### Memory analisys in linux systems

 https://akkadia.org/drepper/cpumemory.pdf
 
 **free** - Display amount of free and used memory in the system - https://linux.die.net/man/1/free
 
 **df** - (from disk filesystem?) report file system disk space usage  https://linux.die.net/man/1/df
 
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

-  **df** command (for _disk filesystem_): this will report how much free memory has the filesystem. You usually invoque `df -sh` the -h flag stands for "human readable", and the -s for summary

 - **du** command (stands for: _disk usage_): reports an estimation of the file space usage. is better to use it with the optinons -sh. -s for summary and -h for human readeble.

for example to check the disk free, you can use:

```bash
df -ah 
``
- a for 'all'
- h for 'human readable' 

TODO: COMPLETE

6) **memsusage**: is a script that reports the memory consuption of a given program. http://man7.org/linux/man-pages/man1/memusage.1.html

https://akkadia.org/drepper/cpumemory.pdf


## system monitoring

- uname - print system information, like kernel version, hardware, operating systen. https://linux.die.net/man/1/uname
- ulimits
- sar:Collect, report, or save system activity information.  https://linux.die.net/man/1/sar
- iotop - simple top-like I/O monitor  https://linux.die.net/man/1/iotop
- vmstat - Report virtual memory statistics https://linux.die.net/man/8/vmstat
- iostat - Report Central Processing Unit (CPU) statistics and input/output statistics for devices, partitions and network filesystems (NFS). https://linux.die.net/man/1/iostat
- top- display Linux tasks
- ps - report a snapshot of the current processes - https://linux.die.net/man/1/ps
- pstree - display a tree of processes  - https://linux.die.net/man/1/pstree
- pmap - report memory map of a process - https://linux.die.net/man/1/pmap
- systemctl -

In the workst of cases, it is also possible scrap /proc, /proc has all the info about the running processes. But this may be not very portable. 

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

- **lsmod** - program to show the status of modules in the Linux Kernel. https://linux.die.net/man/8/lsmod
- **modinfo** - presents info about the modules the kernel is using. https://linux.die.net/man/8/modinfo
- **modprobe** - program to add and remove modules from the Linux Kernel. https://linux.die.net/man/8/modprobe
- **insmod** - simple program to insert a module into the Linux Kernel. https://linux.die.net/man/8/insmod

# How to evaluate the startup of linux system

Bootchart is a tool for performance analysis and visualization of the GNU/Linux boot process. Resource utilization and process information are collected during the boot process and are later rendered in a PNG, SVG or EPS encoded chart.
http://www.bootchart.org/  or  https://github.com/xrmx/bootchart


# How to check for open network connectios, open ports or alike:

Use the command **netstat** and filter with the options (netstat is deprecated and it is better to use the **ss** command)

```bash
netstat -tulpn
```
if the command is run as root, then the program that is using those connections will be shown. 

## Example

### QUESTION 

 An unknown process is bound to the port 8088.
 Identify the process and prevent it from running again by stopping and
 disabling any associated services. Finally, remove the package that was
 responsible for starting this process.


### ANSWER 

Check the process which is bound to port 8088 on this node using **netstat**:

controlplane $ netstat -natulp | grep 8088
This shows that the the process openlitespeed is the one which is using this port. Check if any service is running with the same name:

controlplane $ systemctl list-units  -t service --state active | grep -i openlitespeed
lshttpd.service                    loaded active running OpenLiteSpeed HTTP Server
This shows that a service called openlitespeed is managed by lshttpd.service which is currently active.

Next, stop the service and disable it:

controlplane $ systemctl stop lshttpd
controlplane $ systemctl disable lshttpdxx
Finally, check for the package by the same name:

controlplane $ apt list --installed | grep openlitespeed
Uninstall the package:

controlplane $ apt remove openlitespeed -y

## How to automaticaly mount a volume at boot

Define it in the file: /etc/fstab.

# Run a script as a background daemon

It is possible with '&':

```bash
nohup node myscript.js > /dev/null 2>1 &
```

nohup:  doesn't allow termination of the process even in the event the stty is finished (the console/shell) 
/dev/null : the output of the process goes to the null-device (shinkhole).
2>&1 : stderr is redirected to stdout -- in this case stdout already is redirected to /dev/null --
& : run the process in the background (as a daemon)

## For Real time

 - ionice - get/set program io scheduling class and priority https://linux.die.net/man/1/ionice
 - heartbeat - Heartbeat subsystem for High-Availability Linux https://linux.die.net/man/8/heartbeat
 - uptime - Tell how long the system has been running.
 - gcov -  is a test coverage program. Use it in concert with GCC to analyze your programs to help create more efficient, faster running code and to discover untested parts of your program. https://linux.die.net/man/1/gcov   https://linux.die.net/man/1/arm-linux-gnu-gcov
 - gprof - "GNU profiler": display call graph profile data. "Gprof" calculates the amount of time spent in each routine. https://linux.die.net/man/1/gprof   and   https://www.maketecheasier.com/profile-c-program-linux-using-gprof/  
 - strace - trace system calls and signals - strace is a useful diagnostic, instructional, and debugging tool.- https://linux.die.net/man/1/strace
 - ltrace - A library call tracer - It intercepts and records the dynamic library calls which are called by the executed process and the signals which are received by that process. It can also intercept and print the system calls executed by the program. - https://linux.die.net/man/1/ltrace
 - ptrace - process trace - #include <sys/ptrace.h> - The ptrace() system call provides a means by which one process (the "tracer") may observe and control the execution of another process (the "tracee"), and examine and change the tracee's memory and registers. It is primarily used to implement breakpoint debugging and system call tracing. - https://linux.die.net/man/2/ptrace
 - nm - list symbols from object files  - https://linux.die.net/man/1/nm
 - dstat - versatile tool for generating system resource statistics - https://linux.die.net/man/1/dstat
 - gstack - print a stack trace of a running process -- https://linux.die.net/man/1/pstack 
 - poll, ppoll - wait for some event on a file descriptor - #include <poll.h>
 - select _ select() and pselect() allow a program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation (e.g., input possible). A file descriptor is considered ready if it is possible to perform the corresponding I/O operation (e.g., read(2)) without blocking.
 - valgrind - a suite of tools for debugging and profiling programs - http://www.valgrind.org/docs/manual/index.html.
 - mmap, munmap - map or unmap files or devices into memory-  conforms with POSIX.1-2001. is defined in  <unistd.h> 
 - sysconf - get configuration information at run time-  #include <unistd.h> - POSIX.1 compatible - https://linux.die.net/man/3/sysconf
 - clock_getres, clock_gettime, clock_settime - clock and time functions - #include <time.h> - POSIX.1-2001.
 - btrace - perform live tracing for block devices - http://man7.org/linux/man-pages/man8/btrace.8.html <br>
 - mtrace, muntrace - malloc tracing - https://linux.die.net/man/3/mtrace
 
 
   getrlimit, setrlimit, prlimit - get/set resource limits: http://man7.org/linux/man-pages/man2/getrlimit.2.html
   
   coredumps: http://man7.org/linux/man-pages/man5/core.5.html
   
   
 http://www.admin-magazine.com/Articles/Law-of-Averages-Load-Averaging <br>
 https://people.seas.harvard.edu/~apw/stress/   <br>
 http://smackerelofopinion.blogspot.com/2014/06/stress-ng-updated-system-stress-test.html   <br>
 watchdog: https://mmonit.com/monit/   <br>
  
 The tmpfs facility allows the creation of filesystems whose contents reside in virtual memory.  Since the files on such filesystems
 typically reside in RAM, file access is extremely fast. http://man7.org/linux/man-pages/man5/tmpfs.5.html
 
  https://www.bootchart.org/
  
  
### For debugging: gdb

main website: https://www.gnu.org/software/gdb/

gdb good stuff:

 https://youtu.be/PorfLSr3DDI

graphical interface for gdb: gdb --tui 

For debugging: gdb and core dumps:

http://www.brendangregg.com/blog/2016-08-09/gdb-example-ncurses.html

https://sourceware.org/gdb/onlinedocs/gdb/index.html#Top


### Tools to monitor linux systems

 - top and htop: Linux process ponitoring
 - vmstat: virtual memory statistics
 - lsof: list open files
 - tcpdump: network packet analyzer
 - netstat: network statistics (its deprecated and is better to use the ss command)
 - ss
 - monitorix: system and network monitoring   https://www.monitorix.org/
 - iotop: Monitor Linux Disk I/O
 - iostat: Input / Output Statistics
 - iptraf: Real Time IP LAN Monitoring
 - psacct: Monitor User Activity
 - monit: Linux Process & Srvc Monitoring
 - nethogs: Monitor Per Process Network
 - nmon: Monitor Linux Performance 
 - watch: monitor a given element
 - bootchart https://www.bootchart.org/
 - kernelshark
 - bootgraph  https://github.com/torvalds/linux/blob/master/scripts/bootgraph.pl
 - ulimit
 - oprofile https://man7.org/linux/man-pages/man1/oprofile.1.html
 - lltn   https://lttng.org/docs/#doc-getting-started
 
  
#### How to create timers:

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
$> nmap 192.168.0.1-10
```

or using a wild card

```bash
$>nmap 192.168.0*
```
to exclude a given:

```bash
$>nmap 192.168.0*  --exclude 192.168.1.5
```

We can see what ports currently have services listening on them by running a quick command:

```
>sudo netstat -tulpn
```

#### ping discovery

```bash
nmap -sP 192.168.1.0/24
```


# How to instal GCC

 GCC. : gnu compiler collection
 
 ```bash
 $ sudo apt update
 $ sudo aptget install build-essential
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

## How to install ncurses

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

## How to install apache 

```bash
apt-get update
apt-get install apache2 php php-mysql -y
service apache2 restart
```

## How to install nginx-light

```bash
sudo apt-get install nginx-light -y
```
# Build root 

ref: https://buildroot.org/

It is a system for generating linux images. 

 - reference: https://youtu.be/9vsu67uMcko

```bash
git clone git://git.buildroot.net/buildroot
cd buildroot
# in the /configs folder there are already ready configuration files 
make <and_your_config_file>
# this will create a .config file
make menuconfig
make
# this will take a while
cd output/images # the images are here: sdcard.image
```

# GIT

 - https://git-scm.com/docs/gittutorial
 - https://www.git-scm.com/doc
 - https://linux.die.net/man/7/gittutorial 
 - https://linux.die.net/man/7/gittutorial-2
 - https://linux.die.net/man/7/gitworkflows
 - https://linux.die.net/man/7/gitglossary
 - the untold story of git: https://youtu.be/Uq41qdjJ8Xs?si=owopc3blVu6zHWhI
 - Two decades of Git: A conversation with creator Linus Torvalds: https://youtu.be/sCr_gb8rdEI?si=Ma-zS5lbRYPqGsIF

easy way to learn: https://learngitbranching.js.org/

```bash
usage: git [--version] [--help] [-C <path>] [-c <name>=<value>]
           [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
           [-p | --paginate | -P | --no-pager] [--no-replace-objects] [--bare]
           [--git-dir=<path>] [--work-tree=<path>] [--namespace=<name>]
           <command> [<args>]

These are common Git commands used in various situations:

start a working area (see also: git help tutorial)
   clone     Clone a repository into a new directory
   init      Create an empty Git repository or reinitialize an existing one

work on the current change (see also: git help everyday)
   add       Add file contents to the index
   mv        Move or rename a file, a directory, or a symlink
   restore   Restore working tree files
   rm        Remove files from the working tree and from the index

examine the history and state (see also: git help revisions)
   bisect    Use binary search to find the commit that introduced a bug
   diff      Show changes between commits, commit and working tree, etc
   grep      Print lines matching a pattern
   log       Show commit logs
   show      Show various types of objects
   status    Show the working tree status

grow, mark and tweak your common history
   branch    List, create, or delete branches
   commit    Record changes to the repository
   merge     Join two or more development histories together
   rebase    Reapply commits on top of another base tip
   reset     Reset current HEAD to the specified state
   switch    Switch branches
   tag       Create, list, delete or verify a tag object signed with GPG

collaborate (see also: git help workflows)
   fetch     Download objects and refs from another repository
   pull      Fetch from and integrate with another repository or a local branch
   push      Update remote refs along with associated objects

'git help -a' and 'git help -g' list available subcommands and some
concept guides. See 'git help <command>' or 'git help <concept>'
to read about a specific subcommand or concept.
See 'git help git' for an overview of the system.
```

## How to install git 
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


to verify the git version in the system
```bash
git --version
```

## configuring GIT

```bash
git config --global user.name "_myusername"
git config --global user.email _myuseremail 
git config --global core.editor _emacs
git config --global merge.tool  kdiff3
```

to check the settings.
```bash
git config --list 
```

git has 3 levels of configuration 

- the system level config: git config --system,  stored at /ect/gitconfig. it afects to all the computer
- the user level: git config --global, stored in ~/.gitconfig  
- the repository level: git config, defined in .git/config of each repository 

these configuration level are hierarchical, 

to check the configuration: git config --global --list 
or just read the configuration files:

```bash
cat /etc/gitconfig
cat ~/.gitconfig  
cat .git/config
```

to configure the user: 

```bash
git config --global user.name "myName"
```
to configure the email: 
```bash
git config --global user.email "myName@email.com"
```
to check the configuration values, agian
```bash
git config --global --list
```
to set the core editor:
```bash
git config --global core.editor nano/gedit/emacs/vim/...
```
to help to do matches to correct commands:
```bash
git config --global help.autocorrect 1
```
to show colors while reporting in git: 
```bash
git config --global color.ui auto
```
```bash
git config --global core.autcrlf input
```

to remove any of those varibles:
```bash
git config --unset user.name 
```

to ignore files with:  .gitignore


REFERENCES:

References are labels associated to commit's SHA hash value. The reference **master** points to the master branch. A branch label points to the latest commit in a brach, its tip. actually branch labels are implemented only as refereces to given commits. the referenes are stored in the .git/refs directory. local branch references are in the .git/refs/heads directory. 

**NOTE**: The _**“master”**_ branch in Git is not a special branch. It is exactly like any other branch. The only reason nearly every repository has one is that the git init command creates it by default and most people don’t bother to change it.

The **HEAD** reference is the reference to the actual commit in you local branch. Watch out! because in other repository systems the concept of 'head' is diffenent. In git it just identifies the branch you are currently on.

The **origin**  is the default name Git gives to the server you cloned from.

the tilde (**~**) and caret (**^**) are used to refence to previous commits. to use them you append them to a commits refernce. You can use a ~ or ~1, that points to the parent of the given commit, if you use ~~ or ~2 you are refering to the parent's parent of the pointed commit. If you use the ~~~ or ~3 the reference is to the parent's parent's parent of the pointed commit. and so on ...

the **caret** (^) is used to point to a parent in a merge commit. so ^1 or ^ refers to the first parent and ^2 refers to  the second parent. or if you stack them : ^^ refers to the first's parent first parent of the pointed commit. 

TAGS: 
a tag is just a refenced defined to point to a given commit. So you can also use tags instead of SHA values to reference commits.  

there are two types of tags. A lightweight tag, is just a simple reference name to a given commit. An annotated tag, it includes more information as author, date, messates, commit ID, and can be signed and verified with GPG (GNU Privacy Guard). 

to view the tags defined in a given repository use the tag command:

```bash
git tag
git push remoterepo tagname
```
to tranfer all the tags you use:

```bash
git push remoterepo --tags
```

to view the information about a given tag:

```bash
git show tagname
```

to tag a certain commit you use:

```bash
git tag tagname commitreference
```
you need to use the -a option to indicate an annotaded tag

 
to create a git repository, use:
```bash
git init
```
this will create a hidden .git file, in which the info of the repository will be saved. 

to add a file
```bash
git add finename
```
to add all modified files, it is possible to use the -u flag
```bash
git add -u 
```

then check the status of the repo
```bash
git status
```
the new added file should appear as a new file, and it is staged to be added to the repo, which will be done with:
```bash
git commit
```
this will pop up the custom text editor, so that we can add a message to the commit. or that can be also done with the flag:
```bash
git commit -m "message with the commit"
```

we can check the last commit done with the command:
```bash
git log
```

**git show HEAD** <- shows the HEAD info

to get to a branch
```bash
git checkout branchName
```
with this the **git checkout** command, moves the HEAD (the current point we are pointing in the repository) to the new "branchName", and at the same time, sets the files to point to the files at that point in "branchName". 

to save changes, that are not ready to commit, but that we dont want to lose either, the 'stash' command is used:
```bash
git stash
```
I can check the changes stashed with:
```bash
git stash list
```

this will list the pending changes. 


to pull the changes back, use:
```bash
git stash apply
```

if we check after that the stash list, we can see the stash is still in the list. 

it is also possible to use:
```bash
git stash pop
```
is the same as the stash apply, but it removes it from the stash list. 


to remove the changes pending, use.
```bash
git stash drop 
```

BRANCH CREATION
```bash
git branch MyNewBranchName OriginBranchName
```

```bash
git checkout MyNewBranchName 
```

TRACKING BRANCHES.

A tracking branch is a local branch that identifies itself with a remote branch. It usually is represented as <name_remote>/<name-local-branch>, for example: <origin>/<master> (origin stands for the remote master branch, and master is our local branch). 

For example when you create a repo by means of 'git clone' you are creating a tracking branch

but tracking branches update differently in local and remote branches. So tracking branches are only updated with network commands like: clone, fetch, push or pull

the command 'git branch' displays all the local branches. the command 'git branch --all' displays the local, remote and tracking branches, the command 'git branch -r' display all remote branches.

it is possible to change the remote tracking branch wit the command 'git remote set-head <remote> <branch>'
 
you can use 'git log --all' to see a log of all local and remote branches.

BRANCHING MERGING:


there are different types of merging:

- fast-fordward merge
- merge commit
- squash merge
- rebase

The **fast-fordward merge** moves the base of the master label to to the tip of the local/actual branch. the FF merge is only possible if no other commits have been done in the master branch since the local branch was branched out of the master branch. with a ff merge the history of the repo is lineal as there are no commits with multiple parents. Also no merge conflicts should exist due to the previous reason.

```bash
git checkout master
git merge mybranch
git branch -d mybranch
```

The **merge commit** actually merges the changes in two given branches.

```bash
git checkout master
git merge mybranch
echo "resolve conflicts if needed"
git branch -d mybranch
```

to merge banches, you invoque.

```bash
git merge mybranchname
```


if conflicts exists, those must be resolved. 

for this the merge tool is used, it is invoqued with:

```bash
git mergetool 
```

after solving the merging issues, if we request the status, the changes should appear

```bash
git status
```

then we can check the repository with the staging area: 

```bash
git diff --cached
```

then commit
```bash
git commit -m "message to commit branches"
```

then is safe to delete branch
```bash
git branch -d mybranchname
```


REBASE:

```bash
git rebase BranchToRebase
```

in case conflicts exists, use the merge tool:
```bash
git merge tool
```
once done, better to check:

```bash
git status
git diff --cache
```
then continue with the rebase:

```bash
git rebase --continue 
```

when a repo is created with clone, its rebase is automatically

BRANCHES:

a branch is the set of commits that trace back all the way to the project first commit. Actually a branch only implies to create a label that points to one commit, with will be the latest commit of the created branch.

to see a list of branches

```bash
git branch
```
the current branch will be marked with an asterisk

to see the list of the remote braches, you use the -r option

```bash
git branch -r
```

to create a branch:

```bash
git branch <newbranchname>
```
the act of creating a branch only creates a label.

then we use the 'checkout' command. it changes the current commit to the label of the checkout branch. So the HEAD reference, passes to point to the current commit, to the checkout branch. - it updates the working tree from the files from the checked out 

actually the 'checkout' command only updates the reference of the HEAD reference from the previous branch to the new desired branch. 

```bash
git checkout <branchname>
```

to indicate a specific commit, use its SHA1 identifier. this is useful for example if you want to view the code in a previous state of the project. beware, because then you can get into a detached head situation ( the HEAD is not pointing to a branch label)-

the detached head state is the situation in which the label HEAD points directly to a commit (that is not pointed by a brach label tag)

it is possible to unify the branch creation (git branch) and its checkout, with the option -b

```bash
git checkout -b <branchname>
```
this will create a new branch and checkout to it.

to list the remote branches:

```bash
git branch -r 
```
to delete a branch, just means to delete a branch label. to delete a branch we use the -d or -D options.

```branch
git branch -d <branchname>
```

NETWORK COMMANDS

these are the commands that allow to communicate to a remote repository

- git clone - copies a remote repo and creates a local repo.
- git fetch - gets the data from a remote repository. it updates the tracking branch information.
- git pull - is fetch + merge commands
- git push - add changes to the remote repository.
- git rebase - rebase is a form of merge, so there is possible to have merge conflicts. It moves the changes of a branch to the tip of another branch 


ADDING FILES.
 To track all of the changes to all of the files in our directory we should use the command git add -A.
 
 
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
- git log --oneline --decorate --graph
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
- git reflog
- git tag
- git daemon
- git format-patch
- git am



## SSH keypair setup for GitHub (or GitHub/GitLab/BitBucket, etc, etc)

### Create a repo.

Make sure there is at least one file in it (even just the README.md)

### Generate a SSH key pair (private/public):

```
ssh-keygen -t rsa -C "your_email@example.com"
```
	
or even better:

```
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```
	
### Copy the contents of the public SSH key

macOS:
```
pbcopy < ~/.ssh/id_rsa.pub
```
GNU/Linux (requires the xclip package):
```
xclip -sel clip < ~/.ssh/id_rsa.pub
```
Windows Command Line:
```
type %userprofile%\.ssh\id_rsa.pub | clip
```
Git Bash on Windows / Windows PowerShell:
```
cat ~/.ssh/id_rsa.pub | clip
```
or of course copy it via your favorite editor, cat, or whatever suits your needs :)

### Copy the public SSH key to GitHub

Copy the contents of the to your SSH keys to your GitHub account settings (https://github.com/settings/keys).
Test the SSH key:
```
ssh -T git@github.com -v
```
Change directory into the local clone of your repository (if you're not already there) and run:
```
git remote set-url origin git@github.com:username/your-repository.git
```
Now try editing a file (try the README) and then do:
```
git add -A
git commit -am "Update README.md"
git push
```
You should not be asked for a username or password. If it works, your SSH key is correctly configured.
	
### Updating a PR (pull request) in github
	
For updating a pull request in GitHub is as easy as committing the wanted changes into existing branch
(that was used with pull request), but often it is also wanted to squash the changes into single commit:

```
git checkout yourbranch
git rebase -i origin/master

# Edit command names accordingly
  pick   1fc6c95 My pull request
  squash 6b2481b Hack hack - will be discarded
  squash dd1475d Also discarded

git push -f origin yourbranch
```
	
...and now the pull request contains only one commit.

# GERRIT

ref: https://gerrit-review.googlesource.com/Documentation/intro-gerrit-walkthrough.html


Links:

https://www.kernel.org/ <br>
http://www.linux.org/ <br>
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
https://linux.die.net/HOWTO/HOWTO-INDEX/howtos.html  <br>
https://linuxconfig.org/  <br>
https://wiki.linuxfoundation.org/realtime/rtl/blog#the_jury_has_spoken   <br>
https://www.linux.com <br>
https://m.youtube.com/watch?v=JRyrhsx-L5Y&t=246s

https://0xax.gitbooks.io/linux-insides/content/Theory/linux-theory-1.html

GNU ARM embedded toolchain:  https://launchpad.net/gcc-arm-embedded

C library for embedded systems:  https://sourceware.org/newlib/

other small fast C library : https://musl.libc.org/

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

## USER SPACE AND KERNEL SPACE

### user space

user space is the part of the memory where all the user mode application run, and that memory can be swapped at any time, when necessary.

user space processes then run in its own virtual memory addresses space, and unless specifically requested cannot address the memory of other processes. (tring to read a memory out of their space is the famous segmentation faolt error).

### kernel space

kernel space is restricted and exclusively reserverd for running the kernel, kernel extension, modules and drivers.

linux kernel space gives full access to the hardware, 

http://www.ibiblio.org/pub/Linux/docs/faqs/Threads-FAQ/html/Types.html


user application 
 V
gnu glibc             ..........user space /\
 V
system call interface ............kernel space V
 V 
kernel
 V 
architecture dependant kernel code
 V 
hardware platform


## strace

https://linux.die.net/man/1/strace

strace is a commad to track and debug system calls and signals. you use it typing 'strace' + program. But it is useful to use the -o option (for output), so the command is: 'strace -o output.txt + argument_program'. The -c option (for count calls) give us a list of the used system calls. We can monitor only one type of system calls with the option -e + name_system_call (open,stat,chmod,unlink ...). to get a timestamp, you use the -t option or for a relative timestamp, the time between calls use the -r option. strace by default don't monitor the spawned processes, to check them also use the -f option. If the program we want to check is already running we can attach strace to it with 'strace -p <prog_PID>' 

## process evaluation 

as part of the package Psmic, it is possible to use the following programs: 

 - fuser: Reports the Process IDs (PIDs) of processes that use the given files or file systems
 - killall: Kills processes by name; it sends a signal to all processes running any of the given commands
 - peekfd: Peek at file descriptors of a running process, given its PID
 - prtstat: Prints information about a process
 - pslog: Reports current logs path of a process
 - pstree: Displays running processes as a tree
 - pstree.x11: Same as pstree, except that it waits for confirmation before exiting

## system analysis tools

https://linux.die.net/man/1/explain - explain system call error messages
https://linux.die.net/man/2/ptrace  - process trace
https://linux.die.net/man/1/pstack - print a stack trace of a running process
https://linux.die.net/man/1/nm    - list symbols from object files

tgkill  - send a signal to a thread - https://linux.die.net/man/2/tgkill
pmap - report memory map of a process  - https://linux.die.net/man/1/pmap


**dstat** - versatile tool for generating system resource statistics - https://linux.die.net/man/1/dstat

**smem** - Report memory usage with shared memory divided proportionally.

**backtrace** -returns a backtrace for the calling program - https://linux.die.net/man/3/backtrace

**dlopen** - The function dlopen() loads the dynamic library  - https://linux.die.net/man/3/dlopen

**uselib** - he system call uselib() serves to load a shared library to be used by the calling process - https://linux.die.net/man/2/uselib

**sar** - System Activity Report. https://linux.die.net/man/1/sar

Performance tools
ifstat(1), iftop(8), iostat(1), mpstat(1), netstat(1), nfsstat(1), nstat, vmstat(1), xosview(1)

mpatrol, a library for controlling and tracing dynamic memory allocations.
mpatrol - http://mpatrol.sourceforge.net/doc/index.html#Top

Debugging tools
htop(1), lslk(1), lsof(8), top(1),

efence - Electric Fence Malloc Debugger - https://linux.die.net/man/3/efence

Process tracing
ltrace(1), pmap(1), ps(1), pstack(1), strace(1), trace-cmd

- oprofile https://man7.org/linux/man-pages/man1/oprofile.1.html
- lltn   https://lttng.org/docs/#doc-getting-started

Binary debugging
ldd(1), file(1), nm(1), objdump(1), readelf(1)

Memory usage tools
free(1), memusage, memusagestat, slabtop(1), memcheck, valgrind

Accounting tools
dump-acct, dump-utmp, sa(8)

Hardware debugging tools
dmidecode, ifinfo(1), lsdev(1), lshal(1), lshw(1), lsmod(8), lspci(8), lsusb(8), smartctl(8), x86info(1)

Application debugging
mailstats(8), qshape(1)

Xorg related tools
xdpyinfo(1), xrestop(1)

Other useful info
collectl(1), proc(5), procinfo(8)

code coverage:
- **gcov**: http://gcc.gnu.org/onlinedocs/gcc/Gcov.html <br>
- **gcovr** : https://gcovr.com/en/stable/ <br>
- **lcov** : http://ltp.sourceforge.net/coverage/lcov.php <br>

performance:
- oprofile https://man7.org/linux/man-pages/man1/oprofile.1.html
- lltn   https://lttng.org/docs/#doc-getting-started
 

Valgrind http://www.valgrind.org/docs/manual/quick-start.html

gdb https://www.gnu.org/software/gdb/
libmcheck - Turns on memory allocation checking when linked to

libmemusage - Used by memusage to help collect information about the memory usage of a program

libcw  -  http://libcwd.sourceforge.net/

MM: http://www.engelschall.com/sw/mm/

mpr: http://freshmeat.net/projects/mpr/

for checking cpu performance: **lscpu**  ref: http://man7.org/linux/man-pages/man1/lscpu.1.html

A list of Linux tools that can be used to explore object/executable files.

 - **ar**: creates static libraries.
 - **objdump**: this is the most important binary tool; it can be used to display all the information in an object binary file.
 - **file**: displays object type an dinformations. 
 - **strings**: list all the printable strings in a binary file.
 - **nm**: lists the symbols defined in the symbol table of an object file.
 - **ldd**: lists the shared libraries on which the object binary is dependent.
 - **strip**: deletes the symbol table information.
 - **strace**
 - **trace-cmd**
 - **ltrace**
 - **readelf** 

other references: 

 - http://www.unknownroad.com/rtfm/gdbtut/gdbadvanced.html#CORE
 - http://www.brendangregg.com/bpf-performance-tools-book.html


## ABOUT OPEN SOURCE SOFTWARE LICENSES.

Mainly there are two types of licenses: restrictive and permisive

restrictive licenses: derivative works are intended to remain open, and changes must be made availables. Example: GPL (general public license) (aka copyleft)

permisive licenses: like BSD or Apache licenses. - dont need to be make public.

## Tips for hardening linux

 Keep boot dir as read-only.  # vi /etc/fstab	then, Add the following line at the bottom "LABEL=/boot/boot ext2 defaults,ro 1 2"	in case of upgrade we need to reset the change 

2. Review Logs Regularly 	in our case we have a log server that will be easy to modify local logs.	For example this is the dafault log files name and their usage: /var/log/message – Where whole system logs or current activity logs are available.	/var/log/auth.log – Authentication logs.	/var/log/kern.log – Kernel logs. /var/log/cron.log – Crond logs (cron job).	/var/log/maillog – Mail server logs.	/var/log/boot.log – System boot log. /var/log/mysqld.log – MySQL database server log file. /var/log/secure – Authentication log.	/var/log/utmp or /var/log/wtmp : Login records file.	/var/log/yum.log: Yum log files.

3. Monitor User Activity with psacct	Installing psacct Packages # yum install psacct	Starting psacct or acct service # chkconfig psacct on	# /etc/init.d/psacct start Display Statistics of Users Connect Time # ac	Display Statistics of Users Day-wise # ac -d	Display Time Totals for each User # ac -p	Display Individual User Time # ac username	Print All Account Activity Information # sa Search Logs for Commands # lastcomm ls

4. Disable SSH Login via Root

```
# useradd username	add password 
# passwd username	provide sudo permissions to the newly added use

r # echo 'username ALL=(ALL) ALL'
```
	
```
>> /etc/sudoers	now it's time to disable root login 	
 ```
 
  1. open the sshd configuration file # vi /etc/ssh/sshd_conf	
  2. uncomment the line 'PermitRootLogin no'	
  3. save and restart # service sshd restart

Search for the authentication options and change the root login permission by setting it to no like below.

```
PermitRootLogin no
```

Afterwards just save the file and exit the text editor.
	
Making changes to the SSH configuration file will require you to restart the service, on CentOS cloud servers use the following.

```
sudo systemctl restart sshd
```
	
On systems running Ubuntu, the service is simply called SSH, the same will work with Debian.

```
sudo service ssh restart
```

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

```
sudo apt-get install fail2ban
``` 

To configure, open up the configuration file in a text editor, find the services you want to have it watch (for example, SSH), and then restart the service.

10. Turn Off IPv6	# vi /etc/sysconfig/network	add the following lines "NETWORKING_IPV6=no	IPV6INIT=no"8. Lockdown Cronjobs	# echo ALL >>/etc/cron.deny

11. - - Check for open ports

If a service is listening on a port, it leaves the door open for possible exploit.

We can see what ports currently have services listening on them by running a quick command:

```
sudo netstat -tulpn
```

12. Disable USB Mount
One crucial method by which you can ensure higher security, especially against someone who can physically tamper with your computer is to ban them from using USB to attack it. There are many sophisticated USB-based malware which is activated automatically when the pen drive is inserted in your USB port, so this is a crucial tip to strengthen your Linux security. The only price you have to pay is to quit using USB drives all the time and find another method to safely transfer data. Here is how to do it:

Step 1: Open any text editor and write:

```
→ install usb-storage /bin/true
```

Step 2: Save the file as a .conf type of file and save in the following location:

```
→ /etc/modprobe.d/
```

Step 3: Restart your computer and test if you are able to mount a USB drive.

13. Enable Your Firewall
Basically, this is one thing that every self-respecting Linux user should do when they install a Linux distribution. It more of a security ethic advise, primarily because, even with the firewall disabled, Linux has all the ports locked down either way. But, you never know, if your computer will be targeted sooner or later, because someone with hardened security obviously has something to hide and people quickly realize this. To enable your Linux firewall, you must run the Linux Terminal after which type:

```
sudo apt-get install guf
```

GUFW stands for “Graphical Uncomplicated Fire Wall”. The command will install it and after it has finished doing so, you should open it, by typing in your terminal it’s abbreviation and hitting Enter

```
gufw
```

After you open GUFW you will see it’s simple user interface. From there simply click on the slider button next to Status to turn it from OFF to ON

14. Make your BIOS More Secure
This tip may not be directly Linux related but it is considered as a general security risk for most Linux distributions. After installing Linux on your computer, it is a good idea to disable any possibility of your computer to boot via USB, CD/DVD or other external drives. This means that nobody can overwrite your Linux and hence damage it or even try to access your drive by booting a Live OS. And this is just the tip of the iceberg of security threats when external boot is enabled. This is why, you should access BIOS on your system start up and go to the Boot tab from which disable the booting option from external drives:
Image: https://sensorstechforum.com/wp-content/uploads/2017/07/bios-boot-tab-sensorstechforum.jpg

In addition to these measures, add a BIOS password, which will stop someone with a physical access to your computer to enter the BIOS

15. Limit your pings or disable responding to pings

As lots of bots find your server by pinging, turning off pings is one way to help hide it (though this really only helps servers that you aren't driving the public to)

16. Use Firejail Sandboxing When You Try New Applications

In general, Linux operating systems are designed in order to be secure by default. But this does not mean that your online browsing is not exposed against any sniffing or phishing attacks – the main reason why you need to secure yourself against new browser extensions or apps that may be unwanted on your Linux machine. Firejail is one security app that is very simple to set up and works on the latest Linux distros. Here is how to set it up on 16.04 LTS Ubuntu:

```
sudo apt-get update
sudo apt-get install firejail
ls /etc/firejail
``` 

Now you have successfully entered a page where you should see the profiles of all the programs installed on your computer. They should look somewhat like the following:

skype.profile
dropbox.profile
icedove.profile
Tor.profile

If we would like to secure Tor web browser, for example, we can use the “firejail” command in the following syntax:

```
 firejail firefox
 ```
 
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

19. use Shadow with Cracklib, to enforce sstrong passwords: http://www.linuxfromscratch.org/blfs/view/9.0/postlfs/cracklib.html 


	
# HOW TO: LINUX REALTIME:

https://m.youtube.com/watch?v=BKkX9WASfpI

https://m.youtube.com/watch?v=BxJm-Ujipcg

https://lwn.net/Articles/743740/

https://lwn.net/Articles/743946/

https://lwn.net/Articles/821578/

https://www.kernel.org/doc/Documentation/scheduler/sched-deadline.txt

Using KernelShark to analyze the real-time scheduler https://lwn.net/Articles/425583/

# More references

Steven Rostedt - Learning the Linux Kernel with tracing - https://m.youtube.com/watch?v=JRyrhsx-L5Y&t=246s

Introduction to Memory Management in Linux - https://m.youtube.com/watch?v=7aONIVSXiJ8
 
 
 

Introduction to Linux Memory Management - Christopher Lameter, Jump Trading LLC https://m.youtube.com/watch?v=wbi6IZDIv_4

Pragmatic Guide to Boot-Time Optimization - Chris Simmonds - https://m.youtube.com/watch?v=gIK1he6Ocpg

https://elinux.org/images/7/70/Opdenacker-boot-time-ELC-2014.pdf&ved=2ahUKEwi4q9z1zPPrAhX66eAKHR6tCowQFjARegQIBhAB&usg=AOvVaw0a3KsXZ0owCVtYeSWwxc2L

Booting faster: https://m.youtube.com/watch?v=fTLsS_QZ8us

Making C Less Dangerous in the Linux kernel  https://m.youtube.com/watch?v=FY9SbqTO5GQ

How to compile the linux kernel  https://youtu.be/bBU7mT2lgPU

configuring linux kernel  https://m.youtube.com/watch?v=NVWVHiLx1sU    

core dump tutorial https://m.youtube.com/watch?v=h8mtQ1FyoA4


# NOTES ON SELINUX

## Introduction
	
reference: http://www.selinuxproject.org/page/Main_Page
	
Security Enhaced Linux (SELinux) is a Linux Kernel Security Module (aka LSM) that provides a mechanism for supporting access control security policies, 
including mandatory access control (MAC). SELinux is a label-based mandatory acess control. There are labeled processes on one side (subjects) and labeled
resouces (objects) on other side, and the "allow" rueles regulate the relationship of subjects and objects

 - subjects are the elememts that perform operations
 - objects are the elements in which operations are made on.

An example for a context: "u:object_r_etc_t:s0"

- u: user use
- Object_r: the role
- etc_t: the type
- s0: the multi-level-security (MLS) sensitivity level.

### MAC features

- Restricts/allows acess based on a centralized policy
- SELinux is an implementaion of MAC (mandatory access control)
- The owner of a resource doesn't decide on its access mode
- Everything is denied by default
- The kernel provides an MAC API: LSM (linux security module)
- MAC in not dependant of DAC (Discreccional Access Control). Both access have to be allowed
- Other LSM-based MAC implementations are: Smack, Tomoy, Yama

### Disadvantes

- Expensive setup. Big effort is required
- All the components need to be aligned with this policy development
- Complicated policy update process in a running system

## How SELinux is implemented

- The system is viewed as subject (processes) performing actions of objetcs (files, devices, ports ...)
- All subjects and all objects get a label. **Everything gets a label** 
- The **input** of the access control system are **requests**: Subject lable, operation and object label
- The **output** are **decisions**: Allow or Deny.

Lets see an example: a subject Alice, wants to read a document "My-Document" from a folder "Filling-Cabinet".

The subjet is Alice and there are two objects

- Object: My-Document
  - Class: file
  - type: My-Document_t
  
- Object: Filling cabinet
  - Class: cabinet
  - Type: Filling-cabinet
  
 step 1: opening the cabinet.
 
 Alice wants to read teh document "My-Document" form the folder "Filling-cabinet"
 
 Subject: Alice
 - Object type: Filling-cabinet
    - Class: cabinet
 - operation: 
    - open
	
 step 2: search for the document
 
  Alice wants to seach a cabinet of type Filling-cabinet_t
  
  Subject: Alice
  - object: Filling-cabinet
     - class: cabinet
  - operation: 
     - Search
	 
 step 3: opening the document
 
 Alice wants to oepn a file of type My-Document_t
 
 Subjetc: Alice
  - object: My-Document
    -class: file
  - operation: 
    - open
	
 step 4: reading the document
 
 Alice wants to read the file of type My-Document_t
 
 Subject: Alice
  - object: My-Document
    - class: file
  - operation:
      - read

 Summary: 
  Subject: Alice
  Objects: Filing-cabinet, My-Docuemnt
  Operations: cabinet:open, cabinet:search, file:open, file:search
  
  pseudo-code:
  
  ```
  allow Alice to { opean search } cabinet of type Filing-Cabinet_t
  allow Alice to { open read } file of type My-Docuemnt_t
  ```
  
  ## SELinux labels (aka context)
  
  A policy rule has to be created to define the acess of: 
  - user or domain
  - rol or object
  - type of operation
  - level acess
  
  ```
  user:role:type:level: category {.selinux-label}
  ```
  
  The label is the name of the rule. Once created the policy rule,
  the next step is to label the file system and processes in order to SELinux knows which rule policy has to be used in every case. 
  
  SELinux access control paradigms
  
  Labels (also known as context) is a string with 5 parameters: user, role, type, level and category
  
# Notes on AppArmor
	
AppArmor is other Linux security module
	
- ref: https://apparmor.net/
- ref: https://ubuntu.com/server/docs/security-apparmor#
	
AppArmor profile can work in two modes:

	- Complain mode: AA will gnerate a report on what the program is doing. This is useful, to know what a program does normally
	- Enforce mode: loaded a profile in enforme comde, and AA will prevent the program form doing anything it is not allowed to by the profile.  
