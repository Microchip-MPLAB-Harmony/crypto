/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypto_sha256_hw.h

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

#ifndef _CRYPTO_SHA256_HW_H_
#define _CRYPTO_SHA256_HW_H_


#include "configuration.h"


#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105)
#include "crypt_sha_sam11105.h"
#elif defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156)
#include "crypt_sha_sam6156.h"
#endif

struct wc_Sha256 
{
    int devId;
    word32 flags; /* enum wc_HashFlags in hash.h */

#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105)
    struct icm_descriptor icm_descriptor;
    uint8_t  buffer[SHA256_BLOCK_SIZE];  /* 64 bytes = 512 bits */
    uint32_t digest[SHA256_DIGEST_SIZE/4];
    uint64_t total_len;   /* number of bytes to be processed  */
#elif defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156)
    CRYPT_SHA_SAM6156_shaDescriptor sha_descriptor;
    uint8_t  buffer[SHA256_BLOCK_SIZE];
    uint32_t digest[SHA256_DIGEST_SIZE/4];
    uint64_t total_len;   /* number of bytes to be processed  */
#elif defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2803) /* SAML11  */  \
   || defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2805) /* PIC32CM */
    uint8_t  buffer[SHA256_BLOCK_SIZE];
    uint32_t digest[SHA256_DIGEST_SIZE/sizeof(uint32_t)];
    size_t   bufferLength; /* number of bytes currently in the buffer */
    uint64_t totalLength;  /* cumulative number of bytes processed  */
#endif
};
#ifndef WC_SHA256_TYPE_DEFINED
    typedef struct wc_Sha256 wc_Sha256;
    #define WC_SHA256_TYPE_DEFINED
#endif

#endif
