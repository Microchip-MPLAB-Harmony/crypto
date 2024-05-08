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

import crypto_globals   #Initial globals
import crypto_defs as g #Modified globals
#import superglobals

################################################################################
#Scan to see if any of the Hash Selections is True and set the symbol
#CONFIG_USE_CRYPTO
#--Returns True if CONFIG_USE_DS changes value
################################################################################
def ScanDigSign():
    if   (g.cryptoDsEcdsaEnabledSymbol.getValue()       == True): 
        newValue = True
    else:
        newValue = False

    if (g.CONFIG_USE_DS.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_DS.setValue(newValue)
        print("CRYPO:  CONFIG_USE_DS = %s"%(g.CONFIG_USE_DS.getValue()))
        return True

#Check if the ECDSA is enabled and the ECDSA HW Driver Files are needed.
# TODO:  For now only Mistral 6156. Some mods required for other HW
#--Returns True if the ECDSA HW Driver enable/disable has changed
def ScanDigSignHw():
    retVal = False
    fKey = "ECDSA"

    #DS Scan
    newValue = False
    if (g.cryptoDsEcdsaEnabledSymbol.getValue()   == True):
        if (g.cryptoHwDsEcdsaEnabledSymbol.getValue() == True):
            newValue = True

    if (g.CONFIG_USE_ECDSA_HW.getValue() != newValue):
        g.CONFIG_USE_ECDSA_HW.setValue(newValue)
        print("ECDSA:  Enable HW(%s)"%(newValue))
        for fSym in g.hwDriverFileDict[fKey]:
            fSym.setEnabled(newValue)
        return True
    else:
        print("ECDSA: HW Unchanged (%s)"%(newValue))
        return False



def SetupCryptoDsMenu(cryptoComponent):

    #DS File Generation Enable
    g.CONFIG_USE_DS= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_DS", None)
    g.CONFIG_USE_DS.setVisible(False)
    g.CONFIG_USE_DS.setLabel("Crypto")
    g.CONFIG_USE_DS.setDefaultValue(False)

    #ECDSA File Generation Enable
    g.CONFIG_USE_ECDSA= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_ECDSA", None)
    g.CONFIG_USE_ECDSA.setVisible(False)
    g.CONFIG_USE_ECDSA.setLabel("Crypto ECDSA")
    g.CONFIG_USE_ECDSA.setDefaultValue(False)

    #ECDSA File Generation Enable
    g.CONFIG_USE_ECDSA_HW= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_ECDSA_HW", None)
    g.CONFIG_USE_ECDSA_HW.setVisible(False)
    g.CONFIG_USE_ECDSA_HW.setLabel("Crypto ECDSA HW")
    g.CONFIG_USE_ECDSA_HW.setDefaultValue(False)

    #DS - Crypto DS Algorithms Main Menu
    g.dsMenu = cryptoComponent.createMenuSymbol(
            "crypto_ds_menu", None)
    g.dsMenu.setLabel("Digital Signing Algorithms")
    g.dsMenu.setDescription("Digial Signing Algorithms")
    g.dsMenu.setVisible(True)
    g.dsMenu.setHelp('MC_CRYPTO_DS_API_H')

    #DS - ECDSA Mode
    g.cryptoDsEcdsaEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_ds_ecdsa_en", g.dsMenu)
    g.cryptoDsEcdsaEnabledSymbol.setLabel("ECDSA?")
    g.cryptoDsEcdsaEnabledSymbol.setDescription(
            "Enable support for the Digital Signing ECDSA protocol")
    g.cryptoDsEcdsaEnabledSymbol.setVisible(True)
    g.cryptoDsEcdsaEnabledSymbol.setReadOnly(False)
    g.cryptoDsEcdsaEnabledSymbol.setDefaultValue(True)
    g.cryptoDsEcdsaEnabledSymbol.setHelp('CRYPT_ECDSA_SUM')

    #DS ECDSA HW Symbol
    g.cryptoHwDsEcdsaEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_ds_ecdsa_hw_en", g.cryptoDsEcdsaEnabledSymbol)
    g.cryptoHwDsEcdsaEnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwDsEcdsaEnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the ECDSA Signing Algorithm")
    g.cryptoHwDsEcdsaEnabledSymbol.setVisible(False)
    g.cryptoHwDsEcdsaEnabledSymbol.setDefaultValue(False)
    if ((g.cryptoHwDsEcdsaSupported == True)):
        g.cryptoDsEcdsaEnabledSymbol.setDependencies(
                handleDsEcdsaEnabled, ["crypto_ds_ecdsa_en",
                                       "crypto_ds_ecdsa_hw_en"])
        if (g.cryptoDsEcdsaEnabledSymbol.getValue() == True):
            g.cryptoHwDsEcdsaEnabledSymbol.setVisible(True)
            g.cryptoHwDsEcdsaEnabledSymbol.setDefaultValue(True)

    #Check to see if any of the Ds selections is True
    #--Used to include the CC DS API Files
    ScanDigSign()
    ScanDigSignHw()

#-----------------------------------------------------
#DS-ECDSA Handlers

def handleDsEcdsaEnabled(symbol, event):
    if (g.cryptoDsEcdsaEnabledSymbol.getValue() == True):
        print("DS: ECDSA  Enabled")
        if (g.cryptoHwDsEcdsaSupported):
            print("DS: ECDSA HW Enabled")
            g.cryptoHwDsEcdsaEnabledSymbol.setVisible(True)
        else:
            g.cryptoHwDsEcdsaEnabledSymbol.setValue(False)
            g.cryptoHwDsEcdsaEnabledSymbol.setVisible(False)
    else:
        g.cryptoHwDsEcdsaEnabledSymbol.setValue(False)
        g.cryptoHwDsEcdsaEnabledSymbol.setVisible(False)
    ScanDigSign()

    #Check for ECDSA HW Driver Update
    if (ScanDigSignHw() == True):
        numHwDrv = len(g.hwDriverFileDict["ECDSA"])
        print("ECDSA: %d Driver File Symbols Updated:"%(numHwDrv))
        if (len(g.hwDriverFileDict['ECDSA']) > 0):
            for fSym in g.hwDriverFileDict['ECDSA']:
                print(" File(%s) - %s"%(fSym.getEnabled(),fSym.getOutputName()))
        else: print("ECDSA:  %d Driver Files Updated"%(numHwDrv))

    for fSym in g.hwDriverFileDict["ECDSA"]:
        print("ECDSA:  Update [ECDSA]%s(%s)"%(
              fSym.getOutputName(),fSym.getEnabled()))
