#include "stm32f4xx.h"
#include <stdint.h>

void i2c_burstwrite(char saddr, char maddr, int n, char *data)
{
	//set temp variable for addr reset
	volatile int temp;

	//checking bus is busy
	while((I2C1->SR2 & (1U<<1))!=0);

	//ENABLE START BIT
	I2C1->CR1 |= (1U<<8);

	//WAIT TILL START
	while((I2C1->SR1 & (1U<<0))==0);

	//SEND SLAVE ADDRESS + WRITE BIT
	I2C1->DR = saddr<<1;

	//WAIT TILL ADDR
	while((I2C1->SR1 & (1U<<1))==0);

	//CLEAR ADDR
	temp = I2C1->SR1;
	temp = I2C1->SR2;

	//WAIT TILL TRANSMITTED
	while((I2C1->SR1 & (1U<<7))==0);

	//SEND MEMORY ADDRESS
	I2C1->DR = maddr;

	while(n>0)
	{
		//wait till it transmitted
		while((I2C1->SR1 & (1U<<7))==0);

		I2C1->DR = *data++;

		n--;

	}

	//wait till last byte transmitted from status register (BTF)
	while((I2C1->SR1 & (1U<<2))==0);

	//STOP BIT
	I2C1->CR1 |= (1U<<9);



}



void i2c_burstread(char saddr, char maddr, int n, char *data)
{
	//creating temp variable for address clearing
	volatile int temp;

	//checking bus is busy
	while((I2C1->SR2 & (1U<<1))!=0);

	//START BIT
	I2C1->CR1 |= (1U<<8);

	//WAIT UNTIL START BIT IS GENERATED
	while((I2C1->SR1 & (1U<<0))==0);

	//SEND SLAVE ADDRESS + WRITE
	I2C1->DR = saddr<<1;

	//wait till ADDR BIT IS SET
	while((I2C1->SR1 & (1U<<1))==0);

	//CLEAR ADDR BIT
	temp= I2C1->SR1;
	temp= I2C1->SR2;

	//WAIT UNTIL TXE BIT IS FREE
	while((I2C1->SR1 & (1U<<7))==0);

	//SEND MEMORY  ADDRESS
	I2C1->DR= maddr;

	//wait till it is transmitted
	while((I2C1->SR1 & (1U<<7))==0);

	//RESTART BIT
	I2C1->CR1 |= (1U<<8);

	//WAIT TILL START BIT GENERATED
	while((I2C1->SR1 & (1U<<0))==0);

	//TRANSMIT SLAVE ADDRESS + READ
	I2C1->DR = saddr<<1 | 1;

	//WAIT FOR ADDR BIT
	while((I2C1->SR1 & (1U<<1))==0);

	//SET ACK BIT
	I2C1->CR1 |= (1U<<10);

	//CLEAR ADDR BIT
	temp= I2C1->SR1;
	temp= I2C1->SR2;

	while(n>0)
	{
		if(n==1U)
		{
			//disable ack bit
			I2C1->CR1 &= ~(1U<<10);

			//SEND STOP BIT
			I2C1->CR1 |= (1U<<9);

			//wait till the byte received
			while((I2C1->SR1 & (1U<<6))==0);

			//READ DATA
			*data++ = I2C1->DR;

			break;
		}
		else{

			//WAIT FOR BYTE RECEIVED
			while((I2C1->SR1 & (1U<<6))==0);

			*data++ = I2C1->DR;

			n--;
		}

	}






}


void i2c_byteread(char saddr, char maddr, char *data) //PROBLEM
{
	//temp variable for clearing addr bit
	volatile int temp;

	//wait for bus to free
	while((I2C1->SR2 & (1U<<1))!=0);

	//generate start bit
	I2C1->CR1 |= (1U<<8);

	//WAIT TILL START BIT IS GENERATED
	while((I2C1->SR1 & (1U<<0))==0);



	//slave address + write bit
	I2C1->DR = saddr<<1;


	// PROBLEM


	while((I2C1->SR1 & (1U<<1))==0)
	{
	    if(I2C1->SR1 & (1U<<10)) // AF bit
	    {
			for(int i=0;i<10000000;i++);

	        break;
	    }
	}

	//clearing AF BIT
	I2C1->SR1 &= ~(1U<<10);

	//CLEARING THE ADDRESS BIT
	temp= I2C1->SR1;
	temp= I2C1->SR2;


	//send memory address in slave
	I2C1->DR = maddr;

	//wait until it is transmitted
	while((I2C1->SR1 & (1U<<7))==0);

	//generate start bit for restart
	I2C1->CR1 |= (1U<<8);

	//WAIT TILL START BIT IS GENERATED
	while((I2C1->SR1 & (1U<<0))==0);

	//sending slave address + read
	I2C1->DR = (saddr<<1 | 1);

	//wait till this is sent
	while((I2C1->SR1 & (1U<<1))==0);

	//clear ack to tell the slave this is the last byte
	I2C1->CR1 &= ~(1U<<10);

	//CLEARING THE ADDRESS BIT
	temp= I2C1->SR1;
	temp= I2C1->SR2;

	//setting the stop bit
	I2C1->CR1 |= (1U<<9);

	//WAIT FOR the BYTE TO BE RECEIVED
	while((I2C1->SR1 & (1U<<6))==0);

	*data++ = I2C1->DR;


}

void i2c_gpio_init(void) // NO PROBLEM
{
	//ENABLING GPIOB
	RCC->AHB1ENR |= (1U<<1);

	//SET PB8 AND PB9 AS AF
	GPIOB->MODER |= (1U<<19);
	GPIOB->MODER &= ~(1U<<18);

	GPIOB->MODER |= (1U<<17);
	GPIOB->MODER &= ~(1U<<16);

	//SETTING PA8 AND PA9 AS OPEN DRAIN OUTPUT
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);

	//SETTING PULL UP RESISTOR FOR SDA AND SCL

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &= ~(1U<<19);

	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &= ~(1U<<17);

	//SETTING ALTERNATE FUNCTION FOR PB8 AND PB9
	GPIOB->AFR[1] &= ~(1U<<7);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &= ~(1U<<5);
	GPIOB->AFR[1] &= ~(1U<<4);

	GPIOB->AFR[1] &= ~(1U<<3);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &= ~(1U<<1);
	GPIOB->AFR[1] &= ~(1U<<0);




}


void i2c_config(void) //NO PROBLEM
{
	//gpio pins are initialized for i2c
	i2c_gpio_init();

	//enable bus for i2c1
	RCC->APB1ENR |= (1U<<21);

	//ENTER RESET MODE
	I2C1->CR1 |= (1U<<15);

	//EXIT RESET MODE
	I2C1->CR1 &= ~(1U<<15);

	//SET FREQ
	I2C1->CR2 &= ~(1U<<5);
	I2C1->CR2 |=  (1U<<4);
	I2C1->CR2 &= ~(1U<<3);
	I2C1->CR2 &= ~(1U<<2);
	I2C1->CR2 &= ~(1U<<1);
	I2C1->CR2 &= ~(1U<<0);

	//SET CLOCK MODE
	I2C1->CCR = 80;

	//SETTING TRISE TIME
	I2C1->TRISE = 17;

	//ENABLE I2C1
	I2C1->CR1 |= (1U<<0);


}





