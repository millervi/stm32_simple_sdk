/*!
    \file assert.h
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

/* Define to prevent recursive inclusion */
#ifndef _ASSERT_H_
#define _ASSERT_H_
/* ====================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Comment it out to exclude all asserts from the project */
#ifdef CONFIG_LOGGER_ON
	#define USE_FULL_ASSERT
#endif /* CONFIG_LOGGER_ON */
/* ====================================================================== */

#ifdef USE_FULL_ASSERT
/*!
	\brief The assert_param macro is used for function's parameters check
	\param expr: If expr is false, it calls assert_failed function
		   which reports the name of the source file and the source
		   line number of the call that failed
		   If expr is true, it returns no value
*/
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((const char *)__FILE__, __LINE__))
/* ====================================================================== */

/*!
	\brief Reports the name of the source file and the source line number
		   where the assert_param error has occurred.
	\param file: pointer to the source file name
	\param line: assert_param error line source number
*/
void assert_failed(const char *file, unsigned long int line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* _ASSERT_H_ */
