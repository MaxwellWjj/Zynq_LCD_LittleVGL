#ifndef _INIT_H_
#define _INIT_H_

#include "LCD/vdma_config.h"
#include "LCD/vtc_config.h"
#include "LCD/pwm_config.h"
#include "CLK_WIZARD/clk_wizard_config.h"
#include "GPIO/gpiopl_config.h"
#include "IIC/iic_config.h"
#include "lvgl/lvgl.h"
#include "lvgl/porting/lv_port_disp.h"
#include "lvgl/porting/lv_port_indev.h"
#include "SYS/sys_config.h"
#include "TASK_TIMER/tick_inc.h"

void system_initialize(void);

#endif
