/*!
    \file hal_usart_log.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-21
*/

/* Define to prevent recursive inclusion */
#ifndef _HAL_USART_LOG_H_
#define _HAL_USART_LOG_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief HAL function for init usart log */
void  hal_usart_log_init(void);

/*! \brief HAL function for deinit usart log */
void  hal_usart_log_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_USART_LOG_H_ */