#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GLP");

static int hello_init(void)
{
	printk(KERN_ALERT "Hello World!");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Good bye!");
}

module_init(hello_init);
module_exit(hello_exit);

//ref: https://lwn.net/Kernel/LDD3/
//ref: https://www.youtube.com/watch?v=juGNPLdjLH4
