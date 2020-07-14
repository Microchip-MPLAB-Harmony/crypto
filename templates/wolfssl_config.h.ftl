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
    <#lt>/*wolfSSL TLS Layer Configuration*/
    <#lt>/******************************************************************************/

    <#lt>#define WOLFSSL_ALT_NAMES
    <#lt>#define WOLFSSL_DER_LOAD
    <#lt>#define KEEP_OUR_CERT
    <#lt>#define KEEP_PEER_CERT
    <#lt>#define HAVE_CRL_IO
    <#lt>#define HAVE_IO_TIMEOUT
    <#lt>#define HAVE_FFDHE_2048
    <#lt>#define HAVE_FFDHE_3072
    <#lt>#define HAVE_FFDHE_4096
    <#lt>#define HAVE_FFDHE_6144
    <#lt>#define HAVE_FFDHE_8192
    <#lt>#define TFM_NO_ASM
    <#lt>#define WOLFSSL_NO_ASM
    <#lt>#define SIZEOF_LONG_LONG 8
    <#lt>#define WOLFSSL_USER_IO
    <#lt>#define NO_WRITEV
    <#lt>#define MICROCHIP_TCPIP

    <#if wolfsslOsalHeapKeys>
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

    <#if wolfsslTLS13>
        <#lt>#define WOLFSSL_TLS13
        <#lt>#define HAVE_TLS_EXTENSIONS
        <#lt>#define HAVE_SUPPORTED_CURVES
        <#if wolfsslPostHandshakeAuth>
            <#lt>#define WOLFSSL_POST_HANDSHAKE_AUTH
        </#if>
    <#elseif wolfsslTlsSni || wolfsslTlsEccCurvesExt>
        <#lt>#define HAVE_TLS_EXTENSIONS
        <#if wolfsslTlsEccCurvesExt>
            <#lt>#define HAVE_SUPPORTED_CURVES
        </#if>
        <#if wolfsslTlsSni>
            <#lt>#define HAVE_SNI
        </#if>
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
    
    <#if wolfsslpwdkdf == false> 
        <#lt>#define NO_PWDBASED
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
    </#if>
    
    <#if wolfsslNoOldTls>
        <#lt>#define NO_OLD_TLS
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