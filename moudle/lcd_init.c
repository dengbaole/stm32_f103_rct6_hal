#include "lcd_init.h"
#include "delay.h"
#include <string.h>

uint8_t display_buff[DISPLAY_BUF_SIZE];
uint8_t rx_buff[DISPLAY_BUF_SIZE + 4];
uint8_t tx_buff[DISPLAY_BUF_SIZE + 4];


void lcd_gpio_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitStruct.Pin = LCD_SPI_PIN_SCK ;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin =  LCD_SPI_PIN_MOSI;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = LCD_BLK_PIN ;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	LCD_BL_OFF();
	GPIO_InitStruct.Pin =  LCD_RES_PIN;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


	GPIO_InitStruct.Pin = LCD_DC_PIN;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	

	

	
	GPIO_InitStruct.Pin = LCD_CS_PIN ;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}




void LCD_Writ_Bus(uint8_t dat) {
	TFT_CS_LOW();
	
	HAL_SPI_Transmit(&hspi2, &dat, 1, HAL_MAX_DELAY);
	TFT_CS_HIGH();
}



void LCD_WR_DATA8(uint8_t dat) {
	LCD_Writ_Bus(dat);
}



void LCD_WR_DATA(uint16_t dat) {
	LCD_Writ_Bus(dat >> 8);
	LCD_Writ_Bus(dat);
}



void LCD_WR_REG(uint8_t dat) {
	TFT_RS_CMD();//д����
	LCD_Writ_Bus(dat);
	TFT_RS_DATA();//д����
}



void tftSetWindows(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	if(USE_HORIZONTAL == 0) {
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 26);
		LCD_WR_DATA(x2 + 26);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 1);
		LCD_WR_DATA(y2 + 1);
		LCD_WR_REG(0x2c);//������д
	} else if(USE_HORIZONTAL == 1) {
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 26);
		LCD_WR_DATA(x2 + 26);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 1);
		LCD_WR_DATA(y2 + 1);
		LCD_WR_REG(0x2c);//������д
	} else if(USE_HORIZONTAL == 2) {
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 1);
		LCD_WR_DATA(x2 + 1);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 26);
		LCD_WR_DATA(y2 + 26);
		LCD_WR_REG(0x2c);//������д
	} else {
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1 + 1);
		LCD_WR_DATA(x2 + 1);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1 + 26);
		LCD_WR_DATA(y2 + 26);
		LCD_WR_REG(0x2c);//������д
	}
}

void lcd_init(void) {

	LCD_RES_Clr();
	delay_ms(10);
	LCD_RES_Set();
	delay_ms(10);
	delay_ms(10);
	LCD_WR_REG(0x11);     //Sleep out
	delay_ms(12);                //Delay 120ms
	LCD_WR_REG(0xB1);     //Normal mode
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB2);     //Idle mode
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB3);     //Partial mode
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x3C);
	LCD_WR_REG(0xB4);     //Dot inversion
	LCD_WR_DATA8(0x03);
	LCD_WR_REG(0xC0);     //AVDD GVDD
	LCD_WR_DATA8(0xAB);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x04);
	LCD_WR_REG(0xC1);     //VGH VGL
	LCD_WR_DATA8(0xC5);   //C0
	LCD_WR_REG(0xC2);     //Normal Mode
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0xC3);     //Idle
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0x6A);
	LCD_WR_REG(0xC4);     //Partial+Full
	LCD_WR_DATA8(0x8D);
	LCD_WR_DATA8(0xEE);
	LCD_WR_REG(0xC5);     //VCOM
	LCD_WR_DATA8(0x0F);
	LCD_WR_REG(0xE0);     //positive gamma
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x0E);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x36);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x10);
	LCD_WR_REG(0xE1);     //negative gamma
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x02);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x25);
	LCD_WR_DATA8(0x35);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x10);
	LCD_WR_REG(0xFC);
	LCD_WR_DATA8(0x80);
	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL == 0) {
		LCD_WR_DATA8(0x08);
	} else if(USE_HORIZONTAL == 1) {
		LCD_WR_DATA8(0xC8);
	} else if(USE_HORIZONTAL == 2)	{
		LCD_WR_DATA8(0x78);
	} else {
		LCD_WR_DATA8(0xA8);
	}
	LCD_WR_REG(0x21);     //Display inversion
	LCD_WR_REG(0x29);     //Display on

}



void lcd_clear(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color) {
	uint16_t i, j;
	tftSetWindows(xsta, ysta, xend - 1, yend - 1); //设置显示范围
	// for(i = ysta; i < yend; i++) {
	// 	for(j = xsta; j < xend; j++) {
	// 		LCD_WR_DATA(color);
	// 	}
	// }
	memset(display_buff, 0x66, 160);
	TFT_RS_DATA();  // 数据模式
	TFT_CS_LOW();
	for(uint16_t i = 0; i < 160; i++) {
		SPI2_SendData_DMA(display_buff, 160);
	}

	TFT_CS_HIGH();
}



// void LCD_ShowPicture2(uint16_t x, uint16_t y, const sBITMAP* pic) {
// 	uint16_t i, j;
// 	u32 k = 0;
// 	tftSetWindows(x, y, x + pic->w - 1, y + pic->h - 1);

// 	for(i = 0; i < pic->h; i++) {
// 		for(j = 0; j < pic->w; j++) {
// 			LCD_WR_DATA8(pic->map[k * 2]);
// 			LCD_WR_DATA8(pic->map[k * 2 + 1]);
// 			k++;
// 		}
// 	}
// }

//void LCD_ShowPicture2(uint16_t x, uint16_t y, const sBITMAP* pic) {
//	uint32_t buf_size = pic->w * pic->h * 2;

//	tftSetWindows(x, y, x + pic->w - 1, y + pic->h - 1);

//	TFT_RS_DATA();  // 数据模式
//	TFT_CS_LOW();
//	for(uint16_t i = 0; i < 16; i++) {
//		SPI2_SendData_DMA((uint8_t*)pic->map + i * 1600, 1600);
//	}

//	TFT_CS_HIGH();
//}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
	// 设置像素位置的窗口
	uint8_t buff_temp[2];
	buff_temp[0] = color >> 4;
	buff_temp[1] = color & 0x0f;
	tftSetWindows(x, y, x, y);

	TFT_RS_DATA();  // 数据模式
	TFT_CS_LOW();

	// 发送颜色数据，高位和低位
	SPI2_SendData_DMA(buff_temp, 2);  // 发送2个字节（16位颜色）

	TFT_CS_HIGH();
}


// #include "flash_drv.h"

// void LCD_ShowPicture_test(uint16_t x, uint16_t y, uint32_t add) {
// 	uint16_t i, j;
// 	uint32_t k = add;
// 	tftSetWindows(x, y, 80 - 1, 160 - 1);
// 	// memset(sector_data, 0x80, 1600);

// 	for(i = 0; i < 16; i++) {
// 		memset(tx_buff, 0xff, 1600);
// 		W25Q128_ReadData(rx_buff, k + i * 1600, 1600);
// 		// memset(rx_buff, i, 1600);
// 		// for(j = 0; j < 800; j++) {
// 		// 	LCD_WR_DATA8(sector_data[j*2]);
// 		// 	LCD_WR_DATA8(sector_data[j*2+1]);
// 		// }
// 		TFT_RS_DATA();  // 数据模式
// 		TFT_CS_LOW();
// 		// for(uint16_t i = 0; i < 16; i++){
// 		// SPI2_SendData_DMA(rx_buff, 1600);

// 		SPI2_DMA_TransmitReceive(rx_buff + 1, tx_buff, 1600); //？？
// 		// }

// 		TFT_CS_HIGH();
// 	}
// }


static uint8_t get_max(uint8_t a, uint8_t b) {
	return a > b ? a : b;
}

static uint8_t get_min(uint8_t a, uint8_t b) {
	return a < b ? a : b;
}

// 没有边界检测
// 背景图放最前面
// void display_component(FLASH_sBITMAP_TABLE* bitmap_table) {
// 	uint16_t current_screen_h_end = 0;
// 	uint16_t current_screen_h_start = 0;

// 	uint16_t picture_h_end = 0;
// 	uint16_t picture_h_start = 0;

// 	uint16_t draw_h_end = 0;
// 	uint16_t draw_h_start = 0;
// 	tftSetWindows(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
// 	for(uint16_t j = 0; j < SPLIT_SCREEN; j++) {
// 		current_screen_h_start = j * DISPLAY_HEIGHT / SPLIT_SCREEN;
// 		current_screen_h_end += DISPLAY_HEIGHT / SPLIT_SCREEN; //display_buff 高度 0-4行


// 		memset(display_buff, 0x00, DISPLAY_BUF_SIZE);
// 		// TFT_CS_HIGH();
// 		for(uint8_t i = 0; bitmap_table[i].bitmap != NULL; i++) {
// 			//在获取每张图片的数据

// 			//如果图片在屏幕内，则获取数据
// 			picture_h_start = bitmap_table[i].y;
// 			picture_h_end = bitmap_table[i].y + bitmap_table[i].bitmap->h;
// 			draw_h_start = get_max(current_screen_h_start, picture_h_start);
// 			draw_h_end = get_min(current_screen_h_end, picture_h_end);
// 			if(draw_h_start <= draw_h_end) {
// 				//地址
// 				// Read_Flash_Start(bitmap_table[i].bitmap->map_address + (draw_h_start - picture_h_start)* bitmap_table[i].bitmap->w * 2);
// 				// FLASH_CS_LOW();
// 				// //接收数据
// 				// spi_dma_rx_date(rx_buff, (draw_h_end - draw_h_start) * bitmap_table[i].bitmap->w * 2);
// 				// FLASH_CS_HIGH();

// 				//数据接收
// 				W25Q128_ReadData(rx_buff, bitmap_table[i].bitmap->map_address + (draw_h_start - picture_h_start)* bitmap_table[i].bitmap->w * 2, (draw_h_end - draw_h_start) * bitmap_table[i].bitmap->w * 2);

// 				if(bitmap_table[i].bitmap->h == DISPLAY_HEIGHT && bitmap_table[i].bitmap->w == DISPLAY_WIDTH) {
// 					for(uint8_t k = 0; k < (draw_h_end - draw_h_start); k++) {
// 						memcpy(&display_buff[(draw_h_start - current_screen_h_start + k)*DISPLAY_WIDTH * 2 + bitmap_table[i].x * 2], &rx_buff[k * bitmap_table[i].bitmap->w * 2 + 1], bitmap_table[i].bitmap->w * 2);
// 					}
// 				} else {
// 					for(uint16_t k = 0; k < (draw_h_end - draw_h_start); k++) {
// 						for(uint16_t x = 0; x < bitmap_table[i].bitmap->w; x++) {
// 							// 计算源和目标索引
// 							uint16_t src_index = k * bitmap_table[i].bitmap->w * 2 + x * 2;
// 							uint16_t dst_index = (draw_h_start - current_screen_h_start + k) * DISPLAY_WIDTH * 2 + bitmap_table[i].x * 2 + x * 2;
// 							// if (src_index + 1 >= DISPLAY_BUF_SIZE) {
// 							// 	continue; // 跳过超出源缓冲区的像素
// 							// }

// 							// if (dst_index + 1 >= DISPLAY_BUF_SIZE) {
// 							// 	continue; // 跳过超出目标缓冲区的像素
// 							// }
// 							// 读取源像素
// 							// uint16_t pixel = rx_buff[src_index] | (rx_buff[src_index + 1] << 8);

// 							// 检查是否为透明色
// 							// if(pixel != 0x0000) {
// 							// 复制像素到目标缓冲区
// 							display_buff[dst_index] |= rx_buff[src_index + 1];
// 							display_buff[dst_index + 1] |= rx_buff[src_index + 2];
// 							// }
// 						}
// 					}
// 				}
// 			}
// 		}

// 		// TFT_RS_DATA();
// 		// TFT_CS_LOW();
// 		// spi_dma_tx_date(display_buff, DISPLAY_BUF_SIZE);
// 		// TFT_CS_HIGH();


// 		// tftsetdcandcs(1, 0);
// 		// spi_write_blocking(SPI_PORT, display_buff, DISPLAY_BUF_SIZE);
// 		// tftsetdcandcs(1, 1);

// 		TFT_RS_DATA();  // 数据模式
// 		TFT_CS_LOW();
// 		SPI2_DMA_TransmitReceive(display_buff, tx_buff, DISPLAY_BUF_SIZE); //？？
// 		TFT_CS_HIGH();
// 	}
// }


