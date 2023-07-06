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

/* A specific byte pattern stored at the begining of SmartEEPROM data area.
 * When the application comes from a reset, if it finds this signature,
 * the assumption is that the SmartEEPROM has some valid data.
 */
#define SMEE_CUSTOM_SIG 0x5a5a5a5a
/* Fixed address for storing the value of the counter. This address must be within the total
 * number of EEPROM data bytes ( Defined by SBLK and PSZ fuse values).
 */
#define MEM_ADDR 1
/* This example assumes SBLK = 1 and PSZ = 3, thus total size is 4096 bytes */
#define SEEP_FINAL_BYTE_INDEX 4095
/* Define a pointer to access SmartEEPROM as bytes */
uint8_t *SmartEEPROM8 = (uint8_t *)SEEPROM_ADDR;


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
	
	//Send the timer count via UART every 1s
	char timeString[6];
	sprintf(timeString, "%02d:%02d<%10d>\n", min, s, c);
	io_write(io, (uint8_t *)timeString, strlen(timeString));            //TO DO: check the actual length!
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	bool clock_edge_event1 = 0;
	bool clock_edge_event2 = 0;
	bool clock_edge_event3 = 0;
	bool clock_edge_event4 = 0;
	
	static bool timer_status = 0;  //variable for detecting if timer is counting or not

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
		
		//Detect the input from the DIP_SWITCH
		clock_edge_event1 = edge_detector(PORT->Group[CODE_INPUT1/32].IN.reg & (1<<(CODE_INPUT1%32)),0);  //input from Photo-interrupters (LTH-301-05)
		clock_edge_event2 = edge_detector(PORT->Group[CODE_INPUT2/32].IN.reg & (1<<(CODE_INPUT2%32)),1);  //input from Reflective Optical Sensor (CNY70)  
		
		if(clock_edge_event1 && timer_status == 0){
			timer_start(&TIMER_0);
			timer_status = 1;
		}else if(clock_edge_event1 && timer_status == 1){
			timer_stop(&TIMER_0);
			timer_status = 0;
		}else if(clock_edge_event2){
			
			//First Store the value of the timer to EEPROM
			SmartEEPROM8[MEM_ADDR] = (uint32_t *)min;
			SmartEEPROM8[MEM_ADDR+1] = (uint32_t *)s;
			SmartEEPROM8[MEM_ADDR+2] = (uint32_t *)c;
			
			// Then reset the variables for restarting the counting
			min = 0;
			s = 0;
		}
	}	
	
	return 0;
}
