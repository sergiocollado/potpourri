# Notes on Linux start up process

## LSB (Linux Standard Base)

LSB is a joint project between the LF (Linux Foundation) and several Linux distributions, to promote and develop a set of open standards to increase 
compatibility among Linux distributions, and enable software application run on any compliant system even in binary form. 

https://refspecs.linuxfoundation.org/lsb.shtml

It is based on POSIX specifications

It standarize the software system architecture.

The standarization areas are:
- standard libraries
- commands and utilities
- filesystem Hierarchy Standard (FHS) https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html
- run levels
- the printing system
- boot facilities

## SysV-init boot process

SysV is the init system previous to Systemd. It is relevant to know how it works.

reference: https://web.mit.edu/rhel-doc/4/RH-DOCS/rhel-rg-en-4/ch-boot-init-shutdown.html

The basic stages of the boot process for an x86 system are:

   - The system BIOS checks the system and launches the first stage boot loader on the MBR of the primary hard disk.
   - The first stage boot loader loads itself into memory and launches the second stage boot loader from the /boot/ partition.
   - The second stage boot loader loads the kernel into memory, which in turn loads any necessary modules and mounts the root partition read-only.
   - The kernel transfers control of the boot process to the /sbin/init program.
   - The /sbin/init program loads all services and user-space tools, and mounts all partitions listed in /etc/fstab.
   - The user is presented with a login screen for the freshly booted Linux system.

reference: https://tldp.org/LDP/sag/html/init-process.html




### SysV Init Runlevels

reference: https://web.mit.edu/rhel-doc/4/RH-DOCS/rhel-rg-en-4/s1-boot-init-shutdown-sysv.html <br>
reference: https://tldp.org/LDP/sag/html/run-levels-intro.html

	The SysV init runlevel system provides a standard process for controlling which programs init launches or halts when initializing a runlevel. SysV init was chosen because it is easier to use and more flexible than the traditional BSD-style init process.

The configuration files for SysV init are located in the /etc/rc.d/ directory. Within this directory, are the rc, rc.local, rc.sysinit, and, optionally, the rc.serial scripts as well as the following directories:

```
init.d/
rc0.d/
rc1.d/
rc2.d/
rc3.d/
rc4.d/
rc5.d/
rc6.d/
```
The init.d/ directory contains the scripts used by the /sbin/init command when controlling services. 

### Runlevels

The idea behind SysV init runlevels revolves around the idea that different systems can be used in different ways. For example, a server runs more efficiently without the drag on system resources created by the X Window System. Or there may be times when a system administrator may need to operate the system at a lower runlevel to perform diagnostic tasks, like fixing disk corruption in runlevel 1.

The characteristics of a given runlevel determine which services are halted and started by init. For instance, runlevel 1 (single user mode) halts any network services, while runlevel 3 starts these services. By assigning specific services to be halted or started on a given runlevel, init can quickly change the mode of the machine without the user manually stopping and starting services.

        0 — Halt <br>
        1 — Single-user text mode<br>
        2 — Not used (user-definable)<br>
        3 — Full multi-user text mode<br>
        4 — Not used (user-definable)<br>
        5 — Full multi-user graphical mode (with an X-based login screen)<br>
        6 — Reboot <br>
        
        
![init_files](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/init_files.png)


