/* 
 * File:   cryptoST_aes_cbc.h
 * Author: C14102
 *
 * Created on November 6, 2019, 7:49 AM
 */

#ifndef CRYPTOST_AES_CBC_H
#define	CRYPTOST_AES_CBC_H

#ifdef	__cplusplus
extern "C" {
#endif

#if 0
#include <wolfssl/wolfcrypt/settings.h>
// #include <wolfssl/wolfssl/verion.h>
#ifdef USE_FLAT_TEST_H
    #include "test.h"
#else
   // #include "wolfssl/wolfcrypt/test/test.h"
#endif
#include <wolfssl/wolfcrypt/types.h>
#include <wolfssl/wolfcrypt/des3.h>
#include <wolfssl/wolfcrypt/aes.h>
#include <wolfssl/wolfcrypt/wc_encrypt.h>
#endif
    
#include "../test_data/cryptoSpeedTestData.h"

#if 1 //def WOLFSSL_AES_128
const char * cryptoSTE_aes_cbc_128_timed(cryptoST_testDetail_t * result,
                                   cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_aes_cbc_128_timed(t_,r_,i_) \
    PRINT("**** AES_CBC(128) is not available!" CRLF);
#endif // def WOLFSSL_AES_128

#if 1 //def WOLFSSL_AES_192
const char * cryptoSTE_aes_cbc_192_timed(cryptoST_testDetail_t * result,
                                   cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_aes_cbc_192_timed(t_,r_,i_) \
    PRINT("**** AES_CBC(192) is not available!" CRLF);
#endif // def WOLFSSL_AES_192

#if 1 //def WOLFSSL_AES_256
const char * cryptoSTE_aes_cbc_256_timed(cryptoST_testDetail_t * result,
                                   cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_aes_cbc_256_timed(t_,r_,i_) \
    PRINT("**** AES_CBC(256) is not available!" CRLF);
#endif // def WOLFSSL_AES_256


#ifdef	__cplusplus
}
#endif
#endif // ndef CRYPTOST_AES_CBC_H
