
#include <atmel_start.h>
#include "atmel_start_pins.h"
#include "hpl_usart_async.h"
#include <stdio.h>

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


// This function takes a current speed value and applies PI algorithm. This function needs to be called at regular intervals to work
// level indicates the duty cycle value to the PWM. The below function takes a target speed and current speed. Based on which it returns the level (duty cycle).
 
int8_t p_speed_control(int32_t current_speed, int32_t target_speed);

#endif /* CONTROLLER_H_ */