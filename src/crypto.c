/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypto.c

  Summary:
    Crypto Framework Libarary source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic
	Framework Library for PIC32 families of Microchip microcontrollers.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* Implements Microchip CRYPTO API layer */
#include "crypto/crypto.h"
#include "wolfssl/wolfcrypt/compress.h"
#include "wolfssl/wolfcrypt/error-crypt.h"

// *****************************************************************************
// *****************************************************************************
// Section: Microchip CRYPTO APIs
// *****************************************************************************
// *****************************************************************************

#ifndef NO_MD5
/* Initialize MD5 */
int CRYPT_MD5_Initialize(CRYPT_MD5_CTX* md5)
{
    if (md5 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    (void)wc_InitMd5(&md5->holder);

    return 0;
}

int CRYPT_MD5_DataSizeSet(CRYPT_MD5_CTX* md5, unsigned int sz)
{
    if (md5 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

#ifdef WOLFSSL_PIC32MZ_HASH
    wc_Md5SizeSet(&md5->holder, sz);
#endif

    return 0;
}

/* Add data to MD5 */
int CRYPT_MD5_DataAdd(CRYPT_MD5_CTX* md5, const unsigned char* input,
                      unsigned int sz)
{
    if (md5 == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Md5Update(&md5->holder, input, sz);
}

/* Get MD5 Final into digest */
int CRYPT_MD5_Finalize(CRYPT_MD5_CTX* md5, unsigned char* digest)
{
    if (md5 == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Md5Final(&md5->holder, digest);
}
#endif  // NO_MD5

#ifndef NO_SHA
/* Initialize SHA */
int CRYPT_SHA_Initialize(CRYPT_SHA_CTX* sha)
{
    if (sha == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_InitSha(&sha->holder);
}

int CRYPT_SHA_DataSizeSet(CRYPT_SHA_CTX* sha, unsigned int sz)
{
    if (sha == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

#ifdef WOLFSSL_PIC32MZ_HASH
    wc_ShaSizeSet(&sha->holder, sz);
#endif

    return 0;
}

/* Add data to SHA */
int CRYPT_SHA_DataAdd(CRYPT_SHA_CTX* sha, const unsigned char* input,
                       unsigned int sz)
{
    if (sha == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ShaUpdate(&sha->holder, input, sz);
}

/* Get SHA Final into digest */
int CRYPT_SHA_Finalize(CRYPT_SHA_CTX* sha, unsigned char* digest)
{
    if (sha == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ShaFinal(&sha->holder, digest);
}
#endif // NO_SHA

#ifndef NO_SHA256
/* Initialize SHA-256 */
int CRYPT_SHA256_Initialize(CRYPT_SHA256_CTX* sha256)
{

    if (sha256 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_InitSha256(&sha256->holder);
}

int CRYPT_SHA256_DataSizeSet(CRYPT_SHA256_CTX* sha256, unsigned int sz)
{
    if (sha256 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

#ifdef WOLFSSL_PIC32MZ_HASH
    wc_Sha256SizeSet(&sha256->holder, sz);
#endif

    return 0;
}

/* Add data to SHA-256 */
int CRYPT_SHA256_DataAdd(CRYPT_SHA256_CTX* sha256, const unsigned char* input,
                         unsigned int sz)
{
    if (sha256 == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha256Update(&sha256->holder, input, sz);
}

/* Get SHA-256 Final into digest */
int CRYPT_SHA256_Finalize(CRYPT_SHA256_CTX* sha256, unsigned char* digest)
{
    if (sha256 == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha256Final(&sha256->holder, digest);
}
#endif // NO_SHA256

#ifdef WOLFSSL_SHA224
/* Initialize SHA-224 */
int CRYPT_SHA224_Initialize(CRYPT_SHA256_CTX* sha224)
{
    if (sha224 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_InitSha224(&sha224->holder);
}

/* Add data to SHA-224 */
int CRYPT_SHA224_DataAdd(CRYPT_SHA256_CTX* sha224, const unsigned char* input,
                         unsigned int sz)
{
    if (sha224 == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha224Update(&sha224->holder, input, sz);
}

/* Get SHA-224 Final into digest */
int CRYPT_SHA224_Finalize(CRYPT_SHA256_CTX* sha224, unsigned char* digest)
{
    if (sha224 == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha224Final(&sha224->holder, digest);
}
#endif  // WOLFSSL_SHA224

#ifdef WOLFSSL_SHA384
/* Initialize SHA-384 */
int CRYPT_SHA384_Initialize(CRYPT_SHA384_CTX* sha384)
{

    if (sha384 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_InitSha384(&sha384->holder);
}

/* Add data to SHA-384 */
int CRYPT_SHA384_DataAdd(CRYPT_SHA384_CTX* sha384, const unsigned char* input,
                         unsigned int sz)
{
    if (sha384 == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha384Update(&sha384->holder, input, sz);
}

/* Get SHA-384 Final into digest */
int CRYPT_SHA384_Finalize(CRYPT_SHA384_CTX* sha384, unsigned char* digest)
{
    if (sha384 == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha384Final(&sha384->holder, digest);
}
#endif  // WOLFSSL_SHA384

#ifdef WOLFSSL_SHA512
/* Initialize SHA-512 */
int CRYPT_SHA512_Initialize(CRYPT_SHA512_CTX* sha512)
{

    if (sha512 == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_InitSha512(&sha512->holder);
}

/* Add data to SHA-512 */
int CRYPT_SHA512_DataAdd(CRYPT_SHA512_CTX* sha512, const unsigned char* input,
                         unsigned int sz)
{
    if (sha512 == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha512Update(&sha512->holder, input, sz);
}

/* Get SHA-512 Final into digest */
int CRYPT_SHA512_Finalize(CRYPT_SHA512_CTX* sha512, unsigned char* digest)
{
    if (sha512 == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Sha512Final(&sha512->holder, digest);
}
#endif  // WOLFSSL_SHA512

#ifndef NO_HMAC
/* Set HMAC key with type */
int CRYPT_HMAC_SetKey(CRYPT_HMAC_CTX* hmac, int type, const unsigned char* key,
                      unsigned int sz)
{

    if ((hmac == NULL) || (key == NULL) || (0U == sz))
    {
        return (int)BAD_FUNC_ARG;
    }

    int wc_sha;
    if      (CRYPT_HMAC_SHA    == type) {wc_sha = (int)WC_SHA;}
    else if (CRYPT_HMAC_SHA256 == type) {wc_sha = (int)WC_SHA256;}
    else if (CRYPT_HMAC_SHA384 == type) {wc_sha = (int)WC_SHA384;}
    else if (CRYPT_HMAC_SHA512 == type) {wc_sha = (int)WC_SHA512;}
    else
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_HmacSetKey(&hmac->holder, wc_sha, key, sz);
}

int CRYPT_HMAC_DataAdd(CRYPT_HMAC_CTX* hmac, const unsigned char* input,
                       unsigned int sz)
{
    if (hmac == NULL || input == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_HmacUpdate(&hmac->holder, input, sz);
}

/* Get HMAC Final into digest */
int CRYPT_HMAC_Finalize(CRYPT_HMAC_CTX* hmac, unsigned char* digest)
{
    if (hmac == NULL || digest == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_HmacFinal(&hmac->holder, digest);
}
#endif // NO_HMAC

#ifdef HAVE_LIBZ
/* Huffman Compression, set flag to do static, otherwise dynamic */
/* return compressed size, otherwise < 0 for error */
int CRYPT_HUFFMAN_Compress(unsigned char* out, unsigned int outSz,
                           const unsigned char* in, unsigned int inSz,
                           unsigned int flags)
{
    if (out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Compress(out, outSz, in, inSz, flags);
}

/* Huffman DeCompression, self determines type */
/* return decompressed size, otherwise < 0 for error */
int CRYPT_HUFFMAN_DeCompress(unsigned char* out, unsigned int outSz,
                             const unsigned char* in, unsigned int inSz)
{
    if (out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_DeCompress(out, outSz, in, inSz);
}
#endif  // HAVE_LIBZ

#ifndef NO_RNG
/* RNG Initialize, < 0 on error */
int CRYPT_RNG_Initialize(CRYPT_RNG_CTX* rng)
{

    if (rng == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

#ifdef WOLFSSL_MICROCHIP_SAME70
	return same70_InitRng();
#else
    return wc_InitRng(&rng->holder);
#endif
}

/* RNG Deinitialize (free) */
int CRYPT_RNG_Deinitialize(CRYPT_RNG_CTX* rng)
{
    if (rng == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    (void)wc_FreeRng(&rng->holder);

    return 0;
}

/* RNG Get single bytes, < 0 on error */
int CRYPT_RNG_Get(CRYPT_RNG_CTX* rng, unsigned char* b)
{
    if (rng == NULL || b == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_RNG_GenerateByte(&rng->holder, (byte*)b);
}

/* RNG Block Generation of sz bytes, < 0 on error */
int CRYPT_RNG_BlockGenerate(CRYPT_RNG_CTX* rng, unsigned char* b,
                            unsigned int sz)
{
    if (rng == NULL || b == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

#if defined(WOLFSSL_MICROCHIP_SAME70)
    return same70_RNG_GenerateBlock(b, sz);
#else
    return wc_RNG_GenerateBlock(&rng->holder, b, sz);
#endif
}
#endif  /* NO_RNG */

#ifndef NO_DES3
/* Triple DES Key Set, may have iv, will have direction */
int CRYPT_TDES_KeySet(CRYPT_TDES_CTX* tdes, const unsigned char* key,
                      const unsigned char* iv, int dir)
{

    if (tdes == NULL || key == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Des3_SetKey(&tdes->holder, key, iv, dir);
}

/* Triple DES Iv Set, sometimes added later */
int CRYPT_TDES_IvSet(CRYPT_TDES_CTX* tdes, const unsigned char* iv)
{
    if (tdes == NULL || iv == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Des3_SetIV(&tdes->holder, iv);
}

/* Triple DES CBC Encrypt */
int CRYPT_TDES_CBC_Encrypt(CRYPT_TDES_CTX* tdes, unsigned char* out,
                           const unsigned char* in, unsigned int inSz)
{
    if (tdes == NULL || out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Des3_CbcEncrypt(&tdes->holder, out, in, inSz);
}

/* Triple DES CBC Decrypt */
int CRYPT_TDES_CBC_Decrypt(CRYPT_TDES_CTX* tdes, unsigned char* out,
                           const unsigned char* in, unsigned int inSz)
{
    if (tdes == NULL || out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_Des3_CbcDecrypt(&tdes->holder, out, in, inSz);
}
#endif  /* NO_DES3 */

#ifndef NO_AES
/* AES Key Set, may have iv, will have direction */
int CRYPT_AES_KeySet(CRYPT_AES_CTX* aes, const unsigned char* key,
                     unsigned int keyLen, const unsigned char* iv, int dir)
{

    if (aes == NULL || key == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_AesSetKey(&aes->holder, key, keyLen, iv, dir);
}

/* AES Iv Set, sometimes added later */
int CRYPT_AES_IvSet(CRYPT_AES_CTX* aes, const unsigned char* iv)
{
    if (aes == NULL || iv == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_AesSetIV(&aes->holder, iv);
}

#ifdef HAVE_AES_CBC
int CRYPT_AES_CBC_Encrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                          const unsigned char* in, unsigned int inSz)
{
    if (aes == NULL || out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_AesCbcEncrypt(&aes->holder, out, in, inSz);
}

/* AES CBC Decrypt */
int CRYPT_AES_CBC_Decrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                          const unsigned char* in, unsigned int inSz)
{
    if (aes == NULL || out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_AesCbcDecrypt(&aes->holder, out, in, inSz);
}
#endif /* HAVE_AES_CBC */

#ifdef WOLFSSL_AES_COUNTER
/* AES CTR Encrypt (used for decrypt too, with ENCRYPT key setup) */
int CRYPT_AES_CTR_Encrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                          const unsigned char* in, unsigned int inSz)
{
    if (aes == NULL || out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_AesCtrEncrypt(&aes->holder, out, in, inSz);
}
#endif /* WOLFSSL_AES_COUNTER */

#if defined(HAVE_AESGCM)
int CRYPT_AES_GCM_SetKey(CRYPT_AES_CTX* aes, const unsigned char* key, unsigned int len)
{


    if (aes == NULL || key == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }
    return wc_AesGcmSetKey(&aes->holder, key, len);
}

int CRYPT_AES_GCM_Encrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                                   const unsigned char* in, unsigned int sz,
                                   const unsigned char* iv, unsigned int ivSz,
                                   unsigned char* authTag, unsigned int authTagSz,
                                   const unsigned char* authIn, unsigned int authInSz)
{
    if (aes == NULL || out == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }
    return wc_AesGcmEncrypt(&aes->holder, out, in, sz, iv, ivSz, authTag, authTagSz, authIn, authInSz);
}

int CRYPT_AES_GCM_Decrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                                   const unsigned char* in, unsigned int sz,
                                   const unsigned char* iv, unsigned int ivSz,
                                   const unsigned char* authTag, unsigned int authTagSz,
                                   const unsigned char* authIn, unsigned int authInSz)
{
    if (aes == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }
    return wc_AesGcmDecrypt(&aes->holder, out, in, sz, iv, ivSz, authTag, authTagSz, authIn, authInSz);
}
#endif  /* HAVE_AESGCM */

#ifdef WOLFSSL_AES_DIRECT
/* AES Direct mode encrypt, one block at a time */
int CRYPT_AES_DIRECT_Encrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                             const unsigned char* in)
{
    if (aes == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    (void)wc_AesEncryptDirect(&aes->holder, out, in);

    return 0;
}

/* AES Direct mode decrypt, one block at a time */
int CRYPT_AES_DIRECT_Decrypt(CRYPT_AES_CTX* aes, unsigned char* out,
                             const unsigned char* in)
{
    if (aes == NULL || out == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    (void)wc_AesDecryptDirect(&aes->holder, out, in);

    return 0;
}
#endif /* WOLFSSL_AES_DIRECT */
#endif /* NO_AES */

#ifndef NO_RSA
/* MISRAC 2023 deviation block start */
/* Following MISRA-C rules deviated in this block  */
/* MISRA C-2023 Directive 4.12 - Deviation record ID - H3_MISRAC_2023_D_4_12_DR_1 */
/* MISRA C-2023 Rule 21.3 - Deviation record ID - H3_MISRAC_2023_R_21_3_DR_1 */
/* MISRA C-2023 Rule 14.4 - Deviation record ID - H3_MISRAC_2023_R_14_4_DR_1 */
/* MISRA C-2023 Rule 15.6 - Deviation record ID - H3_MISRAC_2023_R_15_6_DR_1 */

/* The RSA key is allocated from the heap because its size depends on
   FP_MAX_BITS and is too large to embed in the context on small targets.
   Allocation is confined to the two functions below, every allocation is
   checked against NULL, and each XMALLOC is paired with exactly one XFREE.

   Rules 14.4 and 15.6 are deviated because the wolfSSL XFREE macro expands to
   "do { void* xp = (p); if (xp) <release>; } while (0)", which tests a pointer
   rather than an essentially boolean expression and omits braces on the
   then-branch. Both constructs are internal to the macro and cannot be
   corrected from this file. XFREE is retained deliberately: it selects the
   deallocator that matches the active wolfSSL memory backend, which for a
   static memory pool is not interchangeable with free(). */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma coverity compliance block \
(deviate:1 "MISRA C-2023 Directive 4.12" "H3_MISRAC_2023_D_4_12_DR_1" )\
(deviate:2 "MISRA C-2023 Rule 21.3" "H3_MISRAC_2023_R_21_3_DR_1" )\
(deviate:2 "MISRA C-2023 Rule 14.4" "H3_MISRAC_2023_R_14_4_DR_1" )\
(deviate:1 "MISRA C-2023 Rule 15.6" "H3_MISRAC_2023_R_15_6_DR_1" )

/* RSA Initialize */
int CRYPT_RSA_Initialize(CRYPT_RSA_CTX* rsa)
{
    if (rsa == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    rsa->holder = XMALLOC(sizeof(RsaKey), NULL, DYNAMIC_TYPE_RSA);
    if (rsa->holder == NULL)
    {
        return -1;
    }

    return wc_InitRsaKey_ex(rsa->holder, NULL, 0);
}

/* RSA Free resources */
int CRYPT_RSA_Free(CRYPT_RSA_CTX* rsa)
{
    if (rsa == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    if (rsa->holder != NULL)
    {
        (void)wc_FreeRsaKey(rsa->holder);
        XFREE(rsa->holder, NULL, DYNAMIC_TYPE_RSA);
        rsa->holder = NULL;
    }

    return 0;
}

#pragma coverity compliance end_block "MISRA C-2023 Directive 4.12"
#pragma coverity compliance end_block "MISRA C-2023 Rule 21.3"
#pragma coverity compliance end_block "MISRA C-2023 Rule 14.4"
#pragma coverity compliance end_block "MISRA C-2023 Rule 15.6"
#pragma GCC diagnostic pop
/* MISRAC 2023 deviation block end */

/* RSA Public key decode ASN.1 */
int CRYPT_RSA_PublicKeyDecode(CRYPT_RSA_CTX* rsa, const unsigned char* in,
                              unsigned int inSz)
{
    unsigned int idx = 0;
    (void)idx;

    if (rsa == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_RsaPublicKeyDecode(in, &idx, rsa->holder, inSz);
}

/* RSA Private key decode ASN.1 */
int CRYPT_RSA_PrivateKeyDecode(CRYPT_RSA_CTX* rsa, const unsigned char* in,
                               unsigned int inSz)
{
    unsigned int idx = 0;
    (void)idx;

    if (rsa == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_RsaPrivateKeyDecode(in, &idx, rsa->holder, inSz);
}

/* RSA Public Encrypt */
int CRYPT_RSA_PublicEncrypt(CRYPT_RSA_CTX* rsa, unsigned char* out,
                            unsigned int outSz, const unsigned char* in,
                            unsigned int inSz, CRYPT_RNG_CTX* rng)
{
    if (rsa == NULL || in == NULL || out == NULL || rng == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_RsaPublicEncrypt(in, inSz, out, outSz, rsa->holder,
                            &rng->holder);
}

/* RSA Private Decrypt */
int CRYPT_RSA_PrivateDecrypt(CRYPT_RSA_CTX* rsa, unsigned char* out,
                             unsigned int outSz, const unsigned char* in,
                             unsigned int inSz)
{
    if (rsa == NULL || in == NULL || out == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_RsaPrivateDecrypt(in, inSz, out, outSz, rsa->holder);
}

/* RSA Get Encrypt size helper */
int CRYPT_RSA_EncryptSizeGet(CRYPT_RSA_CTX* rsa)
{
    if (rsa == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_RsaEncryptSize(rsa->holder);
}
#endif // NO_RSA

#ifdef HAVE_ECC
/* MISRAC 2023 deviation block start */
/* Following MISRA-C rules deviated in this block  */
/* MISRA C-2023 Directive 4.12 - Deviation record ID - H3_MISRAC_2023_D_4_12_DR_1 */
/* MISRA C-2023 Rule 21.3 - Deviation record ID - H3_MISRAC_2023_R_21_3_DR_1 */
/* MISRA C-2023 Rule 14.4 - Deviation record ID - H3_MISRAC_2023_R_14_4_DR_1 */
/* MISRA C-2023 Rule 15.6 - Deviation record ID - H3_MISRAC_2023_R_15_6_DR_1 */

/* The ECC key is allocated from the heap because its size depends on which
   curves are enabled and is too large to embed in the context on small targets.
   Allocation is confined to the two functions below, every allocation is
   checked against NULL, and each XMALLOC is paired with exactly one XFREE.

   Rules 14.4 and 15.6 are deviated because the wolfSSL XFREE macro expands to
   "do { void* xp = (p); if (xp) <release>; } while (0)", which tests a pointer
   rather than an essentially boolean expression and omits braces on the
   then-branch. Both constructs are internal to the macro and cannot be
   corrected from this file. XFREE is retained deliberately: it selects the
   deallocator that matches the active wolfSSL memory backend, which for a
   static memory pool is not interchangeable with free(). */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma coverity compliance block \
(deviate:1 "MISRA C-2023 Directive 4.12" "H3_MISRAC_2023_D_4_12_DR_1" )\
(deviate:2 "MISRA C-2023 Rule 21.3" "H3_MISRAC_2023_R_21_3_DR_1" )\
(deviate:2 "MISRA C-2023 Rule 14.4" "H3_MISRAC_2023_R_14_4_DR_1" )\
(deviate:1 "MISRA C-2023 Rule 15.6" "H3_MISRAC_2023_R_15_6_DR_1" )

/* ECC init */
int CRYPT_ECC_Initialize(CRYPT_ECC_CTX* ecc)
{
    if (ecc == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    ecc->holder = XMALLOC(sizeof(ecc_key), NULL, DYNAMIC_TYPE_ECC);
    if (ecc->holder == NULL)
    {
        return -1;
    }

    return wc_ecc_init(ecc->holder);
}


/* ECC free resources */
int CRYPT_ECC_Free(CRYPT_ECC_CTX* ecc)
{
    if (ecc == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    if (ecc->holder != NULL)
    {
        (void) wc_ecc_free(ecc->holder);
        XFREE(ecc->holder, NULL, DYNAMIC_TYPE_ECC);
        ecc->holder = NULL;
    }

    return 0;
}

#pragma coverity compliance end_block "MISRA C-2023 Directive 4.12"
#pragma coverity compliance end_block "MISRA C-2023 Rule 21.3"
#pragma coverity compliance end_block "MISRA C-2023 Rule 14.4"
#pragma coverity compliance end_block "MISRA C-2023 Rule 15.6"
#pragma GCC diagnostic pop
/* MISRAC 2023 deviation block end */

/* ECC Public x963 Export */
int CRYPT_ECC_PublicExport(CRYPT_ECC_CTX* ecc, unsigned char* out,
                           unsigned int outSz, unsigned int* usedSz)
{
    int          ret;
    unsigned int inOut = outSz;

    if (ecc == NULL || out == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    ret = wc_ecc_export_x963(ecc->holder, out, &inOut);
    if (ret == 0)
    {
        *usedSz = inOut;
    }

    return ret;
}

/* ECC Public x963 Import */
int CRYPT_ECC_PublicImport(CRYPT_ECC_CTX* ecc, const unsigned char* in,
                           unsigned int inSz)
{
    if (ecc == NULL || in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ecc_import_x963(in, inSz, ecc->holder);
}

/* ECC Private x963 Import */
int CRYPT_ECC_PrivateImport(CRYPT_ECC_CTX* ecc, const unsigned char* priv,
         unsigned int privSz, const unsigned char* pub, unsigned int pubSz)
{
    if (ecc == NULL || priv == NULL || pub == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ecc_import_private_key(priv, privSz, pub, pubSz,
                                 ecc->holder);
}

/* ECC DHE Make key */
int CRYPT_ECC_DHE_KeyMake(CRYPT_ECC_CTX* ecc, CRYPT_RNG_CTX* rng, int keySz)
{
    if (ecc == NULL || rng == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ecc_make_key(&rng->holder, keySz, ecc->holder);
}

/* ECC DHE Make shared secret with our private and peer public */
int CRYPT_ECC_DHE_SharedSecretMake(CRYPT_ECC_CTX* priv, CRYPT_ECC_CTX* pub,
                  unsigned char* out, unsigned int outSz, unsigned int* usedSz)
{
    int ret;
    unsigned int inOut = outSz;

    if (priv == NULL || pub == NULL || out == NULL || usedSz == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    ret = wc_ecc_shared_secret(priv->holder, pub->holder,
                            out, &inOut);
    if (ret == 0)
    {
        *usedSz = inOut;
    }

    return ret;
}

/* ECC DSA Hash Sign */
int CRYPT_ECC_DSA_HashSign(CRYPT_ECC_CTX* ecc, CRYPT_RNG_CTX* rng,
                           unsigned char* sig, unsigned int sigSz,
                           unsigned int* usedSz, const unsigned char* in,
                           unsigned int inSz)
{
    int ret;
    unsigned int inOut = sigSz;

    if (ecc == NULL || rng == NULL || sig == NULL || usedSz == NULL ||
                                                                in == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    ret = wc_ecc_sign_hash(in, inSz, sig, &inOut, &rng->holder,
                       ecc->holder);
    if (ret == 0)
    {
        *usedSz = inOut;
    }

    return ret;
}

/* ECC DSA Hash Verify */
int CRYPT_ECC_DSA_HashVerify(CRYPT_ECC_CTX* ecc, const unsigned char* sig,
                             unsigned int sigSz, unsigned char* hash,
                             unsigned int hashSz, int* status)
{
    if (ecc == NULL || sig == NULL || hash == NULL || status == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    int ret = wc_ecc_verify_hash(sig, sigSz, hash, hashSz, status,
                          ecc->holder);
    if (ret != 0)
    {
        *status = 0;
    }

    return ret;
}

/* ECC get key size helper */
int CRYPT_ECC_KeySizeGet(CRYPT_ECC_CTX* ecc)
{
    if (ecc == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ecc_size(ecc->holder);
}

/* ECC get signature size helper */
int CRYPT_ECC_SignatureSizeGet(CRYPT_ECC_CTX* ecc)
{
    if (ecc == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

    return wc_ecc_sig_size(ecc->holder);
}
#endif // HAVE_ECC

/* Save error string from err to str which needs to be >= 80 chars */
int CRYPT_ERROR_StringGet(int err, char* str)
{
    if (str == NULL)
    {
        return (int)BAD_FUNC_ARG;
    }

#ifdef NO_ERROR_STRINGS
    /* Under NO_ERROR_STRINGS, wc_ErrorString() is a macro that copies
       WOLFSSL_MAX_ERROR_SZ (>= 64) bytes from a 37-character literal
       (38 bytes including the terminator), which violates MISRA C-2023
       Rule 21.18. Bound the copy by the size of the source object. */
    {
        static const char noStr[] = "no support for error strings built in";

        (void)err;
        (void)XMEMCPY(str, noStr, sizeof(noStr));
    }
#else
    wc_ErrorString(err, str);
#endif

    return 0;
}

