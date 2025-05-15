// reference: https://youtu.be/yPbcUeOjOSY
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/slab.h>

#define pr_fmt(fmt) "%s:%s: " fmt, KBUILD_MODNAME, __func__

static dev_t dev_nr; // this structure will have the major and minor number
static struct cdev my_cdev;
static struct class *my_class;

#define MEMSIZE 64

static int my_open(struct inode *inode, struct file *filp)
{
	pr_info("file is open\n");
	filp->private_data = kmalloc(MEMSIZE, GFP_KERNEL);
	// for an atomic context, use GFP_ATOMIC
	// for DMA applications, use GFP_DMA (it allocates continous memory)

	if (!filp->private_data)
	{
		pr_err("Out of memory\n");
		return -ENOMEM;
	}

	return 0;
}

static int my_release(struct inode *inode, struct file *filp)
{
	pr_info("file is closed\n");
	kfree(filp->private_data); // release the allocated memory
	return 0;
}

static ssize_t my_read (struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	char *text = filp->private_data;
	int not_copied, delta;
	int to_copy = (len + *off) < MEMSIZE ? len : (MEMSIZE - *off);

	printk("Read is called, we want to read %ld  bytes, but actually only copying %d bytes. The offest is %lld\n", len, to_copy, *off);

	if (*off >= sizeof(text))
		return 0;

	not_copied = copy_to_user(&text[*off], user_buf, to_copy);
	delta = to_copy - not_copied;
	if (not_copied)
		pr_warn("Could only copy %d bytes\n", delta);

	*off += delta;  //update the offset

	return delta;
}

static ssize_t my_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	char *text = filp->private_data;
	int not_copied, delta;
	int to_copy = (len + *off) < MEMSIZE ? len : (MEMSIZE - *off);

	printk("Write is called, we want to write %ld  bytes, but actually only copying %d bytes. The offest is %lld\n", len, to_copy, *off);

	if (*off >= sizeof(text))
		return 0;

	not_copied = copy_from_user(&text[*off], user_buf, to_copy);
	delta = to_copy - not_copied;
	if (not_copied)
		pr_warn("Could only copy %d bytes\n", delta);

	*off += delta;

	return delta;
}

static struct file_operations fops = {
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
	.llseek = default_llseek, // this is provided by the kernel
};

int __init my_init(void)
{
	int status;
#ifdef STATIC_DEVNR
	dev_nr = STATIC_DEVNR;
	status = register_chrdev_region(dev_nr, MINORMASK + 1, "hello_cdev");
#else
	status = alloc_chrdev_region(&dev_nr, 0, MINORMASK + 1, "hello_cdev");
#endif
	if (status) {
		pr_err(" Error reserving the region of dev numbers\n");
		return status;
	}

	cdev_init(&my_cdev, &fops);
	my_cdev.owner = THIS_MODULE;

	status = cdev_add(&my_cdev, dev_nr, MINORMASK + 1);
	if (status) {
		pr_err(" Error adding cdev\n");
		goto free_devnr;
	}

	pr_info(" registered a character device for major %d starting with minor %d\n", MAJOR(dev_nr), MINOR(dev_nr));

	// create the class
	my_class = class_create(THIS_MODULE, "my_class");
	// class-create: https://elixir.bootlin.com/linux/v3.4/source/drivers/base/class.c#L249
	// class-create: https://elixir.bootlin.com/linux/v3.4/source/include/linux/device.h#L450
	if (!my_class) {
		pr_err(" Could not create class my_class\n");
		status = ENOMEM;
		goto delete_cdev;
	}

	// create the device
	if (!device_create(
			my_class,
			NULL /*parent device*/,
			dev_nr /*device number*/,
			NULL /*additional data*/,
			"hello%d" /*device name*/,
			0/*%d*/
		)) {
		pr_err("Could not create device hello0\n");
		status = ENOMEM;
		goto delete_class;
	}

	pr_info(" Created device under /sys/class/my_class/hello0\n");


	return 0;

delete_class:
	class_unregister(my_class);
	class_destroy(my_class);
delete_cdev:
	cdev_del(&my_cdev);

free_devnr:
	unregister_chrdev_region(dev_nr, MINORMASK +1);
	return status;
}

void __exit my_exit(void)
{
	device_destroy(my_class, dev_nr);
	class_unregister(my_class);
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev_nr, MINORMASK +1);
	pr_info(" Goodbye, kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4Linux");
MODULE_DESCRIPTION("A sample driver for manually registering a character device");


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

/*
sergio@laptop: cd /sys
sergio@laptop:/sys$ ls
block  bus  class  dev  devices  firmware  fs  hypervisor  kernel  module  power
sergio@laptop:/sys$ cd class/
sergio@laptop:/sys/class$ ls
accel          dma_heap        intel_scu_ipc  nvme-generic    rc            tpmrm
ata_device     dmi             iommu          nvme-subsystem  regulator     tty
ata_link       drm             kfd            pci_bus         remoteproc    usb_role
ata_port       drm_dp_aux_dev  leds           pci_epc         rfkill        vc
backlight      extcon          lirc           phy             rtc           video4linux
bdi            firmware        mdio_bus       powercap        scsi_device   virtio-ports
block          gpio            mem            power_supply    scsi_disk     vtconsole
bluetooth      graphics        misc           ppdev           scsi_generic  wakeup
bsg            hidraw          mmc_host       ppp             scsi_host     watchdog
devcoredump    hwmon           msr            pps             sound         wmi_bus
devfreq        i2c-adapter     my_class       printer         spi_master
devfreq-event  i2c-dev         nd             ptp             spi_slave
devlink        ieee80211       net            pwm             thermal
dma            input           nvme           rapidio_port    tpm
sergio@laptop:/sys/class$ cd my_class/
sergio@laptop:/sys/class/my_class$ ls
hello0
sergio@laptop:/sys/class/my_class$ cd hello0
sergio@laptop:/sys/class/my_class/hello0$ ls
dev  power  subsystem  uevent
sergio@laptop:/sys/class/my_class/hello0$ cd dev
-bash: cd: dev: Not a directory
sergio@laptop:/sys/class/my_class/hello0$ cat dev
511:0
sergio@laptop:/sys/class/my_class/hello0$ # those are the major and minor dev numbers
sergio@laptop:/sys/class/my_class/hello0$
sergio@laptop:/sys/class/my_class/hello0$ ls -lh /dev/hello0
crw------- 1 root root 511, 0 abr 13 12:14 /dev/hello0
# there are the mayor  VVV, V  and minor number again

 * */
