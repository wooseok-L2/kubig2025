/*
sudo insmod switch_driver.ko
dmesg
sudo mknod /dev/switch_driver c 222 0
sudo chmod 666 /dev/switch_driver
*/
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define DEV_MAJOR_NUMBER 222
#define DEV_NAME "switch_driver"

static int switch_driver_open(struct inode *inode, struct file *file);
static int switch_driver_release(struct inode *inode, struct file *file);
static ssize_t switch_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs);

int sw[4] = {4 + 512, 17 + 512, 27 + 512, 22 + 512};

static struct file_operations switch_driver_fops = {
    .owner = THIS_MODULE,
    .open = switch_driver_open,
    .release = switch_driver_release,
    .read = switch_driver_read,
};

static int switch_driver_init(void)
{
    printk(KERN_INFO "switch driver init!\n");
    register_chrdev(DEV_MAJOR_NUMBER, DEV_NAME, &switch_driver_fops);
    return 0;
}

static void switch_driver_exit(void)
{
    printk(KERN_INFO "switch driver exit!\n");
    unregister_chrdev(DEV_MAJOR_NUMBER, DEV_NAME);
}

static int switch_driver_open(struct inode *inode, struct file *file)
{
    int ret, i;
    printk(KERN_INFO "switch driver open!\n");
    for (i = 0; i < 4; ++i)
    {
        ret = gpio_request(sw[i], "switch");
        if (ret < 0)
            printk(KERN_INFO "switch driver %d request fail!\n", i);
    }
    return 0;
}

static int switch_driver_release(struct inode *inode, struct file *file)
{
    int i;
    printk(KERN_INFO "switch driver release!\n");
    for (i = 0; i < 4; ++i)
    {
        gpio_free(sw[i]);
    }
    return 0;
}

static ssize_t switch_driver_read(struct file *file, char __user *buf, size_t length, loff_t *ofs)
{
    int ret, i;
    char read_buf[4];
    printk(KERN_INFO "switch_driver_read!\n");
    for (i = 0; i < 4; ++i)
        read_buf[i] = gpio_get_value(sw[i]);
    ret = copy_to_user(buf, read_buf, sizeof(read_buf));
    if (ret < 0)
        printk(KERN_INFO "switch driver copy to user fail!\n");
    return 0;
}

module_init(switch_driver_init);
module_exit(switch_driver_exit);
MODULE_LICENSE("GPL");