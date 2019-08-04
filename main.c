#include "init.h"
#include "DELAY/delay.h"
#include "GUI/ui.h"

volatile u8 tx_buffer_index;
volatile u8 rx_buffer_index;

int main(void)
{
	system_initialize();
	lv_test_theme_2();
	while(1){
		lv_task_handler();
		delay_ms(10);
		Xil_DCacheFlushRange((INTPTR)BufferPtr, 1024 * 600 * 4);
	}
	return XST_SUCCESS;
}

