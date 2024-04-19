# coding: utf-8
"""*****************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

################################################################################
#### Global Variables ####
################################################################################

global interruptsChildren
interruptsChildren = ATDF.getNode('/avr-tools-device-file/devices/device/interrupts').getChildren()



def instantiateComponent(ba414ecomponent):
    global InterruptVector
    global InterruptHandlerLock
    global InterruptHandler
    global InterruptVectorUpdate
    global ba414eSymInterruptMode

    InterruptVector = []
    InterruptHandler = []
    InterruptHandlerLock = []
    InterruptVectorUpdate = []

    #Clock enable
    Database.setSymbolValue("core", "BA414E_CLOCK_ENABLE", True, 1)

    ba414e = ba414ecomponent.createBooleanSymbol("BA414E_ENABLED", None)
    ba414e.setLabel("Use ba414e?")
    ba414e.setDescription("Enables ba414e")
    ba414e.setVisible(False)
    ba414e.setDefaultValue(True)
    
    ba414eObjects = ba414ecomponent.createIntegerSymbol("BA414E_MAX_CLIENTS", None)
    ba414eObjects.setLabel("Number of Clients")
    ba414eObjects.setMax(50)
    ba414eObjects.setMin(1)
    ba414eObjects.setDefaultValue(5)

    ba414eSymInterruptMode = ba414ecomponent.createBooleanSymbol("BA414E_INTERRUPT_MODE", None)
    ba414eSymInterruptMode.setLabel("Enable Interrupts ?")
    ba414eSymInterruptMode.setDefaultValue(True)
    ba414eSymInterruptMode.setDependencies(ba414InterruptMenu, ["BA414E_INTERRUPT_MODE"])
    
    # RTOS Configuration
    ba414eRtosMenu = ba414ecomponent.createMenuSymbol("BA414E_RTOS_MENU", None)
    ba414eRtosMenu.setLabel("RTOS Configuration")
    ba414eRtosMenu.setDescription("RTOS Configuration")
    ba414eRtosMenu.setVisible(False)
    ba414eRtosMenu.setVisible((Database.getSymbolValue("HarmonyCore", "SELECT_RTOS") != "BareMetal") and (Database.getSymbolValue("HarmonyCore", "SELECT_RTOS") != None))
    ba414eRtosMenu.setDependencies(ba414eshowRTOSMenu, ["HarmonyCore.SELECT_RTOS"])
    
    # BA414E Execution mode
    ba414eExecMode = ba414ecomponent.createComboSymbol("BA414E_RTOS", ba414eRtosMenu, ["Standalone"]) 
    ba414eExecMode.setLabel("Run this driver instance as")
    ba414eExecMode.setVisible(False)
    ba414eExecMode.setDescription("BA414E Execution mode")
    ba414eExecMode.setDefaultValue("Standalone")
    
    # BA414E Task Stack Size
    ba414eTaskSize = ba414ecomponent.createIntegerSymbol("BA414E_RTOS_STACK_SIZE", ba414eRtosMenu)
    ba414eTaskSize.setLabel("Stack Size")
    ba414eTaskSize.setVisible(True)
    ba414eTaskSize.setDescription("BA414E Task Stack Size")
    ba414eTaskSize.setDefaultValue(1024)
    ba414eTaskSize.setDependencies(ba414eRTOSStandaloneMenu, ["BA414E_RTOS"])
    
    # BA414E Task Priority
    ba414eTaskPriority = ba414ecomponent.createIntegerSymbol("BA414E_RTOS_TASK_PRIORITY", ba414eRtosMenu)
    ba414eTaskPriority.setLabel("Task Priority")
    ba414eTaskPriority.setVisible(True)
    ba414eTaskPriority.setDescription("BA414E Task Priority")
    ba414eTaskPriority.setDefaultValue(1)
    ba414eTaskPriority.setDependencies(ba414eRTOSStandaloneMenu, ["BA414E_RTOS"])
    
    # BA414E Task Delay?
    ba414eUseTaskDelay = ba414ecomponent.createBooleanSymbol("BA414E_RTOS_USE_DELAY", ba414eRtosMenu)
    ba414eUseTaskDelay.setLabel("Use Task Delay?")
    ba414eUseTaskDelay.setVisible(True)
    ba414eUseTaskDelay.setDescription("BA414E Use Task Delay?")
    ba414eUseTaskDelay.setDefaultValue(False)
    ba414eUseTaskDelay.setDependencies(ba414eRTOSStandaloneMenu, ["BA414E_RTOS"])
    
    # BA414E Task Delay
    ba414eTaskDelay = ba414ecomponent.createIntegerSymbol("BA414E_RTOS_DELAY", ba414eRtosMenu)
    ba414eTaskDelay.setLabel("Task Delay")
    ba414eTaskDelay.setVisible(False)
    ba414eTaskDelay.setDescription("BA414E Task Delay")
    ba414eTaskDelay.setDefaultValue(1000)
    ba414eTaskDelay.setDependencies(ba414eRTOSTaskDelayMenu, ["BA414E_RTOS","BA414E_RTOS_USE_DELAY"])
    
    setInteruptStatus(ba414eSymInterruptMode.getValue())
    
    # add "<#include \"/crypto/drivers/ba414e/templates/system_init.c.data.ftl\">"  to list SYSTEM_INIT_C_MODULE_INITIALIZATION_DATA
    ba414eSysInitDataSourceFtl = ba414ecomponent.createFileSymbol(None, None)
    ba414eSysInitDataSourceFtl.setType("STRING")
    ba414eSysInitDataSourceFtl.setOutputName("core.LIST_SYSTEM_INIT_C_LIBRARY_INITIALIZATION_DATA")
    ba414eSysInitDataSourceFtl.setSourcePath("drivers/ba414e/templates/system/system_data_initialize.c.ftl")
    ba414eSysInitDataSourceFtl.setMarkup(True)
    
    # add "<#include \"/crypto/drivers/ba414e/templates/system_init.c.call.ftl\">"  to list SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE
    ba414eSysInitCallSourceFtl = ba414ecomponent.createFileSymbol(None, None)
    ba414eSysInitCallSourceFtl.setType("STRING")
    ba414eSysInitCallSourceFtl.setOutputName("core.LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE")
    ba414eSysInitCallSourceFtl.setSourcePath("drivers/ba414e/templates/system/system_initialize.c.ftl")
    ba414eSysInitCallSourceFtl.setMarkup(True)

    ba414eSystemDefFile = ba414ecomponent.createFileSymbol(None, None)
    ba414eSystemDefFile.setType("STRING")
    ba414eSystemDefFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    ba414eSystemDefFile.setSourcePath("drivers/ba414e/templates/system/system_definitions.h.ftl")
    ba414eSystemDefFile.setMarkup(True)
    
    ba414eSystemDefObjFile = ba414ecomponent.createFileSymbol(None, None)
    ba414eSystemDefObjFile.setType("STRING")
    ba414eSystemDefObjFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_OBJECTS")
    ba414eSystemDefObjFile.setSourcePath("drivers/ba414e/templates/system/system_definitions_object.h.ftl")
    ba414eSystemDefObjFile.setMarkup(True)
    
    ba414eSystemConfigFtl = ba414ecomponent.createFileSymbol(None, None)
    ba414eSystemConfigFtl.setSourcePath("drivers/ba414e/templates/system/system_config.h.ftl")
    ba414eSystemConfigFtl.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    ba414eSystemConfigFtl.setMarkup(True)
    ba414eSystemConfigFtl.setType("STRING")
    
    # add "<#include \"/crypto/drivers/ba414e/templates/system_tasks.c.ftl\">"  to list SYSTEM_TASKS_C_CALL_LIB_TASKS
    ba414eSysTaskSourceFtl = ba414ecomponent.createFileSymbol(None, None)
    ba414eSysTaskSourceFtl.setType("STRING")
    ba414eSysTaskSourceFtl.setOutputName("core.LIST_SYSTEM_TASKS_C_CALL_LIB_TASKS")
    ba414eSysTaskSourceFtl.setSourcePath("drivers/ba414e/templates/system/system_tasks.c.ftl")
    ba414eSysTaskSourceFtl.setMarkup(True)

    ba414eSystemRtosTasksFile = ba414ecomponent.createFileSymbol("DRV_BA414E_SYS_RTOS_TASK", None)
    ba414eSystemRtosTasksFile.setType("STRING")
    ba414eSystemRtosTasksFile.setOutputName("core.LIST_SYSTEM_RTOS_TASKS_C_DEFINITIONS")
    ba414eSystemRtosTasksFile.setSourcePath("drivers/ba414e/templates/system/system_rtos_tasks.c.ftl")
    ba414eSystemRtosTasksFile.setMarkup(True)
    ba414eSystemRtosTasksFile.setEnabled((Database.getSymbolValue("HarmonyCore", "SELECT_RTOS") != "BareMetal"))
    ba414eSystemRtosTasksFile.setDependencies(genRtosTask, ["HarmonyCore.SELECT_RTOS"])

    setupFiles(ba414ecomponent)
    
    

def ba414eshowRTOSMenu(symbol, event):
    if (event["value"] == None):
        symbol.setVisible(False)
        print("BA414E: OSAL Disabled")
    elif (event["value"] != "BareMetal"):
        # If not Bare Metal
        symbol.setVisible(True)
        print("BA414E rtos")
    else:
        symbol.setVisible(False)
        print("BA414E Bare Metal") 


def ba414eRTOSStandaloneMenu(symbol, event):
    if (event["value"] == 'Standalone'):        
        symbol.setVisible(True)
        print("ba414e Standalone")
    else:
        symbol.setVisible(False)
        print("ba414e Combined")       

def ba414eRTOSTaskDelayMenu(symbol, event):
    ba414eRtos = Database.getSymbolValue("ba414e","BA414E_RTOS")
    ba414eRtosUseDelay = Database.getSymbolValue("ba414e","BA414E_RTOS_USE_DELAY")
    if((ba414eRtos == 'Standalone') and ba414eRtosUseDelay):      
        symbol.setVisible(True)
    else:
        symbol.setVisible(False)

def getVectorIndex(string):

    vector_index = "-1"

    for param in interruptsChildren:
        name = str(param.getAttribute("name"))
        if string == name:
            vector_index = str(param.getAttribute("index"))
            break

    return vector_index
    
def setInteruptStatus(status):
    ba414eIntIndex = getVectorIndex("CRYPTO1")
    ba414eErrorIntIndex = getVectorIndex("CRYPTO1_FAULT")
    print("BA414E:Set Interrupt Status EVIC_" + str(ba414eIntIndex) + "_ENABLE " + str(status) )

    Database.setSymbolValue("core", "EVIC_" + str(ba414eIntIndex) + "_ENABLE", status, 1)
    Database.setSymbolValue("core", "EVIC_" + str(ba414eErrorIntIndex) + "_ENABLE", status, 1)
    
    Database.setSymbolValue("core", "EVIC_" + str(ba414eIntIndex) + "_HANDLER_LOCK", status, 1)
    Database.setSymbolValue("core", "EVIC_" + str(ba414eErrorIntIndex) + "_HANDLER_LOCK", status, 1)

    if status == True:
        Database.setSymbolValue("core", "EVIC_" + str(ba414eIntIndex) + "_INTERRUPT_HANDLER", "DRV_BA414E_InterruptHandler", 1)
        Database.setSymbolValue("core", "EVIC_" + str(ba414eErrorIntIndex) + "_INTERRUPT_HANDLER", "DRV_BA414E_ErrorInterruptHandler", 1)
    else:
        Database.setSymbolValue("core", "EVIC_" + str(ba414eIntIndex) + "_INTERRUPT_HANDLER", "BA414E_Handler", 1)
        Database.setSymbolValue("core", "EVIC_" + str(ba414eErrorIntIndex) + "_INTERRUPT_HANDLER", "BA414E_ErrorHandler", 1)


def ba414InterruptMenu(symbol, event):
    enable = symbol.getValue()
    setInteruptStatus(enable)
    
def genRtosTask(symbol, event):
    symbol.setEnabled((Database.getSymbolValue("HarmonyCore", "SELECT_RTOS") != "BareMetal"))
    
    
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

    filename.setEnabled(enabled)


def setupFiles(basecomponent) :
    global cryptoOverridableSrcFiles
    global cryptoOverridableHeaderFiles
    driverSourceFiles = get_script_dir() + "/../drivers/ba414e/src/*.c"
    driverPublicHeaderFiles = get_script_dir() + "/../drivers/ba414e/*.h"
    driverPrivateHeaderFiles = get_script_dir() + "/../drivers/ba414e/src/*.h"
    

    dsfl = trimFileNameList(glob.glob(driverSourceFiles))
    dphfl = trimFileNameList(glob.glob(driverPublicHeaderFiles))
    dhfl = trimFileNameList(glob.glob(driverPrivateHeaderFiles))
    configName = Variables.get("__CONFIGURATION_NAME")
    
    for file in dsfl:
        addFileName(file, "ba414e", basecomponent, "drivers/ba414e/src/", "driver/ba414e/src/", True, "config/" + configName + "/driver/ba414e/src")

    for file in dhfl:
        addFileName(file, "ba414e", basecomponent, "drivers/ba414e/src/", "driver/ba414e/src/", True, "config/" + configName + "/driver/ba414e/src")

    for file in dphfl:
        addFileName(file, "ba414e", basecomponent, "drivers/ba414e/", "driver/ba414e/", True, "config/" + configName + "/driver/ba414e/")
    