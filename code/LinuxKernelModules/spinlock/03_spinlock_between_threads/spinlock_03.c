#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>

unsigned int counter; /* shared data: */
DEFINE_SPINLOCK(counter_lock);
struct task_struct *read_thread, *write_thread;

static int writer_function(void *data)
{
	while(!kthread_should_stop()) {
		spin_lock(&counter_lock);	// start of critical section
		counter++;
		spin_unlock(&counter_lock);	// end of critical section
		msleep(500);
	}
	//do_exit(0);
	return 0;
}

static int read_function(void *data)
{
	while(!kthread_should_stop()) {
		spin_lock(&counter_lock);	// start of critical section
		pr_info("counter: %d\n", counter);
		spin_unlock(&counter_lock);	// end of critical section
		msleep(500);
	}
	//do_exit(0);
	return 1;
}

static int __init my_mod_init(void)
{
	pr_info("Entering module.\n");
	counter = 0;

	read_thread = kthread_run(read_function, NULL, "read-thread");
	write_thread = kthread_run(writer_function, NULL, "write-thread");

	return 0;
}

static void __exit my_mod_exit(void)
{
	kthread_stop(read_thread);
	kthread_stop(write_thread);
	pr_info("Exiting module.\n");
}

module_init(my_mod_init);
module_exit(my_mod_exit);

MODULE_LICENSE("GPL");
