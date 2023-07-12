#include <set_duty.h>

double set_duty(uint8_t number){
	
	static int CurrentState = 0;
	static double output = 0;

	// 	number 0 -> ASCII 48 -> binary 110000
	// 	number 1 -> ASCII 49 -> binary 110001
	// 	number 2 -> ASCII 50 -> binary 110010
	// 	number 3 -> ASCII 51 -> binary 110011
	// 	number 4 -> ASCII 52 -> binary 110100
	// 	   +     -> ASCII 43 -> binary 101011
	// 	   -     -> ASCII 45 -> binary 101101

	if(number != 48 && number != 49 && number != 50 && number != 51 && number != 52 && number != 43 && number != 45){
		CurrentState = 0;
		}else{
		CurrentState = number;
	}
	
	switch (CurrentState){
		case 48:
		output = 0;
		break;
		case 49:
		output = 0.25;
		break;
		case 50:
		output = 0.5;
		break;
		case 51:
		output = 0.75;
		break;
		case 52:
		output = 1;
		break;
		case 43:
		output += 0.25;
		break;
		case 45:
		output -= 0.25;
		break;
		case 0:
		output = 0;
		break;
	}
	
	//check that the value of duty is between 0 and 1
	if(output >= 1.0){
		output = 1.0;
		}else if(output <= 0.0){
		output = 0.0;
	}
	return output;
}