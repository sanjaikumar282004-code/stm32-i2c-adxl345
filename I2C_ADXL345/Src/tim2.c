/*
 * tim2.c
 *
 *  Created on: May 21, 2026
 *      Author: sanja
 */

#include "stm32f4xx.h"

void tim3_input_capture_init(void)
{
	//Enable GPIOA FOR PA6
	RCC->AHB1ENR |= (1U<<0);

	//SET PA6 AS ALTERNATE FUNCTION
	GPIOA->MODER |= (1U<<13);
	GPIOA->MODER &= ~(1U<<12);

	//SET PA6-> TIM3CH1
	GPIOA->AFR[0] &= ~(1U<<27);
	GPIOA->AFR[0] &= ~(1U<<26);
	GPIOA->AFR[0] |= (1U<<25);
	GPIOA->AFR[0] &= ~(1U<<24);

	//ENABLE TIMER 3
	RCC->APB1ENR |= (1U<<1);

	//SET COUNTER CLOCK
	TIM3->PSC = 1599;

	//ENABLE INPUT MODE IN TIMER3
	TIM3->CCMR1 |= (1U<<0);
	TIM3->CCMR1 &= ~(1U<<1);

	//ENABLE CAPTURE MODE
	TIM3->CCER |= (1U<<0);

	//START THE TIMER 3
	TIM3->CR1 |= (1U<<0);


}




void tim2_output_capture_init(void)
{
	//Enable GPIOA
	RCC->AHB1ENR |= (1U<<0);

	//SET PA5 AS ALTERNATE FUNCTION
	GPIOA->MODER |= (1U<<11);
	GPIOA->MODER &= ~(1U<<10);

	//PA5-> TIM2 CH1
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] &= ~(1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	//ENABLE TIMER 2
	RCC->APB1ENR |= (1U<<0);

	//SETTING COUNTER CLOCK VALUE
	TIM2->PSC = 1599;

	//SETTING PERIOD
	TIM2->ARR = 9999;

	//SETTING TOGGLE OUTPUT COMPARE MODE
	TIM2->CCMR1 &= ~(1U<<6);
	TIM2->CCMR1 |= (1U<<5);
	TIM2->CCMR1 |= (1U<<4);

	//ENABLING TIMER 2 CAPTURE/COMPARE MODE
	TIM2->CCER |= (1U<<0);

	//CLEARING THE COUNTING REGISTER
	TIM2->CNT =0;

	//ENABLE COUNTER
	TIM2->CR1 |= (1U<<0);



}


void tim2_1s_init(void)
{
	//Enable clock for Timer 2 or APB1ENR
	RCC->APB1ENR |= (1U<<0);

	//SET PRESCALAR VALUE
	TIM2->PSC = 1599;

	//SET ARR or PERIOD VALUE
	TIM2->ARR = 9999;

	//CLEAR THE COUNTING REGISTER
	TIM2->CNT = 0;

	//ENABLE THE COUNTER
	TIM2->CR1 |= (1U<<0);

}

void tim2_10s_interrupt_init(void)
{
	//Enable clock for Timer 2 or APB1ENR
	RCC->APB1ENR |= (1U<<0);

	//SET PRESCALAR VALUE
	TIM2->PSC = 1599;

	//SET ARR or PERIOD VALUE
	TIM2->ARR = 99999;

	//CLEAR THE COUNTING REGISTER
	TIM2->CNT = 0;

	//ENABLE THE COUNTER
	TIM2->CR1 |= (1U<<0);

	//ENABLE THE INTERRUPT
	TIM2->DIER |= (1U<<0);

	NVIC_EnableIRQ(TIM2_IRQn);

}

