/*
sudo insmod led_driver.ko
dmesg
ls /dev
sudo mknod /dev/led_driver c 221 0
sudo chmod 666 /dev/led_driver
*/
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define DEV_MAJOR_NUMBER 221
#define DEV_NAME "led_driver"

static int led_driver_open(struct inode *inode, struct file *file);
static int led_driver_release(struct inode *inode, struct file *file);
static ssize_t led_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs);

int led[4] = {23 + 512, 24 + 512, 25 + 512, 1 + 512};

static struct file_operations led_driver_fops = {
    .owner = THIS_MODULE,
    .open = led_driver_open,
    .release = led_driver_release,
    .write = led_driver_write,
};

static int led_driver_init(void)
{
    printk(KERN_INFO "led driver init!\n");
    register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &led_driver_fops);
    return 0;
}

static void led_driver_exit(void)
{
    printk(KERN_INFO "led driver exit!\n");
    unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

static int led_driver_open(struct inode *inode, struct file *file)
{
    int ret, i;
    printk(KERN_INFO "led driver open!\n");
    for (i = 0; i < 4; ++i)
    {
        ret = gpio_request(led[i], "LED");
        if (ret < 0)
            printk(KERN_INFO "led driver %d request fail!\n", i);
    }
    return 0;
}

static int led_driver_release(struct inode *inode, struct file *file)
{
    int i;
    printk(KERN_INFO "led driver release!\n");
    for (i = 0; i < 4; ++i)
    {
        gpio_free(led[i]);
    }
    return 0;
}
static ssize_t led_driver_write(struct file *file, const char __user *buf, size_t length, loff_t *ofs)
{
    int ret, i;
    unsigned char cbuf[4];
    ret = copy_from_user(cbuf, buf, length);
    if (ret < 0)
        printk(KERN_INFO "lcopy from user error!\n");
    printk(KERN_INFO "led driver open!\n");
    for (i = 0; i < 4; ++i)
    {
        ret = gpio_direction_output(led[i], cbuf[i]);
        if (ret < 0)
            printk(KERN_INFO "led driver %d direction output fail!\n", i);
    }
    return 0;
}

module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_LICENSE("GPL");