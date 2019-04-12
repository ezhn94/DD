#include <wiringPi.h>

int a = 27;//GPIO16
int b = 26;//GPIO12
int c = 23;//GPIO13
int d = 24;//GPIO19
int e = 25;//GPIO26
int f = 28;// GPIO20
int g = 29;//GPIO21
int dp = 22;//GPIO6
int i;

void digital_off()//0
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(dp, HIGH);
}

int main()
{
	wiringPiSetup();
	{
		for (i = 22; i <= 29; i++)
			pinMode(i, OUTPUT);
	}
	
	digital_off();

	return 0;
}