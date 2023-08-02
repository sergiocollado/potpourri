// reference: https://stackoverflow.com/questions/26077140/how-to-test-your-own-linux-module

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <asm-generic/uaccess.h>

#define MY_BUFFER_SIZE   (1024 * 10)
#define MY_CHRDEV_MAJOR  217
#define MY_CHRDEV_MINOR  0

static struct cdev my_cdev;
static unsigned char *my_buf;
static dev_t my_dev = MKDEV(MY_CHRDEV_MAJOR, MY_CHRDEV_MINOR);

ssize_t my_read(struct file *file, char __user * buf, size_t count, loff_t * ppos)
{
    int size;

    size = MY_BUFFER_SIZE - 100 - (int)*ppos;
    if (size > count)
        size = count;

    if (copy_to_user(buf, my_buf + *ppos, count))
        return -EFAULT;

    *ppos += size;
    return size;
}

ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    int size;

    size = MY_BUFFER_SIZE - 100 - (int)*ppos;
    if (size > count)
        size = count;

    if (copy_from_user(my_buf + *ppos, buf, count))
        return -EFAULT;

    *ppos += size;
    return size;
}

long my_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk ("%s!\n", __FUNCTION__);
    return 0;
}

int my_mmap(struct file *f, struct vm_area_struct *vma)
{
    printk ("%s!\n", __FUNCTION__);
    return 0;
}
int my_open(struct inode *i, struct file *f)
{
    printk ("%s!\n", __FUNCTION__);
    return 0;
}
int my_release(struct inode *i, struct file *f)
{
    printk ("%s!\n", __FUNCTION__);
    return 0;
}

struct file_operations my_fops =
{
    .owner =   THIS_MODULE,
    .read =    &my_read,
    .write =   &my_write,
    .unlocked_ioctl = &my_unlocked_ioctl,
    .mmap =    &my_mmap,
    .open =    &my_open,
    .release = &my_release,
};


static int __init my_module_init(void)
{
    int line = 0;
    unsigned char *pos;

    printk ("%s!\n", __FUNCTION__);
    my_buf = (unsigned char *)kzalloc(MY_BUFFER_SIZE, 0);
    if (my_buf == NULL) {
        printk("%s - failed to kzallocate buf!\n", __FUNCTION__);
        return -1;
    }
    pos = my_buf;
    while (pos - my_buf < MY_BUFFER_SIZE - 100) {
        sprintf(pos, "Line #%d\n", line++);
        pos += strlen(pos);
    }
    cdev_init(&my_cdev, &my_fops);
    if (register_chrdev_region(my_dev, 1, "my_dev")) {
        pr_err("Failed to allocate device number\n");
    }
    cdev_add(&my_cdev, my_dev, 1);
    printk ("%s - registered chrdev\n", __FUNCTION__);
    return 0;
}

static void __exit my_module_exit(void)
{
    printk ("my_module_exit.\n");
    unregister_chrdev_region(my_dev, 1);
    return;
}
module_init(my_module_init);
module_exit(my_module_exit);
MODULE_LICENSE("GPL");

/**

A basic kernel module would normally include registering a character device. Simple imlementation requires:

Register chrdev region with specific major & minor.
Allocate file operations structure and implement the basic read / write APIs.
Initialize and register character device with the file operations structure to the major / minor region.
See the following code snippet as a template of a module (only read / write APIs are imlemented):

This module uses a buffer for file operations, therefore can be tested on any machine, regardless of its HW. Make sure you avoid unnecessary printk's as loops may harm your kernel stability.

Once this is done, in user-space shell you should create a /dev node to represent your character device:

```
sudo mknod /dev/[dev_name] c [major] [minor]
```

for example:

```
sudo mknod /dev/my_dev c 217 0
```

Then you can test your read / write APIs with:

```
sudo insmod my_modult.ko
cat /dev/my_dev
less -f /dev/my_dev
sudo su
root> echo "This is a test" > /dev/my_dev
root> exit
cat /dev/my_dev
```
The shell commands listed above perform read, then login as root (to allow writing to device), write to the char dev, then exit and read again to see the changes.

Now you'd normally implement ioctl and mmap if needed.

**/
