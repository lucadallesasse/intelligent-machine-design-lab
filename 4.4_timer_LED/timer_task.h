#ifndef TIMER_TASK_H_INCLUDED
#define TIMER_TASK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <atmel_start.h>
#include <pwm.h>

bool timer_task1_cb(const struct timer_task *const timer_task);
bool timer_task2_cb(const struct timer_task *const timer_task);
	
#ifdef __cplusplus
}
#endif
#endif