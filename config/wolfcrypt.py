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
#import crypto_globals               #Initial globals
import crypto_defs           as g   #Modified globals

if (g.trustZoneSupported != None): 
    print("WOLFCRYPT: Start Component Module (TZ)")
else:
    print("WOLFCRYPT: Start Component Module")

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

    if Variables.get("__TRUSTZONE_ENABLED") != None and Variables.get("__TRUSTZONE_ENABLED") == "true":
        w.trustZoneSupported = True
        print("WOLFCRYPT:  TRUST_ZONE is true")
    else:
        print("WOLFCRYPT:  TRUST_ZONE NOT true")

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

    #Configuration GUI
    w.cryptoHaveZlib = wolfCryptComponent.createBooleanSymbol("wolfcrypt_havezlib", None)
    w.cryptoHaveZlib.setVisible(False)
    w.cryptoHaveZlib.setDefaultValue(False)

    #w.cryptoSupportCompression = wolfCryptComponent.createBooleanSymbol("wolfcrypt_supportcompression", None)
    #w.cryptoSupportCompression.setLabel("Support Compression?")
    #w.cryptoSupportCompression.setDescription("Add support for zLib compression")
    #w.cryptoSupportCompression.setVisible(False)
    #w.cryptoSupportCompression.setDefaultValue(False)
    #w.cryptoSupportCompression.setHelp('CRYPT_HUFMANN_SUM')


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

def AddFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
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
    if (w.trustZoneSupported != None): 
        if (w.trustZoneSupported == True):
            #Set TrustZone <filelist>.setSecurity("SECURE")
            filename.setSecurity("SECURE")
            print("WOLFCRYPT:  Adding (TZ) ""%s"" "%(projectPath + fileName))
        else:
            #UnSet TrustZone <filelist>.setSecurity("NON_SECURE")
            filename.setSecurity("NON_SECURE")
            print("WOLFCRYPT:  Adding ""%s"" "%(projectPath + fileName))

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
        AddFileName(file, "wolfcrypt", basecomponent,
                    "../wolfssl/wolfcrypt/src/",
                    "../../third_party/wolfssl/wolfcrypt/src/",
                    True, "/third_party/wolfssl/wolfcrypt/src")

    #All header files in the wolfssl/wolfcrypt directory
    #All header files in the component wolfssl/wolfssl/wolfcrypt directory
    #--Headers expected at third_party/wolfssl/wolfssl/wolfcrypt directory
    #--Except the overrides
    print("WOLFCRYPT: Header files")
    for file in wchfl:
        AddFileName(file, "wolfcrypt", basecomponent,
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
        AddFileName(file, "wolfcryptport", basecomponent,
                    "../wolfssl/wolfcrypt/src/port/pic32/",
                    "../../third_party/wolfssl/wolfcrypt/src/port/pic32/",
                    True, "third_party/wolfssl/wolfcrypt/port/pic32")

    ##--All hdr files in the third_party/wolfssl/wolfssl/wolfcrypt/port/pic32 
    print("WOLFCRYPT: Port Header files")
    for file in wcphfl:
        AddFileName(file, "wolfcryptport", basecomponent,
                    "../wolfssl/wolfssl/wolfcrypt/port/pic32/",
                    "../../third_party/wolfssl/wolfssl/wolfcrypt/port/pic32/",
                    True, "third_party/wolfssl/wolfcrypt/port/pic32")

    #All files in  thirdparty/wolfssl/wolfssl/wolfcrypt/src/port/mplabharmony3
    #directory
    #--Except the overrides

    print("WOLFCRYPT: Special Files")
    #misc.c 
    AddFileName("misc.c", "misc", basecomponent,
                "../wolfssl/wolfcrypt/src/",
                "../../third_party/wolfssl/wolfssl/wolfcrypt/src/",
                True, 
                "third_party/wolfssl/wolfssl/src/wolfcrypt")

    #certs_test.h
    AddFileName("certs_test.h", "wolfcrypt", basecomponent,
                "../wolfssl/wolfssl/",
                "../../third_party/wolfssl/wolfssl/",
                True, "third_party/wolfssl/wolfssl")

    #evp.c
    AddFileName("evp.c", "misc", basecomponent,
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
    # AddFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
    # --Filename from direct srcpath to project directory relative destpath
    #
    #AddFileName("config.h", "misc", basecomponent,
    #            "config/",
    #            "../../third_party/wolfssl",
    #            True, "third_party/wolfssl")

    #Global Preprocessor define - HAVE_CONFIG_H
    #NOTE:  Used by WolfSSL library to use the config.h, which includes the
    #       project configuration.h
    wolfcryptConfigH = basecomponent.createSettingSymbol("wolfsslConfigH", None)
    wolfcryptConfigH.setCategory("C32")
    wolfcryptConfigH.setKey("preprocessor-macros")
    wolfcryptConfigH.setValue("HAVE_CONFIG_H")
    wolfcryptConfigH.setAppend(True, ";")
    if (w.trustZoneSupported == True):
        wolfcryptConfigH.setSecurity("SECURE")

    #Global Preprocessor define - WOLFSSL_USER_SETTINGS
    #NOTE:  Used by WolfSSL library to use the user_settings.h, which includes
    #       the project configuration.h
    wolfcryptUserSettingsH= basecomponent.createSettingSymbol("wolfsslUserSettingsH", None)
    wolfcryptUserSettingsH.setCategory("C32")
    wolfcryptUserSettingsH.setKey("preprocessor-macros")
    wolfcryptUserSettingsH.setValue("WOLFSSL_USER_SETTINGS")
    wolfcryptUserSettingsH.setAppend(True, ";")
    if (w.trustZoneSupported == True):
        wolfcryptUserSettingsH.setSecurity("SECURE")

    #Global Preprocessor define - WOLFSSL_IGNORE_FILE_WARN
    wolfcryptIgnoreFileWarn = basecomponent.createSettingSymbol("wolfsslIgnoreFileWarn", None)
    wolfcryptIgnoreFileWarn.setCategory("C32")
    wolfcryptIgnoreFileWarn.setKey("preprocessor-macros")
    wolfcryptIgnoreFileWarn.setValue("WOLFSSL_IGNORE_FILE_WARN")
    wolfcryptIgnoreFileWarn.setAppend(True, ";")
    if (w.trustZoneSupported == True):
        wolfcryptIgnoreFileWarn.setSecurity("SECURE")

    #TODO:
    #Header file search path
    #wolfcryptSearchPath = basecomponent.setPath("..\src\third_party\wolfssl\wolfssl")


def onAttachmentConnected(source, target):
    print("WOLFCRYPT: Attached " + target["component"].getID())

    #ZLIB
    if (target["component"].getID() == "lib_zlib"):
        w.cryptoHaveZlib.setValue(True)
        #w.cryptoSupportCompression.setVisible(True)

    #SYS_TIME Dependency
    #if ((target["component"].getID() == 'sys_time') or
    #    (source["component"].getID() == 'LIB_WOLFCRYPT_Dependency')):
    #    #asn1Support.setReadOnly(False)
    #    cryptoTrngEnabledSymbol.setReadOnly(False)
    #    cryptoTrngEnabledSymbol.setValue(True)


def onAttachmentDisconnected(source, target):
    print("WOLFCRYPT: Detached " + target["component"].getID())

    #ZLIB
    if (target["component"].getID() == "lib_zlib"):
        w.cryptoHaveZlib.setValue(False)
        #w.cryptoSupportCompression.setVisible(False)


    #SYS_TIME
    #if (target["component"].getID() == "sys_time"):
    #    asn1Support.setValue(False)
    #    #asn1Support.setReadOnly(True)
    #    cryptoTrngEnabledSymbol.setValue(False)
    #    cryptoTrngEnabledSymbol.setReadOnly(True)
