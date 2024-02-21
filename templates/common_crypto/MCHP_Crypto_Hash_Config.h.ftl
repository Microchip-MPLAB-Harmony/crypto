/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Hash.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef MCHP_CRYPTO_HASH_CONFIG_H
#define MCHP_CRYPTO_HASH_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

//Max session allowed for Hash Algorithm
#define CRYPTO_HASH_SESSION_MAX (1) 
#define CRYPTO_HASH_WC_ALGO_EN

// *****************************************************************************
// *****************************************************************************


<#-- HASH MD5 -->
<#if crypto_md5 == true>
    <#lt>#define CRYPTO_HASH_MD5_EN
    <#if crypto_md5_hw == true>
        <#lt>#define CRYPTO_HASH_HW_MD5_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_MD5_EN
        </#if>
    </#if>
<#-- HASH RIPEMD-160 -->
<#if crypto_ripe_md_160 == true>
    <#lt>#define CRYPTO_HASH_RIPEMD160_EN
    <#if crypto_ripemd_160_hw == true>
        <#lt>#define CRYPTO_HASH_HW_RIPEMD160_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_RIPEMD160_EN
        </#if>
    </#if>
<#-- HASH SHA1 -->
<#if crypto_sha1 == true>
    <#lt> #define CRYPTO_HASH_SHA1_EN
    <#if crypto_sha1_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA1_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA1_EN
        </#if>
    </#if>
<#-- HASH SHA2 -->
<#if crypto_sha2_224 == true>
    <#lt>#define CRYPTO_HASH_SHA2_224_EN
    <#if crypto_sha2_224_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA2_224_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA2_224_EN
        </#if>
    </#if>
<#if crypto_sha2_256 == true>
    <#lt>#define CRYPTO_HASH_SHA2_256_EN
    <#if crypto_sha2_256_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA2_256_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA2_256_EN
        </#if>
    </#if>
<#if crypto_sha2_384 == true>
    <#lt>#define CRYPTO_HASH_SHA2_384_EN
    <#if crypto_sha2_384_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA2_384_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA2_384_EN
        </#if>
    </#if>
<#if crypto_sha2_512 == true>
    <#lt>#define CRYPTO_HASH_SHA2_512_EN
    <#if crypto_sha2_512_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA2_512_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA2_512_EN
        </#if>
    </#if>
<#if false>
    //#define	CRYPTO_HASH_WC_SHA2_512_224_EN
    //#define	CRYPTO_HASH_WC_SHA2_512_256_EN
</#if>
<#-- HASH SHA3 -->
<#if crypto_sha3_224 == true>
    <#lt>#define CRYPTO_HASH_SHA3_224_EN
    <#if crypto_sha3_224_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA3_224_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA3_224_EN
        </#if>
    </#if>
<#if crypto_sha3_256 == true>
    <#lt>#define CRYPTO_HASH_SHA3_256_EN
    <#if crypto_sha3_256_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA3_256_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA3_256_EN
        </#if>
    </#if>
<#if crypto_sha3_384 == true>
    <#lt>#define CRYPTO_HASH_SHA3_384_EN
    <#if crypto_sha3_384_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA3_384_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA3_384_EN
        </#if>
    </#if>
<#if crypto_sha3_512 == true>
    <#lt>#define CRYPTO_HASH_SHA3_512_EN
    <#if crypto_sha3_512_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA3_512_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA3_512_EN
        </#if>
    </#if>
<#-- HASH SHA3 SHAKE -->
<#if crypto_sha3_shake_128 == true>
    <#lt>#define CRYPTO_HASH_SHA3_SHAKE128_EN
    <#if crypto_sha3_shake_128_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA3_SHAKE128_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA3_SHAKE128_EN
        </#if>
    </#if>
<#if crypto_sha3_shake_256 == true>
    <#lt>#define CRYPTO_HASH_SHA3_SHAKE256_EN
    <#if crypto_sha3_shake_256_hw == true>
        <#lt>#define CRYPTO_HASH_HW_SHA3_SHAKE256_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_SHA3_SHAKE256_EN
        </#if>
    </#if>
<#-- HASH BLAKE -->
<#if crypto_blake_224 == true>
    <#lt>#define CRYPTO_HASH_BLAKE_224_EN
    <#if crypto_blake_224_hw == true>
        <#lt>#define USE_HASH_BLAKE_224_HW
        <#lt>#define CRYPTO_HASH_HW_BLAKE_224_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE_224_EN
        </#if>
    </#if>
<#if crypto_blake_256 == true>
    <#lt>#define CRYPTO_HASH_BLAKE_256_EN
    <#if crypto_blake_256_hw == true>
        <#lt>#define USE_HASH_BLAKE_256_HW
        <#lt>#define CRYPTO_HASH_HW_BLAKE_256_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE_256_EN
        </#if>
    </#if>
<#if crypto_blake_384 == true>
    <#lt>#define CRYPTO_HASH_BLAKE_384_EN
    <#if crypto_blake_384_hw == true>
        <#lt>#define USE_HASH_BLAKE_384_HW
        <#lt>#define CRYPTO_HASH_HW_BLAKE_384_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE_384_EN
        </#if>
    </#if>
<#if crypto_blake_512 == true>
    <#lt>#define CRYPTO_HASH_BLAKE_512_EN
    <#if crypto_blake_512_hw == true>
        <#lt>#define USE_HASH_BLAKE_512_HW
        <#lt>#define CRYPTO_HASH_HW_BLAKE_512_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE_512_EN
        </#if>
    </#if>
<#-- HASH BLAKE2 -->
<#if crypto_blake2s_224 == true>
    <#lt>#define CRYPTO_HASH_BLAKE2S_224_EN
    <#if crypto_blake2s_224_hw == true>
        <#lt>#define CRYPTO_HASH_HW_BLAKE2S_224_EN
        <#lt>#define CRYPTO_HASH_BLAKE2S_224_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE2S_224_EN
        </#if>
    </#if>
<#if crypto_blake2s_256 == true>
    <#lt>#define CRYPTO_HASH_BLAKE2S_256_EN
    <#if crypto_blake2s_256_hw == true>
        <#lt>#define CRYPTO_HASH_HW_BLAKE2S_256_EN
        <#lt>#define CRYPTO_HASH_BLAKE2S_256_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE2S_256_EN
        </#if>
    </#if>
<#if crypto_blake2b_384 == true>
    <#lt>#define CRYPTO_HASH_BLAKE2B_384_EN
    <#if crypto_blake2b_384_hw == true>
        <#lt>#define CRYPTO_HASH_HW_BLAKE2B_384_EN
        <#lt>#define CRYPTO_HASH_BLAKE2B_384_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE2B_384_EN
        </#if>
    </#if>
<#if crypto_blake2b_512 == true>
    <#lt>#define CRYPTO_HASH_BLAKE2B_512_EN
    <#if crypto_blake2b_512_hw == true>
        <#lt>#define CRYPTO_HASH_HW_BLAKE2B_512_EN
        <#lt>#define CRYPTO_HASH_BLAKE2B_512_EN
    <#else>
        <#lt>#define CRYPTO_HASH_WC_BLAKE2B_512_EN
        </#if>
    </#if>

// ---------- FUNCTIONAL CONFIGURATION END ----------

#if (defined(CRYPTO_HASH_SHA2_224_EN) || defined(CRYPTO_HASH_SHA2_256_EN) || \
     defined(CRYPTO_HASH_SHA2_384_EN) || defined(CRYPTO_HASH_SHA2_512_EN) || \
     defined(CRYPTO_HASH_SHA2_512_224_EN) || defined(CRYPTO_HASH_SHA2_512_256_EN))
<#lt>#define CRYPTO_HASH_SHA2_EN
#endif
#if (defined(CRYPTO_HASH_WC_SHA2_224_EN) || defined(CRYPTO_HASH_WC_SHA2_256_EN) || \
     defined(CRYPTO_HASH_WC_SHA2_384_EN) || defined(CRYPTO_HASH_WC_SHA2_512_EN) || \
     defined(CRYPTO_HASH_WC_SHA2_512_224_EN) || defined(CRYPTO_HASH_WC_SHA2_512_256_EN) )
<#lt>#define CRYPTO_HASH_WC_SHA2_EN
#endif
#if (defined(CRYPTO_HASH_SHA3_224_EN) || defined(CRYPTO_HASH_SHA3_256_EN) || \
     defined(CRYPTO_HASH_SHA3_384_EN) || defined(CRYPTO_HASH_SHA3_512_EN))
<#lt>#define CRYPTO_HASH_SHA3_EN
#endif
#if (defined(CRYPTO_HASH_WC_SHA3_224_EN) || \
     defined(CRYPTO_HASH_WC_SHA3_256_EN) || \
     defined(CRYPTO_HASH_WC_SHA3_384_EN) || \
     defined(CRYPTO_HASH_WC_SHA3_512_EN))
<#lt>#define CRYPTO_HASH_WC_SHA3_EN
#endif
#if (defined(CRYPTO_HASH_SHA3_SHAKE128_EN) || \
     defined(CRYPTO_HASH_SHA3_SHAKE256_EN))
<#lt>#define CRYPTO_HASH_SHA3_SHAKE_EN
#endif

#if (defined(CRYPTO_HASH_WC_SHA3_SHAKE128_EN) || \
     defined(CRYPTO_HASH_WC_SHA3_SHAKE256_EN))
<#lt>#define CRYPTO_HASH_WC_SHA3_SHAKE_EN
#endif
#if (defined(CRYPTO_HASH_BLAKE2S_224_EN) || \
     defined(CRYPTO_HASH_BLAKE2S_256_EN) || \
     defined(CRYPTO_HASH_BLAKE2B_384_EN) || \
     defined(CRYPTO_HASH_BLAKE2B_512_EN))
<#lt>#define CRYPTO_HASH_BLAKE2_EN
#endif
#if (defined(CRYPTO_HASH_WC_BLAKE2S_224_EN) || \
     defined(CRYPTO_HASH_WC_BLAKE2S_256_EN) || \
     defined(CRYPTO_HASH_WC_BLAKE2B_384_EN) || \
     defined(CRYPTO_HASH_WC_BLAKE2B_512_EN))
<#lt>#define CRYPTO_HASH_WC_BLAKE2_EN
#endif

#endif //MCHP_CRYPTO_HASH_CONFIG_H
