#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/stringify.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

#define DI(name) s##name##name
#define DDI(name) DI(n##name##name)
#define DDDI(name) DDI(n##name##name)
#define DDDDI(name) DDDI(n##name##name)
#define DDDDDI(name) DDDDI(n##name##name)

#define PLUS1(name) name##e

/*Generate a symbol whose name length is 511 */
#define LONGEST_SYM_NAME  DDDDDI(g1h2i3j4k5l6m7n)
//#define LONGEST_SYM_NAME Sergi_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_12345678901234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_1234567890_Sergio

/*Generate a symbol whose name length is 512 */
#define LONGEST_SYM_PLUS1 PLUS1(LONGEST_SYM_NAME)

int noinline LONGEST_SYM_NAME(void)
{
	return 424242;
}

int noinline LONGEST_SYM_NAME_PLUS1(void)
{
	return 434343;
}

/*
_Static_assert(sizeof(__stringify(LONGEST_SYM_NAME)) == KSYM_NAME_LEN, \
"Incorrect symbol length found. Expected KSYM_NAME_LEN: " \
__stringify(KSYM_NAME_LEN) ", but found a symbol of different lenght: " \
__stringify(sizeof(LONGEST_SYM_NAME)));
*/

static int test_init(void)
{
	unsigned long (*kallsyms_lookup_name)(const char *name);
	static int (*longest_sym)(void);

	struct kprobe kp = {
		.symbol_name = "kallsyms_lookup_name",
	};

	if (register_kprobe(&kp) < 0) {
		pr_info("test_longest_symbol_kallsyms: kprobe not registered\n");
		return -1;
	}

	kallsyms_lookup_name = (unsigned long (*)(const char *name))kp.addr;
	unregister_kprobe(&kp);

	longest_sym = \
	    (void*) kallsyms_lookup_name(__stringify(LONGEST_SYM_NAME));

	if (424242 == longest_sym())
	{
		pr_info("longest symbol is there. Size: " __stringify(sizeof(LONGEST_SYM_NAME)));
		return 0;
	}
	else
	{
		pr_err("longest symbol not found");
		return -1;
	}
};

void test_exit(void)
{};

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
