#include<linux/module.h>
#include<linux/init.h>

int my_init(void)
{
	printk("hello - Hello kernel!\n");
	return 0; // returns 0 means the funtion worked as expected (no error)
}

void my_exit(void)
{
	printk("hello - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
