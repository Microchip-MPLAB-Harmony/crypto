/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_DigSign_HwWrapper.c

  Summary:
    Crypto Framework Library wrapper file for the digital signature in the 
    hardware cryptographic library.

  Description:
    This source file contains the wrapper interface to access the hardware 
    cryptographic library in Microchip microcontrollers for digital signature.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include "crypto/common_crypto/MCHP_Crypto_DigSign_HwWrapper.h"
#include "crypto/driver/drv_crypto_ecc_hw_cpkcl.h"
#include "crypto/driver/drv_crypto_ecdsa_hw_cpkcl.h"

// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************

static crypto_DigiSign_Status_E lCrypto_DigSign_Ecdsa_Hw_GetCurve(
    crypto_EccCurveType_E eccCurveType, CRYPTO_CPKCL_CURVE *hwEccCurve)
{
    switch (eccCurveType)
    {
        case CRYPTO_ECC_CURVE_P256:
            *hwEccCurve = CRYPTO_CPKCL_CURVE_P256;
            break;
        
        case CRYPTO_ECC_CURVE_P384:
            *hwEccCurve = CRYPTO_CPKCL_CURVE_P384;
            break;
        
        default:
            return CRYPTO_DIGISIGN_ERROR_CURVE;
        
    }
    
    return CRYPTO_DIGISIGN_SUCCESS;
}    

static crypto_DigiSign_Status_E lCrypto_DigSign_Ecdsa_Hw_MapResult(
    CRYPTO_ECDSA_RESULT result)
{
    switch (result) 
    {
        case CRYPTO_ECDSA_RESULT_SUCCESS:
            return CRYPTO_DIGISIGN_SUCCESS;
            
        case CRYPTO_ECDSA_ERROR_PUBKEYCOMPRESS:
            return CRYPTO_DIGISIGN_ERROR_PUBKEYCOMPRESS;
            
        case CRYPTO_ECDSA_RESULT_ERROR_CURVE:
            return CRYPTO_DIGISIGN_ERROR_CURVE;
            
        case CRYPTO_ECDSA_RESULT_ERROR_RNG:   
            return CRYPTO_DIGISIGN_ERROR_RNG;
        
        case CRYPTO_ECDSA_RESULT_ERROR_FAIL:
            return CRYPTO_DIGISIGN_ERROR_FAIL;
            
        default:
            ;
    }
    
    return CRYPTO_DIGISIGN_ERROR_FAIL;
}

// *****************************************************************************
// *****************************************************************************
// Section: DigSign Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

crypto_DigiSign_Status_E Crypto_DigiSign_Ecdsa_Hw_Sign(uint8_t *inputHash, 
    uint32_t hashLen, uint8_t *outSig, uint32_t sigLen, uint8_t *privKey, 
    uint32_t privKeyLen, crypto_EccCurveType_E eccCurveType_En)
{
    crypto_DigiSign_Status_E result;
    CRYPTO_ECDSA_RESULT hwResult;
    CPKCL_ECC_DATA eccData;
    CRYPTO_CPKCL_CURVE hwEccCurve;
    
    /* Get curve */
    result = lCrypto_DigSign_Ecdsa_Hw_GetCurve(eccCurveType_En, &hwEccCurve);
    if (result != CRYPTO_DIGISIGN_SUCCESS)
    {
        return result;
    }
    
    /* Initialize the hardware library for ECDSA signature generation */
    hwResult = DRV_CRYPTO_ECDSA_InitEccParamsSign(&eccData, (pfu1)inputHash, 
                                                  (pfu1)privKey, hwEccCurve);
    if (hwResult != CRYPTO_ECDSA_RESULT_SUCCESS) 
    {
        return lCrypto_DigSign_Ecdsa_Hw_MapResult(hwResult);
        
    }
    
    /* Sign the message */
    hwResult = DRV_CRYPTO_ECDSA_Sign(&eccData, (pfu1)outSig);

    return lCrypto_DigSign_Ecdsa_Hw_MapResult(hwResult);
}

crypto_DigiSign_Status_E Crypto_DigiSign_Ecdsa_Hw_Verify(uint8_t *inputHash, 
    uint32_t hashLen, uint8_t *inputSig, uint32_t sigLen, uint8_t *pubKey, 
    uint32_t pubKeyLen, int8_t *hashVerifyStatus, 
    crypto_EccCurveType_E eccCurveType_En)
{
    crypto_DigiSign_Status_E result;
    CRYPTO_ECDSA_RESULT hwResult;
    CPKCL_ECC_DATA eccData;
    CRYPTO_CPKCL_CURVE hwEccCurve;
    
    /* Get curve */
    result = lCrypto_DigSign_Ecdsa_Hw_GetCurve(eccCurveType_En, &hwEccCurve);
    if (result != CRYPTO_DIGISIGN_SUCCESS)
    {
        return result;
    }
    
    /* Initialize the hardware library for ECDSA signature verification */
    hwResult = DRV_CRYPTO_ECDSA_InitEccParamsVerify(&eccData, (pfu1)inputHash, 
                                                    (pfu1)pubKey, hwEccCurve);
    
    /* Verify the signature */
    hwResult = DRV_CRYPTO_ECDSA_Verify(&eccData, (pfu1)inputSig);
    
    /* Set verification status */
    if (hwResult == CRYPTO_ECDSA_RESULT_SUCCESS) 
    {
        *hashVerifyStatus = 1;
    }
    else 
    {
        *hashVerifyStatus = 0;
    }

    return lCrypto_DigSign_Ecdsa_Hw_MapResult(hwResult);
}
