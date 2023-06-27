#include <atmel_start.h>
#include <string.h>
#include <custom_functions.h>

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initialize the value */
	bool input[4];
	bool clock_edge_event = 0;
	
	int value = 0;
	int result = 0;
	
	while (1) {
		clock_edge_event = edge_detector();
		
		if(clock_edge_event){
			//get the 4 bit from the DIP switch
			input[3] = (PORT->Group[BIT1/32].IN.reg & (1<<(BIT1%32))); //PB04
			input[2] = (PORT->Group[BIT2/32].IN.reg & (1<<(BIT2%32))); //PB05
			input[1] = (PORT->Group[BIT3/32].IN.reg & (1<<(BIT3%32))); //PB06
			input[0] = (PORT->Group[BIT4/32].IN.reg & (1<<(BIT4%32))); //PB07
			//convert the 4-bit value into integer
			value = input[3]*8 + input[2]*4 + input[1]*2 + input[0];
			//state machine for detecting the right sequence for counting up and down
			result = HandleEvent(value);
		}
		
		int seven_seg[7];
		//convert the count value into a sequence for the 7 segment display
		switch(result){
			case 0:
				seven_seg[0] = 1;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 1;
				seven_seg[4] = 1;
				seven_seg[5] = 1;
				seven_seg[6] = 0;
			break;
			case 1:
				seven_seg[0] = 0;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 0;
				seven_seg[4] = 0;
				seven_seg[5] = 0;
				seven_seg[6] = 0;			
			break;
			case 2:
				seven_seg[0] = 1;
				seven_seg[1] = 1;
				seven_seg[2] = 0;
				seven_seg[3] = 1;
				seven_seg[4] = 1;
				seven_seg[5] = 0;
				seven_seg[6] = 1;
			break;
			case 3:
				seven_seg[0] = 1;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 1;
				seven_seg[4] = 0;
				seven_seg[5] = 0;
				seven_seg[6] = 1;
			break;
			case 4:
				seven_seg[0] = 0;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 0;
				seven_seg[4] = 0;
				seven_seg[5] = 1;
				seven_seg[6] = 1;
			break;
			case 5:
				seven_seg[0] = 1;
				seven_seg[1] = 0;
				seven_seg[2] = 1;
				seven_seg[3] = 1;
				seven_seg[4] = 0;
				seven_seg[5] = 1;
				seven_seg[6] = 1;
			break;
			case 6:
				seven_seg[0] = 1;
				seven_seg[1] = 0;
				seven_seg[2] = 1;
				seven_seg[3] = 1;
				seven_seg[4] = 1;
				seven_seg[5] = 1;
				seven_seg[6] = 1;
			break;
			case 7:
				seven_seg[0] = 1;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 0;
				seven_seg[4] = 0;
				seven_seg[5] = 0;
				seven_seg[6] = 0;
			break;
			case 8:
				seven_seg[0] = 1;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 1;
				seven_seg[4] = 1;
				seven_seg[5] = 1;
				seven_seg[6] = 1;
			break;
			case 9:
				seven_seg[0] = 1;
				seven_seg[1] = 1;
				seven_seg[2] = 1;
				seven_seg[3] = 1;
				seven_seg[4] = 0;
				seven_seg[5] = 1;
				seven_seg[6] = 1;
			break;
		}
		
		gpio_set_pin_level(OUT1,!seven_seg[0]);  //port PB08 - A in the 7seg
		gpio_set_pin_level(OUT2,!seven_seg[1]);  //port PB09
		gpio_set_pin_level(OUT3,!seven_seg[2]);  //port PB14
		gpio_set_pin_level(OUT4,!seven_seg[3]);  //port PB15
		gpio_set_pin_level(OUT5,!seven_seg[4]);  //port PB26
		gpio_set_pin_level(OUT6,!seven_seg[5]);  //port PB27
		gpio_set_pin_level(OUT7,!seven_seg[6]);  //port PB28
	}
}
