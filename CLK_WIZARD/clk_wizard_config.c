/*
 * clk_wizard_config.c
 *
 *  Created on: 2017Äê2ÔÂ27ÈÕ
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 */

#include "clk_wizard_config.h"

/*****************************************************************************/
/**
*
* This is the Wait_For_Lock function, it will wait for lock to settle change
* frequency value
*
* @param	CfgPtr_Dynamic provides pointer to clock wizard dynamic config
*
* @return
*		- Error 0 for pass scenario
*		- Error > 0 for failure scenario
*
* @note		None
*
******************************************************************************/
int Wait_For_Lock(XClk_Wiz_Config *CfgPtr_Dynamic)
{
	u32 Count = 0;
	u32 Error = 0;

	while(!(*(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK)) {
		if(Count == 10000) {
			Error++;
			break;
		}
		Count++;
        }
    return Error;
}

/*****************************************************************************/
/**
*
* This is the Clk_Wiz_Reconfig function, it will reconfigure frequencies as
* per input array
*
* @param	CfgPtr_Dynamic provides pointer to clock wizard dynamic config
* @param	Findex provides the index for Frequency divide register
* @param	Sindex provides the index for Frequency phase register
*
* @return
*		-  Error 0 for pass scenario
*		-  Error > 0 for failure scenario
*
* @note	 None
*
******************************************************************************/
int Clk_Wiz_Reconfig(XClk_Wiz_Config *CfgPtr_Dynamic)
{
    u32 Count = 0;
    u32 Error = 0;
    u32 Fail  = 0;
    u32 Frac_en = 0;
    u32 Frac_divide = 0;
    u32 Divide = 0;
    float Freq = 0.0;

    Fail = Wait_For_Lock(CfgPtr_Dynamic);
    if(Fail) {
	Error++;
        xil_printf("\n ERROR: Clock is not locked for default frequency" \
	" : 0x%x\n\r", *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
     }

    /* SW reset applied */
    *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x00) = 0xA;

    if(*(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK) {
	Error++;
        xil_printf("\n ERROR: Clock is locked : 0x%x \t expected "\
	  "0x00\n\r", *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    }

    /* Wait cycles after SW reset */
    for(Count = 0; Count < 2000; Count++);

    Fail = Wait_For_Lock(CfgPtr_Dynamic);
    if(Fail) {
	  Error++;
          xil_printf("\n ERROR: Clock is not locked after SW reset :"
	      "0x%x \t Expected  : 0x1\n\r",
	      *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    }

    /* Calculation of Input Freq and Divide factors*/
    Freq = (CLK_WIZ_VCO_FACTOR/DYNAMIC_INPUT_FREQ_FACTOR);

    Divide = Freq;
    Freq = (float)(Freq - Divide);

    Frac_divide = Freq * 10000;

    if(Frac_divide % 10 > 5) {
	   Frac_divide = Frac_divide + 10;
    }
    Frac_divide = Frac_divide/10;

    if(Frac_divide > 1023 ) {
	   Frac_divide = Frac_divide / 10;
    }

    if(Frac_divide) {
	   /* if fraction part exists, Frac_en is shifted to 26
	    * for input Freq */
	   Frac_en = (CLK_FRAC_EN << 26);
    }
    else {
	   Frac_en = 0;
    }

    /* Configuring Multiply and Divide values */
    *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x200) = \
	Frac_en | (Frac_divide << 16) | (Divide << 8) | 0x01;
    *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x204) = 0x00;

    /* Calculation of Output Freq and Divide factors*/
    Freq = (CLK_WIZ_VCO_FACTOR / DYNAMIC_OUTPUT_FREQFACTOR);

    Divide = Freq;
    Freq = (float)(Freq - Divide);

    Frac_divide = Freq * 10000;

    if(Frac_divide%10 > 5) {
	Frac_divide = Frac_divide + 10;
    }
    Frac_divide = Frac_divide / 10;

    if(Frac_divide > 1023 ) {
        Frac_divide = Frac_divide / 10;
    }

    if(Frac_divide) {
	/* if fraction part exists, Frac_en is shifted to 18 for output Freq */
	Frac_en = (CLK_FRAC_EN << 18);
    }
    else {
	Frac_en = 0;
    }

    /* Configuring Multiply and Divide values */
    *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x208) =
	    Frac_en | (Frac_divide << 8) | (Divide);
    *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x20C) = 0x00;

    /* Load Clock Configuration Register values */
    *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x25C) = 0x07;

    if(*(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK) {
	Error++;
        xil_printf("\n ERROR: Clock is locked : 0x%x \t expected "
	    "0x00\n\r", *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
     }

     /* Clock Configuration Registers are used for dynamic reconfiguration */
     *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x25C) = 0x02;

    Fail = Wait_For_Lock(CfgPtr_Dynamic);
    if(Fail) {
	Error++;
        xil_printf("\n ERROR: Clock is not locked : 0x%x \t Expected "\
	": 0x1\n\r", *(u32 *)(CfgPtr_Dynamic->BaseAddr + 0x04) & CLK_LOCK);
    }
	return Error;
}


void Clk_wizard_init(XClk_Wiz *InstancePtr, u32 DeviceId)
{
	int Status;
	XClk_Wiz_Config *CfgPtr_Dynamic;

	/*
	 * Get the CLK_WIZ Dynamic reconfiguration driver instance
	 */
	CfgPtr_Dynamic = XClk_Wiz_LookupConfig(DeviceId);
	if (!CfgPtr_Dynamic) {
		xil_printf("ERR:: CLK device not found\r\n");
		return;
	}

	/*
	 * Initialize the CLK_WIZ Dynamic reconfiguration driver
	 */
	Status = XClk_Wiz_CfgInitialize(InstancePtr, CfgPtr_Dynamic, CfgPtr_Dynamic->BaseAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("ERR:: CLK Wizard Initialization failed failed %d\r\n", Status);
		return;
	}


	Clk_Wiz_Reconfig(CfgPtr_Dynamic);

}
