#include <atmel_start.h>
#include "custom_functions.h"

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initialize the value */
	bool input = 0;
	bool clock_edge_event = 0;
	bool led = 0;
	
	while (1) {
		clock_edge_event = edge_detector();
		
		if(clock_edge_event){
			input = (PORT->Group[CODE_INPUT/32].IN.reg & (1<<(CODE_INPUT%32)));
			led = HandleEvent(input);
		}
		
		if(led){
			//PORT->Group[LED0/32].OUTCLR.reg = (1<<LED0%32);
			gpio_set_pin_level(LED0,0);
			
		}else{
			//PORT->Group[LED0/32].OUTSET.reg = (1<<LED0%32);
			gpio_set_pin_level(LED0,1);
			
		}
	}
}
