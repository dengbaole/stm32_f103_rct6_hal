#ifndef __LED_H
#define __LED_H

#include "sys.h"
#include "platform.h"

#define LED2_B_PIN           GPIO_PIN_7
#define LED2_PORT           GPIOC

#define LED_B_PIN           GPIO_PIN_0
#define LED_B_PORT           GPIOC
#define LED_R_PIN           GPIO_PIN_1
#define LED_R_PORT           GPIOC
#define LED_G_PIN           GPIO_PIN_2
#define LED_G_PORT           GPIOC


void led_init(void);

#endif

