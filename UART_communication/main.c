#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include <pwm.h>


void PWM_genrt(uint16_t period, uint16_t duty)
{
	tcc_disable(TCC0);
	tcc_set_period_value(TCC0, period);
	tcc_set_compare_value(TCC0, duty, 0);
	tcc_enable(TCC0);
}


double set_duty(uint8_t number){
	
	static int CurrentState = 0;
	static double output = 0;

// 	number 0 -> ASCII 48 -> binary 110000
// 	number 1 -> ASCII 49 -> binary 110001
// 	number 2 -> ASCII 50 -> binary 110010
// 	number 3 -> ASCII 51 -> binary 110011
// 	number 4 -> ASCII 52 -> binary 110100
// 	   +     -> ASCII 43 -> binary 101011
// 	   -     -> ASCII 45 -> binary 101101

	if(number != 48 && number != 49 && number != 50 && number != 51 && number != 52 && number != 43 && number != 45){
		CurrentState = 0;
	}else{
		CurrentState = number;
	}
	
	switch (CurrentState){
		case 48:
			output = 0;
		break;
		case 49:
			output = 0.25;
		break;
		case 50:
			output = 0.5;
		break;
		case 51:
			output = 0.75;
		break;
		case 52:
			output = 1;
		break;
		case 43:
			output += 0.25;
		break;
		case 45:
			output -= 0.25;
		break;
		case 0:
			output = 0;
		break;
	}
	
	//check that the value of duty is between 0 and 1
	if(output >= 1.0){
		output = 1.0;
	}else if(output <= 0.0){
		output = 0.0;
	}
 	return output;	
}

int main(void){
	
	double duty = 0;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/* Initialization of the UART communication */
	struct io_descriptor *io;
	uint8_t b = 1;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	
	while (1) {
		//io_write(io, (uint8_t *)"Hello World!", 12);
		//if there is an input value from the terminal and assign it to command variable. Then with this command value change the duty cycle of the PWM
		io_read(io,&b,1);
		duty = set_duty(b);
		
		//PWM to set the desired duty cycle
 		PWM_0_init();
		if(duty == 0){
// 			tcc_disable(TCC0);
// 			//printf("1KHz PWM Waveform output available on WO[1] PIN\r\n");
// 			//tcc_set_compare_value(TCC0, duty*VALUE_FOR_100perc, COMPARE_CHANNEL_0); //green_led at 100Hz
// 			tcc_set_compare_value(TCC0, 0x2ee0, COMPARE_CHANNEL_0);
// 			tcc_enable(TCC0);
			//PWM_genrt(0xffff,0x0000);
			tcc_disable(TCC0);
		}else if(duty == 0.25){
			PWM_genrt(0x1770,0xffff/900000);
		//}else if(duty == 0.50){
			//PWM_genrt(0x1770,0xffff/800);	
		//}else if(duty == 0.75){
			//PWM_genrt(0x1770,0x1770/100);
		//}else if(duty == 1){
			//PWM_genrt(0x1770,0x1770);
		}else{
			tcc_disable(TCC0);
		}
	}
}
