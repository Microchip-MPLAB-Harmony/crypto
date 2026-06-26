/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_aes_sam6149.h

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

#ifndef _CRYPTO_AES_SAM6149_H_
#define _CRYPTO_AES_SAM6149_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "wolfssl/wolfcrypt/aes.h"

typedef union {
    struct {
        uint8_t START : 1;
        uint8_t : 7;
        uint8_t SWRST : 1;
        uint32_t : 23;
    }s;
    uint32_t v;
}CRYPT_AES_SAM6149_AES_CR;

typedef enum  {
    CRYPT_AES_SAM6149_DECRYPTION = 0, /**< Decryption of data will be performed. */
    CRYPT_AES_SAM6149_ENCRYPTION,     /**< Encryption of data will be performed. */
}crypt_aes_sam6149_ciphers;

typedef enum  {
    CRYPT_AES_SAM6149_AES128,
    CRYPT_AES_SAM6149_AES192,
    CRYPT_AES_SAM6149_AES256,    
}crypt_aes_sam6149_keySizes;

typedef enum crypt_aes_sam6149_startModes {
    CRYPT_AES_SAM6149_MANUAL_START,
    CRYPT_AES_SAM6149_AUTO_START,
    CRYPT_AES_SAM6149_IDATAR0_START
}crypt_aes_sam6149_startModes;

typedef enum crypt_aes_sam6149_opModes {
    CRYPT_AES_SAM6149_ECB = 0,       /**< Electronic Codebook (ECB). */
    CRYPT_AES_SAM6149_CBC,           /**< Cipher Block Chaining (CBC). */
    CRYPT_AES_SAM6149_OFB,           /**< Output Feedback (OFB). */
    CRYPT_AES_SAM6149_CFB,           /**< Cipher Feedback (CFB). */
    CRYPT_AES_SAM6149_CTR,           /**< Counter (CTR). */
    CRYPT_AES_SAM6149_GCM,           /**< Galois Counter Mode (GCM).*/
}crypt_aes_sam6149_opModes;

typedef enum  {
    CRYPT_AES_SAM6149_SIZE_128BIT = 0,   /**< Cipher feedback data size is 128-bit. */
    CRYPT_AES_SAM6149_SIZE_64BIT,        /**< Cipher feedback data size is 64-bit. */
    CRYPT_AES_SAM6149_SIZE_32BIT,        /**< Cipher feedback data size is 32-bit. */
    CRYPT_AES_SAM6149_SIZE_16BIT,        /**< Cipher feedback data size is 16-bit. */
    CRYPT_AES_SAM6149_SIZE_8BIT,         /**< Cipher feedback data size is 8-bit. */
}crypt_aes_sam6149_cfbSizes;

typedef union {
    struct {
        crypt_aes_sam6149_ciphers CIPHER : 1;
        uint8_t GTAGEN : 1;
        uint8_t : 1;
        uint8_t DUALBUFF : 1;
        crypt_aes_sam6149_keySizes PROCDLY : 4;
        crypt_aes_sam6149_startModes SMOD : 2;
        crypt_aes_sam6149_keySizes KEYSIZE : 2;
        crypt_aes_sam6149_opModes OPMODE : 3;
        uint8_t LOD : 1;
        crypt_aes_sam6149_cfbSizes CFBS : 3;
        uint8_t : 1;
        uint8_t CKEY : 4;
        uint8_t : 8;
    }s;
    uint32_t v;
}CRYPT_AES_SAM6149_AES_MR;

typedef union {
    struct {
        uint8_t DATRDY : 1;
        uint8_t : 7;
        uint8_t URAD : 1;
        uint8_t : 7;
        uint8_t TAGRDY : 1;
        uint16_t : 15;
    }s;
    uint32_t v;
} CRYPT_AES_SAM6149_AES_IER;

typedef CRYPT_AES_SAM6149_AES_IER CRYPT_AES_SAM6149_AES_IDR;
typedef CRYPT_AES_SAM6149_AES_IER CRYPT_AES_SAM6149_AES_IMR;

typedef enum 
{
    CRYPT_AES_SAM6149_IDR_WR_PROCESSING,
    CRYPT_AES_SAM6149_ODR_RD_PROCESSING,
    CRYPT_AES_SAM6149_MR_WR_PROCESSING,
    CRYPT_AES_SAM6149_ODR_RD_SUBKGEN,
    CRYPT_AES_SAM6149_MR_WR_SUBKGEN,
    CRYPT_AES_SAM6149_WOR_RD_ACCESS,
}crypt_aes_sam6149_URATs;

typedef union {    
    struct {
        uint8_t DATRDY : 1;
        uint8_t : 7;
        uint8_t URAD : 1;
        uint8_t : 3;
        crypt_aes_sam6149_URATs URAT : 4;
        uint8_t TAGRDY : 1;
        uint16_t : 15;
    }s;
    uint32_t v;
}CRYPT_AES_SAM6149_AES_ISR;




#ifdef __cplusplus
}
#endif





#endif
