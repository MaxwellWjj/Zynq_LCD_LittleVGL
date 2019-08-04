#include "gpiopl_config.h"
#include "stdio.h"

void GpioplIntrHandler(void *Callback)
{
	XGpio *GpioPtr = (XGpio *)Callback;
	u32 IrqStatus;
	u32 gpio;
	u8 regaddress;

	IrqStatus = XGpio_InterruptGetStatus(GpioPtr);

	XGpio_InterruptDisable(GpioPtr, TOUCH_INTR_MASK);

	if((IrqStatus & GPIO_INTR_MASK) == GPIO_INTR_MASK)
	{
		gpio = XGpio_DiscreteRead(GpioPtr, 1);

		/*when touch interrupt input is low*/
		if((~gpio) & TOUCH_INTR_MASK)
		{
			regaddress = 2;
			/*read touch information from FT5206 in LCD*/
			I2C_write(&IicPs, &regaddress, 1, IIC_SLAVE_ADDR);
	    	I2C_read(&IicPs, readbuffer, 29, IIC_SLAVE_ADDR);
			touch_flag = 1;
		}

	}

//	printf("touch\n");
	XGpio_InterruptClear(GpioPtr, IrqStatus);

	XGpio_InterruptEnable(GpioPtr, TOUCH_INTR_MASK);

}


void Gpiopl_Setup_Intr_System(XScuGic *GicInstancePtr, XGpio *InstancePtr, u16 IntrId)
{
        XScuGic_Connect(GicInstancePtr, IntrId,
                        (Xil_ExceptionHandler)GpioplIntrHandler,//set up the timer interrupt
                        (void *)InstancePtr);

        XScuGic_Enable(GicInstancePtr, IntrId);//enable the interrupt for the Timer at GIC

    	XGpio_InterruptEnable(InstancePtr, GPIO_INTR_MASK);
    	XGpio_InterruptGlobalEnable(InstancePtr);

 }

int Gpiopl_init(XGpio *InstancePtr, u32 DeviceId)
{

	int Status;
	/* Initialize AXI GPIO */
	Status = XGpio_Initialize(InstancePtr, DeviceId);
	if (Status != XST_SUCCESS) {
		xil_printf("AXI GPIO config failed!\r\n");
		return XST_FAILURE;
	}

	XGpio_SetDataDirection(InstancePtr, 1, DATA_DIRECTION_MASK);

	XGpio_DiscreteClear(InstancePtr, 1, 0x000001FF);

	touch_flag = 0;
	gpio_output_state = 0;

    return 1;
}
