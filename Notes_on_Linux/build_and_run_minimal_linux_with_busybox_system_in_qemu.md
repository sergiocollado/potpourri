reference:
 - https://blog.vmsplice.net/2011/02/near-instant-kernel-development-cycle.html
 - https://dev.to/alexeyden/quick-qemu-setup-for-linux-kernel-module-debugging-2nde
 - https://gist.github.com/chrisdone/02e165a0004be33734ac2334f215380e 
 - https://gist.github.com/ncmiller/d61348b27cb17debd2a6c20966409e86  
 - https://mudongliang.github.io/2017/09/12/how-to-build-a-custom-linux-kernel-for-qemu.html 
 - http://blog.vmsplice.net/2011/02/near-instant-kernel-development-cycle.html 
 - https://mgalgs.io/2015/05/16/how-to-build-a-custom-linux-kernel-for-qemu-2015-edition.html 
 - https://youtu.be/LyWlpuntdU4
 - https://youtu.be/asnXWOUKhTA 
 - https://youtu.be/c4j6z2huJxs 
 - Build a embedded linux using buildroot: https://youtu.be/ysoi0bn66oM
 - https://vccolombo.github.io/cybersecurity/linux-kernel-qemu-setup/
 - https://blog.k3170makan.com/2020/11/linux-kernel-exploitation-0x0-debugging.html
 - How To Build QEMU Images With Buildroot - Hardware Hacking Tutorial : https://youtu.be/O9RHMKJqVTg
 - x86-64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_ubuntu-host_qemu-vm_x86-64-kernel.md
 - arm64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_linux-host_qemu-vm_arm64-kernel.md
 - riscv64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_linux-host_qemu-vm_riscv64-kernel.md
 - https://ibug.io/blog/2019/04/os-lab-1/
 - a simple workflow to debug the linux kernel: https://marliere.net/posts/1/

### Instruction to install qemu different architectures

 - x86_64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_ubuntu-host_qemu-vm_x86-64-kernel.md
 - arm64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_linux-host_qemu-vm_arm64-kernel.md
 - risc64v: https://github.com/google/syzkaller/blob/master/docs/linux/setup_linux-host_qemu-vm_riscv64-kernel.md


# Building a minimal linux system with busybox

 - reference: https://youtu.be/asnXWOUKhTA?list=PLw27zZE-QQB9z59AI0EnAE998NSSJ4k9p
 - reference: what is busybox? https://linuxhandbook.com/what-is-busybox/

> BusyBox is an open source project that provides a stripped down implementation of around 400 common UNIX/Linux commands. Stripped down? Yes. BusyBox implementation removes the uncommon, rarely used command options. Everything fits under 1 MB and this minimal image is the reason why it has gained popularity among embedded system and IoT domain as well as in the cloud computing world.
> BusyBox is superb alternative to GNU Coreutils specially in cases where the small size of the operating system matters big.

 - reference: https://busybox.net/about.html

```bash
#!/bin/bash

set -xe

# reference: https://youtu.be/asnXWOUKhTA?list=PLw27zZE-QQB9z59AI0EnAE998NSSJ4k9p
# we will need a kernel and a root partition, and in that root partition we will install busybox

KERNEL_VERSION=5.15.6
BUSYBOX_VERSION=1.34.1

mkdir -p src
cd src

	# Kernel: donwload, unpack, default configuration and compile
	
        KERNEL_MAJOR=$(echo $KERNEL_VERSION | sed 's/\([0-9]*\)[^0-9].*/\1/')

        # 1- to download the code
        #wget https://mirrors.edge.kernel.org/pub/linux/kernel/v$KERNEL_MAJOR.x/linux-$KERNEL_VERSION.tar.gz
	#tar -xf linux-$KERNEL_VERSION.tar.gz
        #cd linux-$KERNEL_VERSION
        # 2- to download the repo in that tag
        git clone --branch v$KERNEL_VERSION git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git # consider if use --depth 1
	cd linux-stable
	
		make defconfig
		time make -j$(nproc) || exit
                # maybe we should test: make defconfig & make kvm_guest.config - Enable Kconfig items for running this kernel as a KVM guest
	cd ..
	
	# Busybox: download, unpack
	wget https://busybox.net/downloads/busybox-$BUSYBOX_VERSION.tar.bz2
	tar -xf busybox-$BUSYBOX_VERSION.tar.bz2
	cd busybox-$BUSYBOX_VERSION
		
		make defconfig
		# we need a static build of busybox. So the libraries are build into the executable binary
		sed 's/^.*CONFIG_STATIC[^_].*$/CONFIG_STATIC=y/g' -i .config	
		time make -j$(nproc)|| exit
	
		# you need to install musl at least in manjaro based systems
		# sudo packman -s musl kernel-headers-musl
		# make CC=musl-gcc -j$(nproc) busybox || exit
	
	cd ..
	
cd ..

# now pull the compiled kernel from the source directory 
# 1
#cp src/linux-$KERNEL_VERSION/arch/x86_64/boot/bzImage ./
#2
cp src/linux-stable/arch/x86_64/boot/bzImage ./

# we need a root drive: initrd
mkdir initrd
cd initrd 

	# create standard directories
	mkdir -p bin dev proc sys
	cd bin
	
		cp ../../src/busybox-$BUSYBOX_VERSION/busybox ./
		
		for prog in $(./busybox --list); do
		# iterate through all the programs and create sym links
			ln -s /bin/busybox ./$prog
		done

	cd ..
	
	# tell the kernel what to do at start up, for that we create a init script
	echo '#!/bin/sh' > init
	echo 'mount -t sysfs sysfs /sys' >> init
	echo 'mount -t proc proc /proc' >> init
	echo 'mount -t devtmpfs udev /dev' >> init
	echo 'sysctl -w kernel.printk="2 4 1 7"' >> init
	echo 'clear' >> init
        echo 'echo -e "\nBoot took $(cut -d' ' -f1 /proc/uptime) seconds\n"' >> init
	echo '/bin/sh' >> init
	echo 'poweroff -f' >> init # turn the hw off when the terminal is exited.        
	#echo 'echo -e "\nBoot took $(cut -d' ' -f1 /proc/uptime) seconds\n"' >> init # -- not sure this line is working
        # ... check below for other interesting 'init' file.

	chmod -R 777 . # maybe we are overdoing here
	
	find . | cpio -o -H newc > ../initrd.img
		
cd ..

# launch the system
#qemu-system-x86_64 -kernel bzImage -initrd initrd.img
# in need of killing qemu: killall qemu*

# you can use also: -nographic -append 'console=tyyS0', so:
#qemu-system-x86_64 -kernel bzImage -initrd initrd.img -nographic -append 'console=ttyS0'
# so you handle a serial interface

#for better performance, add the `-enable-kvm` option if your host has KVM enabled:
qemu-system-x86_64 -kernel bzImage -initrd initrd.img -nographic -append 'console=ttyS0' -enable-kvm

# press CTRL + D, to close the serial interface to the qemu machine.
# or CTRL + A and then X.

```

Other interesting init file to use, is:

```bash
#!/bin/sh
/bin/mount -t devtmpfs devtmpfs /dev
/bin/mount -t proc none /proc
/bin/mount -t sysfs none /sys
exec 0</dev/console
exec 1>/dev/console
exec 2>/dev/console
cat <<!


Boot took $(cut -d' ' -f1 /proc/uptime) seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


!
exec /bin/sh
```

Other links to build other qemu machines are at:
 - x86-64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_ubuntu-host_qemu-vm_x86-64-kernel.md
 - arm64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_linux-host_qemu-vm_arm64-kernel.md
 - riscv64: https://github.com/google/syzkaller/blob/master/docs/linux/setup_linux-host_qemu-vm_riscv64-kernel.md
 - a simple workflow to debug the linux kernel: https://marliere.net/posts/1/



# other builds
## Common

````
export OPT=/opt
export BUILDS=/some/where/mini_linux
mkdir -p $BUILDS
````

## Linux kernel

````
export LINUX=$OPT/linux
export LINUX_BUILD=$BUILDS/linux
mkdir -p $LINUX_BUILD
cd $LINUX
make O=$LINUX_BUILD allnoconfig
cd $LINUX_BUILD
make menuconfig
````

Configure the kernel according the following:

````
64-bit kernel ---> yes
General setup ---> Initial RAM filesystem and RAM disk (initramfs/initrd) support ---> yes
General setup ---> Configure standard kernel features ---> Enable support for printk ---> yes
Executable file formats / Emulations ---> Kernel support for ELF binaries ---> yes
Executable file formats / Emulations ---> Kernel support for scripts starting with #! ---> yes
Device Drivers ---> Generic Driver Options ---> Maintain a devtmpfs filesystem to mount at /dev ---> yes
Device Drivers ---> Generic Driver Options ---> Automount devtmpfs at /dev, after the kernel mounted the rootfs ---> yes
Device Drivers ---> Character devices ---> Enable TTY ---> yes
Device Drivers ---> Character devices ---> Serial drivers ---> 8250/16550 and compatible serial support ---> yes
Device Drivers ---> Character devices ---> Serial drivers ---> Console on 8250/16550 and compatible serial port ---> yes
File systems ---> Pseudo filesystems ---> /proc file system support ---> yes
File systems ---> Pseudo filesystems ---> sysfs file system support ---> yes
````

Build the kernel:

````
time make -j($nproc)
````

````
...
Kernel: arch/x86/boot/bzImage is ready  (#1)

real    2m37.247s
user    1m58.541s
sys     0m25.542s
````

## Busybox

````
export BUSYBOX=$OPT/busybox
export BUSYBOX_BUILD=$BUILDS/busybox
mkdir -p $BUSYBOX_BUILD
cd $BUSYBOX
make O=$BUSYBOX_BUILD defconfig
cd $BUSYBOX_BUILD
make menuconfig
````

Configure Busybox according the following:

````
Busybox Settings ---> Build Options ---> Build BusyBox as a static binary (no shared libs) ---> yes
````

Build Busybox:

````
time make -j8
````

````
...
Final link with: m

real    0m20.356s
user    0m46.959s
sys     0m10.628s
````

Install Busybox:

````
make install
````

Create an initramfs:

````
export INITRAMFS_BUILD=$BUILDS/initramfs
mkdir -p $INITRAMFS_BUILD
cd $INITRAMFS_BUILD
mkdir -p bin sbin etc proc sys usr/bin usr/sbin
cp -a $BUSYBOX_BUILD/_install/* .
````

Add a `$INITRAMFS_BUILD/init` script to the initramfs with the following content:

````
#!/bin/sh

mount -t proc none /proc
mount -t sysfs none /sys

cat <<!


Boot took $(cut -d' ' -f1 /proc/uptime) seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


!
exec /bin/sh
````

Create the initramfs archive:

````
chmod +x init
find . -print0 | cpio --null -ov --format=newc \
  | gzip -9 > $BUILDS/initramfs.cpio.gz
````

## Run and see (`<CTRL>a x` to quit)

````
qemu-system-x86_64 -kernel $LINUX_BUILD/arch/x86_64/boot/bzImage \
  -initrd $BUILDS/initramfs.cpio.gz -nographic \
  -append "console=ttyS0"
````

Note: for better performance, add the `-enable-kvm` option if your host has KVM enabled:
````
qemu-system-x86_64 -kernel $LINUX_BUILD/arch/x86_64/boot/bzImage \
  -initrd $BUILDS/initramfs.cpio.gz -nographic \
  -append "console=ttyS0" -enable-kvm
````

````
...


Boot took 0.45 seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


/ # ls /
bin      etc      linuxrc  root     sys
dev      init     proc     sbin     usr
/ # QEMU: Terminated
````

## Buildroot

We assume that a toolchain is available in `/opt/toolchains/x86_64-unknown-linux-gnu` with prefix `x86_64-unknown-linux-gnu`, gcc version 5.x, kernel headers series 4.3.x, glibc C library and C++ support. These are reasonable defaults if you are using a toolchain generated by crosstool-NG. Adapt to your own situation. Notes:
* You cannot use the native toolchain of your host computer (see Buildroot documentation to understand why).
* If you do not have a toolchain already, you can build one using crosstool-NG (or Buildroot itself) and reuse it for other projects.
* crosstool-NG is the recommended tool to build your own toolchain but avoid using uClibc (no IPV6 support), prefer uClibc-ng or glibc.
* You can also use the built-in toolchain of Buildroot but be aware that it will take way longer than using an existing toolchain. Be also aware that in many cases you will have to re-build the toolchain after modifying the Buildroot configuration.
* No yet convinced? Please use crosstool-NG, build and use your own toolchain.

````
export BUILDROOT=$OPT/buildroot
export BUILDROOT_BUILD=$BUILDS/buildroot
mkdir -p $BUILDROOT_BUILD
cd $BUILDROOT_BUILD
touch Config.in external.mk
echo 'name: mini_linux' > external.desc
echo 'desc: minimal linux system with buildroot' >> external.desc
mkdir configs overlay
cd $BUILDROOT
make O=$BUILDROOT_BUILD BR2_EXTERNAL=$BUILDROOT_BUILD qemu_x86_64_defconfig
cd $BUILDROOT_BUILD
make menuconfig
````

Configure Buildroot according the following:

````
Build options ---> Location to save buildroot config ---> $(BR2_EXTERNAL)/configs/mini_linux_defconfig
Build options ---> Download dir ---> /some/where/buildroot_dl
Build options ---> Number of jobs to run simultaneously (0 for auto) ---> 8
Build options ---> Enable compiler cache ---> yes
Build options ---> Compiler cache location ---> /some/where/buildroot_ccache
Toolchain ---> Toolchain type ---> External toolchain
Toolchain ---> Toolchain ---> Custom toolchain
Toolchain ---> Toolchain origin ---> Pre-installed toolchain
Toolchain ---> Toolchain path ---> /opt/toolchains/x86_64-unknown-linux-gnu
Toolchain ---> Toolchain prefix ---> x86_64-unknown-linux-gnu
Toolchain ---> External toolchain gcc version ---> 5.x
Toolchain ---> External toolchain kernel headers series ---> 4.3.x
Toolchain ---> External toolchain C library ---> glibc/eglibc
Toolchain ---> Toolchain has C++ support? ---> yes
System configuration ---> System hostname ---> mini_linux
System configuration ---> System banner ---> Welcome to mini_linux
System configuration ---> Run a getty (login prompt) after boot ---> TTY port ---> ttyS0
System configuration ---> Network interface to configure through DHCP --->
System configuration ---> Root filesystem overlay directories ---> $(BR2_EXTERNAL)/overlay
Kernel ---> Linux Kernel ---> no
Filesystem images ---> cpio the root filesystem (for use as an initial RAM filesystem) ---> yes
Filesystem images ---> Compression method ---> gzip
````

Save the configuration and build:

````
make savedefconfig
````

Add a `$BUILDROOT_BUILD/overlay/init` script to the overlay with the following content:

````
#!/bin/sh
/bin/mount -t devtmpfs devtmpfs /dev
/bin/mount -t proc none /proc
/bin/mount -t sysfs none /sys
exec 0</dev/console
exec 1>/dev/console
exec 2>/dev/console
cat <<!


Boot took $(cut -d' ' -f1 /proc/uptime) seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


!
exec /bin/sh
````

Build the root filesystem:

````
chmod +x overlay/init
time make
````

````
...
real    1m52.905s
user    0m50.682s
sys     0m36.928s
````

## Run and see (`<CTRL>a x` to quit)

````
qemu-system-x86_64 -kernel $LINUX_BUILD/arch/x86_64/boot/bzImage \
  -initrd $BUILDROOT_BUILD/images/rootfs.cpio.gz -nographic \
  -append "console=ttyS0"
````

Note: for better performance, add the `-enable-kvm` option if your host has KVM enabled.

````
...


Boot took 0.57 seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


/ # ls /
bin      init     linuxrc  opt      run      tmp
dev      lib      media    proc     sbin     usr
etc      lib64    mnt      root     sys      var
/ # QEMU: Terminated
````

## Add and run a custom user application

Create a new directory for the custom user applications:

````
export APPS=$BUILDS/apps
mkdir -p $APPS
cd $APPS
````

Add an application source file `$APPS/hello_world.c` with the following content:

````
#include <stdio.h>

int main(int argc, char **argv) {
	printf("mini_linux says: Hello world!\n");
	return 0;
}
````

Add a `$APPS/Makefile` with the following content (replace the `CROSS_COMPILE` definition with whatever is appropriate in your specific case):

````
CROSS_COMPILE	:= /opt/toolchains/x86_64-unknown-linux-gnu/bin/x86_64-unknown-linux-gnu-
CC		:= $(CROSS_COMPILE)gcc

hello_world: hello_world.o
	$(CC) -o $@ $<

hello_world.o: hello_world.c
	$(CC) -c -o $@ $<

clean:
	rm -f hello_world hello_world.o
````

Compile the application, copy it in the Buildroot overlay directory and re-build the root filesystem:

````
make
...
cp hello_world $BUILDROOT_BUILD/overlay
...
cd $BUILDROOT_BUILD
make
````

## Run and see (`<CTRL>a x` to quit)

````
qemu-system-x86_64 -kernel $LINUX_BUILD/arch/x86_64/boot/bzImage \
  -initrd $BUILDROOT_BUILD/images/rootfs.cpio.gz -nographic \
  -append "console=ttyS0"
````

Note: for better performance, add the `-enable-kvm` option if your host has KVM enabled.

````
...


Boot took 0.57 seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


/ # ls
bin          init         media        root         tmp
dev          lib          mnt          run          usr
etc          lib64        opt          sbin         var
hello_world  linuxrc      proc         sys
/ # ./hello_world
mini_linux says: Hello world!
/ # QEMU: Terminated
````

## Add loadable module support to the Linux kernel

````
cd $LINUX_BUILD
make menuconfig
````

Change the kernel configuration according the following:

````
Enable loadable module support ---> yes
````

Re-build the kernel and its modules (none, in our case) and install the modules in the Buildroot overlay directory:

````
make -j8
make -j8 modules
make modules_install INSTALL_MOD_PATH=$BUILDROOT_BUILD/overlay
````

## Add a custom user module

Create a new directory for the custom user modules:

````
export MODULES=$BUILDS/modules
mkdir -p $MODULES
cd $MODULES
````

Add a module source file `$MODULES/hello_world.c` with the following content:

````
/* hello_world.c */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init first_init(void)
{
  pr_info("mini_linux module says: Hello world!\n");
  return 0;
}

static void __exit first_exit(void)
{
  pr_info("Bye\n");
}

module_init(first_init);
module_exit(first_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My first module");
MODULE_AUTHOR("The Doctor");
````

Add a `$MODULES/Makefile` with the following content:

````
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello_world.o

else
# normal makefile
KDIR ?= $(LINUX_BUILD)

default:
	$(MAKE) -C $(KDIR) M=$$PWD

modules_install:
	$(MAKE) -C $(KDIR) M=$$PWD $@

clean:
	rm -rf *.o .*.cmd *.ko hello_world.mod.c modules.order Module.symvers .tmp_versions
endif
````

Compile the module, install it in the Buildroot overlay directory and re-build the root filesystem:

````
make
...
make modules_install INSTALL_MOD_PATH=$BUILDROOT_BUILD/overlay
...
cd $BUILDROOT_BUILD
make
````

## Run and see (`<CTRL>a x` to quit)

````
qemu-system-x86_64 -kernel $LINUX_BUILD/arch/x86_64/boot/bzImage \
  -initrd $BUILDROOT_BUILD/images/rootfs.cpio.gz -nographic \
  -append "console=ttyS0"
````

Note: for better performance, add the `-enable-kvm` option if your host has KVM enabled.

````
...


Boot took 0.57 seconds

        _       _     __ _                  
  /\/\ (_)_ __ (_)   / /(_)_ __  _   ___  __
 /    \| | '_ \| |  / / | | '_ \| | | \ \/ /
/ /\/\ \ | | | | | / /__| | | | | |_| |>  < 
\/    \/_|_| |_|_| \____/_|_| |_|\__,_/_/\_\ 


Welcome to mini_linux


/ # ls lib/modules/4.8.0\+/extra
hello_world.ko
/ # lsmod
Module                  Size  Used by    Not tainted
/ # insmod lib/modules/4.8.0\+/extra/hello_world.ko
hello_world: loading out-of-tree module taints kernel.
mini_linux module says: Hello world!
/ # lsmod
Module                  Size  Used by    Tainted: G  
hello_world              704  -
/ # QEMU: Terminated
````


# DEBUGING A LINUX KERNEL WITH QEMU AND GDB

References:
 - https://javiercarrascocruz.github.io/syzbot
 - https://marliere.net/posts/1/
 - https://github.com/google/syzkaller/blob/master/docs/linux/setup_ubuntu-host_qemu-vm_x86-64-kernel.md#install-qemu
 - https://github.com/google/syzkaller/blob/master/docs/syzbot_assets.md
 - https://nickdesaulniers.github.io/blog/2018/10/24/booting-a-custom-linux-kernel-in-qemu-and-debugging-it-with-gdb/
 - Mentorship Session: Linux Kernel Debugging Tricks of the Trade: https://youtu.be/FdNIiQxwJuk

```bash
$ qemu-system-x86_64 \
        -m 2G \
        -smp 2 \
        -kernel linux/arch/x86/boot/bzImage \
	-append "console=ttyS0 root=/dev/sda earlyprintk=serial net.ifnames=0" \
        -drive file=image/bullseye.img,format=raw \
        -net user,host=10.0.2.10,hostfwd=tcp::10021-:22 \
        -net nic,model=e1000 \
        -enable-kvm \
        -append nokaslr \
        -nographic \
        -snapshot \
        -pidfile vm.pid \
	2>&1 | tee vm.log
```

```bash
$ gdb -tui -ex "target remote :1234" "$HOME/linux/vmlinux" 
```

Reference qemu-gdb: https://www.qemu.org/docs/master/system/gdb.html



