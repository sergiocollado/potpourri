// reference: https://www.opensourceforu.com/2011/01/understanding-a-kernel-oops/

/*
An “Oops” is what the kernel throws at us when it finds something faulty, or an exception,
in the kernel code. It’s somewhat like the segfaults of user-space. An Oops dumps its message
on the console; it contains the processor status and the CPU registers of when the fault
occurred. The offending process that triggered this Oops gets killed without releasing locks
or cleaning up structures. The system may not even resume its normal operations sometimes;
this is called an unstable state. Once an Oops has occurred,
the system cannot be trusted any further.
**/

#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 
 
static void create_oops() { 
        *(int *)0 = 0; 
} 
 
static int __init my_oops_init(void) { 
        printk("oops from the module\n"); 
        create_oops(); 
       return (0); 
} 
static void __exit my_oops_exit(void) { 
        printk("Goodbye world\n"); 
} 
 
module_init(my_oops_init); 
module_exit(my_oops_exit);
