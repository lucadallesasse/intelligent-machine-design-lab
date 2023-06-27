#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"

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
	}
}
