// reference: https://youtu.be/RZuL-j5qXg0?list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
// the latest way to do it is: https://youtu.be/m_dmlwFCBS4
#include<linux/module.h>
#include<linux/init.h>
#include<linux/spi/spi.h>

#define MY_BUS_NUM 0
static struct spi_device *bmp280_dev;

int __init my_init(void)
{
	struct spi_master *master;
	u8 id;
	u8 val[] = {0x75, 0x40};

	// Parameters for SPI device
	struct spi_board_info spi_device_info = {
		.modalias = "bmp280",
		.max_speed_hz = 1000000,
		.bus_num = MY_BUS_NUM,
		.chip_select = 0,
		.mode = 3,
	};

	printk("hello - Hello kernel!\n");


	// get access to the spi bus
	master = spi_busnum_to_master(MY_BUS_NUM); //IN NEW KERNEL THIS FUCTION DOESN'T EXIST ANY MORE!!
	// Check if we could get the master
	if (!master) {
		pr_err("There is not spi bus with Nr: %d\n", MY_BUS_NUM);
		return -1;
	}

	// Create new spi device
	bmp280_dev = spi_new_device(master, &spi_device_info);
	if(!bmp280_dev) {
		pr_err("There is not spi bus with Nr: %d\n", MY_BUS_NUM);
		return -1;
	}

	bmp280_dev->bits_per_word = 8;

	// Setup the bus for device's parameters
	if (spi_setup(bmp280_dev) != 0) {
		pr_err("Could not change bus setup\n");
		spi_unregister_device(bmp280_dev);
		return -1;
	}

	// Read chip Id
	id = spi_w8r8(bmp280_dev, 0xD0);
	pr_info("Chip id: 0x%x\n", id);

	// Write to config reg
	spi_write(bmp280_dev, val, sizeof(8));
	id = spi_w8r8(bmp280_dev, 0xF5);
	pr_info("Config Reg. value: 0x%x\n", id);

	return 0;
}

void __exit my_exit(void)
{
	if (bmp280_dev)
		spi_unregister_device(bmp280_dev);

	printk("hello - Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("A simple LKM ple LKM to read and write some registers of a BMP280 sensor");


/* to check the logs run: sudo dmesg -WHT &
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
