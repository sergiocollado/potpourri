# NOTES ON LINUX DEVICE DRIVERS

## What is a device driver.

A device driver is a code, that contrals a given tye of device in the compuer.

A device driver has three sides
- one side talks to the kernen
- one side talks to the hardware
- one side talks to the user. 

## What is a kernel module?

Tradicinaly the way to add code to the kernel was to recompile the kernel and reboot the system.

Kernel modules, are a piece of ccode that can be load/inserted  and unloaded/removed form the kernel whenever needed.

It can be refered by other names:

- Loadable kernel modules (LKM)
- modules

Its extension is .ko (Kernel Object)

## Standard location for kernel modules

Moudeles are located in the /lib/modules/<kernel version> direcory of the rootfs by default

to check them: 

```
cd /lib/modules/`uname -r`/
finx . -name '*.ko' | wc -l # to count the number of kernel modules
```

## Device drivers vs kernel modules

A kernel module doesn't have to be a device driver. 

A driver is liek a sub-class of module

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

1. Size: Moudle management consumes unpeable kernel memory. A basic kernel with a number of modules loaded will 
consume more memory than an equivalen kernel with the dirvers compiled into th ekernel image itself. This can be
an issue on machines with limited physical memory

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

- In-source tree: mdoules presen tin the linux kernel source code
- Out-of-tree: modules not present in lthe linux kernel s

All modules start out as "out-of-tree" developments, that can be compiled using the 
condtex of a source-tree. 

Once a module gets accepted to be included, it becomes an in-tree module.

## Basic commands

- List modules: (lsmod) lsmod ges its information by reading the file /proc/module (previously) or /sys/module
- module information: (modinfo) : prints the information of the module










