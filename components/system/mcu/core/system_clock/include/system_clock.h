/*!
    \file system_clock.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

/* Define to prevent recursive inclusion */
#ifndef _SYSTEM_CLOCK_H_
#define _SYSTEM_CLOCK_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
/* ====================================================================== */

#ifndef NVIC_PRIORITYGROUP_0
/*! \brief 0 bit  for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007)
/*! \brief 1 bit  for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006)
/*! \brief 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005)
/*! \brief 3 bits for pre-emption priority, 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004)
/*! \brief 4 bits for pre-emption priority, 0 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003)
#endif
/* ====================================================================== */

/*! \brief Function for init system clock */
void system_rcc_init(void);

/*! \brief Function for deinit system clock */
void system_rcc_deinit(void);

/*!
	\brief Function for get sys tick counter
    \return Value system tick counter
*/
uint32_t system_get_tick_counter(void);

/*! \brief Handler of irq system tick */
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_CLOCK_H_ */
