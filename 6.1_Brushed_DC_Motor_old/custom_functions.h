#ifndef CUSTOM_FUNCTIONS_H_INCLUDED
#define CUSTOM_FUNCTIONS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <atmel_start.h>

bool HandleEvent(bool);
bool edge_detector(bool,int);
	
#ifdef __cplusplus
}
#endif
#endif