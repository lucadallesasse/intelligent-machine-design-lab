/*
 * PID.c
 *
 * Created: 25/07/2022 19:10:21
 *  Author: IMDL_USER_7
 */ 

#include "global.h"

//defines explian in the report
#define UART_TO_RPM 1.31
#define RPM_TO_PWM 101

/* Global Variables for PID */
float d_Temp = 0;
float i_Temp = 0;
int pwm_duty_cycle_temp = 0;

//Take this function from internet and modified as per desired explain in the report, I set the KI and KD to zero
int pid_controller(int rpm_value, int set_point_uart) {

	//Local variables for PID
	const float Kp = 0.004; // The value for Proportional gain
	const float Ki = 0; // The value for Integral gain
	const float Kd = 0; // The value for Differential gain

	volatile float Set_Point = set_point_uart * UART_TO_RPM; // The Motor reference point we are aiming to acheive rpm to
	int iMax = 100; // Used to prevent integral wind-up
	int iMin = -100; // Used to prevent integral wind-up
	volatile float Err_Value; // Holds the calculated Error value
	volatile float P_Term; // Holds the calculated Proportional value
	volatile float I_Term; // Holds the calculated Integral value
	volatile float D_Term; // Holds the calculated Differential value
	volatile float pwm_duty_cycle; // Holds the new PWM value
	int rpm_normalize;
	// More efficient to read this once and store as used 3 times
	Err_Value = Set_Point - rpm_value;

	// This calculates Proportional value, Kp is multiplied with Err_Value and the result is assigned to P_Term
	P_Term = Kp * Err_Value;

	// Prepare Integral value, add the current error value to the integral value and assign the total to i_Temp
	i_Temp += Err_Value;

	// Prevents integral wind-up, limits i_Temp from getting too positive or negative
	if (i_Temp > iMax) {
		i_Temp = iMax;
		} else if (i_Temp < iMin) {
		i_Temp = iMin;
	}

	// Calculates the Integral value, Ki is multiplied with i_Temp and the result is assigned to I_Term
	I_Term = Ki * i_Temp;

	// Calculates Differential value, Kd is multiplied with (d_Temp minus new_ADC_value) and the result is assigned to D_Term
	// The new_ADC_value will become the old ADC value on the next function call, this is assigned to d_Temp so it can be used
	D_Term = Kd * (d_Temp - Err_Value);
	d_Temp = Err_Value;

	/****** Now we have the P_Term, I_Term and D_Term *****/
	pwm_duty_cycle = (P_Term * RPM_TO_PWM + I_Term + D_Term) + pwm_duty_cycle_temp;

	// PWM overflow prevention
	if (pwm_duty_cycle > PERIOD) {
		pwm_duty_cycle = PERIOD;
		} else if (pwm_duty_cycle < 3) {
		pwm_duty_cycle = 3;
	}

	
	// Assigns the current PWM duty cycle value to PWM_Temp
	pwm_duty_cycle_temp = pwm_duty_cycle;

	return pwm_duty_cycle;
}