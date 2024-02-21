<#lt><#----------------------------------------------------------------------------
<#lt> Copyright (C) 2019-2024 Microchip Technology Inc. and its subsidiaries.
<#lt>
<#lt>Microchip Technology Inc. and its subsidiaries.
<#lt>
<#lt>Subject to your compliance with these terms, you may use Microchip software 
<#lt>and any derivatives exclusively with Microchip products. It is your 
<#lt>responsibility to comply with third party license terms applicable to your 
<#lt>use of third party software (including open source software) that may 
<#lt>accompany Microchip software.
<#lt>
<#lt>THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
<#lt>EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
<#lt>WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
<#lt>PURPOSE.
<#lt>
<#lt>IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
<#lt>INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
<#lt>WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
<#lt>BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
<#lt>FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
<#lt>ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
<#lt>THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
<#lt>----------------------------------------------------------------------------->
<#lt>
<#lt>/*** wolfCrypt Library Configuration ***/
<#lt>
<#lt>//configuration.h included in config.h and user_settings.h allowing these
<#lt>//files to configure WolfSSL library
<#lt>//--WolfSSL project defines to use these files are WOLFSSL_USER_SETTINGS and
<#lt>//  HAVE_CONFIG_H
/*** wolfCrypt Library Configuration ***/

<#lt>/*** wolfCrypt Library Configuration ***/
<#lt>#define MICROCHIP_PIC32
<#lt>#define MICROCHIP_MPLAB_HARMONY
<#lt>#define MICROCHIP_MPLAB_HARMONY_3
<#lt>#define HAVE_MCAPI
<#lt>#define SIZEOF_LONG_LONG 8
<#lt>#define WOLFSSL_USER_IO
<#lt>#define NO_WRITEV
<#lt>#define NO_FILESYSTEM
<#lt>#define USE_FAST_MATH
<#lt>#define NO_INLINE 


<#lt>//Math Model Defines
<#lt>//#define WOLFSSL_SP_MATH_ALL
<#lt>#define WOLFSSL_SP_SMALL
//Using this to declare wolfmath functions:
//mp_reverse used by fp_to_unsigned_bin (tfm.c)unctions: 
//get_digit_count,get_digit in ecc.c 
<#lt>#define WOLFSSL_SP_MATH   

//Needed when WOFSSL_SP_MATH defined
<#lt>#define WOLFSSL_HAVE_SP_RSA  

<#lt>//To prevent usage of SP functions defined by this: 
<#lt>//#if defined(HAVE_FIPS_VERSION) && HAVE_FIPS_VERSION == 2 
<#lt>//&& ( defined(WOLFSSL_SP_ARM32_ASM) || defined(WOLFSSL_SP_ARM64_ASM) ) 
<#lt>#define WOLFSSL_SP_NO_256   

<#lt>//#define WOLFSSL_SP_ARM32_ASM   //Dependent on MCU Arch.


<#lt>#define NO_PWDBASED
<#lt>//#define WOLF_CRYPTO_CB  // provide call-back support if this is disable then its does not use callback from Wolfcrypt
<#lt>#define WOLFCRYPT_ONLY

// ---------- FUNCTIONAL CONFIGURATION START ----------
<#lt>#define WOLFSSL_AES_SMALL_TABLES
<#lt>#define NO_MD4
<#lt>#define WOLFSSL_SHA224
<#lt>#define WOLFSSL_SHA384
<#lt>#define WOLFSSL_SHA512
<#lt>#define HAVE_SHA512
<#lt>#define WOLFSSL_SHA3
<#lt>#define HAVE_BLAKE2
<#lt>#define WOLFSSL_RIPEMD
<#lt>#define NO_HMAC
<#lt>#define WOLFSSL_AES_128
<#lt>#define WOLFSSL_AES_192
<#lt>#define WOLFSSL_AES_256
<#lt>#define WOLFSSL_AES_DIRECT
<#lt>#define HAVE_AES_DECRYPT
<#lt>#define HAVE_AES_ECB
<#lt>#define HAVE_AES_CBC
<#lt>#define WOLFSSL_AES_COUNTER
<#lt>#define WOLFSSL_AES_CFB
<#lt>#define WOLFSSL_AES_OFB
<#lt>#define HAVE_AESGCM
<#lt>#define WOLFSSL_AES_XTS
<#lt>#define HAVE_AESCCM
<#lt>#define WOLFSSL_CMAC
<#lt>#define HAVE_CAMELLIA
<#lt>#define HAVE_IDEA
<#lt>#define HAVE_HC128
<#lt>#define HAVE_RABBIT

<#lt>#define HAVE_ECC
<#lt>#define HAVE_ECC_KEY_EXPORT    //Required for WOLFCRYPT_HAVE_ECCSI
<#lt>#define HAVE_X963_KDF
<#lt>#define ECC_SHAMIR
<#lt>#define WOLFSSL_CUSTOM_CURVES
<#lt>#define HAVE_CURVE25519
<#lt>#define HAVE_ED25519
<#lt>#define FP_ECC
<#lt>#define HAVE_ECC521    //ECC_MAX_BITS


<#lt>//#define HAVE_DH
<#lt>//#define WOLFSSL_HAVE_SP_DH
    
<#lt>#define HAVE_ANON
<#lt>#define WOLFSSL_OLD_PRIME_CHECK
<#lt>#define NO_DSA
<#lt>#define FP_MAX_BITS 4096
<#lt>#define USE_CERT_BUFFERS_2048
<#lt>#define WOLFSSL_RSA_PUBLIC_ONLY
<#lt>#define WC_RSA_PSS
<#lt>#define WOLFSSL_STATIC_RSA
<#lt>#define NO_DEV_RANDOM
<#lt>#define HAVE_HASHDRBG
<#lt>#define WC_NO_HARDEN //why this is used
<#lt>#define SINGLE_THREADED
<#lt>#define NO_ERROR_STRINGS
<#lt>#define NO_WOLFSSL_MEMORY
<#lt>// ---------- FUNCTIONAL CONFIGURATION END ----------

<#lt>//********************************************************
<#lt>//#define WOLFSSL_SHAKE128  //Manually Commented, Not supported by Wolfcrypt
<#lt>#define WOLFSSL_SHAKE256 //Manually Added
<#lt>#define HAVE_BLAKE2S     //manually added
<#lt>#define HAVE_BLAKE2B     //manually added
<#lt>#define HAVE_CHACHA      //manually Added   
<#lt>#define HAVE_AES_KEYWRAP //manually added
<#lt>#define HAVE_ECC_DHE     //manually added
<#lt>#define WOLFCRYPT_HAVE_ECCSI //manually added
<#lt>#define WOLFSSL_AES_EAX //manually added
//*********************************************************


<#lt>//*********************************************************
<#lt>//#define WC_NO_RNG //when using RNG
<#lt>//#define WC_NO_HASHDRBG
<#lt>//#define HAVE_ECC_ENCRYPT
<#lt>//#define NO_RSA
<#lt>//#define NO_DH
<#lt>//#define NO_SIG_WRAPPER
<#lt>//#define NO_RSA  
<#lt>//**********************************************************

// ---------- FUNCTIONAL CONFIGURATION END ----------



// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/
