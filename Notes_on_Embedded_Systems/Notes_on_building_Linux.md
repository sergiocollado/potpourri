

There are four main players for building a custom linux system.
- Toolchain
- Bootloader
- Kernel 
- RootFileSystem

The standard GNU toolchain consist on:
- Binutils: assembler, linker, ...
- GCC (GNU Compiler Collection)
- C library


<!--
for custom real-time oriented systems, you will have to cosider the following
Embedded and Real-Time Systems Requierments
Cross-Development Environments: Goals and Needs 
Cross-Development Toolchain
Setting Up a Target Development Board
KBuild System
Boot loaders 
Kernel Configuration, Compilation, Booting
Device Drivers - Device Trees
Target Filesystem Packaging
Build Target Root Filesystem
Root Filesystem Choices
Need for special libraries, as could be uClibc
Network stacks
Build BusyBox 
Kernel Monitoring and Debugging
Right-Sizing
Memory Technology Devices
Compressed Filesystems
System Upgrades
Real-Time Extensions
-->

Check you have the building tools: 

it is recomended update all:

```bash
apt-get update && apt-get upgrade
```

to re-index, use:

```bash
>sudo updatedb
```


```bash
sudo apt-get install build-essential
```

for make:

```bash
sudo apt-get install build-essential
```
for gcc:

```bash
sudo apt-get install gcc
```

and the kernel sources:

```bash
# apt-get install linux-headers-$(uname -r)
```


You will need the following components:

```bash
>root@user:/home/usr# sudo apt-get install mlocate 
```











REFERENCES AND USEFUL LINKS.

GNU ARM embedded toolchain:  https://launchpad.net/gcc-arm-embedded

C library for embedded systems:  https://sourceware.org/newlib/

binutils:  http://www.gnu.org/software/binutils/

GNU ARM TOOLCHAIN: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm

developers: https://launchpad.net/~gcc-arm-embedded-developers

gcc: http://gcc.gnu.org/

https://launchpadlibrarian.net/287100910/How-to-build-toolchain.pdf

kERNEL:  https://www.kernel.org/

