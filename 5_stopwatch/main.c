#include <atmel_start.h>
#include "custom_functions.h"
#include <pwm.h>
#include <string.h>
#include <stdio.h>

// Struct for Timer Task
static struct timer_task task1;

static int s = 0;
static int min = 0;
static struct io_descriptor *io;

static void timer_task1_cb(const struct timer_task *const timer_task)
{	
	s += 1;
	
	if(s < 60){
	}else{
		s = 0;
		min += 1;
	}
	
	char timeString[6];
	sprintf(timeString, "%02d:%02d\n", min, s);
	io_write(io, (uint8_t *)timeString, 6);
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	bool clock_edge_event1 = 0;
	bool clock_edge_event2 = 0;
	bool clock_edge_event3 = 0;
	
	/* Initialization of the UART communication */
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);
	
	task1.interval = 25;
	task1.cb = timer_task1_cb;
	task1.mode = TIMER_TASK_REPEAT;
	
	// Add timer task
	timer_add_task(&TIMER_0, &task1);
	
	while (1){
		
		clock_edge_event1 = edge_detector(PORT->Group[CODE_INPUT1/32].IN.reg & (1<<(CODE_INPUT1%32)),0);
		clock_edge_event2 = edge_detector(PORT->Group[CODE_INPUT2/32].IN.reg & (1<<(CODE_INPUT2%32)),1);
		clock_edge_event3 = edge_detector(PORT->Group[CODE_INPUT3/32].IN.reg & (1<<(CODE_INPUT3%32)),2);
		
		if(clock_edge_event1 && !clock_edge_event2 && !clock_edge_event3){
			timer_start(&TIMER_0);
		}else if(!clock_edge_event1 && clock_edge_event2 && !clock_edge_event3){
			timer_stop(&TIMER_0);
		}else if(!clock_edge_event1 && !clock_edge_event2 && clock_edge_event3){
			min = 0;
			s = 0;
		}
	}	
	
	return 0;
}
