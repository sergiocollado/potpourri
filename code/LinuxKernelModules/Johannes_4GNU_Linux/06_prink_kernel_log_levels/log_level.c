#include<linux/module.h>
#include<linux/init.h>
// reference: https://docs.kernel.org/core-api/printk-basics.html
//
// to check the log levels:
//
// `cat /proc/sys/kernel/printk`
//
// The result shows the current, default, minimum and boot-time-default log levels.
//
// To change the current console_loglevel simply write the desired level to
// /proc/sys/kernel/printk. For example, to print all messages to the console:
//
// `# echo 8 > /proc/sys/kernel/printk`
//
// Another way, using dmesg:
//
// `# dmesg -n 5`
//
// Besides being more concise than the equivalent printk() calls, they can use
// a common definition for the format string through the pr_fmt() macro.
// For instance, defining this at the top of a source file (before
// any #include directive):
//
// `#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__`

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

int __init my_init(void)
{
	printk(KERN_INFO "log_level - this is info\n");
	printk(KERN_WARNING "log_level - this is a warning\n");
	printk(KERN_ALERT "log_level - this is an alert\n");
	printk(KERN_DEBUG "log_level - this is a debug message\n");
	return 0;
}

void __exit my_exit(void)
{
	pr_emerg("log_level - Module is unloaded\n");
	pr_err("log_level - error\n");
	pr_info("log_level - the last info ...\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("A simple hello kernel module showing logging levels");


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
