/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    drv_crypto_ecdsa_hw_cpkcl.c
  
  Summary:
    Crypto Framework Library source for the CPKCC ECDSA functions.

  Description:
    This source contains the function code for the CPKCC ECDSA.
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

#include <string.h>
#include "drv_crypto_ecc_hw_cpkcl.h"
#include "drv_crypto_ecdsa_hw_cpkcl.h"
#include "CryptoLib_CPKCL/CryptoLib_typedef_pb.h"
#include "CryptoLib_CPKCL/CryptoLib_mapping_pb.h"
#include "CryptoLib_CPKCL/CryptoLib_Headers_pb.h"
#include "CryptoLib_CPKCL/CryptoLib_JumpTable_Addr_pb.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

// All buffers maximum size + 4
static u1 pubKeyX[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];    
static u1 pubKeyY[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];  
static u1 localHash[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];    
static u1 privateKey[P521_PUBLIC_KEY_COORDINATE_SIZE + 4]; 
static u1 signX[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];
static u1 signY[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];
    
// *****************************************************************************
// *****************************************************************************
// Section: CPKCL ECDSA Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_InitEccParamsSign(CPKCL_ECC_DATA *pEccData, 
    pfu1 hash, u4 hashLen, pfu1 privKey, u4 privKeyLen, 
    CRYPTO_CPKCL_CURVE eccCurveType)
{
    CRYPTO_CPKCL_RESULT result;
    
    /* Initialize CPKCL */
    result = DRV_CRYPTO_ECC_InitCpkcl();
    if (result != CRYPTO_CPKCL_RESULT_INIT_SUCCESS) 
    {
        return CRYPTO_ECDSA_RESULT_INIT_FAIL;
    }
    
    /* Fill curve parameters */
    result = DRV_CRYPTO_ECC_InitCurveParams(pEccData, eccCurveType);
    if (result != CRYPTO_CPKCL_RESULT_CURVE_SUCCESS) 
    {
        return CRYPTO_ECDSA_RESULT_ERROR_CURVE;
    }
    
    /* Clean out local buffers */
    memset(localHash, 0, sizeof(localHash));
    memset(privateKey, 0, sizeof(privateKey));
    
    /* Copy leaving first 4 bytes empty */
    memcpy(&localHash[4], hash, hashLen);
    memcpy(&privateKey[4], privKey, privKeyLen);
    
    /* Store in context */
    pEccData->pfu1HashValue = (pfu1) localHash;
    pEccData->pfu1PrivateKey = (pfu1) privateKey;
    
    return CRYPTO_ECDSA_RESULT_SUCCESS;
}

CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_Sign(CPKCL_ECC_DATA *pEccData, 
    pfu1 pfulSignature, u4 signatureLen)
{
     /* Clean out local buffers */
    memset(signX, 0, sizeof(signX));
    memset(signY, 0, sizeof(signY));
    
    /* Set sizes */
    u2 u2ModuloPSize = pEccData->u2ModuloPSize;
    u2 u2OrderSize = pEccData->u2OrderSize;
    
    /* Generate scalar number */
    CPKCL_Rng(nu1RBase) = (nu1) BASE_CONV_RANDOM(u2ModuloPSize);
    CPKCL_Rng(u2RLength) = u2OrderSize;
    CPKCL(u2Option) = CPKCL_RNG_GET;
    vCPKCL_Process(Rng, pvCPKCLParam);
    if (CPKCL(u2Status) != CPKCL_OK)
    {
	return CRYPTO_ECDSA_RESULT_ERROR_RNG;
    }
    
    u1 au1ScalarNumber[u2OrderSize];    
    DRV_CRYPTO_ECC_SecureCopy(au1ScalarNumber,
	(pu1) ((BASE_CONV_RANDOM(u2ModuloPSize))), u2OrderSize + 4);

    /* Copy parameters for ECDSA signature generation in memory areas */
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_MODULO(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1ModuloP, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_POINT_A_X(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointX, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_POINT_A_Y(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointY, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_POINT_A_Z(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointZ, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_A(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1ACurve, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_ORDER(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointOrder, u2OrderSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_PRIVATE_KEY(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1PrivateKey, u2OrderSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_HASH(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1HashValue, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSA_SCALAR(u2ModuloPSize, u2OrderSize))),
        (pfu1) au1ScalarNumber, u2OrderSize + 4);

    /* ECC signature */
    /* Ask for a signature generation */
    CPKCL_ZpEcDsaGenerate(nu1ModBase) = (nu1) BASE_ECDSA_MODULO(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1CnsBase) = (nu1) BASE_ECDSA_CNS(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1PointABase) = (nu1) BASE_ECDSA_POINT_A(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1PrivateKey) = (nu1) BASE_PRIVATE_KEY(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1ScalarNumber) = (nu1) BASE_ECDSA_SCALAR(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1OrderPointBase) = (nu1) BASE_ECDSA_ORDER(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1ABase) = (nu1) BASE_ECDSA_A(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1Workspace) = (nu1) BASE_ECDSA_WORKSPACE(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaGenerate(nu1HashBase) = (nu1) BASE_ECDSA_HASH(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaGenerate(u2ModLength) = u2ModuloPSize;
    CPKCL_ZpEcDsaGenerate(u2ScalarLength) = u2OrderSize;

    /* Launch the signature generation */
    /* See CPKCL_Rc_pb.h for possible u2Status Values */
    vCPKCL_Process(ZpEcDsaGenerateFast, pvCPKCLParam);
    if (CPKCL(u2Status) != CPKCL_OK)
    {
	return CRYPTO_ECDSA_RESULT_ERROR_FAIL;
    }

    /* Copy the result */
    DRV_CRYPTO_ECC_SecureCopy(signX,
        (pu1) ((BASE_ECDSA_POINT_A(u2ModuloPSize, u2OrderSize))),
                u2OrderSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(signY,
        (pu1) ((BASE_ECDSA_POINT_A(u2ModuloPSize, u2OrderSize)))
                + u2OrderSize + 4, u2OrderSize + 4);
    
    memcpy(pfulSignature, &signX[4], u2OrderSize);
    memcpy(&pfulSignature[u2OrderSize], &signY[4], u2OrderSize);
                    
    return CRYPTO_ECDSA_RESULT_SUCCESS;
}

 CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_InitEccParamsVerify(CPKCL_ECC_DATA *pEccData, 
    pfu1 hash, u4 hashLen, pfu1 pubKey, CRYPTO_CPKCL_CURVE eccCurveType)
{
    CRYPTO_CPKCL_RESULT result;
    
    /* Fill curve parameters */
    result = DRV_CRYPTO_ECC_InitCurveParams(pEccData, eccCurveType);
    if (result != CRYPTO_CPKCL_RESULT_CURVE_SUCCESS) 
    {
        return CRYPTO_ECDSA_RESULT_ERROR_CURVE;
    }
    
    /* Get coordinates of public key */
    memset(pubKeyX, 0, sizeof(pubKeyX));
    memset(pubKeyY, 0, sizeof(pubKeyY));
    result = DRV_CRYPTO_ECC_SetPubKeyCoordinates(pEccData, pubKey, &pubKeyX[4], 
                                                 &pubKeyY[4], eccCurveType);
    if (result == CRYPTO_CPKCL_RESULT_CURVE_ERROR)
    {
        return CRYPTO_ECDSA_RESULT_ERROR_CURVE;
    }
    else if (result == CRYPTO_CPKCL_RESULT_COORDINATES_COMPRESS_ERROR) 
    {
        return CRYPTO_ECDSA_ERROR_PUBKEYCOMPRESS;
    }
    
    pEccData->pfu1PublicKeyX = (pfu1) pubKeyX;
    pEccData->pfu1PublicKeyY = (pfu1) pubKeyY;
    
    /* Store hash locally */
    memset(localHash, 0, sizeof(localHash));
    memcpy(&localHash[4], hash, hashLen);
    pEccData->pfu1HashValue = (pfu1) localHash;
    
    return CRYPTO_ECDSA_RESULT_SUCCESS;
}
    
CRYPTO_ECDSA_RESULT DRV_CRYPTO_ECDSA_Verify(CPKCL_ECC_DATA *pEccData, 
    pfu1 pfu1Signature)
{
    pu1 pu1Tmp;
    
    /* Set sizes */
    u2 u2ModuloPSize = pEccData->u2ModuloPSize;	
    u2 u2OrderSize = pEccData->u2OrderSize;
    
    /* Clean out local buffers */
    memset(signX, 0, sizeof(signX));
    memset(signY, 0, sizeof(signY));
    
    /* Copy signature leaving first 4 bytes empty */
    memcpy(&signX[4], pfu1Signature, u2OrderSize);
    memcpy(&signY[4], &pfu1Signature[u2OrderSize], u2OrderSize);

    /* Copy the signature into appropriate memory area */
    /* Take care of the input signature format */
    pu1Tmp = (pu1) ((BASE_ECDSAV_SIGNATURE(u2ModuloPSize, u2OrderSize)));
    DRV_CRYPTO_ECC_SecureCopy(pu1Tmp, signX, u2OrderSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(pu1Tmp + u2OrderSize + 4, signY, u2OrderSize + 4);

    /* Copy parameters for ECDSA signature verification in memory areas */
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_MODULO(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1ModuloP, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_POINT_A_X(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointX, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_POINT_A_Y(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointY, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_POINT_A_Z(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointZ, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_A(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1ACurve, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_ORDER(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1APointOrder, u2OrderSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_PUBLIC_KEY_X(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1PublicKeyX, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_PUBLIC_KEY_Y(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1PublicKeyY, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_PUBLIC_KEY_Z(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1PublicKeyZ, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_ECDSAV_HASH(u2ModuloPSize, u2OrderSize))),
        pEccData->pfu1HashValue, u2ModuloPSize + 4);

    /* Ask for a verification generation */
    CPKCL_ZpEcDsaVerify(nu1ModBase) = (nu1) BASE_ECDSAV_MODULO(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1CnsBase) = (nu1) BASE_ECDSAV_CNS(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1PointABase) = (nu1) BASE_ECDSAV_POINT_A(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1PointPublicKeyGen) = (nu1) BASE_ECDSAV_PUBLIC_KEY(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1PointSignature) = (nu1) BASE_ECDSAV_SIGNATURE(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1OrderPointBase) = (nu1) BASE_ECDSAV_ORDER(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1ABase) = (nu1) BASE_ECDSAV_A(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1Workspace) = (nu1) BASE_ECDSAV_WORKSPACE(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcDsaVerify(nu1HashBase) = (nu1) BASE_ECDSAV_HASH(u2ModuloPSize,
        u2OrderSize);
    CPKCL_ZpEcDsaVerify(u2ModLength) = u2ModuloPSize;
    CPKCL_ZpEcDsaVerify(u2ScalarLength) = u2OrderSize;

    /* Verify the signature */
    vCPKCL_Process(ZpEcDsaVerifyFast, pvCPKCLParam);
    if (CPKCL(u2Status) != CPKCL_OK)
    {
	return CRYPTO_ECDSA_RESULT_ERROR_FAIL;
    }

    return CRYPTO_ECDSA_RESULT_SUCCESS;
}
