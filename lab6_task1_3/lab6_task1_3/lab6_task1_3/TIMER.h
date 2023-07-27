/*
 * TIMER.h
 *
 * Created: 25/07/2022 18:50:19
 *  Author: IMDL_USER_7
 */ 


#ifndef TIMER_H_
#define TIMER_H_#include <atmel_start.h>

#include "driver_init.h"

extern bool call_back_0_flag;
extern bool call_back_1_flag;

static struct timer_task TIMER_0_task1, TIMER_0_task2;
static void TIMER_0_task1_cb(const struct timer_task *
const timer_task);
static void TIMER_0_task2_cb(const struct timer_task *
const timer_task);
void TIMER_0_initialize_interval(void);

#endif /* TIMER_H_ */