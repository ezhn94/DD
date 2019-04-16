#include <linux/gpio.h>

#define A	16
#define B	12
#define C	13
#define D	19
#define E	26
#define F	20
#define G	21
#define P	6

void digital_0(void)//0
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 0);
	gpio_set_value(E, 0);
	gpio_set_value(F, 0);
	gpio_set_value(G, 1);
	gpio_set_value(P, 1);
}
void digital_1(void)//1
{
	gpio_set_value(A, 1);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 1);
	gpio_set_value(E, 1);
	gpio_set_value(F, 1);
	gpio_set_value(G, 1);
	gpio_set_value(P, 1);
}
void digital_2(void)//2
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 0);
	gpio_set_value(C, 1);
	gpio_set_value(D, 0);
	gpio_set_value(E, 0);
	gpio_set_value(F, 1);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
}
void digital_3(void)//3
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 0);
	gpio_set_value(E, 1);
	gpio_set_value(F, 1);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
}
void digital_4(void)//4
{
	gpio_set_value(A, 1);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 1);
	gpio_set_value(E, 1);
	gpio_set_value(F, 0);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
}
void digital_5(void)//5
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 1);
	gpio_set_value(C, 0);
	gpio_set_value(D, 0);
	gpio_set_value(E, 1);
	gpio_set_value(F, 0);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
	gpio_set_value(E, 1);
}
void digital_6(void)//6
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 1);
	gpio_set_value(C, 0);
	gpio_set_value(D, 0);
	gpio_set_value(E, 0);
	gpio_set_value(F, 0);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
}
void digital_7(void)//7
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 1);
	gpio_set_value(E, 1);
	gpio_set_value(F, 1);
	gpio_set_value(G, 1);
	gpio_set_value(P, 1);
}
void digital_8(void)//8
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 0);
	gpio_set_value(E, 0);
	gpio_set_value(F, 0);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
}
void digital_9(void)//9
{
	gpio_set_value(A, 0);
	gpio_set_value(B, 0);
	gpio_set_value(C, 0);
	gpio_set_value(D, 0);
	gpio_set_value(E, 1);
	gpio_set_value(F, 0);
	gpio_set_value(G, 0);
	gpio_set_value(P, 1);
}