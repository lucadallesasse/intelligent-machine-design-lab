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

void USART_0_ex(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"USART test", 12);
}

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initialize the value */
	bool clock_edge_event = 0;
	
	while (1) {
		clock_edge_event = edge_detector();
		
		if(clock_edge_event){
			USART_0_ex();
		}
	}
}
