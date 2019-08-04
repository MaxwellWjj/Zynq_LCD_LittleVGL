/*
 * vdma_config.h
 *
 *  Created on: 2017��2��17��
 *      Author: 201607062058
 */

#ifndef VDMA_CONFIG_H_
#define VDMA_CONFIG_H_

#include "xaxivdma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"

#define AXI_VDMA_DEV_ID		    XPAR_AXIVDMA_0_DEVICE_ID

#define VDMA_INTR_ID		XPAR_FABRIC_AXI_VDMA_0_MM2S_INTROUT_INTR


#define IMAGE_WIDTH     1024
#define IMAGE_HEIGHT	600
#define BYTES_PER_PIXEL	4

#define NUMBER_OF_READ_FRAMES  1

#define MEM_BASE_ADDR		0x10000000
#define BUFFER0_BASE		(MEM_BASE_ADDR)

XAxiVdma AxiVdma;

void Vdma_Setup_Intr_System(XScuGic *GicInstancePtr, XAxiVdma *InstancePtr, u16 IntrId);
void ReadErrorCallBack(void *CallbackRef, u32 Mask);
void Vdma_Init(XAxiVdma *InstancePtr, u32 DeviceId);
int ReadSetup(XAxiVdma *InstancePtr);
int Vdma_Start(XAxiVdma *InstancePtr);

#endif /* VDMA_CONFIG_H_ */
