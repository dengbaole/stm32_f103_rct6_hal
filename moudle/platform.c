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

	module_init();
	btim_timx_int_init(100 - 1, 720 - 1); // 1ms中断
	led_init();
	lcd_gpio_init();
	spi2_init();
	lcd_init();
	lcd_clear(0, 0, LCD_W, LCD_H, LBBLUE);
	lcd_clear(0, 0, 4, 4, RED);
	LCD_BL_ON();//打开背光
	// LCD_BL_OFF();

}
