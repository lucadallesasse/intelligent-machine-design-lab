#include <atmel_start.h>

bool HandleEvent(bool bit_entered){
	
	static char CurrentState = 0;
	static bool output = 0; //if 1 LED on, if 0 LED off
	
	bool on_pattern[] = {0,1,0,1,1};
	bool off_pattern[] = {0,1,1,0,1};
		
	switch (CurrentState){
	case 0:
		if(bit_entered == on_pattern[0]){
			CurrentState = 1;				
		}else{
			CurrentState = 0; 		
		}
		break;
	case 1:
		if(bit_entered == on_pattern[1]){
			CurrentState = 2;				
			}else{
			CurrentState = 1;
		}
		break;
	case 2:
		if(bit_entered == on_pattern[2]){
			CurrentState = 3;			
			}
		else if(bit_entered == off_pattern[2]){
			CurrentState = 5;	
		}
		break;
	case 3:
		if(bit_entered == on_pattern[3]){
			CurrentState = 4;			
			}else{
			CurrentState = 1;
		}
		break;		
	case 4:
		if(bit_entered == on_pattern[4]){
			CurrentState = 5;			
			output = 1;
			}else{
			CurrentState = 3;
		}
		break;
	case 5:
		if(bit_entered == 0){
			CurrentState = 6;			
			}else{
			CurrentState = 0;	
		}
		break;
	case 6:
		if(bit_entered == 0){
			CurrentState = 1;			
			}else{
			CurrentState = 2;
			output = 0;
		}
		break;
	}
	return output;		
}

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
