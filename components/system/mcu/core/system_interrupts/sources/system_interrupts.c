/*!
    \file system_interrupts.c
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-21
*/

#include "system_interrupts.h"
#include <stdbool.h>
/* ====================================================================== */

void NMI_Handler(void) {
    while (true) {
        /* Do not let the program run further */
    }
}
/* ====================================================================== */

void HardFault_Handler(void) {
    while (true) {
        /* Do not let the program run further */
    }
}
/* ====================================================================== */

void MemManage_Handler(void) {
    while (true) {
        /* Do not let the program run further */
    }
}
/* ====================================================================== */

void BusFault_Handler(void) {
    while (true) {
        /* Do not let the program run further */
    }
}
/* ====================================================================== */

void UsageFault_Handler(void) {
    while (true) {
        /* Do not let the program run further */
    }
}
/* ====================================================================== */

void SVC_Handler(void) {
    /* Add an action if needed */
}
/* ====================================================================== */

void DebugMon_Handler(void) {
    /* Add an action if needed */
}
/* ====================================================================== */

void PendSV_Handler(void) {
    /* Add an action if needed */
}
/* ====================================================================== */
