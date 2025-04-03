// read switch 정보 얻기, write led 조작 드라이버
// write -> toggle , interrupt -> switch -> toggle

/*
sudo insmod led_switch_driver.ko
dmesg
sudo mknod /dev/led_switch_driver c 223 0
sudo chmod 666 /dev/led_switch_driver
*/

#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define DEV_MAJOR_NUMBER 223
#define DEV_NAME "led_switch_driver"

#define SW1 57
#define SW2 58
#define SW3 59
#define SW4 60
// TODO: 확인 후 변경

static int led_switch_driver_open(struct inode *inode, struct file *file);
static int led_switch_driver_release(struct inode *inode, struct file *file);
static ssize_t led_switch_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs);
static ssize_t led_switch_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs);

static int led[4] = {23 + 512, 24 + 512, 25 + 512, 1 + 512};
static int sw[4] = {4 + 512, 17 + 512, 27 + 512, 22 + 512};
static int led_status[4] = {0};

static struct file_operations led_switch_driver_fops = {
    .owner = THIS_MODULE,
    .open = led_switch_driver_open,
    .release = led_switch_driver_release,
    .read = led_switch_driver_read,
    .write = led_switch_driver_write,
};

irqreturn_t irq_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "Debug %d\n", irq);
    switch (irq)
    {
    case SW1:
        led_status[0] = !led_status[0];
        gpio_set_value(led[0], led_status[0]);
        break;
    case SW2:
        led_status[1] = !led_status[1];
        gpio_set_value(led[1], led_status[1]);
        break;
    case SW3:
        led_status[2] = !led_status[2];
        gpio_set_value(led[2], led_status[2]);
        break;
    case SW4:
        led_status[3] = !led_status[3];
        gpio_set_value(led[3], led_status[3]);
        break;
    }
    return 0;
}

static int led_switch_driver_init(void)
{
    printk(KERN_INFO "switch driver init!\n");
    register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &led_switch_driver_fops);
    return 0;
}

static void led_switch_driver_exit(void)
{
    printk(KERN_INFO "switch driver exit!\n");
    unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

static int led_switch_driver_open(struct inode *inode, struct file *file)
{
    int ret, i;
    printk(KERN_INFO "switch driver open!\n");
    for (i = 0; i < 4; ++i)
    {
        ret = gpio_request(led[i], "LED");
        if (ret < 0)
            printk(KERN_INFO "led driver %d request fail!\n", i);
        ret = gpio_request(sw[i], "switch");
        if (ret < 0)
            printk(KERN_INFO "switch driver %d request fail!\n", i);
        ret = request_irq(gpio_to_irq(sw[i]), (irq_handler_t)irq_handler, IRQF_TRIGGER_RISING, "IRQ", (void *)(irq_handler));
        if (ret < 0)
            printk(KERN_INFO "request_irq failed!\n");
    }
    return 0;
}

static int led_switch_driver_release(struct inode *inode, struct file *file)
{
    int i;
    printk(KERN_INFO "switch driver release!\n");
    for (i = 0; i < 4; ++i)
    {
        gpio_free(sw[i]);
        gpio_free(led[i]);
    }
    return 0;
}

static ssize_t led_switch_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs)
{
    int ret, i;
    char read_buf[4];
    printk(KERN_INFO "led_switch_driver_read!\n");
    for (i = 0; i < 4; ++i)
        read_buf[i] = led_status[i];
    ret = copy_to_user(buf, read_buf, sizeof(read_buf));
    if (ret < 0)
        printk(KERN_INFO "switch driver copy to user fail!\n");
    return 0;
}

static ssize_t led_switch_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs)
{
    int ret, i;
    unsigned char cbuf[4];
    ret = copy_from_user(cbuf, buf, length);
    if (ret < 0)
        printk(KERN_INFO "lcopy from user error!\n");
    printk(KERN_INFO "led driver open!\n");
    for (i = 0; i < 4; ++i)
    {
        if (cbuf[i] == 1)
        {
            led_status[i] = !led_status[i];
        }
        ret = gpio_direction_output(led[i], led_status[i]);
        if (ret < 0)
            printk(KERN_INFO "led driver %d direction output fail!\n", i);
    }
    return 0;
}

module_init(led_switch_driver_init);
module_exit(led_switch_driver_exit);
MODULE_LICENSE("GPL");