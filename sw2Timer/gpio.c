#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "myswitch.h"

void signal_handler(int signum)
{
	static int timeValue = 0;
	if (signum == SIGIO)
	{
		timeValue++;
		printf("time: %02d.%02d sec\r", timeValue/100, timeValue%100);
		fflush(stdout);
	}
}


int main(int argc, char** argv)
{
	char buf[BUFSIZ];
	int i = 0;
	int fd;
	int count;
	memset(buf, 0, BUFSIZ);

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGIO, signal_handler);

	sprintf(buf, "/dev/%s", GPIO_DEVICE);

	fd = open(buf, O_RDWR);
	if (fd < 0)
	{
		printf("Error open()\n");
		printf("sudo chmod 666 /dev/%s\n", GPIO_DEVICE);
		return -1;
	}

	sprintf(buf, "%d", getpid());
	count = write(fd, buf, strlen(buf));
	if (count < 0)
	{
		printf("Error write()\n");
	}

	while (1);

	close(fd);
	return 0;

}