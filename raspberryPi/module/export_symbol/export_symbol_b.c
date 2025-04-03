#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

extern void export_symbol_test_func1(void);
extern void export_symbol_test_func2(void);

static int __init export_symbol_b_init(void)
{
    printk(KERN_INFO "export symbol b init!\n");
    export_symbol_test_func1();
    export_symbol_test_func2();
    return 0;
}

static void __exit export_symbol_b_exit(void)
{
    printk(KERN_INFO "export symbol b exit!\n");
}
module_init(export_symbol_b_init);
module_exit(export_symbol_b_exit);
MODULE_LICENSE("GPL");