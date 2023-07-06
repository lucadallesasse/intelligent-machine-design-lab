#include <atmel_start.h>
#include "custom_functions.h"
#include <pwm.h>

// Struct for Timer Task
static struct timer_task task1;
static struct timer_task task2;

static bool led = 0;


static bool timer_task2_cb(const struct timer_task *const timer_task)
{
	gpio_set_pin_level(LED_green2,1);
}

static bool timer_task1_cb(const struct timer_task *const timer_task)
{
	// Set up Timer Function
	task2.interval = 10;
	task2.cb = timer_task2_cb;
	task2.mode = TIMER_TASK_ONE_SHOT;
	bool input = 0;
	
	// Toggle green LED2
	gpio_set_pin_level(LED_green2,0);
	
	input = (PORT->Group[CODE_INPUT/32].IN.reg & (1<<(CODE_INPUT%32)));   //get the input from DIP_SWITCH
	led = HandleEvent(input);                                             //check into the state machine the input sequence and store the output
	
	if(led){
		//Set compare value of the PWM to blink the red LED at 100Hz
		//tcc_set_compare_value(TCC0, 0x1770/50, 0);
		tcc_set_compare_value(TCC0, 0x1770/100, 0);
		}else{
		//Turn off the led
		tcc_set_compare_value(TCC0, 0x1770/50, 0);
	}
	
	timer_add_task(&TIMER_1, &task2);
	timer_start(&TIMER_1);
	
	return led;
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	task1.interval = 25;
	task1.cb = timer_task1_cb;
	task1.mode = TIMER_TASK_REPEAT;
	
	// Add timer task
	timer_add_task(&TIMER_0, &task1);
	timer_start(&TIMER_0);
	
	tcc_set_period_value(TCC0, 0x1770/50);  

	while (1){}	
	
	return 0;
}
