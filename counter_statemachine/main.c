#include <atmel_start.h>
#include <string.h>

int HandleEvent(int number){
	
	static char CurrentState = 0;	
	static int count = 0;
	
	int up_pattern[] = {0,4,6,2,0};
	int down_pattern[] = {0,4,5,1,0};
		
	switch (CurrentState){
	case 0:
		if(number == up_pattern[0]){
			CurrentState = 1;				
		}else{
			CurrentState = 0; 		
		}
		break;
	case 1:
		if(number == up_pattern[1]){
			CurrentState = 2;				
			}else{
			CurrentState = 0;
		}
		break;
	case 2:
		if(number == up_pattern[2]){
			CurrentState = 3;			
			}
		else if(number == down_pattern[2]){
			CurrentState = 6;	
		}
		else{
			CurrentState = 0;
		}
		break;
	case 3:
		if(number == up_pattern[3]){
			CurrentState = 4;			
			}else{
			CurrentState = 0;
		}
		break;		
	case 4:
		if(number == up_pattern[4]){
			CurrentState = 5;			
			count += 1;
			}else{
			CurrentState = 0;
		}
		break;
	case 5:
		if(number == 0){
			CurrentState = 1;			
			}
		else if(number == 4){
			CurrentState = 2;	
		}else{
			CurrentState = 0;	
		}
		break;
	case 6:
		if(number == down_pattern[3]){
			CurrentState = 7;			
			}else{
			CurrentState = 0;
		}
		break;
	case 7:
		if(number == down_pattern[4]){
			CurrentState = 8;
			count -= 1;
			}
		else{
			CurrentState = 0;
		}
		break;
	case 8:
		if(number == 0){
			CurrentState = 1;
		}
		else if(number == 4){
			CurrentState = 2;
			}else{
			CurrentState = 0;
		}
		break;
	}
	return count;		
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
