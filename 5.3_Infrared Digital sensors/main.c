#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include <pwm.h>

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/* Initialization of the UART communication */
	struct io_descriptor *io1;
	uint8_t buff = 0;
	usart_sync_get_io_descriptor(&USART_0, &io1);
	usart_sync_enable(&USART_0);
	
	/* Initialization of the UART communication */
	static struct io_descriptor *io2;
	static uint8_t out_buff = 0;
	static uint8_t in_buff = 0;
	usart_async_get_io_descriptor(&USART_1, &io2);
	usart_async_enable(&USART_1);
	
	while (1) {
		
		//Read input command from terminal
		io_read(io1,&buff,1);
	
		if(buff == 49){
			//LED off
			out_buff = 0;
		}else if(buff == 48){
			//LED on
			out_buff = 1;
		}
		//Write to the UART_TX channel to drive the transistor
		io_write(io2,&out_buff,1);

	
		//read the CMOS output of the phototransistor
		//io_read(io2,&in_buff,1);
		//Output 'Ecco' when the phototransistor is not blocked
		//io_write(io1,&in_buff, 1);
	}
}
