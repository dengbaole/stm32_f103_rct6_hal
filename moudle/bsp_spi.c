#include "bsp_spi.h"

volatile uint8_t dma_tx_complete = 0;
volatile uint8_t dma_rx_complete = 0;

SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;
DMA_HandleTypeDef hdma_spi2_rx;

// DMA传输完成中断回调函数
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi) {
	if(hspi->Instance == SPI2) {
		dma_tx_complete = 1;
	}
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi) {
	if(hspi->Instance == SPI2) {
		dma_rx_complete = 1;
	}
}

// DMA错误中断回调函数
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* hspi) {
	if(hspi->Instance == SPI2) {
		// 处理错误
		dma_tx_complete = 1;
		dma_rx_complete = 1;
	}
}

void spi2_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// 使能时钟
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();

	// GPIO配置: PB13-SCK, PB14-MISO, PB15-MOSI
	GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;  // SCK, MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_14;  // MISO
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// SPI2配置
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	HAL_SPI_Init(&hspi2);

	// DMA发送通道配置 (DMA1 Channel5 - SPI2_TX)
	hdma_spi2_tx.Instance = DMA1_Channel5;
	hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_spi2_tx.Init.Mode = DMA_NORMAL;
	hdma_spi2_tx.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&hdma_spi2_tx);

	// 关联DMA到SPI
	__HAL_LINKDMA(&hspi2, hdmatx, hdma_spi2_tx);

	// DMA接收通道配置 (DMA1 Channel4 - SPI2_RX)
	hdma_spi2_rx.Instance = DMA1_Channel4;
	hdma_spi2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_spi2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi2_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_spi2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_spi2_rx.Init.Mode = DMA_NORMAL;
	hdma_spi2_rx.Init.Priority = DMA_PRIORITY_HIGH;
	HAL_DMA_Init(&hdma_spi2_rx);

	// 关联DMA到SPI
	__HAL_LINKDMA(&hspi2, hdmarx, hdma_spi2_rx);

	// 使能DMA中断
	HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0x01, 0x01);
	HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0x01, 0x02);
	HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

// DMA中断服务函数
void DMA1_Channel4_IRQHandler(void) {
	HAL_DMA_IRQHandler(&hdma_spi2_rx);
}

void DMA1_Channel5_IRQHandler(void) {
	HAL_DMA_IRQHandler(&hdma_spi2_tx);
}

void SPI2_DMA_TransmitReceive(uint8_t* txbuf, uint8_t* rxbuf, uint16_t len) {
	// 等待之前的DMA传输完成
	while (__HAL_DMA_GET_FLAG(&hdma_spi2_tx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi2_tx)));
	while (__HAL_DMA_GET_FLAG(&hdma_spi2_rx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi2_rx)));

	// 清除标志
	dma_tx_complete = 0;
	dma_rx_complete = 0;

	// 启动DMA传输
	HAL_SPI_TransmitReceive_DMA(&hspi2, txbuf, rxbuf, len);

	// 等待传输完成
	while (!dma_tx_complete || !dma_rx_complete);

	// 等待SPI传输完成
	while (__HAL_SPI_GET_FLAG(&hspi2, SPI_FLAG_TXE) == RESET);
	while (__HAL_SPI_GET_FLAG(&hspi2, SPI_FLAG_BSY) == SET);
}

uint8_t SPI_ReadWriteByte(uint8_t TxData) {
	uint8_t RxData = 0;
	SPI2_DMA_TransmitReceive(&TxData, &RxData, 1);
	return RxData;
}

void SPI2_SendData_DMA(uint8_t* txbuf, uint16_t len) {
	// 等待之前的DMA传输完成
	while (__HAL_DMA_GET_FLAG(&hdma_spi2_tx, __HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi2_tx)));

	dma_tx_complete = 0;

	// 启动DMA发送
	HAL_SPI_Transmit_DMA(&hspi2, txbuf, len);

	// 等待传输完成
	while (!dma_tx_complete);

	// 等待SPI传输完成
	while (__HAL_SPI_GET_FLAG(&hspi2, SPI_FLAG_TXE) == RESET);
	while (__HAL_SPI_GET_FLAG(&hspi2, SPI_FLAG_BSY) == SET);
}