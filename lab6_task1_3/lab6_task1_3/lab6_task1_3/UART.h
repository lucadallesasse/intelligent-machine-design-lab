/*
 * UART.h
 *
 * Created: 25/07/2022 18:49:21
 *  Author: IMDL_USER_7
 */ 



#ifndef UART_H_
#define UART_H_#include <atmel_start.h>

#include "driver_init.h"

volatile static uint32_t data_arrived = 0;
struct io_descriptor * io;

void uart_initialization();
static void tx_cb_USART_0(const struct usart_async_descriptor *
const io_descr);
static void rx_cb_USART_0(const struct usart_async_descriptor *
const io_descr);
static void err_cb_USART_0(const struct usart_async_descriptor *
const io_descr);

#endif /* UART_H_ */