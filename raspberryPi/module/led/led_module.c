// sudo apt install raspberrypi-kernel-headers

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int led_module_init(void)
{
    printk(KERN_INFO "led module init!\n");
    return 0;
}

static void led_module_exit(void)
{
    printk(KERN_INFO "led module exit!\n");
}

module_init(module_exam_init);
module_exit(module_exam_exit);
MODULE_LICENSE("GPL");