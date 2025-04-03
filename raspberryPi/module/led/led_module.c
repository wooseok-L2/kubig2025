#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define HIGH 1
#define LOW 0

int led[4] = {23 + 512, 24 + 512, 25 + 512, 1 + 512};

static int led_module_init(void)
{
    int ret, i;
    printk(KERN_INFO "led module init! \n");
    for (i = 0; i < 4; i++)
    {
        ret = gpio_request(led[i], "LED");
        if (ret < 0)
            printk(KERN_INFO "led mosule gpio request failed!\n");
    }
    for (i = 0; i < 4; i++)
    {
        ret = gpio_direction_output(led[i], HIGH);
        msleep(100);
    }
    for (i = 3; i >= 0; i--)
    {
        gpio_direction_output(led[i], LOW);
        msleep(100);
    }
    for (i = 0; i < 4; i++)
    {
        ret = gpio_direction_output(led[i], HIGH);
        msleep(100);
    }
    return 0;
}

static void led_module_exit(void)
{
    int i;
    printk(KERN_INFO "led module exit!\n");
    for (i = 3; i >= 0; i--)
    {
        gpio_direction_output(led[i], LOW);
        msleep(100);
    }
    for (i = 0; i < 4; i++)
    {
        gpio_free(led[i]);
    }
    printk(KERN_INFO "All GPIOs freed successfully.\n");
}

module_init(led_module_init);
module_exit(led_module_exit);
MODULE_LICENSE("GPL");