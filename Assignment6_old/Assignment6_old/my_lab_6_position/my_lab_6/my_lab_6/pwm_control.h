/*
 * pwm_control.h
 *
 * Created: 7/27/2022 5:48:44 AM
 *  Author: IMDL_USER_8
 */ 

#include <atmel_start.h>
#include "atmel_start_pins.h"
#include "hpl_usart_async.h"
#include <stdio.h>

#ifndef PWM_CONTROL_H_
#define PWM_CONTROL_H_


// This function takes a current speed value and applies PI algorithm. This function needs to be called at regular intervals to work

// level indicates the duty cycle value to the PWM. The below function takes a target speed and current speed. Based on which it returns the level (duty cycle).
 
int32_t pi_speed_control(int32_t current_speed, int32_t target_speed);

 
 int8_t pi_position_control(int32_t current_position, int32_t target_position);


#endif /* PWM_CONTROL_H_ */