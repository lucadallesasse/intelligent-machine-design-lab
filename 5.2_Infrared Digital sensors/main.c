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
static int c = 0;

bool flag = 0;

static void timer_task1_cb(const struct timer_task *const timer_task)
{	
	//count
	s += 1;
	c += 1;
	
	if(s < 60){
	}else{
		s = 0;
		min += 1;
	}
	
	flag = 1;
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
	
	// Timer configuration: every 1s execute the task
	task1.interval = 25;
	task1.cb = timer_task1_cb;
	task1.mode = TIMER_TASK_REPEAT;
	// Add timer task
	timer_add_task(&TIMER_0, &task1);
	
	while (1){
		
		//Send the timer count via UART whenever the flag is set by the interrupt (every 1s)
		if(flag){
			char timeString[6];
			sprintf(timeString, "%02d:%02d\n", min, s, c);
			io_write(io, (uint8_t *)timeString, 6);
		}
			
		flag = 0;
		
		//Detect the input from the sensors
		clock_edge_event1 = edge_detector(PORT->Group[CODE_INPUT1/32].IN.reg & (1<<(CODE_INPUT1%32)),0);  //input from Photo-interrupters (LTH-301-05)
		clock_edge_event2 = edge_detector(PORT->Group[CODE_INPUT2/32].IN.reg & (1<<(CODE_INPUT2%32)),1);  //input from Photo-interrupters (LTH-301-05)
		clock_edge_event3 = edge_detector(PORT->Group[CODE_INPUT3/32].IN.reg & (1<<(CODE_INPUT3%32)),2);  //input from Reflective Optical Sensor (CNY70)
		
		if(clock_edge_event1){
			//Start the timer
			timer_start(&TIMER_0);
		}else if(clock_edge_event2){
			//Stop the timer
			timer_stop(&TIMER_0);
		}else if(clock_edge_event3){
			
			//First Store the value of the timer to EEPROM
// 			SmartEEPROM8[MEM_ADDR] = (uint32_t *)min;
// 			SmartEEPROM8[MEM_ADDR+1] = (uint32_t *)s;
// 			SmartEEPROM8[MEM_ADDR+2] = (uint32_t *)c;
			
			// Then reset the variables for restarting the counting
			min = 0;
			s = 0;
		}
	}	
	
	return 0;
}
