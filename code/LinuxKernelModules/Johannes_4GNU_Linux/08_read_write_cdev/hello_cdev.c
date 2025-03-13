// reference: https://youtu.be/vYx63d2xuzM
// SPDX-License-Identifier: GPL-2.0 
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

static int major;  // store the major device number
static char text[64];

static ssize_t my_read (struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	//__user: is an attribute that signals that the parameter comes
	//from user space, and thus it cannot be trusted (it could be
	//a null pointer), it has to be checked
	//
	//len: it is the size of the buffer.
	//
	//off: a pointer to the current file offset (position of the "cursor")
	//this offset has to be incresed by the amount the characters written
	//in the device.

	int not_copied, delta;
	int to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

	printk("Read is called, we want to read %ld  bytes, but actually only copying %d bytes. The offest is %lld\n", len, to_copy, *off);

	if (*off >= sizeof(text))
		return 0;

	not_copied = copy_to_user(user_buf, &text[*off], to_copy);
	delta = to_copy - not_copied;
	if (not_copied)
		pr_warn("Could only copy %d bytes\n", delta);

	*off += delta;  //update the offset

	return delta;
}

static ssize_t my_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	int not_copied, delta;
	int to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

	printk("Write is called, we want to write %ld  bytes, but actually only copying %d bytes. The offest is %lld\n", len, to_copy, *off);

	if (*off >= sizeof(text))
		return 0;

	not_copied = copy_from_user(&text[*off], user_buf, to_copy);
	delta = to_copy - not_copied;
	if (not_copied)
		pr_warn("Could only copy %d bytes\n", delta);

	*off += delta;

	return delta;
}

static struct file_operations fops = {
	.read = my_read,
	.write = my_write
};

int __init my_init(void)
{
	major = register_chrdev(0, "hello_cdev", &fops);
	// creates a char device, and links the device numbers to it.
	// 0 will check for a free major device number and take it
	// &fops is a pointer to the file's operations in that char dev.
	// as fops is empty, this char dev will not support any file operation
	if (major < 0) {
		printk("Error registering chrdev\n");
		return major;
	}
	printk("Major device number: %d\n", major);
	return 0;
}

void __exit my_exit(void)
{
	unregister_chrdev(major, "hello cdev");
	printk(" - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("A sample driver for registering a character device");


/* to check the logs run: sudo dmesg -WH &
 * to compile the module: make
 * to load the module: sudo insmod hello.ko
 * to read the module information check: modinfo hello.ko
 * to check the module symbols: nm hello.ko
 * to check if the module is loaded: lsmod | grep hello
 * to remove the module: rmmod hello
 * to insert a module with all its dependencies of other modules use: modprobe
 *   for example: sudo modprobe industrialio
 *   to be able use modprobe the module must be in /lib/modules folder
 *
 *  Once you insmod the module, and the chrdev is registered, you can use
 *  the reported number in dmesg for creating a chrdev with 'mknod'.
 *  'mknod' stands for 'make node'
 *  >sudo mknod /dev/hello0 c <major> 0
 *  then its is possible to try to read from it, with the command:
 *  >sudo cat /dev/hello0
 *  after that remove /dev/hello0 manually.> $sudo rm /dev/hello0
 */
