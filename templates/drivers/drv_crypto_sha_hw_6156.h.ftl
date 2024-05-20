/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    drv_crypto_sha_hw_6156.h

  Summary:
    Crypto Framework Library interface file for hardware SHA.

  Description:
    This header file contains the interface that make up the SHA hardware 
    driver for the following families of Microchip microcontrollers:
    PIC32CXMTxx, SAMA5D2, SAM9X60.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2024, Microchip Technology Inc., and its subsidiaries. All rights reserved.

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

#ifndef _DRV_CRYPTO_SHA_HW_6156_H_
#define _DRV_CRYPTO_SHA_HW_6156_H_

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

typedef enum 
{
    CRYPTO_SHA_MANUAL_START  = 0,    /* Manual start mode */
    CRYPTO_SHA_AUTO_START    = 1,    /* Auto start mode */
    CRYPTO_SHA_IDATAR0_START = 2     /* SHA_IDATAR0 access only mode */
} CRYPTO_SHA_START_MODE;

typedef enum 
{
  CRYPTO_SHA_ALGORITHM_SHA1 = 0,             /* SHA1 algorithm processed */
  CRYPTO_SHA_ALGORITHM_SHA256 = 1,           /* SHA256 algorithm processed */
  CRYPTO_SHA_ALGORITHM_SHA384 = 2,           /* SHA384 algorithm processed */
  CRYPTO_SHA_ALGORITHM_SHA512 = 3,           /* SHA512 algorithm processed */
  CRYPTO_SHA_ALGORITHM_SHA224 = 4,           /* SHA224 algorithm processed */
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
  CRYPTO_SHA_ALGORITHM_SHA512_224 = 5,       /* SHA512/224 algorithm processed */
  CRYPTO_SHA_ALGORITHM_SHA512_256 = 6,       /* SHA512/256 algorithm processed */
</#if>
  CRYPTO_SHA_ALGORITHM_HMAC_SHA1 = 8,        /* HMAC algorithm with SHA1 Hash processed */
  CRYPTO_SHA_ALGORITHM_HMAC_SHA256 = 9,      /* HMAC algorithm with SHA256 Hash processed */
  CRYPTO_SHA_ALGORITHM_HMAC_SHA384 = 10,     /* HMAC algorithm with SHA384 Hash processed */
  CRYPTO_SHA_ALGORITHM_HMAC_SHA512 = 11,     /* HMAC algorithm with SHA512 Hash processed */
  CRYPTO_SHA_ALGORITHM_HMAC_SHA224 = 12,     /* HMAC algorithm with SHA224 Hash processed */
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
  CRYPTO_SHA_ALGORITHM_HMAC_SHA512_224 = 13, /* HMAC algorithm with SHA512/224 Hash processed */
  CRYPTO_SHA_ALGORITHM_HMAC_SHA512_256 = 14, /* HMAC algorithm with SHA512/256 Hash processed */
</#if>
} CRYPTO_SHA_ALGORITHM;

typedef enum {
	CRYPTO_SHA_NO_HASH_CHECK = 0,      /* No hash check */
	CRYPTO_SHA_HASH_CHECK_EHV,         /* Check hash with expected hash in value registers */
	CRYPTO_SHA_HASH_CHECK_MESSAGE,     /* Check hash with expected hash after message */
} CRYPTO_SHA_HASH_CHECK;

typedef enum {
	CRYPTO_SHA_BLOCK_SIZE_WORDS_16  = 16,   /* Block size in words for SHA1, SHA224 and SHA256 */
	CRYPTO_SHA_BLOCK_SIZE_WORDS_32  = 32,   /* Block size in words for SHA384, SHA512, SHA512/224 and SHA512/256 */
} CRYPTO_SHA_BLOCK_SIZE;

typedef enum {
	CRYPTO_SHA_DISGEST_SIZE_SHA1    = 5,  /* SHA1 hash size in words */
	CRYPTO_SHA_DIGEST_SIZE_SHA224   = 7,  /* SHA224 and SHA512/224 hash size in words */
	CRYPTO_SHA_DIGEST_SIZE_SHA256   = 8,  /* SHA256 and SHA512/256 hash size in words */
	CRYPTO_SHA_DIGEST_SIZE_SHA384   = 12, /* SHA384 hash size in words */
	CRYPTO_SHA_DIGEST_SIZE_SHA512   = 16, /* SHA512 hash size in words */
} CRYPTO_SHA_DIGEST_SIZE;

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
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    uint8_t : 8;
    uint8_t UNLOCK : 1;
    uint8_t : 7;    
<#else>
    uint16_t : 16;  
</#if>
  } s;
  uint32_t v;
} CRYPTO_SHA_CR;

typedef union
{
  struct {
    CRYPTO_SHA_START_MODE SMOD : 2;
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    uint8_t : 1;
    uint8_t AOE : 1;
<#else>
    uint8_t : 2;
</#if>
    uint8_t PROCDLY : 1;
    uint8_t UIHV : 1;
    uint8_t UIEHV : 1;
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    uint8_t BPE : 1;
<#else>
    uint8_t : 1;
</#if>
    CRYPTO_SHA_ALGORITHM ALGO : 4;
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    uint8_t : 3;
    uint8_t TMPLCK : 1;
<#else>
    uint8_t : 4;
</#if>
    uint8_t DUALBUFF: 1;
    uint8_t : 7;
    CRYPTO_SHA_HASH_CHECK CHECK : 2;
    uint8_t : 2;
    uint8_t CHKCNT : 4;
  } s;
  uint32_t v;  
} CRYPTO_SHA_MR;

typedef union
{
  struct {
    uint8_t DATRDY : 1;
<#if __PROCESSOR?matches("PIC32CX.*MT.*")>
    uint8_t ENDTX : 1;
    uint8_t TXBUFE : 1;
    uint8_t : 5;
<#else>
    uint8_t : 7;
</#if>
    uint8_t URAD : 1;
    uint8_t : 7;
    uint8_t CHECKF : 1;
    uint8_t : 7;
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    uint8_t SECE : 1;
    uint8_t : 7;
<#else>
    uint8_t : 8;
</#if>
  } s;
  uint32_t v;
} CRYPTO_SHA_IER;

#define CRYPTO_SHA_IDR CRYPTO_SHA_IER
#define CRYPTO_SHA_IMR CRYPTO_SHA_IER

typedef union
{
  struct {
    uint8_t DATRDY : 1;
<#if __PROCESSOR?matches("PIC32CX.*MT.*")>
    uint8_t ENDTX : 1;
    uint8_t TXBUFE : 1;
    uint8_t : 1;
<#else>
    uint8_t : 3;
</#if>
    uint8_t WRDY : 1;
    uint8_t : 3;
    uint8_t URAD : 1;
    uint8_t : 3;
    uint8_t URAT : 3;
    uint8_t : 1;
    uint8_t CHCKF : 1;
    uint8_t : 3;
    uint8_t CHKST : 4;
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    uint8_t SECE : 1;
    uint8_t : 7;
<#else>
    uint8_t : 8;
</#if>
  } s;
  uint32_t v;
} CRYPTO_SHA_ISR;
  
// *****************************************************************************
// *****************************************************************************
// Section: SHA Common Interface 
// *****************************************************************************
// *****************************************************************************

void DRV_CRYPTO_SHA_Init(CRYPTO_SHA_ALGORITHM shaAlgo);

void DRV_CRYPTO_SHA_Update(uint32_t *data, CRYPTO_SHA_BLOCK_SIZE dataBlockSize);

void DRV_CRYPTO_SHA_GetOutputData(uint32_t *digest, 
    CRYPTO_SHA_DIGEST_SIZE digestLen);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif /* _DRV_CRYPTO_SHA_6156_HW_H_ */
