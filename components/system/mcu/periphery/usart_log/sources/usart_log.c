/*!
    \file usart_log.c
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

#include "usart_log.h"
/* ====================================================================== */

void usart_log_init(void) {
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*! \brief Peripheral clock enable */
	USART_LOG_BUS_CLK_EN;
	USART_LOG_PORT_BUS_CLK_EN;
	/*! \brief Usart / uart gpio tx configuration */
	GPIO_InitStruct.Pin = USART_LOG_TX_PIN;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = USART_LOG_ALTERN_FUNC;
	/*! \brief Init gpio tx */
	LL_GPIO_Init(USART_LOG_TX_PORT, &GPIO_InitStruct);
	/*! \brief Usart configuration */
	USART_InitStruct.BaudRate = USART_LOG_BAUDRATE;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	/*! \brief Init usart */
	LL_USART_Init(USART_LOG_MODULE, &USART_InitStruct);
	/*! \brief Enable usart */
	LL_USART_ConfigHalfDuplexMode(USART_LOG_MODULE);
	LL_USART_Enable(USART_LOG_MODULE);
}
/* ====================================================================== */

void usart_log_deinit(void) {
	/*! \brief Peripheral clock disable */
	USART_LOG_BUS_CLK_DI;
	USART_LOG_PORT_BUS_CLK_DI;
	/*! \brief Deinit gpio tx */
	LL_GPIO_DeInit(USART_LOG_TX_PORT);
	/*! \brief Deinit usart */
	LL_USART_DeInit(USART_LOG_MODULE);
	/*! \brief Disable usart */
	LL_USART_Disable(USART_LOG_MODULE);
}
/* ====================================================================== */

int __io_putchar(int ch) {
	uint8_t c[1];
	c[0] = ch & 0x00FF;
	while (!LL_USART_IsActiveFlag_TXE(USART_LOG_MODULE)) {
		/* Wait active flag TXE */
	}
	LL_USART_TransmitData8(USART_LOG_MODULE, *(uint8_t*)c);
	return ch;
}
/* ====================================================================== */

int _write(int file,char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		__io_putchar(*ptr++);
	}
	return len;
}
/* ====================================================================== */
