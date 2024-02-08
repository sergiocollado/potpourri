References:
 - Intro to character device drivers: https://sysprog21.github.io/lkmpg/#character-device-drivers
 - Drivers implementer's API: https://docs.kernel.org/driver-api/index.html
 - Linux kernel documentation - device drivers: https://docs.kernel.org/driver-api/driver-model/driver.html
 - The Linux device driver: https://docs.kernel.org/driver-api/driver-model/overview.html
 - https://sysprog21.github.io/lkmpg/#character-device-drivers
 - Understanding the structure of a Linux Device Driver: https://youtu.be/pIUTaMKq0Xc
 - Let's code a Linux Driver: https://www.youtube.com/watch?v=x1Y203vH-Dc&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
 - Linux kernel labs - character drivers: https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html
 - Introduction to Linux device drivers: https://youtu.be/fQkObOxVTVo
 - Introduction to Linux device drivers part 2: https://youtu.be/n1wHgGmDXwE
 - Fast bit: Linux device driver programming: https://www.youtube.com/watch?v=YR_vYTh8CmY&list=PLERTijJOmYrAtfl5U_TAbCOisCNb7XEbb
 - Linux device drivers: https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-part-1-introduction/
 - Linux device drivers tutorial: https://www.youtube.com/watch?v=BRVGchs9UUQ&list=PLArwqFvBIlwHq8WMKgsXSQdqIvymrEz9k&index=2


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

zero on success, a negative error code on failure.

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

#### Description

Allocates a range of char device numbers.
The major number will be chosen dynamically, and returned (along with the first minor number) in dev

#### Arguments

 - dev: output parameter for first assigned number
 - baseminor: first of the requested range of minor numbers
 - count: the number of minor numbers required
 - name: the name of the associated device or driver


#### Return Value

Returns zero or a negative error code.


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









