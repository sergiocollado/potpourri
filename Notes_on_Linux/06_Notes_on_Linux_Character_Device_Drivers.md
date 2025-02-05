References:
 - Intro to character device drivers: https://sysprog21.github.io/lkmpg/#character-device-drivers
 - Linux Kernel Programming Part 2 - Char Device Drivers and Kernel Synchronization:
    - https://github.com/PacktPublishing/Linux-Kernel-Programming/blob/master/Linux-Kernel-Programming-(Part-2)/Linux%20Kernel%20Programming%20Part%202%20-%20Char%20Device%20Drivers%20and%20Kernel%20Synchronization_eBook.pdf
    - https://github.com/PacktPublishing/Linux-Kernel-Programming-Part-2
 - https://tldp.org/LDP/lkmpg/2.6/html/c567.html
 - Drivers implementer's API: https://docs.kernel.org/driver-api/index.html
 - Linux kernel documentation - device drivers: https://docs.kernel.org/driver-api/driver-model/driver.html
 - The Linux device driver: https://docs.kernel.org/driver-api/driver-model/overview.html
 - https://sysprog21.github.io/lkmpg/#character-device-driversfstruct cdev
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
 - Understanding the structure of a Linux device driver: https://youtu.be/pIUTaMKq0Xc
 - linux block drivers: https://olegkutkov.me/2020/02/10/linux-block-device-driver/
 - Linux device drivers introduction: https://youtu.be/fQkObOxVTVo
 - character device drivers tutorial list: https://www.youtube.com/watch?v=Zn8mEZXr6nE&list=PL2GL6HVUQAuksbptmKC7X4zruZlIl59is


## Introduction: what is a device driver?

In Linux everything is considered to be a file so devices are also considered to be a file.

A device driver is a piece of code that configurs and manages devices. The device driver code knows how to 
configure the device, how to process requests which come from the device, and how to send data to the device. 

In UNIX, hardware devices are accessed by the user through special device files.

These files are grouped into the `/dev` directory, and system calls `open`, `read`, `write`, `close`, `lseek`, `mmap` etc. are redirected by the operating system to the device driver associated with the physical device.

In the UNIX world there are two categories of device files and thus device drivers: 
 - **character**
 - **block**

This division is done 
 - by the speed, 
 - volume and 
 - way of organizing the data to be transferred from the device to the system and vice versa.

In the first category, there are slow devices, which manage a small amount of data, and access to data does not require frequent seek queries. Examples are devices such as keyboard, mouse, sensors, serial ports, sound card, joystick. In general, operations with these devices (read, write) are performed sequentially byte by byte. Those devices are known as **character devices**

The second category includes devices where data volume is large, data is **organized on blocks**, and has to be handled in **blocks**, and search is common, those decives re more complex than the character devices. Examples of devices that fall into this category are hard drives, cdroms, ram disks, magnetic tape drives, USB cameras...  For these devices, reading and writing is done at the data block level. Those devices are known as **block devices**

For the two types of device drivers, the Linux kernel offers different APIs.

If for __**character devices**__ system calls go directly to device drivers, in case of **block devices**, the drivers do not work directly with system calls. 

In the case of __**block devices**__, communication between the user-space and the block device driver is mediated by the __**file management**__ subsystem and the block device subsystem. 

You can know the character and block device drivers in a system with the command `cat /proc/devices`. 

### Character Device Driver

A character device typically transfers data to and from a user application — they behave like pipes or serial ports, instantly reading or writing the byte data in a character-by-character stream.

#### Command to list all the character device driver
```bash
$ls -l /dev/ | grep "^c"
```

#### Command to list all the block device driver

```bash
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
 - **Major Number** : identifies the device type (IDE disk, SCSI disk, serial port, etc.)
 - **Minor Number** : identifies the device (first disk, second serial port, etc.)

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

In columns 5th and 6th of the result you can see the major, respectively the minor for each device.

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

```C
#define MINORBITS	20
#define MINORMASK	((1U << MINORBITS) - 1)

#define MAJOR(dev)	((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)	((unsigned int) ((dev) & MINORMASK))
#define MKDEV(ma,mi)	(((ma) << MINORBITS) | (mi))
```

#### Example:

```C
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

```C
int register_chrdev_region (dev_t from,	unsigned count,	const char *name);
```

Description: register a range of device numbers

Arguments:
 - from : the first in the desired range of device numbers; must include the major number.
 - count: the number of consecutive device numbers required
 - name: the name of the device or driver. This will appear in /proc/devices

Return Value:
 - zero on success, a negative error code on failure.

```C
void unregister_chrdev_region(dev_t from, unsigned int count);
```

Header File: <linux/fs.h>

Example:

```C
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

```bash
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

```C
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

```C
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

```C
$sudo insmod ./hello.ko
$ sudo insmod ./hello.ko base_minor=1048576 count=10 device_name=usb
```

There are some limits:

```bash
/* fs/char_dev.c */
#define CHRDEV_MAJOR_MAX 512
/* Marks the bottom of the first segment of free char majors */
#define CHRDEV_MAJOR_DYN_END 234
/* Marks the top and bottom of the second segment of free char majors */
#define CHRDEV_MAJOR_DYN_EXT_START 511
#define CHRDEV_MAJOR_DYN_EXT_END 384
```

@fs/char_dev.c:
```C
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

Device files `/dev` are managed as part of the VFS (virtual file subsystem) subsystem of the Linux kernel. 

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

example: https://www.youtube.com/watch?v=hbSSi4bHF8E&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa&index=5

```bash
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
```bash
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

```C
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

```C
void class_destroy (struct class *cls);
```

Note, the pointer to be destroyed must have been created with a call to class_create().

- reference about `class_destroy()`: https://www.kernel.org/doc/html/latest/driver-api/infrastructure.html?highlight=device_create#c.class_destroy


Now, the name will appear in /sys/class/<name>.

Example:

```C
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

```bash
$ udevadm monitor
```
With this command, you can tap into `udev` in real time and see what it sees when you plug in different devices

 - reference: https://linux.die.net/man/8/udevmonitor

### Create a device and register it with sysfs

```C
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
```C
void device_destroy (struct class *class, dev_t devt);
```

Example:

```C
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

```C
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

```C
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
```C
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

#### __user attribute

 - reference: https://stackoverflow.com/questions/4521551/what-are-the-implications-of-the-linux-user-macro

`__user` marks user space pointers and tells the developer/system not to trust it. If user gives you "invalid" pointer, then kernel tries to reference it (note that kernel can reference everywhere) and it can corrupt it's own space.

For example in "read"(in you usbdevice_fs.h) should provide you a (__user) buffer to write the result to. So you have to use copy_to_user, but not memcopy, strcpy or anything like this.

Also: The __user macro is defined with some other macros like __force/__kernel etc in the compiler.h header file. They are actually not of any use to traditional compilers, including GCC/ICC etc. But it's useful for kernel static analysis tools like sparse (more information here: Sparse - Linux Kernel Newbies). When you mention the macros like `__user`/`__kernel`/`__force` etc, it keeps special meaning for sparse.

### struct cdev

In kernel, each character device is represented using this structure.

Header File: linux/cdev.h

```C
struct cdev {
        struct kobject kobj;
        struct module *owner;               // the module owner
        const struct file_operations *ops;  // the file operations
        struct list_head list;
        dev_t dev;                          // the device number
        unsigned int count;                 
} __randomize_layout;
```
 - reference: https://elixir.bootlin.com/linux/v6.11.4/source/include/linux/cdev.h#L14

 - **kobj**: is the undeliying kernel object
 - **owner**: this should be set with the THIS_MODULE macro.
 - **ops**: this is the set of file operation associated with this character device
 - **dev**: this is teh character device identifier


Functions:

```C
void cdev_init(struct cdev *, const struct file_operations *); //initialize a cdev structure

struct cdev *cdev_alloc(void); //Allocates and returns a cdev structure

int cdev_add(struct cdev *, dev_t, unsigned int minor_count); // add a char device to the system

void cdev_del(struct cdev *dev); // remove a cdev from the system
```

### introduction to device file operations

 The `cdev->ops` element points to the file operations supported by a given decie. Each of thesse
 operations is the tareg of a partigular system call, in the way that when the system call is
 invoqued in the user space, this system call is redirected in the kernel to its file operation 
 counterpart in  `cdev->ops'. `file_oeprations` is the data structure that holds these operations.

 - reference: https://elixir.bootlin.com/linux/v6.11.4/source/include/linux/fs.h#L2022

```C
struct file_operations {
	struct module *owner;
	fop_flags_t fop_flags;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
	int (*iopoll)(struct kiocb *kiocb, struct io_comp_batch *,
			unsigned int flags);
	int (*iterate_shared) (struct file *, struct dir_context *);
	__poll_t (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	void (*splice_eof)(struct file *file);
	int (*setlease)(struct file *, int, struct file_lease **, void **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
	void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
	unsigned (*mmap_capabilities)(struct file *);
#endif
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *,
			loff_t, size_t, unsigned int);
	loff_t (*remap_file_range)(struct file *file_in, loff_t pos_in,
				   struct file *file_out, loff_t pos_out,
				   loff_t len, unsigned int remap_flags);
	int (*fadvise)(struct file *, loff_t, loff_t, int);
	int (*uring_cmd)(struct io_uring_cmd *ioucmd, unsigned int issue_flags);
	int (*uring_cmd_iopoll)(struct io_uring_cmd *, struct io_comp_batch *,
				unsigned int poll_flags);
} __randomize_layout;
```

- **struct module *owner**:
- **loff_t (*llseek) (struct file *, loff_t, int); **: 
- **ssize_t (*read) (struct file *, char __user *, size_t, loff_t *); **: 
- **ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *); **:
- **int (*flush) (struct file *, fl_owner_t id); **: 
- **__poll_t (*poll) (struct file *, struct poll_table_struct *); **: 
- **int (*mmap) (struct file *, struct vm_area_struct *); **: 
- **int (*open) (struct inode *, struct file *); **:
- **int (*release) (struct inode *, struct file *); **:
- **int (*fsync) (struct file *, loff_t, loff_t, int datasync); **:
- **long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long); **: 
  

### cdev_init vs cdev_alloc

```C
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
`cdev_alloc` allocates the memory for a character driver struct and returns the pointer.

```C
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

```C
 struct cdev *my_dev = cdev_alloc();

    if (my_dev != NULL)
    	my_dev->ops = &my_fops;  /* The file_operations structure */
	my_dev->owner = THIS_MODULE;
```

```C
cdev_init(struct cdev *cdev, const struct file_operations *fops);
```


The owner field of the structure should be initialized to THIS_MODULE to protect against ill-advised module unloads while the device is active.
In case someone tries to unload the module while it is working the assignation of THIS_MODULE prevents this. 


### Example of a character driver with file operations registration with `cdev_alloc`

```C
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

```C
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

```C
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

```C
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

```C
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

```C
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

```C
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

```C
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

### struct inode

> Originally the term was "index node number", which was shortened to
> "inode number", shortened again to "inumber", and finally "ino".  

 - reference: https://elixir.bootlin.com/linux/v6.7.5/source/include/linux/fs.h#L639

Header File: <linux/fs.h>

The `inode` structure is used by the kernel internally to represent files. 

An inode uniquely identifies a file in a file system.

```C
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

```C
unsigned int iminor(struct inode *inode);

unsigned int imajor(struct inode *inode);
```

### Example

```C
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

	//struct file
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

	//struct inode
	pr_info("Mode: %ho\n", inode->i_mode);
	pr_info("User Id: %d\n", inode->i_uid.val);
	pr_info("Group Id: %d\n", inode->i_gid.val);
	pr_info("Inode number:%lu\n", inode->i_ino);
	pr_info("Major number:%d\t Minor Number:%d\n", imajor(inode), iminor(inode));
	pr_info("Major number:%d\t Minor Number:%d\n", MAJOR(inode->i_rdev), MINOR(inode->i_rdev));

	//Accessing struct inode from struct file
	pr_info("Inode number through file structure:%lu\n", file->f_inode->i_ino);
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

```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/mydevice"

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
For checking the inode number of the char driver, check it with:
```C
stat /dev/mydevice
```



### Access to the address space pointers from kernel space

Accessing process address space can not be done directly (by de-referencing a user-space pointer). 

Direct access of a user-space pointer can lead to 
 - incorrect behavior (depending on architecture, a user-space pointer may not be valid or mapped to kernel-space), 
 - a kernel oops (the user-mode pointer can refer to a non-resident memory area) or 
 - security issues. 

Proper access to user-space data is done by calling the macros / functions below:

```C
old linux version before 4.x:
#include <asm/uaccess.h>
```
```C
latest linux version:
#include <linux/uaccess.h>

put_user(type val, type *address);
get_user(type val, type *address);
unsigned long copy_to_user(void __user *to, const void *from, unsigned long n);
unsigned long copy_from_user(void *to, const void __user *from, unsigned long n)
```

All macros / functions return 0 in case of success and another value in case of error and have the following roles:

 - `put_user` put in the user-space at the address address value of the val; Type can be one on 8, 16, 32, 64 bit (the maximum supported type depends on the hardware platform);
 - `get_user` analogue to the previous function, only that val will be set to a value identical to the value at the user-space address given by address;
 - `copy_to_user` copies n bytes from the kernel-space, from the address referenced by from in user-space to the address referenced by to;
 - `copy_from_user` copies n bytes from user-space from the address referenced by from in kernel-space to the address referenced by to.


### copy_from_user
```
unsigned long copy_from_user(void *to, const void __user *from, unsigned long n)
```
Header File: <linux/uaccess.h>

The copy_from_user function copies a block of data from user space into a kernel buffer. 

It accepts
 - destination buffer (in kernel space), 
 - a source buffer (from user space), and 
 - a length defined in bytes

Returns: zero on success, non-zero to indicate a failure to copy some number of bytes.

Example:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

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
	pr_info("%s:Count:%lu \t offset:%llu\n", __func__,
			count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	char kernel_buffer[100] = {0};
	int retval;

	pr_info("%s: Kernel Buffer:%p\t User Buffer:%p\n", __func__, kernel_buffer, user_buffer);
	retval = copy_from_user(kernel_buffer, user_buffer, count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s:Kernel Buffer:%s\t Count:%lu \t offset:%llu\n", __func__, kernel_buffer,
			count, *offset);
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

The user app:
```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/mydevice"

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


### copy_to_user

```C
unsigned long copy_to_user(void __user *to, const void *from, unsigned long n);
```
Header File: <linux/uaccess.h>

The copy_to_user function copies a block of data from the kernel into user space. 

This function accepts a 
 - pointer to a user space buffer, 
 - a pointer to a kernel buffer, and 
 - a length defined in bytes. 

Returns zero on success or non-zero to indicate the number of bytes that weren’t transferred

Example:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

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
	char kernel_buffer[10] = "kernel";

	int retval;

	retval = copy_to_user(user_buffer, kernel_buffer, 7);

	pr_info("%s: Copy to user returned:%d\n", __func__, retval);

	pr_info("%s:Kernel buffer:%s \t Count:%lu \t offset:%llu\n", __func__,
			kernel_buffer, count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	char kernel_buffer[100] = {0};
	int retval;

	retval = copy_from_user(kernel_buffer, user_buffer, count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s:Kernel Buffer:%s\t Count:%lu \t offset:%llu\n", __func__, kernel_buffer,
			count, *offset);
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

The user app:
```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/mydevice"

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
	printf("Buffer:%s\n", buffer);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```
### put_user

`put_user` function is used to write a simple variable from the kernel into user space

```C
put_user (x, ptr);
```
 - x: Value to copy to user space. 
 - ptr: Destination address, in user space.

It supports simple types like char and int, but not larger data types like structures or arrays.

Example:

#### What are jiffies?

Informally, According to wikipedia, jiffy is term used for any unspecified short period of time.

Coming back to our Linux kernel world, `jiffies` are a global variable which stores the number of clock ticks since boot. It is present in `<linux/jiffies.h>`

Let's write a character driver which on read returns the value of `jiffies`.

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "jiffies";
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
	if (count < sizeof(jiffies))
                return -EINVAL;
        if (!put_user(jiffies, (u64 *)user_buffer))  // WATCH OUT the castion to u64*
            return sizeof(jiffies);
        else
            return -EFAULT;

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

The user app:

```C
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd;
	unsigned long long old_jiffies;
	unsigned long long new_jiffies;
	
	fd = open("/dev/jiffies", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}

	if (read(fd, &old_jiffies, sizeof(old_jiffies)) != sizeof(old_jiffies)) {
		printf("Failed in reading first jiffies\n");
		exit(3);
	} else {
		printf("First Read:%lld\n", old_jiffies);
	}

	sleep(1);  // sleep for 1 second

	if (read(fd, &new_jiffies, sizeof(new_jiffies)) != sizeof(new_jiffies)) {
		printf("Failed in reading second jiffies\n");
		exit(4);
	} else {
		printf("Second Read:%lld\n", new_jiffies);
	}

	printf("Difference:%lld\n", (new_jiffies - old_jiffies));
	close(fd);
}
```

1. You could see from the output, the difference we got is X, it means the value of jiffie increments by X every second, this also means the timer is configured to generate X interrupts every second.

2. We use `put_user` to copy the value of jiffies to user space. `put_user` is faster than `copy_to_user`, and can copy up to 8 bytes of data. The size that put_user copies depends on the type of the pointer argument and is determined at compiled time using typeof and sizeof builtins.

### get_user

To read a simple variable from user space, you use the `get_user` function

This function is used for simple types such as char and int, but larger data types like structures must use the copy_from_user function

```C
get_user (x, ptr);
```

Example:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "myint";
int count = 1;
dev_t devicenumber;

int value = 0;

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
	if (count < sizeof(value))
                return -EINVAL;
        if (!put_user(value, (int *)user_buffer))
            return sizeof(value);
        else
            return -EFAULT;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	pr_info("%s\n", __func__);
	get_user(value, (int *)user_buffer);  // WATCH OUT the casting to int*
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

The user app:

```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/myint"

int main()
{
	int fd;
	int retval;
	int value = 10;

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	retval = write(fd, &value, sizeof(value));
	printf("Write retval:%d\n", retval);
	getchar();

	value = 2;

	retval = read(fd, &value, sizeof(value));
	printf("Read retval:%d\t value:%d\n", retval, value);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

### Parsing a structure between kernel space and user space

If for example we have the following structure, how we can pass it to a character driver?

```c
// mystruct.h
#ifndef __MYSTRUCT_H
#define __MYSTRUCT_H

typedef struct abc
{
	int i;
	char c;
}abc;

#endif
```



```c
include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "mystruct.h"

int base_minor = 0;
char *device_name = "mystruct";
int count = 1;
dev_t devicenumber;
abc kernel_struct;

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
	int retval;

	retval = copy_to_user(user_buffer, &kernel_struct, sizeof(kernel_struct));   // HERE! THE STRUCTURE IS MOVED FROM THE kernel_struct
                                                                                     // STRUCTURE TO THE user_buffer

	pr_info("%s: Copy to user returned:%d\n", __func__, retval);

	pr_info("%s:int :%d\t char:%c \t Count:%lu \t offset:%llu\n", __func__,
			kernel_struct.i, kernel_struct.c, count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	int retval;

	retval = copy_from_user(&kernel_struct, user_buffer, count);               // HERE WE ARE COPYING FROM THE user_buffer
                                                                                   // INTO the kernel_struct
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s:int:%d\t char:%c\t Count:%lu \t offset:%llu\n", __func__, kernel_struct.i,
			kernel_struct.c, count, *offset);
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

the program in user space:

```c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "mystruct.h"

#define DEVICE_FILE "/dev/mystruct"

int main()
{
	int fd;
	int retval;
	abc user_struct = {5, 'a'};

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	retval = write(fd, &user_struct, sizeof(user_struct));
	printf("Write retval:%d\n", retval);
	getchar();

	user_struct.i = 4;
	user_struct.c = 'b';

	retval = read(fd, &user_struct, sizeof(user_struct));
	printf("Read retval:%d\t int:%d\tchar:%c\n", retval, user_struct.i, user_struct.c);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```


### It is possible to pass variables on the heap between kernel space and user space

In the previous point it was showcased that it is possible to pass variables in the stack between user space and kernel space. 
Can variables on the heap also be passed between user space and kernel space? Yes, it can be done without any issue.

```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

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
	pr_info("%s:Count:%lu \t offset:%llu\n", __func__,
			count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	char kernel_buffer[100] = {0};
	int retval;

	pr_info("%s: Kernel Buffer:%p\t User Buffer:%p\n", __func__, kernel_buffer, user_buffer);
	retval = copy_from_user(kernel_buffer, user_buffer, count);                              // HERE THE VARIABLE IS BEING COPIED FROM THE USER
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s:Kernel Buffer:%s\t Count:%lu \t offset:%llu\n", __func__, kernel_buffer,
			count, *offset);
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


```c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_FILE "/dev/mydevice"

int main()
{
	int fd;
	int retval;
	char *buffer = malloc(sizeof(char)*10);     // THIS IS THE VARIABLE WE WANT TO MOVE AROUND

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	strcpy(buffer, "hello");

	retval = write(fd, buffer, strlen(buffer));
	printf("Write retval:%d\n", retval);
	getchar();

	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

### It is possible to pass a structure with one member on the stack and other member on the heap?

For example, the structure: 

```c
#ifndef __MYSTRUCT_H
#define __MYSTRUCT_H

typedef struct abc
{
	int i;
	char *str;
}abc;

#endif
```

```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "mystruct.h"

int base_minor = 0;
char *device_name = "mystruct";
int count = 1;
dev_t devicenumber;
abc kernel_struct;

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
	int retval;

	retval = copy_to_user(user_buffer, &kernel_struct, sizeof(kernel_struct));

	pr_info("%s: Copy to user returned:%d\n", __func__, retval);

	pr_info("%s:int :%d\t str:%s \t Count:%lu \t offset:%llu\n", __func__,
			kernel_struct.i, kernel_struct.str, count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	int retval;

	retval = copy_from_user(&kernel_struct, user_buffer, count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s:int:%d\t str:%s\t Count:%lu \t offset:%llu\n", __func__, kernel_struct.i,
			kernel_struct.str, count, *offset);
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

```c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mystruct.h"

#define DEVICE_FILE	"/dev/mystruct"

int main()
{
	int fd;
	int retval;
	abc user_struct;

	user_struct.str = malloc(sizeof(char)*10);
	strcpy(user_struct.str, "hello");
	user_struct.i = 10;

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	retval = write(fd, &user_struct, sizeof(user_struct));
	printf("Write retval:%d\n", retval);
	getchar();

	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

This will not work, the module will freeze.

### Printing Device Numbers

Kernel provides a couple of utility macros to print device numbers.

```
Header File: <linux/kdev_t.h>

int print_dev_t(char *buffer, dev_t dev);

char *format_dev_t(char *buffer, dev_t dev);
```

Both macros encode the device number into the given buffer; the only difference is `print_dev_t` returns the number of characters printed, while `format_dev_t` returns buffer;

The buffer size should be at least 20 bytes, which is the size of the device number.

Example:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
	dev_t devicenumber;
	char buffer[20];

	devicenumber = MKDEV(120, 30);
	printk("Device Number :%s\n", format_dev_t(buffer, devicenumber));
	buffer[0] = '\0';
	printk("print_dev_t returned:%d\t Device Number:%s\n", print_dev_t(buffer, devicenumber), buffer);

	return -1;  // this will make the init to fail!
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### String functions in the kernel

There are many functions in the kernel related to strings and those funtions don't depend on the standard library: https://docs.kernel.org/core-api/kernel-api.html#c.strlen

Example:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

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
	char kernel_buffer[10] = "kernel";
	int retval;

	retval = copy_to_user(user_buffer, kernel_buffer, 7);
	pr_info("%s: strlen:%lu\n", __func__, strlen(kernel_buffer));    // HERE THE STRLEN IS USED TO CHECK THE LEN OF THE KERNEL BUFFER
	pr_info("%s: Copy to user returned:%d\n", __func__, retval);
	pr_info("%s:Kernel buffer:%s \t Count:%lu \t offset:%llu\n", __func__,
                        kernel_buffer, count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	char kernel_buffer[100] = {0};
	int retval;

	pr_info("%s: Kernel Buffer:%p\t User Buffer:%p\n", __func__, kernel_buffer, user_buffer);
	pr_info("%s: strlen user buffer:%lu\n", __func__, strlen(user_buffer));             // HERE STRLEN() IS USED TO CHECK THE LEN OF THE USER BUFFER
	retval = copy_from_user(kernel_buffer, user_buffer, count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s:Kernel Buffer:%s\t Count:%lu \t offset:%llu\n", __func__, kernel_buffer,
			count, *offset);
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

And the program:

```C
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

	getchar();

	retval = read(fd, buffer, 10);
	printf("Read retval:%d\n", retval);
	getchar();

	retval = write(fd, "hello", 5);
	printf("Write retval:%d\n", retval);
	getchar();

	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

### strnlen_user

Get the size of a string in user space.

```
long strnlen_user (const char __user *s, long  	n);

s 	The string to measure.

n	The maximum valid length
```

reference: https://elixir.bootlin.com/linux/v4.4/source/lib/strnlen_user.c#L104

```C
/**
 * strnlen_user: - Get the size of a user string INCLUDING final NUL.
 * @str: The string to measure.
 * @count: Maximum count (including NUL character)
 *
 * Context: User context only. This function may sleep if pagefaults are
 *          enabled.
 *
 * Get the size of a NUL-terminated string in user space.
 *
 * Returns the size of the string INCLUDING the terminating NUL.
 * If the string is too long, returns a number larger than @count. User
 * has to check the return value against "> count".
 * On exception (or invalid count), returns 0.
 *
 * NOTE! You should basically never use this function. There is
 * almost never any valid case for using the length of a user space
 * string, since the string can be changed at any time by other
 * threads. Use "strncpy_from_user()" instead to get a stable copy
 * of the string.
 */
long strnlen_user(const char __user *str, long count)
{
	unsigned long max_addr, src_addr;

	if (unlikely(count <= 0))
		return 0;

	max_addr = user_addr_max();
	src_addr = (unsigned long)str;
	if (likely(src_addr < max_addr)) {
		unsigned long max = max_addr - src_addr;
		return do_strnlen_user(str, count, max);
	}
	return 0;
}
EXPORT_SYMBOL(strnlen_user);
```


Get the size of a NUL-terminated string in user space.

Returns the size of the string INCLUDING the terminating NUL.

If the string is too long, returns a value greater than n.

As stated on the function explanation, better use the function `strncpy_from_user()`.

> Use "strncpy_from_user()" instead to get a stable copy of the string.


### How to pass one variable with members on the stack and on the heap.


```C
#ifndef __MYSTRUCT_H
#define __MYSTRUCT_H

typedef struct abc
{
	int i;
	char *str;
}abc;

#endif
```

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "mystruct.h"

int base_minor = 0;
char *device_name = "mystruct";
int count = 1;
dev_t devicenumber;
abc kernel_struct;
char kernel_buffer[100];

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
	int retval;

        // COPY_TO_USER HAS TO BE CALLED TWICE!!!

	retval = copy_to_user(&((abc *)user_buffer)->i, &kernel_struct.i, sizeof(kernel_struct.i));
	pr_info("%s: Copy to user returned:%d\n", __func__, retval);

	retval = copy_to_user(((abc *)user_buffer)->str, kernel_buffer, strlen(kernel_buffer)+1);
	pr_info("%s: Copy to user returned:%d\n", __func__, retval);



	pr_info("%s:int :%d\t str:%s \t Count:%lu \t offset:%llu\n", __func__,
			kernel_struct.i, kernel_struct.str, count, *offset);
        return 0;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	int retval;
	int string_length = 0;

        // COPY_FROM_USER HAS TO BE CALLED TWICE!!!
	// FIRST IS COPIED THE STACK
 	// SECOND IS COPIED THE HEAP

	retval = copy_from_user(&kernel_struct, user_buffer, count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);

	string_length = strnlen_user(kernel_struct.str, 100);
	retval = copy_from_user(&kernel_buffer, kernel_struct.str, string_length);

	pr_info("%s: Length:%d\n", __func__, string_length);
	pr_info("%s:int:%d\t str:%s\t Count:%lu \t offset:%llu\n", __func__, kernel_struct.i,
			kernel_buffer, count, *offset);
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

```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mystruct.h"

#define DEVICE_FILE	"/dev/mystruct"

int main()
{
	int fd;
	int retval;
	abc user_struct;

	user_struct.str = malloc(sizeof(char)*10);
	strcpy(user_struct.str, "hello");
	user_struct.i = 10;

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();


	retval = write(fd, &user_struct, sizeof(user_struct));
	printf("Write retval:%d\n", retval);
	getchar();

	memset(&user_struct, 0, sizeof(user_struct));

	user_struct.str = malloc(sizeof(char)*10);
	retval = read(fd, &user_struct, sizeof(user_struct));
	printf("Write retval:%d\n", retval);
	printf("Int:%d\t Str:%s\n", user_struct.i, user_struct.str);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

### The problem reading character by character

In the character device driver:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];

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
	int retval;

	pr_info("%s\n", __func__);
	retval = copy_to_user(user_buffer, kernel_buffer, count);
	pr_info("%s: Copy to user returned:%d\n", __func__, retval);

        return count;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t count, loff_t *offset)
{
	int retval;

	pr_info("%s\n", __func__);
	retval = copy_from_user(kernel_buffer, user_buffer, count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);
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

there would be any issue if it was readed character by character?

For example: 

```c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/msg"

int main()
{
	int fd;
	int retval;
	char buffer[10];
	int i;

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

	for (i = 0; i < 10; i++) {
		retval = read(fd, buffer, 1);       // READING BYTE BY BYTE!
		printf("Read retval:%d\n", retval);
		printf("Read buffer:%c\n", buffer[0]);
		getchar();
	}
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

Every time, the returned value is the first one :/


To fix this, the `*offp` should be updated after each data transfer to represent the current file position after
successfully completion of the system call. 

The code has to be updated to:

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int retval;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	if (buffer_index + read_count > MAX_SIZE) {
		pr_err("%s: buffer_index:%d\t read_count:%lu\t Max Size:%d\n",__func__,
				buffer_index, read_count, MAX_SIZE);
		return -ENOSPC;
	}

	retval = copy_to_user(user_buffer, kernel_buffer+*offset, read_count);
	pr_info("%s: Copy to user returned:%d\n", __func__, retval);
	//update file offset                                                        // UPDATE FILE OFFSET
	*offset += read_count;

        return read_count;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int retval;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	if (buffer_index + write_count > MAX_SIZE) {
		pr_err("%s: buffer_index:%d\t write_count:%lu\t Max Size:%d\n",__func__,
				buffer_index, write_count, MAX_SIZE);
		return -ENOSPC;
	}

	retval = copy_from_user(kernel_buffer+buffer_index, user_buffer, write_count);
	pr_info("%s: Copy from user returned:%d\n", __func__, retval);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	buffer_index += write_count;
	//update file offset                                                       // UPDATE FILE OFFSET
	*offset += write_count;
        return write_count;
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

We can check with the program:

```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/msg"

int main()
{
	int fd;
	int retval;
	char buffer[10];
	int i;

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

	retval = write(fd, "world", 5);
	printf("Write retval:%d\n", retval);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

And the program:

```C
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE	"/dev/msg"

int main()
{
	int fd;
	int retval;
	char buffer[10];
	int i;

	printf("Opening File:%s\n", DEVICE_FILE);
	fd = open(DEVICE_FILE, O_RDWR);

	if (fd < 0) {
		perror("Open Failed");
		exit(1);
	}

	getchar();

	retval = read(fd, buffer, 5);
	buffer[retval] = '\0';
	printf("read retval:%d\n", retval);
	printf("read buffer:%s\n", buffer);
	getchar();

	retval = read(fd, buffer, 5);
	buffer[retval] = '\0';
	printf("read retval:%d\n", retval);
	printf("read buffer:%s\n", buffer);
	getchar();
	
	printf("Closing File\n");
	close(fd);
	getchar();

	return 0;
}
```

There is still a problem: to read/write less of the available

For this: 

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	// THIS VARIABLES ARE ADDED 
	int bytes_read;
	int available_space; // MAXIMUM SIZE - OFFSET
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{

	// THIS VARIABLES ARE ADDED 
	int bytes_written;
	int available_space; // MAXIMUM SIZE - OFFSET
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
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

We can check the behaviour with the program:

```C
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buffer[50];	
	int fd;
	int length;
	int i = 0;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}
	printf("write : %d\n", write(fd, "hello world", sizeof("hello world")));	
	printf("write : %d\n", write(fd, "bye world", sizeof("bye world")));

	//set the file position to 0
	lseek(fd, 0, SEEK_SET);
	perror("lseek");
	memset(buffer, 0, sizeof(buffer));
	length = read(fd, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\t length:%d\n", buffer, length);

	for (i = 0 ; i < length; i++)
		printf("buffer[%d]:\t%c\n", i, buffer[i]);
	memset(buffer, 0, sizeof(buffer));
	length = read(fd, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\tlength:%d\n", buffer, length);
	close(fd);
}
```

This stills fails because `lseek()` is not implemented yet.

### Implementing `lseek`

 - reference: https://man7.org/linux/man-pages/man2/lseek.2.html

The `llseek` method implements the `lseek` and `llseek` system calls.

If your device is unseekable, you should return `-ESPIPE`


>     lseek() repositions the file offset of the open file description
>       associated with the file descriptor fd to the argument offset
>       according to the directive whence as follows:
> 
>       SEEK_SET
>              The file offset is set to offset bytes.
>
>       SEEK_CUR
>              The file offset is set to its current location plus offset
>              bytes.
>
>       SEEK_END
>              The file offset is set to the size of the file plus offset
>              bytes.
>
>       lseek() allows the file offset to be set beyond the end of the
>       file (but this does not change the size of the file).  If data is
>       later written at this point, subsequent reads of the data in the
>       gap (a "hole") return null bytes ('\0') until data is actually
>       written into the gap.


```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;

	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

static loff_t device_lseek(struct file *file, loff_t offset, int orig)       // LSEEK
{
	loff_t new_pos = 0;

	switch(orig) {
		case 0 : /*seek set*/
			new_pos = offset;
			break;
		case 1 : /*seek cur*/
			new_pos = file->f_pos + offset;
			break;
		case 2 : /*seek end*/
			new_pos = MAX_SIZE - offset;
			break;
	}
	if(new_pos > MAX_SIZE)
		new_pos = MAX_SIZE;
	if(new_pos < 0)
		new_pos = 0;
	file->f_pos = new_pos;
	return new_pos;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek
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

the program: 

```C
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char buffer[50];	
	int fd;
	int length;
	int i = 0;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}
	printf("write : %d\n", write(fd, "hello world", sizeof("hello world")));	
	printf("write : %d\n", write(fd, "bye world", sizeof("bye world")));

	//set the file position to 0
	lseek(fd, 0, SEEK_SET);
	perror("lseek");
	memset(buffer, 0, sizeof(buffer));
	length = read(fd, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\t length:%d\n", buffer, length);
	for (i = 0 ; i < length; i++)
		printf("buffer[%d]:\t%c\n", i, buffer[i]);
	memset(buffer, 0, sizeof(buffer));
	length = read(fd, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\tlength:%d\n", buffer, length);
	close(fd);
}
```


### Creating multiple device nodes

In our previous program, we created a single device, let's modify the code to create multiple device nodes for example: 5 device nodes 

While allocating the device numbers, we need to specify the number of minor devices in the count argument:

```
int alloc_chrdev_region (dev_t *   dev,  unsigned  baseminor, unsigned  count, const char * name);
```

We need to create an array of struct cdev, and register each of the cdev with one minor number.

So for creating 5 device nodes, the parameter `count` must be 5. 

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define MAX_DEVICES     5

int base_minor = 0;
char *device_name = "msg";
int count = MAX_DEVICES;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev[MAX_DEVICES];

#define MAX_SIZE (1024)
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

static loff_t device_lseek(struct file *file, loff_t offset, int orig)
{
        loff_t new_pos = 0;

        switch(orig) {
                case 0 : /*seek set*/
                        new_pos = offset;
                        break;
                case 1 : /*seek cur*/
                        new_pos = file->f_pos + offset;
                        break;
                case 2 : /*seek end*/
                        new_pos = MAX_SIZE - offset;
                        break;
        }
        if(new_pos > MAX_SIZE)
                new_pos = MAX_SIZE;
        if(new_pos < 0)
                new_pos = 0;
        file->f_pos = new_pos;
        return new_pos;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek
};

static int test_hello_init(void)
{
	int i = 0;
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {       // count = MAX_DEVICES = 5 
		int major = MAJOR(devicenumber);                                         // for each device number 
		printk("Device number registered\n");
		printk("Major number received:%d\n", major);
		for (i = 0; i < MAX_DEVICES; i++) {
			dev_t tmp_device = MKDEV(major, i);
			device = device_create(class, NULL, tmp_device, NULL, "%s%d", device_name, i);
			cdev_init(&mycdev[i], &device_fops);
			mycdev[i].owner = THIS_MODULE;
			cdev_add(&mycdev[i], tmp_device, 1);
		}

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	int major = MAJOR(devicenumber);
	int i = 0;
	dev_t tmp_device;
	for (i = 0; i < MAX_DEVICES; i++) {                  // removing all the device nodes
		tmp_device = MKDEV(major, i);
		device_destroy(class, tmp_device);
		cdev_del(&mycdev[i]);
	}
	
	class_destroy(class);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

To check the number of device's drivers created:

```bash
ls /dev/msg* -al
```

remember to enable the access rights:

```bash
sudo chmod 666 /dev/msg*
```

The program:

```C
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buffer[50];	
	int fd1, fd2;
	int length;
	int i = 0;

	fd1 = open("/dev/msg1", O_RDWR);
	if (fd1 < 0) {
		perror("fd1 failed");
		exit(2);
	}

	fd2 = open("/dev/msg2", O_RDWR);
	if (fd2 < 0) {
		perror("fd2 failed");
		exit(2);
	}

	printf("write : %d\n", write(fd1, "hello world", sizeof("hello world")));	
	lseek(fd2, 0, SEEK_SET);
	perror("lseek");
	memset(buffer, 0, sizeof(buffer));
	length = read(fd2, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\t length:%d\n", buffer, length);
	close(fd1);
	close(fd2);
}
```

The execution of this program, shows that if the device 1 is written, it is possible to read it from the device 2, and 
that is not what is intended, the goal is that each device has its own data section.

### container_of macro

 - reference: https://radek.io/2012/11/10/magical-container_of-macro/
 - reference: http://www.kroah.com/log/linux/container_of.html
 - reference: https://www.oreilly.com/library/view/linux-device-drivers/9781785280009/de059d89-b6c5-4dc8-8569-f7de37d98b62.xhtml
   
 - definition: https://elixir.bootlin.com/linux/v6.7.5/source/tools/include/linux/kernel.h#L35

```
#ifndef container_of
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof(((type *)0)->member) * __mptr = (ptr);	\
	(type *)((char *)__mptr - offsetof(type, member)); })
#endif
```

`container_of` macro is the macro you see almost in most of driver code. Search of "container_of" macro in drivers folder of Linux Source code gave more than 10 k results.

#### What is the use of container_of macro?
Given a structure having many members. The container_of macro will give the address of the structure when you pass the address of one of the member variable of that structure.

```C
({ void *__mptr = (void *)(ptr);
((type *)(__mptr - offsetof(type, member))); })
```
To understand these two lines of the macro, we need to get familiar with the following concepts:
 - typeof()
 - offsetof()
 - Compound Statements

1. `typeof()`: It is a very useful operator helpful to find out the type of the argument at run time. Using typeof we can write a simple macro which can work for multiple types. For example the swap function defined in kernel.h

```c
/*
 * swap - swap value of @a and @b
 */
#define swap(a, b) \
    do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)
```

2. `offsetof(type, member)`: The `offsetof()` returns the offset of the field member from the start of structure type

This is useful as the size of the members of the structure can differ across different architectures (x86, x86_64) and sometimes compiler also adds some padding for performance.


3. Compound Statements:
  
Compound statements is a sequence of statements surrounded by braces. Parentheses also go around these braces.

The last line in the compound statement should be an expression followed by a semicolon. The value of the expression serves as the value of the compound statement.
`container_of` is also a compound statement, the value of `((type *)(__mptr - offsetof(type, member)));` will be the return value of macro.

One example of how to use it:

```c
#include <stdio.h>

#define offsetof(TYPE, MEMBER)	((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member)	({	\
						const typeof ( ((type *)0)->member) *__mptr = (ptr); \
						(type *)( (char *)__mptr - offsetof(type, member));})

struct test
{
	int member1;
	float member2;
};

int main()
{
	struct test t1;
	float *ptr = &t1.member2;
	printf("Address of t1:\t\t%p\n", &t1);
	printf("Address of t1 container_method:\t\t%p\n", 
			container_of(ptr, struct test, member2));
	return 0;
}
```

### Adding support for private data

A new structure for each device data will be created:

```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define MAX_DEVICES (5)

int base_minor = 0;
char *device_name = "msg";
int count = MAX_DEVICES;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
#define MAX_SIZE (1024)
struct msg_device                     // THIS NEW STRUCTURE IS USED TO KEEP THE PRIVATE DATA OF EACH DEVICE NODE
{
	struct cdev mycdev;
	char kernel_buffer[MAX_SIZE];
};

static struct msg_device msg_devices[MAX_DEVICES];  // AN ARRAY OF THOSE STRUCTURES IS CREATED TO KEEP THE DATA PRIVATE

int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	// IN THE OPENING WE RETRIEVE THE ADDECUATE STRUCTURE, WITH THE CONTAINER_OF MACRO
        // FROM THE inode->i_cdev IT IS POSIBLE TO GET THE BASE ADDRESS OF THE GIVEN DEVICE
        // AND THEN LATER ACCESS THE kernel_buffer
	struct msg_device *my_device = container_of(inode->i_cdev, struct msg_device, mycdev);
	file->private_data = my_device;

	pr_info("%s\n", __func__);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	struct msg_device *my_device = (struct msg_device *)file->private_data;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, my_device->kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;
	struct msg_device *my_device = (struct msg_device *)file->private_data;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(my_device->kernel_buffer+*offset,  
				user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, my_device->kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

static loff_t device_lseek(struct file *file, loff_t offset, int orig)
{
        loff_t new_pos = 0;

        switch(orig) {
                case 0 : /*seek set*/
                        new_pos = offset;
                        break;
                case 1 : /*seek cur*/
                        new_pos = file->f_pos + offset;
                        break;
                case 2 : /*seek end*/
                        new_pos = MAX_SIZE - offset;
                        break;
        }
        if(new_pos > MAX_SIZE)
                new_pos = MAX_SIZE;
        if(new_pos < 0)
                new_pos = 0;
        file->f_pos = new_pos;
        return new_pos;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek
};

static int test_hello_init(void)
{
	int i = 0;
	class = class_create(THIS_MODULE, "myclass");

	if (!alloc_chrdev_region(&devicenumber, base_minor, count, device_name)) {
		int major = MAJOR(devicenumber);
		printk("Device number registered\n");
		printk("Major number received:%d\n", major);
		for (i = 0; i < MAX_DEVICES; i++) {
			dev_t tmp_device = MKDEV(major, i);
			device = device_create(class, NULL, tmp_device, NULL, "%s%d", device_name, i);
			cdev_init(&msg_devices[i].mycdev, &device_fops);
			msg_devices[i].mycdev.owner = THIS_MODULE;
			cdev_add(&msg_devices[i].mycdev, tmp_device, 1);
		}

	}
	else
		printk("Device number registration Failed\n");

	return 0;
}

static void test_hello_exit(void)
{
	int major = MAJOR(devicenumber);
	int i = 0;
	dev_t tmp_device;
	for (i = 0; i < MAX_DEVICES; i++) {
		tmp_device = MKDEV(major, i);
		device_destroy(class, tmp_device);
		cdev_del(&msg_devices[i].mycdev);
	}
	
	class_destroy(class);
	unregister_chrdev_region(devicenumber, count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

And the program:

```c
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buffer[50];	
	int fd1, fd2;
	int length;
	int i = 0;

	fd1 = open("/dev/msg1", O_RDWR);
	if (fd1 < 0) {
		perror("fd1 failed");
		exit(2);
	}

	fd2 = open("/dev/msg2", O_RDWR);
	if (fd2 < 0) {
		perror("fd2 failed");
		exit(2);
	}

	printf("write : %d\n", write(fd1, "hello world", sizeof("hello world")));	
	lseek(fd2, 0, SEEK_SET);
	perror("lseek");
	memset(buffer, 0, sizeof(buffer));
	length = read(fd2, buffer, sizeof(buffer));
	buffer[length] = '\0';
	printf("Read:%s\t length:%d\n", buffer, length);
	close(fd1);
	close(fd2);
}
```

### What happens when write is call from user-space

Let's see what happens when a user-space application calls write on a device file, for example in our previous program we wrote our own null device: /dev/my_null

So, we execute write using: `echo "Hello" > /dev/my_null`

Userspace internally calls GLibC write call which calls write System Call.

Step1: Write system call in kernel is executed which is present in `fs/read_write.c`, which calls `ksys_write`.

Step2:  The `fd` passed by user is an index in the file descriptor table present in the kernel, `fdget_pos` fetches the struct `fd` of the particular file

```
struct fd {
    struct file *file;
    unsigned int flags;
};

static inline loff_t file_pos_read(struct file *file)
{
    return file->f_pos;
}
```
This position extracts the offset within the file, and calls `vfs_write`, and then the return value of write call is updated with offset

Step 3: In `vfs_write`,

	 - It checks whether the file was opened in read-only mode
	 - Checks whether this file has write method
	 - Whether the passed user buffer is a valid buffer for reading
	 - Verifies the area for writing is valid and for security permissions
	 - And calls `__vfs_write` 

Step 4: Finally in `__vfs_write`, it calls our write function present in the `fops` (struct file_operations) present in the struct file.

So, this is the way, even if we pass only three arguments from user space, kernel reads the offset from the file and pass it to our write function defined in our driver.


## ioctl (Input output Control)

IOCTL is referred as Input and Output Control

Device files are supposed to represent physical devices.

Most physical devices are used for output as well as input. We have write and read system calls for input and output.

This is not always enough.

The major use of this is in case of handling some specific operations of a device for which the kernel does not have a system call by default.

Examples:
1. Ejecting the media from a “cd” drive,
2. change the Baud Rate of Serial port
3. Adjust the Volume
4. Reading or Writing device registers


The system call `ioctl()` is provided for device-specific custom commands (such as format, reset and shutdown) that are not provided by standard system calls such as read(), write

```
int ioctl(int fd, unsigned long request, ...);
```

Every device can have its own ioctl commands, which can be

 - read ioctl's (to send information from a process to the kernel)
 - write ioctl's (to return information to a process)
 - both or neither

See `ioctl_list(2)` for a list of  many  of  the  known `ioctl()` calls.

 - reference: https://linux.die.net/man/2/ioctl_list
 - reference: https://linux.die.net/man/2/ioctl


```c
#include <sys/ioctl.h>
int ioctl(int d, int request, ...);
```

The ioctl() function manipulates the underlying device parameters of special files. In particular, many operating characteristics of character special files (e.g., terminals) may be controlled with ioctl() requests. The argument d must be an open file descriptor.
The second argument is a device-dependent request code. The third argument is an untyped pointer to memory. It's traditionally char *argp (from the days before void * was valid C), and will be so named for this discussion.

An ioctl() request has encoded in it whether the argument is an in parameter or out parameter, and the size of the argument argp in bytes. Macros and defines used in specifying an ioctl() request are located in the file <sys/ioctl.h>.

#### ioctl example - BLKGETSIZE

On Linux-based systems the size of a block special device can be obtained using the ioctl request BLKGETSIZE.

It returns the device size as a number of 512-byte blocks

```C
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main()
{
	// get the block size of the /dev/sda1 (first hard drive)
	int fd;
	unsigned long num_blocks;

	fd = open("/dev/sda1", O_RDONLY);
	perror("fd");

	//0x00001260   BLKGETSIZE            unsigned long *
	ioctl(fd, 0x00001260,	&num_blocks);
	perror("ioctl");
	printf("Number of blocks: %lu, this makes %.3f GB\n",
	 num_blocks,
	 (double)num_blocks * 512.0 / (1024 * 1024 * 1024));
	close(fd);
	return 0;
}
```

BLKGETSIZE ioctl returns unsigned long , it may fail if the size is 2TB or greater. 

For this reason it is better to use BLKGETSIZE64  which produces a 64-bit result which is the size in bytes
```c
Header File: <linux/fs.h>
```

```c
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <stdint.h>

int main()
{
	int fd;
	uint64_t size;

	fd = open("/dev/sda1", O_RDONLY);
	perror("fd");

	ioctl(fd, BLKGETSIZE64,	&size);
	perror("ioctl");
	printf("Size %ld GB\n",  (size)/ (1024 * 1024 * 1024));
	close(fd);
	return 0;
}
```

### ioctl driver method

The ioctl driver method has a prototype that differs somewhat from the user space version:

```c
long (*unlocked_ioctl) (struct file *filp, unsigned int cmd, unsigned long arg);
```

The `filp` pointer is the value corresponding to the file descriptor `fd` passed on by the application and is the same parameters to the open method.

The `cmd` argument is passed from the user unchanged, and the optional `arg` argument is passed in the form of an unsigned long

So in the char device driver example, it would be: 

```c
long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	pr_info("%s: Cmd:%u\t Arg:%lu\n", __func__, cmd, arg);

	return 0;
}
```


```c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	pr_info("%s: Cmd:%u\t Arg:%lu\n", __func__, cmd, arg);

	return 0;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.unlocked_ioctl = device_ioctl	
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

remember to enable the access rights:

```bash
sudo chmod 666 /dev/msg*
```

And the program in user-space:

```c
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>

int main()
{
	int fd;

	fd = open("/dev/msg", O_RDWR);
	perror("fd");

	ioctl(fd, 0x01, 10);
	perror("ioctl");
	getchar();

	ioctl(fd, 0x01);
	perror("ioctl");
	getchar();
	close(fd);
	return 0;
}
```

### Adding serveral ioctl in the driver

Most ioctl implementations consist of a big switch statement that selects the correct behavior according to the cmd argument.

```c
long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	pr_info("%s: Cmd:%u\t Arg:%lu\n", __func__, cmd, arg);

	switch(cmd)
	{
		//Get Length of buffer
		case 0x01:
			pr_info("Get Buffer Length\n");
			put_user(MAX_SIZE, (unsigned int *)arg);
			break;
		//clear buffer
		case 0x02:
			pr_info("Clear buffer\n");
			memset(kernel_buffer, 0, sizeof(kernel_buffer));
			break;
		//fill character
		case 0x03:
			get_user(ch, (unsigned char *)arg);
			pr_info("Fill Character:%c\n", ch);
			memset(kernel_buffer, ch, sizeof(kernel_buffer));
			buffer_index = sizeof(kernel_buffer);
			break;
		default:
			pr_info("Unknown Command:%u\n", cmd);
			return -EINVAL;
	}
	return 0;
}
```

And the application could be like: 


```c
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    char buffer[1024];	
	int fd;
	unsigned int length;
	unsigned char ch = 'A';
	int i = 0;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}
	//Get Length  - 0x01
	ioctl(fd, 0x01, &length);
	printf("Length:%u\n", length);
	//Set Character - 0x03
	ioctl(fd, 0x03, &ch);
	perror("ioctl");
	lseek(fd, 0, SEEK_SET);
	perror("lseek");
	length = read(fd, buffer, 1024);
	perror("Read");
	printf("length:%d\n", length);
	buffer[1023] = '\0';
	printf("Buffer:%s\n", buffer);
	close(fd);
}
```

### Symbolic names to ioctl commands

Symbolic names are given to numeric values of commands to simplify coding.

These symbols are usually declared in header files. 

User space programs must of course, needs to include the header to access those symbols


```c
#ifndef __IOCTL_CMD_H
#define __IOCTL_CMD_H

#define MSG_IOCTL_GET_LENGTH	0x01

#define MSG_IOCTL_CLEAR_BUFFER	0x02

#define MSG_IOCTL_FILL_BUFFER	0x03

#endif
```

And the ioctl function would be:

```c

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	pr_info("%s: Cmd:%u\t Arg:%lu\n", __func__, cmd, arg);

	switch(cmd)
	{
		//Get Length of buffer
		case MSG_IOCTL_GET_LENGTH:
			pr_info("Get Buffer Length\n");
			put_user(MAX_SIZE, (unsigned int *)arg);
			break;
		//clear buffer
		case MSG_IOCTL_CLEAR_BUFFER:
			pr_info("Clear buffer\n");
			memset(kernel_buffer, 0, sizeof(kernel_buffer));
			break;
		//fill character
		case MSG_IOCTL_FILL_BUFFER:
			get_user(ch, (unsigned char *)arg);
			pr_info("Fill Character:%c\n", ch);
			memset(kernel_buffer, ch, sizeof(kernel_buffer));
			buffer_index = sizeof(kernel_buffer);
			break;
		default:
			pr_info("Unknown Command:%u\n", cmd);
			return -EINVAL;
	}
	return 0;
}
```

And the program in user-space would be: 

```c
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ioctl_cmd.h"

int main(int argc, char *argv[])
{
    char buffer[1024];	
	int fd;
	unsigned int length;
	unsigned char ch = 'A';
	int i = 0;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}
	//Get Length  - 0x01
	ioctl(fd, MSG_IOCTL_GET_LENGTH, &length);
	printf("Length:%u\n", length);
	//Set Character - 0x03
	ioctl(fd, MSG_IOCTL_FILL_BUFFER, &ch);
	perror("ioctl");
	lseek(fd, 0, SEEK_SET);
	perror("lseek");
	length = read(fd, buffer, 1024);
	perror("Read");
	printf("length:%d\n", length);
	buffer[1023] = '\0';
	printf("Buffer:%s\n", buffer);
	close(fd);
}
```


### Defining ioctl() commands

 - Reference: https://docs.kernel.org/userspace-api/ioctl/ioctl-number.html

Programmers much choose a number for the integer command representing each command implemented through `ioctl`.

Normally many programmers choose a set of small numbers starting with 0 or 1 and go up from there.

Picking arbitrary number is a bad idea, because:
 - Two device nodes may have the same major number
 - An application could open more than one device and mix up the file descriptors,  thereby sending the right command to the wrong device.
 - Sending wrong ioctl commands can have catastrophic consequences, including damage to hardware.

Example: Program might find itself trying to change the baud rate of non-serial port input stream, such as FIFO or an audio device.

To help programmers create unique ioctl command codes, `ioctl` codes have been divided into four bitfields.

1. type/magic number:
	
	8 - bit Wide
	Choose one number after looking into  Documentation/ioctl-number.txt and use it throughout the driver

2. number:
	8-bits wide. Sequential number you assign to your command

3. direction:
	Direction of data transfer. Possible values:
```
		_IOC_NONE(NO Data Transfer)
		_IOC_READ 	--> Reading from the device, driver must write into userspace
		_IOC_WRITE
		_IOC_READ|_IOC_WRITE
```
5. size:

	Size of the user data involved.
	Width depends on the architecture: usually 13 or 14 bits
	You can find its value for your specific architecture in the macro `_IOC_SIZEBITS`

```
Header File: <linux/ioctl.h>
```

This above header file defines macro that help set up the command numbers as follows:

 - reference: https://docs.kernel.org/userspace-api/ioctl/ioctl-number.html
   
```
_IO(type, nr) (for a command that has no argument)
_IOR(type, nr, datatype) (for reading data from the driver)
_IOW(type, nr, datatype) (for writing data to the driver)
_IOWR(type, nr, datatype) (for bidirectional data transfer)
```

Type and number fields are passed as arguments and size field is derived by applying sizeof to the datatype argument.

```C
#include <stdio.h>
#include <linux/ioctl.h>

#define MAGIC_NUMBER1	'l'
#define MAGIC_NUMBER2	'i'

int main()
{
	printf("IO(MAGIC_NUMBER1, 1):%x\n", _IO(MAGIC_NUMBER1, 1));
	printf("IO(MAGIC_NUMBER2, 1):%x\n", _IO(MAGIC_NUMBER2, 1));

	getchar();
	printf("IO(MAGIC_NUMBER1, 2):%x\n", _IO(MAGIC_NUMBER1, 2));
	printf("IO(MAGIC_NUMBER2, 2):%x\n", _IO(MAGIC_NUMBER2, 2));
	
	getchar();
	printf("IOR(MAGIC_NUMBER1, 2, int):%lx\n", _IOR(MAGIC_NUMBER1, 2, int));
	printf("IOR(MAGIC_NUMBER2, 2, int):%lx\n", _IOR(MAGIC_NUMBER2, 2, int));

	getchar();

	printf("IOR(MAGIC_NUMBER1, 3, int):%lx\n", _IOR(MAGIC_NUMBER1, 3, int));
	printf("IOR(MAGIC_NUMBER2, 3, int):%lx\n", _IOR(MAGIC_NUMBER2, 3, int));

	getchar();
	printf("IOWR(MAGIC_NUMBER2, 3, int):%lx\n", _IOWR(MAGIC_NUMBER2, 4, int));
	return 0;

}
```

### Macros to decode information from the ioctl command

```C
_IOC_TYPE(cmd) /* gets the magic number of the device this command targets */

_IOC_NR( cmd) /* gets the sequential number of the command within your device */

_IOC_SIZE(cmd) /* gets the size of the data structure */

_IOC_DIR( cmd) /* gets the direction of data transfer,
                                can be one of the following:
                                _IOC_NONE
                                _IOC_READ
                                _IOC_WRITE
                                _IOC_READ | _IOC_WRITE
                                */
```

Example:

```C
#include <stdio.h>
#include <linux/ioctl.h>

#define MAGIC_NUMBER1	'l'

#define CMD1 _IO(MAGIC_NUMBER1, 1)
#define CMD2 _IOW(MAGIC_NUMBER1, 2, int)
#define CMD3 _IOWR(MAGIC_NUMBER1, 3, char)

void printDirection(unsigned int cmd)
{
	switch(_IOC_DIR(cmd))
	{
		case _IOC_NONE:
			printf("_IOC_NONE\n");
			break;
		case _IOC_READ:
			printf("_IOC_READ\n");
			break;
		case _IOC_WRITE:
			printf("_IOC_WRITE\n");
			break;
		case _IOC_READ | _IOC_WRITE:
			printf("_IOC_READ | _IOC_WRITE\n");
			break;
	}
}

int main()
{
	printf("Number:%u\n", _IOC_NR(CMD1));
	printf("Number:%lu\n", _IOC_NR(CMD2));
	printf("Number:%lu\n", _IOC_NR(CMD3));

	printf("Magic Number:%u\n", _IOC_TYPE(CMD1));
	printf("Magic Number:%lu\n", _IOC_TYPE(CMD2));
	printf("Magic Number:%lu\n", _IOC_TYPE(CMD3));

	printf("Size:%u\n", _IOC_SIZE(CMD1));
	printf("Size:%lu\n", _IOC_SIZE(CMD2));
	printf("Size:%lu\n", _IOC_SIZE(CMD3));
	
	printDirection(CMD1);
	printDirection(CMD2);
	printDirection(CMD3);

	return 0;
}
```

### Updating the driver with the ioctl macros

```C
#ifndef __IOCTL_CMD_H
#define __IOCTL_CMD_H

#define MSG_MAGIC_NUMBER    0x21

#define MSG_IOCTL_GET_LENGTH    _IOR(MSG_MAGIC_NUMBER, 1, unsigned int)

#define MSG_IOCTL_CLEAR_BUFFER  _IO(MSG_MAGIC_NUMBER, 2)

#define MSG_IOCTL_FILL_BUFFER   _IOW(MSG_MAGIC_NUMBER, 3, unsigned char)

#define MSG_IOCTL_MAX_CMDS      3

#endif
```

```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include "ioctl_cmd.h"

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE (1024)
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;
	
	pr_info("bytes_to_read:%d\n", bytes_to_read);

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

static loff_t device_lseek(struct file *file, loff_t offset, int orig)
{
        loff_t new_pos = 0;

        switch(orig) {
                case 0 : /*seek set*/
                        new_pos = offset;
                        break;
                case 1 : /*seek cur*/
                        new_pos = file->f_pos + offset;
                        break;
                case 2 : /*seek end*/
                        new_pos = MAX_SIZE - offset;
                        break;
        }
        if(new_pos > MAX_SIZE)
                new_pos = MAX_SIZE;
        if(new_pos < 0)
                new_pos = 0;
        file->f_pos = new_pos;
        return new_pos;
}

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	pr_info("%s: Cmd:%u\t Arg:%lu\n", __func__, cmd, arg);

	switch(cmd)
	{
		//Get Length of buffer
		case MSG_IOCTL_GET_LENGTH:
			pr_info("Get Buffer Length\n");
			put_user(MAX_SIZE, (unsigned int *)arg);
			break;
		//clear buffer
		case MSG_IOCTL_CLEAR_BUFFER:
			pr_info("Clear buffer\n");
			memset(kernel_buffer, 0, sizeof(kernel_buffer));
			break;
		//fill character
		case MSG_IOCTL_FILL_BUFFER:
			get_user(ch, (unsigned char *)arg);
			pr_info("Fill Character:%c\n", ch);
			memset(kernel_buffer, ch, sizeof(kernel_buffer));
			buffer_index = sizeof(kernel_buffer);
			break;
		default:
			pr_info("Unknown Command:%u\n", cmd);
			return -EINVAL;
	}
	return 0;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek,
	.unlocked_ioctl = device_ioctl	
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

And the program in user-land:

```C
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <sys/ioctl.h>
#include "ioctl_cmd.h"

int main(int argc, char *argv[])
{
    	char buffer[1024];	
	int fd;
	unsigned int length;
	unsigned char ch = 'A';
	int i = 0;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}
	//Get Length  - 0x01
	ioctl(fd, MSG_IOCTL_GET_LENGTH, &length);
	printf("Length:%u\n", length);
	//Set Character - 0x03
	ioctl(fd, MSG_IOCTL_FILL_BUFFER, &ch);
	perror("ioctl");
	lseek(fd, 0, SEEK_SET);
	perror("lseek");
	length = read(fd, buffer, 1024);
	perror("Read");
	printf("length:%d\n", length);
	buffer[1023] = '\0';
	printf("Buffer:%s\n", buffer);
	close(fd);
}
```


### Return Value in case an incorrect ioctl number is given

What should be the return value when invalid command is passed?

Acording to the POSIX Standard, if an inappropriate ioctl command has  been issued , then -ENOTTY should be returned.

```
ENOTTY -  Inappropriate IOCTL For the device
```

So the function would be: 

```C

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	pr_info("%s: Cmd:%u\t Arg:%lu\n", __func__, cmd, arg);

	if (_IOC_TYPE(cmd) != MSG_MAGIC_NUMBER) return -ENOTTY;
	if (_IOC_NR(cmd) > MSG_IOCTL_MAX_CMDS) return -ENOTTY;

	switch(cmd)
	{
		//Get Length of buffer
		case MSG_IOCTL_GET_LENGTH:
			pr_info("Get Buffer Length\n");
			put_user(MAX_SIZE, (unsigned int *)arg);
			break;
		//clear buffer
		case MSG_IOCTL_CLEAR_BUFFER:
			pr_info("Clear buffer\n");
			memset(kernel_buffer, 0, sizeof(kernel_buffer));
			break;
		//fill character
		case MSG_IOCTL_FILL_BUFFER:
			get_user(ch, (unsigned char *)arg);
			pr_info("Fill Character:%c\n", ch);
			memset(kernel_buffer, ch, sizeof(kernel_buffer));
			buffer_index = sizeof(kernel_buffer);
			break;
		default:
			pr_info("Unknown Command:%u\n", cmd);
			return -ENOTTY;
	}
	return 0;
}
```

### access_ok


We need to take care of the `arg` parameter in the `ioctl` function, as it is a user space.

We can use `copy_from_user`/`copy_to_user` to safely copy data from user to kernel and vice versa.

These functions are less efficient in case of copying small data items. You can use `put_user`/`get_user` for copying 1, 2, 4 or 8 bytes

If you only want to verify the address without transferring data, you can use the macro `access_ok`

There is a macro known as `acess_ok`

The `access_ok()` checks ensure that the userspace application isn't asking the kernel to read from or write to kernel addresses (they're an integrity/security check). Just because a pointer was supplied by userspace doesn't mean that it's definitely a userspace pointer - in many cases "kernel pointer" simply means that it's pointing within a particular region of the virtual address space.

Additionally, calling `access_ok()` with `VERIFY_WRITE` implies `VERIFY_READ`, so if you check the former you do not need to also check the latter.

The `access_ok` macro is just a quick check for the probable validity of the pointer. For example, it would catch mistaken calls with NULL or read-only arguments.

Ideally, the driver should recover even if later the access functions fail. This could however happen only after some expensive hardware operations. Therefore checking early may make the driver more robust against the most common user-space programmer errors.

- reference: https://stackoverflow.com/questions/12357752/what-is-the-point-of-using-the-linux-macro-access-ok

```
Header File: <asm/uaccess.h>

int access_ok(int type, void *addr, unsigned long size);
```

 - type: VERIFY_READ/VERIFY_WRITE: depending on action: reading the user space memory or writing it
 - addr: user space address
 - size: Depends on the ioctl command.

If you need to both read and write, use `VERIFY_WRITE`, it is a superset of `VERIFY_READ`.

Return value: `1` for success, `0` for failure in this case you should return `-EFAULT`.

Note: The 5.0 kernel dropped the type argument to `access_ok()`

 - reference: https://lkml.org/lkml/2019/1/4/418


### Updated driver with the access_ok() macro

```c
#ifndef __IOCTL_CMD_H
#define __IOCTL_CMD_H

#define MSG_MAGIC_NUMBER    0x21
#define MSG_IOCTL_GET_LENGTH    _IOR(MSG_MAGIC_NUMBER, 1, unsigned int)
#define MSG_IOCTL_CLEAR_BUFFER  _IO(MSG_MAGIC_NUMBER, 2)
#define MSG_IOCTL_FILL_BUFFER   _IOW(MSG_MAGIC_NUMBER, 3, unsigned char)
#define MSG_GET_ADDRESS		_IOR(MSG_MAGIC_NUMBER, 4, unsigned long long)
#define MSG_IOCTL_MAX_CMDS      4

#endif
```


```C
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include "ioctl_cmd.h"

int base_minor = 0;
char *device_name = "msg";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

#define MAX_SIZE        1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
        return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer,
                      size_t read_count, loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;

	pr_info("%s read offset:%lld\n", __func__, *offset);
	 available_space = MAX_SIZE - *(offset);

	if (read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;
	
	pr_info("bytes_to_read:%d\n", bytes_to_read);

	if (bytes_to_read == 0) {
		pr_err("%s: No available space in the buffer for reading\n",
				__func__);
		return -ENOSPC;
	}

	if (buffer_index > *offset)
                bytes_to_read = buffer_index - *offset;
        else
                return 0;


	bytes_read = bytes_to_read - copy_to_user(user_buffer, kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: Copy to user returned:%d\n", __func__, bytes_to_read);

	//update file offset
	*offset += bytes_read;

        return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer,
                       size_t write_count, loff_t *offset)
{
	int bytes_written;
	int available_space;
	int bytes_to_write;

	pr_info("%s write offset:%lld\n", __func__, *offset);
	available_space = MAX_SIZE - *(offset);

	if (write_count < available_space)
		bytes_to_write = write_count;
	else
		bytes_to_write = available_space;

	if (bytes_to_write == 0) {
		pr_err("%s: No available space in the buffer for writing\n",
				__func__);
		return -ENOSPC;
	}

	bytes_written = bytes_to_write - copy_from_user(kernel_buffer+*offset,  user_buffer, bytes_to_write);
	pr_info("%s: Bytes written:%d\n", __func__, bytes_written);
	pr_info("%s: kernel_buffer:%s\n", __func__, kernel_buffer);

	//update file offset
	*offset += bytes_written;
	buffer_index += bytes_written;
        return bytes_written;
}

static loff_t device_lseek(struct file *file, loff_t offset, int orig)
{
        loff_t new_pos = 0;

        switch(orig) {
                case 0 : /*seek set*/
                        new_pos = offset;
                        break;
                case 1 : /*seek cur*/
                        new_pos = file->f_pos + offset;
                        break;
                case 2 : /*seek end*/
                        new_pos = MAX_SIZE - offset;
                        break;
        }
        if(new_pos > MAX_SIZE)
                new_pos = MAX_SIZE;
        if(new_pos < 0)
                new_pos = 0;
        file->f_pos = new_pos;
        return new_pos;
}

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	int retval = 0;
	long size = _IOC_SIZE(cmd);

	pr_info("%s: Cmd:%u\t Arg:%lu Size:%lu add:%p\n", __func__, cmd, arg, size, &ch);

	if (_IOC_TYPE(cmd) != MSG_MAGIC_NUMBER) return -ENOTTY;
	if (_IOC_NR(cmd) > MSG_IOCTL_MAX_CMDS) return -ENOTTY;

	//Achtung! access_ok is kernel-oriented, so the concept of read and write is reversed
	
	retval = access_ok((void __user *)arg, size);

	pr_info("access_ok returned:%d\n", retval);
	if (!retval)
		return -EFAULT;

	switch(cmd)
	{
		//Get Length of buffer
		case MSG_IOCTL_GET_LENGTH:
			pr_info("Get Buffer Length\n");
			put_user(MAX_SIZE, (unsigned int *)arg);
			break;
		//clear buffer
		case MSG_IOCTL_CLEAR_BUFFER:
			pr_info("Clear buffer\n");
			memset(kernel_buffer, 0, sizeof(kernel_buffer));
			break;
		//fill character
		case MSG_IOCTL_FILL_BUFFER:
			get_user(ch, (unsigned char *)arg);
			pr_info("Fill Character:%c\n", ch);
			memset(kernel_buffer, ch, sizeof(kernel_buffer));
			buffer_index = sizeof(kernel_buffer);
			break;
		//address of kernel buffer
		case MSG_GET_ADDRESS:
			put_user(&kernel_buffer, (unsigned long long*)arg);
			pr_info("MSG_GET_ADDRESS\n");
			break;
		default:
			pr_info("Unknown Command:%u\n", cmd);
			return -ENOTTY;
	}
	return 0;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek,
	.unlocked_ioctl = device_ioctl	
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

user-land program:

```c
#include <sys/ioctl.h>
#include "ioctl_cmd.h"

int main(int argc, char *argv[])
{
    char buffer[1024];	
	int fd;
	unsigned int length;
	unsigned char ch = 'A';
	int i = 0;
	unsigned long long ptr ;

	fd = open("/dev/msg", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}

	ioctl(fd, MSG_GET_ADDRESS, &ptr);
	printf("%llx\n", ptr);
	perror("ioctl");
	getchar();

	ioctl(fd, MSG_GET_ADDRESS, ptr);  // this will fail the access_ok: Bad Address - access_ok returns 0. Because a kernel pointer was passed.
	perror("ioctl");
	getchar();

	//Get Length  - 0x01
	ioctl(fd, MSG_IOCTL_GET_LENGTH, &length);
	printf("Length:%u\n", length);
	//Set Character - 0x03
	ioctl(fd, MSG_IOCTL_FILL_BUFFER, &ch);
	perror("ioctl");
	lseek(fd, 0, SEEK_SET);
	perror("lseek");
	length = read(fd, buffer, 1024);
	perror("Read");
	printf("length:%d\n", length);
	buffer[1023] = '\0';
	printf("Buffer:%s\n", buffer);
	ioctl(fd, 4);
	perror("ioctl");
	close(fd);
}
```


You can use `__put_user`/`__get_user` if access_ok has already being called. This will save few cycles.

```c
#define put_user(x, ptr)                                        \
({                                                              \
        void __user *__p = (ptr);                               \
        might_fault();                                          \
        access_ok(__p, sizeof(*ptr)) ?          \
                __put_user((x), ((__typeof__(*(ptr)) __user *)__p)) :   \
                -EFAULT;                                        \
})

#define get_user(x, ptr)                                        \
({                                                              \
        const void __user *__p = (ptr);                         \
        might_fault();                                          \
        access_ok(__p, sizeof(*ptr)) ?          \
                __get_user((x), (__typeof__(*(ptr)) __user *)__p) :\
                ((x) = (__typeof__(*(ptr)))0,-EFAULT);          \
})
```

### COMPACT_IOCTL

`compat_ioctl()` Its purpose is to allow 32-bit userland programs to make ioctl calls on a 64-bit kernel. The meaning of the last argument to ioctl depends on the driver, so there is no way to do a driver-independent conversion.

 - reference: https://unix.stackexchange.com/questions/4711/what-is-the-difference-between-ioctl-unlocked-ioctl-and-compat-ioctl


To generate a 32bit application in a 64 bit machine, use the flag `-m32` when compiling: 

```
gcc myprogram -o myprogram -m32
```

use : `file myprogram` to verify the ELF type.

Need to install when compiling for 32 bit in 64 bit machine
```
$ sudo apt-get install g++-multilib
```

```
long (*compat_ioctl) (struct file *filp, unsigned int cmd, 
                          unsigned long arg);
```

Called when a 32-bit process calls ioctl() on a 64-bit system

It should then do whatever is required to convert the argument to native data types and carry out the request.

So the function should be udpated to: 

```c
struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek,
	.unlocked_ioctl = device_ioctl,      /* for 64 bits */
	.compat_ioctl = device_ioctl         /* for 32 bits calls*/
};
```

### Sending a signal from module to process

The function for doing this is
```
int send_sig(int signal, struct task_struct *task, int priv);
```

 - signal: Signal to send
 - task: Corresponds to task_struct corresponding to the process
 - priv: 0 for user applications, 1 for kernel

```c
#ifndef __IOCTL_CMD_H
#define __IOCTL_CMD_H

#define SIG_MAGIC_NUMBER (0x21)
#define SIG_IOCTL_SET_PID    _IOW(SIG_MAGIC_NUMBER, 1, unsigned int)
#define SIG_IOCTL_SET_SIGNAL  _IOW(SIG_MAGIC_NUMBER, 2, unsigned int)
#define SIG_IOCTL_SEND_SIGNAL   _IO(SIG_MAGIC_NUMBER, 3)
#define SIG_IOCTL_MAX_CMDS (3)

#endif
```

```c

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <linux/sched/signal.h>
#include "ioctl_cmd.h"

int base_minor = 0;
char *device_name = "sig";
int count = 1;
dev_t devicenumber;

static struct class *class = NULL;
static struct device *device = NULL;
static struct cdev mycdev;

static int sig_pid = 0;
static struct task_struct *sig_tsk = NULL;
static int sig_tosend = SIGKILL;

#define MAX_SIZE (1024)
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

long device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	int retval = 0;
	long size = _IOC_SIZE(cmd);

	pr_info("%s: Cmd:%u\t Arg:%lu Size:%lu add:%p\n", __func__, cmd, arg, size, &ch);

	if (_IOC_TYPE(cmd) != SIG_MAGIC_NUMBER) return -ENOTTY;
	if (_IOC_NR(cmd) > SIG_IOCTL_MAX_CMDS) return -ENOTTY;

	//access_ok is kernel-oriented, so the concept of read and write is reversed
	
	retval = access_ok((void __user *)arg, size);

	pr_info("access_ok returned:%d\n", retval);
	if (!retval)
		return -EFAULT;

	switch(cmd)
	{
		//Get Length of buffer
		case SIG_IOCTL_SET_PID:
			pr_info("SIG_IOCTL_SET_PID\n");
			get_user(sig_pid, (unsigned int *)arg);
			pr_info("PID:%d\n", sig_pid);
			sig_tsk = pid_task(find_vpid(sig_pid), PIDTYPE_PID);
			break;
		//clear buffer
		case SIG_IOCTL_SET_SIGNAL:
			pr_info("SIG_IOCTL_SET_SIGNAL\n");
			get_user(sig_tosend, (unsigned int *)arg);
			pr_info("signal:%d\n", sig_tosend);
			break;
		//fill character
		case SIG_IOCTL_SEND_SIGNAL:
			pr_info("SIG_IOCTL_SEND_SIGNAL\n");
			if (!sig_tsk) {
                        pr_info("You haven't set the pid; using current\n");
                        	sig_tsk = current;
                        	sig_pid = (int)current->pid;
                	}
			retval = send_sig(sig_tosend, sig_tsk, 0);
			pr_info("retval = %d\n", retval);
			break;
		default:
			pr_info("Unknown Command:%u\n", cmd);
			return -ENOTTY;
	}
	return 0;
}


struct file_operations device_fops = {
	.open = device_open,
	.release = device_release,
	.unlocked_ioctl = device_ioctl,
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

the user-land program:

```c
#include <stdio.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <unistd.h>
#include "ioctl_cmd.h"

void signal_handler(int sig)
{
	printf("Signal Received\n");
}

int main(int argc, char *argv[])
{
	int fd;
	pid_t pid = getpid();
	int snd_signal = SIGUSR1;

	printf("PROCESS PID:%d\n", pid);

	signal(SIGUSR1, signal_handler);
	fd = open("/dev/sig", O_RDWR);
	if (fd < 0) {
		perror("fd failed");
		exit(2);
	}

	ioctl(fd, SIG_IOCTL_SET_PID, &pid);
	ioctl(fd, SIG_IOCTL_SET_SIGNAL, &snd_signal);
	ioctl(fd, SIG_IOCTL_SEND_SIGNAL);
	perror("ioctl");
	getchar();

	close(fd);
}
```


## Some interesting directories related to character drivers

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















