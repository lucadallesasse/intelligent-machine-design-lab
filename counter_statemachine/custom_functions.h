#ifndef CUSTOM_FUNCTIONS_H_INCLUDED
#define CUSTOM_FUNCTIONS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <atmel_start.h>

int HandleEvent(int);
bool edge_detector(void);
	
#ifdef __cplusplus
}
#endif
#endif