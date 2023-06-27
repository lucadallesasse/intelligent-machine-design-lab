#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"


#define COMPARE_CHANNEL_0 0
#define VALUE_FOR_500us 0xBB8 // decimal = 3000
#define TCC_DEFAULT_CONFIGURATION PWM_0_init()

bool edge_detector(void){

	static char clock_state = 0;
	bool edge_input = (PORT->Group[SW0/32].IN.reg & (1<<(SW0%32)));
	
	bool edge_detected = 0;
		
	
	switch(clock_state){
		case 0:
		if(edge_input == 0){
			clock_state = 1;
			edge_detected = 1;
		}else{
			clock_state = 0;
			edge_detected = 0;
		}
		break;
		case 1:
		if(edge_input == 0){
			clock_state = 1;
			edge_detected = 0;
		}else{
			clock_state = 0;
			edge_detected = 0;
		}
		break;
		}
	return edge_detected;
}

double set_duty(bool input[]){
		
	static double duty = 0;
	
	// number 0 -> ASCII 48 -> binary 110000
	// number 1 -> ASCII 49 -> binary 110001
	// number 2 -> ASCII 50 -> binary 110010
	// number 3 -> ASCII 51 -> binary 110011
	// number 4 -> ASCII 52 -> binary 110100
	//   +      -> ASCII 43 -> binary 101011
	//   -      -> ASCII 45 -> binary 101101
	
	bool number0[] = {1,1,0,0,0,0};
	bool number1[] = {1,1,0,0,0,1};
	bool number2[] = {1,1,0,0,1,0};		
	bool number3[] = {1,1,0,0,1,1};
	bool number4[] = {1,1,0,1,0,0};
	bool symbol_plus[] = {1,0,1,0,1,1};
	bool symbol_minus[] = {1,0,1,1,0,1};
		
	switch (input){
		case number0:
			duty = 0.16;
		break;
		case number1:
			duty = 0.32;
		break;
		case number2:
			duty = 0.48;
		break;
		case number3:
			duty = 0.64;
		break;
		case number4:
			duty = 0.80;
		break;
		case symbol_plus:
			duty = 1;
		break;
		case symbol_minus:
			duty = 0;
		break;
	}
	
	//check that the value of duty is between 0 and 1
	if(duty > 1){
		duty = 1;
	}else if(duty < 0){
		duty = 0;
	}
	
	return duty;
}

double ste_duty_alternative(int number){
	
	static char CurrentState = 0;
	static double duty = 0;
		
	bool number0[] = {1,1,0,0,0,0};
	bool number1[] = {1,1,0,0,0,1};
	bool number2[] = {1,1,0,0,1,0};
	bool number3[] = {1,1,0,0,1,1};
	bool number4[] = {1,1,0,1,0,0};
	bool symbol_plus[] = {1,0,1,0,1,1};
	bool symbol_minus[] = {1,0,1,1,0,1};
	
	switch (CurrentState){
		case 0:
		if(number == number0[0]){
			CurrentState = 1;
			}else{
			CurrentState = 0;
		}
		break;
		case 1:
		if(number == number0[1]){
			CurrentState = 2;
			}
		else if(number == symbol_plus[1]){
			CurrentState = 3;
		}
		break;
		case 2:
		if(number == number0[2]){
			CurrentState = 10;
			}else{
			CurrentState = 2;
		}
		break;
		case 3:
		if(number == symbol_plus[2]){
			CurrentState = 4;
			}
		else{
			CurrentState = 0;
		}
		break;
		case 4:
		if(number == symbol_plus[3]){
			CurrentState = 5;
			}else{
			CurrentState = 8;
		}
		break;
		case 5:
		if(number == symbol_plus[4]){
			CurrentState = 6;
			}else{
			CurrentState = 1;
		}
		break;
		case 6:
		if(number == symbol_plus[4]){
			CurrentState = 7;
			duty = 1;
			}else{
			CurrentState = 0;
		}
		break;
		case 7:
		if(number == 1){
			CurrentState = 2;
		}
		else{
			CurrentState = 11;
		}
		break;
		case 8:
		if(number == symbol_minus[4]){
			CurrentState = 9;
			}else{
			CurrentState = 2;
		}
		break;
		case 9:
		if(number == symbol_minus[5]){
			CurrentState = 10;
			duty = 0;
			}else{
			CurrentState = 12;
		}
		break;
		case 10:
		if(number == 1){
			CurrentState = 2;
			}else{
			CurrentState = 15;
		}
		break;
		case 11:
		if(number == number0[3]){
			CurrentState = 12;
			}else{
			CurrentState = 15;
		}
		break;
		case 12:
		if(number == number0[4]){
			CurrentState = 13;
			}else{
			CurrentState = 16;
		}
		break;
		case 13:
		if(number == number0[5]){
			CurrentState = 14;
			duty = 0.16;
			}else{
			CurrentState = 19;
			duty = 0.32;
		}
		break;
		case 14:
		if(number == 1){
			CurrentState = 1;
			}else{
			CurrentState = 0;
		}
		break;
		case 15:
		if(number == number4[4]){
			CurrentState = 20;
			}else{
			CurrentState = 8;
		}
		break;
		case 16:
		if(number == number2[5]){
			CurrentState = 17;
			duty = 0.48;
			}else{
			CurrentState = 18;
			duty = 0.64;
		}
		break;
		case 17:
		if(number == 1){
			CurrentState = 4;
			}else{
			CurrentState = 0;
		}
		break;
		case 18:
		if(number == 1){
			CurrentState = 0;
			}else{
			CurrentState = 0;
		}
		break;
		case 19:
		if(number == 1){
			CurrentState = 2;
			}else{
			CurrentState = 3;
		}
		break;
		case 20:
		if(number == number4[5]){
			CurrentState = 21;
			duty = 0.8;
			}else{
			CurrentState = 6;
		}
		break;
		case 21:
		if(number == 1){
			CurrentState = 1;
			}else{
			CurrentState = 0;
		}
		break;
	}
	return duty;
}

int main(void){
	
	int duty = 0;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	struct io_descriptor *io;
	uint8_t *buf;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	
	/* Initialize the value */
	bool clock_edge_event = 0;
	
	while (1) {
		
		clock_edge_event = edge_detector();
		//if there is a clock detection read the value from the terminal and assign it to command variable. Then with this command value change the duty cycle of the PWM
		if(clock_edge_event){
			//io_write(io, (uint8_t *)"USART test", 12);
			io_read(io, buf, 7);
			duty = set_duty((bool *)buf);
		}
		
		//PVW to set the desired duty cycle
		TCC_DEFAULT_CONFIGURATION;
		if(duty != 0){
			//PORT->Group[LED0/32].OUTCLR.reg = (1<<LED0%32);
			tcc_disable(TCC0);
			//printf("1KHz PWM Waveform output available on WO[1] PIN\r\n");
			tcc_set_compare_value(TCC0, VALUE_FOR_500us, COMPARE_CHANNEL_1); //red_led at 100Hz
			tcc_enable(TCC0);
			}else{
			//PORT->Group[LED0/32].OUTSET.reg = (1<<LED0%32);
			tcc_disable(TCC0);
		}
	}
}
