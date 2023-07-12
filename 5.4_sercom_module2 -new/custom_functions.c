#include <custom_functions.h>

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

bool edge_detector(bool edge_input, int i){

	static bool clock_state[4] = {0};
	
	bool edge_detected[4] = {0};
	
	
	switch(clock_state[i]){
		case 0:
		if(edge_input == 0){
			clock_state[i] = 0;
			edge_detected[i] = 0;
			}else{
			clock_state[i] = 1;
			edge_detected[i] = 1;
		}
		break;
		case 1:
		if(edge_input == 1){
			clock_state[i] = 1;
			edge_detected[i] = 0;
			}else{
			clock_state[i] = 0;
			edge_detected[i] = 0;
		}
		break;
	}
	return edge_detected[i];
}
