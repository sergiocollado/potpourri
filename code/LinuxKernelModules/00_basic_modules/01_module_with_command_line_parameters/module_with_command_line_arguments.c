// SPDX-License-Identifier: GPL-2.0+

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

static short int myshort = 1;
static int myint = 42;
static long int mylong = 999999;
static char *mystring = "Hey there!";
static int myintarray[2] = { 42, 42 };
static int arr_argc = 0;
static bool mybool = true;

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");
module_param(mybool, bool, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(mybool, "A boolean value");

module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init test_arguments_init(void)
{
	pr_info("\nModule arguments test:\n=====================\n");
	pr_info("myshort is a short integer: %hd\n", myshort);
	pr_info("myint is an integer: %d\n", myint);
	pr_info("mylong is a long integer: %ld\n", mylong);
	pr_info("mystring is a string: %s\n", mystring);
	pr_info("myboolean is %s\n", mybool ? "true":"false");

	for (int i = 0; i < ARRAY_SIZE(myintarray); i++)
		pr_info("myintarray[%d] = %d\n", i, myintarray[i]);

	pr_info("got %d arguments for myintarray.\n", arr_argc);
	return 0;
}

static void __exit test_arguments_exit(void)
{
	pr_info("removing module arguments test\n");
}

module_init(test_arguments_init);
module_exit(test_arguments_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sergio Gonzalez Collado");
MODULE_DESCRIPTION("Kernel module with command line arguments");
