#include <linux/init.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define GPIO_BASE 0xFE200000 // video -> CPU
#define GPIO_SIZE 0x1000

#define GPFSEL0 0x00
#define GPFSEL1 0x04
#define GPFSEL2 0x08

#define GPSET0 0x1C
#define GPCTL0 0x28

int led[4] = {23, 24, 25, 1};
static void __iomem *gpio_base;

static int led_module_init(void)
{
    int i, reg_offset, bit;
    __u32 value;
    gpio_base = ioremap(GPIO_BASE, GPIO_SIZE);
    printk(KERN_INFO "led module init! \n");
    for (i = 0; i < 4; i++)
    {
        // 출력 설정
        reg_offset = (led[i] / 10) * 4;
        bit = (led[i] % 10) * 3;
        value = ioread32(gpio_base + reg_offset);
        value = (value & ~(7 << bit)) | (1 << bit);
        iowrite32(value, gpio_base + reg_offset);

        // HIGH 설정
        iowrite32(1 << led[i], gpio_base + GPSET0);
    }
    return 0;
}

static void led_module_exit(void)
{
    for (int i = 0; i < 4; i++)
    {
        iowrite32(1 << led[i], gpio_base + GPCTL0);
    }
    iounmap(gpio_base);
    printk(KERN_INFO "All GPIOs freed successfully.\n");
}

module_init(led_module_init);
module_exit(led_module_exit);
MODULE_LICENSE("GPL");