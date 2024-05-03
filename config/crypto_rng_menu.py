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
#--Returns True if CONFIG_USE_MAC changes value
################################################################################
def ScanRng():
    if   (g.cryptoRngTrngEnabledSymbol.getValue()       == True): newValue = True
    elif (g.cryptoRngPrngEnabledSymbol.getValue()        == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_RNG.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_RNG.setValue(newValue)
        print("CRYPTO:  CONFIG_USE_RNG = %s"%(g.CONFIG_USE_RNG.getValue()))
        return True

#Check if the TRNG is enabled and the TRNG HW Driver Files are needed.
# TODO:  For now only Mistral 6146. Some mods required for other HW
#--Returns True if the TRNG HW Driver enable/disable has changed
def ScanTrngHw():
    retVal = False
    fKey = "TRNG"

    #TRNG Scan
    newValue = False
    if (g.cryptoRngTrngEnabledSymbol.getValue()   == True):
        if (g.cryptoHwRngTrngEnabledSymbol.getValue() == True):
            newValue = True

    print("TRNG: trng_hw - %s (newValue = %s)"%(
        g.CONFIG_USE_TRNG_HW.getValue(), newValue))

    if (g.CONFIG_USE_TRNG_HW.getValue() != newValue):
        g.CONFIG_USE_TRNG_HW.setValue(newValue)
        print("TRNG:  Enable HW (%s)"%(newValue))
        for fSym in g.hwDriverFileDict[fKey]:
            fSym.setEnabled(newValue)
        return True
    else:
        print("TRNG: HW Unchanged (%s)"%(newValue))
        return False


def SetupCryptoRngMenu(cryptoComponent):

    #RNG File Generation Enable
    g.CONFIG_USE_RNG= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_RNG", g.macMenu)
    g.CONFIG_USE_RNG.setVisible(False)
    g.CONFIG_USE_RNG.setLabel("Crypto")
    g.CONFIG_USE_RNG.setDefaultValue(False)

    #TRNG HW Driver Generation Enable
    g.CONFIG_USE_TRNG_HW = cryptoComponent.createBooleanSymbol(
            "config_use_trng_hw", g.hashMenu)
    g.CONFIG_USE_TRNG_HW.setVisible(False)
    g.CONFIG_USE_TRNG_HW.setLabel("Crypto TRNG HW")
    g.CONFIG_USE_TRNG_HW.setDefaultValue(False)

    #RNG - Crypto RNG Algorithms Main Menu
    g.rngMenu = cryptoComponent.createMenuSymbol(
            "crypto_rng", None)
    g.rngMenu.setLabel("RNG Algorithms")
    g.rngMenu.setDescription("Random Number Generation (RNG)")
    g.rngMenu.setVisible(True)
    g.rngMenu.setHelp('MC_CRYPTO_RNG_API_H')

    #RNG-TRNG
    g.cryptoRngTrngEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_rng_trng_en", g.rngMenu)
    g.cryptoRngTrngEnabledSymbol.setLabel("True RNG?")
    g.cryptoRngTrngEnabledSymbol.setDescription(
            "Enable support for the True RNG")
    g.cryptoRngTrngEnabledSymbol.setVisible(True)
    g.cryptoRngTrngEnabledSymbol.setReadOnly(False)
    g.cryptoRngTrngEnabledSymbol.setDefaultValue(False)

    #TRNG HW Symbol 
    g.cryptoHwRngTrngEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_rng_trng_hw", g.cryptoRngTrngEnabledSymbol)
    g.cryptoHwRngTrngEnabledSymbol.setLabel(
            "Use Hardware Acceleration?")
    g.cryptoHwRngTrngEnabledSymbol.setDescription(
            "Turn on the hardware acceleration" +
            "for the TRNG Algorithm")
    g.cryptoHwRngTrngEnabledSymbol.setVisible(False)
    g.cryptoHwRngTrngEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwTrngSupported == True):
        g.cryptoHwRngTrngEnabledSymbol.setDependencies(
            handleRngTrngEnabled, ["crypto_rng_trng_en", "crypto_rng_trng_hw"])
        if (g.cryptoRngTrngEnabledSymbol.getValue() == True):
            g.cryptoHwRngTrngEnabledSymbol.setVisible(True)
            g.cryptoHwRngTrngEnabledSymbol.setDefaultValue(True)
    g.cryptoHwRngTrngEnabledSymbol.setHelp('CRYPT_TRNG_SUM')

    #RNG-RNG
    g.cryptoRngPrngEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_rng_prng_en", g.rngMenu)
    g.cryptoRngPrngEnabledSymbol.setLabel("Pseudo RNG?")
    g.cryptoRngPrngEnabledSymbol.setDescription(
            "Enable support for the Pseudo RNG")
    g.cryptoRngPrngEnabledSymbol.setVisible(True)
    g.cryptoRngPrngEnabledSymbol.setReadOnly(False)
    g.cryptoRngPrngEnabledSymbol.setDefaultValue(True)

    #Check to see if any of the AEAD selections is True
    #--Used to include the CC AEAD API Files
    ScanRng() #set g.CONFIG_USE_TRNG and api file enables(TODO)

    #Check to init the drivers to the TRNG HW selections
    ScanTrngHw()  #set g.CONFIG_USE_TRNG_HW and driver file enable


#-----------------------------------------------------
#TRNG
def handleRngTrngEnabled(symbol, event):
    print("TRNG: Handle Event (HW supported %s"%(g.cryptoHwTrngSupported))
    if (g.cryptoRngTrngEnabledSymbol.getValue() == True):
        print("TRNG: Enabled")
        if (g.cryptoHwTrngSupported):
            print("TRNG: Set Visible")
            g.cryptoHwRngTrngEnabledSymbol.setVisible(True)
        else:
            g.cryptoHwRngTrngEnabledSymbol.setValue(False)
            g.cryptoHwRngTrngEnabledSymbol.setVisible(False)
    else:
        print("TRNG: Disabled")
        g.cryptoHwRngTrngEnabledSymbol.setValue(False)
        g.cryptoHwRngTrngEnabledSymbol.setVisible(False)
    ScanRng()

    #Check for Sha HW Driver Update
    if (ScanTrngHw() == True):
        numHwDrv = len(g.hwDriverFileDict["TRNG"])
        print("TRNG: %d Driver File Symbols Updated:"%(numHwDrv))
        if (len(g.hwDriverFileDict["TRNG"]) > 0):
            for fSym in g.hwDriverFileDict["TRNG"]:
                print(" File(%s) - %s"%(fSym.getEnabled(),fSym.getOutputName()))
        else: print("TRNG:  %d Driver Files Updated"%(numHwDrv))

    print("TRNG: Update %d files"%(len(g.hwDriverFileDict["TRNG"])))
    for fSym in g.hwDriverFileDict["TRNG"]:
        print("TRNG :  Update [TRNG]%s(%s)"%(
              fSym.getOutputName(),fSym.getEnabled()))




