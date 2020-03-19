/* cryptoSTV_zero_aes

   This package provides NULL data sets of various lengths to
   demonstrate basic operation of AES. In particular, to expose
   the differences between counter modes by revealing the
   progression of the IV and KEY turns.
*/

#ifndef CRYPTOSTV_ZERO_AES
#define CRYPTOSTV_ZERO_AES 1

#include "./cryptoSpeedTestData.h"

/*************************************************************
 * Obligatory entry points for executing a test
 *************************************************************/
extern cryptoST_testAPI_t const microchip_zero_aes;

#endif // CRYPTOSTV_ZERO_AES
