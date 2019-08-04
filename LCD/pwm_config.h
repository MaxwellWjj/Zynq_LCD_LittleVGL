/*
 * pwm_config.h
 *
 *  Created on: 2017Äê2ÔÂ27ÈÕ
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 */

#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_

#include "PWM.h"
#include "xil_types.h"
#include "xil_printf.h"

#define PWM_DEV_BASEADDR        XPAR_PWM_0_PWM_AXI_BASEADDR

#define PERIOD_CLOCK_NUM        409600  //4.096ms
#define DUTY_CLOCK_NUM          204800
#define PWM_INDEX               0


void PWM_Init(u32 baseAddr, u32 period_clocks, u32 duty_clocks, u32 pwmIndex);
void PWM_increase_duty(u32 baseAddr, u32 clocks, u32 pwmIndex);
void PWM_decrease_duty(u32 baseAddr, u32 clocks, u32 pwmIndex);


#endif /* PWM_CONFIG_H_ */
