# Notes on how to build and embedded linux framework

 The principal components are: 
 
  - Toolchain
  - Bootloader
  - Kernel 
  - Rootfs
  
  Also using Qemu for emulation. 
  
  Reference: https://medium.com/@chienhaotan/compiling-and-running-a-minimal-kernel-with-busybox-bfc45a991017
  
  
 ## Toolchain
  
 The toolchain are the programs needed for compile, build, debug and analyse your code. It consists at least of: 
    - binutils: GNU assembler, linker ...
	- gcc: comopier
	- C library: libc
	- gdb: debugger
	
There are two types of toolchain
- native: run compiler on the target system.
- crosscompie: compile the code on a host machine, and run on target machine.

### Example for raspberry pi. 

You can download the toolchain from https://github.com/raspberrypi/tools

Settinig up the toolchain for crosscompiling

```shell
export ARCH=arm
export PATH=$PACH:/home/quemu/rpi/rpi/demo/tools-master/arm-bcm2708/arm-linux-gnueabihf/bin
export CROSS_COMPILE=arm-linux-gnueabihf-
arm-linux-gnueabihf-gcc hello.c -o helly_dyn
file hello_dyn

# run using built qemu
./qemu/sysroot/bin/qemu-arm -L /home/qemu/rpi/demo/tools-master/arm-bcm2708/arm-linux-gnueabihf/arm-linux-gnueabihf ./hello_dyn 

# the -L is the flag to declare where the libraries are
```

## Bootloader

### What happens when you press the start button?

Now that the core components are installed in the computer system, 
it is time to boot up the system. We can compare this to how we wake
 up in the morning and do a quick check to see if everything is 
 working. Only when everything is OK, do we get up and start our day. 
 The image below shows the steps a computer system goes through before
 it shows you a working interface (in the form of an Operating System).


#### Step 1: Press the Power Button

When we press the power button on our computer system, a signal is sent
 to the PSU (Power Supply Unit) to allow power to flow. 

#### Step 2: Firmware starts

A computer system contains firmware that allows all its components 
 to start up. The central system that manages this is called the Unified 
 Extensible Firmware Interface (UEFI). **Note: We will often see the term 
 BIOS mentioned instead of UEFI. BIOS does the same as UEFI, but has mainly
 been replaced by UEFI**

#### Step 3: Power-On Self Test

 One of the routines that the UEFI loads is the Power-On Self Test,
 which tests if every required component is present, configured correctly,
 and functioning.

#### Step 4: Select Boot Device

The computer system the UEFI holds an ordered list which prioritizes on which 
 device to look first for the boot up routine for the Operating System.

#### Step 5: Initiate Bootloader

 On the selected boot device, the bootloader is initiated. This bootloader 
 transfers the Operating System from the selected boot device to the Random Access
 Memory. Once the OS is transferred, the UEFI gives control over the different 
 components to the OS.
 
 
 In an embedded syste, it is usual that the bootloader, do the following minimal tasks:
   - Setup SDRAM controller
   - Setup serial port for debug
   - Setupe the boot media for loading the kernel and rootfs from it (like an SD card, NOR/NAND flash, Ethernet).
   - Setup filesystem driver (fat32, ext3/4, nfs)
   - Load kernel
   - Setup rootfs enviroment so the kernel can boot rootfs.
   
   There are two common bootloaders: 
    - for PC: GRUB, LILO (they are somewhat big, so that is why they are not suitable for embedded devices)
	- for embedded devices: Uboot, redboot
	
	Some references for Grug: 
	 - Brief Introduction to U-Boot - the Universal Bootloader: https://akhileshmoghe.github.io/_post/embedded/linux/bootloader/u-boot
	 - U-Boot documentation: https://docs.u-boot-project.org/en/latest/
	 - U-Boot repository: https://source.denx.de/u-boot/u-boot
	 - Is is available for several architecures
	 - Is both a first-stage and second-stage bootloader
	 - It is loaded by the system's ROM from a supported boot device, such as SD card
	   NOR/NAND flash ...
	 - In case size contrains U-Boot can be split in two stages: SPL (Secondary Program Loader) and U-Boot
	 
	 
	### Building U-Boot for Raspberry Pi:
	
	#### Checkout U-Boot source code
	 ```
	 $ git clone git://git.denx.de/u-boot.git
	 
	 $ git checkout v2017.03 // or the branch you need
	 
	 $ sudo apt-get install device-tree compiler
	 ```

	
	#### Install ARM compiler for cross compilation
	
	 For 32-bit
	
	 ```
	$ sudo apt update
	$ sudo apt install gcc-arm-linux-gnueabi
	$ export CROSS_COMPILE=arm-linux-gnueabi-
	 ```
	For 64-bit
	
	```
	$ sudo apt update
	$ sudo apt install gcc-aarch64-linux-gnu
	$ export CROSS_COMPILE=aarch64-linux-gnu- 
	```
	#### enviroment variables
	
	... this example is for the Rpi:
	```
		export ARCH=arm
		export PATH=$PATCH:/home/qemu/rpi/demo/tools-master7arm-bcm2708/arm-linux-gnueabihf/bin
		export CROSS_COMPILE=arm-linux-gnueabihf-
	
	```
	
	#### Complile the U-boot source code for Rpi
	
	Configs and DTBs for particular to boards:
	
	Watch out! 
	 - Every Raspberry Pi board and the Compute Modules comes with different DTBs and DTB Overlays.
	 - One config file from `/u-boot/configs/` folder corresponds to a particular DTB, as mentioned in config parameter: CONFIG_DEFAULT_DEVICE_TREE.
     - Look for different config files for various supported boards under /u-boot/configs/ directory in checked-out repository.
	 - There are different config files for different Raspberry Pi versions and for either 32/64-bit builds. Select appropriate config file.
	 
	 for Rpi 4, 32 bits:
	 ```
	 make rpi_4_32b_defconfig
	 ```
	
	 For Rpi 3, 64 bits:
		
	 ```
	 make rpi_4_32b_defconfig
	 ```
	 
	Compile U-boot source code for RPI: 
	```
    $ cd /u-boot/
    $ make ARCH=arm CROSS_COMILE=arm-linux-gnueabihf- dsitclean // first clean
	$ git checkout v2017.3 // checkout the needed branch
	$ sudo apt-get install device-tree install // this is needed
	$ export ARCH=arm
	$ export PATH=$PATCH:/home/qemu/rpi/demo/tools-master7arm-bcm2708/arm-linux-gnueabihf/bin
	$ export CROSS_COMPILE=arm-linux-gnueabihf-
	// generate the configuration
	$ make ARCH=arm CLORS_COMPILE=arm-linux-gnueabihf- <rpi_3_32b_defconfig> // choose the defconfig file you need in /u-boot/configs
	// the configuration will be written in the .config file 
	// compile
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabithf -j$(nproc)
	// u-boot.bin is the file that you will need to put in the SD card boot partition
	 ```
	 
	 This will create u-boot and `u-boot.bin` binaries in the `/u-boot/` folder.
	 
	 #### Complile the U-boot source code for Qemu
	 
	 ```
	 git clone git::/git.denx.de/u-boot.git
	 cd u-boot
	 git checkout v2014.07  //older version for the target versatilepb_config, this is a general board target
	 
	 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- versatilepb_config  //configure it
	 make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- j$(nproc) // build it
	 // the u-boot.bin should have been generated
	 
	 // to run u-boot in qemu:
	 
	 $ sudo qemu-system-arm \
	 -kernel u-boot/u-boot \
	 -m 256 \
	 -M versatilepb \
	 -no-reboot \
	 -nographic \
	 -net nic \
	 -net tap-ifname=vnet0,script=no,downscript=no
	 
	 ```
	 
	#### Verify U-Boot binaries
	
	```
    $ file u-boot
    u-boot: ELF 32-bit LSB shared object, ARM, EABI5 version 1 (SYSV), dynamically linked, with debug_info, not stripped
    
    $ file u-boot.bin 
    u-boot.bin: COM executable for DOS
	```
	
	#### Testing U-Boot on Rpi
	
	- Copy the compiled `u-boot.bin` binary to the Boot Partition of the Raspberry Pi SD card.
	- Modify Raspberry Pi boot flow to add u-boot bootloader stage as the last stage of normal RPi Boot process, before starting the kernel.
	  - Add `kernel=u-boot.bin` in the `config.txt` file and save this file.
	  - With this, the `start.elf` file loads the `u-boot.bin` instead of the kernel.
	  - Now, it’s u-boot bootloaders responsibility to properly load the Linux Kernel + DTBs in memory and start the kernel.
	  - Back-up the original `config.txt` file, before any edits
	  
	  ```
	  $ mount /dev/sdb1 /mnt/tmp
      $ cp u-boot.bin /mnt/tmp/
      $ echo 'kernel=u-boot.bin' > /mnt/tmp/config.txt
      $ umount /mnt/tmp
	  ```
	  
	  
	  ### tftp on U-Boot
	  
	  - Tftp is used by uboot to fetch files from a tftp server (i.e a host pc)
	  - previouslee is needed to set self ip(ipaddrs) and server ip(serverip) in u-boot using the commands:
	    - `setenv ipaddr 192.168.1.xxx`
		- `setenv serverip 121.168.1.yyy`
		- `setenv bootfile uImage`
	  - set the ip addres on host side
	    - `ifconfig vnet0 192.168.1.yyy`
	  - start the tftp in the host `tftp`, save the image in the tftp server. 
	  
	  
	  to convert the linux image into an file u-boot can understad, yo need the tools: 
	  ```
	  sudo apt install u-boot-tools
	  ```
	  
	  create the image, and save it in the tfpt location in the host
	  ```
	   mkimage -n 'Kernel Image' -A arm -0 linux -C nont -T kenrel -a 0x8000 e 0x8000 -d kernel-qemu-4.4.36 uImage
	  ```
	  
	  
	## Kernel
		
	
	Reference: https://gist.github.com/cGandom/23764ad5517c8ec1d7cd904b923ad863
	
	### Emulating Raspberry Pi 4 with Qemu

> **Just a quick update before we dive in:** what we're actually doing here is running Raspberry Pi OS (64-bit) on a QEMU virtual ARM setup. This isn't full-blown hardware emulation of the Raspberry Pi 4, but more about creating a virtual environment for the OS. It doesn't mimic all the specific hardware features of the Pi 4, but it's pretty useful and great for general testing. I turned to this solution mainly to extract a modified sysroot from the Raspberry Pi OS, something not readily available in other resources. For those looking into detailed emulation of the actual Raspberry Pi 4's hardware in QEMU, check out this link for the latest updates: https://gitlab.com/qemu-project/qemu/-/issues/1208.

Hope it helps! :D

Shortcomings: No GUI yet, only console.

### Steps

1. Download **Raspberry Pi OS (64-bit)** from [Raspberry Pi operating system images](https://www.raspberrypi.com/software/operating-systems/#raspberry-pi-os-64-bit). <br>Here we downloaded Raspberry Pi OS (64-bit) with desktop, Kernel version: 6.1, Debian version: 11 (bullseye), Release date: May 3rd 2023, named `2023-05-03-raspios-bullseye-arm64.img`. We put it in `/home/mydir`.
3. Install the required packages on your host system:
    ```shell
    $ # Cross compilers for arm64
    $ sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
    
    $ # Qemu itself
    $ sudo apt install qemu qemubuilder qemu-system-gui qemu-system-arm qemu-utils \
        qemu-system-data qemu-system
    ```
4. Build the Linux kernel for qemu arm64 (You can download the kernel from [Kernel.org](https://www.kernel.org/)):
    ```shell
    $ wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.34.tar.xz
    $ tar xvJf linux-6.1.34.tar.xz
    $ cd linux-6.1.34
    
    $ # create a .config file
    $ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make defconfig
    $ # Use the kvm_guest config as the base defconfig, which is suitable for qemu
    $ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make kvm_guest.config
    $ # Build the kernel
    $ ARCH=arm64 CROSS_COMPILE=/bin/aarch64-linux-gnu- make -j8

    $ cp arch/arm64/boot/Image /home/mydir
    ```
3. Mount the image for enabling ssh and configuring username and password:
    1. Get the correct offset value with the help of `fdisk` utility:
        ```shell
        $ fdisk -l 2023-05-03-raspios-bullseye-arm64.img
        Disk 2023-05-03-raspios-bullseye-arm64.img: 4.11 GiB, 4412407808 bytes, 8617984 sectors
        Units: sectors of 1 * 512 = 512 bytes
        Sector size (logical/physical): 512 bytes / 512 bytes
        I/O size (minimum/optimal): 512 bytes / 512 bytes
        Disklabel type: dos
        Disk identifier: 0x3e247b30
        Device                                 Boot  Start     End Sectors  Size Id Type
        2023-05-03-raspios-bullseye-arm64.img1        8192  532479  524288  256M  c W95 FAT32 (LBA)
        2023-05-03-raspios-bullseye-arm64.img2      532480 8617983 8085504  3.9G 83 Linux
        ```
        As we can see, we have two partitions inside the downloaded image. The first device (partition) is the bootable partition, and the second one is the root filesystem. The first partition is what will be mounted as `/boot` in Raspberry Pi, and this is where we'll need to create some files.
        <br>Obtain the correct **offset** of the first device by multiplying the start of the first partition (here 8192) by the sector size (here 512).
Here it will be calculated as **8192 * 512 = 4194304**
    2. Mount the image in `/mnt/rpi` directory:
        ```shell
        $ sudo mkdir /mnt/rpi
        $ sudo mount -o loop,offset=4194304 2023-05-03-raspios-bullseye-arm64.img /mnt/rpi
        ```
    3. Create a file named `ssh` to enable ssh:
        ```shell
        $ cd /mnt/rpi
        $ sudo touch ssh
        ```
    4. Additionally, create a file named `userconf.txt` in the same directory and put your desired username and password there, like `<username>:<hashed-password>` (might be better to leave the username as `pi`). This will be your default credentials:
        ```shell
        $ openssl passwd -6                                     # Generate the <hashed-password>
        $ echo 'pi:<hashed-password>' | sudo tee userconf.txt   # Put them inside `userconf.txt`
        ```
    5. Finally, unmount the image:
        ```shell
        $ sudo umount /mnt/rpi
        ```
4. Run qemu emulator:
    ```shell
    $ cd /home/mydir
    $ qemu-system-aarch64 -machine virt -cpu cortex-a72 -smp 6 -m 4G \
        -kernel Image -append "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0" \
        -drive format=raw,file=2023-05-03-raspios-bullseye-arm64.img,if=none,id=hd0,cache=writeback \
        -device virtio-blk,drive=hd0,bootindex=0 \
        -netdev user,id=mynet,hostfwd=tcp::2222-:22 \
        -device virtio-net-pci,netdev=mynet \
        -monitor telnet:127.0.0.1:5555,server,nowait
    ```
    This machine will be able to access the internet.
5. After the machine is completely booted up, you can login to it from your computer by using ssh and the username and password you specified:
    ```shell
    $ ssh -l pi localhost -p 2222
    ```
6. Done!

### Troubleshooting

* If you had any problem with connecting to internet, it might be because of bad DNS configurations, and you should consider adding `nameserver 8.8.8.8` to top of the file `/etc/resolv.conf` in the machine. 
* You can access the qemu monitor console with:
    ```shell
    $ telnet localhost 5555
    ```
	
	
 ## Root Filesystem
 
 ### Busy Box
 
  Busy box is an utility that proivdes lots fo linux utilities in one executable.

  Reference: https://busybox.net/about.html  
  
  Reference: https://www.reddit.com/r/linux/comments/1p4tb9/what_is_busybox_and_what_is_it_used_for_in_the/
  
  BusyBox is an implementation of a typical set of UNIX userland tools (including a shell, 
  ash, and a text editor, vi), as well as a complete bootstrapping toolchain (init etc.), 
  all compiled into a single executable. The trick is that this executable looks at the
  name by which it got called to act as the desired program: e.g.,
  if you call the busybox executable through a symlink called `ls`, it will act like `ls;
  call the same executable through a different symlink named `grep`, and it acts as `grep`.
  This is done to keep the total size of the userland tools at a minimum: all the shared 
  functionality between these tools is linked into this one binary, removing the need 
  for duplication.

  This is useful in a wide variety of situations, but mostly when disk space is a concern.
  A typical busybox binary is under 700 kB in size, yet provides everything you need
  (except a kernel) to run a complete UNIX system. Common use cases include:
   - embedded devices
   - mobile devices
   - installers (busybox allows running an entire temporary OS in memory, e.g. on a ramdisk)
   - running a mini-OS to bootstrap the real one (I think this is often done with LiveCDs and the like)
   - tiny distros such as Damn Small Linux
   - experiments like running a complete Linux system in a VM implemented in JavaScript and running in your browser
   
   
   ### Git clone and compile Busybox
   
   reference: https://medium.com/@chienhaotan/compiling-and-running-a-minimal-kernel-with-busybox-bfc45a991017
   
   ```shell
    $  cd .. # don't do stuff in the linux directory, git will be confused
	$ git clone --depth=1 https://github.com/mirror/busybox.git && cd busybox
	$ make defconfig 
	$ vi .config # set CONFIG_STATIC=y
	$ make -j$(nproc)
	$ make CONFIG_PREFIX=$PWD/BUSYBOX install
	$ ls BUSYBOX 
    bin  linuxrc  sbin  usr
   ```
   
   If you are cross-compiling, then add the usual stuff
   
   ```shell
   export ARCH=arm
   export PATH=$PACH:/home/quemu/rpi/rpi/demo/tools-master/arm-bcm2708/arm-linux-gnueabihf/bin
   export CROSS_COMPILE=arm-linux-gnueabihf-
   make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- defconfig
   make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig # add or remove needed packages...
   
   # Check the generated `.config` file. 
   
   make ARCH=arm CROSS_COMPÑILE=arm-lilnux-gnueabihf-  CONFIG_PREFIX=$PWD/BUSYBOX install
   ```
   
   
   
   Then we make out `initrd` with busybox
   
   ```shell
	$ cd ../linux # return back to linux directory
	$ mkdir initrd && cd initrd # like vfs (from previously), this will house our new initrd
	$ mkdir etc proc sys
	$ cat << EOF > init                              
	#!/bin/sh
						   
	mount -t proc proc /proc
	mount -t sysfs none /sys
													  
	# https://busybox.net/FAQ.html#job_control
													  
	mknod /dev/ttyS0 c 4 64
	setsid sh -c 'exec sh </dev/ttyS0 >/dev/ttyS0 2>&1'
	EOF                                                   
	$ chmod +x init
   ```
   
   The above init shell script will be our entrypoint
   
   ```shell
   $ cp ../../busybox/BUSYBOX/* . # copy over our compiled busybox utilities
   $ find . | cpio -o -H newc | gzip > root.cpio.gz # package it
   ```
   
   Basically, `init` will call our busybox utilities! Internally, /bin/ls is a symlink to /bin/busybox ls
   
   
   ### DropBear
   
   It is a small ssh server and client: https://github.com/mkj/dropbear
   
   get the ddorpbear tal file and extract it: 
   
   ```shell
   wget http://mat.ucc.assn.au/dropbear/releases/dropbear-0.53.1.tar.gz
   tar -xvf dropbear-0.53.1.tar.gz
   cd dropbear-0.53.1
   
   #Configure
   ./configure --prefix=$PWD/../rootfs/ --host=arm-linux-gnueabihf --disable-zlib CC=arm-linux-gnueabihf-gcc LDFLAGS="-Wl,--gc-sections" CFLAGS="-ffunction-sections -fdata-sections -0s"
   
   #Build 
   export ARCH=arm
   export PATH=$PACH:/home/quemu/rpi/rpi/demo/tools-master/arm-bcm2708/arm-linux-gnueabihf/bin
   export CROSS_COMPILE=arm-linux-gnueabihf-
   
   make PROGRAMS="dropbear dbclient dropbearkey dropbearconvert scp" MULTI=1 strip
   
   #Install
   sudo make install
   
   #check into  /rootfs/bin/ if it has been added properly
   ``` 
   
   ### Setup Rootfs
   
   Create the rdinit rootfs
   
   ```shell
   cd rootfs && find. | cpio --quiet -o H newc > ../rootfs.cpio && cd -
   ```
   
   ```
   #strip the library to reuce the size
   arm-linux-gnueabihf-strirp lib/
   
   #Create the directory structure
   mkdir dev etc etc/dropbear etc/initd mnt opt proc root sys tmp var var/log var/www
   
   ## minimal needed configuration for /etc
   #fstab is used to load the 
   # create "etc/fstab" cotianeing the following
   LABEL=/	    /    		tmpfs    defaults         0  0
   none  		/dev/pts  	devpts 	 gid=5,mode=620   0  0
   none         /proc       proc     defaults         0  0
   none         /tmp        tmpfs    defaults         0  0
   -------------------------------------
   
   #Create "etc/inittab"
   ::sysinit:/etc/init.d/rcS
   
   
   # /bin/ash
   # 
   # start an 'askfirst' shell on the serial port
   console::askfirst:-/bin/ash
   
   #stuff to do when restarting the init process
   ::restart:/sbin/init
   
   #stuff to do before rebooting
   ::ctrlaltdel:/sbin/reboot
   ::shutdown:/bint/umount -a -r 
   ::shutdown:/sbin/swapoff -a 
   
   #create 'etc/init.d/rcS'
   
   #!/bin/sh
   echo "Starting rcS..."
   
   echo "++ Mounting filesystem"
   mount -t proc none /porc
   mount -t sysfs none /sys
   mount -t tmpfs none /tmp
   
   echo "++ Setting up mdev"
   
   echo /shin/mdev > /proc/sys/kernel/hotplug
   mdev -same
   
   mkdir -p /dev/pts
   mkdir -p /dev/i2c
   mount -t devpts devpts /dev/pts
   
   echo "++ Starting telnet daemon"
   telnetd -l /bin/shared
   
   echo "++ Starting http daemon"
   httpd -h /var/www
   
   echo "++ Starting ftp daemon"
   tcpsvd 0:21 ftpd ftdp -w /&
   
   echo "++ Starting dropbear (ssh) daemon"
   ln -s /sbin/dropbear /usr/bin/scp
   ln -s /bin/dbclient  /usr/bin/dbclient
   
   #for the client to request a connection, the target board needs to run the dropbear server daemon
   #before taht, ssh key shoud be generated
   #for the target board the deault location for the kesy is the /etc/dropbear directory
   #create the keys using the dropbearkey command:
   
   dropbearkey -t rsa -f /etc/dropbear/dropbear_rsa_host_key
   dropbearkey -t dss -f /etc/dropbear/dropbear_dss_host_key
   
   #change the permission of dropebar
   chmod 700 /etc/dropbear
   
   #start dopebar
   dropbear
   
   echo "rcS Complete"
   
   #set the appropiate permisions on "etc/init.d/rcS"
   
   bash> chmod 755 eetc/init.d/rcS
   bash> sudo chown root:root etc/init.d/rcS
   
   #create rdinit rootfs
   cd rootfs && find . | cpio --quiet 
   
   
   ```
   
   
   
   
   # Build systems 
   
   1-> Buildroot

   2-> Yocto
   
   
   ## Buildroot
   
   Buildroot is a simple, efficient and easy-to-use tool to generate embedded Linux systems through cross-compilation. It is based on menuconfig configuration. Here based on menuconfig, xconfig and some other we can select or remove packages to build the images.

Reference:-

https://buildroot.org/
   
   Host machine:- Ubuntu-20.04 x64 bit

```shell
sudo apt install sed make binutils gcc g++ bash patch gzip bzip2 perl tar cpio python unzip rsync wget libncurses-dev
git clone git://git.buildroot.net/buildroot
```

or

```shell
git clone https://git.buildroot.net/git/buildroot.git( if git is blocked by your company)
```

### Buildroot common commands

make help - To get various commands available by buildroot

clean - delete all files created by build

distclean - delete all non-source files (including .config) plus dl folder too.

uboot-menuconfig - Run uboot menuconfig

linux-menuconfig - Run linux menuconfig

busybox-menuconfig - Run busybox menuconfig

Build:

all - make world

toolchain - Build toolchain

sdk - Build relocatable SDK

Configuration:

menuconfig - interactive curses-based configuration

make V = 1 - For verbose during building

### Building of an ARM based qemu


First of all do the prerequisite.

Then go to the buildroot cloned directory.

#Configure for the cortex_a9 based ARM qemu target

make qemu_arm_vexpress_defconfig

#Do menuconfig to add or remove any packages(It is just like busybox menuconfig which we have already overed in rootfs section)

make menuconfig

#Build the complete target

make V=1

#Build will be done in output and final images will be kept in output/images/

Note:- This process may take up-to 4 to 5 hours based on internet speed and host machine speed.


### Running of qemu build images for cortex_a9 target

Run the qemu image using command

```shell
output/images/start-qemu.sh
```

Note:- To understand what is behind the scene to run qemu image, open the file using command

```shell
cat output/images/start-qemu.sh
```


## Yocto

The Yocto Project. It's not an embedded Linux Distribution, It creates a custom one for you.

The Yocto Project (YP) is an open source collaboration project that helps developers create custom Linux-based systems regardless of the hardware architecture.

The project provides a flexible set of tools and a space where embedded developers worldwide can share technologies, software stacks, configurations, and best practices that can be used to create tailored Linux images for embedded and IOT devices, or anywhere a customized Linux OS is needed.

Reference:-

https://www.yoctoproject.org/

### prerequisites to build Yocto

Host machine:- Ubuntu-20.04

```shell
sudo apt-get install gawk wget git diffstat unzip texinfo gcc build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 xterm python3-subunit mesa-common-dev

git clone git://git.yoctoproject.org/poky

cd poky

git checkout dunfell
```

### Yocto common commands

```shell
#Build the console based core-image to boot

bitbake core-image-minimal

#Build the GUI based images with more utils to boot

bitbake core-image-sato

#Build a toolchain for standalone development like build you own utils, bootloader, kernel and so on.

bitbake meta-toolchain
```
Note:-

After build is over, toolchain script will be tmp/deploy/sdk/*-toolchain*.sh. You need to extract the toolchain after running the *-toolchain*.sh script.

To use the toolchain, just soure the toolchain_directory using command:- source toolchain_dir

```shell
# Build a complete SDK

bitbake -c populate_sdk core-image-minimal/core-image-sato
```


### Building of ARM based qemu target

First complete the prerequisite

Then, go to the poky directory.

```shell
#Setup the yocto environment

source oe-init-build-env
```


#After that you will be propmpted with the below message and redirected to build directory

You can now run 'bitbake <target>'

Common targets are:
```
core-image-minimal

core-image-sato

meta-toolchain

meta-ide-support
```

```
#From the build directory, in file conf/local.conf enable the below config after removing # and disable other machine configuration(MACHINE ??= "qemux86-64") after adding #

MACHINE ?= "qemuarm"
```

```
#Now if you want to build the console based core-image to boot, run the below command

bitbake core-image-minimal

#Otherwise for building the GUI based images with more utils to boot, run the below command

bitbake core-image-sato
```


Note:- This process may take upto 4 to 5 hours based on internet speed and host machine speed

### Running of qemu build images

To run the build images, use the below command
```
runqemu
```
