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

import crypto_globals               #Initial globals
import crypto_defs           as g   #Modified globals
import crypto_hash_menu      as hm  #HASH GUI
import crypto_symmetric_menu as sm  #Symmetric Menu
import crypto_aead_menu      as am  #Aead Menu
import crypto_mac_menu       as mm  #Hmac Menu
import crypto_digsign_menu   as ds  #Digital Signing Menu
import crypto_kas_menu       as kas #Key Auth Menu
import crypto_rng_menu       as rng #rng Menu

src_ext      = ('.c')
hdr_ext      = ('.h')
mipslib_ext  = ('.a')


#*******************************************************************************
# Adds File to project database and enables/disables it
# --Root Parent
def AddFileName(fileName, prefix, component,
                srcPath, destPath, enabled, projectPath):
    fileID = prefix + fileName.replace('.', '_')
    fileNameSymbol = component.createFileSymbol(fileID, None)
    fileNameSymbol.setProjectPath(projectPath)
    fileNameSymbol.setSourcePath(srcPath + fileName)
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
        print("CRYPTO:  Adding (TZ=%s) ""%s"" "%(tz, projectPath + fileName))
    else:
        fileNameSymbol.setSecurity("NON_SECURE")
        tz = "N" 
        print("CRYPTO:  Adding ""%s"" "%(projectPath + fileName))

    return (fileID, tz)


def get_script_dir(follow_symlinks=True):
    if getattr(sys, 'frozen', False): # py2exe, PyInstaller, cx_Freeze
        path = os.path.abspath(sys.executable)
    else:
        path = inspect.getabsfile(get_script_dir)
    if follow_symlinks:
        path = os.path.realpath(path)
    return os.path.dirname(path)


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
        (symid, tz) = AddFileName(fileName,                     #Filename 
                         "common_crypto",              #MCC Symbol Name Prefix
                         basecomponent,                #MCC Component
                         "src/common_crypto/",         #Src Path
                         "crypto/common_crypto/",      #Dest Path
                         True,                         #Enabled
                         projectPath) #Project Path

    projectPath = "config/" + configName + "/crypto/common_crypto/src/"
    for fileName in ccpsfl_trim:
        (symid, tz) = AddFileName(fileName,                     #Filename    
                         "common_crypto",              #MCC Symbol Name Prefix
                         basecomponent,                #MCC Component
                         "src/common_crypto/src/",     #Path Src
                         "crypto/common_crypto/src/",  #Path Dest
                         True,                         #Enabled
                         projectPath)



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

    #cryptoAdditionalHwDefines = cryptoComponent.createStringSymbol(
    #                                 "cryptoAdditionalHwDefines", None)
    #cryptoAdditionalHwDefines.setVisible(False)

    g.localCryptoComponent = cryptoComponent

    #Scan ATDF for Hardware suport
    #TODO:  Run Hardware Support (Next Release)
    #setupHardwareSupport()

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

    #----------------------------------------------------------------
    #WOLFCRYPT Library Configuration as used by CRYPTO component 
    #
    #TODO:  Has dependency on Wolfcrypt component 
    #       Always generated for now.
    #
    #TODO: Header file search path (get this to work) 
    #wolfcryptSearchPath = basecomponent.setPath("..\src\config\crypto\wolfcrypt")
    #wolfcryptSearchPath = basecomponent.setPath("..\src\third_party\wolfssl\wolfssl")
    #wolfcryptSearchPath = basecomponent.setPath("..\src\third_party\wolfssl\wolfssl")

    #Project Include Path Directories
    if (g.trustZoneSupported == True):
        ccIncludePath = cryptoComponent.createSettingSymbol("XC32_CRYPTO_SECURE_INCLUDE_DIRS", None)
        ccIncludePath.setSecurity("SECURE")
    else:
        ccIncludePath = cryptoComponent.createSettingSymbol("XC32_CRYPTO_INCLUDE_DIRS", None)
    ccIncludePath.setCategory("C32")
    ccIncludePath.setKey("extra-include-directories")
    ccIncludePath.setValue( "../src/third_party/wolfssl/wolfssl/wolfcrypt"
                            + ";../src/third_party/wolfssl"
                            + ";../src/third_party/wolfcrypt"
                            + ";../src/config/" + configName + "/crypto/wolfcrypt")
    ccIncludePath.setAppend(True, ";")


    #<config>/MCHP_Crypto_Hash_Config.h - API File
    projectPath = "config/" + configName + "/crypto/common_crypto/"
    

    #INCLUDE FILE to configure WOLFCRYPT with the HAVE_CONFIG_H 
    #project define.
    (symid, tz) = AddFileName("config.h",                   #Filename    
                     "common_crypto",              #MCC Symbol Name Prefix
                     cryptoComponent,                #MCC Component
                     "src/wolfcrypt/",             #Src Path
                     "crypto/wolfcrypt/",          #Dest Path
                     True,                         #Enabled
                     projectPath)                  #Project Path

    #INCLUDE FILE to configure WOLFCRYPT with the WOLFSSL_USER_SETTINGS 
    #Project define
    (symid, tz) = AddFileName("user_settings.h",            #Filename    
                     "common_crypto",              #MCC Symbol Name Prefix
                     cryptoComponent,                #MCC Component
                     "src/wolfcrypt/",             #Path Src
                     "crypto/wolfcrypt/",          #Path Dest
                     True,                         #Enabled
                     projectPath)                  #Project Path

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
    hm.SetupCryptoHashMenu(g.localCryptoComponent)

    #<config>/MCHP_Crypto_Hash_Config.h - API File
    #fileName    = "MCHP_Crypto_Hash_Config.h"
    #TODO:  Enable Dependency on CONFIG_USE_HASH
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
        print("CRYPTO:  Adding HASH=%s "" "%(
                   g.CONFIG_USE_HASH.getValue(), projectPath + fileName + ".ftl" ))


    #SYM Function Group
    #--CONFIG_USE_SYM
    sm.SetupCryptoSymmetricMenu(g.localCryptoComponent)

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
        print("CRYPTO:  Adding SYM=%s "" "%(
                   g.CONFIG_USE_SYM.getValue(), projectPath + fileName + ".ftl" ))

    #AEAD Function Group
    #--CONFIG_USE_AEAD
    am.SetupCryptoAeadMenu(g.localCryptoComponent)

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
        print("CRYPTO:  Adding AEAD=%s "" "%(
                   g.CONFIG_USE_AEAD.getValue(), projectPath + fileName + ".ftl" ))

    #MAC Function Group
    #--CONFIG_USE_MAC
    mm.SetupCryptoMacMenu(g.localCryptoComponent)

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
        print("CRYPTO:  Adding MAC=%s "" "%(
                   g.CONFIG_USE_MAC.getValue(), projectPath + fileName + ".ftl" ))

    #KAS - Key Authorization Function Group
    #--CONFIG_USE_KAS
    kas.SetupCryptoKasMenu(g.localCryptoComponent)

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
        print("CRYPTO:  Adding KAS=%s "" "%(
                   g.CONFIG_USE_KAS.getValue(), projectPath + fileName + ".ftl" ))

    #DS - Digital Signing Function Group
    #--CONFIG_USE_DS
    ds.SetupCryptoDsMenu(g.localCryptoComponent)

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
        print("CRYPTO:  Adding DS=%s "" "%(
                   g.CONFIG_USE_DS.getValue(), projectPath + fileName + ".ftl" ))

    #RNG - Digital Signing Function Group
    #--CONFIG_USE_RNG
    rng.SetupCryptoRngMenu(g.localCryptoComponent)

    #<config>/MCHP_Crypto_Rng_Config.h - API File
    fileName    = "MCHP_Crypto_RNG_Config.h"
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
        print("CRYPTO:  Adding RNG=%s "" "%(
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
# Scan the ATDF file for hardware module names given in the list items
# where each item is a dictionary given by:
# [ <Module name>, <Modula ID number>, "",
#   <list of driver files>,            <set of HW symbols>)]
#
################################################################################
def scanHardware(list):
    periphNode = ATDF.getNode("/avr-tools-device-file/devices/device/peripherals")
    modules = periphNode.getChildren()
    for module in modules:
        for item in list:
            if (
                (module.getAttribute("name")      == item[0]) and
                (module.getAttribute("id")        == item[1]) and
                (((module.getAttribute("version") == item[2]) or
                  item[2] == ""))):
                #NOTE: item[3] Symbols used by FTL doesn't seem to be used.
                #print(item[4])
                g.cryptoHwAdditionalDefines = g.cryptoHwAdditionalDefines.union(item[4])
                #print(cryptoHwAdditionalDefines)
                #print("CRYPTO HSM:  %s (%s) %s (%s) %s (%s)"%(
                #    module.getAttribute("name"),    item[0],
                #    module.getAttribute("id"),      item[1],
                #    module.getAttribute("version"), item[2]))
                return True
    return False

################################################################################
# Detect MCU Target HW support for each particular crypto function
# by scanning the ATDF file.
#
# crypto<hw function>Supported
#
################################################################################
def setupHardwareSupport() :

    print("CRYPTO:  Scan HW Support")
    g.cryptoHwTrngSupported   = scanHardware(g.cryptoHwTrngSupport)

    #HASH
    g.cryptoHwMd5Supported    = scanHardware(g.cryptoHwMd5Support)
    g.cryptoHwSha1Supported   = scanHardware(g.cryptoHwSha1Support)
    g.cryptoHwSha224Supported = scanHardware(g.cryptoHwSha224Support)
    g.cryptoHwSha256Supported = scanHardware(g.cryptoHwSha256Support)
    g.cryptoHwSha384Supported = scanHardware(g.cryptoHwSha384Support)
    g.cryptoHwSha512Supported = scanHardware(g.cryptoHwSha512Support)

    #AES
    g.cryptoHwAes128Supported    = scanHardware(g.cryptoHwAes128Support)
    g.cryptoHwAes192Supported    = scanHardware(g.cryptoHwAes192Support)
    g.cryptoHwAes256Supported    = scanHardware(g.cryptoHwAes256Support)
    g.cryptoHwAesCbcSupported    = scanHardware(g.cryptoHwAesCbcSupport)
    g.cryptoHwAesCtrSupported    = scanHardware(g.cryptoHwAesCtrSupport)
    g.cryptoHwAesCfb1Supported   = scanHardware(g.cryptoHwAesCfb1Support)
    g.cryptoHwAesCfb8Supported   = scanHardware(g.cryptoHwAesCfb8Support)
    g.cryptoHwAesCfb64Supported  = scanHardware(g.cryptoHwAesCfb64Support)
    g.cryptoHwAesCfb128Supported = scanHardware(g.cryptoHwAesCfb128Support)
    g.cryptoHwAesOfbSupported    = scanHardware(g.cryptoHwAesOfbSupport)
    g.cryptoHwAesXtsSupported    = scanHardware(g.cryptoHwAesXtsSupport)
    g.cryptoHwAesGcmSupported    = scanHardware(g.cryptoHwAesGcmSupport)
    g.cryptoHwAesCcmSupported    = scanHardware(g.cryptoHwAesCcmSupport)

    #AEAD

    #HMAC

    #DES
    g.cryptoHwDesSupported    = scanHardware(g.cryptoHwDesSupport)
    g.cryptoHwDesCbcSupported = scanHardware(g.cryptoHwDesCbcSupport)
    g.cryptoHwDesCfbSupported = scanHardware(g.cryptoHwDesCfbSupport)
    g.cryptoHwDesOfbSupported = scanHardware(g.cryptoHwDesOfbSupport)

    #RSA
    g.cryptoHwRsaSupported    = scanHardware(g.cryptoHwRsaSupport)

    #ECC
    g.cryptoHwEccSupported    = scanHardware(g.cryptoHwEccSupport)

    #HW Modules
    g.cryptoHW_U2803Present   = scanHardware(g.cryptoHW_U2803)
    g.cryptoHW_U2805Present   = scanHardware(g.cryptoHW_U2805)
    g.cryptoHW_03710Present   = scanHardware(g.cryptoHW_03710)

    if (g.cryptoHwAes128Supported or g.cryptoHwAes128Supported or
        g.cryptoHwAes192Supported or g.cryptoHwAes256Supported):
        g.cryptoHwAesSupported = True
        #print("CRYPTO HW:  HW AES SUPPORTED")
    else:
        #print("CRYPTO HW:  HW AES NOT SUPPORTED")
        g.cryptoHwAesSupported = False

    if (g.cryptoHwTrngSupported     or  g.cryptoHwMd5Supported or
        g.cryptoHwSha1Supported     or
        g.cryptoHwSha224Supported   or  g.cryptoHwSha256Supported or
        g.cryptoHwSha384Supported   or  g.cryptoHwSha512Supported or
        g.cryptoHwAesSupported      or  g.cryptoHwDesSupported or
        g.cryptoHwRsaSupported      or  g.cryptoHwEccSupported):
        g.cryptoHwSupported = True
    else:
        g.cryptoHwSupported = False

    #g.cryptoAdditionalHwDefines.setDefaultValue(", ".join(g.cryptoHwAdditionalDefines))
    #print(g.cryptoAdditionalHwDefines.getValue())


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
    #Wolfcrypto implementation
    srcPath = "templates/system/system_definitions.h.ftl"
    ccSystemDefIncFile = cryptoComponent.createFileSymbol("DRV_CC_SYSTEM_DEF", None)
    if (g.trustZoneSupported == True):
        ccSystemDefIncFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_SECURE_H_INCLUDES")
        tz = "S"
        g.trustZoneFileIds.append(ccSystemDefIncFile.getID())
        print("CRYPTO:  Adding (TZ=%s) %s"%(tz, srcPath))
    else:
        ccSystemDefIncFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
        print("CRYPTO:  Adding  %s"%(srcPath))
    ccSystemDefIncFile.setSourcePath(srcPath)
    ccSystemDefIncFile.setMarkup(True)
    ccSystemDefIncFile.setType("STRING")

    #<config>/configuration.h - Add CC Driver Configuration 
    if (g.trustZoneSupported == True):
        srcPath  = "templates/system/"
        fileName = "system_config_wolfcrypt_tz.h.ftl"
        projectPath = "config/" + configName + "/crypto/common_crypto/"
        dstPath     = "",
        outName     = "configuration_tz.h"
        ccSystemConfigFile = cryptoComponent.createFileSymbol(
                "DRV_CC_SYSTEM_CONFIG_TZ", None)
        ccSystemConfigFile.setOutputName(outName)
        ccSystemConfigFile.setDestPath(destPath)
        ccSystemConfigFile.setProjectPath(projectPath)
        ccSystemConfigFile.setSourcePath(srcPath + fileName)
        ccSystemConfigFile.setMarkup(True)
        ccSystemConfigFile.setType("STRING")
        ccSystemConfigFile.setSecurity("SECURE")
        g.trustZoneFileIds.append(ccSystemConfigFile.getID())
        print("CRYPTO:  Adding (TZ) %s"%(srcPath+fileName))
    else:
        srcPath = "templates/system/system_config.h.ftl"
        ccSystemConfigFile = cryptoComponent.createFileSymbol(
                "DRV_CC_SYSTEM_CONFIG", None)
        ccSystemConfigFile.setOutputName(
            "core.LIST_SYSTEM_CONFIG_H_DRIVER_CONFIGURATION")
        ccSystemConfigFile.setSourcePath(srcPath)
        ccSystemConfigFile.setMarkup(True)
        ccSystemConfigFile.setType("STRING")
        print("CRYPTO:  Adding (NS) %s"%(srcPath))

    #<config>/initialization.c - Add Driver Initialization code
    srcPath = "templates/system/system_initialize.c.ftl"
    ccSystemInitFile = cryptoComponent.createFileSymbol(
            "DRV_CC_SYS_INIT", None)
    ccSystemInitFile.setType("STRING")
    if (g.trustZoneSupported == True):
        ccSystemInitFile.setOutputName(
                "core.LIST_SYSTEM_INIT_SECURE_C_SYS_INITIALIZE_DRIVERS")
        print("CRYPTO:  Adding (TZ=S) %s"%(srcPath))
        g.trustZoneFileIds.append(ccSystemInitFile.getID())
    else:
        ccSystemInitFile.setOutputName(
                "core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS")
        print("CRYPTO:  Adding %s"%(srcPath))
    ccSystemInitFile.setSourcePath(srcPath)
    ccSystemInitFile.setMarkup(True)


################################################################################
#  TODO: NOT USED.  This looks like a menu function that is not being used.
#        Could use this for the sub-menu items to the General HW Enable 
################################################################################
def setHwEnabledMenuItems(enable):
    for symbol in cryptoHwMenuComponentsList:
        if enable:
            if symbol.getLabel()[-2:] != "HW":
                symbol.setLabel(symbol.getLabel() + " - HW")
        else:
            if symbol.getLabel()[-2:] == "HW":
                symbol.setLabel(symbol.getLabel()[:-5])


################################################################################
################################################################################
# GUI Selection and Attachement Callbacks
################################################################################

################################################################################
#-----------------------------------------------------
#TrustZone
#  TODO:  This is to make TrustZone optional
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

    if (src["component"].getID() == "lib_wolfcrypt"):
        print("CRYPTO: lib_wolfcrypt support DISconnected")

    if (target["component"].getID() == "lib_zlib"):
        g.cryptoHaveZlib.setValue(False)
        #g.cryptoSupportCompression.setVisible(False)

    #TODO: put in wolfcrypt.py
    #if (target["component"].getID() == "sys_time"):
        #g.asn1Support.setValue(False)
        #asn1Support.setReadOnly(True)
        #cryptoTrngEnabledSymbol.setValue(False)
        #cryptoTrngEnabledSymbol.setReadOnly(True)
