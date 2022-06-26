/*!
    \file logger.c
    \author Miller Vitaliy millervimail@gmail.com
    \date 2021-01-17
*/

#include "logger.h"
/* ===================================================================== */

/*! \brief Local var for on / off log level information */
static bool level_i = false;
/*! \brief Local var for on / off log level warning */
static bool level_w = false;
/*! \brief Local var for on / off log level error */
static bool level_e = false;
/*! \brief Local var for on / off log level assert */
static bool level_a = false;
/* ====================================================================== */

void set_log_level_state(log_level_t level, bool state)
{
	if (level == LOG_LEVEL_I) { level_i = state; }
	if (level == LOG_LEVEL_W) { level_w = state; }
	if (level == LOG_LEVEL_E) { level_e = state; }
	if (level == LOG_LEVEL_A) { level_a = state; }
}
/* ====================================================================== */

bool get_log_level_state(log_level_t level)
{
	bool state = false;

	if (level == LOG_LEVEL_I) { state = level_i; }
	if (level == LOG_LEVEL_W) { state = level_w; }
	if (level == LOG_LEVEL_E) { state = level_e; }
	if (level == LOG_LEVEL_A) { state = level_a; }

	return state;
}
/* ====================================================================== */
