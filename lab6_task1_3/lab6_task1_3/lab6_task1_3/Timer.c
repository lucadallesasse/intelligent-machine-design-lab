/*
 * Timer.c
 *
 * Created: 25/07/2022 18:50:56
 *  Author: IMDL_USER_7
 */ 
#include "Timer.h"

bool call_back_0_flag = 0;
bool call_back_1_flag = 0;

/**
 * Example of using TIMER_0.
 */

static void TIMER_0_task1_cb(const struct timer_task *
  const timer_task) {
  call_back_0_flag = 1;
}

static void TIMER_0_task2_cb(const struct timer_task *
  const timer_task) {
  call_back_1_flag = 1;
}

void TIMER_0_initialize_interval(void) {


  TIMER_0_task1.interval = 100;
  TIMER_0_task1.cb = TIMER_0_task1_cb;
  TIMER_0_task1.mode = TIMER_TASK_REPEAT;
  TIMER_0_task2.interval = 10;
  TIMER_0_task2.cb = TIMER_0_task2_cb;
  TIMER_0_task2.mode = TIMER_TASK_REPEAT;

  timer_add_task( & TIMER_0, & TIMER_0_task1);
  timer_add_task( & TIMER_0, & TIMER_0_task2);
  timer_start( & TIMER_0);
}