/* cryptoSTV_wolfSSL_AES_GCM

   This package transliterates test data from the wolfSSL test.c file,
   specifically the data for the AES tests.
*/

#ifndef CRYPTOSTV_WOLFSSL_AES_GCM
#define CRYPTOSTV_WOLFSSL_AES_GCM 1

#include "./cryptoSpeedTestData.h"

/*************************************************************
 * Obligatory entry points for executing a test
 *************************************************************/
extern cryptoST_testAPI_t const wolfSSL_aes_gcm;

#endif // CRYPTOSTV_WOLFSSL_AES_GCM
