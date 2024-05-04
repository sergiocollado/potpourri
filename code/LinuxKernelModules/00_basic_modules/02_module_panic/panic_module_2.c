// SPDX-License-Identifier: GPL-2.0+

/*
 * panic_module.c -- A Kernel module that panics the kernel
 * NOTE: Running the following code, WILL CRASH YOUR SYSTEM. An easy poweroff poweron should fix it though
 */

#include<linux/init.h>
#include<linux/module.h>
#include<linux/panic.h>
#include<linux/delay.h>

static int __init panic_module_init(void)
{
	int *p = (int*)NULL;
	int y;

	pr_info("Panic Module Init.\n");

	/* giving a chance to log the previous message */
	msleep(1000);

	/* Panic the kernel by dereferencing a NULL pointer.
	* Note that, this would only cause an OOPS. To panic the kernel on OOPS
	* you would also have to set `CONFIG_PANIC_ON_OOPS=y` and set the
	* `CONFIG_PANIC_ON_OOPS_VALUE=1`.
	*/
	y = *p;

	pr_info("Panic module: %d\n", y);

	return 0;
}

static void __exit panic_module_cleanup(void)
{
	pr_info(": Panic Module Cleanup.\n");
}

module_init(panic_module_init);
module_exit(panic_module_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sergio Gonzalez Collado");
MODULE_DESCRIPTION("A Kernel Module to panic te kernel");
