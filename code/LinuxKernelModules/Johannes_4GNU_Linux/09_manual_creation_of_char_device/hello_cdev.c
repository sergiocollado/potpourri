// reference: https://youtu.be/mQAVmM9GpI0
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

static dev_t dev_nr; // this structure will have the major and minor number
static struct cdev my_cdev;

static ssize_t my_read (struct file *f, char __user *u, size_t l, loff_t *o)
{
	pr_info(" Read is called\n");
	return 0;
}

static struct file_operations fops = {
	.read = my_read
};

int __init my_init(void)
{
	int status;
#ifdef STATIC_DEVNR
	dev_nr = STATIC_DEVNR;
	status = register_chrdev_region(dev_nr, MINORMASK + 1, "hello_cdev");
#else
	status = alloc_chrdev_region(&dev_nr, 0, MINORMASK + 1, "hello_cdev");
#endif
	if (status) {
		pr_err(" Error reserving the region of dev numbers");
		return status;
	}

	cdev_init(&my_cdev, &fops);
	my_cdev.owner = THIS_MODULE;

	status = cdev_add(&my_cdev, dev_nr, MINORMASK + 1);
	if (status) {
		pr_err(" Error adding cdev\n");
		goto free_devnr;
	}

	pr_info(" registered a character device for major %d starting with minor %d\n", MAJOR(dev_nr), MINOR(dev_nr));

	return 0;

free_devnr:
	unregister_chrdev_region(dev_nr, MINORMASK +1);
	return status;
}

void __exit my_exit(void)
{
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev_nr, MINORMASK +1);
	pr_info(" Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("A sample driver for manually registering a character device");


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
 *  >cat /dev/hello0
 *  this should report an error, because the read operation have not been
 *  defined.
 *  after that remove /dev/hello0 manually. (with 'rm' ... it is just a file)
 */
