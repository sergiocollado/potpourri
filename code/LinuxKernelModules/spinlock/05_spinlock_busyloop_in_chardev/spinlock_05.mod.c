#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x7a2af7b4, "cpu_number" },
	{ 0xb5b54b34, "_raw_spin_unlock" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xaee657ee, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x3818fa5c, "device_create" },
	{ 0x4800abdd, "cdev_init" },
	{ 0x58c36c14, "cdev_add" },
	{ 0xeabef977, "device_destroy" },
	{ 0x645620c0, "class_destroy" },
	{ 0x8bee73ff, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D8D9487C18AA58C6F8A7C74");
