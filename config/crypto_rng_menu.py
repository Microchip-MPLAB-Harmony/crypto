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
#  CONFIG_USE_RNG
#--Returns True if CONFIG_USE_RNG changes value
################################################################################
def ScanRng():
    if   (g.cryptoRngTrngEnabledSymbol.getValue() == True):
        newValue = True
    elif (g.cryptoRngPrngEnabledSymbol.getValue() == True):
        newValue = True
    else:
        newValue = False

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
    fKey = "TRNG"

    #TRNG Scan
    if (g.cryptoHwTrngSupported == True):
        hwValue = g.cryptoRngTrngEnabledSymbol.getValue()

        print("TRNG: Update(%s) %d files"%(
              hwValue, len(g.hwDriverFileDict["TRNG"])))

        #Enable Disable HW Driver File generation
        for fSym in g.hwDriverFileDict[fKey]:
            fSym.setEnabled(hwValue)
            print("  %s(%s)"%(fSym.getID(),hwValue))
        return True
    else:
        print("TRNG: Not Supported")
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

    #RNG-TRNG(HW)
    g.cryptoRngTrngEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_rng_trng_en", g.rngMenu)
    g.cryptoRngTrngEnabledSymbol.setLabel("True RNG (HW)?")
    g.cryptoRngTrngEnabledSymbol.setDescription(
            "Enable HW support for the True RNG")
    if (g.cryptoHwTrngSupported == True):
        if (len(g.hwDriverFileDict["TRNG"]) == 0):
            print("CRYPTO:  TRNG HW Driver Not Available")
            g.cryptoRngTrngEnabledSymbol.setVisible(True)
            g.cryptoRngTrngEnabledSymbol.setReadOnly(True)
            g.cryptoRngTrngEnabledSymbol.setDefaultValue(False)
            g.CONFIG_USE_TRNG_HW.setValue(False) 
        else:
            print("CRYPTO:  TRNG HW Driver Supported")
            g.cryptoRngTrngEnabledSymbol.setVisible(True)
            g.cryptoRngTrngEnabledSymbol.setReadOnly(False)
            g.cryptoRngTrngEnabledSymbol.setDefaultValue(False)
            g.cryptoRngTrngEnabledSymbol.setDependencies(
                handleRngTrngEnabled, ["crypto_rng_trng_en"])
            g.CONFIG_USE_TRNG_HW.setValue(True) 
    else:
        g.cryptoRngTrngEnabledSymbol.setVisible(False)
        g.cryptoRngTrngEnabledSymbol.setReadOnly(True)
        g.cryptoRngTrngEnabledSymbol.setDefaultValue(False)
        g.CONFIG_USE_TRNG_HW.setValue(False) 

    #RNG-RNG
    g.cryptoRngPrngEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_rng_prng_en", g.rngMenu)
    g.cryptoRngPrngEnabledSymbol.setLabel("Pseudo RNG?")
    g.cryptoRngPrngEnabledSymbol.setDescription(
            "Enable support for the Pseudo RNG")
    g.cryptoRngPrngEnabledSymbol.setVisible(True)
    g.cryptoRngPrngEnabledSymbol.setReadOnly(False)
    g.cryptoRngPrngEnabledSymbol.setDefaultValue(False)
    g.cryptoRngPrngEnabledSymbol.setDependencies(
            handleRngPrngEnabled, ["crypto_rng_prng_en"])

    #Check to see if any of the AEAD selections is True
    #--Used to include the CC AEAD API Files
    ScanRng() #set g.CONFIG_USE_TRNG and api file enables(TODO)

    #Check to init the drivers to the TRNG HW selections
    ScanTrngHw()  #Enable the HW driver files (when selected)


#-----------------------------------------------------
#TRNG
def handleRngTrngEnabled(symbol, event):
    print("TRNG: Symbol - " + event["namespace"] + " EID " + event["id"])
    print("TRNG: Handle Event SID %s (HW Support %s)"%(
        symbol.getID(), g.cryptoHwTrngSupported), )
    newValue = g.cryptoRngTrngEnabledSymbol.getValue()
    g.CONFIG_USE_TRNG_HW.setValue(newValue)
    ScanRng()
    ScanTrngHw()
    print("TRNG:  HW(%s)"%(g.CONFIG_USE_TRNG_HW.getValue()))

def handleRngPrngEnabled(symbol, event):
    print("PRNG: Symbol - " + event["namespace"] + " event - " + event["id"])
    print("PRNG: Handle Event SID %s (Value %s)"%(
        symbol.getID(), g.cryptoRngPrngEnabledSymbol.getValue))
    ScanRng()
