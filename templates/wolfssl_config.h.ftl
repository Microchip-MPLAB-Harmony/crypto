<#--
/*******************************************************************************
  Application Header

  File Name:
  wolfssl_config.h.ftl

  Summary:
 config file for wolfSSL to avoid custom build options

  Description:
 config file for wolfSSL to avoid custom build options
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2018 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END


-->
<#lt>/******************************************************************************/
<#lt>//Crypto V4 Common Crypto API - WolfCrypt Library Support
<#lt>/******************************************************************************/
#define CRYPTO_WOLFCRYPT_SUPPORT_ENABLE

-->
<#lt>/******************************************************************************/
<#lt>/*wolfSSL TLS Layer Configuration*/
<#lt>/******************************************************************************/

/*** wolfCrypt Library Configuration ***/
<#lt>#define MICROCHIP_PIC32
<#lt>#define MICROCHIP_MPLAB_HARMONY
<#lt>#define MICROCHIP_MPLAB_HARMONY_3
<#lt>#define HAVE_MCAPI
<#lt>#define SIZEOF_LONG_LONG 8
<#lt>#define WOLFSSL_USER_IO
<#lt>#define NO_WRITEV
<#lt>#define NO_FILESYSTEM
<#lt>#define NO_PWDBASED

//Math Model Defines
<#lt>#define USE_FAST_MATH
<#lt>#define WOLFSSL_SP_MATH_ALL   //As recommended by WolfSSL (Garski) 
<#lt>#define WOLFSSL_SP_MATH       //Using this to declare wolfmath functions: 
                                   //mp_reverse used by fp_to_unsigned_bin (tfm.c)
                                   //get_digit_count,get_digit in ecc.c 
<#lt>#define WOLFSSL_HAVE_SP_RSA   //Needed when WOFSSL_SP_MATH defined
<#lt>#define WOLFSSL_SP_NO_256     //To prevent usage of SP functions defined by this: 
                                   //    #if defined(HAVE_FIPS_VERSION) && HAVE_FIPS_VERSION == 2 
                                   //    && ( defined(WOLFSSL_SP_ARM32_ASM) || defined(WOLFSSL_SP_ARM64_ASM) ) 
//#define WOLFSSL_SP_ARM32_ASM //Dependent on MCU Arch.

<#lt>#define WOLF_CRYPTO_CB  // provide call-back support
<#lt>#define WOLFCRYPT_ONLY
//xxx

// ---------- FUNCTIONAL CONFIGURATION START ----------
<#lt>#define WOLFSSL_AES_SMALL_TABLES
<#lt>#define WOLFSSL_SHA224
<#lt>#define WOLFSSL_SHA384
<#lt>#define WOLFSSL_SHA512
<#lt>#define HAVE_SHA512
<#lt>#define WOLFSSL_AES_128
<#lt>#define WOLFSSL_AES_192
<#lt>#define WOLFSSL_AES_256
<#lt>#define WOLFSSL_AES_DIRECT
<#lt>#define HAVE_AES_DECRYPT
<#lt>#define HAVE_AES_ECB
<#lt>#define HAVE_AES_CBC
<#lt>#define HAVE_AES_EXT

<#lt>#define WOLFSSL_AES_COUNTER
<#lt>#define WOLFSSL_AES_CFB
<#lt>#define WOLFSSL_AES_OFB
<#lt>#define HAVE_AESGCM
<#lt>#define WOLFSSL_AES_XTS
<#lt>#define HAVE_AESCCM
<#lt>#define WOLFSSL_AES_EAX 

//<#lt>#define WOLFSSL_CMAC
//<#lt>#define NO_RC4
//<#lt>#define NO_HC128
//<#lt>#define NO_RABBIT
//<#lt>#define HAVE_ECC
//<#lt>#define NO_DH
<#lt>#define FP_MAX_BITS 4096
<#lt>#define USE_CERT_BUFFERS_2048
<#lt>#define NO_DEV_RANDOM
<#lt>#define HAVE_HASHDRBG
<#lt>#define WC_NO_HARDEN
<#lt>#define SINGLE_THREADED
<#lt>#define NO_SIG_WRAPPER
<#lt>#define NO_ERROR_STRINGS
<#lt>#define NO_WOLFSSL_MEMORY

<#-- 
/*******************************************************************************
 End of File
*/
-->
