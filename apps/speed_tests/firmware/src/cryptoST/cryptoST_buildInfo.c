/* 
 * File:   cryptoST_buildInfo.c
 * Author: C14102
 *
 * Created on June 10, 2020, 11:34 AM
 * 
 * Make visible the compiler options.
 * This file should be gimmicked to build every time.
 *    touch ../src/cryptoST/cryptoST_buildInfo.c
 */

#include "cryptoST_buildInfo.h"
#include "cryptoST_print.h" // for STRINGIZE

/* public */
cryptoST_buildInfo_t cryptoST_buildInfo =
{
    .buildDate = __DATE__,
    .buildTime = __TIME__,
#if __OPTIMIZE__
    .optimized = "yes",
#else
    .optimized = "no",
#endif
    // Relies on makefile hack: // -D__PROCESSOR__=$(MP_PROCESSOR_OPTION)
    // added as a parameter to the compiler command line.
    .processor = STRINGIZE(__PROCESSOR__),
};
