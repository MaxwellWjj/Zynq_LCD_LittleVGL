/*
 * vdma_config.c
 *
 *  Created on: 2017��2��17��
 *      Author: 201607062058
 */


#include "vdma_config.h"


void Vdma_Setup_Intr_System(XScuGic *GicInstancePtr, XAxiVdma *InstancePtr, u16 IntrId)
{
        XScuGic_Connect(GicInstancePtr, IntrId,
                        (Xil_ExceptionHandler)XAxiVdma_ReadIntrHandler,
                        InstancePtr);

        XScuGic_Enable(GicInstancePtr, IntrId);

        XAxiVdma_SetCallBack(InstancePtr, XAXIVDMA_HANDLER_ERROR, ReadErrorCallBack, (void *)InstancePtr, XAXIVDMA_READ);
        XAxiVdma_IntrEnable(InstancePtr, XAXIVDMA_IXR_ERROR_MASK, XAXIVDMA_READ);
 }

void ReadErrorCallBack(void *CallbackRef, u32 Mask)
{

	if (Mask & XAXIVDMA_IXR_ERROR_MASK)
	{
		xil_printf("VDMA READ ERROR!\r\n" );
	}
}

void Vdma_Init(XAxiVdma *InstancePtr, u32 DeviceId)
{

	XAxiVdma_Config *Config;
	int Status;

	Config = XAxiVdma_LookupConfig(DeviceId);
	if (!Config) {
		xil_printf("No video DMA found for ID %d\r\n",DeviceId );
		return;
	}

	/* Initialize DMA engine */
	Status = XAxiVdma_CfgInitialize(InstancePtr, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("Configuration Initialization failed %d\r\n", Status);
		return;
	}

//	Status = XAxiVdma_SetFrmStore(InstancePtr, NUMBER_OF_READ_FRAMES, XAXIVDMA_READ);
//	if (Status != XST_SUCCESS) {
//
//		xil_printf(
//		    "Setting Frame Store Number Failed in Read Channel"
//							" %d\r\n", Status);
//		return;
//	}

	ReadSetup(InstancePtr);
}

/*****************************************************************************/
/**
*
* This function sets up the read channel
*
* @param	InstancePtr is the instance pointer to the DMA engine.
*
* @return	XST_SUCCESS if the setup is successful, XST_FAILURE otherwise.
*
* @note		None.
*
******************************************************************************/
int ReadSetup(XAxiVdma *InstancePtr)
{
	int Index;
	UINTPTR Addr;
	int Status;
	XAxiVdma_DmaSetup ReadCfg;

	ReadCfg.VertSizeInput = IMAGE_HEIGHT;
	ReadCfg.HoriSizeInput = IMAGE_WIDTH * BYTES_PER_PIXEL;

	ReadCfg.Stride = IMAGE_WIDTH * BYTES_PER_PIXEL;
	ReadCfg.FrameDelay = 0;  /* This example does not test frame delay */

	ReadCfg.EnableCircularBuf = 1;
	ReadCfg.EnableSync = 0;  /* No Gen-Lock */

	ReadCfg.PointNum = 0;    /* No Gen-Lock */
	ReadCfg.EnableFrameCounter = 0; /* Endless transfers */

	ReadCfg.FixedFrameStoreAddr = 0; /* We are not doing parking */

	Status = XAxiVdma_DmaConfig(InstancePtr, XAXIVDMA_READ, &ReadCfg);
	if (Status != XST_SUCCESS) {
		xil_printf(
		    "Read channel config failed %d\r\n", Status);

		return XST_FAILURE;
	}

	/* Initialize buffer addresses
	 *
	 * These addresses are physical addresses
	 */
	Addr = BUFFER0_BASE;
	for(Index = 0; Index < NUMBER_OF_READ_FRAMES; Index++) {
		ReadCfg.FrameStoreStartAddr[Index] = Addr;

		Addr += IMAGE_WIDTH * BYTES_PER_PIXEL * IMAGE_HEIGHT;
	}

	/* Set the buffer addresses for transfer in the DMA engine
	 * The buffer addresses are physical addresses
	 */
	Status = XAxiVdma_DmaSetBufferAddr(InstancePtr, XAXIVDMA_READ,
			ReadCfg.FrameStoreStartAddr);
	if (Status != XST_SUCCESS) {
		xil_printf(
		    "Read channel set buffer address failed %d\r\n", Status);

		return XST_FAILURE;
	}

	return XST_SUCCESS;
}


int Vdma_Start(XAxiVdma *InstancePtr)
{
	int Status;

	Status = XAxiVdma_DmaStart(InstancePtr, XAXIVDMA_READ);
	if (Status != XST_SUCCESS) {
		xil_printf(
		    "Start read transfer failed %d\r\n", Status);

		return XST_FAILURE;
	}

	return XST_SUCCESS;
}
