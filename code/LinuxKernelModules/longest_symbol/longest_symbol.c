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

_Static_assert(sizeof(__stringify(LONGEST_SYM_NAME)) == KSYM_NAME_LEN, \
"Incorrect symbol length found. Expected KSYM_NAME_LEN: " \
__stringify(KSYM_NAME) ", but found: " \
__stringify(sizeof(LONGEST_SYM_NAME)));

static void test_longest_symbol(struct kunit *test)
{
	KUNIT_EXPECT_EQ(test, 424242, LONGEST_SYM_NAME());
};

static void test_longest_symbol_kallsyms(struct kunit *test)
{
	unsigned long (*kallsyms_lookup_name)(const char *name);
	static int (*longest_sym)(void);

	struct kprobe kp = {
		.symbol_name = "kallsyms_lookup_name",
	};

	if (register_kprobe(&kp) < 0) {
		pr_info("test_longest_symbol_kallsyms: kprobe not registered\n");
		KUNIT_ASSERT_TRUE(test, register_kprobe(&kp) < 0);
		return;
	}

	kallsyms_lookup_name = (unsigned long (*)(const char *name))kp.addr;
	unregister_kprobe(&kp);

	longest_sym = \
	    (void*) kallsyms_lookup_name(__stringify(LONGEST_SYM_NAME));
	KUNIT_EXPECT_EQ(test, 424242, longest_sym());
};

static void test_longest_symbol_plus1(struct kunit *test)
{
	KUNIT_EXPECT_EQ(test, 434343, LONGEST_SYM_NAME_PLUS1());
};

static void test_longest_symbol_plus1_kallsyms(struct kunit *test)
{
	unsigned long (*kallsyms_lookup_name)(const char *name);
	static int (*longest_sym_plus1)(void);

	struct kprobe kp = {
		.symbol_name = "kallsyms_lookup_name",
	};

	if (register_kprobe(&kp) < 0) {
		pr_info("test_longest_symbol_plus1_kallsyms: "
				"kprobe not registered\n");
		KUNIT_ASSERT_TRUE(test, register_kprobe(&kp) < 0);
		return;
	}

	kallsyms_lookup_name = (unsigned long (*)(const char *name))kp.addr;
	unregister_kprobe(&kp);

	longest_sym_plus1 = \
	    (void*) kallsyms_lookup_name(__stringify(LONGEST_SYM_NAME_PLUS1));
	KUNIT_EXPECT_EQ(test, 434343, longest_sym_plus1());
};

module_init(test_hello_init);
module_exit(test_hello_exit);

MODULE_LICENSE("GPL");
