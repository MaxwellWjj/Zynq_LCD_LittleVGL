/*
 * pwm_config.c
 *
 *  Created on: 2017Äê2ÔÂ27ÈÕ
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 */

#include "pwm_config.h"

void PWM_Init(u32 baseAddr, u32 period_clocks, u32 duty_clocks, u32 pwmIndex)
{

	PWM_Set_Period(baseAddr, period_clocks);

	PWM_Set_Duty(baseAddr, duty_clocks, pwmIndex);
}


void PWM_increase_duty(u32 baseAddr, u32 clocks, u32 pwmIndex)
{
	u32 duty;

	duty = PWM_Get_Duty(baseAddr, pwmIndex);

	if((duty + clocks) <= PERIOD_CLOCK_NUM)
	{
		PWM_Set_Duty(baseAddr, (duty + clocks), pwmIndex);
	}

}

void PWM_decrease_duty(u32 baseAddr, u32 clocks, u32 pwmIndex)
{
	u32 duty;
	s32 s;

	duty = PWM_Get_Duty(baseAddr, pwmIndex);

	s = duty - clocks;

	if(s >= 0)
	{
		PWM_Set_Duty(baseAddr, (duty - clocks), pwmIndex);
	}

}
