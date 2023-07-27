/*
 * global.h
 *
 * Created: 25/07/2022 19:11:38
 *  Author: IMDL_USER_7
 */ 

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <atmel_start.h>

#include "driver_init.h"

// SET PWM lower limit
#define PWM_LOWER 0x00
#define PERIOD 10000
//edge detection
extern bool edge_detect;
extern uint8_t delay_clk;
//used for UART input
extern int pid_uart_input;
extern uint8_t receive_character_arr[3];

//Function
int pid_controller(int rpm_value, int set_point_uart);
uint8_t * convertIntegerToChar(int integer_value);
void edge_detection_read();
unsigned concatenate(unsigned x, unsigned y);
void FSM_UART();

#endif /* GLOBAL_H_ */