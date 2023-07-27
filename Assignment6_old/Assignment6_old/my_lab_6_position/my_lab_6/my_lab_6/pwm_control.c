/*
 * pwm_control.c
 *
 * Created: 7/27/2022 6:03:16 AM
 *  Author: IMDL_USER_8
 */ 

#include "pwm_control.h"
#include "driver_init.h"

// Define the variables that need to run during the whole program execution

// "I_error" represents the cumulative error from the Integral controller and "P_error" represents the current error when the function was called
float I_error = 0.0;
float P_error = 0.0;

float I_error_pos = 0.0;
float P_error_pos = 0.0;
char debug[200];

 // define the constants for proportional and integral controller. 
 // Fine tune these parameters
 float Kp_speed = 0.2;
 float Ki_speed = 0.01; 
 
 float Kp_pos = 0.015;
 float Ki_pos = 0.002;
 
 // define the duty cycle to be produced by the micro controller
 float dutycycle_speed = 0.0;
 float dutycycle_pos = 0.0;
 
 // need to check these values during testing
 #define RPM_2_TICKS 1
 #define POS_2_TICKS 1

int32_t pi_speed_control(int32_t current_speed, int32_t target_speed)
{
	volatile float current_error;
	
	volatile float P_term = 0.0;
	volatile float I_term = 0.0;
	float i_max = 100.0;
	float i_min = -100.0;
	
	current_error = 1.0 * target_speed - current_speed;
	P_error = current_error;
	I_error = I_error + current_error;
	
	// Integral error control (a.k.a integral anti windup). In order to make sure the I_term doesn't increase to infinity
	if (I_error > i_max)
	{
		I_error = i_max;
	}
	else if (I_error < i_min)
	{
		I_error = i_min;
	}
	
	P_term = Kp_speed*P_error;
	I_term = Ki_speed*I_error;
	
	// Currently 10000 ticks configured as time period for the PWM functionality
	// We need to multiple the P and I terms with RPM_2_TICKS as output is not in percentage but ticks
	
	dutycycle_speed = (P_term + I_term)*RPM_2_TICKS + dutycycle_speed;
	
	if (dutycycle_speed > 100)
	{
		dutycycle_speed = 100;
	}
	else if (dutycycle_speed < -100)
	{
		dutycycle_speed = -100;
	}
	//
	//size_t debug_length = sprintf(debug, "current_error = %ld | P_term = %ld | I_term = %ld | dutycycle_speed = %ld | current speed = %ld | target speed = %ld\n",(int32_t)current_error, (int32_t)P_term, (int32_t)I_term, (int32_t)dutycycle_speed, (int32_t)current_speed, (int32_t)target_speed);
	
	//io_write(&USART_0.io, debug, debug_length);
	//delay_ms(20);
	
	return dutycycle_speed;	
}

int8_t pi_position_control(int32_t current_position, int32_t target_position)
{
	float current_error;
	
	float P_term = 0.0;
	float I_term = 0.0;
	float i_max = 100.0;
	float i_min = -100.0;
	
	current_error = 1.0 * target_position - current_position;
	P_error_pos = current_error;
	I_error_pos = I_error_pos + current_error;
	
	// Integral error control (a.k.a integral anti windup). In order to make sure the I_term doesn't increase to infinity
	if (I_error_pos > i_max)
	{
		I_error_pos = i_max;
	}
	else if (I_error_pos < i_min)
	{
		I_error_pos = i_min;
	}
	
	P_term = Kp_pos*P_error_pos;
	I_term = Ki_pos*I_error_pos;
	
	// Currently 10000 ticks configured as time period for the PWM functionality
	// We need to multiple the P and I terms with POS_2_TICKS as output is not in percentage but ticks
	
	dutycycle_pos = (P_term + I_term)*POS_2_TICKS + dutycycle_pos;
		
	// make sure the duty cycle lies within the period ticks (which is configured as 10000 here)
	if (dutycycle_pos > 100)
	{
		dutycycle_pos = 100;
	}
	else if (dutycycle_pos < -100)
	{
		dutycycle_pos = -100;
	}
	
    //size_t debug_length = sprintf(debug, "current_error = %ld | P_term = %ld | I_term = %ld | dutycycle_speed = %ld | current position = %ld | target position = %ld\n",(int32_t)current_error, (int32_t)P_term, (int32_t)I_term, (int32_t)dutycycle_pos, (int32_t)current_position, (int32_t)target_position);
	//
	//io_write(&USART_0.io, debug, debug_length);
	
	return dutycycle_pos;	
}