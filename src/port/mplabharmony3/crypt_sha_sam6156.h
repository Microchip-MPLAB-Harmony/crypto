/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_sha_sam6156.h

  Summary:
    Crypto Framework Library header for cryptographic functions.

  Description:
    This header file contains function prototypes and definitions of
    the data types and constants that make up the Cryptographic Framework
    Library for SAMA5D2 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2019-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

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

#ifndef CRYPT_SHA_SAM6156_H_
#define CRYPT_SHA_SAM6156_H_

#include <stdint.h>

typedef union {
  struct {
    uint8_t START : 1;
    uint8_t : 3;
    uint8_t FIRST : 1;
    uint8_t : 3;
    uint8_t SWRST : 1;
    uint8_t : 3;
    uint8_t WUIHV : 1;
    uint8_t WUIEHV : 1;
    uint8_t : 2;
#if defined(CRYPTO_SHA_HW_6156_R)
    uint8_t : 8;
    uint8_t UNLOCK : 1;
    uint8_t : 7;    
#else
    uint16_t : 16;  
#endif
  } s;
  uint32_t v;
} CRYPT_SHA_SAM6156_SHA_CR;

typedef enum 
{
  SHA_HW_MANUAL_START = 0,
  SHA_HW_AUTO_START = 1,
  SHA_HW_IDATAR0_START = 2,
}CRYPT_SHA_SAM6156_StartModes;

typedef enum 
{
  SHA_HW_SHA1 = 0,
  SHA_HW_SHA256 = 1,
  SHA_HW_SHA384 = 2,
  SHA_HW_SHA512 = 3,
  SHA_HW_SHA224 = 4,
  SHA_HW_HMAC_SHA1 = 8,
  SHA_HW_HMAC_SHA256 = 9,
  SHA_HW_HMAC_SHA384 = 10,
  SHA_HW_HMAC_SHA512 = 11,
  SHA_HW_HMAC_SHA224 = 12,
}CRYPT_SHA_SAM6156_Alogithms;

typedef enum 
{
  SHA_HW_NO_CHECK = 0,
  SHA_HW_CHECK_EHV = 1,
  SHA_HW_CHECK_MESSAGE = 2,
}CRYPT_SHA_SAM6156_HashCheck;

typedef union
{
  struct {
    CRYPT_SHA_SAM6156_StartModes SMOD : 2;
#if defined(CRYPTO_SHA_HW_6156_R)
    uint8_t AOE : 1;
    uint8_t : 1;
#else
    uint8_t : 2;
#endif
    uint8_t PROCDLY : 1;
    uint8_t UIHV : 1;
    uint8_t UIEHV : 1;
#if defined(CRYPTO_SHA_HW_6156_R)
    uint8_t BPE : 1;
#else
    uint8_t : 1;
#endif
    CRYPT_SHA_SAM6156_Alogithms ALGO : 4;
#if defined(CRYPTO_SHA_HW_6156_R)
    uint8_t : 3;
    uint8_t TMPLCK : 1;
#else
    uint8_t : 4;
#endif
    uint8_t DUALBUFF: 1;
    uint8_t : 7;
    CRYPT_SHA_SAM6156_HashCheck CHECK : 2;
    uint8_t : 2;
    uint8_t CHKCNT : 4;
  } s;
  uint32_t v;  
}CRYPT_SHA_SAM6156_SHA_MR;

typedef union
{
  struct {
    uint8_t DATRDY : 1;
    uint8_t : 7;
    uint8_t URAD : 1;
    uint8_t : 7;
    uint8_t CHECKF : 1;
    uint8_t : 7;
#if defined(CRYPTO_SHA_HW_6156_R)
    uint8_t SECE : 1;
    uint8_t : 7;
#else
    uint8_t : 8;
#endif
  } s;
  uint32_t v;
} CRYPT_SHA_SAM6156_SHA_IER;

#define CRYPT_SHA_SAM6156_SHA_IDR CRYPT_SHA_SAM6156_SHA_IER
#define CRYPT_SHA_SAM6156_SHA_IMR CRYPT_SHA_SAM6156_SHA_IER

typedef union
{
  struct {
    uint8_t DATRDY : 1;
    uint8_t : 3;
    uint8_t WRDY : 1;
    uint8_t : 3;
    uint8_t URAD : 1;
    uint8_t : 3;
    uint8_t URAT : 3;
    uint8_t : 1;
    uint8_t CHCKF : 1;
    uint8_t : 3;
    uint8_t CHKST : 4;
#if defined(CRYPTO_SHA_HW_6156_R)
    uint8_t SECE : 1;
    uint8_t : 7;
#else
    uint8_t : 8;
#endif
  } s;
  uint32_t v;
} CRYPT_SHA_SAM6156_SHA_ISR;

  
typedef struct 
{
  CRYPT_SHA_SAM6156_Alogithms ALGO : 4;
} CRYPT_SHA_SAM6156_shaDescriptor;
  


#endif /* CRYPT_SHA_SAM6156_H_ */
