#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "bsp_spi.h"
#include "sys.h"

#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
	#define LCD_W 80
	#define LCD_H 160

#else
	#define LCD_W 160
	#define LCD_H 80
#endif


// ������ͷ�ļ����������¶���


#define LCD_SPI_GPIO          GPIOB
#define LCD_SPI_PIN_MOSI      GPIO_PIN_15
#define LCD_SPI_PIN_SCK       GPIO_PIN_13

#define LCD_CS_PIN           GPIO_PIN_2  // PD2
#define LCD_DC_PIN           GPIO_PIN_12  // PC12
#define LCD_RES_PIN          GPIO_PIN_11  // PC11
#define LCD_BLK_PIN          GPIO_PIN_10 // PC10





#define LCD_SCLK_Clr() HAL_GPIO_WritePin(LCD_SPI_GPIO,LCD_SPI_PIN_SCK,GPIO_PIN_RESET)//SCL=SCLK
#define LCD_SCLK_Set() HAL_GPIO_WritePin(LCD_SPI_GPIO,LCD_SPI_PIN_SCK,GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(LCD_SPI_GPIO,LCD_SPI_PIN_MOSI,GPIO_PIN_RESET)//SDA=MOSI
#define LCD_MOSI_Set() HAL_GPIO_WritePin(LCD_SPI_GPIO,LCD_SPI_PIN_MOSI,GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOC,LCD_RES_PIN,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOC,LCD_RES_PIN,GPIO_PIN_SET)

#define TFT_RS_CMD()   HAL_GPIO_WritePin(GPIOC,LCD_DC_PIN,GPIO_PIN_RESET)//DC
#define TFT_RS_DATA()   HAL_GPIO_WritePin(GPIOC,LCD_DC_PIN,GPIO_PIN_SET)

#define TFT_CS_LOW()   HAL_GPIO_WritePin(GPIOD,LCD_CS_PIN,GPIO_PIN_RESET)//CS
#define TFT_CS_HIGH()   HAL_GPIO_WritePin(GPIOD,LCD_CS_PIN,GPIO_PIN_SET)

#define LCD_BL_ON()  HAL_GPIO_WritePin(GPIOC,LCD_BLK_PIN,GPIO_PIN_RESET)//BLK
#define LCD_BL_OFF()  HAL_GPIO_WritePin(GPIOC,LCD_BLK_PIN,GPIO_PIN_SET)


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE           	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

#define DISPLAY_WIDTH 80
#define DISPLAY_HEIGHT 160
#define SPLIT_SCREEN 160   //DISPLAY_WIDTH * DISPLAY_HEIGHT*2/SPLIT_SCREEN 需要整除
#define DISPLAY_BUF_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT*2/SPLIT_SCREEN)
extern uint8_t display_buff[DISPLAY_BUF_SIZE];
extern uint8_t rx_buff[DISPLAY_BUF_SIZE + 4];
extern uint8_t tx_buff[DISPLAY_BUF_SIZE + 4];

void lcd_gpio_init(void);//��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void tftSetWindows(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); //�������꺯��
void lcd_init(void);//LCD��ʼ��
void lcd_clear(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
// void LCD_ShowPicture2(uint16_t x, uint16_t y, const sBITMAP* pic);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_ShowPicture_test(uint16_t x, uint16_t y, uint32_t add);
// void display_component(FLASH_sBITMAP_TABLE* bitmap_table);
#endif




