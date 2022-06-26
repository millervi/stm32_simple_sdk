/*!
    \file bsp.c
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

#include "bsp.h"
#include "system_clock.h"
#include "hal_usart_log.h"
#include "logger.h"
/* ====================================================================== */

#if defined(LOGGER_ON)
/*! \brief Local bsp tag, using for messages of log */
static const char* TAG = "BSP";
#endif /* LOGGER_ON */
/* ====================================================================== */

void bsp_init(void) {
	system_rcc_init();
	hal_usart_log_init();
	LOGGER(LOG_LEVEL_I, TAG, "Bsp init");
}
/* ====================================================================== */

void bsp_deinit(void) {
    /*! \todo */
}
/* ====================================================================== */
