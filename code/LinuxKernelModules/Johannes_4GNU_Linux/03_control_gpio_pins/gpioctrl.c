#include<linux/module.h>
#include<linux/init.h>
#include<linux/gpio/consumer.h>

// reference: https://www.youtube.com/watch?v=7eY6NTIdReg&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa&index=4

// this is only for raspberry pi
// raspberry pi pinout: https://pinout.xyz/
// check the giio with: 'gpiodetect' command
// we can check the gpio's of the system in '/sys/class/gpio'.
//
// no device tree used here, is too much at the moment.
// this module has a downside, it only allows to control the led,
// while the module is being loaded. :/ 

static struct gpio_desc *led, *button;

#define IO_LED 21
#define IO_BUTTON 20

#define IO_OFFSET 0

int my_init(void)
{
	int status;

	printk("hello - Hello kernel!\n");
	led = gpio_to_desc(IO_LED + IO_OFFSET);
	if (!led) {
		printk("gpioctrl - Error getting pin 21\n");
		return -ENODEV;
	}

	button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
	if (!button) {
		printk("gpioctrl - Error getting pin 20\n");
		return -ENODEV;
	}

	status = gpiod_direction_input(led, 0);
	if (status) {
		printk("gpioctrl - Error setting pin 20 output\n");
		return -status;
	}

	status = gpiod_direction_input(button);
	if (status) {
		printk("gpioctrl - Error setting pin 21 output\n");
		return -status;
	}

	gpiod_set_value(led, 1);
	printk("gpioctrl button is %s pressed\n", gpiod_get_value(button) ? ""  : "not");
	return 0;
}

void my_exit(void)
{
	// set the led to 0
	gpiod_set_value(led, 0);

	printk("hello - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("An example for using GPIOs without the device tree");

/* to check the logs run: sudo dmesg -WH &
 * to compile the module: make
 * to load the module: sudo insmod hello.ko
 * to read the module information check: modinfo hello.ko
 * to check the module symbols: nm hello.ko
 * to check if the module is loaded: lsmod | grep hello
 * to remove the module: rmmod hello
 * to insert a module with all its dependencies of other modules use: modprobe
 *   for example: sudo modprobe industrialio
 *   to be able use modprobe the module must be in /lib/modules folder
 */
