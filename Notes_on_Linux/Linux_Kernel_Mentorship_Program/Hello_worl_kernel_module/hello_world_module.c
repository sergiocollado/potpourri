// SPDX-License-Identifier: GPL-2.0+

#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void)
{
    pr_info("Hello World!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Bye World!\n");
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sergio Gonzalez Collado");
MODULE_DESCRIPTION("Simple Hello World! module");
