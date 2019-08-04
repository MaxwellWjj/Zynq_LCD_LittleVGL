#include "iic_config.h"

void I2C_write(XIicPs *InstancePtr, u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr)
{

	int Status;
	XIicPs *Iic;
	Iic = InstancePtr;

	while (XIicPs_BusIsBusy(Iic)) {
		/* NOP */
	}

	/*
	 * Send data to slave, errors are reported
	 */
	Status = XIicPs_MasterSendPolled(Iic, MsgPtr,
			ByteCount, SlaveAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("I2C write error! %d\r\n", Status);
		return;
	}

	//xil_printf("I2C write done!\r\n");

}

void I2C_read(XIicPs *InstancePtr, u8 *MsgPtr, s32 ByteCount, u16 SlaveAddr)
{

	XIicPs *Iic;
	Iic = InstancePtr;
	int Status;

	while (XIicPs_BusIsBusy(Iic)) {
		/* NOP */
	}

	/*
	 * Receive data from slave, errors are reported
	 */

	Status = XIicPs_MasterRecvPolled(Iic, MsgPtr, ByteCount, SlaveAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("I2C read error! %d\r\n", Status);
		return;
	}

}

int Iic_init(XIicPs *InstancePtr, u16 DeviceId, u32 sclk_rate)
{
	int Status;
	XIicPs_Config *Config;


	/*
	 * Initialize the IIC driver so that it's ready to use
	 * Look up the configuration in the config table, then initialize it.
	 */
	Config = XIicPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		xil_printf("NO I2C CONFIG !\r\n");
		return XST_FAILURE;
	}

	Status = XIicPs_CfgInitialize(InstancePtr, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("IIC cfg failed!\r\n");
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XIicPs_SelfTest(InstancePtr);
	if (Status != XST_SUCCESS) {
		xil_printf("IIC selftest failed!\r\n");
		return XST_FAILURE;
	}

//	/*
//	 * Setup the handlers for the IIC that will be called from the
//	 * interrupt context when data has been sent and received, specify a
//	 * pointer to the IIC driver instance as the callback reference so
//	 * the handlers are able to access the instance data.
//	 */
//	XIicPs_SetStatusHandler(InstancePtr, (void *) InstancePtr, Iic_Handler);
//
	/*
	 * Set the IIC serial clock rate.
	 */
	XIicPs_SetSClk(InstancePtr, sclk_rate);

	IicSendComplete = 0;
	IicRecvComplete = 0;
	IicTotalErrorCount = 0;

	return XST_SUCCESS;
}
