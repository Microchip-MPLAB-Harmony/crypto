/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypto_sha_hw.h

  Summary:
    Crypto Framework Libarary interface file for hardware RNG

  Description:
    This file contains the interface that is required to be implemented by
    the RNG hardware driver..
**************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2019 Microchip Technology Inc. and its subsidiaries.

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

#ifndef _CRYPT_SHA_HW_H_
#define _CRYPT_SHA_HW_H_

#include "configuration.h"
#ifdef NO_INLINE
    #include "crypto/src/misc.h"
#else
    #define WOLFSSL_MISC_INCLUDED
    #include "crypto/src/misc.c"
#endif

#if defined(CRYPTO_SHA_HW_11105)
#include "crypt_sha_sam11105.h"
#endif

#if defined(CRYPTO_SHA_HW_6156)
#include "crypt_sha_sam6156.h"
#endif

typedef struct 
{
#if defined(CRYPTO_SHA_HW_11105)
    struct icm_descriptor icm_descriptor;
    uint8_t  buffer[CRYPT_SHA256_BLOCK_BYTES];  /* 64 bytes = 512 bits */
    uint32_t digest[CRYPT_SHA256_DIGEST_BYTES/4];
    uint64_t total_len;   /* number of bytes to be processed  */
#endif
#if defined(CRYPTO_SHA_HW_6156)
    struct sha_descriptor sha_descriptor;
#endif
}crypt_sha_hw_descriptor;

int CRYPT_SHA1_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_SHA224_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_SHA256_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_SHA384_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_SHA512_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);

int CRYPT_HMAC_SHA1_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_HMAC_SHA224_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_HMAC_SHA256_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_HMAC_SHA384_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);
int CRYPT_HMAC_SHA512_InitSha(crypt_sha_hw_descriptor* sha, void* heap, int devId);

int CRYPT_SHA_Update(crypt_sha_hw_descriptor* sha, const byte* data, word32 len);
int CRYPT_SHA_Final(crypt_sha_hw_descriptor* sha, byte* hash);
void CRYPT_SHA_Free(crypt_sha_hw_descriptor* sha);
void crypt_InitSha(crypt_sha_hw_descriptor* sha);

#endif /* _CRYPT_SHA_HW_H_ */
