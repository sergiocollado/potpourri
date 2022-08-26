# NOTES ON LINUX DEVICE DRIVERS

## What is a device driver.

A device driver is a code, that contrals a given tye of device in the compuer.

A device driver has three sides
- one side talks to the kernen
- one side talks to the hardware
- one side talks to the user. 

## What is a kernel module?

Tradicionaly the way to add code to the kernel was to recompile the kernel and reboot the system.

Kernel modules, are a piece of ccode that can be load/inserted  and unloaded/removed form the kernel whenever needed.

It can be refered by other names:

- Loadable kernel modules (LKM)
- Modules

Its extension is .ko (Kernel Object)

## Standard location for kernel modules

Modules are located in the /lib/modules/<kernel version> direcory of the rootfs by default

to check them: 

```
cd /lib/modules/`uname -r`/
finx . -name '*.ko' | wc -l # to count the number of kernel modules
```

## Device drivers vs kernel modules

A kernel module doesn't have to be a device driver. 

A driver is like a sub-class of module

modules are used for:
- device dirvers
- file system
- system calls
- network drivers: dirvers implementing a network protocol
- tty line disciplines: for terminal devices

## Advantages of kernel modules

1. All parts of the base kernel stay loaded all the time. Modules can save you memory, becasue they are loaded only
when they are requested to be loaded.

2. User would need to rebuild and reboot the kernel every time they would requier a new funcionality

3. A bug in driver which is compiled as a part of kernel will sotp system from loading, whereas module allows systems to load. 

4. faster to mantain and debug

5. Makes it easier to manatain multiple machines on a single kernel base

## Disadvanteges of kernel modules

1. Size: Moudle management consumes unpeable kernel memory. A basic kernel with a number of modules loaded will consume more memory than an equivalen kernel with the dirvers compiled into th ekernel image itself. This can be an issue on machines with limited physical memory

2. As the kernel modules are loaded very late in the boot process, hence core funcionality has to go 
in the vase kernel (e.g. memory management)

3. Security. if you build your kernel statically and disalbe linux's dynamic module loading feature, youprevent runn-time 
modification of the kernel code.

## Configuration

In orden to suppor module, the kernel must have been build, with the following option enabled:

CONFIG_MODULES=y

```
cd /boot
cat config-`uname -r` | grep CONFIG_MODULES
```

## Types of modules

- In-source tree: modules present in the linux kernel source code
- Out-of-tree: modules not present in the linux kernel 

All modules start out as "out-of-tree" developments, that can be compiled using the 
condtex of a source-tree. 

Once a module gets accepted to be included, it becomes an in-tree module.

## Basic commands

- lsmod: List modules, lsmod ges its information by reading the file /proc/module (previously) or /sys/module
- modinfo: module information, prints the information of the module
- insmod: 
  

## Hello World kernel module
  
  In C/C++ programming the main() function is the entry point and exit point
  
  Kernel modules must have al least two funcions:
  - a start (initialization function): which is called when the module is loaded into the kernel
  - an end funcion (cleanup), which is called just befor it si removed
  
  This is done with the module_init() and module_exit() macros
  
 ### Licensing
  
  Module should specify which license you are using MODULE_LICENSE() macro
  
  - "GPL" GNU plublic lincese v2 or later
  - GPL v2
  - GPL and addictional rights
  - Dual BSD/GPL
  - Dual MIT/GPL
  - Dual MPL/GPL
  - Propietary (non-free-modules)
  
### Header files
  
  All kernel modules needs to include "linux/module.h" for macro expansion of module_init and module_exit.
  
  "linux/kernel.h" only for the macro expansion for the printk() log level.
  
### HelloWorldModule.c
  
```
  #include <linux/kernel>
  #include <linux/module>
  
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
  
### Compiling it
  
To compiile the module, the kermel make file is needed
  
```
ls /lib/modules/'uname -r'/bulid/Makefile
```
  
use the make, with the -C option, that indicates to use the makefile indicated in the folder by -C
  
``` 
make -C /lib/modules/`uname -r/build/
``` 
just this, will not be enought. this makefile uses a makefile, so a small makefile needs to be added
  
 
```
cat Makefile
obj-m := hello.o
```
 
obj-m : stands for module. 
  
```
make -C /lib/modules/'uname -r'/build/ M={PWD} modules
```
 
The file .ko, should be generated 
 
At to this point, this is an out-of-tree module. To load it to the kernel, the 'insmod' command is used.
  
```
sudo insmod ./helloWorld.ko
lsmod # to check if the module indeed has been loaded
sudo rmmod helloWorld # to remove the module
```
  
In the code there is a 'printk', this is not printed in the console, for that the command 'dmesg' is needed.
  

### Compile and clean module commands

 To build a module, use:
 ```
  make -C /lib/modules/`uname -r`/build M=${PWD} modules
 ```
  
 T clean the module: 
 ```
  make -C /lib/modules/`uname -r`/build M=${PWD} clean
 ```
  
The `-C` option state to to change the directory provided, instead of using the current directory use the one provided by the -C option.
  
The `M=` argument causes the Makefile tomove back into your module source directory before trying to build modules. 
  
The kernel Makefile will read the local makefile to findout what to build, this is indicated by writing: obj-m +=HelloWorldModule.o

### Cross compiling kernel modules
  
There are two variables that the kernel uses to select the target architecture: 
  - ARCH
  - CROSS_COMPILE
  
The default vaues for both are found in the top-level Makefile and the values of both may be overridden on the command line.
  
ARCH: architecture targetes as the kernel knows it.
  
CROSS_COMPILE: set this to the prefix of your toolchain (including the trailing dash "-")
So if the toolchain is invoked as say x86_64-pc-linux-gnu-gcc, just remove the trailing gcc and that is what should be used: x86_64-pc-linux-gnu-.
  
```
$ make ARCH=arm CROSS_COMPILE=arm-buildroot-linux-uclibgnueabi- -C /home/..../..../output/build/linux-X.Y:Z m=${PWD} modules  
```

 ### Printk
  
 `Printf()` is a function from the standard C library. `printk()` is a kernel level function.
  
`printk' function is called with one argumet:
  
 ```
 printk(KERN_log_prority "hello world!");
 ```
 The log_priority is one of eight values, predefined in linx/kernel.h,
  
 - EMERG, ALERT, CRIT, ERR, WARNING, NOTICE, INFO, DEBUG
  
 `printk()`writes in the kernel buffer.
  
### Simplified makefile
  
So to build a module, the command is use:
  
```
make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
```
  
and to clean the module, the command:
  
```
make -C /lib/modules/ùname -r/build M=${PWD} clean
```

This is a bit bothersome, so a new makefile can be used:
  
```
obj-m := hello.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/ùname -r/build M=${PWD} clean
```

### What happens we do insmod in a module
  
  The kernel module is a piece of kernel code (.ko in elf format) which can be added to the running kernel, and when loaded can be removed from the kernel.
  
1- It calls init_Module() to inform the querken that a module is attemp to be loaded an transfers the control to the kernel 
  
2- In the kernel, `sys_init_module()`is run. It does the following operations
  - Verify that the user has the permissions to load the moduel
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
  
```
obj-m := linux.o
linux-objs := hello.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/ùname -r/build M=${PWD} clean  
```
  
if we check the name of the modules, with lsmode, we would find the linux module
  
### Module composed of several files
 
We can have a module in several files. For example:
  
HelloWorldModule.c
  
```
  #include <linux/kernel>
  #include <linux/module>
  
  MODULE_LICENSE("GPL")
  
  static int __init test_hello_init(void)
  {
      printk(KERN_INFO "%s: In init\n", __func__);
      furnc();
      return 0;
  }
  
  static void __exit test_hello_exit(void)
  {
       printk(KERN_INFO "%s: In exit\n", __func__);
  }
  
  module_init(test_hello_init);
  module_exit(test_hello_exit);
```
  
  
  
  
  Reference: https://lwn.net/Kernel/LDD3/
 
