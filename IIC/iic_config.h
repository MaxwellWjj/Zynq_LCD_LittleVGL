/*
 * iic_intr.h
 *
 *  Created on: 2017��3��1��
 * www.osrc.cn
 * www.milinker.com
 * copyright by nan jin mi lian dian zi www.osrc.cn
 */

#ifndef IIC_INTR_H_
#define IIC_INTR_H_

#include "xparameters.h"
#include "xiicps.h"
#include "xscugic.h"
#include "xil_cache.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "sleep.h"


#define IIC_SLAVE_ADDR		0x38     //I2C address of FT5206 in LCD
#define IIC_SCLK_RATE		400000   //400Khz

#define IIC_DEVICE_ID		XPAR_XIICPS_0_DEVICE_ID
#define IIC_INT_VEC_ID		XPAR_XIICPS_0_INTR


volatile u32 IicSendComplete;
volatile u32 IicRecvComplete;
volatile u32 IicTotalErrorCount;

XIicPs IicPs;

void I2C_write(XIicPs *InstancePtr, u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr);
void I2C_read(XIicPs *InstancePtr, u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr);
int Iic_init(XIicPs *InstancePtr, u16 DeviceId, u32 sclk_rate);


#endif /* IIC_INTR_H_ */
