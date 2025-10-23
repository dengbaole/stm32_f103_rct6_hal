#include "led_drv.h"


void led_init(void) {
	GPIO_InitTypeDef gpio_init_struct;

	__HAL_RCC_GPIOC_CLK_ENABLE();

	gpio_init_struct.Pin = LED2_B_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED2_PORT, &gpio_init_struct);
	HAL_GPIO_WritePin(LED2_PORT, LED2_B_PIN, GPIO_PIN_SET);

	gpio_init_struct.Pin = LED_B_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_B_PORT, &gpio_init_struct);
	HAL_GPIO_WritePin(LED_B_PORT, LED_B_PIN, GPIO_PIN_SET);

	gpio_init_struct.Pin = LED_R_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_R_PORT, &gpio_init_struct);
	HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_SET);

	gpio_init_struct.Pin = LED_G_PIN;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_G_PORT, &gpio_init_struct);
	HAL_GPIO_WritePin(LED_G_PORT, LED_G_PIN, GPIO_PIN_SET);
}


