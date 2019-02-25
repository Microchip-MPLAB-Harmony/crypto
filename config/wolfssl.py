#/*****************************************************************************
# Copyright (C) 2018-2019 Microchip Technology Inc. and its subsidiaries.
#
# Microchip Technology Inc. and its subsidiaries.
#
# Subject to your compliance with these terms, you may use Microchip software 
# and any derivatives exclusively with Microchip products. It is your 
# responsibility to comply with third party license terms applicable to your 
# use of third party software (including open source software) that may 
# accompany Microchip software.
#
# THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
# EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
# WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
# PURPOSE.
#
# IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
# INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
# WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
# BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
# FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
# ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
# THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
#*****************************************************************************/


def instantiateComponent(wolfsslComponent):
    wolfssl = wolfsslComponent.createBooleanSymbol("wolfssl", None)
    wolfssl.setLabel("Use wolfSSL?")
    wolfssl.setDescription("Enables wolfSSL")
    wolfssl.setVisible(False)
    wolfssl.setDefaultValue(True)

    wolfsslDebug = wolfsslComponent.createBooleanSymbol("wolfssl_debug", None)
    wolfsslDebug.setLabel("Enable Debug Messaging")
    wolfsslDebug.setVisible(True)
    
    wolfsslProtocolMenu = wolfsslComponent.createMenuSymbol("wolfssl_protocol_menu", None)
    wolfsslProtocolMenu.setLabel("Protocol and Key Exchange")
    wolfsslProtocolMenu.setVisible(True)

    wolfsslDTLS = wolfsslComponent.createBooleanSymbol("wolfsslDTLS", wolfsslProtocolMenu)
    wolfsslDTLS.setLabel("DTLS")
    wolfsslDTLS.setDescription("Enables DTLS")
    wolfsslDTLS.setDefaultValue(True)
    wolfsslDTLS.setVisible(True)

    wolfsslTLSMenu = wolfsslComponent.createMenuSymbol("wolfssl_tls_menu", wolfsslProtocolMenu)
    wolfsslTLSMenu.setLabel("TLS")
    wolfsslTLSMenu.setVisible(True)
    
    wolfsslTLS13 = wolfsslComponent.createBooleanSymbol("wolfsslTLS13", wolfsslTLSMenu)
    wolfsslTLS13.setLabel("TLS 1.3 Support")
    wolfsslTLS13.setDescription("Enable TLS 1.3 Support")
    wolfsslTLS13.setDefaultValue(False)
    wolfsslTLS13.setVisible(True)
    
    wolfsslTlsPostAuth = wolfsslComponent.createBooleanSymbol("wolfsslPostHandshakeAuth", wolfsslTLS13)
    wolfsslTlsPostAuth.setLabel("Post Handshake Authentication")
    wolfsslTlsPostAuth.setDescription("Enable Post-handshake Authentication")
    wolfsslTlsPostAuth.setDefaultValue(False)
    wolfsslTlsPostAuth.setVisible(True)
    
    wolfsslTlsHelloRetryCookie = wolfsslComponent.createBooleanSymbol("wolfsslHelloRetryCookie", wolfsslTLS13)
    wolfsslTlsHelloRetryCookie.setLabel("Hello Retry Request Cookie")
    wolfsslTlsHelloRetryCookie.setDescription("Enable the server to send Cookie Extension in HRR with state")
    wolfsslTlsHelloRetryCookie.setDefaultValue(False)
    wolfsslTlsHelloRetryCookie.setVisible(True)
    
    wolfsslHarden = wolfsslComponent.createBooleanSymbol("wolfsslHarden", None)
    wolfsslHarden.setLabel("Timing Resistance and Blinding")
    wolfsslHarden.setDescription("Enable Hardened build, Enables Timing Resistance and Blinding ")
    wolfsslHarden.setDefaultValue(True)
    wolfsslHarden.setVisible(True)
    
    wolfsslCacheMenu = wolfsslComponent.createMenuSymbol("wolfssl_cache_menu", None)
    wolfsslCacheMenu.setLabel("Cache")
    wolfsslCacheMenu.setVisible(True)
    
    wolfsslSessionCache = wolfsslComponent.createComboSymbol("wolfSslSessionCache", wolfsslCacheMenu, ["Normal", "Small", "Big", "Huge", "None"])
    wolfsslSessionCache.setLabel("Session Cache Size")
    wolfsslSessionCache.setDescription("Set the size of the session cache")
    wolfsslSessionCache.setDefaultValue("Normal")
    wolfsslSessionCache.setVisible(True)
    
    wolfsslPersistSessionCache = wolfsslComponent.createBooleanSymbol("wolfSslSaveCache", wolfsslCacheMenu)
    wolfsslPersistSessionCache.setLabel("Persistent session cache")
    wolfsslPersistSessionCache.setDescription("Enable persistent session cache")
    wolfsslPersistSessionCache.setVisible(True)
    wolfsslPersistSessionCache.setDefaultValue(False)
    
    wolfsslPersistCertCache = wolfsslComponent.createBooleanSymbol("wolfSslSaveCert", wolfsslCacheMenu)
    wolfsslPersistCertCache.setLabel("Persistent cert cache")
    wolfsslPersistCertCache.setDescription("Enable persistent cert cache")
    wolfsslPersistCertCache.setVisible(True)
    wolfsslPersistCertCache.setDefaultValue(False)
    
    wolfsslSessionCerts = wolfsslComponent.createBooleanSymbol("wolfSslSessionCerts", None)
    wolfsslSessionCerts.setLabel("Session Certs")
    wolfsslSessionCerts.setDescription("Enable session cert storing")
    wolfsslSessionCerts.setVisible(True)
    wolfsslSessionCerts.setDefaultValue(False)
    
    wolfsslKeyGen = wolfsslComponent.createBooleanSymbol("wolfSslKeyGen", None)
    wolfsslKeyGen.setLabel("Key Generation")
    wolfsslKeyGen.setDescription("Enable key generation")
    wolfsslKeyGen.setVisible(True)
    wolfsslKeyGen.setDefaultValue(False)
    
    wolfsslCertGen = wolfsslComponent.createBooleanSymbol("wolfSslCertGen", None)
    wolfsslCertGen.setLabel("Cert Generation")
    wolfsslCertGen.setDescription("Enable cert generation")
    wolfsslCertGen.setVisible(True)
    wolfsslCertGen.setDefaultValue(False)
    
    wolfsslCertReq = wolfsslComponent.createBooleanSymbol("wolfSslCertReq", None)
    wolfsslCertReq.setLabel("Cert Request Generation")
    wolfsslCertReq.setDescription("Enable cert request generation")
    wolfsslCertReq.setVisible(True)
    wolfsslCertReq.setDefaultValue(False)

    wolfsslKeyDerivationMenu = wolfsslComponent.createMenuSymbol("wolfssl_key_derivation_menu", None)
    wolfsslKeyDerivationMenu.setLabel("Key Derivation Algorithms")
    wolfsslKeyDerivationMenu.setVisible(True)
    
    wolfsslHkdf = wolfsslComponent.createBooleanSymbol("wolfsslHkdf", wolfsslKeyDerivationMenu)
    wolfsslHkdf.setLabel("HKDF")
    wolfsslHkdf.setDescription("Enable HKDF (HMAC-KDF) support")
    wolfsslHkdf.setVisible(True)
    wolfsslHkdf.setDefaultValue(False)
    
    wolfsslX963kdf = wolfsslComponent.createBooleanSymbol("wolfsslx963kdf", wolfsslKeyDerivationMenu)
    wolfsslX963kdf.setLabel("X9.43 KDF")
    wolfsslX963kdf.setDescription("Enable X9.63 KDF support")
    wolfsslX963kdf.setVisible(True)
    wolfsslX963kdf.setDefaultValue(False)
    
    wolfsslNoErrorString = wolfsslComponent.createBooleanSymbol("wolfsslNoErrorStrings", None)
    wolfsslNoErrorString.setLabel("Error String")
    wolfsslNoErrorString.setDescription("Enable error strings table")
    wolfsslNoErrorString.setVisible(True)
    wolfsslNoErrorString.setDefaultValue(False)
    
    wolfsslNoOldTls = wolfsslComponent.createBooleanSymbol("wolfsslNoOldTls", wolfsslTLSMenu)
    wolfsslNoOldTls.setLabel("Old Version Support")
    wolfsslNoOldTls.setDescription("Enable support for older versions of TLS.  (1.1, 1.0, SSL)")
    wolfsslNoOldTls.setVisible(True)
    wolfsslNoOldTls.setDefaultValue(False)
    
    wolfsslUseFastMath = wolfsslComponent.createBooleanSymbol("wolfsslUseFastMath", None)
    wolfsslUseFastMath.setLabel("Use Fast Math")
    wolfsslUseFastMath.setDescription("Enable fast math ops")
    wolfsslUseFastMath.setVisible(True)
    wolfsslUseFastMath.setDefaultValue(False)
    
    wolfsslClientSupport = wolfsslComponent.createBooleanSymbol("wolfsslClientSupport", None)
    wolfsslClientSupport.setLabel("Client Support")
    wolfsslClientSupport.setDescription("Enable client support")
    wolfsslClientSupport.setVisible(True)
    wolfsslClientSupport.setDefaultValue(True)
    
    wolfsslServerSupport = wolfsslComponent.createBooleanSymbol("wolfsslServerSupport", None)
    wolfsslServerSupport.setLabel("Server Support")
    wolfsslServerSupport.setDescription("Enable server support")
    wolfsslServerSupport.setVisible(True)
    wolfsslServerSupport.setDefaultValue(True)

    
    wolfsslConfigInfo = wolfsslComponent.createFileSymbol("wolfssl_config_info", None)
    wolfsslConfigInfo.setSourcePath("templates/wolfssl_config.h.ftl")
    wolfsslConfigInfo.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    wolfsslConfigInfo.setMarkup(True)
    wolfsslConfigInfo.setType("STRING")
    wolfsslConfigInfo.setEnabled(True)
    
    includeFilename = wolfsslComponent.createFileSymbol("include_filename", None)
    includeFilename.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME"))
    includeFilename.setSourcePath("config/config.h")
    includeFilename.setDestPath("")
    includeFilename.setOutputName("config.h")
    includeFilename.setType("HEADER")
    
    wolfsslConfigH = wolfsslComponent.createSettingSymbol("wolfsslConfigH", None)
    wolfsslConfigH.setCategory("C32")
    wolfsslConfigH.setKey("preprocessor-macros")
    wolfsslConfigH.setValue("HAVE_CONFIG_H")
    
    wolfsslSupportSrcPath = wolfsslComponent.createSettingSymbol("wolfsslSupportSrcPath", None)
    wolfsslSupportSrcPath.setValue("../src/third_party/wolfcrypt_support")
    wolfsslSupportSrcPath.setCategory("C32")
    wolfsslSupportSrcPath.setKey("extra-include-directories")
    wolfsslSupportSrcPath.setAppend(True, ";")

    wolfsslSrcPath = wolfsslComponent.createSettingSymbol("wolfsslSrcPath", None)
    wolfsslSrcPath.setValue("../src/third_party/wolfssl")
    wolfsslSrcPath.setCategory("C32")
    wolfsslSrcPath.setKey("extra-include-directories")
    wolfsslSrcPath.setAppend(True, ";")
    
    # these files are in wolfssl/src/
    fileList_common = [
        'crl.c', 'internal.c', 'keys.c', 'ocsp.c', 'sniffer.c',
        'ssl.c', 'tls.c', 'tls13.c', 'wolfio.c', 
    ]
    
    fileList_common_imp = [
        'bio.c'
    ]

    # these header files are in wolfssl/wolfssl/
    fileList_wolfssl_headers = [
        'callbacks.h','certs_test.h','crl.h','error-ssl.h','internal.h','ocsp.h',
        'sniffer.h','sniffer_error.h','ssl.h','test.h','version.h','wolfio.h'
    ]
    # these files are in wolfssl/support/
    fileList_wolfcrypt_support = [
        'aes.h','arc4.h','asn.h','asn_public.h','camellia.h','chacha.h','coding.h',
        'compress.h','cpuid.h','des3.h','dh.h','dsa.h','ecc.h','error-crypt.h','hash.h',
        'hc128.h','hmac.h','integer.h','logging.h','md2.h','md4.h','md5.h','memory.h','misc.h','pkcs7.h','pkcs12.h',
        'mpi_class.h','mpi_superclass.h','pwdbased.h','rabbit.h','random.h','ripemd.h','rsa.h',
        'settings.h','sha.h','sha256.h','sha512.h','tfm.h','types.h','visibility.h','wc_encrypt.h','wc_port.h','wolfmath.h'
    ]
    # these files are in wolfssl/support/
    fileList_misc = [
        'misc.c'
    ]
    for filename in fileList_common:
        addFileName(filename, 'common', wolfsslComponent, "../wolfssl/src/", "../../third_party/wolfssl/src/", True)
    for filename in fileList_wolfssl_headers:
        addFileName(filename, 'header', wolfsslComponent, "../wolfssl/wolfssl/", "../../third_party/wolfssl/wolfssl/", True)
    for filename in fileList_wolfcrypt_support:
        addFileName(filename, 'support', wolfsslComponent, "../wolfssl/support/", "../../third_party/wolfcrypt_support/wolfssl/wolfcrypt/", True)
    for filename in fileList_misc:
        addFileName(filename, 'misc', wolfsslComponent, "../wolfssl/support/", "../../third_party/wolfcrypt_support/wolfcrypt/src/", True)
    #for filename in fileList_common_imp:
    #    addFileName(filename, 'imp', wolfsslComponent, "../wolfssl/src/", "../../third_party/wolfssl/src/", True)    
    
# all files go into or under src/
# The relative root path for srcPath is the dir containing the app's module.xml
# The relative root path for destPath is firmware/src/config/$ConfigName/
def addFileName(fileName, prefix, component, srcPath, destPath, enabled):
    print("Adding file: " + prefix + fileName.replace('.', '_'))
    filename = component.createFileSymbol(prefix + fileName.replace('.', '_'), None)
    filename.setProjectPath("wolfSSL")
    filename.setSourcePath(srcPath + fileName)
    filename.setOutputName(fileName)

    if prefix == 'misc' or prefix == 'imp':
        filename.setDestPath(destPath)
        filename.setType("IMPORTANT")
    elif fileName[-2:] == '.h':
        filename.setDestPath(destPath)
        filename.setType("HEADER")
    else:
        filename.setDestPath(destPath)
        filename.setType("SOURCE")

    filename.setEnabled(enabled)
