#include "stm32f4xx.h"
#include <stdint.h>
#include "i2c.h"


#define DATAFORMAT4G  (0x01)
#define DATAFORMATAD  (0x31)

#define POWERCTRL     0x2D
#define RESET         0x00
#define MEASUREMODE   0x08

#define SADDR         0x53

#define DEVID         0x00

char devid;
uint8_t data_rec[6];

void adxl_read_address(uint8_t reg)
{
	i2c_byteread(SADDR,reg,&devid);  //PROBLEM

	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER &= ~(1U<<11);
	GPIOA->MODER |= (1U<<10);

	GPIOA->ODR &= ~(1U<<5);

	for(int i=0;i<10000000;i++);

	GPIOA->ODR |= (1U<<5);
}


void adxl_write(uint8_t reg, char value)
{
	char data[1];
	data[0]=value;
	i2c_burstwrite(SADDR,reg,1,data);
}

void adxl_read(uint8_t reg)
{
	i2c_burstread(SADDR, reg, 6, (char *)data_rec);
}

void adxl_init()
{
	i2c_config();


	adxl_read_address(DEVID);


	//set data format in adxl345
	adxl_write(DATAFORMATAD,DATAFORMAT4G);



	//power reset
	adxl_write(POWERCTRL,RESET);

	//measure mode in power ctrl
	adxl_write(POWERCTRL,MEASUREMODE);

}







