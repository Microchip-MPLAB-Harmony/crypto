# coding: utf-8
'''#*******************************************************************************
# Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
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
# ***************************************************************************'''

import inspect
import os
import sys
import glob
import ntpath

#Local Modules
print("CRYPTO MODULE Path: " + Module.getPath())
modulePath =  Module.getPath()
sys.path.append(modulePath + "config")

#import crypto_globals               #Initial globals
import crypto_defs           as g   #Modified globals
import crypto_hash_menu      as hm  #HASH GUI
import crypto_symmetric_menu as sm  #Symmetric Menu
import crypto_mac_menu       as mm  #Hmac Menu
import crypto_digsign_menu   as ds  #Digital Signing Menu
import crypto_kas_menu       as kas #Key Auth Menu
import crypto_rng_menu       as rng #rng Menu

src_ext      = ('.c')
hdr_ext      = ('.h')
mipslib_ext  = ('.a')

#*******************************************************************************
# Adds File to project database and enables/disables it
# -- Note that the file destination/source path is relative to  
#    src/config/<config>
def AddFileName(fileName, prefix, component,
                srcPath, destPath, enabled, projectPath):

    fileID = prefix + fileName.replace('.', '_')
    fileNameSymbol = component.createFileSymbol(fileID, None)
    fileNameSymbol.setProjectPath(projectPath)

    srcPath += fileName
    print("CRYPTO: Add(%s) ""%s"""%(enabled,srcPath))
    print("    dstPath ""%s"""%(destPath))
    print("   projPath ""%s"""%(projectPath))
    fileNameSymbol.setSourcePath(srcPath)
    fileNameSymbol.setOutputName(fileName)

    if prefix == 'misc' or prefix == 'imp':
        fileNameSymbol.setDestPath(destPath)
        fileNameSymbol.setType("IMPORTANT")
    elif fileName[-2:] == '.h':
        fileNameSymbol.setDestPath(destPath)
        fileNameSymbol.setType("HEADER")
    else:
        fileNameSymbol.setDestPath(destPath)
        fileNameSymbol.setType("SOURCE")

    fileNameSymbol.setEnabled(enabled)

    #TrustZone - TODO:  Make this a configurable option
    g.trustZoneFileIds.append(fileID)
    if (g.trustZoneSupported == True):
        fileNameSymbol.setSecurity("SECURE")
        tz = "S"
        print("  --Added (TZ) ""%s"" "%(projectPath + fileName))
    else:
        fileNameSymbol.setSecurity("NON_SECURE")
        tz = "N"
        print("  --Added ""%s"" "%(projectPath + fileName))

    return (fileNameSymbol)

#*******************************************************************************
# Adds File to project database and enables/disables it
# -- Note that the file destination/source path is relative to  
#    src/config/<config>
    g.trustZoneFileIds.append(ccHashConfigFile.getID())
def AddMarkupFile(fileName, prefix, component,
                srcPath, destPath, enabled, projectPath):
    fileID = prefix + fileName.replace('.', '_')
    fileNameSymbol = component.createFileSymbol(fileID, None)

    fileNameSymbol.setMarkup(True)
    fileNameSymbol.setOverwrite(True)
    fileNameSymbol.setProjectPath(projectPath)

    srcPath += fileName + ".ftl"

    print("CRYPTO: Add MU(%s) ""%s"""%(enabled,srcPath))
    print("       dstPath ""%s"""%(destPath))
    print("      projPath ""%s"""%(projectPath))
    fileNameSymbol.setSourcePath(srcPath)
    fileNameSymbol.setOutputName(fileName) #without .ftl

    if prefix == 'misc' or prefix == 'imp':
        fileNameSymbol.setDestPath(destPath)
        fileNameSymbol.setType("IMPORTANT")
    elif fileName[-2:] == '.h':
        fileNameSymbol.setDestPath(destPath)
        fileNameSymbol.setType("HEADER")
    else:
        fileNameSymbol.setDestPath(destPath)
        fileNameSymbol.setType("SOURCE")

    fileNameSymbol.setEnabled(enabled)

    #TrustZone
    #--TODO:  Make this a configurable option
    g.trustZoneFileIds.append(fileID)
    if (g.trustZoneSupported == True):
        fileNameSymbol.setSecurity("SECURE")
        tz = "S"
        print("  --Added Project MU (TZ) ""%s"" "%(projectPath + fileName))
    else:
        fileNameSymbol.setSecurity("NON_SECURE")
        tz = "N"
        print("  --Added Project MU ""%s"" "%(projectPath + fileName))

    return (fileNameSymbol)


################################################################################
################################################################################
def get_script_dir(follow_symlinks=True):
    if getattr(sys, 'frozen', False): # py2exe, PyInstaller, cx_Freeze
        path = os.path.abspath(sys.executable)
    else:
        path = inspect.getabsfile(get_script_dir)
    if follow_symlinks:
        path = os.path.realpath(path)
    return os.path.dirname(path)


################################################################################
################################################################################
def TrimFileNameList(rawList) :
    newList = []
    for file in rawList:
        fileName = ntpath.basename(file)
        newList.append(fileName)
    return newList


#################################################################################
##  Crypto V4 Common Crypto API
#################################################################################
def SetupCommonCryptoFiles(basecomponent) :
    global modulePath

    configName = Variables.get("__CONFIGURATION_NAME")  # e.g. "default"$

    print("CRYPTO:  setup CC Files %s"%(modulePath))
    commonCryptoHeaderFiles= (
            modulePath +
            "src/common_crypto/*.h")
    commonCryptoSourceFiles     = (
            modulePath +
            "src/common_crypto/src/*.c")

    #All src/header files in the common/crypto directory
    ccphfl = glob.glob(commonCryptoHeaderFiles)
    ccpsfl = glob.glob(commonCryptoSourceFiles)

    ccphfl = TrimFileNameList(glob.glob(commonCryptoHeaderFiles))
    ccpsfl = TrimFileNameList(glob.glob(commonCryptoSourceFiles))

    ccphfl_trim = ccphfl
    ccpsfl_trim = ccpsfl

    #All src files in the wolfssl/wolfcrypt/src directory
    #--AddFileName(fileName, prefix, component, 
    #              srcPath, destPath, enabled, projectPath):
    for fileName in ccphfl_trim:
        #AddFileName(fileName, prefix, component, 
        #            srcPath, destPath, enabled, projectPath):
        projectPath = "config/" + configName + "/crypto/common_crypto/"
        fileSym = AddFileName(fileName,                     #Filename 
                         "common_crypto",              #MCC Symbol Name Prefix
                         basecomponent,                #MCC Component
                         "src/common_crypto/",         #Src Path
                         "crypto/common_crypto/",      #Dest Path
                         True,                         #Enabled
                         projectPath) #Project Path

    projectPath = "config/" + configName + "/crypto/common_crypto/src/"
    for fileName in ccpsfl_trim:
        fileSym = AddFileName(fileName,                     #Filename    
                         "common_crypto",              #MCC Symbol Name Prefix
                         basecomponent,                #MCC Component
                         "src/common_crypto/src/",     #Path Src
                         "crypto/common_crypto/src/",  #Path Dest
                         True,                         #Enabled
                         projectPath)

################################################################################
################################################################################
def SetupCpkclDriverFiles(basecomponent) :
    global modulePath

    configName = Variables.get("__CONFIGURATION_NAME")  # e.g. "default"$

    print("CRYPTO:  setup CPKCC Driver Files %s"%(g.cpkclDriverPath))
    headerFiles = (modulePath + g.cpkclDriverPath + "*.h")
    sourceFiles = (modulePath + g.cpkclDriverPath + "*.c")
    print("CPKCC: path %s"%(modulePath + g.cpkclDriverPath)) 

    #All src/header files in the common/crypto directory
    hfl = glob.glob(headerFiles)
    sfl = glob.glob(sourceFiles)

    print("CPKCC: %d Headers"%(len(hfl)))
    print("CPKCC: %d Source "%(len(sfl)))
    phfl = TrimFileNameList(glob.glob(headerFiles))
    psfl = TrimFileNameList(glob.glob(sourceFiles))

    phfl_trim = phfl
    psfl_trim = psfl

    g.cpkclDriverFileSyms = []

    #All src files in the wolfssl/wolfcrypt/src directory
    #--AddFileName(fileName, prefix, component, 
    #              srcPath, destPath, enabled, projectPath):
    projectPath = "config/" + configName + "/crypto/drivers/CryptoLib_CPKCL"
    dstPath = "crypto/drivers/CryptoLib_CPKCL/"  #Path Dest
    for fileName in phfl_trim:
        #AddFileName(fileName, prefix, component, 
        #            srcPath, destPath, enabled, projectPath):
        print("CPKCL: Add %s"%(dstPath + fileName))
        fileSym = AddFileName(fileName,                   #Filename 
                         "cpkcc",                         #MCC Symbol Name Prefix
                         basecomponent,                   #MCC Component
                         g.cpkclDriverPath,                 #Src Path
                         dstPath,                         #Path Dest
                         False,                            #Enabled
                         projectPath) #Project Path
        g.cpkclDriverFileSyms.append(fileSym)

    projectPath = "config/" + configName + "/crypto/drivers/CryptoLib_CPKCL"
    for fileName in psfl_trim:
        print("CPKCL: Add %s"%(dstPath + fileName))
        fileSym = AddFileName(fileName,                   #Filename    
                         "cpkcc",                         #MCC Symbol Name Prefix
                         basecomponent,                   #MCC Component
                         g.cpkclDriverPath,                 #Src Path
                         dstPath,                         #Path Dest
                         False,                            #Enabled
                         projectPath) #Project Path
        g.cpkclDriverFileSyms.append(fileSym)


#################################################################################
#### Function to Instantiate the Harmony 3 TM Component - dynamic    
#### Crypto V4 API Library Component - specific to processor
#
# Description:
#    Function that is called during component activation (added to the project
#    graph). The component is allowed to establish dependencies and create
#    symbols.
#     --Code is generated later based on configuration settings
#
# Parameters:
#    component (LocalComponent) – local interface to the newly added component
#    [index (integer)] - for instanced components only, indicates the instance index
#
#### NOTE(s): 
####    1) crypto component module defined by module.py in crypto/config
#################################################################################
def instantiateComponent(cryptoComponent):
    #Crypto Library component added to the project graph

    configName = Variables.get("__CONFIGURATION_NAME")  # e.g. "default"
    processor  = Variables.get("__PROCESSOR")
    Log.writeInfoMessage("Crypto: Project MCU  " + processor)
    print("CRYPTO: Project MCU  " + processor)
    print("Crypto: Display Name " + cryptoComponent.getDisplayName())
    print("Crypto ID: " + cryptoComponent.getID())

    #Dependencies
    g.cryptoWolfSSLIncluded = False

    #TrustZone
    #--Processor name patterns for trustzone: 
    #  trustZoneDevices[device #][0 or 1] 
    g.trustZoneSupported = False
    if Variables.get("__TRUSTZONE_ENABLED") != None and Variables.get("__TRUSTZONE_ENABLED") == "true":
        g.trustZoneSupported = True
        print("CRYPTO:  TRUST_ZONE is true")
    else:
        print("CRYPTO:  TRUST_ZONE NOT true")

    # TODO:  This is the backup for the failure of the variable
    #        to indicate trustZone support.
    #--Processor name patterns for trustzone: 
    #  trustZoneDevices[device #][0 or 1] 
    g.trustZoneSupported = False
    ll = len(g.trustZoneDevices)
    for dev in range(ll):
        if (g.trustZoneDevices[dev][0] in processor):
            if (g.trustZoneDevices[dev][1] in processor):
                print("CRYPTO:  Trust Zone Supported for %s"%processor)
                g.trustZoneSupported = True
                break;

    #String Implementation of defines for crypto_config.h.ftl
    g.cryptoHwDefines = cryptoComponent.createStringSymbol(
                                     "cryptoHwDefines", None)
    g.cryptoHwDefines.setVisible(False)

    g.localCryptoComponent = cryptoComponent

    #Scan ATDF for Hardware suport
    SetupHardwareSupport(g.localCryptoComponent)

    #Add the crypto software implementation src library to file Generation Db
    AddAlwaysOnFiles(g.localCryptoComponent)
    SetupCommonCryptoFiles(g.localCryptoComponent)

    ####=========================================================================
    #### CODE GENERATION GUI CONFIGURATION
    ####
    ##### NOTES: 1) Unique File Symbols are created
    ####         2) The File Symbols are enabled based on the MHC configuration
    ####            symbol values.  The file will be generated if the file symbol
    ####            is enabled.
    ####         3) The the symbol and type of file determines where in the 
    ####            project it will be generated.
    ####=========================================================================
    global CONFIG_USE_CRYPTO

    CONFIG_USE_CRYPTO = cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_CRYPTO", None)
    CONFIG_USE_CRYPTO.setVisible(False)
    CONFIG_USE_CRYPTO.setLabel("Crypto")
    CONFIG_USE_CRYPTO.setDefaultValue(True)


    #Project Include Path Directories
    if (g.trustZoneSupported == True):
        ccIncludePath = cryptoComponent.createSettingSymbol("XC32_CRYPTO_SECURE_INCLUDE_DIRS", None)
        ccIncludePath.setSecurity("SECURE")
    else:
        ccIncludePath = cryptoComponent.createSettingSymbol("XC32_CRYPTO_INCLUDE_DIRS", None)
    ccIncludePath.setCategory("C32")
    ccIncludePath.setKey("extra-include-directories")
    ccIncludePath.setValue(    "../src/third_party/wolfssl/wolfssl/wolfcrypt"
                            + ";../src/third_party/wolfssl"
                            + ";../src/third_party/wolfcrypt"
                            + ";../src/config/" + configName + "/crypto/wolfcrypt"
                            + ";../src/config/" + configName + "/crypto/drivers")

    ccIncludePath.setAppend(True, ";")
    print("CRYPTO: Include Path -")
    print(ccIncludePath.getValue())


    #----------------------------------------------------------------
    #WOLFCRYPT Library Configuration as used by CRYPTO component 
    #
    #TODO:  Has dependency on connected Wolfcrypt component 
    #       Wolfcrypt always generated for now.
    #
    #TODO: Header file search path (get this to work) 
    #wolfcryptSearchPath = basecomponent.setPath("..\src\config\crypto\wolfcrypt")
    #wolfcryptSearchPath = basecomponent.setPath("..\src\third_party\wolfssl\wolfssl")
    #wolfcryptSearchPath = basecomponent.setPath("..\src\third_party\wolfssl\wolfssl")

    #Crypto API Files - to configure Wolfcrypt for SW implementations
    #INCLUDE FILE to configure WOLFCRYPT with the HAVE_CONFIG_H 
    #project define.
    projectPath = "config/" + configName + "/crypto/wolfcrypt/"
    srcPath     = "src/wolfcrypt/"             #Src Path
    dstPath     = "crypto/wolfcrypt/"
    fileSym = AddFileName("config.h",          #Filename    
                          "common_crypto",     #MCC Symbol Name Prefix
                          cryptoComponent,     #MCC Component
                          srcPath,             #Src Path
                          dstPath,             #Dest Path
                          True,                #Enabled
                          projectPath)         #Project Path

    #INCLUDE FILE to configure WOLFCRYPT with the WOLFSSL_USER_SETTINGS 
    #Project define
    fileSym = AddFileName("user_settings.h",   #Filename    
                          "common_crypto",     #MCC Symbol Name Prefix
                          cryptoComponent,     #MCC Component
                          srcPath,             #Path Src
                          dstPath,             #Path Dest
                          True,                #Enabled
                          projectPath)         #Project Path

    #--------------------------------------------------------
    #Crypto Function Group Configuration Files (for API optimization)

    #Locations of Configuration Files/Templates
    projectPath = "config/" + configName + "/crypto/common_crypto/"
    srcPath     = "templates/common_crypto"
    dstPath     = "crypto/common_crypto"

    #TrustZone
    # TODO:  Make TrustZone a visible option.
    g.cryptoTzEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_trustzone", None)
    g.cryptoTzEnabledSymbol.setLabel("Crypto in TrustZone?")
    g.cryptoTzEnabledSymbol.setDescription(
            "Crypto Enabled in TrustZone")
    g.cryptoTzEnabledSymbol.setHelp('CRYPT_TZ_SUM')
    g.cryptoTzEnabledSymbol.setDefaultValue(False)

    #TrustZone menu symbol
    if (g.trustZoneSupported == True):
        g.cryptoTzEnabledSymbol.setVisible(True)
        #g.cryptoTzEnabledSymbol.setDependencies(
        #        handleTzEnabled, ["crypto_trustzone"])
        g.cryptoTzEnabledSymbol.setDefaultValue(True)
        g.cryptoTzEnabledSymbol.setReadOnly(True)   #TODO: Make configurable
    else:
        g.cryptoTzEnabledSymbol.setVisible(False)
        g.cryptoTzEnabledSymbol.setDefaultValue(False)


    #HASH Function Group
    #--CONFIG_USE_HASH
    hm.SetupCryptoHashMenu(cryptoComponent)

    #<config>/MCHP_Crypto_Hash_Config.h - API File
    #TODO:  Enable file gen Dependency on CONFIG_USE_HASH
    fileName    = "MCHP_Crypto_Hash_Config.h"
    ccHashConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_HASH_CONFIG", None)
    ccHashConfigFile.setMarkup(True)
    ccHashConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccHashConfigFile.setOutputName(fileName)
    ccHashConfigFile.setDestPath("crypto/common_crypto/")
    ccHashConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccHashConfigFile.setType("HEADER")
    ccHashConfigFile.setOverwrite(True)
    g.trustZoneFileIds.append(ccHashConfigFile.getID())

    #TrustZone - TODO:  Make this a configurable option
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccHashConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding HASH=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_HASH.getValue(), projectPath + fileName + ".ftl" ))
    else:
        ccHashConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding HASH=%s ""%s"%(
                   g.CONFIG_USE_HASH.getValue(), projectPath + fileName + ".ftl" ))

    #SYM Function Group
    #--CONFIG_USE_SYM
    sm.SetupCryptoSymmetricMenu(cryptoComponent)

    #<config>/MCHP_Crypto_Sym_Config.h - API File
    #fileName    = "MCHP_Crypto_Sym_Config.h"
    fileName    = "MCHP_Crypto_Sym_Config.h"
    ccSymConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_SYM_CONFIG", None)
    ccSymConfigFile.setMarkup(True)
    ccSymConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccSymConfigFile.setOutputName(fileName)
    ccSymConfigFile.setDestPath("crypto/common_crypto/")
    ccSymConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccSymConfigFile.setType("HEADER")
    ccSymConfigFile.setOverwrite(True)
    #TrustZone
    g.trustZoneFileIds.append(ccSymConfigFile.getID())
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccSymConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding SYM=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_SYM.getValue(), projectPath + fileName + ".ftl" ))

    else:
        ccSymConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding SYM=%s ""%s"%(
                   g.CONFIG_USE_SYM.getValue(), projectPath + fileName + ".ftl" ))

    #AEAD Function Group
    #NOTE:  AEAD Menu is setup with the SYM-AES Menu function
    #<config>/MCHP_Crypto_Aead_Config.h - API File
    fileName    = "MCHP_Crypto_Aead_Config.h"
    ccAeadConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_AEAD_CONFIG", None)
    ccAeadConfigFile.setMarkup(True)
    ccAeadConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccAeadConfigFile.setOutputName(fileName)
    ccAeadConfigFile.setDestPath("crypto/common_crypto/")
    ccAeadConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccAeadConfigFile.setType("HEADER")
    ccAeadConfigFile.setOverwrite(True)
    #TrustZone
    g.trustZoneFileIds.append(ccAeadConfigFile.getID())
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccAeadConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding AEAD=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_AEAD.getValue(), projectPath + fileName + ".ftl" ))

    else:
        ccAeadConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding AEAD=%s ""%s"%(
                   g.CONFIG_USE_AEAD.getValue(), projectPath + fileName + ".ftl" ))

    #MAC Function Group
    #--CONFIG_USE_MAC
    mm.SetupCryptoMacMenu(cryptoComponent)

    #<config>/MCHP_Crypto_Mac_Config.h - API File
    fileName    = "MCHP_Crypto_Mac_Config.h"
    ccMacConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_MAC_CONFIG", None)
    ccMacConfigFile.setMarkup(True)
    ccMacConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccMacConfigFile.setOutputName(fileName)
    ccMacConfigFile.setDestPath("crypto/common_crypto/")
    ccMacConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccMacConfigFile.setType("HEADER")
    ccMacConfigFile.setOverwrite(True)
    #TrustZone
    g.trustZoneFileIds.append(ccMacConfigFile.getID())
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccMacConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding MAC=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_MAC.getValue(), projectPath + fileName + ".ftl" ))

    else:
        ccMacConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding MAC=%s "" %s"%(
                   g.CONFIG_USE_MAC.getValue(), projectPath + fileName + ".ftl" ))

    #KAS - Key Authorization Function Group
    #--CONFIG_USE_KAS
    kas.SetupCryptoKasMenu(cryptoComponent)

    #<config>/MCHP_Crypto_Kas_Config.h - API File
    fileName    = "MCHP_Crypto_Kas_Config.h"
    ccKasConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_KAS_CONFIG", None)
    ccKasConfigFile.setMarkup(True)
    ccKasConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccKasConfigFile.setOutputName(fileName)
    ccKasConfigFile.setDestPath("crypto/common_crypto/")
    ccKasConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccKasConfigFile.setType("HEADER")
    ccKasConfigFile.setOverwrite(True)
    #TrustZone
    g.trustZoneFileIds.append(ccKasConfigFile.getID())
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccKasConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding KAS=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_KAS.getValue(), projectPath + fileName + ".ftl" ))

    else:
        ccKasConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding KAS=%s ""%s"%(
                   g.CONFIG_USE_KAS.getValue(), projectPath + fileName + ".ftl" ))

    #DS - Digital Signing Function Group
    #--CONFIG_USE_DS
    ds.SetupCryptoDsMenu(cryptoComponent)

    #<config>/MCHP_Crypto_Ds_Config.h - API File
    fileName    = "MCHP_Crypto_DigSign_Config.h"
    ccDsConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_DS_CONFIG", None)
    ccDsConfigFile.setMarkup(True)
    ccDsConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccDsConfigFile.setOutputName(fileName)
    ccDsConfigFile.setDestPath("crypto/common_crypto/")
    ccDsConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccDsConfigFile.setType("HEADER")
    ccDsConfigFile.setOverwrite(True)
    #TrustZone
    g.trustZoneFileIds.append(ccDsConfigFile.getID())
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccDsConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding DS=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_DS.getValue(), projectPath + fileName + ".ftl" ))

    else:
        ccDsConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding DS=%s ""%s"%(
                   g.CONFIG_USE_DS.getValue(), projectPath + fileName + ".ftl" ))

    #RNG - Digital Signing Function Group
    #--CONFIG_USE_RNG
    rng.SetupCryptoRngMenu(cryptoComponent)

    #<config>/MCHP_Crypto_Rng_Config.h - API File
    fileName    = "MCHP_Crypto_Rng_Config.h"
    ccRngConfigFile= cryptoComponent.createFileSymbol(
            "CC_API_RNG_CONFIG", None)
    ccRngConfigFile.setMarkup(True)
    ccRngConfigFile.setSourcePath(
            "templates/common_crypto/" + fileName + ".ftl")
    ccRngConfigFile.setOutputName(fileName)
    ccRngConfigFile.setDestPath("crypto/common_crypto/")
    ccRngConfigFile.setProjectPath(
            "config/" + configName + "/crypto/common_crypto/")
    ccRngConfigFile.setType("HEADER")
    ccRngConfigFile.setOverwrite(True)
    #TrustZone
    g.trustZoneFileIds.append(ccRngConfigFile.getID())
    if (g.cryptoTzEnabledSymbol.getValue() == True):
        ccRngConfigFile.setSecurity("SECURE")
        print("CRYPTO:  Adding RNG=%s (Secure)""%s"" "%(
                   g.CONFIG_USE_RNG.getValue(), projectPath + fileName + ".ftl" ))

    else:
        ccRngConfigFile.setSecurity("NON_SECURE")
        print("CRYPTO:  Adding RNG=%s ""%s"%(
                   g.CONFIG_USE_RNG.getValue(), projectPath + fileName + ".ftl" ))

################################################################################
#  Crypto Gui Interactions
################################################################################
def handleParentSymbolChange(symbol, event):
    symbol.setVisible(event["value"])

#-----------------------------------------------------
def handleHwTrngEnabled(symbol, event):
    if ((g.cryptoHwTrngEnabledSymbol.getValue() == True) and
        (g.cryptoTrngEnabledSymbol.getValue() == True)):
        g.cryptoHwTrngEnabledSymbol.setVisible(True)
    else:
        g.cryptoHwTrngEnabledSymbol.setValue(False)
        g.cryptoHwTrngEnabledSymbol.setVisible(False)

def handleHashDrngEnabled(symbol, event):
    if ((g.cryptoSha256EnabledSymbol.getValue() == True) and
        (g.cryptoTrngEnabledSymbol.getValue() == True)):
        g.cryptoHashDrngEnabledSymbol.setVisible(True)
    else:
        g.cryptoHashDrngEnabledSymbol.setValue(False)
        g.cryptoHashDrngEnabledSymbol.setVisible(False)


################################################################################
# Scan the ATDF file for hardware crypto driver module names 
# given in the list items, where each item is a dictionary given by:
# [ <atdf Module name>, <atdf Module ID number>, <atdf version code>,
#   [], <set of HW Project Defines> ] 
#
# The list is given like the following: 
#    [<dKey>, <ID>, <Version #>, [], <set of macros to be defined>]
#
# For example:
#    [PUKCC", "U2009", "2.5.0", [],
#     set(["HAVE_MCHP_CRYPTO_ECC_HW_PUKCC"])] #ATSAME54P20A
#
# Updates the g.cryptoHwAdditionalDefines set with the listed MACRO
#
#
################################################################################
def ScanHardware(list):
    periphNode = ATDF.getNode("/avr-tools-device-file/devices/device/peripherals")
    modules = periphNode.getChildren()

    for module in modules:
        for item in list:
            if (
                (module.getAttribute("name")      == item[0]) and
                (module.getAttribute("id")        == item[1]) and
                (((module.getAttribute("version") == item[2]) or
                  item[2] == ""))):

                #print("CRYPTO HW: name(%s) id(%s)"%(item[0],item[1]))

                #Add to the HW support Symbol ID  string to supported hw function
                #--same string as used for the crypto_config.h configuration defines
                g.cryptoHwAdditionalDefines = (
                        g.cryptoHwAdditionalDefines.union(item[4])) #MACRO

                #Add the the HW support name String to the crypto_config.h 
                #HW define configuration list
                #--Same for the numerical ID string list
                g.cryptoHwDevSupport = (
                        g.cryptoHwDevSupport.union([item[0]])) #driver ID
                g.cryptoHwIdSupport= (
                        g.cryptoHwIdSupport.union([item[1]])) #driver ID
                return [item[0], item[1]] #[<Driver name, Driver ID>]
    return [] 


################################################################################
#Add the available HW Drivers
#--Called after HW has been scanned and the HW Driver Symbols enabled.
#--HW Driver Symbols (
#  (TODO:  Drivers only for HW available and the HW function is selected)
################################################################################
def SetupHwDriverFiles(basecomponent):

    print("CRYPTO:  Adding HW Driver Files")
    configName  = Variables.get("__CONFIGURATION_NAME")  # e.g. "default"
    configPath  = "config/" + configName
    srcPathDrv  = "src/drivers/"
    mupPathDrv  = "templates/drivers/"
    dstPathDrv  = "crypto/drivers/"
    dstPathApi  = "crypto/common_crypto/"
    projPathDrv = "config/" + configName + "/crypto/drivers/"
    projPathApi = "config/" + configName + "/crypto/common_crypto/"

    print("CRYPTO HW: %d Driver Names: "%(len(g.cryptoHwDevSupport)))
    print(g.cryptoHwDevSupport)
    print("CRYPTO HW: %d Driver IDs: "%(len(g.cryptoHwIdSupport)))
    print(g.cryptoHwIdSupport)

    #create all possible driver files for this HW
    #--Later scan to see what HW functions are enabled
    #--Create Dict List the driver used for each function
    print("CRYPTO: Driver File Symbols Created:")
    for [dKey, fDict] in g.hwDriverDict.items():  #Driver File Dict

        #Check for Device Hardware Support functions
        if ((dKey in g.cryptoHwDevSupport) or (dKey in g.cryptoHwIdSupport)):
            print("CRYPTO: Supported Device Crypto HW Key %s:  "%(dKey))

            if (dKey == "CPKCC"):
                print("CRYPTO: Use CPKCC Driver Files ")
                SetupCpkclDriverFiles(basecomponent)

            fileNames = set([])
            for fKey in fDict:       #Driver Function Key to file Dict
                for fileName in fDict[fKey]:

                    #Check for duplicate
                    if (fileNames.issuperset([fileName]) == False):

                        #HW Driver Files
                        if (fileName[:4] == "drv_"):
                            if fileName.endswith(".ftl"):
                                fileName = fileName[:len(fileName) - 4]
                                #NOTE:  standard files in src/drivers
                                prePath = "src/" if (fileName.endswith(".c")) else ""
                                fileSym = AddMarkupFile(
                                              fileName,  #File Name 
                                              "",        #id prefix
                                              basecomponent, #Component
                                              mupPathDrv + prePath,
                                              dstPathDrv + prePath, False,
                                              projPathDrv + prePath)
                            else:
                                #NOTE:  standard files in src/drivers
                                prePath = "src/" if fileName.endswith(".c") else ""
                                fileSym = AddFileName(
                                              fileName,  #File Name 
                                              "",        #id prefix
                                              basecomponent, #Component
                                              srcPathDrv + prePath,
                                              dstPathDrv + prePath, False,
                                              projPathDrv + prePath)
                        #API Files
                        elif (fileName[:4] == "MCHP"):
                            if fileName.endswith(".ftl"):
                                fileName = fileName[:len(fileName) - 4]
                                prePath = "src/" if fileName.endswith(".c") else ""
                                #NOTE:  API markup files in templates/driver
                                #       --but generated to src/common_crypto
                                fileSym = AddMarkupFile(
                                              fileName,  #File Name 
                                              "",        #id prefix
                                              basecomponent, #Component
                                              mupPathDrv + prePath,
                                              dstPathApi + prePath, False,
                                              projPathApi + prePath)
                            else:
                                prePath = "src/" if fileName.endswith(".c") else ""
                                fileSym = AddFileName(
                                              fileName,  #File Name 
                                              "",        #id prefix
                                              basecomponent, #Component
                                              srcPathDrv + prePath,
                                              dstPathApi + prePath, False,
                                              projPathApi + prePath)
                        else:
                            print("CRYPTO HW: Unknown ""%s"""%(fileName))
                            continue

                        #New File Added
                        fileNames.update([fileName]) #Add new file
                                            #Add the symbol to the hwDriverFile Dict

                        #Add the file Symbol to the dict list of Driver file names for
                        #that function key (fKey)
                        #--this dict used by function menu selection to enable/disable driver
                        #  file generation
                        g.hwDriverFileDict[fKey].append(fileSym)
                        print(" [%s] %s"%(fKey,fileSym.getOutputName()))
                        fileNames.update([fileName]) #Add new file

                    else:
                        print("CRYPTO HW: Duplicate ""%s"""%(fileName))

                #Add the extra driver files for the given function(fKey) and HW
                #list to enable/disable from the menu
                #TODO:  Disabling from the menu disables the files from being
                #       included from other menus that use these files.
                #       this should be fixed by checking the other menu
                #       selections that could be using these driver files .
                #if (dKey=="CPKCC"):   #used by ECC/ECDH/ECDSA
                #    g.hwDriverFileDict[fKey] += g.cpkclDriverFileSyms


################################################################################
# Detect MCU Target HW support for each particular crypto function
# by scanning the ATDF file.
# --Set HW Symbols to enable the implementation in the .ftl file
# --HW Driver symbols enabled if the hardware is available.
#   (symbol ID same as the HW define strings).  Symbol in list HwDriverSymbol 
# --HW Driver Define strings generated to crypto_config.h
#
################################################################################
def SetupHardwareSupport(cryptoComponent) :

    print("CRYPTO:  HW Scan")

    g.cryptoHwSupportedSymbol= cryptoComponent.createBooleanSymbol(
            "cryptoHwSupported", None)
    g.cryptoHwSupportedSymbol.setVisible(False)
    g.cryptoHwSupportedSymbol.setLabel("Crypto HW Supported")
    g.cryptoHwSupportedSymbol.setDefaultValue(False)

    ##########################
    #TRNG
    g.cryptoHwTrngSupported = False
    g.hwFunctionDriverDict["TRNG"] = ScanHardware(g.cryptoHwTrngSupport)
    if (len(g.hwFunctionDriverDict["TRNG"]) != 0): g.cryptoHwTrngSupported = True
    if (g.cryptoHwTrngSupported): print("CRYPTO HW:  HW TRNG SUPPORTED")

    ##########################
    #HASH

    #------
    g.cryptoHwMd5Supported = False
    g.hwFunctionDriverDict["MD5"] = ScanHardware(g.cryptoHwMd5Support)
    if (len(g.hwFunctionDriverDict["MD5"]) == 2): g.cryptoHwMd5Supported = True
    if (g.cryptoHwMd5Supported): print("CRYPTO HW:  HW MD5 SUPPORTED")


    #------
    g.cryptoHwSha1Supported = False
    g.hwFunctionDriverDict["SHA1"] = ScanHardware(g.cryptoHwSha1Support)
    if (len(g.hwFunctionDriverDict["SHA1"]) == 2): g.cryptoHwSha1Supported = True
    if (g.cryptoHwSha1Supported): print("CRYPTO HW:  HW SHA1 SUPPORTED")

    #------
    #SHA2

    g.cryptoHwSha224Supported = False
    driver = ScanHardware(g.cryptoHwSha224Support)
    if (len(driver) == 2): g.cryptoHwSha224Supported = True
    if (g.cryptoHwSha224Supported): print("CRYPTO HW:  HW SHA224 SUPPORTED")

    #NOTE: Always assume HW SHA support has at least SHA256
    g.cryptoHwShaSupported = False
    g.cryptoHwSha256Supported = False
    g.hwFunctionDriverDict["SHA"] = ScanHardware(g.cryptoHwSha256Support)
    if (len(g.hwFunctionDriverDict["SHA"]) == 2):
        g.cryptoHwSha256Supported = True
        g.cryptoHwShaSupported = True 
    if (g.cryptoHwSha256Supported): print("CRYPTO HW:  HW SHA256 SUPPORTED")

    g.cryptoHwSha384Supported = False
    driver = ScanHardware(g.cryptoHwSha384Support)
    if (len(driver) == 2): g.cryptoHwSha384Supported = True
    if (g.cryptoHwSha384Supported): print("CRYPTO HW:  HW SHA384 SUPPORTED")

    g.cryptoHwSha512Supported = False
    driver = ScanHardware(g.cryptoHwSha512Support)
    if (len(driver) == 2): g.cryptoHwSha512Supported = True
    if (g.cryptoHwSha512Supported): print("CRYPTO HW:  HW SHA512 SUPPORTED")


    ##########################
    #AES 
    g.cryptoHwSymAes128Supported = False
    driver = ScanHardware(g.cryptoHwSymAes128Support)
    if (len(driver) == 2): g.cryptoHwSymAes128Supported = True
    if (g.cryptoHwSymAes128Supported): print("CRYPTO HW:  HW AES 128 SUPPORTED")

    g.cryptoHwSymAes192Supported = False 
    driver = ScanHardware(g.cryptoHwSymAes192Support)
    if (len(driver) == 2): g.cryptoHwSymAes192Supported = True
    if (g.cryptoHwSymAes192Supported): 
        print("CRYPTO HW:  HW AES 192 SUPPORTED")

    #NOTE: Always assume HW AES support has at least AES256
    g.cryptoHwAesSupported =False 
    g.cryptoHwSymAes256Supported = False
    g.hwFunctionDriverDict["AES"] = ScanHardware(g.cryptoHwSymAes256Support)
    if (len(g.hwFunctionDriverDict["AES"]) == 2):
        g.cryptoHwSymAes256Supported = True
        g.cryptoHwSymAesSupported = True 
    if (g.cryptoHwSymAes256Supported): print("CRYPTO HW:  HW AES256 SUPPORTED")

    if (g.cryptoHwSymAes128Supported or g.cryptoHwSymAes128Supported or
        g.cryptoHwSymAes192Supported or g.cryptoHwSymAes256Supported):
        g.cryptoHwSymAesSupported = True
        print("CRYPTO HW:  HW AES SUPPORTED")
    else:
        #print("CRYPTO HW:  HW AES NOT SUPPORTED")
        g.cryptoHwSymAesSupported = False

    #AES Modes
    g.cryptoHwSymAesEcbSupported = False
    devices = ScanHardware(g.cryptoHwSymAesEcbSupport)
    if (len(devices) == 2): g.cryptoHwSymAesEcbSupported = True

    g.cryptoHwSymAesCbcSupported  = False
    devices = ScanHardware(g.cryptoHwSymAesCbcSupport)
    if (len(devices) == 2): g.cryptoHwSymAesCbcSupported = True

    g.cryptoHwSymAesCtrSupported  = False
    devices = ScanHardware(g.cryptoHwSymAesCtrSupport)
    if (len(devices) == 2): g.cryptoHwSymAesCtrSupported = True

    g.cryptoHwSymAesCfb1Supported  = False
    devices = ScanHardware(g.cryptoHwSymAesCfb1Support)
    if (len(devices) == 2): g.cryptoHwSymAesCfb1Supported = True

    g.cryptoHwSymAesCfb8Supported  = False
    devices  = ScanHardware(g.cryptoHwSymAesCfb8Support)
    if (len(devices) == 2): g.cryptoHwSymAesCfb8Supported = True

    g.cryptoHwSymAesCfb64Supported   = False
    devices  = ScanHardware(g.cryptoHwSymAesCfb64Support)
    if (len(devices) == 2): g.cryptoHwSymAesCfb64Supported = True

    g.cryptoHwSymAesCfb128Supported  = False
    devices  = ScanHardware(g.cryptoHwSymAesCfb128Support)
    if (len(devices) == 2): g.cryptoHwSymAesCfb128Supported = True

    g.cryptoHwSymAesOfbSupported     = False
    devices  = ScanHardware(g.cryptoHwSymAesOfbSupport)
    if (len(devices) == 2): g.cryptoHwSymAesOfbSupported = True

    g.cryptoHwSymAesCcmSupported     = False
    devices  = ScanHardware(g.cryptoHwSymAesCcmSupport)
    if (len(devices) == 2): g.cryptoHwSymAesCcmSupported = True

    g.cryptoHwSymAesXtsSupported     = False
    devices  = ScanHardware(g.cryptoHwSymAesXtsSupport)
    if (len(devices) == 2): g.cryptoHwSymAesXtsSupported = True

    g.cryptoHwSymAesGcmSupported     = False
    devices  = ScanHardware(g.cryptoHwSymAesGcmSupport)
    if (len(devices) == 2): g.cryptoHwSymAesGcmSupported = True

    g.cryptoHwSymAesEaxSupported     = False
    devices  = ScanHardware(g.cryptoHwSymAesEaxSupport)
    if (len(devices) == 2): g.cryptoHwSymAesEaxSupported = True

    #======
    #AES Key Wrap
    g.cryptoHwSymAesKwSupported = False
    devices  = ScanHardware(g.cryptoHwSymAesKwSupport)
    if (len(devices) == 2): g.cryptoHwSymAesKwSupported = True


    ##########################
    #AEAD-AES 
    g.cryptoHwAeadAesSupported = False
    g.hwFunctionDriverDict["AEAD"] = ScanHardware(g.cryptoHwAeadAesSupport)
    if (len(g.hwFunctionDriverDict["AEAD"]) == 2): g.cryptoHwAeadAesSupported = True
    if (g.cryptoHwAeadAesSupported): print("CRYPTO HW:  HW AEAD AES SUPPORTED")

    g.cryptoHwAeadAesGcmSupported = False
    driver = ScanHardware(g.cryptoHwAeadAesGcmSupport)
    if (len(driver) == 2): g.cryptoHwAeadAesGcmSupported = True
    if (g.cryptoHwAeadAesGcmSupported): print("CRYPTO HW:  HW AEAD AES Gcm SUPPORTED")

    g.cryptoHwAeadAesCcmSupported = False
    driver = ScanHardware(g.cryptoHwAeadAesCcmSupport)
    if (len(driver) == 2): g.cryptoHwAeadAesCcmSupported = True
    if (g.cryptoHwAeadAesCcmSupported): print("CRYPTO HW:  HW AEAD AES Ccm SUPPORTED")

    g.cryptoHwAeadAesEaxSupported = False
    driver = ScanHardware(g.cryptoHwAeadAesEaxSupport)
    if (len(driver) == 2): g.cryptoHwAeadAesEaxSupported = True
    if (g.cryptoHwAeadAesEaxSupported): print("CRYPTO HW:  HW AEAD AES Eax SUPPORTED")

    g.cryptoHwAeadAesSivCmacSupported = False
    driver = ScanHardware(g.cryptoHwAeadAesSivCmacSupport)
    if (len(driver) == 2): g.cryptoHwAeadAesSivCmacSupported = True
    if (g.cryptoHwAeadAesSivCmacSupported): print("CRYPTO HW:  HW AEAD AES SivCmac SUPPORTED")

    g.cryptoHwAeadAesSivGcmSupported = False
    driver = ScanHardware(g.cryptoHwAeadAesSivGcmSupport)
    if (len(driver) == 2): g.cryptoHwAeadAesSivGcmSupported = True
    if (g.cryptoHwAeadAesSivGcmSupported): print("CRYPTO HW:  HW AEAD AES SivGcm SUPPORTED")


    if (g.cryptoHwAeadAesSupported): print("CRYPTO HW:  HW AEAD-AES SUPPORTED")
    else: print("CRYPTO HW:  HW AEAD-AES NOT SUPPORTED")

    #======
    #HMAC

    ##########################
    #ASYM - Asymmetric Crypto

    #======
    #DES
    g.cryptoHwDesSupported    = False
    g.cryptoHwDesSupported = False
    g.hwFunctionDriverDict["DES"] = ScanHardware(g.cryptoHwDesSupport)
    if (len(g.hwFunctionDriverDict["DES"]) == 2):
        g.cryptoHwDesSupported = True
    if (g.cryptoHwDesSupported): print("CRYPTO HW:  HW ASYM DES SUPPORTED")


    g.cryptoHwDesCbcSupported = False
    driver = ScanHardware(g.cryptoHwDesCbcSupport)
    if (len(driver) == 2): g.cryptoHwDesCbcSupported = True
    if (g.cryptoHwDesCbcSupported): print("CRYPTO HW:  HW ASYM DES Cbc SUPPORTED")

    g.cryptoHwDesCfbSupported = False
    driver = ScanHardware(g.cryptoHwDesCfbSupport)
    if (len(driver) == 2): g.cryptoHwDesCfbSupported = True
    if (g.cryptoHwDesCfbSupported): print("CRYPTO HW:  HW ASYM DES Cfb SUPPORTED")

    g.cryptoHwDesOfbSupported = False
    driver = ScanHardware(g.cryptoHwDesOfbSupport)
    if (len(driver) == 2): g.cryptoHwDesOfbSupported = True
    if (g.cryptoHwDesOfbSupported): print("CRYPTO HW:  HW ASYM DES Ofb SUPPORTED")

    #======
    #RSA
    g.cryptoHwAsymRsaSupported    = ScanHardware(g.cryptoHwAsymRsaSupport)
    if (g.cryptoHwAsymRsaSupported):
        print("CRYPTO HW:  HW ASYM RSA SUPPORTED")
    else:
        g.cryptoHwAsymRsaSupported = False

    #NOTE: Always assume HW AES support has at least AES256
    g.cryptoHwAsymRsaSupported =False 
    g.hwFunctionDriverDict["RSA"] = ScanHardware(g.cryptoHwAsymRsaSupport)
    if (len(g.hwFunctionDriverDict["RSA"]) == 2):
        g.cryptoHwAsymRsaSupported = True
    if (g.cryptoHwAsymRsaSupported): print("CRYPTO HW:  HW ASYM RSA SUPPORTED")


    #======
    #ECC
    g.cryptoHwAsymEccSupported =False 
    g.hwFunctionDriverDict["ECC"] = ScanHardware(g.cryptoHwAsymEccSupport)
    if (len(g.hwFunctionDriverDict["ECC"]) == 2):
        g.cryptoHwAsymEccSupported = True
    if (g.cryptoHwAsymEccSupported): print("CRYPTO HW:  HW ASYM ECC SUPPORTED")

    #-----
    #DS - Digital Signing
    #DS ECDSA
    g.cryptoHwDsEcdsaSupported =False 
    g.hwFunctionDriverDict["ECDSA"] = ScanHardware(g.cryptoHwDsEcdsaSupport)
    if (len(g.hwFunctionDriverDict["ECDSA"]) == 2):
        g.cryptoHwDsEcdsaSupported = True
    if (g.cryptoHwDsEcdsaSupported): print("CRYPTO HW:  HW DS ECDSA SUPPORTED")

    #-----
    #KAS ECDH
    g.cryptoHwKasEcdhSupported    = ScanHardware(g.cryptoHwKasEcdhSupport)
    if (g.cryptoHwKasEcdhSupported):
        print("CRYPTO HW:  HW KAS-ECDH SUPPORTED")
    else:
        g.cryptoHwKasEcdhSupported = False

    g.cryptoHwKasEcdhSupported =False 
    g.hwFunctionDriverDict["ECDH"] = ScanHardware(g.cryptoHwKasEcdhSupport)
    if (len(g.hwFunctionDriverDict["ECDH"]) == 2):
        g.cryptoHwKasEcdhSupported = True
    if (g.cryptoHwKasEcdhSupported): print("CRYPTO HW:  HW KAS ECDH SUPPORTED")

    #======
    #HW Modules
    g.cryptoHW_U2803Present   = ScanHardware(g.cryptoHW_U2803)
    g.cryptoHW_U2803Present   = False
    driver = ScanHardware(g.cryptoHW_U2803)
    if (len(driver) == 2): g.cryptoHW_U2803Present = True

    g.cryptoHW_U2805Present   = ScanHardware(g.cryptoHW_U2805)
    g.cryptoHW_U2805Present   = False
    driver = ScanHardware(g.cryptoHW_U2805)
    if (len(driver) == 2): g.cryptoHW_U2805Present = True

    g.cryptoHW_03710Present   = ScanHardware(g.cryptoHW_03710)
    g.cryptoHW_03710Present   = False
    driver = ScanHardware(g.cryptoHW_03710)
    if (len(driver) == 2): g.cryptoHW_03710Present = True

    if (g.cryptoHwTrngSupported     or  g.cryptoHwMd5Supported or
        g.cryptoHwSha1Supported     or
        g.cryptoHwSha224Supported   or  g.cryptoHwSha256Supported or
        g.cryptoHwSha384Supported   or  g.cryptoHwSha512Supported or
        g.cryptoHwSymAesSupported      or  g.cryptoHwDesSupported or
        g.cryptoHwAsymRsaSupported      or  g.cryptoHwAsymEccSupported or
        g.cryptoHwDsEcdsaSupported):
        g.cryptoHwSupported = True
    else:
        g.cryptoHwSupported = False

    if (g.cryptoHwSupported == True):
        g.cryptoHwSupportedSymbol.setValue(True)
    else:
        g.cryptoHwSupportedSymbol.setValue(False)

    #String Implementation of defines for crypto_config.h.ftl
    #--created from each of the additional define strings
    g.cryptoHwDefines.setDefaultValue(", ".join(g.cryptoHwAdditionalDefines))

    #Create symbols for all possible HW Drivers
    print("CRYPTO HW: %d Symbols --"%(len(g.cryptoHwAdditionalDefines)))
    for defStr in g.hwDriverStrings:
        #Create the driver symbol
        #--Initially true
        g.hwDriverSymbol.append(cryptoComponent.createBooleanSymbol(
                defStr, None))
        g.hwDriverSymbol[-1].setVisible(False)
        g.hwDriverSymbol[-1].setLabel("Crypto HW Driver Supported")

        #Only enable file generation for supported drivers
        if (defStr in g.cryptoHwAdditionalDefines):
            g.hwDriverSymbol[-1].setDefaultValue(True) 
        else:
            g.hwDriverSymbol[-1].setDefaultValue(False) 
        print("    (%s)%s"%(g.hwDriverSymbol[-1].getValue(),
                            g.hwDriverSymbol[-1].getID()) )

    #Now generate the Drivers for the available crypto HW
    SetupHwDriverFiles(cryptoComponent)

    #Enable the peripheral clocks for available crypto HW
    #TODO:  Only enable clocks when the driver function is selected.
    #       For now always enable.
    SetupHwPeripheralClocks(cryptoComponent)


################################################################################
################################################################################
def SetupHwPeripheralClocks(baseComponent):
    configName = Variables.get("__CONFIGURATION_NAME")  # e.g. "default"
    processor  = Variables.get("__PROCESSOR")
    Log.writeInfoMessage("Crypto: Project MCU  " + processor)

    #TODO:  Enable peripheral clocks for Enabled Mistral Crypto/Trng HW
    #  Database.clearSymbolValue("core", trngInstanceName.getValue()+"_CLOCK_ENABLE")
    #
    #if (HAVE_MCHP_CRYPTO_TRNG_HW_6334 in g.cryptoHwAdditionalDefines):
    #    Database.setSymbolValue("core", trngInstanceName.getValue()+"_CLOCK_ENABLE", True, 2)
    #  Database.setSymbolValue("core", aesInstanceName.getValue()+"_CLOCK_ENABLE", True, 2)
    #  Database.setSymbolValue("core", shaInstanceName.getValue()+"_CLOCK_ENABLE", True, 2)
    #  Database.setSymbolValue("core", cpkccInstanceName.getValue()+"_CLOCK_ENABLE", True, 2)
    return



################################################################################
# Files that are alway set to be generated (irregardless of GUI configuration)
# settings.
# --Called from Harmony3 MHC instantiateComponent function
################################################################################
def AddAlwaysOnFiles(cryptoComponent):
    print("CRYPTO: Always on files")

    configName = Variables.get("__CONFIGURATION_NAME")  # e.g. "default"
    configPath = "config/" + configName 

    #--------------------------------------------------------------------------------------
    #Harmony Common Crypto (cc) System Files
    g.trustZoneFileIds = []

    #<config>/definitions.h include files for the crypto component API and
    #Wolfcrypt implementation
    srcPath = "templates/system/system_definitions.h.ftl"
    ccSystemDefIncFile = cryptoComponent.createFileSymbol("DRV_CC_SYSTEM_DEF", None)
    if (g.trustZoneSupported == True):
        ccSystemDefIncFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_SECURE_H_INCLUDES")
        g.trustZoneFileIds.append(ccSystemDefIncFile.getID())
        print("CRYPTO:  Adding (TZ) %s"%(srcPath))
    else:
        ccSystemDefIncFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
        print("CRYPTO:  Adding  %s"%(srcPath))
    ccSystemDefIncFile.setSourcePath(srcPath)
    ccSystemDefIncFile.setMarkup(True)
    ccSystemDefIncFile.setType("STRING")

    #<config>/initialization.c - Add Driver Initialization code
    srcPath = "templates/system/system_initialize.c.ftl"
    ccSystemInitFile = cryptoComponent.createFileSymbol(
            "DRV_CC_SYS_INIT", None)
    ccSystemInitFile.setType("STRING")
    if (g.trustZoneSupported == True):
        ccSystemInitFile.setOutputName(
                "core.LIST_SYSTEM_INIT_SECURE_C_SYS_INITIALIZE_DRIVERS")
        print("CRYPTO:  Adding (TZ) %s"%(srcPath))
        g.trustZoneFileIds.append(ccSystemInitFile.getID())
    else:
        ccSystemInitFile.setOutputName(
                "core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS")
        print("CRYPTO:  Adding %s"%(srcPath))
    ccSystemInitFile.setSourcePath(srcPath)
    ccSystemInitFile.setMarkup(True)

    #<config>/crypto_config.h 
    fileName    = "crypto_config_wolfcrypt_hw.h.ftl"
    outName     = "crypto_config.h"
    projectPath    = "config/" + configName
    srcPath     = "templates/"
    dstPath     = ""
    ccSysConfigFile= cryptoComponent.createFileSymbol(
            "DRV_CC_SYSTEM_CONFIG", None)
    ccSysConfigFile.setSourcePath(srcPath + fileName)
    ccSysConfigFile.setMarkup(True)
    ccSysConfigFile.setOutputName(outName)
    ccSysConfigFile.setDestPath("")
    ccSysConfigFile.setProjectPath(projectPath)
    ccSysConfigFile.setType("HEADER")
    ccSysConfigFile.setOverwrite(True)
    if (g.trustZoneSupported == True):
        ccSysConfigFile.setSecurity("SECURE")
        g.trustZoneFileIds.append(ccSysConfigFile.getID())
        print("CRYPTO(C):  Adding (TZ) %s"%(srcPath+fileName))
    else:
        print("CRYPTO(C):  Adding %s"%(srcPath+fileName))



################################################################################
################################################################################
# GUI Selection and Attachement Callbacks
################################################################################

################################################################################
#-----------------------------------------------------
#TrustZone
#  TODO:  Make TrustZone optional
#def handleTzEnabled(symbol, event):
    #if (g.cryptoTzEnabledSymbol.getValue() == True):
        #Set TrustZone <filelist>.setSecurity("SECURE")
    #else:
        #UnSet TrustZone <filelist>.setSecurity("NON_SECURE")

def onAttachmentConnected(source, target):

    print("CRYPTO: Connected" + source["component"].getID() + "to dst " + target["component"].getID())

    if (source["component"].getID() == "lib_wolfcrypt"):
        g.cryptoWolfCryptIncluded = True
        print("CRYPTO: lib_wolfcrypt support connected")

def onAttachmentDisconnected(source, target):
    print("CRYPTO: Detached " + source["component"].getID() + "to dst " + target["component"].getID())

    if (source["component"].getID() == "lib_wolfcrypt"):
        print("CRYPTO: lib_wolfcrypt support DISconnected")

    #TODO: put in wolfcrypt.py
    #if (target["component"].getID() == "sys_time"):
        #g.asn1Support.setValue(False)
        #asn1Support.setReadOnly(True)
        #cryptoTrngEnabledSymbol.setValue(False)
        #cryptoTrngEnabledSymbol.setReadOnly(True)
