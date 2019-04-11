#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>

#define SW1 0		//gpio17


int main(void)
{
	int swFlag=0;
	int count = 1;
	// Init wiringPi
	wiringPiSetup();

	// pinAssign
	pinMode(SW1, INPUT);

	while (1)
	{
		// swFlag == 0 이고, 스위치가 눌렸을 때
		if (digitalRead(SW1) && (swFlag == 0))
		{
			printf("SWITCH ON: %d\n", count++);
			swFlag = 1;
		}
		else if (digitalRead(SW1) && (swFlag == 1))
		{
			swFlag = 0;
		}
		usleep(100000);
		/*if (digitalRead(SW1))
		{
			printf("SWITCH ON: %d\n", count++);			
		}*/
	}
}
