
# key caracteristics and propierties for embedded systems:

  - Dedicated functionality
  - Limited resources
  - performance and eficiency
  - Real time constrains
  - Interaction with the enviroment.
  - Dependavilitie
      - Availability.
      - Reliability.
      - Safety.
      - Security.
      - Integrity (¿?)
      - Mantanability (?¿)

 When testing this system, the following aspects must be considered:
 
 - Code coverage.
 - Decidison coverage.
 - Complejidad ciclomaática.


There are four main elements, needed for building a custom linux system.

- Toolchain
- Bootloader
- Kernel 
- RootFileSystem

| Element | Description of the element |
| --- | --- |
| toolchain | Collection of tools for builiding the system, copiler, libaries, assemblers, linkers... |
| bootloader | Routine for start/reset  the microprocesor, that will launch the system configuration process |
| kernel | heart of the operating system |
| Rootfilesysten | the file system for our desinged system. |


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

maybe remove the stuff you don't need:

```bash
sudo apt autoremove
```

and the kernel sources:

```bash
# apt-get install linux-headers-$(uname -r)
```

If you are going to build a system, for another device diferent that the one you are using, I mean another architecture, you will
need the linux sources that fit that architecture. When you build a system for another architecure, that is different that the one
you are using, is call 'Crosscompiling'.

You will need the following components:

```bash
>root@user:/home/usr# sudo apt-get install mlocate 
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



# Check list for robustness systems:

 - Inexperienced & foul user.
 - the message protocol used, is acknoledged?
 - there is any kind of protection against message interrumption?
 - there is any kind of protecion against lost messages?
 - the max lenght of any message has been properly defined?
 - there is any kinde of defense agains file corruption? as  md5, or checksums?
 - there are any kind of keep alive messages, heatbeat, watchdogs?
 - there are any ICT (In circuit test) or BIST (Build In Circuit Test)?
 - there is any implementation of FCE (Fordward Correction Errors), or ECC (Error Correction Codes)?
 - Whats the hammingdistance for messages mcomunications.
 - The z-impedance has been defined in comunication lines?
 - Max transmission/reception performace, and average transmission/reception performace, has ben defined, deteermined and tested.
 - Are we keeping track of the REC (Recedived Error Count) or of the TEC (Transmition Error Code).
 - Memory has any kind of ckeching scheduled in it's util live?
 - Memory or the file system, have integrated any kind of ECC (Error Correction Codes)?

 







REFERENCES AND USEFUL LINKS.

GNU ARM embedded toolchain:  https://launchpad.net/gcc-arm-embedded

C library for embedded systems:  https://sourceware.org/newlib/

binutils:  http://www.gnu.org/software/binutils/

GNU ARM TOOLCHAIN: https://developer.arm.com/open-source/gnu-toolchain/gnu-rm

developers: https://launchpad.net/~gcc-arm-embedded-developers

gcc: http://gcc.gnu.org/

https://launchpadlibrarian.net/287100910/How-to-build-toolchain.pdf

kERNEL:  https://www.kernel.org/

