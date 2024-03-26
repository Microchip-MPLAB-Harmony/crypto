# coding: utf-8
"""*****************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************"""
import inspect
import os
import sys
import glob
import ntpath

modulePath =  Module.getPath()
sys.path.append(modulePath + "config")
import wolfcrypt_globals
import wolfcrypt_defs        as w
import crypto_globals               #Initial globals
import crypto_defs           as g   #Modified globals
print("WOLFCRYPT: Start")

#===============================================================================
#OVERRIDE Files  
#--These are WolfSSL files used by the WolfCrypt library that are found in
#  wolfssl/wolfssl/wolfcrypt directory
#cryptoOverridableSrcFiles    = ["aes.c", "des3.c", "random.c", "sha.c", "sha256.c", "sha512.c", ]
#cryptoOverridableSrcFiles    = ["aes.c", "sha.c", "sha256.c", "sha512.c", ]
cryptoOverridableSrcFiles    = []
#cryptoOverridableHeaderFiles = ["aes.h", "sha.h", "sha256.h", "sha512.h", "types.h", "settings.h","wc_port.h",]
cryptoOverridableHeaderFiles = []


def instantiateComponent(wolfCryptComponent):

    #TODO:  Dependency on SysTime module
    global cryptoHaveSysTime
    global cryptoDependSysTime

    #global asn1Support

    #cryptoAdditionalHwDefines = wolfCryptComponent.createStringSymbol("wolfCryptAdditionalHwDefines", None)
    #cryptoAdditionalHwDefines.setVisible(False)
    w.localwolfCryptComponent = wolfCryptComponent

    setupWolfCryptFiles(w.localwolfCryptComponent)

    #---------------------------------------------------------------------------
    #wolfCrypt Library
    wolfcrypt = wolfCryptComponent.createBooleanSymbol("wolfcrypt", None)
    wolfcrypt.setLabel("Use wolfCrypt?")
    wolfcrypt.setDescription("Enables wolfCrypt")
    wolfcrypt.setVisible(False)
    wolfcrypt.setDefaultValue(True)


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

def addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
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

    #TrustZone - TODO:  Make TrustZone optional configuration
    g.trustZoneFileIds.append(filename.getID())
    if (g.trustZoneSupported == True):
        #Set TrustZone <filelist>.setSecurity("SECURE")
        filename.setSecurity("SECURE")
    else:
        #UnSet TrustZone <filelist>.setSecurity("NON_SECURE")
        filename.setSecurity("NON_SECURE")

    filename.setEnabled(enabled)

################################################################################
#  Add General File Componenent to Project
################################################################################
def createFileComponent(baseComponent, fileName, srcPath, destPath):
    fileComp = baseComponent.createFileSymbol(fileName.replace('.', '_'), None)
    fileComp.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME") + "/crypto")
    fileComp.setSourcePath(srcPath + fileName)
    fileComp.setOutputName(fileName)
    fileComp.setDestPath(destPath)

    if fileName[-2:] == '.h':
        fileComp.setType("HEADER")
    else:
        fileComp.setType("SOURCE")

    #TrustZone
    g.trustZoneFileIds.append(fileComp.getID())
    if (g.trustZoneEnabled.getValue() == True):
        #Set TrustZone <filelist>.setSecurity("SECURE")
        fileNameSymbol.setSecurity("SECURE")
    else:
        #UnSet TrustZone <filelist>.setSecurity("NON_SECURE")
        fileNameSymbol.setSecurity("NON_SECURE")

    return fileComp


################################################################################
# Setup all 3rd Party WolfCrypt Library Files
################################################################################
def setupWolfCryptFiles(basecomponent) :

    #global cryptoOverridableSrcFiles
    #global cryptoOverridableHeaderFiles

    print("WOLFCRYPT: get_script_dir -> %s"%(get_script_dir()))

    ## Wolfcrypt Lib Src/Header
    wolfCryptSourceFiles        = get_script_dir() + "/../../wolfssl/wolfcrypt/src/*.c"
    wolfCryptHeaderFiles        = get_script_dir() + "/../../wolfssl/wolfssl/wolfcrypt/*.h"

    #print("WOLFCRYPT: Source files (Non Override)")
    wcsfrl = glob.glob(wolfCryptSourceFiles)
    wcsfl  = []
    for file in wcsfrl:
        filename = ntpath.basename(file)
        if ((not (filename in cryptoOverridableSrcFiles)) and
            (filename != "misc.c") and (filename != "evp.c")):
            wcsfl.append(filename)
        #else:
            #print("WOLFCRYPT:  Override File %s"%filename)

    #print("WOLFCRYPT: Header files (Non Override)")
    wcshrl = glob.glob(wolfCryptHeaderFiles)
    wchfl = []
    for file in wcshrl:
        filename = ntpath.basename(file)
        if ((not (filename in cryptoOverridableHeaderFiles))):
            wchfl.append(filename)
        #else:
            #print("WOLFCRYPT:  Override File %s"%filename)

    #All src files in the component wolfssl/wolfcrypt/src directory
    #--Except the overrides
    print("WOLFCRYPT: Source files")
    for file in wcsfl:
        addFileName(file, "wolfcrypt", basecomponent,
                    "../wolfssl/wolfcrypt/src/",
                    "../../third_party/wolfssl/wolfcrypt/src/",
                    True, "/third_party/wolfssl/wolfcrypt/src")

    #All header files in the wolfssl/wolfcrypt directory
    #All header files in the component wolfssl/wolfssl/wolfcrypt directory
    #--Headers expected at third_party/wolfssl/wolfssl/wolfcrypt directory
    #--Except the overrides
    print("WOLFCRYPT: Header files")
    for file in wchfl:
        addFileName(file, "wolfcrypt", basecomponent,
                    "../wolfssl/wolfssl/wolfcrypt/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/",
                    True, "/third_party/wolfssl/wolfssl/wolfcrypt")

    ##WolfCrypt Port Source/Header Files
    wolfCryptPortSourceFiles    = get_script_dir() + "/../../wolfssl/wolfcrypt/src/port/pic32/*.c"
    wolfCryptPortHeaderFiles    = get_script_dir() + "/../../wolfssl/wolfssl/wolfcrypt/port/pic32/*.h"
    wcpsfl = trimFileNameList(glob.glob(wolfCryptPortSourceFiles))
    wcphfl = trimFileNameList(glob.glob(wolfCryptPortHeaderFiles))

    ##--All src files in the third_party/wolfssl/wolfcrypt/src/port/pic32 
    print("WOLFCRYPT: Port Source files")
    for file in wcpsfl:
        addFileName(file, "wolfcryptport", basecomponent,
                    "../wolfssl/wolfcrypt/src/port/pic32/",
                    "../../third_party/wolfssl/wolfcrypt/src/port/pic32/",
                    True, "third_party/wolfssl/wolfcrypt/port/pic32")

    ##--All hdr files in the third_party/wolfssl/wolfssl/wolfcrypt/port/pic32 
    print("WOLFCRYPT: Port Header files")
    for file in wcphfl:
        addFileName(file, "wolfcryptport", basecomponent,
                    "../wolfssl/wolfssl/wolfcrypt/port/pic32/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/port/pic32/",
                    True, "third_party/wolfssl/wolfcrypt/port/pic32")

    #All files in  thirdparty/wolfssl/wolfssl/wolfcrypt/src/port/mplabharmony3
    #directory
    #--Except the overrides
    '''
    harmonyCryptPortSourceFiles = get_script_dir() + "/../src/common_crypto_api/port/mplabharmony3/*.c"
    harmonyCryptPortHeaderFiles = get_script_dir() + "/../src/common_crypto_api/port/mplabharmony3/*.h"

    hcpsfl = trimFileNameList(glob.glob(harmonyCryptPortSourceFiles))
    hcphfl = trimFileNameList(glob.glob(harmonyCryptPortHeaderFiles))

    print("WOLFCRYPT: Port Source files")
    for file in hcpsfl:
        addFileName(file, "cryptoport", basecomponent,
                    "src/port/mplabharmony3/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/",
                    True, "wolfcrypt/port/pic32")

    #All Harmony header files in  src/port/mplabharmony3
    for file in hcphfl:
        addFileName(file, "cryptoport", basecomponent,
                    "src/port/mplabharmony3/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/port/pic32/",
                    True, "wolfcrypt/port/pic32")
    '''

    '''
    #All the crypto override src files
    print("WOLFCRYPT: OVERRIDE Source files")
    #for file in cryptoOverridableSrcFiles:
    #    addFileName(
    #          file, 
    #          "cryptooverride", #basecomponent, 
    #          "src/", 
    #           "../../third_party/wolfssl/wolfssl/wolfcrypt/src/", 
    #           True, "wolfcrypt")

    for file in cryptoOverridableSrcFiles:
        addFileName(file, "cryptooverride", basecomponent,
                    "src/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/src/",
                    True, "third_party/wolfssl/wolfssl/wolfcrypt")

    #All the crypto override header files
    #NOTE: Overrides in third_party project directory
    print("WOLFCRYPT: OVERRIDE Header files")
    for file in cryptoOverridableHeaderFiles:
        print("  --Override Header %s"%(file))
        #addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
        addFileName(file, 
                    "cryptooverride", 
                    basecomponent,
                    "src/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/",
                    True, 
                    "third_party/wolfssl/wolfssl/wolfcrypt")
    '''

    print("WOLFCRYPT: Special Files")
    #misc.c 
    addFileName("misc.c", "misc", basecomponent,
                "../wolfssl/wolfcrypt/src/",
                "../../third_party/wolfssl/wolfssl/wolfcrypt/src/",
                True, 
                "third_party/wolfssl/wolfssl/src/wolfcrypt")

    #certs_test.h
    addFileName("certs_test.h", "wolfcrypt", basecomponent,
                "../wolfssl/wolfssl/",
                "../../third_party/wolfssl/wolfssl/",
                True, "third_party/wolfssl/wolfssl")

    #evp.c
    addFileName("evp.c", "misc", basecomponent,
                "../wolfssl/wolfcrypt/src/",
                "../../third_party/wolfssl/wolfssl/wolfcrypt/src/",
                True, "third_party/wolfssl/wolfssl/wolfcrypt")



    #<config>/crypto/wolfssl/config.h 
    #--Used to configure WolfCrypt (includes configuration.h)
    #NOTE(S): (1) The actual wolfcrypt configuration defines are in configuration.h
    #             so they can be used via config.h by WolfSSL
    #         (2) Global project define HAVE_CONFIG_H will enable this for
    #             WolfCrypt
    #
    # createFileComponent(baseComponent, fileName, srcPath, destPath):
    # --Filename from direct srcpath to config/<config name>/destPath 
    #
    # addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
    # --Filename from direct srcpath to project directory relative destpath
    #
    #addFileName("config.h", "misc", basecomponent,
    #            "config/",
    #            "../../third_party/wolfssl",
    #            True, "third_party/wolfssl")

    #<config>/configuration.h - Add WolfCrypt Lib Middleware Configuration
    srcPath  = "templates/system/wolfcrypt_system_config.h.ftl"
    wolfCryptConfigInfo = basecomponent.createFileSymbol("wolfcryptConfigInfo", None)
    wolfCryptConfigInfo.setSourcePath(srcPath)
    wolfCryptConfigInfo.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    wolfCryptConfigInfo.setMarkup(True)
    wolfCryptConfigInfo.setType("STRING")
    print("WOLFCRYPT: Add file %s"%(srcPath))

    #Global Preprocessor define - HAVE_CONFIG_H
    #NOTE:  Used by WolfSSL library to use the config.h, which includes the
    #       project configuration.h
    wolfcryptConfigH = basecomponent.createSettingSymbol("wolfsslConfigH", None)
    wolfcryptConfigH.setCategory("C32")
    wolfcryptConfigH.setKey("preprocessor-macros")
    wolfcryptConfigH.setValue("HAVE_CONFIG_H")
    wolfcryptConfigH.setAppend(True, ";")

    #Global Preprocessor define - WOLFSSL_USER_SETTINGS
    #NOTE:  Used by WolfSSL library to use the user_settings.h, which includes
    #       the project configuration.h
    wolfcryptConfigH = basecomponent.createSettingSymbol("wolfsslUserSettingsH", None)
    wolfcryptConfigH.setCategory("C32")
    wolfcryptConfigH.setKey("preprocessor-macros")
    wolfcryptConfigH.setValue("WOLFSSL_USER_SETTINGS")
    wolfcryptConfigH.setAppend(True, ";")

    #Global Preprocessor define - WOLFSSL_IGNORE_FILE_WARN
    wolfcryptIgnoreFileWarn = basecomponent.createSettingSymbol("wolfsslIgnoreFileWarn", None)
    wolfcryptIgnoreFileWarn.setCategory("C32")
    wolfcryptIgnoreFileWarn.setKey("preprocessor-macros")
    wolfcryptIgnoreFileWarn.setValue("WOLFSSL_IGNORE_FILE_WARN")
    wolfcryptIgnoreFileWarn.setAppend(True, ";")

    #TODO:
    #Header file search path
    #wolfcryptSearchPath = basecomponent.setPath("..\src\third_party\wolfssl\wolfssl")

'''
################################################################################
# Add WolfCrypt File Project
################################################################################
def createWolfCryptFileComponent(baseComponent, fileName, srcPath, destPath):
    global cryptoWolfCryptFilesDict
    if fileName in cryptoWolfCryptFilesDict:
        print("CryptoLib Error: Attempting to add the same file twice: " + fileName)
        return
    fc = createFileComponent(baseComponent, fileName, srcPath, destPath)
    cryptoWolfCryptFilesDict[fileName] = fc


################################################################################
# Add HW Crypto Module Driver File to project
################################################################################
def createHwFileComponent(baseComponent, fileName, srcPath, destPath):

    #Check if already added
    if fileName in g.cryptoWolfCryptFilesDict:
        print("CryptoLib Error: Attempting to add a crypto hardware file that is already a common file: " + fileName)
        return
    if fileName in cryptoHwFileComponentsDict:
        print("CryptoLib Error: Attempting to add the same hardware file twice: " + fileName)
        return
    if fileName in cryptoSwFileComponentsDict:
        print("CryptoLib Info: Adding a HW component that already has a SW component, changing to common component " + fileName)
        fc = cryptoSwFileComponentsDict.pop(fileName)
        g.cryptoWolfCryptFilesDict[fileName] = fc
        return

    print("CRYPTO:  Adding HW file " + filename)
    fc = createFileComponent(baseComponent, fileName, srcPath, destPath)
    cryptoHwFileComponentsDict[fileName] = fc


################################################################################
# Add  SW Crypto File to project
################################################################################
def createSwFileComponent(baseComponent, fileName, srcPath, destPath):
    print("WOLFCRYPT:  Adding " + fileName)
    global cryptoWolfCryptFilesDict
    global cryptoSwFileComponentsDict
    global cryptoHwFileComponentsDict
    if fileName in g.cryptoWolfCryptFilesDict:
        print("CryptoLib Error: Attempting to add a crypto software file that is already a common file: " + fileName)
        return
    if fileName in cryptoSwFileComponentsDict:
        print("CryptoLib Error: Attempting to add the same software file twice: " + fileName)
        return
    if fileName in cryptoHwFileComponentsDict:
        print("CryptoLib Info: Adding a SW component that already has a HW component, changing to common component " + fileName)
        fc = cryptoHwFileComponentsDict.pop(fileName)
        g.cryptoWolfCryptFilesDict[fileName] = fc
        return
    fc = createFileComponent(baseComponent, fileName, srcPath, destPath)
    cryptoSwFileComponentsDict[fileName] = fc


################################################################################
# Create All WolfCrypt Library files 
# TODO:  NOT USED
################################################################################
def createAllFileComponents(baseComponent):

    print("WOLFCRYPT: createAllFileComponents")
    global cryptoWolfCryptFilesList

    #WolfCrypt
    for fileName in cryptoWolfCryptFiles:
        createWolfCryptFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoZlibFiles:
        createWolfCryptFileComponent(baseComponent, fileName, "src/zlib-1.2.7/", "crypto/src/zlib-1.2.7/")

    #HW Module Driver files
    #for fileName in cryptoCurrentHwRngSupport[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwMd5Support[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwSha1Support[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwSha224Support[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwSha256Support[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwSha384Support[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwSha512Support[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwAesSupport[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwDesSupport[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwRsaSupport[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentHwEccSupport[3]:
    #    createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #SW files
    #for fileName in cryptoCurrentSwRngSupport[3]:
    #    createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwMd5Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwSha1Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwSha224Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwSha256Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwSha384Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwSha512Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    for fileName in cryptoCurrentSwAesSupport[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentSwDesSupport[3]:
    #    createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentSwRsaSupport[3]:
    #    createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

    #for fileName in cryptoCurrentSwEccSupport[3]:
    #    createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")


################################################################################
################################################################################
def setFilesForHwSupport(enable):
    print("CRYPTO: Set HW support files")
    for fc in g.cryptoHwFileComponentsDict.values():
        fc.setEnabled(enable)
    for fc in g.cryptoSwFileComponentsDict.values():
        fc.setEnabled(not enable)


################################################################################
################################################################################
def setFilesForWolfSslEnabled(enable):
    print("CRYPTO: Set files for WolfSsl")
    if (enable):
        for fc in g.cryptoWolfCryptFilesDict.values():
            fc.setEnabled(False)
        for fc in g.cryptoHwFileComponentsDict.values():
            fc.setEnabled(False)
        for fc in g.cryptoSwFileComponentsDict.values():
            fc.setEnabled(False)
    else:
        for fc in g.cryptoWolfCryptFilesDict.values():
            fc.setEnabled(True)
        setFilesForHwSupport(g.cryptoWolfCryptEnabledMenuComponentsList[0].value)


'''


def onAttachmentConnected(source, target):
    #global cryptoSupportCompression
    #global asn1Support
    #global cryptoTrngEnabledSymbol

    #WolfSSL
    if (target["component"].getID() == "lib_wolfssl"):
        w.cryptoWolfSSLIncluded.setValue(True)

    print("'" + target["component"].getID() + "'")

    #ZLIB
    if (target["component"].getID() == "lib_zlib"):
        w.cryptoHaveZlib.setValue(True)
        #cryptoSupportCompression.setVisible(True)

    '''
    #SYS_TIME
    if ((target["component"].getID() == 'sys_time') or
        (source["component"].getID() == 'LIB_WOLFCRYPT_Dependency')):
        #asn1Support.setReadOnly(False)
        cryptoTrngEnabledSymbol.setReadOnly(False)
        cryptoTrngEnabledSymbol.setValue(True)
    '''

def onAttachmentDisconnected(source, target):
    #global cryptoSupportCompression
    #global asn1Support

    #WolfSSL
    if (target["component"].getID() == "lib_wolfssl"):
        w.cryptoWolfSSLIncluded.setValue(False)

    print("'" + target["component"].getID() + "'")

    #ZLIB
    if (target["component"].getID() == "lib_zlib"):
        w.cryptoHaveZlib.setValue(False)
        #cryptoSupportCompression.setVisible(False)
    '''
    #SYS_TIME
    if (target["component"].getID() == "sys_time"):
        asn1Support.setValue(False)
        #asn1Support.setReadOnly(True)
        cryptoTrngEnabledSymbol.setValue(False)
        cryptoTrngEnabledSymbol.setReadOnly(True)
    '''
