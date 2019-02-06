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


/*** Crypto Library Configuration ***/
#define WC_NO_HARDEN
#define NO_DSA
#define MICROCHIP_MPLAB_HARMONY
#define HAVE_MCAPI
#define WOLFSSL_IGNORE_FILE_WARN

#define MICROCHIP_MPLAB_HARMONY
#define MICROCHIP_MPLAB_HARMONY_3

<#if CONFIG_USE_3RDPARTY_WOLFSSL?? && CONFIG_USE_3RDPARTY_WOLFSSL == true>
<#-- Don't output anything if WOLFSSL is present and enabled -->
<#else>
    <#lt>#define SIZEOF_LONG_LONG 8
    <#lt>#define SINGLE_THREADED
    <#lt>#define WOLFSSL_USER_IO
    <#lt>#define NO_WRITEV
    <#lt>#define NO_DEV_RANDOM
    <#lt>#define NO_FILESYSTEM
    <#lt>#define USE_FAST_MATH
    <#lt>#define TFM_TIMING_RESISTANT
    <#lt>#define USE_CERT_BUFFERS_2048
    <#if cryptoCoreSeries?starts_with("PIC32M")>
        <#lt>#define NO_BIG_INT
    <#else>
    </#if>
    <#if cryptoHashMD5 == false && cryptoCipherECC == false>
        <#lt>#define NO_MD5
    </#if>
    <#if cryptoHashSHA1 == false && cryptoCipherECC == false>
        <#lt>#define NO_SHA
    <#elseif cryptoHashSHA1 == true && cryptoHW == true && cryptoHaveHwSha1 == true>
        <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_SHA1
    </#if>
    <#if cryptoCipherAES_CTR == false && cryptoCipherAES_CBC == false && cryptoCipherAES_ECB == false && cryptoCipherAES_GCM == false>
        <#lt>#define NO_AES
    <#else>
        <#if cryptoHaveHwAes == true && cryptoHW == true>
            <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_AES
        </#if>
        <#if cryptoCipherAES_CTR == true>
            <#lt>#define WOLFSSL_AES_COUNTER
        </#if>
        <#if cryptoCipherAES_ECB == true>
            <#lt>#define HAVE_AES_ECB
        </#if>
        <#if cryptoCipherAES_CBC == true>
            <#lt>#define HAVE_AES_CBC
        </#if>
        <#if cryptoCipherAES_GCM == true>
            <#lt>#define HAVE_AESGCM
        </#if>
    </#if>
    <#if cryptoHashSHA256 == false && cryptoRandom == false>
        <#lt>#define NO_SHA256
        <#lt>#define WC_NO_RNG
    <#elseif cryptoHashSHA256 == true && cryptoHW == true && cryptoHaveHwSha256 == true>
        <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_SHA256
        <#lt>#define CONFIG_HAVE_XDMAC
    </#if>
    <#if cryptoHaveHwRng == true && cryptoRandom == true && cryptoHW == true>
        <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_RNG
    </#if>
    <#if cryptoHashSHA224 == true>
        <#lt>#define WOLFSSL_SHA224
        <#if cryptoHW == true && cryptoHaveHwSha224 == true>
            <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_SHA224
        </#if>
    </#if>
    <#if cryptoHashSHA512 == true || cryptoHashSHA384 == true>
        <#lt>#define WOLFSSL_SHA512
        <#if cryptoHashSHA384 == true>
            <#lt>#define WOLFSSL_SHA384
            <#if cryptoHW == true && cryptoHaveHwSha384 == true>
                <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_SHA384
            </#if>
        </#if>
        <#if cryptoHashSHA512 == true>
            <#if cryptoHW == true && cryptoHaveHwSha512 == true>
                <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_SHA512
            </#if>
        </#if>
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
    <#else>
        <#lt>#define WOLFSSL_STATIC_RSA
        <#lt>#define USE_CERT_BUFFERS_2048
    </#if>
    <#if cryptoHashHMAC == false && cryptoCipherECC == false>
        <#lt>#define NO_HMAC
    </#if>
    <#if cryptoCipher3DES == false>
        <#lt>#define NO_DES3
    </#if>
</#if>
<#if cryptoCipherAES_CBC == false>
#define NO_AES_CBC
</#if>
<#if cryptoCipherAES_CTR == true>
#define WOLFSSL_AES_COUNTER
    <#if cryptoHW == true >
        <#lt>#define HAVE_MICROCHIP_HARMONY3_HW_AES
    </#if>
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
<#if cryptoHW == true>
    <#if cryptAdditionalHwDefines?has_content>
        <#list cryptAdditionalHwDefines?split(", ") as val>
            <#lt>#define ${val}
        </#list>
    </#if>
</#if>
<#--
/*******************************************************************************
 End of File
*/
-->

