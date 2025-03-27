# NOTES ON LINUX KERNEL MODULES

References: 
 - https://lwn.net/Kernel/LDD3/  & http://www.makelinux.net/ldd3/?u=chp-5-sect-5.shtml
 - Linux Kernel module programming guide: https://linux.die.net/lkmpg/
 - kernel modules info: https://www.kernel.org/doc/Documentation/kbuild/modules.txt 
 - The Linux Kernel Module Programming Guide: https://sysprog21.github.io/lkmpg/
 - https://github.com/Johannes4Linux/Linux_Driver_Tutorial
 - Linux kernel in a nutshell: http://www.kroah.com/lkn/
 - How Linux is built with Greg Kroah-Hartman : https://www.youtube.com/watch?v=7WbREHtc5sU
 - The Linux Kernel Module Programming Guide 2001: https://tldp.org/LDP/lkmpg/2.6/html/index.html
 - Writing Portable Device Drivers: https://www.linuxjournal.com/article/5783
 - Eudyptula challenge: https://github.com/agelastic/eudyptula
 - hack the kernel: https://ops-class.org/
 - Kernel Play Guide: https://nskernel.gitbook.io/kernel-play-guide/accessing-the-non-exported-in-modules 
 - (404) EEC3-4029 Operating Systems: http://gauss.ececs.uc.edu/Courses/c4029/videos.html 
 - linux-kernel-labs: https://linux-kernel-labs.github.io/refs/heads/master/index.html
 - Linux explained: https://zedas.fr/tags/linux-explained/
 - How to build modules: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/kbuild/modules.rst 
 - Linux kernel makefiles: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/kbuild/makefiles.rst 
 - Kernel newbies : https://kernelnewbies.org/FirstKernelPatch 
 - Linux device drivers tutorials: https://embetronicx.com/linux-device-driver-tutorials/ 
 - about kallsyms_lookup_name() +5.7: https://xcellerator.github.io/posts/linux_rootkits_11/ 
 - linux device driver series: https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-part-1-introduction/ 
 - Let's code a Linux driver: Let's code a Linux Driver: https://www.youtube.com/watch?v=x1Y203vH-Dc&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa 
 - https://linux.die.net/HOWTO/KernelAnalysis-HOWTO-6.html 
 - Fast Linux Kernel Testing with QEMU: https://ncmiller.dev/2016/05/14/linux-and-qemu.html
 - The kernel API: https://www.kernel.org/doc/htmldocs/kernel-api/index.html 
 - reference: linux kernel API cheatsheet: https://www.cs.bham.ac.uk/~exr/lectures/systems/08_09/docs/kernelAPI/
 - https://www.youtube.com/watch?v=yO2orYVUYt0&list=PLsI2APLEA9Eq6z8zUlOJrqmc5KBwLTV4A&index=7
 - Operating Systems: Three Easy Pieces - https://pages.cs.wisc.edu/~remzi/OSTEP/
 - Kernel challenges: https://github.com/agelastic/eudyptula
 - Linux kernel memory model: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0124r6.html
 - https://sergioprado.blog/talks/


### How to setup an enviroment for kernel development & tools of the trade

- https://stackoverflow.com/questions/33676829/vim-configuration-for-linux-kernel-development
- https://cscope.sourceforge.net/large_projects.html
- https://marliere.net/posts/6/
- https://cscope.sourceforge.net/large_projects.html
- https://hackmd.io/@0xff07/BkYPoUb8Jg
- Mutt: https://dev.to/letsbsocial1/setting-up-and-using-the-mutt-email-client-in-linux-2ngh
- https://github.com/LukeSmithxyz/mutt-wizard
- mutt highlingint patches: https://github.com/jessfraz/dockerfiles/blob/master/mutt/.mutt/mutt-patch-highlighting.muttrc
- https://b4.docs.kernel.org/en/latest/
- https://wilw.dev/blog/2024/10/22/aerc/
- https://aerc-mail.org/
- vscode: https://youtu.be/ePsIEIxZs1c
- vscode: https://youtu.be/nmYaSqe0fGg

## What is a device driver.

A device driver is a code, that contrals a given tye of device in the compuer.

A device driver has three sides
- one side talks to the kernel
- one side talks to the hardware
- one side talks to the user. 

## What is a kernel module?

Tradicionaly the way to add code to the kernel was to recompile the kernel and reboot the system.

Kernel modules, are a pieces of code that can be load/inserted and unloaded/removed form the kernel whenever needed, so 
the kernel modules can be inserted and removed during runtime. 

It can be refered by other names:

- Loadable kernel modules (LKM)
- Modules

Its extension is .ko (Kernel Object)

Remark: **kernel modules are not always device drivers, but device drivers are always kernel modules.**

## Standard location for kernel modules

Modules are located in the /lib/modules/<kernel version> directory of the rootfs by default

to check them: 

```
cd /lib/modules/`uname -r`/
find . -name '*.ko' | wc -l # to count the number of kernel modules
```

### Loading kernel modules

Check the file at `/etc/modules-load.d/modules.conf`

```
  1 # /etc/modules: kernel modules to load at boot time.                             
  2 #                                                                                
  3 # This file contains the names of kernel modules that should be loaded           
  4 # at boot time, one per line. Lines beginning with "#" are ignored.              
  5 # Parameters can be specified after the module name.        
```
 - reference: https://www.cyberciti.biz/faq/linux-how-to-load-a-kernel-module-automatically-at-boot-time/

## Device drivers vs kernel modules

A kernel module doesn't have to be a device driver. 

A driver is like a sub-class of module

modules are used for:
- device drivers
- file system
- system calls
- network drivers: dirvers implementing a network protocol
- tty line disciplines: for terminal devices

## Advantages of kernel modules

1. All parts of the base kernel stay loaded all the time. Modules can save you memory, becasue they are loaded only
when they are requested to be loaded.

2. User would need to rebuild and reboot the kernel every time they would requier a new funcionality

3. A bug in driver which is compiled as a part of kernel will sotp system from loading, whereas module allows systems to load. 

4. Faster to mantain and debug

5. Makes it easier to manatain multiple machines on a single kernel base

## Disadvanteges of kernel modules

1. Size: Moudle management consumes unpeable kernel memory. A basic kernel with a number of modules loaded will consume more memory than an equivalen kernel with the dirvers compiled into th ekernel image itself. This can be an issue on machines with limited physical memory

2. As the kernel modules are loaded very late in the boot process, hence core funcionality has to go 
in the vase kernel (e.g. memory management)

3. Security. if you build your kernel statically and disalbe linux's dynamic module loading feature, youprevent runn-time 
modification of the kernel code.

## Configuration

In orden to suppor module, the kernel must have been build, with the following option enabled:
```
CONFIG_MODULES=y
```
To check if the modules can be applied on a system running check the kernel configuration on that system.

```
cd /boot
cat config-`uname -r` | grep CONFIG_MODULES
```

## Types of modules

- In-source tree, build-in modules, or static modules: modules present in the linux kernel source code, built in the kernel image. As those modules are build in the kernel, those modules cannot be removed and the memory of those modules is occupied permanently during run time.
- Out-of-tree or dynamic modules: modules not present in the linux kernel, those are compiled and linked separately to produce a .ko file. can be dinamically load and unload. 

All modules start out as "out-of-tree" developments, that can be compiled using the contex of a source-tree. 

Once a module gets accepted to be included (in the linux workflow mailing list), it becomes an in-tree module.

A kernel in which is running and out-of-tree module, it is said to be a __tainted kernel__. 

## User space vs Kernel space

When a OS like Linux is used, the code that runs in the CPU can be segregated as user space code and kernel space code. The kernel 
space code runs on the CPU the operation mode of the CPU is in privileged mode, so that code can reach many restricted resources of
the system as control settings, memory, processor instructions ... the user space code will run on non-privilged mode, or restricted 
mode, so it cannot reach those memory locations that it is not allowd to reach. 

If user space program, want any services of the operating system, then it has to use system calls to run those functions that run
in priviled mode. 

## Building external modules

reference linux kernel documentation: https://docs.kernel.org/kbuild/modules.html

## Basic commands

- `lsmod`: List modules, lsmod ges its information by reading the file /proc/module (previously) or /sys/module
- `modinfo`: module information, prints the information of the module.
- `insmod`: used like: `sudo insmod ./mymodule.ko` to load modules.
- `modprobe`: add or remove modules.
- `rmmod`: to remove modules.
- `depmod`: reports dependecies between modules.

 reference: https://www.tecmint.com/load-and-unload-kernel-modules-in-linux/
  
## Hello World kernel module
  
  In C/C++ programming the main() function is the entry point and exit point
  
  Kernel modules must have al least two funcions:
  - a start (initialization function): which is called when the module is loaded into the kernel
  - an end funcion (cleanup), which is called just befor it si removed
  
  This is done with the `module_init()` and `module_exit()` macros
  
 ### Licensing
  
  reference: https://docs.kernel.org/process/license-rules.html#kernel-licensing
  
  Module should specify which license you are using MODULE_LICENSE() macro
  
  - "GPL" GNU plublic lincese v2 or later
  - GPL v2
  - GPL and addictional rights
  - Dual BSD/GPL
  - Dual MIT/GPL
  - Dual MPL/GPL
  - Propietary (non-free-modules)
  
  In case a module doesn't specify a license, it can be compiled, although it will report a warning. It will be able to be loaded into the kernel, but reporting `module license unspecified taints kernel`.
  
  In case an incorrect license is defined, it will compile, but when the module is loaded, it will report that the kernel is tainted. 
  
  Nowadays the licensing is indicated with SPDX identifers: https://lwn.net/Articles/739183/
  
### Tainted kernel
  
  A taint kernel, means that it is not supported by the community. On top of that, some debuggin functionallyty and API calls may be disalbe when the kernel is tainted.
  
  The kernel may became tainted by several reasons:
   - uses of propietary license
   - use of stagin drivers (which are part of the kernel source code but not fully tested)
   - use of out-of-tree modules that are not include with the linux kernel source code
   - certain critical error conditions, such machine check exceptions and kernel oopses.
  
To check if a given moudle is tainted, check the file `/proc/sys/kernel/tainted`. If it retursn 0, the
kernel is not tainted, any other number, indicates the reason it why it is. To decode that number use
the script `kernel-chktaint`:  https://git.kernel.org/pub/scm/linux/kernel/git/torvals/linux.git/plain/tools/debugging/kerenl-chktaint
  
### Header files
  
  All kernel modules needs to include `linux/module.h` for macro expansion of module_init and module_exit.
  
  `linux/kernel.h` only for the macro expansion for the printk() log level.
  
### HelloWorldModule.c
  
```C
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros __init __exit */
  
MODULE_LICENSE("GPL")

static int __init test_hello_init(void)
{
      printk(KERN_INFO "%s: In init\n", __func__);
      return 0;
}
  
static void __exit test_hello_exit(void)
{
       printk(KERN_INFO "%s: In exit\n", __func__);
}
  
module_init(test_hello_init);
module_exit(test_hello_exit);
```
This module has an entry point, which is defined by the macro `module_init` and an
exit point defined by the macro `module_exit`.

  
### Compiling it
  
To compile the module, the kernel make file is needed
  
```bash
ls /lib/modules/'uname -r'/build/Makefile
```
  
use the make, with the -C option, that indicates to use the makefile indicated in the folder by -C
  
```bash
make -C /lib/modules/`uname -r/build/
``` 
just this, will not be enought. this makefile uses a makefile, so a small makefile needs to be added
  
 
```bash
cat Makefile
obj-m := hello.o
```
 
obj-m : stands for module. 
  
```bash
make -C /lib/modules/'uname -r'/build/ M={PWD} modules
```
 
The file .ko, should be generated 
 
At to this point, this is an out-of-tree module. To load it to the kernel, the 'insmod' command is used.
  
```bash
sudo insmod ./helloWorld.ko
lsmod # to check if the module indeed has been loaded
sudo rmmod helloWorld # to remove the module
```
  
In the code there is a 'printk', this is not printed in the console, for that the command 'dmesg' is needed.
  

### Compile and clean module commands

 To build a module, use:
 ```bash
  make -C /lib/modules/`uname -r`/build M=${PWD} modules
 ```
  
 To clean the module: 
 ```bash
  make -C /lib/modules/`uname -r`/build M=${PWD} clean
 ```
  
The `-C` option state to to change the directory provided, instead of using the current directory use the one provided by the -C option.
  
The `M=` argument causes the Makefile to move back into your module source directory before trying to build modules. 
  
The kernel Makefile will read the local makefile to findout what to build, this is indicated by writing: obj-m +=HelloWorldModule.o

### Cross compiling kernel modules
    
It is possible to emulate other architectures with QUEMU, and make developments for those other architectures, for that we need to cross compile.
  
There are two variables that the kernel uses to select the target architecture: 
  - ARCH
  - CROSS_COMPILE
  
The default vaues for both are found in the top-level Makefile and the values of both may be overridden on the command line.
  
ARCH: architecture targetes as the kernel knows it.
  
CROSS_COMPILE: set this to the prefix of your toolchain (including the trailing dash "-")
So if the toolchain is invoked as say x86_64-pc-linux-gnu-gcc, just remove the trailing gcc and that is what should be used: `x86_64-pc-linux-gnu-`.
  
example:
```bash
$ make ARCH=arm CROSS_COMPILE=arm-buildroot-linux-uclibgnueabi- -C /home/..../..../output/build/linux-X.Y:Z m=${PWD} modules  
```

 ### Overview of compiling kernel modules
  
  Kernel use the **kbuild** system to build the kernel modules. The kbuild system reads the assignment of `obj-m := modulename.o` from the local makefile. The the kbuild system knows that it has to build the "modulename.o" and will look for "modulename.c" for the source. 
  
   In case the files are not pressent in the directory passsed to `M=`, the compiling will stop with an error. If the files are present the source file is compiled to a modulename.", and "modulename.mod.c" is created which is compiled to "modulename.mod.o"
  
  The `modulename.mod.c` is a file that basically contains the information about the module (Version information etc)  
  
  The `modulename.o` and the `modulename.mod.o` are linked together by `modpost` in the next stage to create the `modulename.ko`
  
  The file `module.symvers` will contain any of the external symobls that is defined in your module and not present in the `module.symvers` of the kernel.
  
  The file `modules.order` is used in case several modules are compiled together, it will list out the order in which the compilation and creation of .ko is done. 
  
  
 ### Printk
 
 reference: https://www.kernel.org/doc/html/latest/core-api/printk-basics.html 

`printf()` is a function from the standard C library. `printk()` is a kernel level function.
  
`printk' function is called with one argumet:
  
 ```C
 printk(KERN_log_prority "hello world!");
 ```
 The log_priority is one of eight values, predefined in linx/kernel.h,
  
 - EMERG, ALERT, CRIT, ERR, WARNING, NOTICE, INFO, DEBUG, DEFAULT
  
 `printk()`writes in the kernel buffer.


### Error handling in the Kernel

 there are a number of predefined errors in the kernel tha cover most of the cases. Most general ones are defined in `inlcude/uapi/asm-generic/errono-base.h` and also in `include/uapi/asm-generic/errono.h`. For example: 

- https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno-base.h
- https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno.h

```C
#define	EPERM		 1	// Operation not permitted 
#define	ENOENT		 2	// No such file or directory 
#define	ESRCH		 3	// No such process 
#define	EINTR		 4	// Interrupted system call
#define	EIO		 5	// I/O error 
#define	ENXIO		 6	// No such device or address 
#define	E2BIG		 7	// Argument list too long 
#define	ENOEXEC		 8	// Exec format error 
#define	EBADF		 9	// Bad file number 
#define	ECHILD		10	// No child processes 
#define	EAGAIN		11	// Try again 
#define	ENOMEM		12	// Out of memory 
#define	EACCES		13	// Permission denied 
#define	EFAULT		14	// Bad address 
#define	ENOTBLK		15	// Block device required 
#define	EBUSY		16	// Device or resource busy 
#define	EEXIST		17	// File exists
#define	EXDEV		18	// Cross-device link 
#define	ENODEV		19	// No such device 
```

Usually the standard way to return an error is to do int in the `return -ERRORCODE`, in the case of an I/O error, it would be returning `-EIO`.

```
dev = init(&ptr);
if (!dev)
        return -EIO
```

In some cases the error, for exapmle in the case of system calls, can propaget to the user-space, in this case, the value will be automatically asigned to the user space `errono` global variable, in whic case is it posible to use the `strerror(errno)` to translate the error into a readable string.

In other cases, an error must undo everythinig upu to the point where the error happened. In this case the usual way is to use the `goto` statement. 

### Kernel types

references:
 -   Writing Portable Device Drivers: https://www.linuxjournal.com/article/5783
 -   https://ufal.mff.cuni.cz/~jernej/2018/docs/predavanja10.pdf
 -   https://static.lwn.net/images/pdf/LDD3/ch11.pdf
 -   https://kernelnewbies.org/InternalKernelDataTypes

Different processors define different variable sizes for int and long data types. They also differ in specifying whether a variable size is signed or unsigned. Because of this, if you know your variable size has to be a specific number of bits, and it has to be signed or unsigned, then you need to use the built-in data types. The following typedefs can be used anywhere in kernel code and are defined in the linux/types.h header file:

```
u8    unsigned byte (8 bits)
u16   unsigned word (16 bits)
u32   unsigned 32-bit value
u64   unsigned 64-bit value
s8    signed byte (8 bits)
s16   signed word (16 bits)
s32   signed 32-bit value
s64   signed 64-bit value
```

One thing that has caused a lot of problems, as 64-bit machines are getting more popular, is the fact that the size of a pointer is not the same as the size of an `unsigned integer`. The size of a pointer is equal to the size of an `unsigned long`. This can be seen in the prototype for `get_zeroed_page()`:

```
extern unsigned long FASTCALL
    (get_zeroed_page(unsigned int gfp_mask))
```

There are some native kernel data types that you should use instead of trying to use an unsigned long. Some of these are: `pid_t`, `key_t`, `gid_t`, `size_t`, `ssize_t`, `ptrdiff_t`, `time_t`, `clock_t` and `caddr_t`. If you need to use any of these types in your code, please use the given data types; it will prevent a lot of problems.
Memory Issues

Please remember: ** The size of a pointer is equal to the size of an `unsigned long`.**

  
### Simplified makefile
  
So to build a module, the command is use:
  
```bash
make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
```
  
and to clean the module, the command:
  
```bash
make -C /lib/modules/ùname -r/build M=${PWD} clean
```

This is a bit bothersome, so a new makefile can be used:
  
```bash
obj-m := hello.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean
```

### What happens when we do `insmod` in a module
  
  The kernel module is a piece of kernel code (.ko in elf format) which can be added to the running kernel, and when loaded can be removed from the kernel.
  
1- It calls init_Module() to inform the querken that a module is attemp to be loaded an transfers the control to the kernel 
  
2- In the kernel, `sys_init_module()`is run. It does the following operations
  - Verify that the user has the permissions to load the module
  - The load_module function is called
  - The load_module function assigns temporary memory and copies the elf module from the user space to kernel memory using 'copy_from_user'.
  - Checks the sanity of the ELF file.
  - Based on the ELF file interpretation, it generates offset in the temporary memory space allocated. This is called the convenience variables
  - User arguments to the module are also copied to the kernel memory
  - Symbol resolution is done
  - The load_module function returns a reference to the kernel module.
  - The reference to the module returned by load_module is added to a doubly linked list that has a list of all the modules loaded in the system.
  
  
### What happens if a -1 is returned from the init function.
  
Tradicionaly in linux a function that returns zero means success, and a non zero means failure.
  
The loading of the module would fail, and the module will not be loaded. It can be tested with lsmod.
  
### How to give another name to a module.

modify the makefile like:
  
```bash
obj-m := linux.o
linux-objs := hello.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean  
```
  
if we check the name of the modules, with lsmode, we would find the linux module
  
### Module composed of several files
 
We can have a module in several files. For example:
  
HelloWorldModule.c:
  
```C
  #include <linux/kernel>
  #include <linux/module>
  
  MODULE_LICENSE("GPL")
  
  static int __init test_hello_init(void)
  {
      printk(KERN_INFO "%s: In init\n", __func__);
      func();
      return 0;
  }
  
  static void __exit test_hello_exit(void)
  {
       printk(KERN_INFO "%s: In exit\n", __func__);
  }
  
  module_init(test_hello_init);
  module_exit(test_hello_exit);
```
 
and the file func.c:
```
#include <linux/kernel.h>
void func(void)
{
    printk(KERN_INFO "Hey there!");
}
```

The module must be udpated, to add the file:
  
```bash
obj-m := linux.o
linux-objs := hello.o func.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`name -r`/build M=${PWD} clean  
```

### Two kernel modules in a single makefile

You can use a single makefile to generate more than one modules.

  ```bash
obj-m := hello1.o
obj-m += hello2.o
# or also obj-m := hello1.o hello2.o

all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean  
```

### dmesg command
  
`dmesg` is used to control or print the kernel ring buffer, that has the log of the kernel eveents
  
The kernel keeps all the event logs in a ring bugger. This is done to avoid the boot logs being lost until the syslog daemon starts and collects them and stores them in /var/log/dmesg.
  
- to clear the ring buffer. You may need to lauch it with sudo (for permissions)
 ```
  dmesg -c # will clear the ring buffer after printing (by default in the console). C stands for Clear
  dmesg -C # will clear the ring buffer, but will not print its contents
 ```

- to don't print the time stamps
 ```
  dmesg -t # will not print the timestamps
 ```
- restrict dmesg command to list of levels
 ```
  dmesg -l err,warn # will print only error and warn messages
 ```
- print human readable timestamps
 ```
  dmesg -T # will print timestamps in readable format. watch out! the timestamp could be inaccurate.
 ```
- Display the log level in the output
 ```
  dmesg  -x # will print the log level in the output
 ```
- You can combine the options, so dmesg -Tx will print both human friendly and loglevel
 ```
  dmesg -Tx
 ```
- To follow/update messages
 ```
  dmesg -w & # the & is to run it in background. 
 ``` 

### Is possible a kernel module without an exit function?
  
When there is not exit function, the module will not be possible to be removed. When try to be removed, it
will report an EBUSY module. This is defined in `kernel/module.c` at `SYSCALL_DEFINE2(delete_module, ...`
  
### kernel module without an init function?
  
The module may be loaded, but it will do nothing at the beginig. This is defined at kernel/module.c at `SYSCALL_DEFINE3(init_module, ...`

### insmod vs modprobe
  
- `insmod` loads the module given 0insmod /path/to/module.ko' 
- `modprobe` loads the module only in /lib/modules/$(uname -r) 'modprobe /home/test/hello.ko' will not work
  
- `insmod` dependencies if present are not loaded
- `modprobe` calculates dependencies, and loads the dependencies and then the main module.
  
`modprobe` depends on the tool `depmod`to calculate the dependencies. `depmod` calculates the dependencies of all the modules present in /lib/modules/$(uname -r) folder, and places the dependencies information in /lib/modules/$(uname -r)/modules.dep file. See `man depmod`.
  
 It is possible to reload the modules.dep file with `depmod -a`


### Example using modprobe 

#### Get a Count of the Current Installed Modules and Save It to /root/current_count.txt

Display all the loaded modules:
```
lsmod
```
Save the count of all the loaded modules to /root/current_count.txt:
```
lsmod | wc -l > /root/current_count.txt
```

#### Remove the target_core_mod Module and All Its Dependencies

To remove the target_core_module, the iscsi_target_mod dependency must be removed (the -v option can be used to display additional information):
```
modprobe -r iscsi_target_mod
```
Validate the modules have been removed:
```
lsmod | grep target
```

#### Install the nfsd Module

Install the nfsd module using the modprobe command (the -v option can be used to display additional information):

```
modprobe -v nfsd
```
Validate that the module was loaded:
```
lsmod | grep nfsd
```

#### Display the Dependencies for the nfsd Module and Save the Names to /root/dependencies.txt

Display information for the nfsd module:
```
modinfo nsfd
```
Save the names of the dependencies to /root/dependencies.txt:
```
modinfo nfsd | grep depends > /root/dependencies.txt
```
#### Get a Final Count of the Modules and Save It to /root/updated_count.txt

Add the output from lsmod | wc -l to the /root/updated_count.txt file:
```
lsmod | wc -l > /root/updated_count.txt
```


### Understanding module_init & module_exit functions
  
 On `insmod` the function passed in the `module_init` is called, and on `rmmod` the argument passed in `module_exit` is called
  
 Lets review the definiton of thos macros, defined in linux/module.h
  
 ```
  /* Each module must use one moude_init(). */
  #define module_init(intifn)                \
      static inline intcall_t __inittest(void)      \
      { return initfn; }           \
      int init_module(void) __attribute__((alias(#initfn)));
  
  /* This is only required if you wnat to be unloadable. */
  #define module_exit(exitfn)          \
      static inline exitcallt_t __exittest(void)     \
      { return extinfn; }           \
      void cleanup_module(void) __attribute__((alias(#exitfn)));
 ```
 
The purpose of defining `__inittest` function is to check during compile time, the function passed to `module_init()` macro is compatible wit the `initcall_t` type
  
`initcall_t` is defined in linux/init.h (is defined as a function pointer)
  
  ```
  typedef int (*initcall_t)(void);
  ```
  
 If it is declared a module_init functino which returns void instead of int, the compiler will thrown a warning
  
  The gcc attribuete alias is used to sepcify multiple aliases (other names) for a given symbol (function/variable)  
  
  The `alias` attribute of gcc is used to assign another name to the init module, so you can have a better name for tye driver. ( eg. cdrom_inint instead of initd_modue), so not each driver has a init_module named function. 
  
  It is possible to create a module without a `module_init` or `module_exit` functions, if the module had init_module(void) and cleanup_module(void) functions. But we would lost the chance to have dedicated names for those functions. 

 ### Passing  command line arguments/parameters to kernel modules

  - reference: https://tldp.org/LDP/lkmpg/2.6/html/x323.html
  - reference: https://sysprog21.github.io/lkmpg/#passing-command-line-arguments-to-a-module
  - reference: https://litux.nl/mirror/kerneldevelopment/0672327201/ch16lev1sec6.html
  
 It is possible to pass parameters to a module. Passing parameters may be interesting to change the behavior of the module, for example to enable/disable debug logs, or tu suppor different workgin modes. 
  
  The macros for passing parameters are: 
  - `module_param()`
  - `module_param_array()`
  - `module_param_string()`
  - `MODULE_PARM_DESC()` for documenting arguments
  
  Passing parameters to a module is declared in `moduleparam.h` file
  
  ```
  #define module_params(name, type, perm)
     module_param_named(name, name, type, perm)
  ```
  
   - name: name of the variable
   - type: type of the variable. Supported types are charp (char pointer) , bool, invbool (inverse bool), long, chort, uint, unlong, ushort 
   - perm: permissions for the sysfs entry
      - `S_IRUGO`: Only read by all users
      - `S_IWUSR`: Only write by all users
      - 0 : No sysfs entry
        
  It is possible to use numberic values line 0644 for permissions entry.
  
  Example: 
  ```C
  #include <linux/kernel.h>
  #include <linux/module.h>
  
  MODULE_LICENSE("GPL");
  char* name = "Embedded";
  int loop_count = 1;
  module_param(name, charp, S_IRUGO);
  module_param(loop_count, int, S_IRUGO);
  
  static int test_arguments_init(void) 
  {
      int i; 
      printk(KERN_INFO"%s: In init\n", __func__);
      printk(KERN_INFO"%s: Loop count: %d\n", __func__, loop_count);
      for( i = 0; i < loop_count; i++) 
          printk(KERN_INFO"%s: Hi %s\n", __func__, name);
      return 0;
  }
                                 
  static void test_arguments_exit(void)
  {
       printk(KERN_INFO"%s: In exit\n", __func__);                              
  }
  
  module_init(test_arguments_init);
  module_exit(test_arguments_exit);
  MODULE_AUTHOR("Nemo");
  MODULE_DESCRIPTION("Arguments Passing Example");
  ```
  
  This module can be tested with:
                                 
 ```
 sudo dmesg -C  // clean system logs buffer
 sudo insmod ./arguments.ko
 dmesg         
 // or you can use also dmesg -WH & previous to loading the module
 ```
 to give value to the parameter
  
 ```
 sudo rmmod arguments                                
 sudo dmesg -C
 sudo insmod ./arguments.ko loop_count=5 name="Nemo"
 dmesg                          
 ```
  
  If we use `modinfo` it will report the usage of parametes in the modules.
                                 
  Also if check `/sys/module/arguments/parameters/` the parameters are visible, and you can `cat` their values. So in case it is needed to check the values of already loaded modules, it is possible to check them in this way.
  
  In the case if incorrect values are passed to the module parameters, an error reporting invalid parameters will appear.
                                
  For module parameters of builtin modules, those are passed throught the command line: <br>
  syntax: `<module_name>.<parameter_name>=value` <br>
  
  To pass parameter to modules loaded with `modprobe` this is used with th efile `/etc/modprobe.conf', modprove reads that file for the parameters.
  
  To pass multiple words as a parameter, has to be done like: 
  ```
  sudo insmod ./module_name.ko name='"Hello World!"' 
  ```
  
  This happens because if we only use simple quotes `''` or double quotes `""` the shell removes hos quotes an passes it to `insmod`, so about add single quotes over a string. 
  
  In case it is needed to pass an array as a parameter, then it is needed to use the macro `module_param_array()`, instead of the `module_param()` function
  
  ```
  # define module_param(name, type, perm)
  
  - module_param_array: a parameter which is an array 
  - @name: the anme of the arrray variable
  - @type: tye type 
  - @nump: optional pointer filled wiin with the nuber written
  - @perm: visibility in sysfs
  
  #define module_param_array(name, type, nump, perm)
  ```
  
  and to pass the array parameter: <br>
  ```
  sudo insmod ./module_name.ko param_array=1,2,3
  ```  
  
  and example: 
  
  ```C
  #include <linux/kernel.h>
  #include <linux/module.h>
  #include <linux/moduleparam.h>
  
  MODULE_LICENSE("GPL");
  
  int param_array[4];
  static int argc_count = 0;
  module_param_array(param_array, int, &argc_count, S_IWUSR | S_IRUSR);
  
  static int __init test_arguments_init(void)
  {
          int i = 0;
          printk("%s\n", __func__);
          printk("%Argc count:%d\n", argc_count);
          printk("Array elements:\n");
          for (i=0; i < sizeof(param_array)/sizeof(param_array[i]); ++i) {
              printk("%d:\t%d\n", i, param_array[i]);                                                         
          }
          return 0;
  }
                                                                   
  static void __exit test_arguments_exit(void)
  {
          printk("%s\n", __func__);                      
  }
  
  module_init(test_arguments_init);
  module_exit(test_arguments_exit);
  MODULE_AUTHOR("Nemo");
  MODULE_DESCRIPTION("Arguments Passing Array Example");
  ```
 
### Symbols and symbol table

A symbol is a name given to a space in memory, like: data (variables) or instructions (functions). 
                                                                   
A symbol table is a data strcuture created by the compiler containing all the symbols used in the program.
                                                                   
Every kernel image build has a symbol table with it. The Linux kernel symbol table contains names and addresses of all the kernel symbols. When the kernel is installed it will be pressen in `/boot/System.map-<linux-version>
 
TODO: GET SCREENSHOT EXAMPLE!!
  
When a new function is defined in a moudle, the default behavior of this function is local, only the
module which the function is defined can access it, it cannot be accessed by other modules
  
  To export this module it is needed to use EXPORT_SYMBOL or EXPORT_SYMBOL_GPL
  
- `EXPORT_SYMBOL' : the exported symbol can be used by any kernel module
- `EXPORT_SYMBOL_GPL` : the exported symbol can be used by only GPL licensed code.
  
  
The difference between System.map and /proc/kallsyms
  
 - `/proc/kallsysms`: contains the symbols of dynamically loaded modules as well as builtin modules
 - `system.map` : contains symbols of only builtin modules.
  
Example of exporting a function:
  
```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
 
MODULE_LICENSE("GPL");
 
void print_jiffies(void)
 {
     printk(KERNEL_INFO "%s: Jiffies:%ld\n", __func__, jiffies);
 }
  
static int test_export_init(void)
{
     printk(KERN_INFO "%s: In init\n", __func__);
     return 0;
}

static void test_export_exit(void)
{
     printk(KERN_INFO "%s: In exit\n", __func__);  
}
  
EXPORT_SYMBOL_GPL(print_jiffies);
  
module_init(test_export_init);
module_exit(tests_export_exit);
```

To check if the symbol has ben exported, load it: `sudo insmod ./symbold_export.ko'  and check: `cat /proc/kallsyms | grep print_jiffies`
 
  
 ### Export a variable or a function
  
Use: `EXPORT_SYMBOL(<variable_name>)`.
  
You can check how the macro is defined here: https://elixir.bootlin.com/linux/latest/source/include/linux/export.h#L56
  
To check if it was exported, use: `cat /proc/kallsyms | grep <exported_symbol>`
  
  
 ### Module stacking
  
  Module stacking is when new modules use the symobls exported by previous loaded modules.
  
  Example: 
   1. A moudle which exports  function that performs an addition
   2. A second module which uses the exported function 
  
 ```C
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros __init __exit */  
  
MODULE_LICENSE("GPL")

int myadd(int a, int b) 
{
    pr_inf("%s: Adding %d with %d\t Result:%d\n", __func__, a, b, a+b);
    return a+b;
}
  
EXPORT_SYMBOL(myadd);

static int module1_init(void)
{
    pr_info("%s: In init\n", __func__);
    return 0;
}
  
static void module1_exit(void)
{
    pr_info("%s: In exit\n", __func__);  
}
  
module_init(module1_init);
module_exit(module1_exit);
```

```C
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros __init __exit */  
  
MODULE_LICENSE("GPL")
  
extern int myadd(int a, int b);
  
static int module2_init(void)
{
    pr_info("%s: In init\n", __func__);
    pr_info("%s: Add:%d\n", __func__, myadd(3, 5));
    return 0;
}
  
static void module2_exit(void)
{
    pr_info("%s: In exit\n", __func__); 
}
  
module_init(module2_init);
module_exit(module2_exit);
```
  
the makefile:
```
obj-m := module2.o
obj-m += module1.o
  
all: 
     make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
     make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
 
  
If the module 2 is loaded fist, it will report an error: Unknown symbol in module, because module2 depends on module1.
  
First the module1 is loaded: `sudo insmod ./module1.ko´ <br>
Next, verify if the symbols was indeed exported with: `sudo cat /proc/kallsyms | grep myadd' 
  
Then load the second module: `sudo insmod ./module2.ko`
  
For using `modprobe`:
  
  ```bash
  sudo ln -s /<full_path>/module1.ko /lib/modules/$(uname -r)/kernel/drivers/misc  # create soft links
  sudo ln -S /<full_path>/module2.ko /lib/modules/$(uname -r)/kernel/drivers/misc
  
  sudo depmod -a
  
  sudo modprobe module2
  
  # check lsmod, module1 shoud be automatically loaded.
  ```
  
### Version magic
  
version magic: `vermagic` is a string present in the Linux kernel and added into the .modinfo section of the Linux kernel modules.
  
It is used to verify wheter the kernel module was compiled for the particular kernel version or not.
  
When loading a module, the strings in the vermagic value are checked if they match. In case the strings don't match, an error will be reported and the module will not be loaded. 
  
 `VERMAGIC_STRING` is generated by the kernel configuration.
  
  ``` 
  #define VERMAGIC_STRING  \
     UTS_RELEASE " " \
     MODULE_VERMAGIC_SMP MODULE_VERMAGIC_PREEMT \
     MODULE_VERMAGIC_MODULE_UNLOAD MODULE_VERMAGIC_MODVERSIONS \
     MODULE_ARCH_VERMAGIC \
     MODULE_RANDSTRUCT_PLUGIN
  ```
  
 ```C
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/vermagic.h>     /* Needed for vermagic */
  
MODULE_LICENSE("GPL")

static int vermagic_init(void)
{
    pr_info("VERMAGIC_STRING = " VERMAGIC_STRING "\n");
    return 0;
}
  
static void vermagic_exit(void){}
  
module_init(vermagic_init);
module_exit(vermagic_exit);  
```
 
 To check the vermagic of a module: ' sudo modinfo ./<module_name>.ko`
  
 To change the value of vermagic, use: `MOUDLE_INFO()`.
  
 ```C
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/vermagic.h>
  
MODULE_LICENSE("GPL")

static int vermagic_init(void)
{
    pr_info("VERMAGIC_STRING = " VERMAGIC_STRING "\n");
    return 0;
}
  
static void vermagic_exit(void){}
  
module_init(vermagic_init);
module_exit(vermagic_exit);  
MODULE_INFO(vermagic, "123454321");
```
  
### Module metadata
  
To find the version of a given .ko file, what kernel was it build for? using the `modinfo` command, that will report the vermagic number, and with that the kernel version is known.
  
Metadata can be added to a module, with the macros:
  
  - MODULE_DESCRITION: short description of the module.
  - MODULE_AUTHOR: declares the author. If there are several authors, this macro can be used several times.
  - MODULE_VERSION: sets de version of the module.
  
It is possible to add custom iformation like: `MODULE_INFORMATION(<your_tag_name>, <your_tag_value>)`
  
### objdump of a .ko file
  
 A .ko file is an ELF object. And ELF object file consist on various named sections, for example the .text 
section contains the executable code that the loaded loads. 
  
To see all the sections:
```
objdump --section-heades ./<module_name>.ko  
```
 
To see the contents of the .modinfo section

```
objdump --section-heades --section=.modinfo --full-contents ./<module_name>.ko
```

TODO: check if you can use `nm` with the .ko objetc.

### How to dump a kernel stack
  
Calling `dup_stack()` will cause a stack trace to be printed at that point.

So a sample module:
  
```C
#include <linux/module.h>
#include <linux/kernel.h>
  
MODULE_LICENSE("GPL");
static int myinit(void)
{
    pr_info("dump_stac myinit\n");
    dump_stack();
    pr_info("dump_stack after\n");
    return 0;
}
  
static void myexit(void)
{
    pr_info("myexit\n");  
}
module_init(myinit);
module_exit(myexit);
```
  
### kernel panic
  
A kernel panic is an error in the kernel code. On a kerenl panic, the kernel stop running immediately to 
avoid data loss or other damage.
  
The reason to stop running is to protect the computer. 
  
Possible reason:
 - Hardware of software issue (for example unable to finish or complete the init process)
 - Bug in kernel driver
 - Incompatible devices (like RAM)
  
When the kernel decides to Panic, it calls the `panic()` function, which dumps some debug information
and depending on the configuration reboots the system.
  
By default, the kerenl will not reboot on kernel panic. There are two ways to instruct the kerenl to reboot:
 
  - kernel command line: add "panic=N" to the kernel command line, so the kernel reboots after N seconds
  - Proc file system: `echo N > /proc/sys/kernel/panic`, for the kernel to reboot after N seconds on reboot. Notice this setting is not persistant after reboot. 
  
An example of a force panic: 
  
```C
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
  
static int test_panic_init(void)
{
    printk(KERN_INFO "%s: In init\n", __FUNC__);
    panic("Hello kernel! I'm causing the PANIC!!\n"); // this will shut down or reboot depending on the options.
    return 0;
}
  
static void test_panic_exit(void)
{
    printk(KERN_INFO "%s: In exit\n", __FUNC__);
}
module_init(test_panic_init);
module_exit(test_panic_exit);
```
  
### kernel Oops
  
an oops is similar to a segfault in user space. The kernel throws oops message when an exception such as
accesing invalid memory location happens in the kernel code.
  
Upon oops, the kernel perfomrs the following operation:
  
 - kills the offencidng process
 - prints information which can helpl the developeers to debug
 - continues execut9oin. Note: after oops, the system cannot be trusted further as the some of the locks or structures may not be cleaned up
  
An oops message contains the following information:
 - processor status
 - contents of the CPU registers at the time of exception
 - stack trace
 - call trace
  
An example to force an Oops
  
  
```C
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
  
static int test_oops_init(void)
{
    printk(KERN_INFO "%s: In init\n", __FUNC__);
    // try to dereference an invalid location
    *(int*)0x13 = 'a';
    return 0;
}
  
static void test_oops_exit(void)
{
    printk(KERN_INFO "%s: In exit\n", __FUNC__);
}
module_init(test_oops_init);
module_exit(test_oops_exit);
```
  
### Kernel BUG_ON()/BUG() and WARN_ON()
 
reference: https://kernelnewbies.org/FAQ/BUG
  
BUG_ON() is a macro. It is used as:
  - BUG_ON(condition)
  - if (condition) BUG()
  
BUG_ON() It does:
  - prints content of the registvers.
  - prints stack trace.
  - current process dies.
  
WARN_ON() macro does:
  - prints the contents of the registers.
  - prints stack trace. 

### Prepocessor symbols in the `Makefile`
    
```
obj-m := hello.o
  
# kbuild undestands a make variable named CFLAGS_modulename.o to add specific C flags when compiling this unit
CFLAGS_hello.o := -DDEBUG
# this will be applied to all of the source files compiled for your module withthe makefile
# ccflags-y := -DDEBUG
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean
```
  
  
```C
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
  
static int test_hello_init(void)
{
#ifdef DEBUG
    printk(KERN_INFO "%s: In init\n", __FUNC__);
#endif
    return 0;
}
  
static void test_hello_exit(void)
{
#ifdef DEBUG
    printk(KERN_INFO "%s: In exit\n", __FUNC__);
#endif
}
  
module_init(test_hello_init);
module_exit(test_hello_exit);
```  

 ### Process management in the Linux kernel
  
  The number of CPUs in the system is determined by checking the file `/proc/cpuinfo`, there is the information about all the processors. You can run: `cat /proc/cpuinfo | grep processor | wc -l`. 
  
   Also the instruction: The function `get_nprocs_conf()` returns the number of processors configured by the operating system. he function `get_nprocs()` returns the number of processors currently available in the system. Ref: https://linux.die.net/man/3/get_nprocs. Also the macro: `num_online_cpus()`, Ref: https://0xax.gitbooks.io/linux-insides/content/Concepts/linux-cpu-2.html
  
  
  The Linux kernel internally refers to processes s tasks. The kernel stores a list of process in a circular doble linked list called the task list. 
  
  The Linux kernel scheduler task unit, is the thread, not a program. 
  
  Each task/process/thread is represented in kernel in the struct task_struct, deffined at 'linux/sched.h'. 
  
  Lets try to write a module which reads the circular lined list and prits the following information: name, id, state. 
  
  The different states of a task are:
  
  - TASK_RUNNING (R (running)): task is either currently running or on a run-queu wainting to run
  - TASK_INTERRUMPIBLES (S (sleeping)): Task is sleeping/blocked. CAn be runnable/awaekn by a signal
  - TASK_UNINTERRUMPIBLE (D): Similar to TASK_INTERRUMPIBLE, but doesn't wake up on a signal
  - TASK_STOPPED (T): Process execution has stopped. This happens when he task receives: SIGSTOP, SIGTSTP, SIGTTIN or SIGTTOU signals or if it receives any signal while it is being debuggerd. 
  
  You can retrieve those statuses using the command 'ps -el'
  
  ```C
  #include <linux/kernel.h>
  #include <linux/module.h>
  #include <linux/sched/signal.h>
  
  char buffer[256];
  char* get_task_state(long state)
  {
      switch (state) {
          case TASK_RUNNING:
              return "TASK RUNNING";
          case TASK_INTERRUPTIBLE:
              return "TASK INTERRPTIBLE";
          case TASK_UNINTERRUPTIBLE:
              return "TASK UNINTERRUPTIBLE";
          case __TASK_STOPPED:
              return "__TASK_STOPPED";
          case __TASK_TRACED:
              return "__TASK_TRACED";
          default:
          {
              sprintf(buffer, "Unknown type:%ld\n", state);
              return buffer;
          }
      }
  }
  
  static int test_task_init(void)
  {
      struct task_struct* task_list;
      unsigned int process_count = 0;
      /* define for_each_process(p) <
         for (P = &init_task; (p = next_task(p)) != &init_task; )
         */
      for_each_process(task_list) {
          pr_info("task: %s\tPID:%dtate:%s\n", task_list->comm, task_list->pid, get_task_state(last_list->state));
          process_count++;
      }
      pr_info("Number of processes: %u\n", process_count);
      return 0;
  }
  
  static void test_task_exit(void)
  {
      pr_info(%s: in exit\n", __func__);
  }
                                         
  MODULE_LICENSE("GPL");
  module_init(test_tasks_init);
  module_exit(test_tasks_exit);
  ```
  
  So, when writing a module, to retrieve information about the current working process that is running in the kernek, it is needed to read the `task_struct` of the corresponding process.
  
  The kernel provides an easy way to do this, by means of the macro `current`, which alwiays returns a pointer to the current executing process task_struct.  This macro has to be implemented for each architecture. Some architectures store this in a register while other store them in the botom of the kerel stack of processes. 
  
 ```C
 #include <linux/module.h>
 #include <linux/init.h>
 #include <linux.sched.h>
 #include <asm/current.h>
  
static void current_exit(void)
{
   printk("current pid: %d, current process: %s\n", current->pid, current->comm);
}

static int current_init(void)
{
   printk("current pid: %d, current process: %sn", current->pid, current->comm);
}
  

module_init(current_init);
module_exit(current_exit);
```
  
 Other example: 
  
 ```C
 #include <linux/init.h>
 #include <linux/module.h>
 #include <linux/moduleparam.h>
 #include <linux.sched.h>
 #include <linux/sched/signal.h>
  
 MODULE_LICENSE("GPL");
 
 static unsigned int PID = 1;
 module_param(PID, uint, 0400);
  
 void print_task(struct task_struct* task)
 {
      printk("process: %s, paret process: %s\n", task->comm, task->parent->com); 
 }
  
 static int init_find_task(void)
 {
     strcut task_struc* task = NULL;
     
     for_each_process(task) {
         if (task->pid == (pid_t)PID) {
             print_task(task); 
         }
     }
 }
  
 static void exit_find_task(void)
 {
     printk("GOOD BYE: find_task!!\n"); 
 }
  
 module_init(init_find_task);
 module_exit(exit_find_task);
 ```
 A parameter PID for the module is defined, the module looks for the process with that PID, and prints its information: name, and parent name. 
  
Every process has an VAS (virtual address space). This VAS, can be read in `/proc/<pid>/maps`, this will retrieve the address space. 
 
 In the kernel, the VAS or process memory map, can be found int the `struct mm_struct` which container th elist of proces VMAs (virtual memory addresses), page tables, etc...
  
  All information related to the process address space is included in an object called the memory descriptor of type `mm_struct`, accessible via `current->mm`

 ```C
 struct mm_struct {
     /* Pointer to the head of the list of memory region objects */
     struct vm_area_struct* mmap;
     
     /* Pointer to the root of the red-back tree of memory region objects*/
     struct rb_root mm_rb;
  
     /* Pointer to the last referenced memory region object*/  
     struct vm_area_strcut* mmap_cache;
    
     ...
  };
 ```
  
  Linux implements a memory region by meanos of an objecto fo type `vm_area_struct`
  
  ```C
  struct vm_area_struct {
      struct mm_struct* vm_mm;  // pointer to the memory descriptor that owns the region
      unsigned long vm_start;   // First linear address inside the region
      unsigned long vm_end;     // First linear address after the region
  }
  ```
  
  
Each memory region descriptor identifies a linear addess intterval; vm_end-vm_start indicates the lenght of the memory region. 
  
All the regions owned by a process are linked in a simple list.
  
Regions appear in the list in ascending order by memory addresses.
  
  
 Example for retrieving a process memory map:
 
  ```C
 #include <linux/init.h>
 #include <linux/module.h>
 #include <linux/moduleparam.h>
 #include <linux/list.h>
 #include <linux/mm.h>
 #include <linux/mm_types.h>
 #include <linux/proc_fs.h>
 #include <linux/version.h>
 #include <linux.sched.h>
 #include <linux/sched/signal.h>
  
 static unsigned int PID = 1;
 module_param(PID, uint, 0400);
  
 struct dentry* file_entr(struct file* pfile)
 {
 #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,19,0)
    return pfile->f_path.dentry;
 #else
    return pfile->f_dentry;
  
 }

 void print_vmarea_node(struct vm_area_struct* vmnode)
 {
      printk("0x%lx - 0x%lx\t", vmnode->vm_start, vmnode->vm_end);
      if (vmnode->vm_flags & VM_READ)
           printk(KERN_CONT"r");
      else
           printk(KERN_CONT"-");
      
      if (vmnode->vm_flags & VM_WRITE)
           printk(KERN_CONT"w");
      else 
           printk(KERN_CONT"-");
  
      if (vmnode->vm_flags & VM_SHARED)
           printk(KERN_CONT"s");
      else 
           printk(KERN_CONT"p");
      print_vm_file(vmnode);
 }
 
static void print_vm_list(struct vm_area_struct*  vmlist) 
{
    struct vm_area_struct* vmnode = vmlist; 
    while (vmnode != NULL)
    {
         print_vmarea_ndoe(vmnode);
         vmnode = vmnode->vm_next;
    }
}  
 
void print_mm_struct(struct mm_struct* mm)
{
     printk("code : [0x%lx, 0x%lx]\n", mm->start_code, mm->end_code);
     printk("data : [0x%lx, 0x%lx]\n", mm->start_data, mm->end_data);
     printk("heap : [0x%lx, 0x%lx]\n", mm->start_brk, mm->brk);
     printk("stack: [0x%lx\n"], mm->start_stack);
     print_vm_list(mm->mmap);
}
  
static int init_find_task(void)
{
     struct task_struct* task = NULL;
  
     for_each_process(task) {
          if (task->pid == (pid_t)PID) {
              print_mm_struct(task->mm);
          }
     }
  
     return 0;
}
  
static void exit_find_task(void)
{
    print("good bye: find_task!\n");
}
  ``` 
  
### Kernel Threads
  
A kernel Thread is a Linux Task running only in kernel mode. It is not created by running fork() or clone() stste call. Kernel Threads helps the kernel to perform operation in the background. Both kernel threads and user-threads are represented by the same struct `task-struct`. The main difference is that thre is no address space in the kernel thread, so the `mm` variable is set to NULL.
  
To use kernel threads use the API at <linux/kthread.h> 
  
  ```C
  struct task_struct* kthread_create(int (*threadfn)(void* data), void* data, const char name[], ...)
  ```
  parameters:
  - threadfn: the function which thread should run
  - data: arguments for thread function
  - name: printf style format for the name of kernel thrad. 
  - return value: pointer to struct task_struct
  
  Note that the `kthread_create()` only creates the thread but doesn't run the thread, for that it is needd to call `wake_up_process()` with the return value of the `kthread_create()` as argument. 
  
  There is also function that creats the kernel thread an runs it callin `wake_up_process()`:
  
  ```C
  struct task_struct* kthread_run(int (*threadfn)(void* data), void* data, const char name[], ...)
  ```
  
  To stop a kthread: 
  
  ```C
  int kthread_stop(strcut task_struct* k);
  ```
  
  Note: if the kthread is not stopd in the `module_exit`, and `Oops` will be addressed.
  
  `kthread_stop()` is a blocking call, it waits until the function executed by the thread exits. `kthread_stop()` flag stes a variabl ein the task_struct variable which the function running in while(1) shoud check in each of tis loops. 
  
  ```C
  int threadfunc(void* data)
  {
      while(!kthread_should_stop()
      {
           // do work here
      }
      return 0;
  }
  ```
  
  If `ktrhead_stop()`is call and, the kthread had already finished (because the underliying function is not a loop, and may already finished), there will be an `Oops` message. Remember that after an Oops is got, the kernel is considered to be tainted. 
 
  In the case in a module, we dont call `kthread_stop()` at the exit function, and the kthread is still running, then a `Oops` will also happen.
  
  In a module, in case it is needed in which processosr the code is running, use the function `smp_processor_id()`
  
  
  
 #### kthread module examples:
  
 ```C
 #include <linux/init.h>
 #include <linux/module.h>
 #include <linux/kdev_t>
 #include <linux/fs.h>
 #include <linux/cdev.h>
 #include <linux/device.h>
 #include <linux/slab.h>      // kmalloc()
 #include <linux/uaccess.h>   // copy_to/from_user()
 #include <linux/kthread.h>   // kernel threads
 #include <linux.sched.h>     // task_struct
 #include <linux/delay.h>
  
  MODULE_LICENSE("GPL");
  
  static struct task_struct* my_thread;
  
  int thread_function(void* pv)
  {
      int i = 0;
      while(!kthread_should_stop()) 
      {
          printk(KERN_INFO "In thread Funciton %d\n", i++);
          msleep(1000);
      }
      return 0;
  }
    
  static int __int my_driver_init(void)
  {
      my_thread = kthread_create(thread_function, NULL, "myThread");
      if (my_thread) {
          wake_up_process(my_thread);
          return 0;
      } else {
          printk(KERN_ERR "Cannot create kthread\n");
          return -1;
      }
  }
  
  void __exit my_driver_exit(void)
  {
      kthread_stop(my_thread);
      printk(KERN_INFO "Device Driver Removed!\n");
  }
  
  module_init(my_driver_init);
  module_exit(my_driver_exit);
  ``` 
  
 ```C
  MODULE_LICENSE("GPL");
  static int print_running_thread(void* data)
  {
      while(!kthread_should_stop()) {
          struct task_struct* task_list;
          for_each_process(task_list) {
              if (task_list->state == TASK_RUNNING)
                 PR_INFO("Process: %s\tPID:[%d]\State:%s\n", 
                          task_list->comm,  // this is the name of the task
                          task_list->pid,
                          get_task_state(task_list->state));
          }
          msleep(500);
      }
  }
  
  static int test_task_init(void)
  {
      pr_info("%s: In init\n", __func__);
      print_thread = kthread_run(print_running_thread, NULL, "print_running_cpu");
      return 0;
  }
 ...
 ```
 
Example of 2 kthreads running in parallel: 
  
```C
#include <linux/delay.h>  // usleep_range()
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
  
static struct task_struct *kthread1, *kthread2;
  
static int work_func1(void* data)
{
   int i = 0;
   while (!kthread_should_stop()) {
      pr_info("1 %d\n", i);
      usleep_range(1000000, 1000001);
      i++;
      if (i == 10) { i = 0; }
   }
   return 0;
}

static int work_func2(void* data)
{
    int i = 0;
    while (!kthread_should_stop()) {
       pr_info("2 %d\n", i);
       usleep_range(1000000, 1000001);
       i++;
       if (i == 10) { i = 0; }
     }
    return 0;
}

static int myinit(void)
{
    kthread1 = kthread_create(work_func1, NULL, "mykthread1");
    kthread2 = kthread_create(work_func2, NULL, "mykthread2");
    wake_up_process(kthread1);
    wake_up_process(kthread2);
    return 0;
}
  
static void myexit(void)
{
     kthread_stop(kthread1);
     kthread_stop(kthread2);
}
```

```C
#include <linux/delay.h>  // usleep_range()
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
  
static styruct task_struct* my_task = NULL;
  
static int my_kthread(void* data) {
   char* string = (char*)data;
   
   pr_info("my kthread data: %s\n", str);
   pr_info("my kthread smp_processor_id: %d\n", smp_processor_id());
   while (!kthread_should_stop()) {
      msleep(5000);
      pr_info("my kthread running in processor: %d\n", smp_processor_id()); 
   }
}
  
  
static int __init my_init(void)
{
   pr_info("Init\n");
   pr_info("smp_processor_id: %d\n", smp_processor_id());
  
   my_task = kthread_run(my_kthread, "hello! my kthread", "mykthread-%s", "test");
  
   pr_info("Init finished\n");
   return 0;
}
  
static void __exit my_exit(void)
{
   pr_info("Exit\n");
   pr_info("smp_processor_id: %d\n", smp_porcessor_id());
  
   if (my_task) {
       pr_info("stop_kthread\n");
       kthread_stop(my_task);
   }
  
   pr_info("Exit finsihed\n");
}
```
  
### Modules for several linux kernels
  
In different linux kernel version, there are functions that change its signaruture, that is to say functions that change its argumets, for example `access_ok`: 
  
Before 5.0 linux kernel version: 
 
  ```C
  int access_ok(int type, void* addr, unsigned long size);
  ```
  
After 5.0 linux kernel version:
  
  ```C
  int access_ok(void* addr, unsigned long size);
  ```
  
To support multiple kernel versions, that would mean having code conditional compilation directives: 
- LINUX_VERSION_CODE
- KERNEL_VERSION
- UTS_RELEASE  
  
To do this, compare the macro `LINUX_VERSION_CODE` TO THE MACRO `KERNEL_VERSION`
  
- LINUX_VERSION_CODE: this macro expands to the binary representation of the kernel version. One byte for each part of the verson release number. E.g.: 0.0.0 = 0x050000 = 327680. 
  
  This macro `LINUX_VERSION_CODE`uis defined in the header file `<linux/version.h>`
  
  ```
  LINUX_VERSION_CODE = $(VERSION) * 65536 + $(PATCHLEVERL) * 256 + $(SUBLEVEL)
  E.g: 5.0.0 = 5*65536 + 0*256 + 0 = 327680 
  ```

- KERNEL_VERSION: this macro is used to bild an integer code form the indiviudal nubmers that build up a version number. It is defined in the file: `<linux/version.h>`
  
  ```C
  #define LINUX_VERSION_CODE 327698 
  #define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c)) 
  ```
  
- UTS_RELEASE: this macro expands to a string describing the version of the kernel. It is included in the file: `<generated/utsrelease.h>`


### Modules macros: __init __exit, __initdata and __exitdata
 
 #### __init
  
 `__init` is a macro defined at `<linux/init.h>`.
  
 ```C
  #define __init __section(.init.text)
  #define __section(S)   __attribute__((__section__(#S)))
  #define __init __attribute__ ((__sectin__ (".init.text")))
 ```
The `__init` macro informs the compiler to place this functino in a specila section(.init.text) and this memory is discarted after the function call. 
 
The functions specified usgin module_init are initialization functions, that run only once. So th ekernel can free RAM by removing memory used by this particular function. So functions marked using `__init` are discarded after the function call.
  
  #### __exit
  
  The `__exit` macro is defined in `<linux/init.h>`
  
  ```
  #define __exit __section(.exit.text)
  ```
  
  When the kernel module is configured as a builtin mdouel instead of a loadable module, thrre is no need for the exit function.
  
  Adding the `__exit` macro causes the compiler to discardd this function when the module is configured as builtin. This saves on code space as the exit functions won't be called. 
  
  For loadable modules, this macro doesn't have any effect. 
  
#### __initdata and __exit data

  `__initdata` should only be used in the module_init() code. 
  
```
#define __initdata __attribute__ ((__section__ (".init.data")))
#define __exitdata __attribute__ ((__section__ (".exit.data")))
```
  
`__init`/`__exit` is for functions and `__initdata`/`__exitdata` is for variables.
  

### How to list the build-in kernel modules?
  
Kernel modules are code that can be loaded and unloaded into the kernel on demmand.
It can be configured in two ways:
   - build-in (part of the kernel) : it is always present
   - loadable: can be loaded/unloaded as needed.
  
- `lsmod` command list all the kernel code configued as LKM
- `modules.builtin` file list all moudles that are build into the kernel

Use:  `$grep module_name /lib/modules/$(uname -r)/modules.builtin`
  
  
### How to load a module automatically during boot
  
help `man 5 modules`
  
  In the system there is a file `etc/modules-load.d` which contains the names of the kernel modules that are to be loaded at boot time, one per line. Arguments can be given in the same line as the module name. Lines beginning with a '#' are ignored. You have to create a `.conf` file. 

 So create a symbolic link: 
  
```bash
sudo ln -s /<path_to_module>/<custom_module>.ko /lib/modules/`uname -r`/kernel/drivers/misc 
```
 - reference: https://manpages.ubuntu.com/manpages/focal/en/man8/systemd-modules-load.service.8.html

This part doesn't tell the system to add options to the module(s). and is actually rarely needed. To define custom module options, there is `/etc/modprobe.d/` (and other system-reserved places).
  
### Blacklisting kernel modules
  
Blacklisting modules, will prevent the kernel module to be loaded. 
 
This may be necessary because: 
   - associated ahrdware in not needed
   - loading a given module may cause problems. Lie two modules tring to handle the same hardware.
  
To blacklist a module, create a `.conf` file (any name with .conf will do) inside /etc/modprove.d/ and append a line for each module to be blacklisted, using the `blacklist` keyword.
  
Then run the following command to rebuild initramfs `sudo update-initramfs -u`. In the next reboot, the module will be blacklilsted.
  
 It is also possible to blacklist a module from the bootloader. Simply add `module_blacklist=module1,module2,module3` to ther bootloader kernel lline. This can be really useful, in case a broken module prevents the system to boot. 
  
  For example with Grub, edit the file `/etc/default/grup` and at the option: `GRUP_CMDLINE_LINUX` append: `module_blaclist=<module_name>`. Then update the grub configuration file with : `sudo update-grub`, and reboot the system. 
  
### passsing parameters to modprobe. 
  
 The command `modprobe` is used to load modules during boot, to load parameters in case are needed, then create a file `/etc/modprove.d/` with a `.conf` extension (any name will do). And then use the `module_name` and `parameter_name=<value>`. 
  
### systool
  
  `systool` can be used to print the values of files present in the module's /sys/ directory. 
  
  ```
  systool -vm <module_name>
  ```
  
### Printk
 
`printf()` is a function from the standard C library. `printk()` is a kernel level function.
  
`printk' function is called with one argumet:
  
 ```
 printk(KERN_log_prority "hello world!");
 ```
 The log_priority is one of eight values, predefined in linx/kernel.h,
  
 - EMERG, ALERT, CRIT, ERR, WARNING, NOTICE, INFO, DEBUG, DEFAULT
  
 `printk()`writes in the kernel buffer.
  
 #### printk ring buffer
 `printk` is implemented using a ring buffer in the kernel wit a size of __LOG_BUG_LEN bytes, where that value equlas (1 << CONFIG_LOG_BUF_SHIFT). 
 
 If `printk`is continually used, the ring-buffer will be overflowed. 
  
 ```
  cat /boot/config-`uname -r` | grepo CONFIG_LOG_BUF_SHIFT
 ```
  
 `CONFIG_LOG_BUF_SHIFT` can be configured from menuconfig, or the KCONFIG file.
  
  ```
  make menuconfig -> General Setup -> Kernel log buffer size
  ```

#### log levels
  
The log levels hare defined at `kernel.h`. 
  
  
#### default log level
  
 If not sepecified the log level, the default log level will be used. The default log level 
can be checked at `/proc/sys/kernel/printk` 
  
 The default level is associatex with:
   - console_loglevel: level under which the messages are logged on the console device 
   - default_message_loglevel: priority level that is associated by default with messages for which no priority value is specified
   - minimum_console_loglevel: minimum level to allow a message to be logged on the console device
   - maximum_console_loglevel: maximum level
  
  ```
  echo 8 > /porc/sys/kernel/printk # will change the console_loglevel
  ```
  
 #### what is a console?
  
  In linux, a console is a device to which text is written to and text is readed from. 
  
  By default, the console is the (text-mode) screen and keyboard. One can switch to that console by pressing Ctrl+Alt+Fn, where n is 1 to 6. 
  
  When the system is booted, the kernel prints a lot of messages, like "initializing this... ", "initializing that..." . These all get printed via printk that sends the message to the console driver. 
 
  ####  So why don't the kernel messages appear when in graphics mode?
  
  In Linux, graphics mode is implemented not inside the kernel (and thus in cannont print messages in graphics mode), but as a usermode process called X, or X server.
  
  Every program that wants to display a window, sends a message via PIC (Programmable Interrupt Controller) to the X server and says how it (the X server) should draw the window.
  
   Tis message passing is implemented in a shared library, son from the application writer point of view, it is just a call to a function that displays the window.
  
   Xterm is one of the many graphical applications (Konsole and gnome-terminal are the other well-known programs that emulates a terminal.
  
  
  
  
  
  
  
  
  
  

 
