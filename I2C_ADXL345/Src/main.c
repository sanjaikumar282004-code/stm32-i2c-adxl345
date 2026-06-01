#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>
#include "i2c.h"
#include "uart.h"
#include "adxl.h"



#define START_ADD 0x32

extern char devid;
extern uint8_t data_rec[6];

int16_t x,y,z;


int main(void)
{
	uart_init();

	adxl_init();

	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER &= ~(1U<<11);
	GPIOA->MODER |= (1U<<10);


	while(1)
	{

		GPIOA->ODR ^= (1U<<5);

		adxl_read(START_ADD);

		x= ((data_rec[1]<<8) | (data_rec[0]));
		y= ((data_rec[3]<<8) | (data_rec[2]));
		z= ((data_rec[5]<<8) | (data_rec[4]));

		printf("DEVID = 0x%X\r\n", devid);
		printf("X = %d\r\n",(int)x);
		printf("Y = %d\r\n",(int)y);
		printf("Z = %d\r\n\n",(int)z);

		for(int i=0;i<1000000;i++);



	}

}







