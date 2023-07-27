#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include <pwm.h>
//#include "motor_position.h"

static uint8_t buff[5] = {0};
static double incr = 0;
int duty_cycle = 0;
int delta = 0;


struct io_descriptor *io_UART;
//static struct timer_task task1;
//static struct timer_task task2;

// uint8_t rpm = 0;
bool flag = true;
// double error_controller = 0;
// double control_signal = 0;
// int counter = 0;
// int counts = 0;
// double actual_duty_cycle = 0;

static void rx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{

	//Read the first bit of the input buffer and set the direction of rotation
	if(buff[0] == 43){
		
		//Positive direction of rotation
		gpio_set_pin_level(PIN1,false);
		gpio_set_pin_level(PIN2,true);
 	}else if(buff[0] == 45){
 		
 		//Negative direction of rotation
 		gpio_set_pin_level(PIN1,true);
 		gpio_set_pin_level(PIN2,false);
 	}
	 
	int i = 1;
 	if(buff[1] >= 48 && buff[1] <= 57){
		while (buff[i] != 10) {
			delta = duty_cycle * 10 + (buff[i] - 48);
			duty_cycle = delta;
			i++;
			flag = true;
		}
	}else{
		duty_cycle = 0;
		flag = false;
	}

	//Clear the buffer
	for(int i = 0; i < sizeof(buff); i++){
		buff[i] = 0;
		}
}

// static void measure_speed(const struct timer_task *const timer_task)
// {
// 	//Read the RPM at 100Hz and store into rpm variable
// 	io_read(io,counts, 1);
// 	//Provide the RPM and update its value every 1 second
// 	counter += 1;
// 	if(counter > 1000){
// 		counter = 0;
// 		rpm = counts*60;
// 		counts = 0;
// 	}
// 	
// 	actual_duty_cycle = rpm/122;
// }

// static void print_speed(const struct timer_task *const timer_task)
// {
// 	flag = true;
// }


int main(void)
{
	
	atmel_start_init();

	/* Initialization of the UART communication */
	usart_async_register_callback(&EDBG_UART, USART_ASYNC_RXC_CB, rx_cb_USART_0);
	usart_async_get_io_descriptor(&EDBG_UART, &io_UART);
	usart_async_enable(&EDBG_UART);
	
// 	task1.interval = 10;
// 	task1.cb = measure_speed;
// 	task1.mode = TIMER_TASK_REPEAT;
// 	
// 	task2.interval = 1000;
// 	task2.cb = print_speed;
// 	task2.mode = TIMER_TASK_REPEAT;
// 	
// 	//Add timer task for the first timer
// 	timer_add_task(&TIMER_0, &task1);
// 	timer_start(&TIMER_0);
// 	
// 	//Add timer task for the second timer
// 	timer_add_task(&TIMER_1, &task2);
// 	timer_start(&TIMER_1);
	
	tcc_set_period_value(TCC0, 0xffff/50);
	
// 	int Kp = 1; //proportional gain
// 	
// 	int32_t *Steps = 0;
// 	int8_t *Direction = 0;
	//io_write(io_UART, example_EDBG_UART, 12);

	while (1){
		
		//Read input command from terminal
		io_read(io_UART,buff,5);
		tcc_set_compare_value(TCC0, 0, 0);
		
// 		if(flag){
//  			if(duty_cycle <=100 && duty_cycle >= 0){
// 			tcc_set_compare_value(TCC0, 0, 0);
// 			}
//  		}
		
		
// 		if(flag){
// 			//Send the read value of the RPM to the terminal every 0.1s (10Hz)
// 			io_read(io_UART,&rpm,1);
// 		}
// 		
// 		flag = false;	
// 		//Compute the control loop
// 		error_controller = duty_cycle - actual_duty_cycle;  // Calculate the error
// 		control_signal = Kp * error_controller;  // Calculate the control signal	
// 		//Send the corrected value for the duty_cycle cycle
// 		tcc_set_compare_value(TCC0, 0xffff/50*duty_cycle/100, 0);
		
		//motor_position(encoder_step, &Steps, &Direction);

	}
	
	return 0;
}
