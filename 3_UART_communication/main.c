#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include <pwm.h>
#include "set_duty.h"

int main(void){
	
	double duty = 0;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/* Initialization of the UART communication */
	struct io_descriptor *io;
	uint8_t b = 1;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	
	//PWM to set the desired duty cycle
	tcc_set_period_value(TCC0, 0x1770);
	
	while (1) {
		//if there is an input value from the terminal and assign it to command variable. Then with this command value change the duty cycle of the PWM
		io_read(io,&b,1);
		duty = set_duty(b);
		
		if(duty == 0){
			tcc_set_compare_value(TCC0, 0x0, 0);
		}else if(duty == 0.25){
			tcc_set_compare_value(TCC0, 0x5dc, 0);
		}else if(duty == 0.50){
			tcc_set_compare_value(TCC0, 0xbb8, 0);	
		}else if(duty == 0.75){
			tcc_set_compare_value(TCC0, 0x1194, 0);
		}else if(duty == 1){
			tcc_set_compare_value(TCC0, 0x1770, 0); 
		}
	}
}
