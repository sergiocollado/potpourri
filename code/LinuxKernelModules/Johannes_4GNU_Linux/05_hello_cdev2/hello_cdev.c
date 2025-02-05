#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

static int major;
static struct file_operations fops = {};

int __init my_init(void)
{
	major = register_chrdev(0, "hello cdev", &fops);
	// 0 will check for a free major device number and take it
	if (major < 0) {
		printk("hello_cdev - Error registering chrdev\n");
		return major;
	}
	printk("hello_cdev - Major device number: %d\n", major);
	return 0;
}

void __exit my_exit(void)
{
	unregister_chrdev(major, "hello cdev");
	printk("hello - Goodbye, kernel!\n");
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
 *  the reported number in dmesg for creating a chrdev with 'mkmod'.
 *  >sudo mkmod /dev/hello0 <major> 0
 *  then its is possible to try to read from it, with the command:
 *  >cat /dev/hello0
 *  this should report an error, because the read operation have not been
 *  defined.
 *  after that remove /dev/hello0 manually.
 */
