#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include "7seg.h"


#define GPIO_MAJOR	200
#define GPIO_MINOR	0
#define GPIO_DEVICE	"gpio7"

#define BLK_SIZE	100
//#define DEBUG

struct cdev gpio_cdev;
volatile unsigned int *gpio;
static char msg[BLK_SIZE] = { 0 };

static int gpio_open(struct inode *, struct file *);
static int gpio_close(struct inode *, struct file *);
static ssize_t gpio_read(struct file *, char *buff, size_t, loff_t *);
static ssize_t gpio_write(struct file *, const char *, size_t, loff_t *);
char seg[8] = { a,b,c,d,e,f,g,p };
char sw[2] = { N,F };

static struct file_operations gpio_fops = {
	.owner = THIS_MODULE,
	.read = gpio_read,
	.write = gpio_write,
	.open = gpio_open,
	.release = gpio_close,
};

static int gpio_open(struct inode *inod, struct file *fil)
{
	//����� ��� ī��Ʈ�� ���� ��Ų��.
	try_module_get(THIS_MODULE);
	printk(KERN_INFO "GPIO Device opened\n");
	return 0;
}

static int gpio_close(struct inode *inod, struct file *fil)
{
	//����� ��� ī��Ʈ�� ���� ��Ų��.
	module_put(THIS_MODULE);
	printk(KERN_INFO " GPIO Device closed\n");
	return 0;
}

static ssize_t gpio_read(struct file *fil, char *buff, size_t len, loff_t *off)
{
	int count;
	// <linux/gpio.h>���Ͽ� �ִ� gpio_get_value()�� ����
	// gpio�� ���°��� �о�´�. 
	
	// �� �����Ͱ� Ŀ�ο��� �� ���������� ǥ���Ѵ�.
	strcat(msg, " from kernel");

	//Ŀ�ο����� �ִ� msg���ڿ��� ���������� buff�ּҷ� ���� 
	count = copy_to_user(buff, msg, strlen(msg) + 1);

	printk(KERN_INFO "GPIO Device read:%s\n", msg);

	return count;
}


static ssize_t gpio_write(struct file *fil, const char *buff, size_t len, loff_t *off)
{
	int count;
	int i;
	memset(msg, 0, BLK_SIZE);

	count = copy_from_user(msg, buff, len);

	for (i = 0; i < 8; i++)
	{
		gpio_set_value(seg[i], 0);
	}

	printk(KERN_INFO "GPIO Device write:%s\n", msg);
	return count;
}

static int __init initModule(void)
{
	dev_t devno;
	int err;
	int count;
	int i;

	printk("Called initModule()\n");

	// 1. ���ڵ���̽� ����̹��� ����Ѵ�.
	devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
	register_chrdev_region(devno, 1, GPIO_DEVICE);

	// 2. ���� ����̽��� ���� ����ü�� �ʱ�ȭ �Ѵ�.
	cdev_init(&gpio_cdev, &gpio_fops);
	gpio_cdev.owner = THIS_MODULE;
	count = 1;

	// 3. ���ڵ���̽��� �߰�
	err = cdev_add(&gpio_cdev, devno, count);
	if (err < 0)
	{
		printk(KERN_INFO "Error: cdev_add()\n");
		return -1;
	}

	printk(KERN_INFO "'sudo mknod /dev/%s c %d 0'\n", GPIO_DEVICE, GPIO_MAJOR);
	printk(KERN_INFO "'sudo chmod 666 /dev/%s'\n", GPIO_DEVICE);

	// gpio���� ��������� Ȯ���ϰ� ������ ȹ��

	for (i = 0; i < 8; i++)
	{
		err = gpio_request(seg[i], "LED");		// gpio ������ ȹ��
		if (err == -EBUSY)
		{
			printk(KERN_INFO "Error gpio_request\n");
			return -1;
		}

		
	}
	for (i = 0; i < 8; i++)
	{
		gpio_direction_output(seg[i], 0);
	}

	for (i = 0; i < 2; i++)
	{
		err = gpio_request(sw[i], "SW");
		if (err == -EBUSY)
		{
			printk(KERN_INFO "Error gpio_request\n");
			return -1;
		}		
	}
	for (i = 0; i < 2; i++)
	{
		gpio_direction_output(sw[i], 0);
	}
	return 0;
}

static void __exit cleanupModule(void)
{
	int i;
	dev_t devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);

	for (i = 0; i < 8; i++)
	{
		gpio_direction_output(seg[i], 0);
	}	

	//gpio_request()���� �޾ƿ� �������� �ݳ��Ѵ�.
	for (i = 0; i < 8; i++)
	{
		gpio_free(seg[i]);
	}

	// 1.���� ����̽��� ����� �����Ѵ�.
	unregister_chrdev_region(devno, 1);

	// 2.���� ����̽��� ����ü�� �����Ѵ�.
	cdev_del(&gpio_cdev);

	printk("Good-bye!\n");
}


//sudo insmod ȣ��Ǵ� �Լ��� ����
module_init(initModule);

//sudo rmmod ȣ��Ǵ� �Լ��� ����
module_exit(cleanupModule);

//����� ����
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO Driver Module");
MODULE_AUTHOR("jh");
