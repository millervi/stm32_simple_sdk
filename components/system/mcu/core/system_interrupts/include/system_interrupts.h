/*!
    \file system_interrupts.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-21
*/

/* Define to prevent recursive inclusion */
#ifndef _SYSTEM_INTERRUPTS_H_
#define _SYSTEM_INTERRUPTS_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Function for handles non maskable interrupt */
void NMI_Handler(void);

/*! \brief Function for handles hard fault interrupt */
void HardFault_Handler(void);

/*! \brief Function for handles memory management fault */
void MemManage_Handler(void);

/*! \brief Function for handles prefetch fault, memory access fault */
void BusFault_Handler(void);

/*! \brief Function for handles undefined instruction or illegal state */
void UsageFault_Handler(void);

/*! \brief Function for handles system service call via SWI instruction */
void SVC_Handler(void);

/*! \brief Function for handles debug monitor */
void DebugMon_Handler(void);

/*! \brief Function for handles pendable request for system service */
void PendSV_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_INTERRUPTS_H_ */
