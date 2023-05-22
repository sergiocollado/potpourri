#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwlock_types.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

DEFINE_RWLOCK(mylock);
static struct task_struct *thread1, *thread2, *thread3; // define 3 threads

int counter = 0; // this will be the global shared resource

static int write_threadfn(void *arg)
{
	while(!kthread_should_stop() && counter < 100)
	{
		pr_info("processor:%d trying to acquire write lock\n", smp_processor_id());
		write_lock(&mylock); // the write_lock() will wait till all the read_locks are released.
		pr_info("processor:%d acquired write lock\n", smp_processor_id());
		counter++;
		mdelay(100);   // mdelay makes a busy waits (loops around)
		write_unlock(&mylock);
		pr_info("processor:%d released write lock\n", smp_processor_id());
	}
	return 0;
}

static int read_threadfn(void *arg)
{
	while(!kthread_should_stop() && counter <= 100)
	{
		pr_info("processor:%d trying to acquire read lock\n", smp_processor_id());
		read_lock(&mylock);
		pr_info("processor:%d acquired read lock\n", smp_processor_id());
		pr_info("processor:%d\t counter:%d\n", smp_processor_id(), counter);
		mdelay(150);   // mdelay makes a busy waits (loops around)
		read_unlock(&mylock);
		pr_info("processor:%d releasing read lock\n", smp_processor_id());
	}
	return 0;
}

static int __init test_hello_init(void)
{
    thread1 = kthread_run(read_threadfn, NULL, "thread1");
    thread2 = kthread_run(read_threadfn, NULL, "thread2");
    thread3 = kthread_run(write_threadfn, NULL, "thread3");

    return 0;
}

static void __exit test_hello_exit(void)
{
	//pr_info("read lock test module removed\n");
	kthread_stop(thread1);
	kthread_stop(thread2);
	kthread_stop(thread3);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
