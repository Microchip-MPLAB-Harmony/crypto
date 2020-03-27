/* 
 * File:   cryptoST_aes_cbc.h
 * Author: C14102
 *
 * Created on November 6, 2019, 7:49 AM
 */

#ifndef CRYPTOST_AES_EBC_H
#define	CRYPTOST_AES_EBC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../test_data/cryptoSpeedTestData.h"

extern const char * cryptoSTE_aes_ecb_timed(const cryptoST_testDetail_t * result,cryptoSTE_testExecution_t * param);

#if 0
#if 1 //def WOLFSSL_AES_128
const char * cryptoSTE_aes_ebc_128_timed(const cryptoST_testDetail_t * result,
                                   cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_aes_ebc_128_timed(t_,r_,i_) \
    PRINT("**** AES_EBC(128) is not available!" CRLF);
#endif // def WOLFSSL_AES_128

#if 1 //def WOLFSSL_AES_192
const char * cryptoSTE_aes_dbc_192_timed(const cryptoST_testDetail_t * result,
                                   cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_aes_ebc_192_timed(t_,r_,i_) \
    PRINT("**** AES_EBC(192) is not available!" CRLF);
#endif // def WOLFSSL_AES_192

#if 1 //def WOLFSSL_AES_256
const char * cryptoSTE_aes_ebc_256_timed(const cryptoST_testDetail_t * result,
                                   cryptoSTE_testExecution_t * param);
#else
#define cryptoSTE_aes_ebc_256_timed(t_,r_,i_) \
    PRINT("**** AES_EBC(256) is not available!" CRLF);
#endif // def WOLFSSL_AES_256
#endif 

#ifdef	__cplusplus
}
#endif
#endif // ndef CRYPTOST_AES_EBC_H
