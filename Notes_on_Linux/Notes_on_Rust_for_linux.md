# Notes on Rust for Linux


## Rust programming language references:

Languaje reference:                                                           
  - https://doc.rust-lang.org/book                                              
  - https://doc.rust-lang.org/rust-by-example                                   
  - https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/
  - https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/effective-rust.html
  - https://doc.rust-lang.org/nomicon/                                          
  - https://rust-lang.github.io/async-book/01_getting_started/01_chapter.html   
  - https://github.com/rust-lang/rustlings                                      
  - https://github.com/rust-lang/rustlings/tree/rustlings-1   
  - little book of rust macros: https://github.com/DanielKeep/tlborm            
  - little book of rust macros updated: https://github.com/Veykril/tlborm     
  - https://google.github.io/comprehensive-rust/welcome-day-4.html
  - https://github.com/ferrous-systems/teaching-material/tree/main/assignments
  
  - blog. how to module in rust: - https://codeberg.org/vincenzopalazzo/linux-kernel-drivers
  - blog. how to write a module in rust: https://www.jackos.io/rust-kernel/rust-for-linux.html#adding-the-rust-module
  - blog. https://www.jackos.io/rust-kernel/rust-for-linux.html
  - blog. rust module getting startedhttps://wusyong.github.io/posts/rust-kernel-module-00/
  - blog. rust kernel module: hello world https://wusyong.github.io/posts/rust-kernel-module-01/

## Rust for linux

**RFC**: https://lkml.org/lkml/2021/4/14/1023

**Oficial site**: https://github.com/Rust-for-Linux <br>
 - https://rust-for-linux.com/

**website documentation**: https://rust-for-linux.com/

https://github.com/Rust-for-Linux/rust-out-of-tree-module

Documentation: https://github.com/Rust-for-Linux/linux/tree/rust/Documentation/rust

Main work: https://github.com/Rust-for-Linux/linux

Contribute: https://github.com/Rust-for-Linux/linux/contribute

Quick start: https://github.com/Rust-for-Linux/linux/blob/rust/Documentation/rust/quick-start.rst


rust for linux mail-list: https://lore.kernel.org/rust-for-linux/

Rust in the Linux ecosystem : https://youtu.be/jTWdk0jYy54

Rust for Linux: https://youtu.be/46Ky__Gid7M

Documentation: https://rust-for-linux.github.io/docs/kernel/ 

lwn.net More rust concepts for the kernel: https://lwn.net/Articles/869428/

article: https://www.memorysafety.org/blog/memory-safety-in-linux-kernel/

kernel crate: https://rust-for-linux.github.io/docs/kernel/

https://discourse.ubuntu.com/t/ubuntu-kernel-is-getting-rusty-in-lunar/34977

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
 - files from the previous video: https://drive.google.com/drive/folders/1nmUhDVJxCKolkDN64U7Brm4kBQrvUGPq
 - commits from the previous session: https://github.com/wedsonaf/linux/commits/lf-session
 - Kangrejos 2022: https://kangrejos.com/  & https://paulmck.livejournal.com/68136.html
 - LPC 2022: https://youtu.be/Xw9pKeJ-4Bw?list=PLVsQ_xZBEyN0daQRmKO4ysrjkSzaLI6go&t=4320
 - Mentorship Session: Setting Up an Environment for Writing Linux Kernel Modules in Rust: https://www.youtube.com/watch?v=tPs1uRqOnlk
 - The Linux Kernel Gets Rusty - Jonathan Corbet, RUST and the Linux Kernal Development: https://youtu.be/gVC1gp2PS8U


## Others

- https://lwn.net/Articles/869428/
- https://github.com/d0u9/Linux-Device-Driver
- https://austincminor.com/20211030000942-ramfs_rust.html

- https://lkml.org/lkml/2022/9/19/1105
- the pull request to enter Linux: https://lore.kernel.org/lkml/202210010816.1317F2C@keescook/
- about pinning: 
    - https://rust-lang.github.io/async-book/04_pinning/01_chapter.html
    - https://y86-dev.github.io/blog/safe-pinned-initialization/overview.html
    - https://github.com/y86-dev/pinned-init
    - https://github.com/y86-dev/rfcs/blob/field-projection/text/3318-field-pojection.md 
    - https://github.com/rust-lang/rfcs/blob/master/text/2349-pin.md
    - https://y86-dev.github.io/blog/return-value-optimization/placement-by-return.html
    - https://github.com/rust-lang/rfcs/pull/3318
    - https://kangrejos.com/Pinning%20in%20Rust.pdf
    - The perils of pinning: https://lwn.net/Articles/907876/

- https://lwn.net/SubscriberLink/910762/e103310fccf871d3/
- https://blog.hedwing.dev/linux-kernel/intro_to_linux
- https://codeberg.org/vincenzopalazzo/linux-kernel-drivers
- A first look at Rust in the 6.1 kernel: https://lwn.net/Articles/910762/
- Rust in the 6.2 kernel: https://lwn.net/Articles/914458/
- https://hackmd.io/Yp2D8H_hRtuiGD2yYFZyLA
- https://research.nccgroup.com/2023/02/06/rustproofing-linux-part-1-4-leaking-addresses/
- rust kernel module: hello world https://wusyong.github.io/posts/rust-kernel-module-01/


### interestig commits
- rust simple mutex: https://github.com/Rust-for-Linux/linux/commit/47e93d46eaca3a3648837eb6f5ae136812a28831
- rust mutex: https://github.com/Rust-for-Linux/linux/commit/be5ff7d29d5b4da2706cc5384f38d7e417bc26f5
- rust modules: https://github.com/wedsonaf/linux/commits/lf-session
- static assert: https://github.com/Rust-for-Linux/linux/pull/269
- https://github.com/Darksonn/linux/commit/8ef510d25f353c9c2e240e067e232b459e737a90
- https://github.com/Darksonn/linux/commit/ff03d355219af7a4156de81b77b2f423ff3d8a47
- rust: new api for initialization: https://github.com/Rust-for-Linux/linux/pull/909/files#diff-20432b0044e991d44b184c5bfa4cd92681e119758c93ba9fef5f4c629de688f1
- rust: rust: Introduce jiffies-based timer support : https://github.com/fbq/linux-rust/commit/c31a2a3ce7420b43bda2c6f1b43227baf0d13661

### Others 2

rust-dev dockerfile: (reference: https://github.com/mabembedded/dockerfiles/blob/main/Dockerfile.rust)

```
FROM rust

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    vim \
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
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
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

# the config: qemu-busybox-min.config, should be in /kernel/configs

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
~/busybox$ make defconfig # make default configuration
# we want to build busybox statically
~/busybox$ make menuconfig # check: --Settings -> --Build Options -> Build static binary (no shared libs) 
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

#sergio@debian:~/busybox/_install$ find . | cpio -H newc -o | gzip > ./ramdisk.img

#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img
#5314 blocks
#sergio@debian:~/busybox/_install$ ls
#bin  linuxrc  ramdisk.img  sbin  usr

# now we have a ramdisk.img to build the kernel

## move again to the linux folder
sergio@debian:~/busybox$ cd $HOME/linux
sergio@debian:~/linux$ 

#now qemu is installed, it it is not installed yet, then execute: sudo apt install qemu-kvm
sergio@debian:~/linux$ qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img
# qemu: could not load kernel 'vmlinux': No such file or directory # this error is due the kernel has not been compiled yet: make LLVM=1 -j32

# use CTRL +  A and then press: X to get out of it.

# create a etc directory
~/busybox/_install$ mkdir etc
# copy the intitab from the busybox examples:
~/busybox/_install$ cp ../examples/inittab ./etc
# modify the file, removing the tty2::askfirst-/bin/sh to  ... tty5
# regenerate the image. 
#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img

# go back to linux and run it. 
~/linux$ qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img

# still there is the wargin about : can't run "etc/inti.d/rcS": No such file or directory
# and that file is interesting because it allows to run commands at the boot

# Also is the complaint it cannot find /proc. Just create /proc
mkdir /proc
# mount a proc filesystem there
mount -t proc none /proc

# create the file:  "/etc/inti.d/rcS", and there add the commands to mount /proc
#sergio@debian:~/busybox/_install$ mkdir -p etc/init.d/
#sergio@debian:~/busybox/_install$ vim etc/init.d/rcS
mkdir -p /proc
mount -t proc none /proc

# make the file executable
#sergio@debian:~/busybox/_install$ chmod a+x  etc/init.d/rcS

# regenerate the image 
#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img

# now we can boot, and to get out use the command: poweroff

# move to the linux folder.

#sergio@debian:~/linux$   make LLVM=1 menuconfig

# configure: Main Menu -> Kernel hacking -> Sample kernel code -> Rust samples -> Echo server module 
# you may need to enable the samples:  Depends on: SAMPLES [=y] && SAMPLES_RUST [=y]   
# building the kernel again it will include the echo server

# we may want to edit the code, to get some otutput

# vi samples/rust/rust_echo_server.rs 
+ pr_info!("Hello from echo server\n"); 

# ~/linux$ make LLVM=1 -j32

# boot the machine 
qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img

# after booting, in the messages check for the text string "Hello from echo server", 
# that proofs that the echo_server_module has been loaded
# [    2.232579] rust_echo_server: Hello from echo server


the echo server listens to port 8080, and repeats back the received messages. 

# use the command `netstat -a`

~ # netstat -a
Active Internet connections (servers and established)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       
tcp        0      0 0.0.0.0:8080            0.0.0.0:*               LISTEN      
Active UNIX domain sockets (servers and established)
Proto RefCnt Flags       Type       State         I-Node Path
netstat: /proc/net/unix: No such file or directory

#if we try to connect, nothing will happen
VM# nc 127.0.0.1 8080
VM# ifconfig
#... the network interfece is not setup
#enable loopback with:
VM# ifconfig lo up 
# now it is possible to connect to the echo sever
VM# nc 127.0.0.1 8080
... write some random text to see if it is repeated back

# it is interting to have those interfaces up, So please add it to the interface. at etc/init.d/rcS + ipconfig lo up

# exit with poweroff

# another intersting thing to enable is to enable a NIC (network interface card). for this use the command: 
qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img -nic user,model=rtl8139 

# launch the machine, and check the interfaces with: ip link

VM# udhcpc -i eth 

with the previos command, the dhcp is lauched

add in busybox: 
#sergio@debian:~/busybox/_install$ mkdir -p usr/share/udhcpc
#sergio@debian:~/busybox/_install$ cp ../examples/udhcp/simple.script usr/share/udhcpc/default.script 

# with this one file of the busybox examples is copied into that directory: usr/share/udhcpc

# update the init script to: 
#sergio@debian:~/busybox/_install$ vi etc/init.d/rcS
mkdir -p /proc             # creates /proc
mount -t proc none /proc   # mounts /proc filesystem
ifconfig lo up             # start loopback
udhcpc -i eth0             # udpates dhcp

# rebuild the image 
#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img
# relaunch the machine
qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/ramdisk.img -nic user,model=rtl8139 

#if we check ifconfig, the network interface should be up, so networking is active. 
# this allows to go from the VM to the outside world!!!
# with this we can connect to the VM. 

# add an option for fowarding ports in the VM. We are forwarding the port 5555 local machine to the port 23 of the VM
qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img -nic user,model=rtl8139,hostfwd=tcp::5555-:23

# ..other topic, mounting /dev 
VM# mount -t devtmps none /dev
VM# ld /dev # now it should be populated
VM# mkdir /dev/pts
VM# mount -t devpts nodev /dev/pts
VM# telnetd -l /bin/sh                  # now it is possible to run telnetd

from other terminal, try to connect:

#sergio@debian$ telnet localhost 5555
Trying 127.0.0.1... 
Connected to localhost.
Escape character is '^}]'.

# ... and now we are in the VM :)

# lets add those commands into the init script: 
#sergio@debian:~/busybox/_install$ vi etc/init.d/rcS
mkdir -p /proc             # creates /proc
mount -t proc none /proc   # mounts /proc filesystem
ifconfig lo up             # start loopback
udhcpc -i eth0             # udpates dhcp
mkdir -p /dev/
mount -t devtmpfs none /dev
mkdir -p /dev/pts
mount -t devpts none /dev/pts

# rebuild the image 
#sergio@debian:~/busybox/_install$  find . | cpio -H newc -o | gzip > ./ramdisk.img

# launch the VM
qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img -nic user,model=rtl8139,hostfwd=tcp::5555-:23

# try to telnet it
telnet localhost 5555

# other  thing to tacke is forward other port 5556 to the port of the echo_server. 
qemu-system-x86_64 -nographic -kernel vmlinux -initrd ../busybox/_install/ramdisk.img -nic user,model=rtl8139,hostfwd=tcp::5555-:23,hostfwd=tcp::5556-:8080

# so from the local machine, it is possible to cnect to th echo server previouly configured.
nc localhost 5556

Rust analyzer: https://youtu.be/tPs1uRqOnlk?t=3564


sergio@laptop:~/repos/rust-for-linux$ sudo make LLVM=1 -j12 rust-analyzer
[sudo] password for sergio: 
make[1]: rustc: No such file or directory
/bin/sh: 1: rustc: not found
Traceback (most recent call last):
  File "/home/sergio/repos/rust-for-linux/./scripts/generate_rust_analyzer.py", line 141, in <module>
    main()
  File "/home/sergio/repos/rust-for-linux/./scripts/generate_rust_analyzer.py", line 134, in main
    "crates": generate_crates(args.srctree, args.objtree, args.sysroot_src),
  File "/home/sergio/repos/rust-for-linux/./scripts/generate_rust_analyzer.py", line 15, in generate_crates
    with open(objtree / "include" / "generated" / "rustc_cfg") as fd:
FileNotFoundError: [Errno 2] No such file or directory: 'include/generated/rustc_cfg'
make[1]: *** [rust/Makefile:392: rust-analyzer] Error 1
make: *** [Makefile:1837: rust-analyzer] Error 2


...just create 'include/generarted/rust_cfg' and run the command again. 
this will create a file: rust-project.json for the rust LSP server

make LLVM=1 -j12 rustfmtcheck # check the formating

make LLVM=1 -j12 rustfmt # format it

make LLVM=1 -j12 rustdoc # generate documentation

make LLVM=1 -j12 CLIPPY=1 # linter

make LLVM=1 -j12 rusttest # run tests on the host

It is possible to enable KUNITS and rust tests for KUNITs.

```

