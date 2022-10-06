# Notes on Rust

**RFC**: https://lkml.org/lkml/2021/4/14/1023

**Oficial site**: https://github.com/Rust-for-Linux

https://github.com/Rust-for-Linux/rust-out-of-tree-module

Main work: https://github.com/Rust-for-Linux/linux

Contribute: https://github.com/Rust-for-Linux/linux/contribute

Quick start: https://github.com/Rust-for-Linux/linux/blob/rust/Documentation/rust/quick-start.rst


rust for linux mail-list: https://lore.kernel.org/rust-for-linux/

Rust in the Linux ecosystem : https://youtu.be/jTWdk0jYy54

Rust for Linux: https://youtu.be/46Ky__Gid7M

Documentation: https://rust-for-linux.github.io/docs/kernel/ 

lwn.net More rust concepts for the kernel: https://lwn.net/Articles/869428/

article: https://www.memorysafety.org/blog/memory-safety-in-linux-kernel/


## Videos: 

 - Oct 2, 2019: Writing Linux Kernel Modules in Safe Rust - https://www.youtube.com/watch?v=RyY01fRyGhM
 - August 31, 2020: Supporting Linux kernel development in Rust - https://lwn.net/Articles/829858/
 - April 21, 2021: Rust heads into the kernel? - https://lwn.net/Articles/853423/
 - July 7, 2021: Rust for Linux redux - https://lwn.net/Articles/862018/
 - July 19, 2021: A GPIO driver in Rust - https://lwn.net/Articles/863459/
 - Sept 16, 2021: The Rust for Linux project - https://lwn.net/Articles/869145/
 - Sept 20, 2021: More Rust concepts for the kernel - https://lwn.net/Articles/869428/
 - Sept 28, 2021: Using Rust for kernel development - https://lwn.net/Articles/871061/
 - Oct 4, 2021: Rust and GCC, two different ways - https://lwn.net/Articles/871283/
 - Nov 13, 2021: Rust for linux: Rust for Linux
 - Marz 25, 2022: https://www.youtube.com/watch?v=fVEeqo40IyQ
 - Mentorship Session: Rust for Linux: Writing Safe Abstractions & Drivers: https://youtu.be/3VU0hfsbHdc
 - Mentorship Session: Rust for Linux: Code Documentation & Tests: https://youtu.be/J8yoUQKEY5g
 - Mentorship Session: Writing Linux Kernel Modules in Rust: https://youtu.be/-l-8WrGHEGI
 - Kangrejos 2022: https://kangrejos.com/  & https://paulmck.livejournal.com/68136.html
 - LPC 2022: https://youtu.be/Xw9pKeJ-4Bw?list=PLVsQ_xZBEyN0daQRmKO4ysrjkSzaLI6go&t=4320
 - Mentorship Session: Setting Up an Environment for Writing Linux Kernel Modules in Rust: https://www.youtube.com/watch?v=tPs1uRqOnlk


## Others

- https://lwn.net/Articles/869428/
- https://github.com/d0u9/Linux-Device-Driver
- https://austincminor.com/20211030000942-ramfs_rust.html
- rust simple mutex: https://github.com/Rust-for-Linux/linux/commit/47e93d46eaca3a3648837eb6f5ae136812a28831
- rust mutex: https://github.com/Rust-for-Linux/linux/commit/be5ff7d29d5b4da2706cc5384f38d7e417bc26f5
- rust modules: https://github.com/wedsonaf/linux/commits/lf-session
- https://lkml.org/lkml/2022/9/19/1105
- about pinning: 
    - https://y86-dev.github.io/blog/safe-pinned-initialization/overview.html
    - https://github.com/y86-dev/pinned-init
    - https://github.com/y86-dev/rfcs/blob/field-projection/text/3318-field-pojection.md 
    - https://github.com/rust-lang/rfcs/blob/master/text/2349-pin.md
    - https://y86-dev.github.io/blog/return-value-optimization/placement-by-return.html
    - https://github.com/rust-lang/rfcs/pull/3318
    - https://kangrejos.com/Pinning%20in%20Rust.pdf


rust-dev dockerfile: (reference: https://github.com/mabembedded/dockerfiles/blob/main/Dockerfile.rust)

```
FROM rust

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    bison \
    curl \
    flex \
    git \
    git-core \
    libclang-dev \
    libncurses-dev \
    lld \
    clang \
    llvm \
    libelf-dev \
    qemu-kvm 

ENV USER_NAME dev
ARG host_uid=1000
ARG host_gid=1000
RUN groupadd -g $host_gid $USER_NAME && \
    useradd -g $host_gid -m -s /bin/bash -u $host_uid $USER_NAME

USER dev

WORKDIR /home/dev

RUN git clone https://github.com/Rust-for-Linux/linux.git 
RUN git clone https://github.com/mirror/busybox.git
RUN rustup component add rust-src
RUN cd $HOME/linux && cargo install --locked --version $(scripts/min-tool-version.sh bindgen) bindgen
RUN cd $HOME/linux && rustup override set $(scripts/min-tool-version.sh rustc)
RUN make LLVM=1 rustavailable
RUN make LLVM=1 allnoconfig qemu-busybox-min.config rust.config
```


The steps to build: 

```
/src/linux$ make allnoconfig qemu-busybox-min.config
/src/linux$ make LLVM=1 allnoconfig qemu-busybox-min.config #this configuration is for fast development.

# ... but with this .config rust will not be enabled. 
# merged configuration written to .config (needs make)
#
#
# configuration written to .config
# ... another config needs to be used

/src/linux$ make LLVM=1 allnoconfig qemu-busybox-min.config rust.config #this configuration is for fast development.

#Value of CONFIG_RUST is redefined by fragment ./kernel/configs/rust.config:
#Previous value: # CONFIG_RUST is not set
#New value: CONFIG_RUST=y
#
# merged configuration written to .config (needs make)
#
# configuration written to .config
#

make LLVM=1 rustavailable # the rustavailabe target will indicate to check for all dependencies

nproc # to count number of cpus
make LLVM=1 -j32 # compile whit 32 cpus

cd busybox 
make defconfig # make default configuration

make menuconfig # check settings -> --Build Options -> Build static binary (no shared libs) 
# with this it is no needed add a libc image

make -j32
# ... the output should end like: ...
#  LINK    busybox_unstripped
#Static linking against glibc, can't use --gc-sections
#Trying libraries: crypt m resolv rt
# Library crypt is not needed, excluding it
# Library m is needed, can't exclude it (yet)
# Library resolv is needed, can't exclude it (yet)
# Library rt is not needed, excluding it
# Library m is needed, can't exclude it (yet)
# Library resolv is needed, can't exclude it (yet)
#Final link with: m resolv

make install # this create a directory call __install which is our image, the image that will be installed. 

#  ./_install//usr/sbin/ubiupdatevol -> ../../bin/busybox
#  ./_install//usr/sbin/udhcpd -> ../../bin/busybox
#--------------------------------------------------
#You will probably need to make your busybox binary
#setuid root to ensure all configured applets will
#work properly.
#--------------------------------------------------

#sergio@debian:~/busybox$ cd _install
#sergio@debian:~/busybox/_install$ ls
#bin  linuxrc  sbin  usr

# these are the files that will make the image that will be installed later. 
# the tool used to build the image is `cpio`

#sergio@debian:~/busybox/_install$ find . | cpio -H newc -o | gzip > ./ramdisk.image

#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img
#5314 blocks
#sergio@debian:~/busybox/_install$ ls
#bin  linuxrc  ramdisk.img  sbin  usr

# now we have a ramdisk.img to build the kernel

## move again to the linux folder
sergio@debian:~/busybox$ cd $HOME/linux
sergio@debian:~/linux$ 

qemu-system-x86-64 -nographic -kernel vmlinux -initrd ../busybox/ramdisk.img
# qemu: could not load kernel 'vmlinux': No such file or directory # this error is due the kernel has not been compiled yet: make LLVM=1 -j32

CTRL +  A + X to get out of it.

cp ../examples/inittap ./etc
# modify the file, removign the tty2::askfirst-/bin/sh to  ... tty5
# regenerate the image. 
#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img

# go back to linux and run it. 
qemu-system-x86-64 -nographic -kernel vmlinux -initrd ../busybox/ramdisk.img

# still there is the wargin about : can't run "/etc/inti.d/rcS": No such file or directory
# and that file is interesting because it allows to run commands at the boot

# Also is the complain it can find /proc. Just create /proc
mkdir /proc
# mount a proc filesystem there
mount -t proc none /proc

# create the file:  "/etc/inti.d/rcS", and there add the commands to mount /proc


```

