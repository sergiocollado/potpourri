#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwlock_types.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

DEFINE_RWLOCK(mylock);

static int __init test_hello_init(void)
{
    pr_info("trying to get the read lock once\n");
    read_lock(&mylock);
    pr_info("Acquired read lock once\n");
    msleep(2000);
    pr_info("trying to get the read lock twice\n");
    read_lock(&mylock);
    pr_info("Acquired read lock twice\n");
    msleep(2000);
    pr_info("Unlocking read lock once\n");
    read_unlock(&mylock);
    pr_info("Unlocking read lock twice\n");
    read_unlock(&mylock);
    return -1;
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
