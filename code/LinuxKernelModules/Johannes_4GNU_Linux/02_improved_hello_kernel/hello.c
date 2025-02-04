#include<linux/module.h>
#include<linux/init.h>

int __init my_init(void)
{
	printk("hello - Hello kernel!\n");
	return 0;
}

void __exit my_exit(void)
{
	printk("hello - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("A simple hello kernel module");


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
 */
