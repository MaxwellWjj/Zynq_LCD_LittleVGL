/*
 * clk_wizard_config.h
 *
 *  Created on: 2017Äê2ÔÂ27ÈÕ
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 */

#ifndef CLK_WIZARD_CONFIG_H_
#define CLK_WIZARD_CONFIG_H_

#include "xil_types.h"
#include "xstatus.h"
#include "xclk_wiz.h"


#define CLK_DEV_ID              XPAR_CLK_WIZ_0_DEVICE_ID
/*
* The following constants are part of clock dynamic reconfiguration
* They are only defined here such that a user can easily change
* needed parameters
*/

#define CLK_LOCK			1

/*FIXED Value */
#define VCO_FREQ			600
#define CLK_WIZ_VCO_FACTOR		(VCO_FREQ * 10000)

 /*Input frequency in MHz */
#define DYNAMIC_INPUT_FREQ		100
#define DYNAMIC_INPUT_FREQ_FACTOR	(DYNAMIC_INPUT_FREQ * 10000)

/*
 * Output frequency in MHz. User need to change this value to
 * generate grater/lesser interrupt as per input frequency
 */
#define DYNAMIC_OUTPUT_FREQ		51.2
#define DYNAMIC_OUTPUT_FREQFACTOR	(DYNAMIC_OUTPUT_FREQ * 10000)

#define CLK_FRAC_EN			1

#define CLK_WIZ_RECONFIG_OUTPUT		DYNAMIC_OUTPUT_FREQ

XClk_Wiz ClkWiz;

int Wait_For_Lock(XClk_Wiz_Config *CfgPtr_Dynamic);
int Clk_Wiz_Reconfig(XClk_Wiz_Config *CfgPtr_Dynamic);
void Clk_wizard_init(XClk_Wiz *InstancePtr, u32 DeviceId);

#endif /* CLK_WIZARD_CONFIG_H_ */
