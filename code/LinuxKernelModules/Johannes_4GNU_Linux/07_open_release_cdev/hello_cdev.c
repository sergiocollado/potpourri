#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

static int major;  // store the major device number

static int my_open(struct inode *inode, struct file *filp)
{
// inode is a struct to represent a file.
// over this strcut we can retrieve the major and minor number of the opened
// device file
	pr_info("hello_cdev: - Major: %d, Minor: %d\n", imajor(inode), iminor(inode));
// the struct file represents an opened file.
//  - The field 'f_mode' represents the permissions given to the file.
//  - The field 'f_op' is a pointer to the struct f_ops that defines the files operations of that file.
//  - The field 'f_flags' are the flags that have been pased by the 'open' function
//       in user space, nevertheless the recomended way is to access to this by the 'f_mode'.
//  - The field '(void) *private_data' is in case you want to associate data with this file.
//      (like for allocating memory for a given file)
//  - The field 'loff_t f_pos' gives the current position in the opened file

	pr_info("hello_cdev: - filp->f_pos: %lld\n", filp->f_pos);
	pr_info("hello_cdev: - filp->f_mode: 0x%x\n", filp->f_mode);
	pr_info("hello_cdev: - filp->f_flags: 0x%x\n", filp->f_flags);

	return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
	pr_info("hello_cdev: - file is closed\n");
	return 0;
}

static ssize_t my_read (struct file *f, char __user *u, size_t l, loff_t *o)
{
	pr_info("hello cdev - Read is called\n");
	return 0;
}

static struct file_operations fops = {
	.read = my_read,
	.open = my_open,
	.release = my_release
};

int __init my_init(void)
{
	major = register_chrdev(0, "hello cdev", &fops);
	// creates a char device, and links the device numbers to it.
	// 0 will check for a free major device number and take it
	// &fops is a pointer to the file's operations in that char dev.
	// as fops is empty, this char dev will not support any file operation
	if (major < 0) {
		printk("hello_cdev - Error registering chrdev\n");
		return major;
	}
	pr_info("hello_cdev - Major device number: %d\n", major);
	return 0;
}

void __exit my_exit(void)
{
	unregister_chrdev(major, "hello cdev");
	pr_info("hello - Goodbye, kernel!\n");
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
 *  >cat /dev/hello0
 *  this should report an error, because the read operation have not been
 *  defined.
 *  after that remove /dev/hello0 manually.
 */
