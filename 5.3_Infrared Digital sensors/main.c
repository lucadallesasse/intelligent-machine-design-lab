#include <atmel_start.h>
#include "custom_functions.h"
#include <pwm.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Initialization of the UART communication */
	static struct io_descriptor *io1;
	uint8_t buff = 0;
	usart_sync_get_io_descriptor(&EDBG_UART, &io1);
	usart_sync_enable(&EDBG_UART);
	
	/* Initialization of the UART communication */
	static struct io_descriptor *io2;
	uint8_t out_buff = 0;
	uint8_t in_buff = 0;
	usart_sync_get_io_descriptor(&UART, &io2);
	usart_sync_enable(&UART);
	
	//PWM to set the desired duty cycle
	tcc_set_period_value(TCC0, 0x1770);
	
	while (1){
		
		//Read input command from terminal
		io_read(io1,&buff,1);
		
		if(buff == 1){
			//LED off
			out_buff = 0;
			//tcc_set_compare_value(TCC0, 0x0, 0);
		}else if(buff == 0){
			//LED on
			out_buff = 1;
			//tcc_set_compare_value(TCC0, 0x1770, 0);
		}
		//Write to the UART_TX channel to drive the transistor	
		io_write(io2,&out_buff,1);
		//read the CMOS output of the phototransistor
		io_read(io2,&in_buff,1);
		//Output 'Ecco' when the phototransistor is not blocked
		if( in_buff == 0){
			io_write(io1,(uint8_t *)"Ecco\n", 6);
		}
	}
	
	return 0;
}
