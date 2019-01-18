/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    sp.h

  Summary:
    Crypto Framework Library header for cryptographic functions.

  Description:
    This header file contains function prototypes and definitions of
    the data types and constants that make up the Cryptographic Framework
    Library for PIC32 families of Microchip microcontrollers.
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




//DOM-IGNORE-END


#ifndef WOLF_CRYPT_SP_H
#define WOLF_CRYPT_SP_H

#include "crypto/src/types.h"

#if defined(WOLFSSL_HAVE_SP_RSA) || defined(WOLFSSL_HAVE_SP_DH) || \
                                    defined(WOLFSSL_HAVE_SP_ECC)

#include <stdint.h>

#include "crypto/src/integer.h"
#include "crypto/src/sp_int.h"

#include "crypto/src/ecc.h"

#if defined(_MSC_VER)
    #define SP_NOINLINE __declspec(noinline)
#elif defined(__GNUC__)
    #define SP_NOINLINE __attribute__((noinline))
#else
    #define SP_NOINLINE
#endif


#ifdef __cplusplus
    extern "C" {
#endif

#ifdef WOLFSSL_HAVE_SP_RSA

WOLFSSL_LOCAL int sp_RsaPublic_2048(const byte* in, word32 inLen,
    mp_int* em, mp_int* mm, byte* out, word32* outLen);
WOLFSSL_LOCAL int sp_RsaPrivate_2048(const byte* in, word32 inLen,
    mp_int* dm, mp_int* pm, mp_int* qm, mp_int* dpm, mp_int* dqm, mp_int* qim,
    mp_int* mm, byte* out, word32* outLen);

WOLFSSL_LOCAL int sp_RsaPublic_3072(const byte* in, word32 inLen,
    mp_int* em, mp_int* mm, byte* out, word32* outLen);
WOLFSSL_LOCAL int sp_RsaPrivate_3072(const byte* in, word32 inLen,
    mp_int* dm, mp_int* pm, mp_int* qm, mp_int* dpm, mp_int* dqm, mp_int* qim,
    mp_int* mm, byte* out, word32* outLen);

#endif /* WOLFSSL_HAVE_SP_RSA */

#ifdef WOLFSSL_HAVE_SP_DH

WOLFSSL_LOCAL int sp_ModExp_2048(mp_int* base, mp_int* exp, mp_int* mod,
    mp_int* res);
WOLFSSL_LOCAL int sp_ModExp_3072(mp_int* base, mp_int* exp, mp_int* mod,
    mp_int* res);

WOLFSSL_LOCAL int sp_DhExp_2048(mp_int* base, const byte* exp, word32 expLen,
    mp_int* mod, byte* out, word32* outLen);
WOLFSSL_LOCAL int sp_DhExp_3072(mp_int* base, const byte* exp, word32 expLen,
    mp_int* mod, byte* out, word32* outLen);

#endif /* WOLFSSL_HAVE_SP_DH */

#ifdef WOLFSSL_HAVE_SP_ECC

int sp_ecc_mulmod_256(mp_int* km, ecc_point* gm, ecc_point* rm, int map,
                      void* heap);
int sp_ecc_mulmod_base_256(mp_int* km, ecc_point* rm, int map, void* heap);

int sp_ecc_make_key_256(WC_RNG* rng, mp_int* priv, ecc_point* pub, void* heap);
int sp_ecc_secret_gen_256(mp_int* priv, ecc_point* pub, byte* out,
                          word32* outlen, void* heap);
int sp_ecc_sign_256(const byte* hash, word32 hashLen, WC_RNG* rng, mp_int* priv,
                    mp_int* rm, mp_int* sm, void* heap);
int sp_ecc_verify_256(const byte* hash, word32 hashLen, mp_int* pX, mp_int* pY,
                      mp_int* pZ, mp_int* r, mp_int* sm, int* res, void* heap);
int sp_ecc_is_point_256(mp_int* pX, mp_int* pY);
int sp_ecc_check_key_256(mp_int* pX, mp_int* pY, mp_int* privm, void* heap);
int sp_ecc_proj_add_point_256(mp_int* pX, mp_int* pY, mp_int* pZ,
                              mp_int* qX, mp_int* qY, mp_int* qZ,
                              mp_int* rX, mp_int* rY, mp_int* rZ);
int sp_ecc_proj_dbl_point_256(mp_int* pX, mp_int* pY, mp_int* pZ,
                              mp_int* rX, mp_int* rY, mp_int* rZ);
int sp_ecc_map_256(mp_int* pX, mp_int* pY, mp_int* pZ);
int sp_ecc_uncompress_256(mp_int* xm, int odd, mp_int* ym);

#endif /*ifdef WOLFSSL_HAVE_SP_ECC */


#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* WOLFSSL_HAVE_SP_RSA || WOLFSSL_HAVE_SP_DH || WOLFSSL_HAVE_SP_ECC */

#endif /* WOLF_CRYPT_SP_H */

