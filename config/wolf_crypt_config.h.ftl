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

/*** wolfCrypt Library Configuration ***/
#define MICROCHIP_PIC32
#define MICROCHIP_MPLAB_HARMONY
#define MICROCHIP_MPLAB_HARMONY_3
#define HAVE_MCAPI
#define SIZEOF_LONG_LONG 8
#define WOLFSSL_USER_IO
#define NO_WRITEV
#define NO_FILESYSTEM
#define USE_FAST_MATH
#define NO_PWDBASED
#define HAVE_MCAPI
#define WOLF_CRYPTO_CB  // provide call-back support
<#if wolfcrypt_sw_cb == true>
        <#lt>#define WOLF_CRYPTO_CB_ONLY_ECC
        <#lt>#define WOLF_CRYPTO_CB_ONLY_RSA
    </#if>
<#if wolfssl_included?has_content == false || wolfssl_included == false>
    <#lt>#define WOLFCRYPT_ONLY
</#if>
<#-- Will be true when "Use Hardware Cryptography?" is checked -->
<#if wolfcrypt_hw == true>
    <#if wolfcryptCoreSeries?starts_with("PIC32M")>
        <#lt>#define WOLFSSL_MICROCHIP_PIC32MZ
    <#else>
        <#lt>#define WOLFSSL_HAVE_MCHP_HW_CRYPTO
    </#if>
    <#if wolfCryptAdditionalHwDefines?has_content>
        <#lt>// ---------- CRYPTO HARDWARE MANIFEST START ----------
        <#list wolfCryptAdditionalHwDefines?split(", ") as val>
            <#lt>#define ${val}
        </#list>
        <#lt>// ---------- CRYPTO HARDWARE MANIFEST END ----------
        <#lt>#undef WOLFSSL_HAVE_MIN
        <#lt>#undef WOLFSSL_HAVE_MAX
    </#if>
<#else>
    <#if wolfcryptCoreSeries?starts_with("PIC32M")>
		<#lt>#if (__XC32_VERSION > 100000000)
        <#lt>#define WOLFSSL_HAVE_MIN
        <#lt>#define WOLFSSL_HAVE_MAX
		<#lt>#endif
        <#lt>#undef WOLFSSL_HAVE_MIN
        <#lt>#undef WOLFSSL_HAVE_MAX
    </#if>
</#if>
<#lt>// ---------- FUNCTIONAL CONFIGURATION START ----------
<#if wolfcrypt_aes_small_table == true>
    <#lt>#define WOLFSSL_AES_SMALL_TABLES
</#if>
<#if wolfcrypt_md2 == true>
    <#lt>#define WOLFSSL_MD2
</#if>
<#if wolfcrypt_md4 == false>
    <#lt>#define NO_MD4
</#if>
<#assign hmacPrereqs=false>
<#assign pic32MzHash=false>
<#if wolfcrypt_md5 == false>
    <#lt>#define NO_MD5
<#else>
    <#assign hmacPrereqs=true>
    <#if wolfcrypt_hw == true && wolfcrypt_md5_hw == true>
        <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#lt>#define WOLFSSL_PIC32MZ_HASH
            <#assign pic32MzHash=true>
        <#else>
            <#lt>#define WOLFSSL_HAVE_MCHP_HW_MD5
        </#if>
    </#if>
</#if>
<#if wolfcrypt_sha1 == false>
    <#lt>#define NO_SHA // specifically, no SHA1 (legacy name)
<#else>
    <#assign hmacPrereqs=true>
    <#if wolfcrypt_hw == true && wolfcrypt_sha1_hw == true || pic32MzHash == true>
        <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#lt>#define WOLFSSL_PIC32MZ_HASH
            <#assign pic32MzHash=true>
        <#else>
            <#lt>#define WOLFSSL_HAVE_MCHP_HW_SHA1
        </#if>
    </#if>
</#if>
<#if wolfcrypt_sha256 == false>
    <#lt>#define NO_SHA256
    <#lt>#define NO_SHA224
<#else>
    <#-- because of legacy, WOLFSSL_SHA256 or HAVE_SHA256 are never asserted -->
    <#assign hmacPrereqs=true>
    <#if wolfcrypt_hw == true && wolfcrypt_sha264_hw == true || pic32MzHash == true>
        <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#lt>#define WOLFSSL_PIC32MZ_HASH
            <#assign pic32MzHash=true>
        <#else>
            <#if wolfcrypt_sha224 == true>
                <#lt>#define WOLFSSL_SHA224
            </#if>
            <#lt>#define WOLFSSL_HAVE_MCHP_HW_SHA264
        </#if>
    <#else>
        <#if wolfcrypt_sha224 == true>
            <#lt>#define WOLFSSL_SHA224
        </#if>
    </#if>
    <#if wolfcrypt_sha224 == false>
            <#lt>#define NO_SHA224
    </#if>
</#if>
<#if wolfcryptCoreSeries?starts_with("PIC32M")>
    <#if wolfcrypt_hw == true && pic32MzHash == false>
        <#lt>#define NO_PIC32MZ_HASH
    </#if>
</#if>
<#if wolfcrypt_sha384 == true || wolfcrypt_sha512>
    <#assign hmacPrereqs=true>
    <#if wolfcrypt_sha384 == true>
        <#lt>#define WOLFSSL_SHA384
    </#if>
    <#if wolfcrypt_sha512 == true>
        <#lt>#define WOLFSSL_SHA512
        <#lt>#define HAVE_SHA512
    <#else>
        <#lt>#define NO_SHA512
    </#if>
    <#if wolfcrypt_sha2128_hw == true>
        <#lt>#define WOLFSSL_HAVE_MCHP_HW_SHA2128
    </#if>
</#if>
<#if wolfcrypt_sha3 == "small">
    <#lt>#define WOLFSSL_SHA3_SMALL
    <#assign hmacPrereqs=true>
<#elseif wolfcrypt_sha3 == "enabled">
    <#lt>#define WOLFSSL_SHA3
    <#assign hmacPrereqs=true>
</#if>
<#if wolfcrypt_blake2b == true>
    <#lt>#define WOLFSSL_SHA3
    <#lt>#define HAVE_BLAKE2
</#if>
<#if wolfcrypt_ripemd == true>
    <#lt>#define WOLFSSL_RIPEMD
</#if>
<#if hmacPrereqs==true && wolfcrypt_hmac == true>
    <#if wolfcrypt_hkdf==true>
        <#lt>#define HAVE_HKDF
    </#if>
<#else>
    <#lt>#define NO_HMAC
</#if>
<#if wolfcrypt_tdes==true>
    <#if wolfcrypt_tdes_ecb == true>
        <#lt>#define WOLFSSL_DES_ECB
    </#if>
    <#if wolfcrypt_hw == true && wolfcrypt_tdes_hw == true>
        <#if wolfcryptCoreSeries?starts_with("PIC32M")>
        <#else>
            <#lt>#define WOLFSSL_HAVE_MCHP_3DES
            <#if wolfcrypt_tdes_cbc_hw == true>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_3DES_CBC
            </#if>
            <#if wolfcrypt_tdes_ecb == true && wolfcrypt_tdes_ecb_hw == true>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_3DES_EBC
            </#if>
        </#if>
    </#if>
<#else>
    <#lt>#define NO_DES3
</#if>
<#if wolfcrypt_aes == false>
    <#lt>#define NO_AES
<#else>
    <#if wolfcrypt_aes_128 == true>
        <#lt>#define WOLFSSL_AES_128
        <#if wolfcrypt_hw == true && wolfcrypt_aes_hw == true && cryptoCrya_U2803 == true>
            <#-- limit key size if AES HW is enabled and this is a SAML11 -->
            <#lt>#define AES_MAX_KEY_SIZE 128 // limited CRYA in SAML11
        </#if>
    <#else>
        <#-- disabling and enabling must be mutually exclusive -->
        <#lt>#define NO_AES_128
    </#if>
    <#if wolfcrypt_aes_192 == false 
         || (wolfcrypt_hw == true && wolfcrypt_aes_hw == true 
                && (cryptoCrya_U2803 == true || cryptoCrya_03710 == true))>
        <#-- disable if AES HW is enabled and this is a SAML11 or PIC32CM'Lx -->
        <#lt>#define NO_AES_192 // not supported by HW accelerator
    <#else>
        <#-- disabling and enabling must be mutually exclusive -->
        <#lt>#define WOLFSSL_AES_192
    </#if>
    <#if wolfcrypt_aes_256 == false 
         || (wolfcrypt_hw == true && wolfcrypt_aes_hw == true 
                && (cryptoCrya_U2803 == true || cryptoCrya_03710 == true))>
        <#-- disable if AES HW is enabled and this is a SAML11 or PIC32CM'Lx -->
        <#lt>#define NO_AES_256 // not supported by HW accelerator
    <#else>
        <#-- disabling and enabling must be mutually exclusive -->
        <#lt>#define WOLFSSL_AES_256
    </#if>
    <#lt>#define WOLFSSL_AES_DIRECT
    <#lt>#define HAVE_AES_DECRYPT
    <#if wolfcrypt_hw == true && wolfcrypt_aes_hw == true>
        <#if wolfcryptCoreSeries?starts_with("PIC32M")>
        <#else>
            <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_DIRECT
        </#if>
    </#if>
    <#if wolfcrypt_aes_ecb == true>
        <#lt>#define HAVE_AES_ECB
        <#if wolfcrypt_hw == true && wolfcrypt_aes_ecb_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#elseif cryptoCrya_U2803 == true>
            <#-- CRYA is 1-block only so keep aes.c/wc_AesEcbEncrypt() to iterate -->
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_ECB
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_cbc == true>
        <#lt>#define HAVE_AES_CBC
        <#if wolfcrypt_hw == true && wolfcrypt_aes_cbc_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_CBC
            </#if>
        </#if>
    <#else>
        <#-- disabling and enabling must be mutually exclusive -->
        <#-- (only the CBC submode requires this inhibit) -->
        <#lt>#define NO_AES_CBC
    </#if>
    <#if wolfcrypt_aes_ctr == true>
        <#lt>#define WOLFSSL_AES_COUNTER
        <#if wolfcrypt_hw == true && wolfcrypt_aes_ctr_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_CTR
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_cfb == true>
        <#lt>#define WOLFSSL_AES_CFB
        <#if wolfcrypt_hw == true && wolfcrypt_aes_cfb_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_CFB
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_ofb == true>
        <#lt>#define WOLFSSL_AES_OFB
        <#if wolfcrypt_hw == true && wolfcrypt_aes_ofb_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_OFB
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_gcm == true>
        <#lt>#define HAVE_AESGCM
        <#if wolfcrypt_hw == true && wolfcrypt_aes_gcm_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_GCM
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_xts == true>
        <#lt>#define WOLFSSL_AES_XTS
        <#if wolfcrypt_hw == true && wolfcrypt_aes_xts_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_XTS
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_ccm == true>
        <#lt>#define HAVE_AESCCM
        <#if wolfcrypt_hw == true && wolfcrypt_aes_ccm_hw == true && wolfcrypt_aes_hw == true>
            <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#else>
                <#lt>#define WOLFSSL_HAVE_MCHP_HW_AES_CCM
            </#if>
        </#if>
    </#if>
    <#if wolfcrypt_aes_cmac == true>
        <#lt>#define WOLFSSL_CMAC
    </#if>
</#if>
<#if wolfcrypt_camellia == true>
    <#lt>#define HAVE_CAMELLIA
</#if>
<#if wolfcrypt_idea == true>
    <#lt>#define HAVE_IDEA
</#if>
<#if wolfcrypt_arc4 == false>
    <#lt>#define NO_RC4
</#if>
<#if wolfcrypt_hc128 == true>
    <#lt>#define HAVE_HC128
<#else>
    <#lt>#define NO_HC128
</#if>
<#if wolfcrypt_rabbit == true>
    <#lt>#define HAVE_RABBIT
<#else>
    <#lt>#define NO_RABBIT
</#if>
<#if wolfcrypt_ecc == true>
    <#lt>#define HAVE_ECC
    <#if wolfcrypt_ecc_hw == true && wolfcrypt_hw == true>
        <#lt>#define WOLFSSL_HAVE_MCHP_HW_ECC
    </#if>
    <#if wolfcrypt_kdf == true>
        <#lt>#define HAVE_X963_KDF
    </#if>
    <#if wolfcrypt_shamir == true>
        <#lt>#define ECC_SHAMIR
    </#if>
    <#if wolfcrypt_customcurves == true>
        <#lt>#define WOLFSSL_CUSTOM_CURVES
    </#if>
    <#if wolfcrypt_curve25519 == "small">
        <#lt>#define CURVE25519_SMALL
    <#elseif wolfcrypt_curve25519 == "no 128 bit">
        <#lt>#define NO_CURVED25519_128BIT
    <#elseif wolfcrypt_curve25519 == "supported">
        <#lt>#define HAVE_CURVE25519
    </#if>
    <#if wolfcrypt_curve25519 != "unsupported" && wolfcrypt_sha512 == true>
        <#lt>#define HAVE_ED25519
        <#if wolfcrypt_curve25519 == "small">
            <#lt>#define ED25519_SMALL
        </#if>
    </#if>
    <#if wolfcrypt_fpecc == true>
        <#lt>#define FP_ECC
    </#if>
    <#if wolfcrypt_eccencrypt == true && wolfcrypt_hkdf == true>
        <#lt>#define HAVE_ECC_ENCRYPT
    </#if>
     <#if wolfcrypt_eccnosign == true>
        <#lt>#define NO_ECC_SIGN
    </#if>
     <#if wolfcrypt_eccnoverify == true>
        <#lt>#define NO_ECC_VERIFY
    </#if>
</#if>
<#if wolfcrypt_dh == true>
    <#lt>#define HAVE_DH
    <#if wolfcrypt_dh_anon == true>
        <#lt>#define HAVE_ANON
    </#if>
    <#if wolfcrypt_dh_old_prime == true>
        <#lt>#define WOLFSSL_OLD_PRIME_CHECK
    </#if>
<#else>
    <#lt>#define NO_DH
</#if>
<#if wolfcrypt_dsa==false>
    <#lt>#define NO_DSA
</#if>
<#if wolfcrypt_rsa == true>
    <#if wolfcrypt_rsa_hw == true && wolfcrypt_hw == true>
        <#lt>#define WOLFSSL_HAVE_MCHP_HW_RSA
    </#if>
	<#assign fpMaxBits=wolfcrypt_certBuffMaxSize/>
	<#if lib_wolfssl?has_content && lib_wolfssl.wolfsslFfdheGroup8192?has_content && lib_wolfssl.wolfsslFfdheGroup8192  && fpMaxBits < 16384>
		<#assign fpMaxBits=16384/>
	<#elseif lib_wolfssl?has_content && lib_wolfssl.wolfsslFfdheGroup6144?has_content && lib_wolfssl.wolfsslFfdheGroup6144  && fpMaxBits < 12288>
		<#assign fpMaxBits=12288/>
	<#elseif lib_wolfssl?has_content && lib_wolfssl.wolfsslFfdheGroup4096?has_content && lib_wolfssl.wolfsslFfdheGroup4096  && fpMaxBits < 8192>
		<#assign fpMaxBits=8192/>
	<#elseif lib_wolfssl?has_content && lib_wolfssl.wolfsslFfdheGroup3072?has_content && lib_wolfssl.wolfsslFfdheGroup3072  && fpMaxBits < 6144>
		<#assign fpMaxBits=6144/>
	<#elseif lib_wolfssl?has_content && lib_wolfssl.wolfsslFfdheGroup2048?has_content && lib_wolfssl.wolfsslFfdheGroup2048  && fpMaxBits < 4096>
		<#assign fpMaxBits=4096/>
	</#if>
    <#lt>#define FP_MAX_BITS ${fpMaxBits}
    <#if wolfcrypt_certBuffMaxSize == 4096>
        <#lt>#define USE_CERT_BUFFERS_2048
    <#else>
        <#lt>#define USE_CERT_BUFFERS_1024
    </#if>
    <#if wolfcrypt_oaep == false>
        <#lt>#define WC_NO_RSA_OAEP
    </#if>
    <#if wolfcrypt_rsapub == true>
        <#lt>#define WOLFSSL_RSA_PUBLIC_ONLY
        <#if wolfcrypt_rsainline = true>
            <#lt>#define WOLFSSL_RSA_VERIFY_ONLY
            <#lt>#define WOLFSSL_RSA_VERIFY_INLINE
            <#lt>#define NO_SIG_WRAPPER
        </#if>
    </#if>
    <#if wolfcrypt_rsaPss == true>
        <#lt>#define WC_RSA_PSS
    </#if>
    <#if cryptoRsaStatic == true>
        <#lt>#define WOLFSSL_STATIC_RSA
    </#if>
<#else>
    <#lt>#define NO_RSA
</#if>
#define NO_DEV_RANDOM
<#if wolfcrypt_random == true>
    <#if wolfcrypt_hw == true && wolfcrypt_random_hw == true>
        <#if wolfcryptCoreSeries?starts_with("PIC32M")>
            <#lt>#define WOLFSSL_PIC32MZ_RNG
        <#else>
        <#lt>#define WOLFSSL_HAVE_MCHP_HW_RANDOM
        </#if>
    </#if>
    <#if wolfcrypt_hashdrng == true && wolfcrypt_sha256 == true>
        <#lt>#define HAVE_HASHDRBG
    <#else>
        <#lt>#define WC_NO_HASHDRBG
    </#if>
    <#if wolfcrypt_randomtest == false>
        <#lt>#define NO_RNG_TEST
    </#if>
<#else>
    <#lt>#define WC_NO_RNG
    <#lt>#define WC_NO_HASHDRBG
</#if>
<#if wolfcrypt_harden == false>
    <#lt>#define WC_NO_HARDEN
<#else>
    <#lt>#define TFM_TIMING_RESISTANT
    <#lt>#define ECC_TIMING_RESISTANT
    <#lt>#define WC_RSA_BLINDING
</#if>
<#if wolfSslRTOSSupport == "Single Threaded">
    <#lt>#define SINGLE_THREADED
<#elseif wolfSslRTOSSupport == "FreeRTOS">
    <#lt>#define FREERTOS
</#if>
<#if wolfcrypt_asn1 == true>
    <#if wolfcrypt_certgen == true>
        <#lt>#define WOLFSSL_CERT_GEN
        <#if wolfcrypt_certrequestgen == true>
            <#lt>#define WOLFSSL_CERT_REQ
            <#if wolfcrypt_certrequestext == true>
                <#lt>#define WOLFSSL_CERT_EXT
            </#if>            
        </#if>
    </#if>
<#else>
    <#lt>#define NO_ASN
</#if>
<#if wolfcrypt_signature == false>
    <#lt>#define NO_SIG_WRAPPER
</#if>
<#if wolfcrypt_keygen == true>
    <#lt>#define WOLFSSL_KEY_GEN
</#if>
<#if wolfcrypt_errorstrings == false>
    <#lt>#define NO_ERROR_STRINGS
</#if>
<#if wolfcrypt_memorycallbacks == true>
    <#if wolfcrypt_memorytracking == true>
        #define USE_WOLFSSL_MEMORY
        #define WOLFSSL_TRACK_MEMORY
    </#if>
    <#if wolfcrypt_memorylogging == true>
        #define WOLFSSL_MEMORY_LOG
    </#if>
    <#if wolfcrypt_stacklogging == true>
        #define WOLFSSL_STACK_LOG
    </#if>
<#else>
    <#lt>#define NO_WOLFSSL_MEMORY
</#if>
<#if wolfcrypt_debug == true>
    <#lt>#define DEBUG
    <#lt>#define DEBUG_WOLFSSL
</#if>
<#if wolfcrypt_havezlib == true && wolfcrypt_supportcompression == true>
    <#lt>#define HAVE_LIBZ
</#if>
<#if lib_wolfssl?has_content>
    <#if (lib_wolfssl.wolfsslLoadTNGTLSCert)?has_content && ((lib_wolfssl.wolfsslLoadTNGTLSCert) == true)>
        <#lt>/*Enabling TNGTLS certificate loading*/
        <#if !lib_wolfssl.wolfsslTlsEccCurvesExt || !lib_wolfssl.wolfsslTLS13> 
            <#lt>#define HAVE_SUPPORTED_CURVES
        </#if>
        <#lt>#define WOLFSSL_ATECC608A
        <#lt>#define WOLFSSL_ATECC_TNGTLS
        <#lt>#define WOLFSSL_ATECC_ECDH_IOENC
        <#lt>#define HAVE_PK_CALLBACKS
        <#lt>#define WOLFSSL_ATECC508A_NOIDLE
    </#if>
</#if>
<#lt>// ---------- FUNCTIONAL CONFIGURATION END ----------
