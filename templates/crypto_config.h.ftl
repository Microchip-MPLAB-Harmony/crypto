<#----------------------------------------------------------------------------
 Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.

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
----------------------------------------------------------------------------->

<#if cryptoMicrochip == true>

/*** Crypto Library Configuration ***/
#define WC_NO_HARDEN
#define NO_DSA
#define MICROCHIP_MPLAB_HARMONY
#define HAVE_MCAPI
#define WOLFSSL_IGNORE_FILE_WARN
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
<#if CONFIG_USE_3RDPARTY_WOLFSSL?? && CONFIG_USE_3RDPARTY_WOLFSSL == true>
<#-- Don't output anything if WOLFSSL is present and enabled -->
<#else>
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
    <#if cryptoCipher3DES == false>
        <#lt>#define NO_DES3
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
<#if cryptoRandom == false>
#define NO_RNG_TEST
</#if>
</#if>
<#--
/*******************************************************************************
 End of File
*/
-->

