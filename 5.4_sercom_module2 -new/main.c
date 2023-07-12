#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include "custom_functions.h"
#include "set_duty.h"

static uint8_t buff = 0;
static int incr = 0;

struct io_descriptor *io_UART;
struct io_descriptor *io_SPI;
struct io_descriptor *io_I2C;

uint8_t pot_incr = 0b00000100;
uint8_t pot_decr = 0b00001000;

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
	
	gpio_set_pin_level(SPI_CS,false);
	for(int i=0; i < 257; i++){
		io_write(io_SPI, &pot_incr, 1);
	}
	gpio_set_pin_level(SPI_CS,true);
	
	/* Initialization of the I2C communication */
	i2c_m_sync_get_io_descriptor(&I2C_0, &io_I2C);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x56, I2C_M_SEVEN);
	
	//At the startup read the stored value of the potentiometer value
	io_read(io_I2C,&incr, 1);
 	gpio_set_pin_level(SPI_CS,false);
 	for(int i=0; i < incr; i++){
 		io_write(io_SPI, &pot_incr, 1);
 	}
 	gpio_set_pin_level(SPI_CS,true);

	while (1){
		
		//Read input command from terminal
		io_read(io_UART,&buff,1);
		
		/* Receive completed */
		gpio_set_pin_level(SPI_CS,false);
		for(int i=0; i < incr; i++){
			io_write(io_SPI, &pot_decr, 1);
		}
		gpio_set_pin_level(SPI_CS,true);
		
		//Set the number of increment for the potentiometer
		incr = set_duty(buff);
		
		//Send to the potentiometer through the SPI
		gpio_set_pin_level(SPI_CS,false);
		for(int i=0; i < incr; i++){
			io_write(io_SPI, &pot_incr, 1);
		}
		gpio_set_pin_level(SPI_CS,true);
		
		//Write to memory after the new value is sent to the potentiometer
		io_write(io_I2C, &incr, 1);	
		
	}
	
	return 0;
}
