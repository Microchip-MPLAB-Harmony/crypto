/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    drv_crypto_ecdsa_hw_cpkcl.h
  
  Summary:
    Crypto Framework Library header for the CPKCC ECDSA functions.

  Description:
    This header contains the function definitions for the CPKCC ECDSA functions.
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

#ifndef _DRV_CRYPTO_ECDSA_HW_CPKCL_H_
#define _DRV_CRYPTO_ECDSA_HW_CPKCL_H_

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include "CryptoLib_CPKCL/CryptoLib_typedef_pb.h"

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
    CRYPTO_ECDSA_RESULT_SUCCESS, 
    CRYPTO_ECDSA_RESULT_INIT_FAIL,
    CRYPTO_ECDSA_ERROR_PUBKEYCOMPRESS,
    CRYPTO_ECDSA_RESULT_ERROR_CURVE, 
    CRYPTO_ECDSA_RESULT_ERROR_RNG,        
    CRYPTO_ECDSA_RESULT_ERROR_FAIL
} CRYPTO_ECDSA_RESULT;

// *****************************************************************************
// *****************************************************************************
// Section: CPKCC ECDSA Common Interface 
// *****************************************************************************
// *****************************************************************************

CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_InitEccParamsSign(CPKCL_ECC_DATA *pEccData, 
    pfu1 hash, u4 hashLen, pfu1 privKey, u4 privKeyLen, 
    CRYPTO_CPKCL_CURVE eccCurveType);

/* The signature is in MSB mode with the following order: */
/* 4 "0" bytes - S - 4 "0" bytes - R */
CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_Sign(CPKCL_ECC_DATA *pEccData, 
    pfu1 pfulSignature, u4 signatureLen);
                                          
CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_InitEccParamsVerify(CPKCL_ECC_DATA *pEccData, 
    pfu1 hash, u4 hashLen, pfu1 pubKey, CRYPTO_CPKCL_CURVE eccCurveType);

CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_Verify(CPKCL_ECC_DATA *pEccData, 
    pfu1 pfu1Signature);

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif /* _DRV_CRYPTO_ECDSA_HW_CPKCL_H_ */
