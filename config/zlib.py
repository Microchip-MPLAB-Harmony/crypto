#/*****************************************************************************
# Copyright (C) 2013-2019 Microchip Technology Inc. and its subsidiaries.
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
# *****************************************************************************/
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

ignoreFiles = ["gzwrite.c", "gzread.c", "gzclose.c", "gzlib.c"]
#ignoreFiles = []



def instantiateComponent(zlibComponent):
    setupFiles(zlibComponent)
    zlibSrcPath = zlibComponent.createSettingSymbol("zlibSrcPath", None)
    zlibSrcPath.setValue("../src/third_party/zlib")
    zlibSrcPath.setCategory("C32")
    zlibSrcPath.setKey("extra-include-directories")
    zlibSrcPath.setAppend(True, ";")


def get_script_dir(follow_symlinks=True):
    if getattr(sys, 'frozen', False): # py2exe, PyInstaller, cx_Freeze
        path = os.path.abspath(sys.executable)
    else:
        path = inspect.getabsfile(get_script_dir)
    if follow_symlinks:
        path = os.path.realpath(path)
    return os.path.dirname(path)


def trimFileNameList(rawList) :
    global ignoreFiles
    newList = []
    for file in rawList:
        filename = ntpath.basename(file)
        if (not(filename in ignoreFiles)):
            newList.append(filename)
        else:
            print("ZLIB: Removed %s"%(filename)) 
            print(newList)
    return newList


def addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
    print("ZLIB: Add " + fileName) 
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


    if (g.trustZoneSupported != None): 
        if (g.trustZoneSupported == True):
            #Set TrustZone <filelist>.setSecurity("SECURE")
            filename.setSecurity("SECURE")
        else:
            #UnSet TrustZone <filelist>.setSecurity("NON_SECURE")
            filename.setSecurity("NON_SECURE")


def setupFiles(basecomponent) :

    zlibSourceFiles = get_script_dir() + "/../../zlib/*.c"
    zlibHeaderFiles = get_script_dir() + "/../../zlib/*.h"

    print("ZLIB:  " + zlibSourceFiles) 
    print("ZLIB:  " + zlibHeaderFiles) 

    #All src/header files in the common/crypto directory
    zphfl = glob.glob(zlibSourceFiles)
    zpsfl = glob.glob(zlibHeaderFiles)
    print("ZLIB: headers(%d) %s"%(len(zphfl),zlibHeaderFiles))
    print("ZLIB: src(%d) %s"%(len(zpsfl),zlibSourceFiles))

    zhfl = trimFileNameList(zphfl)
    zsfl = trimFileNameList(zpsfl)
    print("ZLIB: TR headers(%d)"%(len(zhfl)))
    print(zhfl)
    print("ZLIB: TR src(%d)"%(len(zhfl)))
    print(zsfl)

    for file in zsfl:
        addFileName(file, "zlib", basecomponent, "../zlib/", "../../third_party/zlib/", True, "zlib")

    for file in zhfl:
        addFileName(file, "zlib", basecomponent, "../zlib/", "../../third_party/zlib/", True, "zlib")


def onAttachmentConnected(source, target):
    print("ZLIB:  Attached to " + target["component"].getID())

def onAttachmentDisconnected(source, target):
    print("ZLIB:  Detached to " + target["component"].getID())
