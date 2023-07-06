/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAME54 has 14 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8
#define GPIO_PIN_FUNCTION_J 9
#define GPIO_PIN_FUNCTION_K 10
#define GPIO_PIN_FUNCTION_L 11
#define GPIO_PIN_FUNCTION_M 12
#define GPIO_PIN_FUNCTION_N 13

#define PA00 GPIO(GPIO_PORTA, 0)
#define PA04 GPIO(GPIO_PORTA, 4)
#define PA05 GPIO(GPIO_PORTA, 5)
#define PA08 GPIO(GPIO_PORTA, 8)
#define PA10 GPIO(GPIO_PORTA, 10)
#define DIP_IN GPIO(GPIO_PORTB, 1)
#define LED_green2 GPIO(GPIO_PORTB, 4)
#define CODE_INPUT1 GPIO(GPIO_PORTB, 5)
#define CODE_INPUT2 GPIO(GPIO_PORTB, 6)
#define CODE_INPUT3 GPIO(GPIO_PORTB, 14)
#define CODE_INPUT4 GPIO(GPIO_PORTB, 15)
#define PB24 GPIO(GPIO_PORTB, 24)
#define PB25 GPIO(GPIO_PORTB, 25)
#define SW0 GPIO(GPIO_PORTB, 31)
#define LED0 GPIO(GPIO_PORTC, 18)

#endif // ATMEL_START_PINS_H_INCLUDED
