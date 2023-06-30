#include <custom_functions.h>

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