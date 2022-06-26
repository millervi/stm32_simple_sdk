/*!
    \file assert.с
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

#include "assert.h"
#include "logger.h"
#include <stdio.h>
/* ====================================================================== */

#ifdef USE_FULL_ASSERT
/*! \brief Local format string for show assert */
static const char* FORMAT = "Wrong parameters value: file %s on line %lu";
/* ====================================================================== */

void assert_failed(const char *file, unsigned long int line)
{
#if defined(LOGGER_ON)
	/*! \brief Local assert tag, using for messages of log */
	static const char* TAG = "ASSERT";
	/* ====================================================================== */

	LOGGER(LOG_LEVEL_A, TAG, FORMAT, file, line);
#else
	printf(FORMAT, file, line);
#endif /* LOGGER_ON */
	while (true) { /* Stop programm so as not to ignore the assertion */ }
}
#endif /* USE_FULL_ASSERT */
/* ====================================================================== */
