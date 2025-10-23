#ifndef _PLATFORM_H_
#define _PLATFORM_H_


#include "stm32f1xx.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led_drv.h"

extern uint8_t time_m;
extern uint8_t time_h;
extern uint8_t beep_on_times;


void platform_init(void);

#endif // !_PLATFORM_H_

