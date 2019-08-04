/*
 * delay.c
 *
 *  Created on: 2017��11��4��
 *      Author: 81967
 */

#include "delay.h"

void delay_us(u16 t)
{
	u32 i;
	u8 j;

	for(i=0;i<t;i++)
	{
		for(j=0;j<10;j++)
		{
			__asm("nop");
			__asm("nop");
			__asm("nop");
			__asm("nop");
			__asm("nop");
			__asm("nop");
			__asm("nop");
			__asm("nop");
		}
	}
}
void delay_ms(u16 ms)
{
	int i=0;
	int j=0;
	for(i=0;i<ms;i++)
		for(j=0;j<10;j++)
			delay_us(100);
}




