/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_wolfcryptcb.c

  Summary:
    Crypto Framework Libarary source file for the wolfcrypt callback

  Description:
    This file contains the wolfssl callback for public key cryptography
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

#include "configuration.h"
#include "wolfssl/wolfcrypt/port/pic32/crypt_wolfcryptcb.h"
#include "wolfssl/wolfcrypt/cryptocb.h"
#include "wolfssl/wolfcrypt/error-crypt.h"
#include "wolfssl/wolfcrypt/port/pic32/crypt_rsa_pukcl.h"
#include "wolfssl/wolfcrypt/port/pic32/crypt_ecc_pukcl.h"


int CRYPT_WCCB_Callback(int devId, wc_CryptoInfo* info, void* ctx)
{
    if (info->algo_type == WC_ALGO_TYPE_PK)
    {
#if defined(WOLFSSL_HAVE_MCHP_HW_RSA)
        if (info->pk.type == WC_PK_TYPE_RSA)
        {
            return Crypt_RSA_HandleReq(devId, info, ctx);
        }
#endif
#if defined(WOLFSSL_HAVE_MCHP_HW_ECC)
        if ((info->pk.type == WC_PK_TYPE_ECDSA_SIGN) ||
            (info->pk.type == WC_PK_TYPE_ECDSA_VERIFY))
        {
            return Crypt_ECC_HandleReq(devId, info, ctx);
        }
#endif
    }    
    return CRYPTOCB_UNAVAILABLE;
}

void CRYPT_WCCB_Initialize()
{
    wc_CryptoCb_RegisterDevice(0, CRYPT_WCCB_Callback, NULL);
}