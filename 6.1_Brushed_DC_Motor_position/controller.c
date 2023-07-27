#include "controller.h"
#include "driver_init.h"

// Define the variables that need to run during the whole program execution

// "I_error" represents the cumulative error from the Integral controller and "P_error" represents the current error when the function was called
float I_error = 0.0;
float P_error = 0.0;
char debug[200];

// define the constants for proportional and integral controller.
// Fine tune these parameters
float Kp_speed = 3;

float Kp_pos = 0.2;
float Ki_pos = 0.0;

// define the duty cycle to be produced by the micro controller
float dutycycle_speed = 0.0;
float dutycycle_pos = 0.0;

int32_t p_speed_control(int32_t current_speed, int32_t target_speed)
{
	volatile float current_error;
	
	volatile float P_term = 0.0;
	
	current_error = target_speed - current_speed;
	P_error = current_error;
	
	P_term = Kp_speed*P_error;
	
	dutycycle_speed = P_term + dutycycle_speed;
	
	if (dutycycle_speed > 100)
	{
		dutycycle_speed = 100;
	}
	else if (dutycycle_speed < -100)    //Only output dutycycle between zero and 100%!!
	{
		dutycycle_speed = -100;
	}
	
	//size_t debug_length = sprintf(debug, "dutycycle_speed = %ld\n",dutycycle_speed);
	//io_write(&USART_0.io, debug, debug_length);
	
	return dutycycle_speed;
}

int32_t p_position_control(int32_t current_position, int32_t target_position)
{
	volatile float current_error;
	
	volatile float P_term = 0.0;
	volatile float I_term = 0.0;
	float i_max = 100.0;
	float i_min = -100.0;
	
	P_error = target_position - current_position;
	//P_error = current_error;
	//I_error = I_error + current_error;
	
	// Integral anti windup in order to make sure the I_term doesn't increase to infinity
// 	if (I_error > i_max)
// 	{
// 		I_error = i_max;
// 	}
// 	else if (I_error < i_min)
// 	{
// 		I_error = i_min;
// 	}
	
	P_term = Kp_pos*P_error;
	//I_term = Ki_pos*I_error;
	
	dutycycle_pos = P_term;
	
	if (dutycycle_pos >= 600 )
	{
		dutycycle_pos = 600;
	}
	else if (dutycycle_pos <= -600)
	{
		dutycycle_pos = -600;
	}
	else if (dutycycle_pos < 60 || dutycycle_pos > -60){
		dutycycle_pos = 0;
	}
	
	return dutycycle_pos;
}