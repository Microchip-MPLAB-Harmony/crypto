/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Common_WolfcryptWrapper.h

  Summary:
    This header file provides Common Prototypes and definitions for the Wolfcrypt Library.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef MCHP_CRYPTO_COMMON_WOLFCRYPTWRAPPER_H
#define MCHP_CRYPTO_COMMON_WOLFCRYPTWRAPPER_H

#include "crypto/common_crypto/MCHP_Crypto_Common.h"

#define CRYPTO_WC_ECC_TOTAL_CURVES (5)

#if (defined(CRYPTO_DIGISIGN_WC_ECDSA_EN) || defined(CRYPTO_KAS_WC_ECDH_EN))
int Crypto_Common_Wc_Ecc_GetWcCurveId(crypto_EccCurveType_E curveType_en);
#endif /* CRYPTO_DIGISIGN_WC_ECDSA_EN || CRYPTO_KAS_WC_ECDH_EN */

#ifdef CRYPTO_DIGISIGN_WC_ECDSA_EN
int Crypto_Common_Wc_Ecc_EncodeToDerSign(uint8_t *inputSign, uint16_t inputSignLen, uint8_t *outDerSign, uint16_t outSignLen);
int Crypto_Common_Wc_Ecc_DecodeDerSign(uint8_t *inputDerSign, uint16_t inputSignDerLen, uint8_t *outSign, uint16_t outSignLen);
#endif /* CRYPTO_DIGISIGN_WC_ECDSA_EN */

#endif /* MCHP_CRYPTO_COMMON_WOLFCRYPTWRAPPER_H */