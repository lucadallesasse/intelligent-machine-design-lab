#include <atmel_start.h>
#include "atmel_start_pins.h"
#include "hpl_usart_async.h"
#include "pwm_control.h"

#define MAX_RPM 100 // should be 122

volatile static uint32_t data_arrived = 0;

char user_input[6];
uint8_t input_char_count = 0;
bool uart_ready = false;
bool input_ready = false;


uint8_t payload[50]; // the payload that will be sent to the PC via UART

uint32_t periodCC0 = 0;
uint32_t pulses = 0; // will store the number of pulses per timer period

uint32_t rpm = 0;

// default direction
int8_t direction = 1; // default direction
// default steps
int32_t steps = 0;

// this will store user input
int32_t level = 0;
int8_t controlled_level = 0;

// Will be fired at each rising edge of HAL sensor A
void TC0_Handler(){
	hri_tc_clear_INTFLAG_MC0_bit(TC0);
	
	// periodCC0 * 60 / (1440 * 1.5MHz)
	periodCC0 = (uint32_t)hri_tccount16_read_CC_reg(TC0, 0); 
	pulses++;
	
	//////////////////////////////////////////////////////////////////////////
	// Getting the direction and the number of steps in each direction
	
	// read HAL_SENSOR_B 
	bool hal_sensor_b = gpio_get_pin_level(HAL_SENSOR_B);
	
	if ((hal_sensor_b == false) && (direction == -1))
	{
		direction = 1; // Reverse
	}
	else if ((hal_sensor_b == true) && (direction == 1))
	{
		direction = -1;
	}
	
	if (direction == 1)
	{
		steps++;
	}
	else
	{
		steps--;
	}
	
	if ((steps > 30000) || (steps < -30000))
	{
		steps = 0;
	}
	
	
}

static void uart_rx_cb(const struct usart_async_descriptor *const io_descr)
{
	/* Receive completed */
	data_arrived = 1;
}

static struct timer_task TIMER_1_task1, TIMER_1_task2;
static struct timer_task TIMER_2_task1, TIMER_2_task2;

/**
 *	capture the number of pulses in the past 10ms
 */
static void TIMER_1_task1_cb(const struct timer_task *const timer_task)
{
	rpm = (pulses * 100 /*Hz*/ * 60.0 /*Min*/ / (1440));
	pulses = 0;
}

// send the RPM value every 100ms
static void TIMER_1_task2_cb(const struct timer_task *const timer_task)
{
	size_t payload_length = sprintf(payload, "position = %d | speed = %lu RPM | direction = %d\n",steps, rpm, direction);
	io_write(&USART_0.io, payload, payload_length);
}

void TIMER_1_config(void)
{
	TIMER_1_task1.interval = 10;
	TIMER_1_task1.cb       = TIMER_1_task1_cb;
	TIMER_1_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_1_task2.interval = 100;
	TIMER_1_task2.cb       = TIMER_1_task2_cb;
	TIMER_1_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_1, &TIMER_1_task1);
	timer_add_task(&TIMER_1, &TIMER_1_task2);
	timer_start(&TIMER_1);
}

static void TIMER_2_task1_cb(const struct timer_task *const timer_task)
{
	if (input_ready == true)
	{
		pwm_disable(&PWM_0);
		//if (level >= 0)
		//{
			//gpio_set_pin_level(MOTOR_INPUT_2, false);
			controlled_level = pi_position_control(steps, level);
			controlled_level = pi_speed_control(rpm * direction, controlled_level);
			//pwm_set_parameters(&PWM_0, 10000, 10000 * (controlled_level / 100.0));
		//}
		//else
		//{
			//gpio_set_pin_level(MOTOR_INPUT_2, true);
			//controlled_level = pi_position_control(steps, level);
			//controlled_level = pi_speed_control(rpm * direction, controlled_level);
			//pwm_set_parameters(&PWM_0, 10000, 10000 + (10000 * (controlled_level / 100.0)));			
		//}
		
		if (controlled_level >= 0)
		{
			gpio_set_pin_level(MOTOR_INPUT_2, false);
			pwm_set_parameters(&PWM_0, 10000, 10000 * (controlled_level / 100.0));
		}
		else
		{
			gpio_set_pin_level(MOTOR_INPUT_2, true);
			pwm_set_parameters(&PWM_0, 10000, 10000 + (10000 * (controlled_level / 100.0)));	
		}
		
		
		pwm_enable(&PWM_0);
	}
}

static void TIMER_2_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_2_config(void)
{
	TIMER_2_task1.interval = 100; // change me to 1
	TIMER_2_task1.cb       = TIMER_2_task1_cb;
	TIMER_2_task1.mode     = TIMER_TASK_REPEAT;
	//TIMER_2_task2.interval = 200;
	//TIMER_2_task2.cb       = TIMER_2_task2_cb;
	//TIMER_2_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_2, &TIMER_2_task1);
	//timer_add_task(&TIMER_2, &TIMER_2_task2);
	timer_start(&TIMER_2);
}

int main(void)
{
	uint8_t recv_char;
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
		
	pwm_set_parameters(&PWM_0, 10000, 0);
	pwm_enable(&PWM_0);
	
	usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, uart_rx_cb);
	usart_async_enable(&USART_0);
	
	TIMER_1_config();
	TIMER_2_config();
	
	
	NVIC_SetPriority(TC0_IRQn, 3);
	NVIC_EnableIRQ(TC0_IRQn);
	__enable_irq();
	while (1) {	
		if (data_arrived == 0) {
			continue;
		}

		while (io_read(&USART_0.io, &recv_char, 1) == 1) {
			if (recv_char == '\n')
			{
				uart_ready = true;
				input_ready = false;
				input_char_count--;
				break;
			}
			user_input[input_char_count++] = recv_char;
			while (io_write(&USART_0.io, &recv_char, 1) != 1) {
			}
		}
		data_arrived = 0;
		if (uart_ready)
		{
			level = 0;
			
			if (input_char_count == 2)
			{
				level = user_input[1] - '0';
			} 
			else if (input_char_count == 3)
			{
				level = ((user_input[1] - '0') * 10) + (user_input[2] - '0');
			}
			else if (input_char_count == 4)
			{
				level = ((user_input[1] - '0') * 100) +  ((user_input[2] - '0') * 10) + (user_input[3] - '0');
			}
			else if (input_char_count == 5)
			{
				level = ((user_input[1] - '0') * 1000) + ((user_input[2] - '0') * 100) +  ((user_input[3] - '0') * 10) + (user_input[4] - '0');
			}
			else
			{
				level = ((user_input[1] - '0') * 10000) + ((user_input[2] - '0') * 1000) + ((user_input[3] - '0') * 100) +  ((user_input[4] - '0') * 10) + (user_input[5] - '0');
			}
			
			if(user_input[0] == '+')
			{
				level = level;
			}
			else if (user_input[0] == '-')
			{
				level = -level;
			}
			
			if (level > 30000)
			{
				level = 30000;
			}
			else if (level < -30000)
			{
				level = -30000;
			}
	
			input_ready = true;
			uart_ready = false;
			input_char_count = 0;
		}
	}
}
