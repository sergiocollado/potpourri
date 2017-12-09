

There are four main players in this game:
- Toolchain
- Bootloader
- Kernel 
- RootFileSystem

The standard GNU toolchain consist on:
- Binutils: assembler, linker, ...
- GCC (GNU Compiler Collection)
- C library

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

