// reference: https://sysprog21.github.io/lkmpg/#read-and-write-a-proc-file

#include <linux/kernel.h> /* We're doing kernel work */
#include <linux/module.h> /* Specifically, a module */
#include <linux/proc_fs.h> /* Necessary because we use the proc fs */
#include <linux/uaccess.h> /* for copy_from_user */
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

#define PROCFS_MAX_SIZE 1024
#define PROCFS_NAME "buffer1k"

// this struct holds information about the /proc file.
static struct proc_dir_entry *our_proc_file;

// the buffer used to store characters for this module.
static char procfs_buffer[PROCFS_MAX_SIZE];

// the size of the buffer
static unsigned long procfs_buffer_size = 0;

// this function is called when the /proc file is read
static ssize_t procfile_read(struct file *file_pointer, char __user *buffer,
			     size_t buffer_length, loff_t *offset)
{
	char s[13] = "HelloWorld!\n";
	int len = sizeof(s);
	ssize_t ret = len;
	int repeat = 3;

	if (*offset >= repeat*len || copy_to_user(buffer, s, len))
	{
		pr_info("copy_to_user failed\n");
		pr_info("offset: %lld\n", *offset);
		ret = 0;
	} else {
		pr_info("procfile read %s\n", file_pointer->f_path.dentry->d_name.name);
		pr_info("offset 1: %lld\n", *offset);
		*offset += len;
		pr_info("offset 2: %lld\n", *offset);
	}

	return ret;
}

// this function is called with the /proc file is written
static ssize_t procfile_write(struct file *file, const char __user *buff,
				size_t len, loff_t *off)
{
	procfs_buffer_size = len;
	if (procfs_buffer_size > PROCFS_MAX_SIZE)
		procfs_buffer_size = PROCFS_MAX_SIZE;

	if (copy_from_user(procfs_buffer, buff, procfs_buffer_size))
		return -EFAULT;

	procfs_buffer[procfs_buffer_size & (PROCFS_MAX_SIZE - 1)] = '\0';
	*off += procfs_buffer_size;
	pr_info("procfile write %s\n", procfs_buffer);
	pr_info("offset: %lld\n", *off);

	return procfs_buffer_size;
}

#ifdef HAVE_PROC_OPS
static const struct proc_ops proc_file_fops = {
    .proc_read = procfile_read,
    .proc_write = procfile_write,
};
#else
static const struct file_operations proc_file_fops = {
    .read = procfile_read,
    .write = procfile_write,
};
#endif

static int __init procfs2_init(void)
{
	our_proc_file = proc_create(PROCFS_NAME, 0666, NULL, &proc_file_fops);
	if (NULL == our_proc_file) {
		proc_remove(our_proc_file);
		pr_alert("Error: Could not initialize /proc/%s\n", PROCFS_NAME);
		return -ENOMEM;
	}

	pr_info("/proc/%s created\n", PROCFS_NAME);
	return 0;
}

static void __exit procfs2_exit(void)
{
	proc_remove(our_proc_file);
	pr_info("/proc/%s removed\n", PROCFS_NAME);
}

module_init(procfs2_init);
module_exit(procfs2_exit);

MODULE_LICENSE("GPL");
