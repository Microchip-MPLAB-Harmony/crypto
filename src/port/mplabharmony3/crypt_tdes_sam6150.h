/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_tdes_sam6150.h

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

#ifndef CRYPT_TDES_SAM6150_H_
#define CRYPT_TDES_SAM6150_H_


/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "configuration.h"
#include <stdint.h>

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_TDES_HW_6150)

typedef union {
  struct {
    uint8_t START : 1;
    uint8_t :7;
    uint8_t SWRST : 1;
    uint8_t : 7;
    uint16_t : 16;
  } s;
  uint32_t v;  
} CRYPTO_TDES_SAM6150_CR;

typedef enum {
  CRYPTO_TDES_SAM6150_SINGLE_DES = 0,
  CRYPTO_TDES_SAM6150_TRIPLE_DES = 1,
  CRYPTO_TDES_SAM6150_XTEA = 2,
} CRYPTO_TDES_SAM6150_DesModes;

typedef enum {
  CRYPTO_TDES_SAM6150_MANUAL_START = 0,
  CRYPTO_TDES_SAM6150_AUTO_START = 1,
  CRYPTO_TDES_SAM6150_IDATAR0_START = 2,
} CRYPTO_TDES_SAM6150_StartModes;

typedef enum {
  CRYPTO_TDES_SAM6150_ECB = 0,
  CRYPTO_TDES_SAM6150_CBC = 1,
  CRYPTO_TDES_SAM6150_OFB = 2,
  CRYPTO_TDES_SAM6150_CFB = 3,
} CRYPTO_TDES_SAM6150_OpModes;

typedef enum {
  CRYPTO_TDES_SAM6150_SIZE_64BIT = 0,
  CRYPTO_TDES_SAM6150_SIZE_32BIT = 1,
  CRYPTO_TDES_SAM6150_SIZE_16BIT = 2,
  CRYPTO_TDES_SAM6150_SIZE_8BIT = 3
} CRYPTO_TDES_SAM6150_CFBSes;
    
typedef union {
  struct {
    uint8_t CIPHER : 1;
    CRYPTO_TDES_SAM6150_DesModes TDESMOD : 2;
    uint8_t :1;
    uint8_t KEYMOD : 1;
    uint8_t : 3;
    CRYPTO_TDES_SAM6150_StartModes SMOD : 2;
    uint8_t : 2;
    CRYPTO_TDES_SAM6150_OpModes OPMOD : 2;
    uint8_t : 1;
    uint8_t LOD : 1;
    CRYPTO_TDES_SAM6150_CFBSes CFBS : 2;
    uint8_t : 6;
    uint8_t : 8;
  } s;
  uint32_t v;
} CRYPTO_TDES_SAM6150_MR;
  
typedef union {
  struct {
    uint8_t DATRDY : 1;
    uint8_t : 7;
    uint8_t URAD : 1;
    uint8_t : 7;
    uint16_t : 16;
  } s;
  uint32_t v;
} CRYPTO_TDES_SAM6150_IER;

#define CRYPTO_TDES_SAM6150_IDR CRYPTO_TDES_SAM6150_IER
#define CRYPTO_TDES_SAM6150_IMR CRYPTO_TDES_SAM6150_IER
#define CRYPTO_TDES_SAM6150_ISR CRYPTO_TDES_SAM6150_IER

typedef union {
  struct {
    uint8_t XTEA_RNDS : 6;
    uint8_t : 2;
    uint32_t : 24;
  } s;
  uint32_t v;
} CRYPTO_TDES_SAM6150_XTEA_RNDR;

#endif

#endif /* CRYPT_TDES_SAM6150_H_ */
