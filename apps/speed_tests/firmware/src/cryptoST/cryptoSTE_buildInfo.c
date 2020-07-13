/* 
 * File:   cryptoSTE_buildInfo.c
 * Author: C14102
 *
 * Make visible the compiler options.
 * This file should be gimmicked to build every time
 * (on the Building tab of the project properties):
 *    touch ../src/cryptoST/cryptotouch ../src/cryptoSTSTE_buildInfo.c
 * 
 * Also relies on a makefile parameter to the compiler command
 * line in Properties/XC32(GlobalOptions)/AdditionalOptions: 
 *     -D__PROCESSOR__=$(MP_PROCESSOR_OPTION)
 */

#include "cryptoSTE_buildInfo.h"
#include "cryptoSTE_print.h" // for STRINGIZE

/* public -- this is a singleton */
cryptoSTE_buildInfo_t cryptoSTE_buildInfo =
{
    .buildDate = __DATE__,
    .buildTime = __TIME__,
#if __OPTIMIZE__
    .optimized = "yes",
#else
    .optimized = "no",
#endif
    .processor = STRINGIZE(__PROCESSOR__),
};
