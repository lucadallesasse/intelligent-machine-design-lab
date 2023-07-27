/*
 * uart.c
 *
 * Created: 25/07/2022 18:48:47
 *  Author: IMDL_USER_7
 */ 


#include "UART.h"

uint8_t UART_TEST[23] = "Motor input uart speed";
static void tx_cb_USART_0(const struct usart_sync_descriptor *
const io_descr) {
	/* Transfer completed */
	//gpio_toggle_pin_level(LED0);
}

static void rx_cb_USART_0(const struct usart_sync_descriptor *
const io_descr) {
	/* Receive completed */
	data_arrived = 1;
}

static void err_cb_USART_0(const struct usart_sync_descriptor *
const io_descr) {

}

void uart_initialization() {
	usart_async_register_callback( & USART_0, USART_ASYNC_TXC_CB, tx_cb_USART_0);
	usart_async_register_callback( & USART_0, USART_ASYNC_RXC_CB, rx_cb_USART_0);
	usart_async_register_callback( & USART_0, USART_ASYNC_ERROR_CB, err_cb_USART_0);
	usart_async_get_io_descriptor( & USART_0, & io);
	usart_async_enable( & USART_0);

}
