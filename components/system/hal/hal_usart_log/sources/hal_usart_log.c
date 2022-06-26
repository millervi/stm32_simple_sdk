/*!
    \file hal_usart_log.c
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-21
*/

#include "hal_usart_log.h"
#include "usart_log.h"
/* ====================================================================== */

void hal_usart_log_init(void)
{
    usart_log_init();
}
/* ====================================================================== */

void hal_usart_log_deinit(void)
{
    usart_log_deinit();
}
/* ====================================================================== */