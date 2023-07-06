/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_usart_sync.h>

#include <hal_usart_sync.h>

#include <hal_delay.h>
#include <hal_timer.h>
#include <hpl_tc_base.h>
#include <tc_lite.h>
#include <hal_timer.h>
#include <hpl_tc_base.h>

extern struct usart_sync_descriptor UART;

extern struct usart_sync_descriptor EDBG_UART;

extern struct timer_descriptor TIMER_1;
extern struct timer_descriptor TIMER_0;

void UART_PORT_init(void);
void UART_CLOCK_init(void);
void UART_init(void);

void EDBG_UART_PORT_init(void);
void EDBG_UART_CLOCK_init(void);
void EDBG_UART_init(void);

void delay_driver_init(void);

void PWM_0_CLOCK_init(void);

void PWM_0_PORT_init(void);

int8_t PWM_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
