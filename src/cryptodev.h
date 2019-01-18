/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    cryptodev.h

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

#ifndef _WOLF_CRYPTO_DEV_H_
#define _WOLF_CRYPTO_DEV_H_

#include "crypto/src/types.h"

#ifdef __cplusplus
    extern "C" {
#endif

#ifdef WOLF_CRYPTO_DEV

#ifndef NO_RSA
    #include "crypto/src/rsa.h"
#endif
#ifdef HAVE_ECC
    #include "crypto/src/ecc.h"
#endif
#ifndef NO_AES
    #include "crypto/src/aes.h"
#endif

/* Crypto Information Structure for callbacks */
typedef struct wc_CryptoInfo {
    int algo_type; /* enum wc_AlgoType */
    struct {
        int type; /* enum wc_PkType */
        union {
        #ifndef NO_RSA
            struct {
                const byte* in;
                word32      inLen;
                byte*       out;
                word32*     outLen;
                int         type;
                RsaKey*     key;
                WC_RNG*     rng;
            } rsa;
        #ifdef WOLFSSL_KEY_GEN
            struct {
                RsaKey* key;
                int     size;
                long    e;
                WC_RNG* rng;
            } rsakg;
        #endif
        #endif
        #ifdef HAVE_ECC
            struct {
                WC_RNG*  rng;
                int      size;
                ecc_key* key;
                int      curveId;
            } eckg;
            struct {
                ecc_key* private_key;
                ecc_key* public_key;
                byte*    out;
                word32*  outlen;
            } ecdh;
            struct {
                const byte* in;
                word32      inlen;
                byte*       out;
                word32*     outlen;
                WC_RNG*     rng;
                ecc_key*    key;
            } eccsign;
            struct {
                const byte* sig;
                word32      siglen;
                const byte* hash;
                word32      hashlen;
                int*        res;
                ecc_key*    key;
            } eccverify;
        #endif
        };
    } pk;
    struct {
        int type; /* enum wc_CipherType */
        int enc;
        union {
        #if !defined(NO_AES) && defined(HAVE_AESGCM)
            struct {
                Aes*        aes;
                byte*       out;
                const byte* in;
                word32      sz;
                const byte* iv;
                word32      ivSz;
                byte*       authTag;
                word32      authTagSz;
                const byte* authIn;
                word32      authInSz;
            } aesgcm_enc;
            struct {
                Aes*        aes;
                byte*       out;
                const byte* in;
                word32      sz;
                const byte* iv;
                word32      ivSz;
                const byte* authTag;
                word32      authTagSz;
                const byte* authIn;
                word32      authInSz;
            } aesgcm_dec;
        #endif
        };
    } cipher;
} wc_CryptoInfo;

typedef int (*CryptoDevCallbackFunc)(int devId, wc_CryptoInfo* info, void* ctx);

WOLFSSL_LOCAL void wc_CryptoDev_Init(void);

WOLFSSL_API int  wc_CryptoDev_RegisterDevice(int devId, CryptoDevCallbackFunc cb, void* ctx);
WOLFSSL_API void wc_CryptoDev_UnRegisterDevice(int devId);


#ifndef NO_RSA
WOLFSSL_LOCAL int wc_CryptoDev_Rsa(const byte* in, word32 inLen, byte* out,
    word32* outLen, int type, RsaKey* key, WC_RNG* rng);

#ifdef WOLFSSL_KEY_GEN
WOLFSSL_LOCAL int wc_CryptoDev_MakeRsaKey(RsaKey* key, int size, long e,
    WC_RNG* rng);
#endif /* WOLFSSL_KEY_GEN */
#endif /* !NO_RSA */

#ifdef HAVE_ECC
WOLFSSL_LOCAL int wc_CryptoDev_MakeEccKey(WC_RNG* rng, int keySize,
    ecc_key* key, int curveId);

WOLFSSL_LOCAL int wc_CryptoDev_Ecdh(ecc_key* private_key, ecc_key* public_key,
    byte* out, word32* outlen);

WOLFSSL_LOCAL int wc_CryptoDev_EccSign(const byte* in, word32 inlen, byte* out,
    word32 *outlen, WC_RNG* rng, ecc_key* key);

WOLFSSL_LOCAL int wc_CryptoDev_EccVerify(const byte* sig, word32 siglen,
    const byte* hash, word32 hashlen, int* res, ecc_key* key);
#endif /* HAVE_ECC */

#if !defined(NO_AES) && defined(HAVE_AESGCM)

WOLFSSL_LOCAL int wc_CryptoDev_AesGcmEncrypt(Aes* aes, byte* out,
     const byte* in, word32 sz, const byte* iv, word32 ivSz,
     byte* authTag, word32 authTagSz, const byte* authIn, word32 authInSz);

WOLFSSL_LOCAL int wc_CryptoDev_AesGcmDecrypt(Aes* aes, byte* out,
     const byte* in, word32 sz, const byte* iv, word32 ivSz,
     const byte* authTag, word32 authTagSz,
     const byte* authIn, word32 authInSz);

#endif /* !NO_AES && HAVE_AESGCM */

WOLFSSL_LOCAL int wc_CryptoDev_Sha256Hash(const byte* data, word32 len, byte* hash);

#endif /* WOLF_CRYPTO_DEV */

#ifdef __cplusplus
    } /* extern "C" */
#endif

#endif /* _WOLF_CRYPTO_DEV_H_ */
