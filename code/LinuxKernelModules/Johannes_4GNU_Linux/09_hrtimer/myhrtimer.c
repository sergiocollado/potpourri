// reference: https://docs.kernel.org/timers/hrtimers.html
#include<linux/module.h>
#include<linux/init.h>
#include<linux/jiffies.h>
#include<linux/hrtimer.h>

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

/** variable for hr timer **/
static struct hrtimer my_hrtimer;
u64 start_t;

static enum hrtimer_restart test_hrtimer_handler(struct hrtimer *timer) {
	// get current time
	u64 now_t = jiffies;
	pr_info("start_t - now_t = %u\n", jiffies_to_msecs(now_t - start_t));
	return HRTIMER_NORESTART;
}

int __init my_init(void)
{
	printk("hello - Hello kernel!\n");

	/* initialize the timer*/
	hrtimer_init(&my_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	my_hrtimer.function = &test_hrtimer_handler;
	start_t = jiffies;
	hrtimer_start(&my_hrtimer, ms_to_ktime(100), HRTIMER_MODE_REL);
	return 0;
}

void __exit my_exit(void)
{
	/* delete the timer*/
	hrtimer_cancel(&my_hrtimer);
	printk(" - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple test LKM's using hrtimer");


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
