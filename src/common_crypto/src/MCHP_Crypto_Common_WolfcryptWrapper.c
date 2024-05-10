/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Common_WolfcryptWrapper.c

  Summary:
    This file contains the Common code for the Wolfcrypt Library application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
*******************************************************************************/

 
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "crypto/common_crypto/MCHP_Crypto_Common.h"
#include "crypto/common_crypto/MCHP_Crypto_Common_WolfcryptWrapper.h"
#include "configuration.h"

#ifdef CRYPTO_DIGISIGN_ALGO_EN
#include "crypto/common_crypto/MCHP_Crypto_DigSign_Config.h"
#endif /* CRYPTO_DIGISIGN_ALGO_EN */

#ifdef CRYPTO_KAS_ALGO_EN
#include "crypto/common_crypto/MCHP_Crypto_Kas_Config.h"
#endif /* CRYPTO_KAS_ALGO_EN */

#if (defined(CRYPTO_DIGISIGN_WC_ECDSA_EN) || defined(CRYPTO_KAS_WC_ECDH_EN))
#include "wolfssl/wolfcrypt/ecc.h"


static const int arr_EccCurveWcMap[CRYPTO_WC_ECC_TOTAL_CURVES][2] =  {
                                                                        {(int)CRYPTO_ECC_CURVE_INVALID, (int)ECC_CURVE_INVALID},
                                                                        {(int)CRYPTO_ECC_CURVE_SECP224R1, (int)ECC_SECP224R1}, 
                                                                        {(int)CRYPTO_ECC_CURVE_SECP256R1, (int)ECC_SECP256R1},
                                                                        {(int)CRYPTO_ECC_CURVE_SECP384R1, (int)ECC_SECP384R1},
                                                                        {(int)CRYPTO_ECC_CURVE_SECP521R1, (int)ECC_SECP521R1},
                                                                    };


int Crypto_Common_Wc_Ecc_GetWcCurveId(crypto_EccCurveType_E curveType_en)
{
    int wcCurveId = -1;
    
    for(int curve = 0; curve < CRYPTO_WC_ECC_TOTAL_CURVES; curve++)
    {
        if(curveType_en == (crypto_EccCurveType_E)arr_EccCurveWcMap[curve][0])
        {
            wcCurveId = arr_EccCurveWcMap[curve][1];
            break;
        }
    }
    
    return wcCurveId;
}
#endif /* CRYPTO_DIGISIGN_WC_ECDSA_EN || CRYPTO_KAS_WC_ECDH_EN */

#ifdef CRYPTO_DIGISIGN_WC_ECDSA_EN

//The size of the r and S values is equivalent to private key size.
//1. DER encoding overhead is of 6 bytes
//2. and one byte for the Signature Hash result. 
//3. If either the r or the S-value has the highest bit set then it needs extra padding of 1 byte.
//4. If the highest bits of both r and s values are set, then both need padding of one byte
//So Signature length is "6-bytes Der format Overhead + r-value + 1-byte r-value's padding(if required) + s-value + 1-byte s-value's padding (if required) + 1-byte signature hash)"
int Crypto_Common_Wc_Ecc_EncodeToDerSign(uint8_t *inputSign, uint16_t inputSignLen, uint8_t *outDerSign, uint16_t outSignLen)
{
    int retWcDerSign = -1;
    retWcDerSign = wc_ecc_rs_to_sig((const char*)inputSign, (const char*)(inputSign+(inputSignLen/2u)), (byte*)outDerSign, (word32*)&outSignLen);
    return retWcDerSign;
}

int Crypto_Common_Wc_Ecc_DecodeDerSign(uint8_t *inputDerSign, uint16_t inputSignDerLen, uint8_t *outSign, uint16_t outSignLen)
{
    int retWcDerSign = -1;
    word32 rLen = (word32)outSignLen/2;
    retWcDerSign = wc_ecc_sig_to_rs((const byte*)inputDerSign, (word32)inputSignDerLen, (byte*)outSign, (word32*)&rLen, (byte*)(outSign+rLen), (word32*)&rLen);
    return retWcDerSign;
}
#endif /* CRYPTO_DIGISIGN_WC_ECDSA_EN */