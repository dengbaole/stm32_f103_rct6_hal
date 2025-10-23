#include "platform.h"

int main(void) {
    platform_init();                  
	while(1) {
		HAL_GPIO_TogglePin(LED2_PORT, LED2_B_PIN);
		HAL_GPIO_TogglePin(LED_B_PORT, LED_B_PIN);
		HAL_GPIO_TogglePin(LED_R_PORT, LED_R_PIN);
		HAL_GPIO_TogglePin(LED_G_PORT, LED_G_PIN);
		delay_ms(200);
	}
}


