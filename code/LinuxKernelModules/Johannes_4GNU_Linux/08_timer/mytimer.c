// reference: https://embetronicx.com/tutorials/linux/device-drivers/using-kernel-timer-in-linux-device-driver/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/gpio.h>
#include<linux/jiffies.h>
#include<linux/timer.h>

/** variable for timer **/
static struct timer_list mytimer;

void timer_callback(struct timer_list *data) {
	pr_info("tick\n");
}

int __init my_init(void)
{
	printk("hello - Hello kernel!\n");

	/* initialize the timer*/
	timer_setup(&mytimer, timer_callback, 0);
	mod_timer(&mytimer, jiffies + msecs_to_jiffies(1000));
	// jiffies is a variable defined in the kernel that keeps the number
	// of system ticks from the startup depending on your system clock.
	return 0;
}

void __exit my_exit(void)
{
	/* delete the timer*/
	del_timer(&mytimer);
	printk("hello - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple test LKM's timer	");


/* to check the logs run: sudo dmesg -WH &
 * to compile the module: make
 * to load the module: sudo insmod hello.ko
 * to read the module information check: modinfo hello.ko
 * to check the module symbols: nm hello.ko
 * to check if the module is loaded: lsmod | grep hello
 * to remove the module: rmmod hello
 * to insert a module with all its dependencies of other modules use: modprobe
 *   for example: sudo modprobe <your_module_name>
 *   to be able use modprobe the module must be in /lib/modules folder
 */
