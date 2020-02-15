#ifndef __DELAY_H__ 
#define __DELAY_H__

#include<LPC17xx.h>

void delayms(uint32_t);
void delayus(uint32_t);



void delayms(uint32_t delayms)
{
	LPC_TIM0 -> TCR = 0x02;		/* reset timer */
	LPC_TIM0 -> PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM0 -> MR0 = (delayms * (25000000 / 1000));
	LPC_TIM0 -> IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM0 -> MCR = 0x04;		/* stop timer on match */
	LPC_TIM0 -> TCR = 0x01;		/* start timer */
	while (LPC_TIM0 -> TCR & 0x01);
}

void delayus(uint32_t delayus) //steps 0f 1us
{
	LPC_TIM0 -> TCR = 0x02;		/* reset timer */
	LPC_TIM0 -> PR  = 0x00;		/* set prescaler to zero */
	LPC_TIM0 -> MR1 = (delayus * (25000000 / 1000000));
	LPC_TIM0 -> IR  = 0xff;		/* reset all interrrupts */
	LPC_TIM0 -> MCR = 0x20;		/* stop timer on match */
	LPC_TIM0 -> TCR = 0x01;		/* start timer */
	while (LPC_TIM0 -> TCR & 0x01);
}
#endif
