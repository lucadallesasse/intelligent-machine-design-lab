#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include "set_duty.h"

static uint8_t buff = 0;
struct io_descriptor *io_UART;
struct io_descriptor *io_SPI;
struct io_descriptor *io_I2C;
static uint8_t pot_write[2];

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Initialization of the UART communication */
	//usart_sync_register_callback(&EDBG_UART, USART_ASYNC_RXC_CB, rx_cb_USART_0);
	usart_sync_get_io_descriptor(&EDBG_UART, &io_UART);
	usart_sync_enable(&EDBG_UART);
	
	/* Initialization of the SPI communication */
	spi_m_sync_get_io_descriptor(&SPI_0, &io_SPI);
	spi_m_sync_enable(&SPI_0);	
	
	/* Initialization of the I2C communication */
	i2c_m_sync_get_io_descriptor(&I2C_0, &io_I2C);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x56, I2C_M_SEVEN);
	
	//At the startup read the stored value of the potentiometer value
	volatile uint8_t buff_read[1] = {0};
	io_write(io_I2C, buff_read, 1);
	volatile uint8_t stored_value[1];
	io_read(io_I2C, stored_value, 1);
	
	volatile uint8_t initial_res[2] = {0b00000000, stored_value[0]};
	
 	gpio_set_pin_level(SPI_CS,false);
	io_write(io_SPI, &initial_res, 2);
	gpio_set_pin_level(SPI_CS,true);
 
	while (1){
		
		//Read input command from terminal
		io_read(io_UART,&buff,1);
		
		//Set the number of increment for the potentiometer
		pot_write[1] = set_duty(buff);
		pot_write[0]= 0b00000000;
	
		//Send to the potentiometer through the SPI
		gpio_set_pin_level(SPI_CS,false);
		io_write(io_SPI, &pot_write, 2);
		gpio_set_pin_level(SPI_CS,true);
		
		//Write to memory after the new value is sent to the potentiometer
		volatile uint8_t buff[2] = {0, pot_write[1]};
		io_write(io_I2C, buff, 2);		
	}
	
	return 0;
}
