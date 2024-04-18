# Notes on Rust for Linux


## Rust programming language references:

Languaje reference:             
  - https://stevedonovan.github.io/rust-gentle-intro/
  - https://doc.rust-lang.org/book                                              
  - https://doc.rust-lang.org/rust-by-example
  - Beginner's guide to Error Handling in Rust: https://www.sheshbabu.com/posts/rust-error-handling/
  - Rust memory safety explained: https://www.infoworld.com/article/3714925/rust-memory-safety-explained.html
  - rustlings exercises: https://github.com/rust-lang/rustlings/tree/rustlings-1
  - https://doc.rust-lang.org/stable/reference/                  
  - https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/
  - https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/effective-rust.html
  - https://doc.rust-lang.org/nomicon/                                          
  - https://rust-lang.github.io/async-book/01_getting_started/01_chapter.html
  - async: red and blue functions: https://journal.stuffwithstuff.com/2015/02/01/what-color-is-your-function/
  - https://github.com/rust-lang/rustlings                                      
  - https://github.com/rust-lang/rustlings/tree/rustlings-1   
  - little book of rust macros: https://github.com/DanielKeep/tlborm            
  - little book of rust macros updated: https://github.com/Veykril/tlborm
  - https://blog.logrocket.com/macros-in-rust-a-tutorial-with-examples/#whatarerustmacros
  - macros_by_example: https://doc.rust-lang.org/reference/macros-by-example.html
  - https://google.github.io/comprehensive-rust/welcome-day-4.html
  - Ferrous training: 
      - https://github.com/ferrous-systems/teaching-material/tree/main/assignments
      - https://github.com/ferrous-systems/rust-training
  - effective rust: https://www.lurklurk.org/effective-rust/
  - awesome rust - curated list of resources: https://github.com/lemunozm/awesome-rust
  - https://docs.rust-embedded.org/book/intro/index.html
  - rust async: https://rust-lang.github.io/async-book/
  - rustup: https://rust-lang.github.io/rustup/
  - https://reintech.io/blog/understanding-implementing-rust-variance-lifetimes
  - FFI: https://doc.rust-lang.org/nomicon/ffi.html#foreign-function-interface
  - FFI: https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/ffi.html
  - intro unsafe rust: https://google.github.io/comprehensive-rust/unsafe-rust/unsafe.html
  - Rust Foreing Functions Interface (FFI): https://michael-f-bryan.github.io/rust-ffi-guide/overview.html
  - Network programming with Rust: https://github.com/PacktPublishing/Network-Programming-with-Rust
  - Complex cpp rust ffi: https://github.com/emilio/rust-cpp-ffi-examples/tree/master
  - bindgen user guide: https://rust-lang.github.io/rust-bindgen/introduction.html
  - rust rfc book: https://rust-lang.github.io/rfcs

Other resources:
  - linux kernel rust documentation: https://docs.kernel.org/rust/index.html
  - key rust concepts for the kernel: https://lwn.net/Articles/869317/
  - patches: https://github.com/tgross35/RFL-patch-registry?tab=readme-ov-file
  - min configs: https://rust-for-linux.zulipchat.com/#narrow/stream/291565-Help/topic/Build.20error.20on.20rust.20next.20when.20using.20minimal.20.2Econfig
  - recipe to  Rust Linux Kernel Workstation Setup: https://gist.github.com/nellshamrell/fa82173c59fc3b7dbb47a58d63aadade
  - more rust concepts for the kernel: https://lwn.net/Articles/869428/
  - rust for linux brief introduction: https://rustmagazine.org/issue-1/rust-for-linux-brief-introduction/
  - https://docs.kernel.org/rust/quick-start.html
  - blog. how to module in rust: - https://codeberg.org/vincenzopalazzo/linux-kernel-drivers
  - blog. how to write a module in rust: https://www.jackos.io/rust-kernel/rust-for-linux.html#adding-the-rust-module
  - blog. https://www.jackos.io/rust-kernel/rust-for-linux.html
  - blog. rust module getting started https://wusyong.github.io/posts/rust-kernel-module-00/
  - blog. rust kernel module: hello world https://wusyong.github.io/posts/rust-kernel-module-01/
  - coccinelle for linux: this is the link to the talk: https://gitlab.inria.fr/coccinelle/coccinelleforrust/-/blob/main/talks/rfl.pdf
  - rust analyzer: https://rust-analyzer.github.io/manual.html
  - https://github.com/rust-unofficial/awesome-rust
  - https://sunjay.dev/learn-game-dev/intro.html
  - game dev in rust: https://www.youtube.com/playlist?list=PLn3eTxaOtL2M-VkAeqk0p3Xn7byveJ9qX
  - bindgen: https://fitzgeraldnick.com/2016/12/14/using-libbindgen-in-build-rs.html
  - bindgen : https://rust-lang.github.io/rust-bindgen/introduction.html
  - bindgen : https://apollolabsblog.hashnode.dev/rust-ffi-and-bindgen-integrating-embedded-c-code-in-rust
  - https://discourse.llvm.org/

  - https://wusyong.github.io/posts/rust-kernel-module-00/
  - https://wusyong.github.io/posts/rust-kernel-module-01/
  - https://wusyong.github.io/posts/rust-kernel-module-02/
  - https://wusyong.github.io/posts/rust-kernel-module-03/

## Design
- reference: https://github.com/fishinabarrel/linux-kernel-module-rust/

We run bindgen on the kernel headers to generate automatic Rust FFI bindings. bindgen is powered by Clang, so we use the kernel's own build system to determine the appropriate CFLAGS. Then we write safe bindings to these types (see the various files inside src/).

Each kernel module in Rust lives in a staticlib crate, which generates a .a file. We pass this object to the Linux kernel's own module build system for linking into a .ko.

The kernel is inherently multi-threaded: kernel resources can be accessed from multiple userspace processes at once, which causes multiple threads of execution inside the kernel to handle system calls (or interrupts). Therefore, the KernelModule type is Sync, so all data shared by a kernel module must be safe to access concurrently (such as by implementing locking).


## Rust for linux

**RFC**: https://lkml.org/lkml/2021/4/14/1023

**Oficial repo**: https://github.com/Rust-for-Linux <br>
**Oficial site**: - https://rust-for-linux.com/

**website documentation**: https://rust-for-linux.com/

- https://docs.kernel.org/rust/index.html
- https://lore.kernel.org/rust-for-linux/
- Key Rust concepts for the kernel: https://lwn.net/Articles/869317/
- More Rust concepts for the kernel: https://lwn.net/Articles/869428/
- https://hackmd.io/team/rust-for-linux-?nav=overview
- https://docs.kernel.org/rust/quick-start.html
- https://github.com/Rust-for-Linux/rust-out-of-tree-module
- Documentation: https://github.com/Rust-for-Linux/linux/tree/rust/Documentation/rust
- https://docs.kernel.org/rust/quick-start.html
- Main work: https://github.com/Rust-for-Linux/linux
- Contribute: https://github.com/Rust-for-Linux/linux/contribute
- Quick start: https://github.com/Rust-for-Linux/linux/blob/rust/Documentation/rust/quick-start.rst
- rust for linux mail-list: https://lore.kernel.org/rust-for-linux/
- Rust in the Linux ecosystem : https://youtu.be/jTWdk0jYy54
- Rust for Linux: https://youtu.be/46Ky__Gid7M
- Documentation: https://rust-for-linux.github.io/docs/kernel/ 
- lwn.net More rust concepts for the kernel: https://lwn.net/Articles/869428/
- article: https://www.memorysafety.org/blog/memory-safety-in-linux-kernel/
- kernel crate: https://rust-for-linux.github.io/docs/kernel/
- https://discourse.ubuntu.com/t/ubuntu-kernel-is-getting-rusty-in-lunar/34977
- R4L in space: https://lwn.net/Articles/954974/ - https://evlproject.org/overview/
- mapping developments: https://github.com/tgross35/RFL-patch-registry

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
 - Mentorship Session: Writing Linux Kernel Modules in Rust: https://www.youtube.com/watch?v=-l-8WrGHEGI
 - The Linux Kernel Gets Rusty - Jonathan Corbet, RUST and the Linux Kernal Development: https://youtu.be/gVC1gp2PS8U
 - Dec 12, 2023: High Stability Rust in Kernel by Kernel CI - Arisu Tachibana, Cybertrust Japan Co. : https://youtu.be/w4nhuQ00VV0


## Others

- https://lwn.net/Articles/869428/
- https://github.com/d0u9/Linux-Device-Driver
- https://austincminor.com/20211030000942-ramfs_rust.html

- https://lkml.org/lkml/2022/9/19/1105
- the pull request to enter Linux: https://lore.kernel.org/lkml/202210010816.1317F2C@keescook/
- about pinning:
    - https://rust-for-linux.zulipchat.com/#narrow/stream/288089-General/topic/Pin.2C.20or.3A.20why.20is.20memory.20moved.20around.3F
    - https://blog.cloudflare.com/pin-and-unpin-in-rust
    - the perils of pinning: https://lwn.net/Articles/907876/
    - https://fasterthanli.me/articles/pin-and-suffering
    - https://rust-lang.github.io/async-book/04_pinning/01_chapter.html
    - https://y86-dev.github.io/blog/safe-pinned-initialization/overview.html
    - https://github.com/y86-dev/pinned-init
    - https://github.com/y86-dev/rfcs/blob/field-projection/text/3318-field-pojection.md 
    - https://github.com/rust-lang/rfcs/blob/master/text/2349-pin.md
    - https://y86-dev.github.io/blog/return-value-optimization/placement-by-return.html
    - https://github.com/rust-lang/rfcs/pull/3318
    - https://kangrejos.com/Pinning%20in%20Rust.pdf
    - rust invariants: https://rustmagazine.org/issue-4/a-brief-discussion-on-invariants-in-rust/
- https://lwn.net/SubscriberLink/910762/e103310fccf871d3/
- https://blog.hedwing.dev/linux-kernel/intro_to_linux
- https://codeberg.org/vincenzopalazzo/linux-kernel-drivers
- A first look at Rust in the 6.1 kernel: https://lwn.net/Articles/910762/
- Rust in the 6.2 kernel: https://lwn.net/Articles/914458/
- https://hackmd.io/Yp2D8H_hRtuiGD2yYFZyLA
- https://research.nccgroup.com/2023/02/06/rustproofing-linux-part-1-4-leaking-addresses/
- rust kernel module: hello world https://wusyong.github.io/posts/rust-kernel-module-01/
- Linux kernel modules in safe Rust: https://github.com/fishinabarrel/linux-kernel-module-rust/
- Arc in RfL: https://hackmd.io/cuKNW7xxRzGsOUMiThs73w?view


Nice intro:
 - https://wusyong.github.io/posts/rust-kernel-module-00/
 - https://wusyong.github.io/posts/rust-kernel-module-01/
 - https://wusyong.github.io/posts/rust-kernel-module-02/
 - https://wusyong.github.io/posts/rust-kernel-module-03/


### interestig commits
- rust simple mutex: https://github.com/Rust-for-Linux/linux/commit/47e93d46eaca3a3648837eb6f5ae136812a28831
- rust mutex: https://github.com/Rust-for-Linux/linux/commit/be5ff7d29d5b4da2706cc5384f38d7e417bc26f5
- rust modules: https://github.com/wedsonaf/linux/commits/lf-session
- static assert: https://github.com/Rust-for-Linux/linux/pull/269
- https://github.com/Darksonn/linux/commit/8ef510d25f353c9c2e240e067e232b459e737a90
- https://github.com/Darksonn/linux/commit/ff03d355219af7a4156de81b77b2f423ff3d8a47
- rust: new api for initialization: https://github.com/Rust-for-Linux/linux/pull/909/files#diff-20432b0044e991d44b184c5bfa4cd92681e119758c93ba9fef5f4c629de688f1
- rust: rust: Introduce jiffies-based timer support : https://github.com/fbq/linux-rust/commit/c31a2a3ce7420b43bda2c6f1b43227baf0d13661
- Support for filesystem abstractions: https://github.com/Rust-for-Linux/linux/issues/1004
- RUST: add module_params macro https://github.com/Rust-for-Linux/linux/commit/62af8b3d3723cf12e932d2b9a8797a18bb9baa70
- RUST NVME: https://github.com/Rust-for-Linux/linux/compare/rust-next...metaspace:linux:nvme
- rust: crates in other kernel directories: https://lore.kernel.org/rust-for-linux/ca2cd71c-0aa1-4365-961c-c10737a9e9a6@gmail.com/T/#m44915f4a18ba9f2b033e186690d964ef8da3e965
- longest symbol: https://lore.kernel.org/rust-for-linux/20231105184010.49194-1-sergio.collado@gmail.com/
- longest symbol 2: https://lore.kernel.org/rust-for-linux/20231119180145.157455-1-sergio.collado@gmail.com/


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

- reference:  Mentorship Session: Setting Up an Environment for Writing Linux Kernel Modules in Rust: https://www.youtube.com/watch?v=tPs1uRqOnlk
- reference: https://rustypenguin.medium.com/setting-environment-for-writing-linux-kernel-modules-in-rust-78ea20242f75

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

