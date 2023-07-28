#include <set_duty.h>

uint8_t set_duty(uint8_t number){
	
	static int CurrentState = 0;
	static int output = 0;

	// 	number 0 -> ASCII 48 -> binary 110000
	// 	number 1 -> ASCII 49 -> binary 110001
	// 	number 2 -> ASCII 50 -> binary 110010
	// 	number 3 -> ASCII 51 -> binary 110011
	// 	number 4 -> ASCII 52 -> binary 110100
	// 	number 5 -> ASCII 53 -> binary 110101
	// 	number 6 -> ASCII 54 -> binary 110110
	// 	number 7 -> ASCII 55 -> binary 110111
	// 	number 8 -> ASCII 56 -> binary 111000
	// 	number 9 -> ASCII 57 -> binary 111001
	// 	   +     -> ASCII 43 -> binary 101011
	// 	   -     -> ASCII 45 -> binary 101101

	if(number != 48 && number != 49 && number != 50 && number != 51 && number != 52 && number != 53 && number != 54 && number != 55 && number != 56 && number != 57){
		}else{
		CurrentState = number;
	}
	
	if(number == 43){
		CurrentState += 1;
	}else if(number == 45){
		CurrentState -= 1;
	}
	
	if(CurrentState >= 57){
		CurrentState = 57;
	}else if(CurrentState <= 48 ){
		CurrentState = 48;
	}
	
	switch (CurrentState){
		case 48:
		output = 0b10000000;
		break;
		case 49:
		output = 0b01110000;
		break;
		case 50:
		output = 0b01100000;
		break;
		case 51:
		output = 0b01010100;
		break;
		case 52:
		output = 0b01001000;
		break;
		case 53:
		output = 0b00111100;
		break;
		case 54:
		output = 0b00110000;
		break;
		case 55:
		output = 0b00100100;
		break;
		case 56:
		output = 0b00011000;
		break;
		case 57:
		output = 0b00000000;
		break;
	}

	return output;
}