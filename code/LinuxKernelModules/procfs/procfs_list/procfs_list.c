#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/mutex.h>
#include <linux/string.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

#define PROCFS_MAX_SIZE 1024
#define PROCFS_NAME "buffer1k"

/* define parameters */
char* procfs_name = PROCFS_NAME;
uint procfs_buffer_max_size = PROCFS_MAX_SIZE;
module_param(procfs_name, charp, S_IRUGO);
module_param(procfs_buffer_max_size, uint, S_IRUGO);

/* this struct holds information about the /proc file */
static struct proc_dir_entry *our_proc_file;

/* the buffer used to store characters for this module */
static char* procfs_buffer;

/* define my_list structure */
struct my_list {
	struct list_head list;
	char *message;
};

/* for reading the list */
struct my_list *read_cursor = NULL;

/* define list nodes counter */
ssize_t num_nodes = 0;

/* declare and init the head node of the linked list */
LIST_HEAD(head_node);

/* mutex to protect the list */
DEFINE_MUTEX(my_lock);

static ssize_t procfile_read(struct file *file_pointer, char __user *buffer,
			     size_t buffer_length, loff_t *offset)
{
	int len = procfs_buffer_max_size;
	struct my_list *tmp = NULL;

	if (read_cursor == NULL) {
		read_cursor = list_first_entry_or_null(&head_node, struct my_list, list);
		if (!read_cursor)
			return 0;
	} else {
		read_cursor = list_next_entry(read_cursor, list);
	}

	mutex_lock(&my_lock);
	list_for_each_entry_safe_from(read_cursor, tmp, &head_node, list) {
		len = strlen(read_cursor->message);
		if ((*offset >= buffer_length)
			|| copy_to_user(buffer, read_cursor->message, len)) {
			pr_info("copy_to_user() failed\n");
			mutex_unlock(&my_lock);
			return 0;
		} else {
			pr_info("procfile read %s- (len:%d):%s\n",
				file_pointer->f_path.dentry->d_name.name,
				len, read_cursor->message);
			offset += len;
			mutex_unlock(&my_lock);
			return len;
		}
	}
	mutex_unlock(&my_lock);

	read_cursor = NULL;
	return 0;
}

static ssize_t procfile_write(struct file *file, const char __user *buff,
				size_t len, loff_t *off)
{
	struct my_list *temp_node = NULL;
	char *temp_message = NULL;
        unsigned long procfs_buffer_size = 0;

	/* always validate __user inputs */
	if (NULL == buff || len == 0)
		return 0;

	procfs_buffer_size = len;
	if (procfs_buffer_size > procfs_buffer_max_size)
		procfs_buffer_size = procfs_buffer_max_size;

	memset(procfs_buffer, '\0', procfs_buffer_size);

	if (copy_from_user(procfs_buffer, buff, procfs_buffer_size))
		return -EFAULT;

	*off += procfs_buffer_size;

	/* generate new element for the list */
	temp_node = kzalloc(sizeof(struct my_list), GFP_KERNEL);
	temp_message = kzalloc(procfs_buffer_size + 2, GFP_KERNEL);
	strncpy(temp_message, procfs_buffer, procfs_buffer_size);
	temp_message[procfs_buffer_size +1] = '\0';
	temp_message[procfs_buffer_size] = '\n';
	temp_node->message = temp_message;
	pr_info("message writen(len:%ld): %s\n",
			strlen(temp_node->message), temp_node->message);

	/* add new element to the list */
	INIT_LIST_HEAD(&temp_node->list);
	mutex_lock(&my_lock);
	list_add_tail(&temp_node->list, &head_node);
	num_nodes ++;
	mutex_unlock(&my_lock);

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
	/* create the /proc entry */
	our_proc_file = proc_create(procfs_name, 0666, NULL, &proc_file_fops);
	if (NULL == our_proc_file) {
		proc_remove(our_proc_file);
		pr_alert("Error: Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}
	pr_info("/proc/%s created\n", procfs_name);

	/* allocate the procfs buffer */
	procfs_buffer = kmalloc(procfs_buffer_max_size, GFP_KERNEL);
	return 0;
}

static void __exit procfs2_exit(void)
{
	struct my_list *cursor, *temp;
	ssize_t count = 0;

	pr_info("expected num_nodes: %ld\n", num_nodes);

	/* traverse the list and delete it */
	list_for_each_entry_safe(cursor, temp, &head_node, list) {
		pr_info("release message(len:%ld): %s",
				strlen(cursor->message), cursor->message);
		kfree(cursor->message);
		list_del(&cursor->list);
		kfree(cursor);
		count++;
	}
	pr_info("released %ld list nodes", count);

	/* free memory of the profs buffer */
	kfree(procfs_buffer);

	/* remove the proc file */
	proc_remove(our_proc_file);
	pr_info("/proc/%s removed\n", procfs_name);
}

module_init(procfs2_init);
module_exit(procfs2_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("module for creating a /proc entry and write/read into a linked list");
MODULE_PARM_DESC(procfs_name, "char string with the name of the /proc entry");
MODULE_PARM_DESC(procgs_buffer_max_size, "uint max size of the buffer");
