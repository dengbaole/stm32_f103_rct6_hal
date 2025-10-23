#include "platform.h"


uint8_t time_s = 0;
uint8_t time_m = 0;
uint8_t time_h = 0;
uint8_t beep_on_times = 3;


void platform_init(void) {
	HAL_Init();                         /* 初始化HAL库 */
	sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
	delay_init(72);                     /* 延时初始化 */
	app_sched_init();
	user_event_init();
	
	led_init();  
}
