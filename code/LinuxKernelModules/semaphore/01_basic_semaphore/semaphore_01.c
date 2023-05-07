#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct semaphore *mysem;

static int __init test_hello_init(void)
{
    mysem = kmalloc(sizeof(mysem), GFP_KERNEL);
    sema_init(mysem, 4); // as 4 is given as initial value this is a 
			 // counting semaphore, if the initial value
			 // was 1 it would be a binary semaphore
    pr_info("semaphore count:%d\n", mysem->count);
    down(mysem);
    pr_info("semaphore count:%d\n", mysem->count);
    pr_info("Starting critical region\n");
    pr_info("Ending critical region\n");
    up(mysem);
    pr_info("semaphore count:%d\n", mysem->count);
    return -1;  // this will make fail the module installation
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
