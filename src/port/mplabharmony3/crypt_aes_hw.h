/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypto_sha1_hw.h

  Summary:
    Crypto Framework Libarary interface file for hardware RNG

  Description:
    This file contains the interface that is required to be implemented by
    the RNG hardware driver..
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2013-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
*/

//DOM-IGNORE-END

#ifndef _CRYPTO_AES_HW_H_
#define _CRYPTO_AES_HW_H_

#include "configuration.h"
#include "wolfssl/wolfcrypt/aes.h"

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149)
#include "crypt_aes_sam6149.h"
#endif

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238)
#include "crypt_aes_u2238.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef struct 
{
#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149)
    CRYPT_AES_SAM6149_AES_MR aesMr;
    //uint8_t aesKey[32];
    //uint8_t aesIv[16];
    //uint32_t aesAddlenr;
    //uint8_t aesGHash[16];
    //uint32_t aesCtr;
    //uint8_t aesGcmH[16];
#elif defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238)
    //uint8_t aesKey[32];
    //uint8_t aesIv[16];
    //uint8_t aesGHash[16];
    //uint32_t aesAadlen;
    //uint32_t aesCtr;
    CRYPT_AES_U2238_AES_CTRLA ctrla;
    CRYPT_AES_U2238_AES_CTRLB ctrlb;
#elif defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2803) // SAML11
    /* nothing to define -- use the default Aes structure */
#elif defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2805) // PIC32CM
    /* nothing to define -- use the default Aes structure */
#endif
}crypt_aes_hw_descriptor;


#ifdef __cplusplus
}
#endif


#endif
