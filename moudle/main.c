#include "platform.h"

int main(void) {
    platform_init();                  
	while(1) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
		delay_ms(200);
	}
}


