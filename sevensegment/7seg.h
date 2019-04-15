#include <linux/gpio.h>

#define a	16
#define b	12
#define c	13
#define d	19
#define e	26
#define f	20
#define g	21
#define p	6
#define N	18
#define F	22

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