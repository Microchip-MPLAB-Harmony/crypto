/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoST_aes_ecb.h

  Summary:
    AES ECB mode encryption driver

  Description:
    This file contains functions to measure the time required 
    to perform AES EBC encryption. Time is reported in clock ticks.

    Electronic Code Book (ECB) mode is notable because 
    an initialization vector (IV) is not required.
 
    The useLocalDriverEntryPoints option is supported
    and provides both WC and CRYA-direct interfaces. Note that if
    WC is configured with UseHardwareCryptography=TRUE, the
    WC interface will invoke the CRYA HW in all cases.
 ******************************************************************************
 */

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2020 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/

//DOM-IGNORE-END

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
