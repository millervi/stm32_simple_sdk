/*!
    \file main.c
    \author Miller Vitaliy millervimail@gmail.com
    \date 2022-01-17
*/

#include "version.h"
#include "autoconf.h"
#include "bsp.h"
#include "logger.h"
#include "assert.h"
#include "lib_a.h"
#include "lib_b.h"
#include <stdbool.h>
#ifdef CONFIG_CXX_ON
    #include <string>
#endif // CONFIG_CXX_ON
/* ====================================================================== */

#ifdef CONFIG_CXX_ON
    using namespace std;
#endif // CONFIG_CXX_ON
/* ====================================================================== */

const char g_version[] =
#ifdef PROJECT_VERSION
    PROJECT_VERSION;
#else
    "<unknow version>";
#endif // PROJECT_VERSION
/* ====================================================================== */

#if defined(LOGGER_ON)
/*! \brief Local app tag, using for messages of log */
static const char* TAG = "APP";
#endif /* LOGGER_ON */
/* ====================================================================== */

extern uint8_t _binary_embed_file_a_hex_start;
extern uint8_t _binary_embed_file_a_hex_end;
extern uint32_t _binary_embed_file_a_hex_size;
/* ====================================================================== */

int main () {
    /* Set all log levels */
	for (int current_level = LOG_LEVEL_BEGIN; current_level <= LOG_LEVEL_END; current_level++) {
        set_log_level_state((log_level_t)current_level, true);
    }
    bsp_init();
    LOGGER(LOG_LEVEL_I, TAG, "Application start, version - %s", g_version);
    LOGGER(LOG_LEVEL_I, TAG, "Show float value - %f", 0.0123456);
    LOGGER(LOG_LEVEL_I, TAG, "Start address of embed file = %p", &_binary_embed_file_a_hex_start);
    LOGGER(LOG_LEVEL_I, TAG, "End address of embed file = %p", &_binary_embed_file_a_hex_end);
    LOGGER(LOG_LEVEL_I, TAG, "Size of embed file = %d", (int)&_binary_embed_file_a_hex_size);
    int size = (int)&_binary_embed_file_a_hex_size;
    for (int i = 0; i < size; i++) {
        LOGGER(LOG_LEVEL_I, TAG, "Embed file byte[%d], value = 0x%X", i, *((&_binary_embed_file_a_hex_start) + i));
    }
    LOGGER(LOG_LEVEL_I, TAG, "%s", get_string_from_static_lib_a());
    LOGGER(LOG_LEVEL_I, TAG, "%s", get_string_from_static_lib_b());
#ifdef CONFIG_CXX_ON
    string str("Hello C++!!!");
    LOGGER(LOG_LEVEL_I, TAG, "%s", str.c_str());
    auto y = [] (int first, int second)
    {
        return first + second;
    };
    LOGGER(LOG_LEVEL_I, TAG, "Lambda - %d", y(1, 2));
#endif // CONFIG_CXX_ON
    return 0;
}