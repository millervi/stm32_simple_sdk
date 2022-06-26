/*!
    \file bsp.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

/* Define to prevent recursive inclusion */
#ifndef _BSP_H_
#define _BSP_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
/* ====================================================================== */

/*! \brief Function for init bsp */
void bsp_init(void);

/*! \brief Function for deinit bsp */
void bsp_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _BSP_H_ */
