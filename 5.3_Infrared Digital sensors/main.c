#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"
#include <pwm.h>

static uint8_t buff;
static uint8_t in_buff;

struct io_descriptor *io1;
struct io_descriptor *io2;

static void rx_cb_USART_0(const struct usart_async_descriptor *const io_descr)
{
	//Write to the UART_TX channel to drive the transistor
	io_write(io2,&buff,1);
}


static void rx_cb_USART_1(const struct usart_async_descriptor *const io_descr)
{
	/* Receive completed */
	//Write the Ecco to the EDBG terminal
	io_write(io1, &in_buff, 1);
}

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/* Initialization of the UART communication */
	usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, rx_cb_USART_0);
	usart_async_get_io_descriptor(&USART_0, &io1);
	usart_async_enable(&USART_0);
	
	/* Initialization of the UART communication */
 	usart_async_register_callback(&USART_1, USART_ASYNC_RXC_CB, rx_cb_USART_1);
 	usart_async_get_io_descriptor(&USART_1, &io2);
 	usart_async_enable(&USART_1);
	 
	tcc_set_period_value(TCC0, 0x4E*3/2);  
	tcc_set_compare_value(TCC0, 0x4E*3/4, 0);
	
	while (1) {
		//Read input command from terminal
		io_read(io1,&buff,1);
		
		//Read CMOS output of the phototransistor output
		io_read(io2,&in_buff,1);
	
	}
}
