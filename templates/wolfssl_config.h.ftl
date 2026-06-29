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
/*
Copyright (C) 2011-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

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

-->
    <#lt>/******************************************************************************/
    <#lt>/*wolfSSL TLS Layer Configuration*/
    <#lt>/******************************************************************************/

    <#lt>#define WOLFSSL_ALT_NAMES
    <#lt>#define WOLFSSL_DER_LOAD
    <#lt>#define KEEP_OUR_CERT
    <#lt>#define KEEP_PEER_CERT
    <#lt>#define HAVE_CRL_IO
    <#lt>#define HAVE_IO_TIMEOUT
    <#lt>#define TFM_NO_ASM
    <#lt>#define WOLFSSL_NO_ASM
    <#lt>#define SIZEOF_LONG_LONG 8
	<#lt>#define WOLFSSL_NO_SOCK
    <#lt>#define WOLFSSL_USER_IO
    <#lt>#define NO_WRITEV
    <#lt>#define MICROCHIP_TCPIP
    <#if wolfsslOsalHeapKeys>
        <#lt>#include "osal/osal.h"
        <#lt>#define XMALLOC_OVERRIDE
        <#lt>#define XMALLOC(s, h, type)  OSAL_Malloc((s))
        <#lt>#define XFREE(p, h, type)    OSAL_Free((p))
    </#if>
    <#if wolfsslFfdheGroup2048>
        <#lt>#define HAVE_FFDHE_2048
    </#if>    
    <#if wolfsslFfdheGroup3072>
        <#lt>#define HAVE_FFDHE_3072
    </#if>    
    <#if wolfsslFfdheGroup4096>
        <#lt>#define HAVE_FFDHE_4096
    </#if>    
    <#if wolfsslFfdheGroup6144>
        <#lt>#define HAVE_FFDHE_6144
    </#if>    
    <#if wolfsslFfdheGroup8192>
        <#lt>#define HAVE_FFDHE_8192
    </#if>    
    <#if wolfsslDTLS>
        <#lt>#define WOLFSSL_DTLS
    </#if>
    <#if wolfsslpwdkdf == false>
        <#lt>#define NO_PWDBASED
    </#if>
    <#if wolfsslTLS13 || wolfsslTlsEccCurvesExt || wolfsslTlsSni>
        <#lt>#define HAVE_TLS_EXTENSIONS
        <#if wolfsslTLS13>
            <#lt>#define WOLFSSL_TLS13
            <#lt>#define HAVE_SUPPORTED_CURVES
            <#if wolfsslPostHandshakeAuth>
                <#lt>#define WOLFSSL_POST_HANDSHAKE_AUTH
            </#if>
            <#if wolfsslHelloRetryCookie>
                <#lt>#define WOLFSSL_SEND_HRR_COOKIE
            </#if>
        <#elseif wolfsslTlsEccCurvesExt>
            <#lt>#define HAVE_SUPPORTED_CURVES
        </#if>
        <#if wolfsslTlsSni>
            <#lt>#define HAVE_SNI
        </#if>
        <#if wolfsslTlsAlpn>
            <#lt>#define HAVE_ALPN
			<#lt>#define USE_WOLF_STRTOK
        </#if>
    </#if>
    <#if !wolfsslTLS12>
        <#lt>#define WOLFSSL_NO_TLS12
    </#if>
    <#if wolfSslSessionCache=="Small">
        <#lt>#define SMALL_SESSION_CACHE
    <#elseif wolfSslSessionCache=="Big">
        <#lt>#define BIG_SESSION_CACHE
    <#elseif wolfSslSessionCache=="Huge">
        <#lt>#define HUGE_SESSION_CACHE
    <#elseif wolfSslSessionCache=="None">
        <#lt>#define NO_SESSION_CACHE
    </#if>
    <#if wolfsslSmallStackSupport> 
        <#lt>#define WOLFSSL_SMALL_STACK
    </#if>
    <#if wolfSslSaveCache>
        <#lt>#define PERSIST_SESSION_CACHE
    </#if>
    <#if wolfSslSaveCert>
        <#lt>#define PERSIST_CERT_CACHE
    </#if>
    <#if wolfSslKeyGen>
        <#lt>#define WOLFSSL_KEY_GEN
    </#if>
    <#if wolfsslEncryptedKeys>
        <#lt>#define WOLFSSL_ENCRYPTED_KEYS
    </#if>
    <#if wolfSslCertGen>
        <#lt>#define WOLFSSL_CERT_GEN
    </#if>
    <#if wolfSslCertReq>
        <#lt>#define WOLFSSL_CERT_REQ
    </#if>
    <#if !wolfsslNoErrorStrings>
        <#lt>#define NO_ERROR_STRINGS
		<#lt>#define WOLFSSL_MAX_ERROR_SZ 64 // Fix Mandatory Misra 21.18 caused by removing error strings with defining NO_ERROR_STRINGS
    </#if>
    <#if !wolfsslNoOldTls>
        <#lt>#define NO_OLD_TLS
    <#else>
        <#lt>#define WOLFSSL_ALLOW_TLSV10
        <#lt>#define WOLFSSL_ALLOW_SSLV3
    </#if>
    <#if wolfsslUseFastMath>
        <#lt>#define USE_FAST_MATH
    </#if>
    <#if !wolfsslClientSupport>
        <#lt>#define NO_WOLFSSL_CLIENT
    </#if>
    <#if !wolfsslServerSupport>
        <#lt>#define NO_WOLFSSL_SERVER
    </#if>
<#-- 
/*******************************************************************************
 End of File
*/
-->