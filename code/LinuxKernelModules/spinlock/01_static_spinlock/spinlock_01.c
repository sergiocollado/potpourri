#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");

DEFINE_SPINLOCK(my_lock);

static int __init test_hello_init(void)
{
    spin_lock(&my_lock);
    pr_info("Starting critical region\n");
    pr_info("Ending critical region\n");
    spin_unlock(&my_lock);
    return -1;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
