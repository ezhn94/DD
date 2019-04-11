//user thread area 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> 

//Raspberry pi3 Physical I/O Peripherals BaseAddress
#define BCM_IO_BASE 0x3F000000 //datasheet 5page 

//GPIO_BaseAddress
#define GPIO_BASE (BCM_IO_BASE + 0x200000) //datasheet 90page. 

//GPIO Function Select Register 0-5
//set pin to inputmode (set -->000)
//000 & 000<<9
#define GPIO_IN(g) (*(gpio+((g)/10)) &=~(7<<(((g)%10)*3)))

//110 | 001 << 9
//set pin to outputmode (set --> 001)
#define GPIO_OUT(g) {(*(gpio+((g)/10)) |=(1<<(((g)%10)*3))); \
					(*(gpio+((g)/10)) |=(1<<(((g)%10)*3)));}	
 
//GPIO Pin Output Set 0 / clr 0
                    //addr   <=  value
#define GPIO_SET(g) (*(gpio+7) = (1<<g))
#define GPIO_CLR(g) (*(gpio+10) = (1<<g))
#define GPIO_GET(g) (*(gpio+13)&(1<<g))
#define GPIO_SIZE 0xB4
 
//volatile로 선언하지 않으면 cpu옆에있는 캐시에 데이터가 저장된다.
//외부적인 요소로 변경되는 값은 volatile을 써야한다.
//gpio는 수시로 바뀌는 메모리 영역이므로 volatile로 선언한다.
//만약 cpu만으로 동작되는 메모리라면 붙이면 안된다. 오히려 성능이 감소한다.
volatile unsigned int *gpio;
 
int main(int argc, char**argv)
{
	//GPIO Pin number
	int gno; //pin number
	int i, mem_fd;
	void *gpio_map;
	//when not input pin number
	if(argc <2)
	{
		printf("Usage: %s GPIO_NO \n", argv[0]);
		return -1;
	}
	gno = atoi(argv[1]);
	
	//device open /dev/mem
	//O_SYNC: write 시 버퍼에만 쓰이고 하드웨어에는 쓰이지 않았을때를 방지한다
	if((mem_fd = open("/dev/mem", O_RDWR | O_SYNC))<0)
	{
		printf("Error: open() /dev/mem\n");
		return -1;
	}
	//void * mmap(void *start, size_t length, int prot, int
	//		        flags, int fd, off_t offset);
	//          virtualAddr 
	gpio_map = mmap(NULL, GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,mem_fd,GPIO_BASE );
	//            physicalAddr
	if(gpio_map == MAP_FAILED)
	{
		printf("Error: mmap() :%d\n", (int)gpio_map);
		return -1;
	}
	gpio = (volatile unsigned int*)gpio_map;

	GPIO_OUT(gno);

	for(int i = 0; i< 5; i++)
	{
		GPIO_SET(gno);
		sleep(1);
		GPIO_CLR(gno);
		sleep(1);
	}
	munmap(gpio_map, GPIO_SIZE);

	return 0;
}

