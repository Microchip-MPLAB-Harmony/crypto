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
        return False
    else:
        g.CONFIG_USE_KAS.setValue(newValue)
        print("CRYPO:  CONFIG_USE_KAS = %s"%(g.CONFIG_USE_KAS.getValue()))
        return True



################################################################################
#Check if the ECDH is enabled and the ECDH HW Driver Files are needed.
# TODO:  For now only Mistral 6156. Some mods required for other HW
#--Returns True if the ECDH HW Driver enable/disable has changed
################################################################################
def ScanKasHw():
    retVal = False
    fKey = "ECDH"

    #KAS Scan
    newValue = False
    if (g.cryptoKasEcdhEnabledSymbol.getValue()   == True):
        if (g.cryptoHwKasEcdhEnabledSymbol.getValue() == True):
            newValue = True

    g.CONFIG_USE_ECDH_HW.setValue(newValue)
    for fSym in g.hwDriverFileDict[fKey]:
        fSym.setEnabled(newValue)
    return True


def SetupCryptoKasMenu(cryptoComponent):

    #KAS File Generation Enable
    g.CONFIG_USE_KAS= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_KAS", g.macMenu)
    g.CONFIG_USE_KAS.setVisible(False)
    g.CONFIG_USE_KAS.setLabel("KAS")
    g.CONFIG_USE_KAS.setDefaultValue(False)

    #KAS HW File Generation Enable
    g.CONFIG_USE_KAS_HW= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_KAS_HW", g.macMenu)
    g.CONFIG_USE_KAS_HW.setVisible(False)
    g.CONFIG_USE_KAS_HW.setLabel("KAS HW")
    g.CONFIG_USE_KAS_HW.setDefaultValue(False)

    #KAS - Crypto KAS Algorithms Main Menu
    g.kasMenu = cryptoComponent.createMenuSymbol(
            "crypto_kas", None)
    g.kasMenu.setLabel("KAS Algorithms")
    g.kasMenu.setDescription("KAS Algorithms")
    g.kasMenu.setVisible(True)
    g.kasMenu.setHelp('MC_CRYPTO_KAS_API_H')


    #KAS-ECDH
    g.cryptoKasEcdhEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_kas_ecdh_en", g.kasMenu)
    g.cryptoKasEcdhEnabledSymbol.setLabel("ECDH?")
    g.cryptoKasEcdhEnabledSymbol.setDescription(
            "Enable support for the ECDH protocol")
    g.cryptoKasEcdhEnabledSymbol.setVisible(True)
    g.cryptoKasEcdhEnabledSymbol.setReadOnly(False)
    g.cryptoKasEcdhEnabledSymbol.setDefaultValue(True)

    #TODO:  HW ECDH Selection

    #Check to see if any of the KAS  selections is True
    #--Used to include the CC KAS  API Files
    ScanKas()

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
    ScanKas()
    ScanKasHw()

#-----------------------------------------------------
#KAS-ECDH Handlers

def handleKasEcdhEnabled(symbol, event):
    if (g.cryptoKasEcdhEnabledSymbol.getValue() == True):
        print("KAS: ECDH  Enabled")
        if (g.cryptoHwKasEcdhSupported):
            print("KAS: ECDH HW Enabled")
            g.cryptoHwKasEcdhEnabledSymbol.setVisible(True)
        else:
            g.cryptoHwKasEcdhEnabledSymbol.setValue(False)
            g.cryptoHwKasEcdhEnabledSymbol.setVisible(False)
    else:
        g.cryptoHwKasEcdhEnabledSymbol.setValue(False)
        g.cryptoHwKasEcdhEnabledSymbol.setVisible(False)
    ScanKas()

    #Check for ECDH HW Driver Update
    if (ScanKasHw() == True):
        numHwDrv = len(g.hwDriverFileDict["ECDH"])
        print("ECDH: %d Driver File Symbols Updated:"%(numHwDrv))
        if (len(g.hwDriverFileDict['ECDH']) > 0):
            for fSym in g.hwDriverFileDict['ECDH']:
                print(" File(%s) - %s"%(fSym.getEnabled(),fSym.getOutputName()))
        else: print("ECDH:  %d Driver Files Updated"%(numHwDrv))

    for fSym in g.hwDriverFileDict["ECDH"]:
        print("ECDH:  Update [ECDH]%s(%s)"%(
              fSym.getOutputName(),fSym.getEnabled()))
