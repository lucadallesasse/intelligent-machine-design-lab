#include <atmel_start.h>

bool HandleEvent(bool bit_entered){
	
	static char CurrentState = 0;
	static bool output = 0; //if 1 LED on, if 0 LED off
	
	bool on_pattern[] = {0,1,0,1,1};
	bool off_pattern[] = {0,1,1,0,1};
		
	switch (CurrentState){
	case 0:
		if(bit_entered == on_pattern[1]){
			CurrentState = 1;				
		}else{
			CurrentState = 0; 		
		}
		break;
	case 1:
		if(bit_entered == on_pattern[2]){
			CurrentState = 2;				
			}else{
			CurrentState = 1;
		}
		break;
	case 2:
		if(bit_entered == on_pattern[3]){
			CurrentState = 3;			
			}
		else if(bit_entered == off_pattern[3]){
			CurrentState = 5;	
		}else{}
		break;
	case 3:
		if(bit_entered == on_pattern[4]){
			CurrentState = 4;			
			}else{
			CurrentState = 1;
		}
		break;		
	case 4:
		if(bit_entered == on_pattern[5]){
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
		}
		break;
	case 6:
		if(bit_entered == 0){
			CurrentState = 0;			
			}else{
			CurrentState = 2;
			output = 0;
		}
		break;
	}
	return output;		
}

bool ReadButton(){
	
	bool bit_entered = 0;
	
	if(gpio_get_pin_level(SW0)){
		bit_entered = gpio_get_pin_level(DIP_IN); 
		return HandleEvent(bit_entered);
	}
}

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initialize the value */
	bool led;
	
	while (1) {
		led = ReadButton();
		if(led == 1){
			gpio_set_pin_level(YLW_LED, 1);
		}else{
			gpio_set_pin_level(YLW_LED, 0);
		}
	}
}
