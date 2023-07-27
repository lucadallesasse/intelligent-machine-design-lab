/*
 * Logic.c
 *
 * Created: 25/07/2022 19:11:58
 *  Author: IMDL_USER_7
 */ 

#include "atmel_start.h"

#include "global.h"


//Define data type for state machine
typedef enum {
	IDLE,
	UART_INPUT_1,
	UART_INPUT_2
}
switch_state_t;
switch_state_t current_state = IDLE;

bool edge_detect = 0;
uint8_t delay_clk = 0;
uint8_t receive_character_arr[3];
uint8_t * convertIntegerToChar(int integer_value) {

	// Count digits in number N
	int temp_int_val = integer_value;
	int digit = 0;
	while (temp_int_val) {

		// Increment number of digits
		digit++;

		// Truncate the last
		// digit from the number
		temp_int_val /= 10;
	}

	// Declare char array for result
	uint8_t * arr;

	// Declare duplicate char array
	uint8_t arr1[digit];

	// Memory allocaton of array
	arr = (uint8_t * ) malloc(digit);

	// Separating integer into digits and
	// accommodate it to character array
	int index = 0;
	while (integer_value) {

		// Separate last digit from
		// the number and add ASCII
		// value of character '0' is 48
		arr1[++index] = integer_value % 10 + '0';

		// Truncate the last
		// digit from the number
		integer_value /= 10;
	}

	// Reverse the array for result
	int i;
	for (i = 0; i < index; i++) {
		arr[i] = arr1[index - i];
	}

	// Char array truncate by null
	arr[i] = '\0';

	// Return char array
	return (uint8_t * ) arr;
}

void edge_detection_read() {
	uint8_t current_clk = 0;
	current_clk = gpio_get_pin_level(RPM_INPUT);
	if (current_clk != delay_clk) {
		if (current_clk > 0) {
			edge_detect = 1;
		}

	}
	delay_clk = current_clk;
}

unsigned concatenate(unsigned x, unsigned y) {
	unsigned pow = 10;
	while ((y - 48) >= pow)
	pow *= 10;
	return (x - 48) * pow + (y - 48);
}

//Output define in each state as like Moore statemachine
void FSM_UART() {
	volatile bool rec_flag;
	uint8_t read_character;
	rec_flag = io_read( & USART_0.io, & read_character, 1);
	if (rec_flag) {

		io_write( & USART_0.io, & read_character, 1);
	}
	volatile bool flag_inp_1 = 0;
	// + is ascii 43 and - is ascii 45
	//volatile bool inp_flag_sign_pos = 0;
	//volatile bool inp_flag_sign_neg = 0;
	flag_inp_1 = read_character >= 48 && read_character <= 57;
	//inp_flag_sign_pos = read_character == '+';
	//inp_flag_sign_neg = read_character == '-';
	volatile bool flag_enter = 0;
	//inp_flag_sign_pos = read_sign == 43;
	//inp_flag_sign_neg = read_sign == 45;
	flag_enter = read_character == '\r';
	if (rec_flag) {

		switch (current_state) {

			case IDLE:
			if (flag_inp_1) {
				//receive_character_arr[1] = read_character;
				receive_character_arr[0] = read_character;
				current_state = UART_INPUT_1;
			} else
			current_state = IDLE;
			break;
			case UART_INPUT_1:
			if (flag_inp_1) {
				receive_character_arr[1] = read_character;
				//receive_character_arr[2] = read_character;
				current_state = UART_INPUT_2;

				} else if (flag_enter) {

				current_state = IDLE;
				pid_uart_input = read_character - 48;
			} else
			current_state = IDLE;
			break;
			case UART_INPUT_2:
			if (flag_enter) {

				current_state = IDLE;
				pid_uart_input = concatenate(receive_character_arr[0], receive_character_arr[1]);
				//pid_uart_input = concatenate(receive_character_arr[1], receive_character_arr[2]);
			} else
			current_state = IDLE;
			break;

			default:
			current_state = IDLE;
			break;
		}

	}
}