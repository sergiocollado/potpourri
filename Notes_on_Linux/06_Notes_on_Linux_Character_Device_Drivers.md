References:
 - Intro to character device drivers: https://sysprog21.github.io/lkmpg/#character-device-drivers
 - Linux Kernel Programming Part 2 - Char Device Drivers and Kernel Synchronization:
    - https://github.com/PacktPublishing/Linux-Kernel-Programming/blob/master/Linux-Kernel-Programming-(Part-2)/Linux%20Kernel%20Programming%20Part%202%20-%20Char%20Device%20Drivers%20and%20Kernel%20Synchronization_eBook.pdf
    - https://github.com/PacktPublishing/Linux-Kernel-Programming-Part-2
 - Drivers implementer's API: https://docs.kernel.org/driver-api/index.html
 - Linux kernel documentation - device drivers: https://docs.kernel.org/driver-api/driver-model/driver.html
 - The Linux device driver: https://docs.kernel.org/driver-api/driver-model/overview.html
 - https://sysprog21.github.io/lkmpg/#character-device-drivers
 - Linux Device Model LDM: https://linux-kernel-labs.github.io/refs/heads/master/labs/device_model.html
 - Understanding the structure of a Linux Device Driver: https://youtu.be/pIUTaMKq0Xc
 - Let's code a Linux Driver: https://www.youtube.com/watch?v=x1Y203vH-Dc&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
 - Linux kernel labs - character drivers: https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html
 - Introduction to Linux device drivers: https://youtu.be/fQkObOxVTVo
 - Introduction to Linux device drivers part 2: https://youtu.be/n1wHgGmDXwE
 - Fast bit: Linux device driver programming: https://www.youtube.com/watch?v=YR_vYTh8CmY&list=PLERTijJOmYrAtfl5U_TAbCOisCNb7XEbb
 - Linux device drivers: https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-part-1-introduction/
 - Linux device drivers tutorial: https://www.youtube.com/watch?v=BRVGchs9UUQ&list=PLArwqFvBIlwHq8WMKgsXSQdqIvymrEz9k&index=2
 - Linux VFS: https://www.kernel.org/doc/html/latest/filesystems/#core-vfs-documentation


## Some interesting directories

### /proc/devices

This file displays the various character and block devices currently configured 

The output from `/proc/devices` includes the **major number** and name of the device

Output is broken into two major sections: 
	- Character devices
	- Block devices

```
sergio@laptop:~$ cat /proc/devices
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
  6 lp
  7 vcs
 10 misc
 13 input
 21 sg
 29 fb
 81 video4linux
 89 i2c
 99 ppdev
108 ppp
116 alsa
128 ptm
136 pts
180 usb
189 usb_device
202 cpu/msr
204 ttyMAX
216 rfcomm
226 drm
234 kfd
235 aux
236 cec
237 lirc
238 media
239 hidraw
240 nvme-generic
241 nvme
242 ttyDBC
243 bsg
244 watchdog
245 remoteproc
246 ptp
247 pps
248 rtc
249 dma_heap
250 dax
251 dimmctl
252 ndctl
253 tpm
254 gpiochip
261 accel

Block devices:
  7 loop
  8 sd
  9 md
 11 sr
 65 sd
 66 sd
 67 sd
 68 sd
 69 sd
 70 sd
 71 sd
128 sd
129 sd
130 sd
131 sd
132 sd
133 sd
134 sd
135 sd
253 device-mapper
254 mdp
259 blkext

```
### The /dev directory

- reference: https://linux.die.net/sag/dev-fs.html

Char devices are accessed through device files, usually located in `/dev`.

The `/dev` directory contains the special device files for all the devices.

The canonical list of the prefixes used in Linux can be found in the documentation at: https://www.kernel.org/doc/html/latest/admin-guide/devices.html

```
$ ls /dev
autofs           loop11  loop53        tty11  tty53      ttyS8
block            loop12  loop54        tty12  tty54      ttyS9
btrfs-control    loop13  loop55        tty13  tty55      udmabuf
bus              loop14  loop56        tty14  tty56      uhid
char             loop15  loop57        tty15  tty57      uinput
console          loop16  loop58        tty16  tty58      urandom
core             loop17  loop59        tty17  tty59      usb
cpu              loop18  loop6         tty18  tty6       userfaultfd
cpu_dma_latency  loop19  loop7         tty19  tty60      userio
cuse             loop2   loop8         tty2   tty61      v4l
disk             loop20  loop9         tty20  tty62      vboxdrv
dma_heap         loop21  loop-control  tty21  tty63      vboxdrvu
dri              loop22  mapper        tty22  tty7       vboxnetctl
drm_dp_aux0      loop23  mcelog        tty23  tty8       vboxusb
drm_dp_aux1      loop24  media0        tty24  tty9       vcs
ecryptfs         loop25  mem           tty25  ttyprintk  vcs1
fb0              loop26  mqueue        tty26  ttyS0      vcs2
fd               loop27  net           tty27  ttyS1      vcs3
full             loop28  ng0n1         tty28  ttyS10     vcs4
fuse             loop29  null          tty29  ttyS11     vcs5
gpiochip0        loop3   nvme0         tty3   ttyS12     vcs6
hidraw0          loop30  nvme0n1       tty30  ttyS13     vcsa
hidraw1          loop31  nvme0n1p1     tty31  ttyS14     vcsa1
hidraw2          loop32  nvme0n1p2     tty32  ttyS15     vcsa2
hidraw3          loop33  nvram         tty33  ttyS16     vcsa3
hpet             loop34  port          tty34  ttyS17     vcsa4
hugepages        loop35  ppp           tty35  ttyS18     vcsa5
hwrng            loop36  psaux         tty36  ttyS19     vcsa6
i2c-0            loop37  ptmx          tty37  ttyS2      vcsu
i2c-1            loop38  pts           tty38  ttyS20     vcsu1
i2c-2            loop39  random        tty39  ttyS21     vcsu2
i2c-3            loop4   rfkill        tty4   ttyS22     vcsu3
i2c-4            loop40  rtc           tty40  ttyS23     vcsu4
i2c-5            loop41  rtc0          tty41  ttyS24     vcsu5
i2c-6            loop42  shm           tty42  ttyS25     vcsu6
i2c-7            loop43  snapshot      tty43  ttyS26     vfio
i2c-8            loop44  snd           tty44  ttyS27     vga_arbiter
initctl          loop45  stderr        tty45  ttyS28     vhci
input            loop46  stdin         tty46  ttyS29     vhost-net
kfd              loop47  stdout        tty47  ttyS3      vhost-vsock
kmsg             loop48  tpm0          tty48  ttyS30     video0
kvm              loop49  tpmrm0        tty49  ttyS31     video1
log              loop5   tty           tty5   ttyS4      zero
loop0            loop50  tty0          tty50  ttyS5      zfs
loop1            loop51  tty1          tty51  ttyS6
loop10           loop52  tty10         tty52  ttyS7
```

The `/dev` directory contains the special device files for all the devices. The device files are created during installation, and later with the /dev/MAKEDEV script. The /dev/MAKEDEV.local is a script written by the system administrator that creates local-only device files or links (i.e. those that are not part of the standard MAKEDEV, such as device files for some non-standard device driver).

This list which follows is by no means exhaustive or as detailed as it could be. Many of these device files will need support compiled into your kernel for the hardware. Read the kernel documentation to find details of any particular device.

#### /dev/fb0
The first framebuffer device. A framebuffer is an abstraction layer between software and graphics hardware. This means that applications do not need to know about what kind of hardware you have but merely how to communicate with the framebuffer driver's API (Application Programming Interface) which is well defined and standardized. The framebuffer is a character device and is on major node 29 and minor 0.

#### /dev/hda
/dev/hda is the master IDE drive on the primary IDE controller. /dev/hdb the slave drive on the primary controller. /dev/hdc , and /dev/hdd are the master and slave devices on the secondary controller respectively. Each disk is divided into partitions. Partitions 1-4 are primary partitions and partitions 5 and above are logical partitions inside extended partitions. Therefore the device file which references each partition is made up of several parts. For example /dev/hdc9 references partition 9 (a logical partition inside an extended partition type) on the master IDE drive on the secondary IDE controller. The major and minor node numbers are somewhat complex. For the first IDE controller all partitions are block devices on major node 3. The master drive hda is at minor 0 and the slave drive hdb is at minor 64. For each partition inside the drive add the partition number to the minor minor node number for the drive. For example /dev/hdb5 is major 3, minor 69 (64 + 5 = 69). Drives on the secondary interface are handled the same way, but with major node 22.

#### /dev/ht0
The first IDE tape drive. Subsequent drives are numbered ht1 etc. They are character devices on major node 37 and start at minor node 0 for ht0 1 for ht1 etc.

#### /dev/js0
The first analogue joystick. Subsequent joysticks are numbered js1, js2 etc. Digital joysticks are called djs0, djs1 and so on. They are character devices on major node 15. The analogue joysticks start at minor node 0 and go up to 127 (more than enough for even the most fanatic gamer). Digital joysticks start at minor node 128.

#### /dev/loop0
The first loopback device. Loopback devices are used for mounting filesystems which are not located on other block devices such as disks. For example if you wish to mount an iso9660 CD ROM image without burning it to CD then you need to use a loopback device to do so. This is usually transparent to the user and is handled by the mount command. Refer to the manual pages for mount and losetup. The loopback devices are block devices on major node 7 and with minor nodes starting at 0 and numbered sequentially.

#### /dev/md0
First metadisk group. Metadisks are related to RAID (Redundant Array of Independent Disks) devices. Please refer to the most current RAID HOWTO at the LDP for more details. This can be found at http://www.tldp.org/HOWTO/Software-RAID-HOWTO.html. Metadisk devices are block devices on major node 9 with minor nodes starting at 0 and numbered sequentially.

#### /dev/mixer
This is part of the OSS (Open Sound System) driver. Refer to the OSS documentation at http://www.opensound.com for more details. It is a character device on major node 14, minor node 0.

#### /dev/null
The bit bucket. A black hole where you can send data for it never to be seen again. Anything sent to /dev/null will disappear. This can be useful if, for example, you wish to run a command but not have any feedback appear on the terminal. It is a character device on major node 1 and minor node 3.

#### /dev/pda
Parallel port IDE disks. These are named similarly to disks on the internal IDE controllers (/dev/hd*). They are block devices on major node 45. Minor nodes need slightly more explanation here. The first device is /dev/pda and it is on minor node 0. Partitions on this device are found by adding the partition number to the minor number for the device. Each device is limited to 15 partitions each rather than 63 (the limit for internal IDE disks). /dev/pdb minor nodes start at 16, /dev/pdc at 32 and /dev/pdd at 48. So for example the minor node number for /dev/pdc6 would be 38 (32 + 6 = 38). This scheme limits you to 4 parallel disks of 15 partitions each.

#### /dev/random or /dev/urandom
These are kernel random number generators. /dev/random is a non-deterministic generator which means that the value of the next number cannot be guessed from the preceding ones. It uses the entropy of the system hardware to generate numbers. When it has no more entropy to use then it must wait until it has collected more before it will allow any more numbers to be read from it. /dev/urandom works similarly. Initially it also uses the entropy of the system hardware, but when there is no more entropy to use it will continue to return numbers using a pseudo random number generating formula. This is considered to be less secure for vital purposes such as cryptographic key pair generation. If security is your overriding concern then use /dev/random, if speed is more important then /dev/urandom works fine. They are character devices on major node 1 with minor nodes 8 for /dev/random and 9 for /dev/urandom.

#### /dev/sda
The first SCSI drive on the first SCSI bus. The following drives are named similar to IDE drives. /dev/sdb is the second SCSI drive, /dev/sdc is the third SCSI drive, and so forth.

#### /dev/ttyS0
The first serial port. Many times this it the port used to connect an external modem to your system.

#### /dev/zero
This is a simple way of getting many 0s. Every time you read from this device it will return 0. This can be useful sometimes, for example when you want a file of fixed length but don't really care what it contains. It is a character device on major node 1 and minor node 5.

### /sys/class file

 - reference: https://man7.org/linux/man-pages/man5/sysfs.5.html
 - reference: https://medium.com/@The_CodeConductor/lets-understand-sys-class-in-linux-efc38a2b4900

>`/sys/class` 
>   This subdirectory contains a single layer of further
>              subdirectories for each of the device classes that have
>              been registered on the system (e.g., terminals, network
>              devices, block devices, graphics devices, sound devices,
>              and so on).  Inside each of these subdirectories are
>              symbolic links for each of the devices in this class.
>              These symbolic links refer to entries in the /sys/devices
>              directory.

`/sys/class` is a directory in the Linux filesystem that provides a way to interact with the kernel and access information about various classes of devices and subsystems.

It is part of the `sysfs` virtual filesystem, which exposes information about the kernel, devices, and their attributes.

In the context of `/sys/class`, the directory contains subdirectories, each corresponding to a particular class of devices or subsystems. Each class directory contains information and control files that allow users and applications to query and modify attributes of devices belonging to that class.

```
$ ls /sys/class
accel          drm             lirc            ppdev         sound
ata_device     drm_dp_aux_dev  mdio_bus        ppp           spi_master
ata_link       extcon          mem             pps           spi_slave
ata_port       firmware        misc            printer       thermal
backlight      gpio            mmc_host        ptp           tpm
bdi            graphics        msr             pwm           tpmrm
block          hidraw          nd              rapidio_port  tty
bluetooth      hwmon           net             rc            usbmisc
bsg            i2c-adapter     nvme            regulator     usb_role
devcoredump    i2c-dev         nvme-generic    remoteproc    vc
devfreq        ieee80211       nvme-subsystem  rfkill        video4linux
devfreq-event  input           pci_bus         rtc           virtio-ports
devlink        intel_scu_ipc   pci_epc         scsi_device   vtconsole
dma            iommu           phy             scsi_disk     wakeup
dma_heap       kfd             powercap        scsi_generic  watchdog
dmi            leds            power_supply    scsi_host     wmi_bus
$ tree /sys/class
```

 - `/sys/class/block`: Contains information about block devices, such as hard drives and partitions.

 - `/sys/class/net`: Contains network device information. You can find details about network interfaces (like eth0, wlan0, etc.) in this directory.

 - `/sys/class/gpio`: Provides access to GPIO pins on the system.

 - `/sys/class/power_supply`: Contains information about power supplies, such as batteries or AC adapters.

When you navigate into one of these directories, you will find files that can be read to obtain information about the devices or written to modify their behavior. This interface is particularly useful for interacting with devices and kernel features at the user level.

The `/sys/class` hierarchy provides a standardized way to access this information in a Linux system.

Reading Information:Users can read information from various files within these class directories. For example, reading from files in /sys/class/net/eth0 might provide details about the network interface.

Writing and Configuration: Certain files allow users to modify the behavior or configuration of devices. For instance, changing the value of a file in /sys/class/gpio/gpiochip0 may control the state of a GPIO pin.

The `/sys/class` directory in Linux plays a vital role in providing a standardized interface for users and applications to interact with various device classes.



## Introduction

In Linux everything is considered to be a file so devices are also considered to be a file.

In UNIX, hardware devices are accessed by the user through special device files.

These files are grouped into the `/dev` directory, and system calls `open`, `read`, `write`, `close`, `lseek`, `mmap` etc. are redirected by the operating system to the device driver associated with the physical device.

In the UNIX world there are two categories of device files and thus device drivers: 
 - **character**
 - **block**

This division is done 
 - by the speed, 
 - volume and 
 - way of organizing the data to be transferred from the device to the system and vice versa.

In the first category, there are slow devices, which manage a small amount of data, and access to data does not require frequent seek queries. Examples are devices such as keyboard, mouse, serial ports, sound card, joystick. In general, operations with these devices (read, write) are performed sequentially byte by byte.

The second category includes devices where data volume is large, data is **organized on blocks**, and search is common. Examples of devices that fall into this category are hard drives, cdroms, ram disks, magnetic tape drives.For these devices, reading and writing is done at the data block level.

For the two types of device drivers, the Linux kernel offers different APIs.

If for **character devices** system calls go directly to device drivers, in case of **block devices**, the drivers do not work directly with system calls. 

In the case of **block devices**, communication between the user-space and the block device driver is mediated by the __**file management**__ subsystem and the block device subsystem. 


### Character Device Driver

A character device typically transfers data to and from a user application — they behave like pipes or serial ports, instantly reading or writing the byte data in a character-by-character stream.

#### Command to list all the character device driver
```
$ls -l /dev/ | grep "^c"
```

#### Command to list all the block device driver

```
$ls -l /dev/ | grep "^b"
```

#### Steps in creating a character driver

1. Allocate a device number dynamically or statically (dev_t)
2. Initializing the character device with its file operations (struct cdev, struct file_operations)
3. Registering the character device with Linux Kernel (cdev_add)

### Major and Minor Number

Connection between the **application** and the **device file** is based on the **name of the device file**.

However the connection between the **device file** and the **device driver** is based on the **number of the device file**, not the name.

A device ID/number consists of two parts
 -	Major Number : identifies the device type (IDE disk, SCSI disk, serial port, etc.)
	- Minor Number : identifies the device (first disk, second serial port, etc.)

Most times, the major identifies the driver, while the minor identifies each physical device served by the driver.

```
ls -l /dev/ttyS*
crw-rw---- 1 root dialout 4, 64 Apr 12 23:18 /dev/ttyS0
crw-rw---- 1 root dialout 4, 65 Apr 12 23:18 /dev/ttyS1
crw-rw---- 1 root dialout 4, 74 Apr 12 23:18 /dev/ttyS10
crw-rw---- 1 root dialout 4, 75 Apr 12 23:18 /dev/ttyS11
crw-rw---- 1 root dialout 4, 76 Apr 12 23:18 /dev/ttyS12
crw-rw---- 1 root dialout 4, 77 Apr 12 23:18 /dev/ttyS13
crw-rw---- 1 root dialout 4, 78 Apr 12 23:18 /dev/ttyS14
```

The special character files are identified by the `c` character in the first column of the command output, and the block type by the character `b`

In columns 5 and 6 of the result you can see the major, respectively the minor for each device.

Certain major identifiers are statically assigned to devices (in the Documentation/admin-guide/devices.txt file from the kernel sources).

reference: https://docs.kernel.org/admin-guide/devices.html

When choosing the identifier for a new device, you can use two methods
	- **static** (choose a number that does not seem to be used already)
	- **dynamic** (kernel will give you a device number)

#### Data Type

A device ID/number is represented using the type **dev_t**.

Defined at: https://elixir.bootlin.com/linux/latest/source/include/linux/types.h#L18

```C
typedef u32 __kernel_dev_t;
```

12 bit major number + 20 bit Minor number =32 bit dev_t

To obtain the major or minor parts of a dev_t, use:

```
	MAJOR(dev_t dev);
	MINOR(dev_t dev);
```

To create a device number from major and minor number:

```
     MKDEV(int major, int minor);
```
Header File: linux/kdev_t.h

 - reference: https://elixir.bootlin.com/linux/v6.7.3/source/include/linux/kdev_t.h#L12

```
#define MINORBITS	20
#define MINORMASK	((1U << MINORBITS) - 1)

#define MAJOR(dev)	((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)	((unsigned int) ((dev) & MINORMASK))
#define MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))
```

#### Example:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
	dev_t devicenumber;

	devicenumber = 10;
	printk("Major Number :%d\n", MAJOR(devicenumber));
	printk("Minor Number :%d\n", MINOR(devicenumber));

	devicenumber = MKDEV(120, 30);
 printk("Device Number: %u\n", devicenumber);
	printk("Major Number :%d\n", MAJOR(devicenumber));
	printk("Minor Number :%d\n", MINOR(devicenumber));

	return 0;
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### Allocating Major and Minor Number

Two ways:

1. Static
2. Dynamic

### Difference between static and dynamic method


Static method is only really useful if you know in advance which major number you want to start with. With Static method , you tell the kernel what device numbers you want (the start major/minor number and count) and it either gives them to you or not (depending on availability).

With Dynamic method, you tell the kernel how many device numbers you need (the starting minor number and count) and it will find a starting major number for you, if one is available, of course.
Partially to avoid conflict with other device drivers, it’s considered preferable to use the Dynamic method function, which will dynamically allocate the device numbers for you.


### static assignment and unallocation of device identifiers:

```
int register_chrdev_region (dev_t from,	unsigned count,	const char *name);
```

Description: register a range of device numbers

Arguments:
 - from : the first in the desired range of device numbers; must include the major number.
 - count: the number of consecutive device numbers required
 - name: the name of the device or driver. This will appear in /proc/devices

Return Value:
 - zero on success, a negative error code on failure.

```
void unregister_chrdev_region(dev_t from, unsigned int count);
```

Header File: <linux/fs.h>

Example:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

int major_number = 120;
int minor_number = 0;
char *device_name = "mychardev";
int count = 1;
dev_t devicenumber;

module_param(major_number, int, 0);
module_param(minor_number, int, 0);
module_param(count, int, 0);
module_param(device_name, charp, 0);

MODULE_LICENSE("GPL");
static int test_hello_init(void)
{

	devicenumber = MKDEV(major_number, minor_number);
	printk("Major Number :%d\n", MAJOR(devicenumber));
	printk("Minor Number :%d\n", MINOR(devicenumber));
	printk("Count:%d\n", count);
	printk("Device Name:%s\n", device_name);

	if (!register_chrdev_region(devicenumber, count, device_name))
		printk("Device number registered\n");
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```
You can call it with: 

```
$ sudo insmod ./hello.ko major_number=126 && cat /proc/devices | less

$ sudo insmod ./hello.ko major_number=128

$ sudo insmod ./hello.ko major_number=126 device_name=usb

$ sudo insmod ./hello.ko major_number=126 minor_number=0 count=1048576 device_name=usb

$ sudo insmod ./hello.ko major_number=126 minor_number=10 count=1048576 device_name=usb
```

### What is the maximum major number?

CHRDEV_MAJOR_MAX as an artificial limit (chosen to be 511)
file: linux/fs.h

### What would happen if a major number already used is reserved?

The registration of the driver will fail.

This is the reason why dinamic allocation of the major namer is prefered. 

### What would happen if it is tryied to register a character driver with the same name?

No problem with this.

### What is the maximum minor number?

the max minor number is 2^20 = 1048576.


### Dynamic Allocation


If we dont want fixed major and minor number please use this method.

This method will allocate the major number dynamically to your driver which is available.

```
int alloc_chrdev_region (dev_t *  dev,
		 	unsigned  	baseminor,
 			unsigned  	count,
		 	const char *  	name);
```

Allocates a range of char device numbers.
The major number will be chosen dynamically, and returned (along with the first minor number) in dev

Arguments:
 - dev: output parameter for first assigned number
 - baseminor: first of the requested range of minor numbers
 - count: the number of minor numbers required
 - name: the name of the associated device or driver

Return Value: Returns zero or a negative error code.


### Example:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

int base_minor = 0;
char *device_name = "mychardev";
int count = 1;
dev_t devicenumber;

module_param(base_minor, int, 0);
module_param(count, int, 0);
module_param(device_name, charp, 0);

MODULE_LICENSE("GPL");
static int test_hello_init(void)
{

	printk("Minor Number :%d\n", base_minor);
	printk("Count:%d\n", count);
	printk("Device Name:%s\n", device_name);

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));
	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```
And for using it: 

```
$sudo insmod ./hello.ko
$ sudo insmod ./hello.ko base_minor=1048576 count=10 device_name=usb
```

There are some limits:

```
/* fs/char_dev.c */
#define CHRDEV_MAJOR_MAX 512
/* Marks the bottom of the first segment of free char majors */
#define CHRDEV_MAJOR_DYN_END 234
/* Marks the top and bottom of the second segment of free char majors */
#define CHRDEV_MAJOR_DYN_EXT_START 511
#define CHRDEV_MAJOR_DYN_EXT_END 384
```

@fs/char_dev.c:
```
static int find_dynamic_major(void)
{
        int i;
        struct char_device_struct *cd;

        for (i = ARRAY_SIZE(chrdevs)-1; i >= CHRDEV_MAJOR_DYN_END; i--) {
                if (chrdevs[i] == NULL)
                        return i;
        }

        for (i = CHRDEV_MAJOR_DYN_EXT_START;
             i >= CHRDEV_MAJOR_DYN_EXT_END; i--) {
                for (cd = chrdevs[major_to_index(i)]; cd; cd = cd->next)
                        if (cd->major == i)
                                break;

                if (cd == NULL)
                        return i;
        }

        return -EBUSY;
}
```

## Device files

A device file is an interface for a device driver that appears in a filesystem as if it were an ordinary file. Such files allow software to interact with a device driver. They are found in the `/dev` directory. 

`/dev` is a very interesting directory that highlights one important aspect of the Linux filesystem - everything is a file or a directory. A file sent to /dev/lp0 gets printed. Sending data to and reading from /dev/ttyS0 will allow you to communicate with a device attached there - for instance, your modem.

- reference in kernel documentation: https://docs.kernel.org/admin-guide/devices.html
- reference about device files: https://en.wikipedia.org/wiki/Device_file
- reference: Linux System Administrators Guide: https://linux.die.net/sag/dev-fs.html
- reference: LDP: https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/dev.html

### Creating Device File

Device file can be created in two ways
 - Manual
 - Automatic

#### Manual device file creation

We can create the device file manually by using `mknod`.


```
$ mknod -m <permissions> <name> <device type> <major> <minor>

-m <permissions> – optional argument that sets the permission bits of the new device file to permissions

<name> – your device file name that should have full path (/dev/name)

<device type> – Put c or b
	c – Character Device

	b – Block Device

<major> – major number of your device

<minor> – minor number of your driver
```

Example: 
```
$sudo mknod -m 0644 /dev/mydevice c 244 10

# WATCH OUT! with the manual approach you have to manually delete the device later: sudo rm /dev/mydevice
```

### Automatic device file creation

A device file is an interface for a device driver that appears in a filesystem as if it were an ordinary file. Such files allow software to interact with a device driver. They are found in the `/dev` directory.

Traditionally, device nodes were stored in the `/dev` directory on Linux systems.

The `/dev` directory contains the special device files for all the devices.

- reference about the `/dev` file: https://linux.die.net/sag/dev-fs.html

There was a node for every possible type of device, regardless of whether it actually existed in the system. 

The result was that this directory took up a lot of space

`udev` introduces a new way of creating device nodes.

It compares the information made available by `sysfs` and creates nodes.

`udev` can be further configured using its configuration files to tune the device file names, their permissions, their types, etc.

So, as far as driver is concerned, the appropriate `/sys` entries need to be populated using the Linux device model APIs declared in `<linux/device.h>` and the rest would be handled by `udev`.

reference: udev - dynamic device management: https://linux.die.net/man/7/udev

> udev provides a dynamic device directory containing only the files for actually present devices. It creates or removes device node files in the /dev directory, or it renames network interfaces.
>
> If udev receives a device event, it matches its configured rules against the available device attributes provided in sysfs to identify the device. Rules that match may provide additional device information or specify a device node name > and multiple symlink names and instruct udev to run additional programs as part of the device event handling.


#### class_create — create a struct class structure

Header File: <linux/device.h>

```
struct class * class_create (struct module *owner, const char *name);
```
 - owner: pointer to the module that is to “own” this struct class
 - name: pointer to a string for the name of this class.
<br>
 - reference about `class_create()`: https://www.kernel.org/doc/html/latest/driver-api/infrastructure.html?highlight=device_create#c.class_create

This is used to create a struct class pointer that can then be used in calls to `device_create()`.

Returns `struct class` pointer on success, or `ERR_PTR()` on error.

Note, the pointer created here is to be destroyed when finished by making a call to `class_destroy()`.


#### class_destroy — destroys a struct class structure

```
void class_destroy (struct class *cls);
```

Note, the pointer to be destroyed must have been created with a call to class_create().

- reference about `class_destroy()`: https://www.kernel.org/doc/html/latest/driver-api/infrastructure.html?highlight=device_create#c.class_destroy


Now, the name will appear in /sys/class/<name>.

Example:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
static struct class *class;

static int test_hello_init(void)
{
    class = class_create(THIS_MODULE, "myclass");
    return 0;
}

static void test_hello_exit(void)
{
	class_destroy(class);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

To monitor what is happening use the command:

```
$ udevadm monitor
```
With this command, you can tap into `udev` in real time and see what it sees when you plug in different devices

 - reference: https://linux.die.net/man/8/udevmonitor

### Create a device and register it with sysfs

```
struct device * device_create(struct class *class,
 			      struct device *parent,
			      dev_t  devt,
			      void *drv_data,
 			      const char *fmt,
		 	      ...);
```
 - reference: https://www.kernel.org/doc/html/latest/driver-api/infrastructure.html?highlight=device_create#c.device_create

This function can be used by char device classes. 

A struct device will be created in sysfs, registered to the specified class.

 - class: pointer to the struct class that this device should be registered to
 - parent: pointer to the parent struct device of this new device, if any
 - devt: the dev_t for the char device to be added
 - fmt: string for the device's name
 - ... : variable arguments

If a pointer to a parent struct device is passed in, the newly created struct device will be a child of that device in sysfs. 

#### device_destroy — removes a device that was created with device_create
```
void device_destroy (struct class *class, dev_t devt);
```

Example:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
static struct class *class;
static struct device *device1, *device2;
dev_t dev1, dev2;

static int test_hello_init(void)
{
    dev1 = MKDEV(200, 1);
    dev2 = MKDEV(200, 2);

    class = class_create(THIS_MODULE, "myclass");
    device1 = device_create(class, NULL, dev1, NULL, "mydevice%d", 1);
    device2 = device_create(class, NULL, dev2, NULL, "mydevice%d", 2);

    return 0;
}

static void test_hello_exit(void)
{
	device_destroy(class, dev1);
	device_destroy(class, dev2);
	class_destroy(class);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### Example of an automatic device node creation

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>

int base_minor = 0;
char *device_name = "mychardev";
int count = 1;
dev_t devicenumber;

static struct class *class;
static struct device *device;

MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));
		device = device_create(class, NULL, devicenumber, NULL, device_name);

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	unregister_chrdev_region(devicenumber, count);
	device_destroy(class, devicenumber);
	class_destroy(class);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```


## File operations

reference inode: https://www.kernel.org/doc/html/latest/filesystems/ext4/inodes.html

### struct file_operations:

Defined in : linux/fs.h
Purpose: Holds pointers to functions defined by the driver that performs various operations on the device.

```
struct file_operations {
    struct module *owner;
    loff_t (*llseek) (struct file *, loff_t, int);
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    [...]
    long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
    [...]
    int (*open) (struct inode *, struct file *);
    int (*flush) (struct file *, fl_owner_t id);
    int (*release) (struct inode *, struct file *);
    [...]
```
 - reference: https://elixir.bootlin.com/linux/latest/source/include/linux/fs.h#L1916
   
Example:
```
struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};
```

The above `fops` structure has defined four function pointers : For reading, writing, opening and closing the device file

It can be noticed that the signature of the function differs from the system call that the user uses. The operating system sits between the user and the device driver to simplify implementation in the device driver.

open does not receive the parameter path or the various parameters that control the file opening mode.
Similarly, read, write, release, ioctl, lseek do not receive as a parameter a file descriptor.
Instead, these routines receive as parameters two structures: `file` and `inode`.

### struct cdev

In kernel, each character device is represented using this structure.

Header File: linux/cdev.h

```
struct cdev {
        struct kobject kobj;
        struct module *owner;               // the module owner
        const struct file_operations *ops;  // the file operations
        struct list_head list;
        dev_t dev;                          // the device number
        unsigned int count;                 
} __randomize_layout;
```
 - reference: https://elixir.bootlin.com/linux/latest/source/include/linux/cdev.h#L14


Functions:

```
void cdev_init(struct cdev *, const struct file_operations *); //initialize a cdev structure

struct cdev *cdev_alloc(void); //Allocates and returns a cdev structure

int cdev_add(struct cdev *, dev_t, unsigned int minor_count); // add a char device to the system

void cdev_del(struct cdev *dev); // remove a cdev from the system
```

### cdev_init vs cdev_alloc

```
struct cdev *cdev_alloc(void)
{
        struct cdev *p = kzalloc(sizeof(struct cdev), GFP_KERNEL);
        if (p) {
                INIT_LIST_HEAD(&p->list);
                kobject_init(&p->kobj, &ktype_cdev_dynamic);
        }
        return p;
}
```
`cdev_alloc` allocates the memory for a character driver struct and returns the pinter.

```
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
{
        memset(cdev, 0, sizeof *cdev);
        INIT_LIST_HEAD(&cdev->list);
        kobject_init(&cdev->kobj, &ktype_cdev_default);
        cdev->ops = fops;
}
```
`cdev_init` gets the pointer to a charecter driver struct, cleans the memory, and 
assigns file operations. 

```
 struct cdev *my_dev = cdev_alloc();

    if (my_dev != NULL)
    	my_dev->ops = &my_fops;  /* The file_operations structure */
	my_dev->owner = THIS_MODULE;
```

```
cdev_init(struct cdev *cdev, const struct file_operations *fops);
```


The owner field of the structure should be initialized to THIS_MODULE to protect against ill-advised module unloads while the device is active.
In case someone tries to unload the module while it is working the assignation of THIS_MODULE prevents this. 


### Example of a character driver with file operations registration with `cdev_alloc`

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

int base_minor = 0;
char *device_name = "mychardevice";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev *mycdev = NULL;

MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
        return count;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int test_hello_init(void)
{
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));

		device = device_create(class, NULL, devicenumber, NULL, "mychardevice");
		mycdev = cdev_alloc();
		if (mycdev) {
			mycdev->ops = &device_fops;
			mycdev->owner = THIS_MODULE;
			cdev_add(mycdev, devicenumber, count);
		}

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	device_destroy(class, devicenumber);
        class_destroy(class);
	cdev_del(mycdev);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

To run the example:

```
sudo dmesg -WH & 
make
sudo insmod ./mychardevice.ko
ls -l /dev/mychardevice           // the permissions must be udpated!
sudo chmod 666 /dev/mychardevice
echo "hello World!" > /dev/mychardevice   // device open, device write, device release
cat /dev/mychardevice                     // device open, device read, device release
sudo rmmod mychardevice
```

### Example of a character driver with file operations registration with `cdev_init`

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

int base_minor = 0;
char *device_name = "mychardev";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;              // memory allocation is here

MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
        return count;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int test_hello_init(void)
{
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));

		device = device_create(class, NULL, devicenumber, NULL, "mydevice");
		cdev_init(&mycdev, &device_fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devicenumber, count);

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	device_destroy(class, devicenumber);
        class_destroy(class);
	cdev_del(&mycdev);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```
To run the example:

```
sudo dmesg -WH & 
make
sudo insmod ./mychardevice.ko
ls -l /dev/mychardevice           // the permissions must be udpated!
sudo chmod 666 /dev/mychardevice
echo "hello World!" > /dev/mychardevice   // device open, device write, device release
cat /dev/mychardevice                     // device open, device read, device release
sudo rmmod mychardevice
```

### Pseudo-Devices

Devices in Linux (and other Unix clones) do not necessarily have to correspond to physical devices. These are known as pseudo-devices. For example:

 - `/dev/urandom` : generates a stream of pseudo-random numbers (try running head /dev/urandom in a terminal)
 - `/dev/null` : produces no output, but accepts and discards any input (if you wanted to test your download speed without writing any data to your disk, you could download a file to `/dev/null` by running, e.g., wget http://some.website/big.file > /dev/null).
 - `/dev/zero`: Used by developers to create a file with no meaningful data but a particular size

```
dd if=/dev/zero of=/temp/zero count=1024
ls /tem/zero
du -f /temp/zero
```

```
        /dev/null
        Read : Returns End of file (read returns 0)
        Write: Data written is discarded

        /dev/zero:
        Read: Returns endless bytes of zeroes (\0 characters)
        Write: Data written is discarded

```

File: drivers/char/mem.c has the implementation for this devices https://elixir.bootlin.com/linux/v6.7.5/source/drivers/char/mem.c#L746


### Example using a char driver from userland

Char driver:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

int base_minor = 0;
char *device_name = "mychardev";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
        return count;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int test_hello_init(void)
{
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));

		device = device_create(class, NULL, devicenumber, NULL, device_name);
		cdev_init(&mycdev, &device_fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devicenumber, count);

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	device_destroy(class, devicenumber);
        class_destroy(class);
	cdev_del(&mycdev);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```


User program:

```
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/mychardev"

int main()
{
	int fd;
	int retval;
	char buffer[10];

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	retval = write(fd, "hello", 5);
	printf("Write retval:%d\n", retval);
	getchar();

	retval = read(fd, buffer, 10);
	printf("Read retval:%d\n", retval);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```


### How many times device driver open and release will be called in case of fork?

In case we have a user app like:

```
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE	"/dev/mychardev"

int main()
{
	int fd;
	int retval;
	char buffer[10];
	pid_t pid;

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();
	pid = fork();
	if (pid == 0) {
		printf("Child Process Executing and writing hello world:%ld\n",
				write(fd, "hello world", sizeof("hello world")));
	}
	else {
		printf(" Parent Process executing and writing hello embedded:%ld\n",
				write(fd, "hello embedded", sizeof("hello embedded")));
	}

	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```


The open and release function is only called once.

When you do fork(), it will not create a new file structure and close() will call the release method of the driver only when the counter of the file structure becomes zero



### struct file

 - reference: https://elixir.bootlin.com/linux/v6.7.5/source/include/linux/fs.h#L992

Header File: <linux/fs.h>

`struct file` is different when compared to FILE of user space program.

A FILE is defined in the C library and never appears in kernel code.

A struct file, on the other hand, is a kernel structure that never appears in user programs.

The file structure represents an open file. (It is not specific to device drivers; every open file in the system has an associated struct file in kernel space.) 

It is created by the kernel on `open` and is passed to any function that operates on the file, until the last `close`.

After all instances of the file are closed, the kernel releases the data structure.

An open file is different from a disk file, represented by `struct inode`.

Important Fields

```
struct file {
	//The file mode identifies the file as either readable or writable
	fmode_t                 f_mode;

	//The current reading or writing position. loff_t is a 64-bit value 
	loff_t f_pos;
	
	//These are the file flags, such as O_RDONLY, O_NONBLOCK, and O_SYNC.
	unsigned int            f_flags;

	//The operations associated with the file.
	struct file_operations *f_op;
	
	//The open system call sets this pointer to NULL before calling the open method for the driver.
	//The driver can use the field to point to allocated data, but then must free memory in the release method before the file structure is destroyed by the kernel
	// private_data is a useful resource for preserving state information across system calls
	void *private_data;

        // pointer to the inode
	struct inode		*f_inode;	/* cached value */ 
};
```

Example to check the behavior:

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

int base_minor = 0;
char *device_name = "mychardev";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);

	if ((file->f_flags & O_ACCMODE) == O_RDONLY) {
		pr_info("Opened File in Read only mode\n");
	}else if ((file->f_flags & O_ACCMODE) == O_WRONLY) {
		pr_info("Opened File in Write only mode");
	}
	else if ((file->f_flags & O_ACCMODE) == O_RDWR) {
		pr_info("Opened File in Read/Write mode");
	}

	if (file->f_flags & O_CREAT) {
		pr_info( "Create if it does not exist");
	}

	if (file->f_flags & O_EXCL) {
		pr_info( "Provide exclusive access");
	}

	if (file->f_flags & O_TRUNC) {
		pr_info( "Truncate the file to zero size first");
	}

	if (file->f_flags & O_APPEND) {
		pr_info( "Append to the file (don't overwrite)");
	}

	if (file->f_flags & O_NONBLOCK) {
		pr_info( "Access methods are non-blocking");
	}

	if (file->f_flags & O_SYNC) {
		pr_info( "O_SYNC");
	}

	pr_info("File Offset:%llu\n", file->f_pos);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
		size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
		size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
	return count;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int test_hello_init(void)
{
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		printk("Device number registered\n");
		printk("Major number received:%d\n", MAJOR(devicenumber));

		device = device_create(class, NULL, devicenumber, NULL, "mydevice");
		cdev_init(&mycdev, &device_fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev, devicenumber, count);

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	device_destroy(class, devicenumber);
	class_destroy(class);
	cdev_del(&mycdev);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

program that uses the char driver:
```
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE	"/dev/mydevice"

int main()
{
	int fd;
	int retval;
	char buffer[10];

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);
	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}
	close(fd);
	getchar();
	fd = open(DEVICE_FILE, O_RDONLY);
	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}
	close(fd);
	getchar();
	fd = open(DEVICE_FILE, O_WRONLY);
	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}
	close(fd);
	getchar();
	fd = open(DEVICE_FILE, O_WRONLY | O_NONBLOCK);
	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}
	close(fd);
	getchar();
	fd = open(DEVICE_FILE, O_WRONLY | O_NONBLOCK | O_APPEND);
	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}
	close(fd);
	getchar();

	return 0;
}
```


### struct inode

 - reference: https://elixir.bootlin.com/linux/v6.7.5/source/include/linux/fs.h#L639

Header File: <linux/fs.h>

The `inode` structure is used by the kernel internally to represent files. 

An inode uniquely identifies a file in a file system.

```
struct inode {
	
	//mode
	umode_t                 i_mode;
	
	kuid_t                  i_uid;
        kgid_t                  i_gid;

	//inode number
	unsigned long           i_ino;

	//Contains the actual device number
	dev_t                   i_rdev;

	// Kernel representation of char device
	struct cdev *i_cdev

};
```

Kernel developers have added two macros that can be used to obtain the major and minor numbers from an inode.

```
unsigned int iminor(struct inode *inode);

unsigned int imajor(struct inode *inode);
```




