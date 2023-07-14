#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include <pwm.h>

static uint8_t buff = 0;
static double incr = 0;
double duty = 0;

struct io_descriptor *io_UART;
static struct timer_task task1;


static void rx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	//Read the first bit of the input buffer and set the direction of rotation
	if(buff[0] == 43){
		
		//Positive direction of rotation
		gpio_set_pin_level(PIN1,true);
		gpio_set_pin_level(PIN2,false);
	}else if(buff[0] == 45){
		
		//Negative direction of rotation
		gpio_set_pin_level(PIN1,false);
		gpio_set_pin_level(PIN2,true);
	}
	
	//for(int i = 1; i < sizeof(buff); i++)
	int i = 1;
	while(true){
		
		if(buff(i) == 13){
			break;
		}else if(buff(i) <= 57 && buff(i) >= 48) {
			duty += (buff(i) - 48)*10^(3-i);
		}else{
			break;
		}
		
		i += 1;
	}
	
	if(duty <=100 && duty >= 0){
		tcc_set_compare_value(TCC0, 0xffff/50*duty/100, 0);
	}
	
}

static void timer_task1_cb(const struct timer_task *const timer_task)
{
	
	uint8_t rpm;
	io_write(io,rpm, 1);
}


int main(void)
{
	
	atmel_start_init();

	/* Initialization of the UART communication */
	usart_async_register_callback(&EDBG_UART, USART_ASYNC_RXC_CB, rx_cb_USART_0);
	usart_async_get_io_descriptor(&EDBG_UART, &io_UART);
	usart_async_enable(&EDBG_UART);
	
	task1.interval = 25;
	task1.cb = timer_task1_cb;
	task1.mode = TIMER_TASK_REPEAT;
	
	// Add timer task
	timer_add_task(&TIMER_0, &task1);
	timer_start(&TIMER_0);
	
	tcc_set_period_value(TCC0, 0xffff/50);

	while (1){
		
		//Read input command from terminal
		io_read(io_UART,&buff,5);
		
	}
	
	return 0;
}
