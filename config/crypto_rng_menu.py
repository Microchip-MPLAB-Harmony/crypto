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
        print("CRYPO:  CONFIG_USE_RNG = %s"%(g.CONFIG_USE_RNG.getValue()))
        return True


def SetupCryptoRngMenu(cryptoComponent):

    #RNG File Generation Enable
    g.CONFIG_USE_RNG= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_RNG", g.macMenu)
    g.CONFIG_USE_RNG.setVisible(False)
    g.CONFIG_USE_RNG.setLabel("Crypto")
    g.CONFIG_USE_RNG.setDefaultValue(False)

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
    g.cryptoRngTrngEnabledSymbol.setVisible(False)
    g.cryptoRngTrngEnabledSymbol.setReadOnly(False)
    g.cryptoRngTrngEnabledSymbol.setDefaultValue(False)

    #RNG-RNG
    g.cryptoRngPrngEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_rng_prng_en", g.rngMenu)
    g.cryptoRngPrngEnabledSymbol.setLabel("Pseudo RNG?")
    g.cryptoRngPrngEnabledSymbol.setDescription(
            "Enable support for the Pseudo RNG")
    g.cryptoRngPrngEnabledSymbol.setVisible(True)
    g.cryptoRngPrngEnabledSymbol.setReadOnly(False)
    g.cryptoRngPrngEnabledSymbol.setDefaultValue(True)


