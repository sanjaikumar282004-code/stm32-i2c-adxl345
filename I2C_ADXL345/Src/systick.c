#include "stm32f4xx.h"

//CALCULATED MANUALLY IN NOTE
#define SYSTICK_LOAD_VALUE 16000
#define ENABLE_COUNTER     (1U<<0)
#define SYSTICK_1S         16000000

void systick_ms(int delay)
{
	//SYSTICK_RVR == LOAD
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	//systick_cvr == VAL
	SysTick->VAL = 0;

	//ENABLE SYSTEM CLOCK
	//SYSTICK_CSR== CTRL

	//ENABLE COUNTER
	SysTick->CTRL |= ENABLE_COUNTER;

	//ENABLE PROCESSOR CLOCK
	SysTick->CTRL |= (1U<<2);


	for(int i=0;i<delay;i++)
	{
		//CHECK COUNT FLAG FOR COUNTING FINISHED
		while((SysTick->CTRL & (1U<<16)) == 0);
	}

	//stop systick
	SysTick->CTRL =0;

}

void systick_init(void)
{
	//SYSTICK_RVR == LOAD
	SysTick->LOAD = SYSTICK_1S;

	//systick_cvr == VAL
	SysTick->VAL = 0;

	//ENABLE SYSTEM CLOCK
	//SYSTICK_CSR== CTRL

	//ENABLE COUNTER
	SysTick->CTRL |= ENABLE_COUNTER;

	//ENABLE PROCESSOR CLOCK
	SysTick->CTRL |= (1U<<2);

	//ENABLE THE INTERRUPT
	SysTick->CTRL |= (1U<<1);

}
