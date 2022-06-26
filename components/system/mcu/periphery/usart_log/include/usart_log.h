/*!
    \file usart_log.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

/* Define to prevent recursive inclusion */
#ifndef _USART_LOG_H_
#define _USART_LOG_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
/* ====================================================================== */

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_MODULE                    USART2

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_BAUDRATE                  115200

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_TX_PORT 					GPIOA

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_TX_PIN 				    LL_GPIO_PIN_2

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_ALTERN_FUNC 				LL_GPIO_AF_7

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_BUS_CLK_EN			    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_BUS_CLK_DI			    LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2)

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_PORT_BUS_CLK_EN 		    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)

/*! \brief Usart log: HW usart definitions */
#define USART_LOG_PORT_BUS_CLK_DI 		    LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
/* ====================================================================== */

/*! \brief Function for init usart log */
void usart_log_init(void);

/*! \brief Function for deinit usart log */
void usart_log_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _USART_LOG_H_ */
