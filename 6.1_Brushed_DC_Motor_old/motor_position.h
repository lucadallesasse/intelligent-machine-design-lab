#ifndef MOTOR_POSITION_H_INCLUDED
#define MOTOR_POSITION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <atmel_start.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_STEPS 30000
#define MIN_STEPS -30000


// State machine states
typedef enum {
	STATE_IDLE,
	STATE_FORWARD,
	STATE_BACKWARD
} State;

void motor_position(int encoder_step, int32_t *Steps, int8_t *Direction)
	
#ifdef __cplusplus
}
#endif
#endif