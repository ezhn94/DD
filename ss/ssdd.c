//================================
// Character device driver example 
// GPIO driver
//================================
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define GPIO_MAJOR	200
#define GPIO_MINOR	0
#define GPIO_DEVICE	"gpio7seg"

#define a	16
#define b	12
#define c	13
#define d	19
#define e	26
#define f	20
#define g	21
#define p	6

#define BLK_SIZE	100
//#define DEBUG

struct cdev gpio_cdev;
volatile unsigned int *gpio;
static char msg[BLK_SIZE] = { 0 };

static int gpio_open(struct inode *, struct file *);
static int gpio_close(struct inode *, struct file *);
static ssize_t gpio_read(struct file *, char *buff, size_t, loff_t *);
static ssize_t gpio_write(struct file *, const char *, size_t, loff_t *);
char ss[8] = { a,b,c,d,e,f,g,p };

void digital_0(void)//0
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 0);
	gpio_set_value(e, 0);
	gpio_set_value(f, 0);
	gpio_set_value(g, 1);
	gpio_set_value(p, 1);
}
void digital_1(void)//1
{
	gpio_set_value(a, 1);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 1);
	gpio_set_value(e, 1);
	gpio_set_value(f, 1);
	gpio_set_value(g, 1);
	gpio_set_value(p, 1);
}
void digital_2(void)//2
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 0);
	gpio_set_value(c, 1);
	gpio_set_value(d, 0);
	gpio_set_value(e, 0);
	gpio_set_value(f, 1);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
}
void digital_3(void)//3
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 0);
	gpio_set_value(e, 1);
	gpio_set_value(f, 1);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
}
void digital_4(void)//4
{
	gpio_set_value(a, 1);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 1);
	gpio_set_value(e, 1);
	gpio_set_value(f, 0);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
}
void digital_5(void)//5
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 1);
	gpio_set_value(c, 0);
	gpio_set_value(d, 0);
	gpio_set_value(e, 1);
	gpio_set_value(f, 0);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
	gpio_set_value(e, 1);
}
void digital_6(void)//6
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 1);
	gpio_set_value(c, 0);
	gpio_set_value(d, 0);
	gpio_set_value(e, 0);
	gpio_set_value(f, 0);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
}
void digital_7(void)//7
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 1);
	gpio_set_value(e, 1);
	gpio_set_value(f, 1);
	gpio_set_value(g, 1);
	gpio_set_value(p, 1);
}
void digital_8(void)//8
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 0);
	gpio_set_value(e, 0);
	gpio_set_value(f, 0);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
}
void digital_9(void)//9
{
	gpio_set_value(a, 0);
	gpio_set_value(b, 0);
	gpio_set_value(c, 0);
	gpio_set_value(d, 0);
	gpio_set_value(e, 1);
	gpio_set_value(f, 0);
	gpio_set_value(g, 0);
	gpio_set_value(p, 1);
}

static struct file_operations gpio_fops = {
	.owner = THIS_MODULE,
	.read = gpio_read,
	.write = gpio_write,
	.open = gpio_open,
	.release = gpio_close,
};

static int gpio_open(struct inode *inod, struct file *fil)
{
	//모듈의 사용 카운트를 증가 시킨다.
	try_module_get(THIS_MODULE);
	printk(KERN_INFO "GPIO Device opened\n");
	return 0;
}


static int gpio_close(struct inode *inod, struct file *fil)
{
	//모듈의 사용 카운트를 감소 시킨다.
	module_put(THIS_MODULE);
	printk(KERN_INFO " GPIO Device closed\n");
	return 0;
}

static ssize_t gpio_read(struct file *fil, char *buff, size_t len, loff_t *off)
{
	int count;
	// <linux/gpio.h>파일에 있는 gpio_get_value()를 통해
	// gpio의 상태값을 읽어온다. 	

	// 이 데이터가 커널에서 온 데이터임을 표기한다.
	strcat(msg, " from kernel");

	//커널영역에 있는 msg문자열을 유저영역의 buff주소로 복사 
	count = copy_to_user(buff, msg, strlen(msg) + 1);

	printk(KERN_INFO "GPIO Device read:%s\n", msg);

	return count;
}


static ssize_t gpio_write(struct file *fil, const char *buff, size_t len, loff_t *off)
{
	int count;
	memset(msg, 0, BLK_SIZE);

	count = copy_from_user(msg, buff, len);

	if (!strcmp(msg, "0"))
		digital_0();
	else if (!strcmp(msg, "1"))
		digital_1();
	else if (!strcmp(msg, "2"))
		digital_2();
	else if (!strcmp(msg, "3"))
		digital_3();
	else if (!strcmp(msg, "4"))
		digital_4();
	else if (!strcmp(msg, "5"))
		digital_5();
	else if (!strcmp(msg, "6"))
		digital_6();
	else if (!strcmp(msg, "7"))
		digital_7();
	else if (!strcmp(msg, "8"))
		digital_8();
	else if (!strcmp(msg, "9"))
		digital_9();
	
	printk(KERN_INFO "GPIO Device write:%s\n", msg);
	return count;
}

static int __init initModule(void)
{
	dev_t devno;
	int err;
	int count;
	int j;
	

	printk("Called initModule()\n");

	// 1. 문자디바이스 드라이버를 등록한다.
	devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
	register_chrdev_region(devno, 1, GPIO_DEVICE);

	// 2. 문자 디바이스를 위한 구조체를 초기화 한다.
	cdev_init(&gpio_cdev, &gpio_fops);
	gpio_cdev.owner = THIS_MODULE;
	count = 1;

	// 3. 문자디바이스를 추가
	err = cdev_add(&gpio_cdev, devno, count);
	if(err < 0)
	{
		printk(KERN_INFO "Error: cdev_add()\n");
		return -1;
	}

	printk(KERN_INFO "'sudo mknod /dev/%s c %d 0'\n", GPIO_DEVICE, GPIO_MAJOR);
	printk(KERN_INFO "'sudo chmod 666 /dev/%s'\n", GPIO_DEVICE);

	// 현재 핀이 사용중인지 확인하고 사용권한 획득

	for(j = 0; j<8; j++)
	{
		err = gpio_request(ss[j], "LED");
		if (err == -EBUSY) {
			printk(KERN_INFO "Error a_request\n");
			return -1;
		}
		gpio_direction_output(ss[j], 0);
	}
	return 0;
}

static void __exit cleanupModule(void)
{
	dev_t devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
	int j;

	for(j = 0; j < 8; j++)
	{
		gpio_direction_output(ss[j], 0);
	}

	//gpio_request()에서 받아온 사용권한을 반납한다.
		
	for(j = 0; j < 8; j++)
	{
		gpio_free(ss[j]);
	}


	// 1.문자 디바이스의 등록을 해제한다.
	unregister_chrdev_region(devno, 1);

	// 2.문자 디바이스의 구조체를 삭제한다.
	cdev_del(&gpio_cdev);

	printk("Good-bye!\n");
}


//sudo insmod 호출되는 함수명 정의
module_init(initModule);

//sudo rmmod 호출되는 함수명 정의
module_exit(cleanupModule);

//모듈의 정보
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO Driver Module");
MODULE_AUTHOR("JH");
