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
import inspect
import os
import sys
import glob
import ntpath


wolfsslOverridableSrcFiles = ["internal.c"]
wolfsslOverridableHeaderFiles = []


def instantiateComponent(wolfsslComponent):
    wolfssl = wolfsslComponent.createBooleanSymbol("wolfssl", None)
    wolfssl.setLabel("Use wolfSSL?")
    wolfssl.setDescription("Enables wolfSSL")
    wolfssl.setVisible(False)
    wolfssl.setDefaultValue(True)

    wolfsslSmallStackSupport = wolfsslComponent.createBooleanSymbol("wolfsslSmallStackSupport", None)
    wolfsslSmallStackSupport.setLabel("Small Stack Support")
    wolfsslSmallStackSupport.setDescription("Enable small stack support")
    wolfsslSmallStackSupport.setVisible(True)
    wolfsslSmallStackSupport.setDefaultValue(False)

    wolfsslOsalHeapKeys = wolfsslComponent.createBooleanSymbol("wolfsslOsalHeapKeys", None)
    wolfsslOsalHeapKeys.setLabel("Use OSAL Heap")
    wolfsslOsalHeapKeys.setDescription("Use OSAL heap in place of C heap")
    wolfsslOsalHeapKeys.setVisible(True)
    wolfsslOsalHeapKeys.setDefaultValue(False)
    wolfsslOsalHeapKeys.setDependencies(setVisibilityOsal, ['HarmonyCore.ENABLE_OSAL'])

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
    
    wolfsslTLSComment = wolfsslComponent.createCommentSymbol("wolfsslTLSComment", wolfsslTLSMenu)
    wolfsslTLSComment.setLabel("**Placeholder for TLS Comment")
    wolfsslTLSComment.setVisible(False)

    wolfsslTLSDowngrade = wolfsslComponent.createBooleanSymbol("wolfsslTLSDowngrade", wolfsslTLSMenu)
    wolfsslTLSDowngrade.setLabel("TLS Downgrade Support")
    wolfsslTLSDowngrade.setDescription("Allow TLS Downgrade To Match Highest Supported Version")
    wolfsslTLSDowngrade.setDefaultValue(False)
    wolfsslTLSDowngrade.setVisible(False)
    wolfsslTLSDowngrade.setDependencies(wolfsslTLSManageVersions, ["wolfsslTLS13", "wolfsslTLS12", "wolfsslNoOldTls"])
    
    wolfsslTLS13 = wolfsslComponent.createBooleanSymbol("wolfsslTLS13", wolfsslTLSMenu)
    wolfsslTLS13.setLabel("TLS 1.3 Support")
    wolfsslTLS13.setDescription("Enable TLS 1.3 Support")
    wolfsslTLS13.setDefaultValue(False)
    wolfsslTLS13.setVisible(True)

    wolfsslTLS12 = wolfsslComponent.createBooleanSymbol("wolfsslTLS12", wolfsslTLSMenu)
    wolfsslTLS12.setLabel("TLS 1.2 Support")
    wolfsslTLS12.setDescription("Enable TLS 1.2 Support")
    wolfsslTLS12.setDefaultValue(True)
    wolfsslTLS12.setVisible(True)

    wolfsslTlsSni = wolfsslComponent.createBooleanSymbol("wolfsslTlsSni", wolfsslTLSMenu)
    wolfsslTlsSni.setLabel("SNI Support")
    wolfsslTlsSni.setDescription("Enable support for server name indication")
    wolfsslTlsSni.setVisible(True)
    wolfsslTlsSni.setDefaultValue(False)

    wolfsslTlsEccCurvesExt = wolfsslComponent.createBooleanSymbol("wolfsslTlsEccCurvesExt", wolfsslTLSMenu)
    wolfsslTlsEccCurvesExt.setLabel("ECC Supported Curves Support")
    wolfsslTlsEccCurvesExt.setDescription("Enable support for ECC supported curves")
    wolfsslTlsEccCurvesExt.setVisible(True)
    wolfsslTlsEccCurvesExt.setDefaultValue(False)
    
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
    
    wolfsslEncryptedKeys = wolfsslComponent.createBooleanSymbol("wolfsslEncryptedKeys", None)
    wolfsslEncryptedKeys.setLabel("Encrypted Keys Support")
    wolfsslEncryptedKeys.setDescription("Enable encrypted keys support")
    wolfsslEncryptedKeys.setVisible(True)
    wolfsslEncryptedKeys.setDefaultValue(False)
    
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

    wolfsslpwdkdf = wolfsslComponent.createBooleanSymbol("wolfsslpwdkdf", wolfsslKeyDerivationMenu)
    wolfsslpwdkdf.setLabel("PBKDFx KDF")
    wolfsslpwdkdf.setDescription("Enable PBKDF1, PBKDF2 & PBKDF support")
    wolfsslpwdkdf.setVisible(True)
    wolfsslpwdkdf.setDefaultValue(False)
    
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

    wolfsslFfdheMenu = wolfsslComponent.createMenuSymbol("wolfssl_ffdhe_menu", wolfsslProtocolMenu)
    wolfsslFfdheMenu.setLabel("DHE")
    wolfsslFfdheMenu.setVisible(True)
    for grpSize in ['2048', '3072', '4096', '6144', '8192']:
        wolfsslFfdheGrpSz = wolfsslComponent.createBooleanSymbol("wolfsslFfdheGroup"+grpSize, wolfsslFfdheMenu)
        wolfsslFfdheGrpSz.setLabel(grpSize + " bits")
        wolfsslFfdheGrpSz.setDescription("DHE " + grpSize + " Group Size")
        wolfsslFfdheGrpSz.setDefaultValue(False)
        wolfsslFfdheGrpSz.setVisible(True)
    
    # Enable TNGTLS Certificate loading?
    wolfsslTNGTLScert = wolfsslComponent.createBooleanSymbol("wolfsslLoadTNGTLSCert",None)
    wolfsslTNGTLScert.setLabel("Trust&Go client certificate")
    wolfsslTNGTLScert.setVisible(False) #will be set from netPres
    wolfsslTNGTLScert.setDescription("Auto load device certificate from Trust&Go TNGTLS? Cryptoauth lib should be configured seperately")
    wolfsslTNGTLScert.setDefaultValue(False)
        
    setupFiles(wolfsslComponent)
    
    
def get_script_dir(follow_symlinks=True):
    if getattr(sys, 'frozen', False): # py2exe, PyInstaller, cx_Freeze
        path = os.path.abspath(sys.executable)
    else:
        path = inspect.getabsfile(get_script_dir)
    if follow_symlinks:
        path = os.path.realpath(path)
    return os.path.dirname(path)

def trimFileNameList(rawList) :
    newList = []
    for file in rawList:
        filename = ntpath.basename(file)
        newList.append(filename)
    return newList
    
def setVisibilityOsal(symbol, event):
    symbol.setVisible(event['value'])
    symbol.setEnabled(event['value'])
        
def addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
    print("Adding file: " + prefix + fileName.replace('.', '_'))
    filename = component.createFileSymbol(prefix + fileName.replace('.', '_'), None)
    filename.setProjectPath(projectPath)
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
    
    
def setupFiles(basecomponent) :
    global wolfsslOverridableSrcFiles
    global wolfsslOverridableHeaderFiles

    wolfSslSourceFiles = get_script_dir() + "/../../wolfssl/src/*.c"
    wolfSslHeaderFiles = get_script_dir() + "/../../wolfssl/wolfssl/*.h"
    
    wcsfrl = glob.glob(wolfSslSourceFiles)
    wcsfl = []
    for file in wcsfrl:
        filename = ntpath.basename(file)
        if ((not (filename in wolfsslOverridableSrcFiles)) and (filename != "bio.c") ):
            wcsfl.append(filename)
    
    wchfl = []
    for file in glob.glob(wolfSslHeaderFiles):
        filename = ntpath.basename(file)
        if ((not (filename in wolfsslOverridableHeaderFiles))):
            wchfl.append(filename)
            
    for file in wcsfl:
        addFileName(file, "wolfssl", basecomponent, "../wolfssl/src/", "../../third_party/wolfssl/src/", True, "wolfssl")
        
    for file in wchfl:
        addFileName(file, "wolfssl", basecomponent, "../wolfssl/wolfssl/", "../../third_party/wolfssl/wolfssl/", True, "wolfssl")
       

    for file in wolfsslOverridableSrcFiles:
        addFileName(file, "wolfssloverride", basecomponent, "src/", "../../third_party/wolfssl/src/", True, "wolfssl")

    for file in wolfsslOverridableHeaderFiles:
        addFileName(file, "wolfssloverride", basecomponent, "src/", "../../third_party/wolfssl/wolfssl/", True, "wolfssl")

def wolfsslTLSManageVersions(symbol, event):
    data = symbol.getComponent()
    stateTdg = bool(symbol.getValue())
    stateOld = bool(data.getSymbolValue("wolfsslNoOldTls"))
    stateT13 = bool(data.getSymbolValue("wolfsslTLS13"))
    stateT12 = bool(data.getSymbolValue("wolfsslTLS12"))
    tlsCount = int(stateOld + stateT13 + stateT12)

    # Handle TLS downgrade option
    if (stateTdg != (tlsCount > 1)):
        symbol.setValue((tlsCount > 1))
    
    # Handle TLS Comment
    commSymbol = data.getSymbolByID("wolfsslTLSComment")
    setLabel = "**TLS Info**"
    setVisible = False
    if (stateOld and (not stateT12)):
        setVisible = True
        setLabel = "!!! Error: TLS 1.2 Must Be Enabled To Support Old Versions"
    elif (tlsCount == 0):
        setVisible = True
        setLabel = "!!! Error: No TLS Versions Enabled"
    elif (tlsCount > 1):
        setVisible = True
        setLabel = "** Info: TLS Downgrade Support Auto-Enabled"
    commSymbol.setLabel(setLabel)
    commSymbol.setVisible(setVisible)
