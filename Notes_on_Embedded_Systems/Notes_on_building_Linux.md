

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

```bash
sudo apt-get install build-essential
```

As well, you'll need a copy of the linux kernel headers:

You will need the following components:

```bash
>root@user:/home/usr# sudo apt-get install mlocate 
```

to re-index inmediatetly use:

```bash
>sudo updatedb
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

