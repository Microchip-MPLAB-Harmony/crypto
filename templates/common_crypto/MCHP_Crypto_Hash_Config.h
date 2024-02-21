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
#define CRYPTO_HASH_SESSION_MAX (1)      //Always define this macro to mention max. session allowed for Hash Algorithm
#define CRYPTO_HASH_WC_ALGO_EN
// *****************************************************************************
// *****************************************************************************
//Macros for MD-5
#define CRYPTO_HASH_MD5_EN
#define CRYPTO_HASH_WC_MD5_EN

//Macros for RIPEMD-160
#define CRYPTO_HASH_RIPEMD160_EN
#define CRYPTO_HASH_WC_RIPEMD160_EN

//Macros for SHA-1
#define CRYPTO_HASH_SHA1_EN
#define CRYPTO_HASH_WC_SHA1_EN

//Macros for SHA-2
#define CRYPTO_HASH_SHA2_224_EN
#define CRYPTO_HASH_SHA2_256_EN
#define CRYPTO_HASH_SHA2_384_EN
#define	CRYPTO_HASH_SHA2_512_EN
#define	CRYPTO_HASH_SHA2_512_224_EN
#define	CRYPTO_HASH_SHA2_512_256_EN
#define CRYPTO_HASH_WC_SHA2_224_EN
#define CRYPTO_HASH_WC_SHA2_256_EN
#define CRYPTO_HASH_WC_SHA2_384_EN
#define	CRYPTO_HASH_WC_SHA2_512_EN
#define	CRYPTO_HASH_WC_SHA2_512_224_EN
#define	CRYPTO_HASH_WC_SHA2_512_256_EN


//MAcros for SHA-3 except SHAKE
#define	CRYPTO_HASH_SHA3_224_EN
#define	CRYPTO_HASH_SHA3_256_EN
#define	CRYPTO_HASH_SHA3_384_EN
#define	CRYPTO_HASH_SHA3_512_EN
#define	CRYPTO_HASH_WC_SHA3_224_EN
#define	CRYPTO_HASH_WC_SHA3_256_EN
#define	CRYPTO_HASH_WC_SHA3_384_EN
#define	CRYPTO_HASH_WC_SHA3_512_EN


//Macros for SHAKE Algorithms
#define	CRYPTO_HASH_SHA3_SHAKE128_EN
#define	CRYPTO_HASH_SHA3_SHAKE256_EN
#define	CRYPTO_HASH_WC_SHA3_SHAKE128_EN
#define	CRYPTO_HASH_WC_SHA3_SHAKE256_EN

//Macros for Blake2 Algorithm
#define	CRYPTO_HASH_BLAKE2B_EN
#define	CRYPTO_HASH_BLAKE2S_EN
#define	CRYPTO_HASH_WC_BLAKE2B_EN
#define	CRYPTO_HASH_WC_BLAKE2S_EN


///////////////////////////////////////


#if (defined(CRYPTO_HASH_SHA2_224_EN) || defined(CRYPTO_HASH_SHA2_256_EN) || defined(CRYPTO_HASH_SHA2_384_EN) || defined(CRYPTO_HASH_SHA2_512_EN) \
                                                                        || defined(CRYPTO_HASH_SHA2_512_224_EN) || defined(CRYPTO_HASH_SHA2_512_256_EN) )
#define CRYPTO_HASH_SHA2_EN
#endif

#if (defined(CRYPTO_HASH_WC_SHA2_224_EN) || defined(CRYPTO_HASH_WC_SHA2_256_EN) || defined(CRYPTO_HASH_WC_SHA2_384_EN) || defined(CRYPTO_HASH_WC_SHA2_512_EN) \
                                                                        || defined(CRYPTO_HASH_WC_SHA2_512_224_EN) || defined(CRYPTO_HASH_WC_SHA2_512_256_EN) )
#define CRYPTO_HASH_WC_SHA2_EN
#endif


#if (defined(CRYPTO_HASH_SHA3_224_EN) || defined(CRYPTO_HASH_SHA3_256_EN) || defined(CRYPTO_HASH_SHA3_384_EN) || defined(CRYPTO_HASH_SHA3_512_EN))
#define CRYPTO_HASH_SHA3_EN
#endif

#if (defined(CRYPTO_HASH_WC_SHA3_224_EN) || defined(CRYPTO_HASH_WC_SHA3_256_EN) || defined(CRYPTO_HASH_WC_SHA3_384_EN) || defined(CRYPTO_HASH_WC_SHA3_512_EN))
#define CRYPTO_HASH_WC_SHA3_EN
#endif


#if (defined(CRYPTO_HASH_SHA3_SHAKE128_EN) || defined(CRYPTO_HASH_SHA3_SHAKE256_EN))
#define CRYPTO_HASH_SHA3_SHAKE_EN
#endif

#if (defined(CRYPTO_HASH_WC_SHA3_SHAKE128_EN) || defined(CRYPTO_HASH_WC_SHA3_SHAKE256_EN))
#define CRYPTO_HASH_WC_SHA3_SHAKE_EN
#endif

#if (defined(CRYPTO_HASH_BLAKE2B_EN) || defined(CRYPTO_HASH_BLAKE2S_EN))
#define CRYPTO_HASH_BLAKE2_EN
#endif

#if (defined(CRYPTO_HASH_WC_BLAKE2B_EN) || defined(CRYPTO_HASH_WC_BLAKE2S_EN))
#define CRYPTO_HASH_WC_BLAKE2_EN
#endif

#endif /* MCHP_CRYPTO_HASH_CONFIG_H */