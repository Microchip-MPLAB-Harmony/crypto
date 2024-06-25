/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    drv_crypto_ecdh_hw_cpkcl.c
  
  Summary:
    Crypto Framework Library source for the CPKCC ECDH functions.

  Description:
    This source contains the function code for the CPKCC ECDH.
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
#include "drv_crypto_ecdh_hw_cpkcl.h"
#include "CryptoLib_CPKCL/CryptoLib_typedef_pb.h"
#include "CryptoLib_CPKCL/CryptoLib_mapping_pb.h"
#include "CryptoLib_CPKCL/CryptoLib_Headers_pb.h"
#include "CryptoLib_CPKCL/CryptoLib_JumpTable_Addr_pb.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

// All buffers maximum size
static u1 sharedKeyX[P521_PUBLIC_KEY_COORDINATE_SIZE];    
static u1 sharedKeyY[P521_PUBLIC_KEY_COORDINATE_SIZE];     

// All buffers maximum size + 4
static u1 pubKeyX[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];  
static u1 pubKeyY[P521_PUBLIC_KEY_COORDINATE_SIZE + 4]; 
static u1 privateKey[P521_PUBLIC_KEY_COORDINATE_SIZE + 4];

// *****************************************************************************
// *****************************************************************************
// Section: CPKCL ECDH Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

CRYPTO_ECDH_RESULT DRV_CRYPTO_ECDH_InitEccParams(CPKCL_ECC_DATA *pEccData, 
    pfu1 privKey, u4 privKeyLen, pfu1 pubKey, CRYPTO_CPKCL_CURVE eccCurveType)
{
    CRYPTO_CPKCL_RESULT result;
    
    /* Initialize CPKCL */
    result = DRV_CRYPTO_ECC_InitCpkcl();
    if (result != CRYPTO_CPKCL_RESULT_INIT_SUCCESS) 
    {
        return CRYPTO_ECDH_RESULT_INIT_FAIL;
    }
    
    /* Fill curve parameters */
    result = DRV_CRYPTO_ECC_InitCurveParams(pEccData, eccCurveType);
    if (result != CRYPTO_CPKCL_RESULT_CURVE_SUCCESS) 
    {
        return CRYPTO_ECDH_RESULT_ERROR_CURVE;
    }
    
    /* Get coordinates of public key */
    memset(pubKeyX, 0, sizeof(pubKeyX));
    memset(pubKeyY, 0, sizeof(pubKeyY));
    result = DRV_CRYPTO_ECC_SetPubKeyCoordinates(pEccData, pubKey, &pubKeyX[4], 
                                                 &pubKeyY[4], eccCurveType);
    if (result == CRYPTO_CPKCL_RESULT_CURVE_ERROR)
    {
        return CRYPTO_ECDH_RESULT_ERROR_CURVE;
    }
    else if (result == CRYPTO_CPKCL_RESULT_COORDINATES_COMPRESS_ERROR) 
    {
        return CRYPTO_ECDH_ERROR_PUBKEYCOMPRESS;
    }
    
    pEccData->pfu1PublicKeyX = (pfu1) pubKeyX;
    pEccData->pfu1PublicKeyY = (pfu1) pubKeyY;
    
    /* Store private key locally, leaving first 4 bytes empty  */
    memset(privateKey, 0, sizeof(privateKey));
    memcpy(&privateKey[4], privKey, privKeyLen);
    pEccData->pfu1PrivateKey = (pfu1) privateKey;
    
    return CRYPTO_ECDH_RESULT_SUCCESS;
}

CRYPTO_ECDH_RESULT DRV_CRYPTO_ECDH_GetSharedKey(CPKCL_ECC_DATA *pEccData, 
    pfu1 sharedKey)
{
    /* Set sizes */
    u2 u2ModuloPSize = pEccData->u2ModuloPSize;
    u2 u2OrderSize = pEccData->u2OrderSize;

    /* Copy parameters for ECDH in memory areas */
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_MODULO(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1ModuloP, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_CNS(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1Cns, u2ModuloPSize + 8);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_SCALAR(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1PrivateKey, u2OrderSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_POINT_A_X(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1PublicKeyX, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_POINT_A_Y(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1PublicKeyY, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_POINT_A_Z(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1PublicKeyZ, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_A(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1ACurve, u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(
        (pu1) ((BASE_SCA_MUL_ORDER(u2ModuloPSize, u2OrderSize))), 
        pEccData->pfu1APointOrder, u2OrderSize + 4);

    /* Ask for a key generation */
    CPKCL_ZpEccMul(nu1ModBase) = (nu1) BASE_SCA_MUL_MODULO(u2ModuloPSize, 
        u2OrderSize);
    CPKCL_ZpEccMul(nu1CnsBase) = (nu1) BASE_SCA_MUL_CNS(u2ModuloPSize, 
        u2OrderSize);
    CPKCL_ZpEccMul(nu1PointBase) = (nu1) BASE_SCA_MUL_POINT_A(u2ModuloPSize, 
        u2OrderSize);
    CPKCL_ZpEccMul(nu1ABase) = (nu1) BASE_SCA_MUL_A(u2ModuloPSize, 
        u2OrderSize);
    CPKCL_ZpEccMul(nu1Workspace) = (nu1) BASE_SCA_MUL_WORKSPACE(u2ModuloPSize, 
        u2OrderSize);
    CPKCL_ZpEccMul(nu1KBase) = (nu1) BASE_SCA_MUL_SCALAR(u2ModuloPSize, 
        u2OrderSize);
    CPKCL_ZpEccMul(u2ModLength) = u2ModuloPSize;
    CPKCL_ZpEccMul(u2KLength) = u2ModuloPSize;
	
    /* Launch the key generation */
    /* See CPKCL_Rc_pb.h for possible u2Status Values */
    vCPKCL_Process(ZpEccMulFast, pvCPKCLParam);
    if (CPKCL(u2Status) != CPKCL_OK)
    {
	return CRYPTO_ECDH_RESULT_ERROR_FAIL;
    }
	
    /* Ask to convert coordinates */
    CPKCL_ZpEcConvProjToAffine(nu1ModBase) = (nu1) BASE_ECDSAV_MODULO(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcConvProjToAffine(nu1CnsBase) = (nu1) BASE_SCA_MUL_CNS(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcConvProjToAffine(nu1PointABase) = (nu1) BASE_SCA_MUL_POINT_A(
        u2ModuloPSize, u2OrderSize);
    CPKCL_ZpEcConvProjToAffine(u2ModLength) = u2ModuloPSize;
    CPKCL_ZpEcConvProjToAffine(nu1Workspace) = (nu1) BASE_SCA_MUL_WORKSPACE(
        u2ModuloPSize, u2OrderSize);
	
    /* Launch the coordinates conversion */
    /* See CPKCL_Rc_pb.h for possible u2Status Values */
    vCPKCL_Process(ZpEcConvProjToAffine, pvCPKCLParam);
    if (CPKCL(u2Status) != CPKCL_OK)
    {
	return CRYPTO_ECDH_RESULT_ERROR_FAIL;
    }
	
    /* Copy the result */
    DRV_CRYPTO_ECC_SecureCopy(sharedKeyX,
        (pu1) ((BASE_SCA_MUL_POINT_A(u2ModuloPSize, u2OrderSize))),
                u2ModuloPSize + 4);
    DRV_CRYPTO_ECC_SecureCopy(sharedKeyY,
        (pu1) ((BASE_SCA_MUL_POINT_A(u2ModuloPSize, u2OrderSize))) 
                + u2ModuloPSize + 4, u2ModuloPSize + 4);   

    /* Remove empty first four bytes */  
    memcpy(sharedKey, &sharedKeyX[4], u2OrderSize);
    
    return CRYPTO_ECDH_RESULT_SUCCESS;
}
