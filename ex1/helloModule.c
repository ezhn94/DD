#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void)
{
	printk("called hello init()\n");
	return 0;
}	

static void __exit hello_exit(void)
{
	printk("called hello exit()\n");
}
module_init(hello_init);
module_exit(hello_exit);

// 밑의 3줄은 기본으로 있어야 한다.
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_AUTHOR("JH");
