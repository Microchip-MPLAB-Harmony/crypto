<#--
/*******************************************************************************
  Cryptographic Library Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    crypto_config.h

  Summary:
    Cryptographic Library.

  Description:
    This file contains the interface definition for the Crypto Library.
    It sets up the definitions required to add or remove elements of the
    library that the user has specified.
*******************************************************************************/

/*******************************************************************************
Copyright (c) 2018 released Microchip Technology Inc.  All rights reserved.

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
-->
/*** Crypto Library Configuration ***/
#define WC_NO_HARDEN
#define NO_DSA
#define MICROCHIP_MPLAB_HARMONY
#define HAVE_MCAPI
<#if maskFamily == "SAME70">
  <#lt>#define MICROCHIP_SAME70
  <#if cryptoHW == true>
    <#lt>#define WOLFSSL_MICROCHIP_SAME70
    <#if cryptoHashMD5 || cryptoHashSHA1 || cryptoHashSHA256 || cryptoHashSHA384 || cryptoHashSHA512 || cryptoRandom>
      <#lt>#define WOLFSSL_SAME70_HASH
    </#if>
  </#if>
<#else>
  <#lt>#define MICROCHIP_PIC32
  <#if cryptoHW == true>
    <#lt>#define WOLFSSL_MICROCHIP_PIC32MZ
    <#if cryptoHashMD5 || cryptoHashSHA1 || cryptoHashSHA256 || cryptoHashSHA384 || cryptoHashSHA512 || cryptoRandom>
      <#lt>#define WOLFSSL_PIC32MZ_HASH
    </#if>
  </#if>
</#if>
<#if CONFIG_USE_3RDPARTY_WOLFSSL!false == false>
    <#lt>#define NO_CERTS
    <#lt>#define NO_PWDBASED
    <#lt>#define NO_OLD_TLS
    <#if cryptoHashMD5 == false && cryptoCipherECC == false>
        <#lt>#define NO_MD5
    </#if>
    <#if cryptoHashSHA1 == false && cryptoCipherECC == false>
        <#lt>#define NO_SHA
    </#if>
    <#if cryptoCipherAES_CTR == false && cryptoCipherAES_CBC == false && cryptoCipherAES_ECB == false && cryptoCipherAES_GCM == false>
        <#lt>#define NO_AES
    </#if>
    <#if cryptoHashSHA256 == false && cryptoRandom == false>
        <#lt>#define NO_SHA256
        <#lt>#define WC_NO_RNG
    </#if>
    <#if cryptoHashSHA384 == true>
        <#lt>#define WOLFSSL_SHA384
    </#if>
    <#if cryptoHashSHA512 == true || cryptoHashSHA384 == true>
        <#lt>#define WOLFSSL_SHA512
    </#if>
    <#if cryptoCipherECC == true>
        <#lt>#define HAVE_ECC
    </#if>
    <#if cryptoCipherECC == false && cryptoCipherRSA == false>
        <#lt>#define NO_ASN
    <#else>
        <#lt>#define USE_FAST_MATH
    </#if>
    <#if cryptoHuffman == true>
        <#lt>#define HAVE_LIBZ
    </#if>
    <#if cryptoCipherRSA == false>
        <#lt>#define NO_RSA
    </#if>
    <#if cryptoHashHMAC == false && cryptoCipherECC == false>
        <#lt>#define NO_HMAC
    </#if>
</#if>
<#if cryptoCipherAES_CTR == true>
#define WOLFSSL_AES_COUNTER
</#if>
<#if cryptoRandom == true>
#define WOLFSSL_AES_DIRECT
</#if>
<#if cryptoRandom == false && cryptoCipherECC == false && cryptoCipherRSA == false>
#define NO_RNG
</#if>

<#--
/*******************************************************************************
 End of File
*/
-->

