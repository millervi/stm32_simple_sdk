/*!
    \file logger.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
    \brief Header file with descriptions

    This file contains the macro for logging
*/

/* Define to prevent recursive inclusion */
#ifndef _LOGGER_H_
#define _LOGGER_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include "autoconf.h"
/* ====================================================================== */

/*! \brief Comment it out to exclude all log messages from the project */
#ifdef CONFIG_LOGGER_ON
	#define LOGGER_ON
#endif /* CONFIG_LOGGER_ON */
/* ====================================================================== */

/*!
	\brief Typedef for log level
	\note Use LOG_LEVEL_BEGIN and LOG_LEVEL_END if neded range for cycle
*/
typedef enum {
	LOG_LEVEL_INVALID_BEGIN = 0, 	///< Default invalid level for exclude null initialization
	LOG_LEVEL_BEGIN = 1,			///< Begin element
	LOG_LEVEL_I = LOG_LEVEL_BEGIN, 	///< Information
	LOG_LEVEL_W, 					///< Warning
	LOG_LEVEL_E, 					///< Error
	LOG_LEVEL_A, 					///< Assert
	LOG_LEVEL_END = LOG_LEVEL_A 	///< End element
} log_level_t;
/* ====================================================================== */

/*!
	\brief Function for set level log state
	\param[in] level: see log_level_t
	\param[in] state: true - log on / false log off
*/
void set_log_level_state(log_level_t, bool);

/*!
	\brief Function for get level log state
	\param[in] level: see log_level_t
	\return State: true - log on / false log off
*/
bool get_log_level_state(log_level_t);

/*!
	\brief Definitions macros for show log message
	\param[in] level: see log_level_t
	\param[in] tag: tag module
	\param[in] args : "..." - arguments specifying data to print

	\code{.c}
	// Use for test logger next code:
	void test_logger(void)
	{
		set_log_level_state(LOG_LEVEL_I, true);
		set_log_level_state(LOG_LEVEL_W, true);
		set_log_level_state(LOG_LEVEL_E, true);
		set_log_level_state(LOG_LEVEL_A, true);

		for (int current_level = LOG_LEVEL_BEGIN; current_level <= LOG_LEVEL_END; current_level++)
			LOGGER(current_level, "LOGGER", "Message - %d", current_level);
	}
	\endcode
*/
#if defined(LOGGER_ON)
#define LOGGER(level, tag, ...) do { \
	bool logging_levels = ((level >= LOG_LEVEL_BEGIN) && (level <= LOG_LEVEL_END)); \
	if ((!logging_levels) || (!get_log_level_state(level))) break; \
	if (level == LOG_LEVEL_I) { printf("(I): "); } \
	if (level == LOG_LEVEL_W) { printf("(W): "); } \
	if (level == LOG_LEVEL_E) { printf("(E): "); } \
	if (level == LOG_LEVEL_A) { printf("(A): "); } \
	printf("%s - ", tag); printf(__VA_ARGS__); printf("\r\n"); \
} while(0)
#else
#define LOGGER(level, tag, ...) do { } while(0)
#endif /* LOGGER_ON */

#ifdef __cplusplus
}
#endif

#endif /* _LOGGER_H_ */
