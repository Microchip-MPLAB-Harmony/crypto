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


<#------------------------------------------------------------------------------ 
The USE_ defines indicate that the function has been selected to
     be included in the build
------------------------------------------------------------------------------->
<#-- HASH MD5 -->
//Selected HASH Functions
<#if crypto_md5 == true>
    <#if crypto_md5_hw == true>
        <#lt>#define USE_HASH_MD5_HW 
    <#else>
        <#lt>#define USE_HASH_MD5
        </#if>
    </#if>
<#-- HASH SHA1 -->
<#if crypto_sha1 == true>
    <#if crypto_sha1_hw == true>
        <#lt>#define USE_HASH_SHA1_HW 
    <#else>
        <#lt>#define USE_HASH_SHA1
        </#if>
    </#if>
<#-- HASH SHA2 -->
<#if crypto_sha2_224 == true>
    <#if crypto_sha2_224_hw == true>
        <#lt>#define USE_HASH_SHA2_224_HW 
    <#else>
        <#lt>#define USE_HASH_SHA2_224
        </#if>
    </#if>
<#if crypto_sha2_256 == true>
    <#if crypto_sha2_256_hw == true>
        <#lt>#define USE_HASH_SHA2_256_HW 
    <#else>
        <#lt>#define USE_HASH_SHA2_256
        </#if>
    </#if>
<#if crypto_sha2_384 == true>
    <#if crypto_sha2_384_hw == true>
        <#lt>#define USE_HASH_SHA2_384_HW 
    <#else>
        <#lt>#define USE_HASH_SHA2_384
        </#if>
    </#if>
<#if crypto_sha2_512 == true>
    <#if crypto_sha2_512_hw == true>
        <#lt>#define USE_HASH_SHA2_512_HW 
    <#else>
        <#lt>#define USE_HASH_SHA2_512
        </#if>
    </#if>
<#-- HASH SHA3 -->
<#if crypto_sha3_224 == true>
    <#if crypto_sha3_224_hw == true>
        <#lt>#define USE_HASH_SHA3_224_HW 
    <#else>
        <#lt>#define USE_HASH_SHA3_224
        </#if>
    </#if>
<#if crypto_sha3_256 == true>
    <#if crypto_sha3_256_hw == true>
        <#lt>#define USE_HASH_SHA3_256_HW 
    <#else>
        <#lt>#define USE_HASH_SHA3_256
        </#if>
    </#if>
<#if crypto_sha3_384 == true>
    <#if crypto_sha3_384_hw == true>
        <#lt>#define USE_HASH_SHA3_384_HW 
    <#else>
        <#lt>#define USE_HASH_SHA3_384
        </#if>
    </#if>
<#if crypto_sha3_512 == true>
    <#if crypto_sha3_512_hw == true>
        <#lt>#define USE_HASH_SHA3_512_HW 
    <#else>
        <#lt>#define USE_HASH_SHA3_512
        </#if>
    </#if>
<#-- HASH BLAKE -->
<#if crypto_blake_224 == true>
    <#if crypto_blake_224_hw == true>
        <#lt>#define USE_HASH_BLAKE_224_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE_224
        </#if>
    </#if>
<#if crypto_blake_256 == true>
    <#if crypto_blake56_hw == true>
        <#lt>#define USE_HASH_BLAKE_256_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE_256
        </#if>
    </#if>
<#if crypto_blake_384 == true>
    <#if crypto_blake_384_hw == true>
        <#lt>#define USE_HASH_BLAKE_384_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE_384
        </#if>
    </#if>
<#if crypto_blake_512 == true>
    <#if crypto_blake_512_hw == true>
        <#lt>#define USE_HASH_BLAKE_512_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE_512
        </#if>
    </#if>
<#-- HASH BLAKE2 -->
<#if crypto_blake2_224 == true>
    <#if crypto_blake2_224_hw == true>
        <#lt>#define USE_HASH_BLAKE2_224_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE2_224
        </#if>
    </#if>
<#if crypto_blake2_256 == true>
    <#if crypto_blake256_hw == true>
        <#lt>#define USE_HASH_BLAKE2_256_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE2_256
        </#if>
    </#if>
<#if crypto_blake2_384 == true>
    <#if crypto_blake2_384_hw == true>
        <#lt>#define USE_HASH_BLAKE2_384_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE2_384
        </#if>
    </#if>
<#if crypto_blake2_512 == true>
    <#if crypto_blake2_12_hw == true>
        <#lt>#define USE_HASH_BLAKE2_512_HW 
    <#else>
        <#lt>#define USE_HASH_BLAKE2_512
        </#if>
    </#if>
<#lt>// ---------- FUNCTIONAL CONFIGURATION END ----------
