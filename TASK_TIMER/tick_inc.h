/*
 *
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
*/

#ifndef TIMER_INTR_H_
#define TIMER_INTR_H_

#include <stdio.h>
#include "xadcps.h"
#include "xil_types.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xscutimer.h"
#include "xil_cache.h"
#include "../lvgl/lvgl.h"

XScuTimer Timer;//timer

//timer info
#define TIMER_DEV_ID        XPAR_XSCUTIMER_0_DEVICE_ID
#define TIMER_IRPT_INTR     XPAR_SCUTIMER_INTR
#define TIMER_LOAD_VALUE    XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2000 // 20ms

void Timer_start(XScuTimer *TimerPtr);
void Timer_Setup_Intr_System(XScuGic *GicInstancePtr,XScuTimer *TimerInstancePtr, u16 TimerIntrId);
int Timer_init(XScuTimer *TimerPtr,u32 Load_Value,u32 DeviceId);
#endif /* TIMER_INTR_H_ */
