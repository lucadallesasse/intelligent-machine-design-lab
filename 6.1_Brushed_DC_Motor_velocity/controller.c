#include "controller.h"
#include "driver_init.h"

// Define the variables that need to run during the whole program execution

//"P_error" represents the current error when the function was called
float P_error = 0.0;
char debug[200];

 // define the constants for proportional and integral controller. 
 // Fine tune these parameters
 float Kp_speed = 3;
 
 // define the duty cycle to be produced by the micro controller
 float dutycycle_speed = 0.0;

int8_t p_speed_control(int32_t current_speed, int32_t target_speed)
{
	volatile float current_error;
	
	volatile float P_term = 0.0;
	
	current_error = target_speed - current_speed;
	P_error = current_error;
	
	P_term = Kp_speed*P_error;
	
	dutycycle_speed = P_term;
	
	if (dutycycle_speed > 100)
	{
		dutycycle_speed = 100;
	}
	else if (dutycycle_speed <= -100)    //Only output dutycycle between zero and 100%!!
	{
		dutycycle_speed = -100;
	}
	
	//size_t debug_length = sprintf(debug, "dutycycle_speed = %ld\n",dutycycle_speed);
	//io_write(&USART_0.io, debug, debug_length);
	
	return dutycycle_speed;
}