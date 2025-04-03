#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>

int sw[4] = {4 + 512, 17 + 512, 27 + 512, 22 + 512};

irqreturn_t irq_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "Debug %d\n", irq);
    return 0;
}

static int switch_interrupt_init(void)
{
    int res, i;
    printk(KERN_INFO "switch_interrupt_init!\n");
    for (i = 0; i < 4; i++)
    {
        res = gpio_request(sw[i], "sw");
        res = request_irq(gpio_to_irq(sw[i]), (irq_handler_t)irq_handler, IRQF_TRIGGER_RISING, "IRQ", (void *)(irq_handler));
        if (res < 0)
            printk(KERN_INFO "request_irq failed!\n");
    }
    return 0;
}

static void switch_interrupt_exit(void)
{
    int i;
    printk(KERN_INFO "switch_interrupt_exit!\n");
    for (i = 0; i < 4; i++)
    {
        free_irq(gpio_to_irq(sw[i]), (void *)(irq_handler));
        gpio_free(sw[i]);
    }
}

module_init(switch_interrupt_init);
module_exit(switch_interrupt_exit);
MODULE_LICENSE("GPL");