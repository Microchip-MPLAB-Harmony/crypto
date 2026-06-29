"""
Copyright (C) 2013-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

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
"""

import inspect
import os
import sys
import glob
import ntpath

ignoreFiles = ["gzwrite.c", "gzread.c", "gzlib.c"]

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
    return newList
    
    
def addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
    #print("Adding file: " + prefix + fileName.replace('.', '_'))
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

    zlibSourceFiles = get_script_dir() + "/../../zlib/*.c"
    zlibHeaderFiles = get_script_dir() + "/../../zlib/*.h"
    
    zsfl = trimFileNameList(glob.glob(zlibSourceFiles))
    zhfl = trimFileNameList(glob.glob(zlibHeaderFiles))
    
    for file in zsfl:
        addFileName(file, "zlib", basecomponent, "../zlib/", "../../third_party/zlib/", True, "zlib")
        
    for file in zhfl:
        addFileName(file, "zlib", basecomponent, "../zlib/", "../../third_party/zlib/", True, "zlib")

