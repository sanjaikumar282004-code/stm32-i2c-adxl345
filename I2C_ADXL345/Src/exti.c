
#include "stm32f4xx.h"

#define GPIOCEN (1U<<2)
#define SYSCFGEN (1U<<14)

void exti_PC13_init(void)
{
	//disable global interrupt
	__disable_irq();

	//enable clock for gpioc
	RCC->AHB1ENR |= GPIOCEN;

	//enable clock for sysconfig for exti
	RCC->APB2ENR |= SYSCFGEN;

	//SET PC13 HAS INPUT
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	//SET PC13 AS INTERRUPT FOR EXTI13
	SYSCFG->EXTICR[3] &= ~(1U<<4);
	SYSCFG->EXTICR[3] |= (1U<<5);
	SYSCFG->EXTICR[3] &= ~(1U<<6);
	SYSCFG->EXTICR[3] &= ~(1U<<7);

	//UNMASK EXTI13 FOR PC13 INTERRUPT
	EXTI->IMR |= (1U<<13);

	//ENABLE FALLING TRIGGER SELECTION REGISTER FOR EXTI13
	EXTI->FTSR |= (1U<<13);

	//ENABLE INTERRUPT FOR EXTI15_10 IN NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//enable global interrupt
	__enable_irq();
}


