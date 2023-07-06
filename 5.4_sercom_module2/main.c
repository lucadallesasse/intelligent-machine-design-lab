#include <atmel_start.h>
#include "custom_functions.h"
#include <pwm.h>
#include <string.h>
#include <stdio.h>
#include "set_duty.h"

/* Fixed address for storing the value of the counter. This address must be within the total
 * number of EEPROM data bytes ( Defined by SBLK and PSZ fuse values).
 */
#define MEM_ADDR 1
/* This example assumes SBLK = 1 and PSZ = 3, thus total size is 4096 bytes */
#define SEEP_FINAL_BYTE_INDEX 4095
/* Define a pointer to access SmartEEPROM as bytes */
uint8_t *SmartEEPROM8 = (uint8_t *)SEEPROM_ADDR;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	double duty = 0;

	/* Initialization of the UART communication */
	static struct io_descriptor *io1;
	uint8_t buff = 0;
	usart_sync_get_io_descriptor(&EDBG_UART, &io1);
	usart_sync_enable(&EDBG_UART);
	
	/* Initialization of the UART communication */
	static struct io_descriptor *io2;
	uint8_t out_buff = 0;
	uint8_t in_buff = 0;
	usart_sync_get_io_descriptor(&UART, &io2);
	usart_sync_enable(&UART);
	
	/* Initialization of the SPI communication */
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);
	spi_m_sync_enable(&SPI_0);
	
	//PWM to set the desired duty cycle
	tcc_set_period_value(TCC0, 0x1770);
	
	while (1){
		
		//Read input command from terminal
		io_read(io1,&buff,1);
		
		duty = set_duty(buff);
		//Send to the potentiometer through the SPI
		io_write(io, &duty, 1);
		SmartEEPROM8[MEM_ADDR] = (uint32_t *)duty;
		 
	}
	
	return 0;
}
