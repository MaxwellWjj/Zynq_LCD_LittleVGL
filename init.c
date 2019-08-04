#include "init.h"

void system_initialize(){
	/************ 初始化外设 ************/

	Clk_wizard_init(&ClkWiz, CLK_DEV_ID);
	Timer_init(&Timer, TIMER_LOAD_VALUE, TIMER_DEV_ID);
	Iic_init(&IicPs, IIC_DEVICE_ID, IIC_SCLK_RATE);
	Gpiopl_init(&Gpio, AXI_GPIO_DEV_ID);
	Vtc_init(&Vtc, VTC_DEV_ID, &Vtc_timing, VIDEO_RESOLUTION_WSVGA);
	Vdma_Init(&AxiVdma, AXI_VDMA_DEV_ID);
	PWM_Init(PWM_DEV_BASEADDR, PERIOD_CLOCK_NUM, DUTY_CLOCK_NUM, PWM_INDEX);
	Init_Intr_System(&Intc);
	Timer_Setup_Intr_System(&Intc, &Timer, TIMER_IRPT_INTR);
	Gpiopl_Setup_Intr_System(&Intc, &Gpio, GPIO_INTR_ID);
    Vdma_Setup_Intr_System(&Intc, &AxiVdma, VDMA_INTR_ID);
	Setup_Intr_Exception(&Intc);
	PWM_Enable(PWM_DEV_BASEADDR);
	gpio_output_state = gpio_output_state | LCD_BL_EN_MASK;
	XGpio_DiscreteWrite(&Gpio, 1, gpio_output_state);

	/************ 初始化外设 ************/

	/************ 初始化图形库 ************/

	lv_init();	//初始化lvgl
	lv_port_disp_init(); //初始化lvgl显示驱动
	lv_port_indev_init(); //初始化lvgl触摸驱动
	Timer_start(&Timer);  //开启定时器，驱动图形库
	Vdma_Start(&AxiVdma); //开启VDMA，屏幕显示

	/************ 初始化图形库 ************/

}
