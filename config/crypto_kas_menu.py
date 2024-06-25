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
def ScanKas():
    if   (g.cryptoKasEcdhEnabledSymbol.getValue() == True):
        newValue = True
    else:
        newValue = False

    if (g.CONFIG_USE_KAS.getValue() == newValue):
        g.CONFIG_USE_ECDH.setValue(newValue)
        return False
    else:
        g.CONFIG_USE_KAS.setValue(newValue)
        g.CONFIG_USE_ECDH.setValue(newValue)
        print("CRYPO:  CONFIG_USE_KAS = %s"%(g.CONFIG_USE_KAS.getValue()))
        return True



################################################################################
################################################################################
def UpdateKasHwDriverFiles():

    ScanKas

    hwVal = g.cryptoHwKasEcdhEnabledSymbol.getValue()
    g.CONFIG_USE_ECDH_HW.setValue(hwVal)

    print("KAS:  Update ECDH HW Driver (%s-%s)"%(
          hwVal, g.CONFIG_USE_ECDH_HW.getValue()))

    hwVal = g.CONFIG_USE_ECDH_HW.getValue()

    #Enable/Disable HW Driver Files

    for fSym in g.hwDriverFileDict["ECDH"]:
        fSym.setEnabled(hwVal)
        print("  %s(%s)"%(fSym.getID(), fSym.getEnabled()))


    #Additional Driver Files used by other functions
    sameDriver = False
    if (g.hwFunctionDriverDict["ECDH"] ==
        g.hwFunctionDriverDict["ECDSA"]):
        print("KAS:  Both KAS-ECDH and DS-ECDSA use %s driver"%
              g.hwFunctionDriverDict["ECDSA"])
        sameDriver = True

    if (sameDriver == True):
        hwVal = (g.cryptoHwDsEcdsaEnabledSymbol.getValue() or
                 g.cryptoHwKasEcdhEnabledSymbol.getValue())
    else:
        hwVal = g.cryptoHwDsEcdsaEnabledSymbol.getValue()

    print("KAS: ECDH uses %s Driver(hw = %s)"%(
        g.hwFunctionDriverDict["ECDH"], hwVal))
    if (g.hwFunctionDriverDict["ECDH"][0] == "CPKCC"):

        print("ECDH: CPKCC Driver Enabled(%s)"%(hwVal))
        for fSym in g.cpkclDriverFileSyms:
            fSym.setEnabled(hwVal)

        #Driver Dependency - ECC Curves
        print("ECDH: ECC Driver Enabled(%s)"%(hwVal))
        for fSym in g.hwDriverFileDict["ECC"]:
            fSym.setEnabled(hwVal)

    return True



################################################################################
# Setup the KAS Menu Items and File Generation
# --Files are listed in g.hwFileDict["ECDH"] list dictionary
################################################################################
def SetupCryptoKasMenu(cryptoComponent):

    #KAS File Generation Enable
    g.CONFIG_USE_KAS= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_KAS", None)
    g.CONFIG_USE_KAS.setVisible(False)
    g.CONFIG_USE_KAS.setLabel("Crypto")
    g.CONFIG_USE_KAS.setDefaultValue(False)

    #ECDH File Generation Enable
    g.CONFIG_USE_ECDH= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_ECDH", None)
    g.CONFIG_USE_ECDH.setVisible(False)
    g.CONFIG_USE_ECDH.setLabel("Crypto ECDH")
    g.CONFIG_USE_ECDH.setDefaultValue(False)

    #ECDH File Generation Enable
    g.CONFIG_USE_ECDH_HW= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_ECDH_HW", None)
    g.CONFIG_USE_ECDH_HW.setVisible(False)
    g.CONFIG_USE_ECDH_HW.setLabel("Crypto ECDH HW")
    g.CONFIG_USE_ECDH_HW.setDefaultValue(False)

    #KAS - Crypto KAS Algorithms Main Menu
    g.kasMenu = cryptoComponent.createMenuSymbol(
            "crypto_kas_menu", None)
    g.kasMenu.setLabel("Key Agreement System (KAS) Menu")
    g.kasMenu.setDescription("Key Agreement Algorithms")
    g.kasMenu.setVisible(True)
    g.kasMenu.setHelp('MC_CRYPTO_KAS_API_H')

    #KAS - KAS Mode
    g.cryptoKasEcdhEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_kas_ecdh_en", g.kasMenu)
    g.cryptoKasEcdhEnabledSymbol.setLabel("ECDH?")
    g.cryptoKasEcdhEnabledSymbol.setDescription(
            "Enable support for the Digital Signing ECDH protocol")
    g.cryptoKasEcdhEnabledSymbol.setVisible(True)
    g.cryptoKasEcdhEnabledSymbol.setReadOnly(False)
    g.cryptoKasEcdhEnabledSymbol.setDefaultValue(True)
    g.cryptoKasEcdhEnabledSymbol.setHelp('CRYPT_ECDH_SUM')

    #KAS ECDH HW Symbol
    g.cryptoHwKasEcdhEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_kas_ecdh_hw_en", g.cryptoKasEcdhEnabledSymbol)
    g.cryptoHwKasEcdhEnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwKasEcdhEnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the ECDH Key Agreement Algorithm")
    g.cryptoHwKasEcdhEnabledSymbol.setVisible(False)
    g.cryptoHwKasEcdhEnabledSymbol.setDefaultValue(False)
    if ((g.cryptoHwKasEcdhSupported == True)):
        g.cryptoKasEcdhEnabledSymbol.setDependencies(
                handleKasEcdhEnabled, ["crypto_kas_ecdh_en",
                                       "crypto_kas_ecdh_hw_en"])
        if (g.cryptoKasEcdhEnabledSymbol.getValue() == True):
            g.cryptoHwKasEcdhEnabledSymbol.setVisible(True)
            g.cryptoHwKasEcdhEnabledSymbol.setDefaultValue(True)

    #Check to see if any of the Kas selections is True
    #--Used to include the CC KAS API Files
    UpdateKasHwDriverFiles

#-----------------------------------------------------
#KAS-ECDH Handlers

def handleKasEcdhEnabled(symbol, event):
    if (g.cryptoKasEcdhEnabledSymbol.getValue() == True):
        print("KAS: ECDH  Enabled")
        if (g.cryptoHwKasEcdhSupported):
            g.cryptoHwKasEcdhEnabledSymbol.setVisible(True)
        else:
            g.cryptoHwKasEcdhEnabledSymbol.setValue(False)
            g.cryptoHwKasEcdhEnabledSymbol.setVisible(False)
    else:
        g.cryptoHwKasEcdhEnabledSymbol.setValue(False)
        g.cryptoHwKasEcdhEnabledSymbol.setVisible(False)

    #Check for ECDH HW Driver Update
    if (UpdateKasHwDriverFiles() == True):
        numHwDrv = len(g.hwDriverFileDict["ECDH"])
        print("ECDH: %d Driver File Symbols Updated:"%(numHwDrv))
        for fSym in g.hwDriverFileDict["ECDH"]:
            print("ECDH:  Update [ECDH]%s(%s)"%(
                  fSym.getOutputName(),fSym.getEnabled()))
        for fSym in g.hwDriverFileDict["ECC"]:
            print("ECC:  Update [ECC]%s(%s)"%(
                  fSym.getOutputName(),fSym.getEnabled()))
