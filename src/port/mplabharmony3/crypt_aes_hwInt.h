/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypto_sha1_hw.h

  Summary:
    Crypto Framework Libarary interface file for hardware AES

  Description:
    This file contains the interface that is required to be implemented by
    the AES hardware driver..
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

#ifndef _CRYPTO_AES_HW_INT_H_
#define _CRYPTO_AES_HW_INT_H_

#include "configuration.h"
#include "wolfssl/wolfcrypt/aes.h"

#ifdef __cplusplus
extern "C" {
#endif

int CRYPT_AES_SetKey(Aes* aes, const byte* userKey, word32 keylen, const byte* iv, int dir);
int CRYPT_AES_CbcEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
int CRYPT_AES_CbcDecrypt(Aes* aes, byte* out, const byte* in, word32 sz);
int CRYPT_AES_CtrEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);

void CRYPT_AES_Free(Aes* aes);
int  CRYPT_AES_Init(Aes* aes, void* heap, int devId);

#if defined(HAVE_AESGCM)
 int CRYPT_AES_GcmEncrypt(Aes* aes, unsigned char* out,
                                   const unsigned char* in, unsigned int sz,
                                   const unsigned char* iv, unsigned int ivSz,
                                   unsigned char* authTag, unsigned int authTagSz,
                                   const unsigned char* authIn, unsigned int authInSz);
 int CRYPT_AES_GcmDecrypt(Aes* aes, unsigned char* out,
                                   const unsigned char* in, unsigned int sz,
                                   const unsigned char* iv, unsigned int ivSz,
                                   const unsigned char* authTag, unsigned int authTagSz,
                                   const unsigned char* authIn, unsigned int authInSz);

#endif

#ifdef __cplusplus
}
#endif


#endif
