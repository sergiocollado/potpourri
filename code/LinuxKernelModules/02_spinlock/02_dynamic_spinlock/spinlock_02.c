#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/slab.h>  // to use kmalloc

MODULE_LICENSE("GPL");

spinlock_t *my_lock;

static int __init test_hello_init(void)
{
    my_lock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
    spin_lock_init(my_lock);    // run time initializing the spin lock.
    spin_lock(my_lock);
    pr_info("Starting critical region\n");
    pr_info("Ending critical region\n");
    spin_unlock(my_lock);
    kfree(my_lock);
    return -1;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
