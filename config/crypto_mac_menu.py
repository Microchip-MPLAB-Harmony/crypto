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

#import crypto_globals   #Initial globals
import crypto_defs as g #Modified globals
#import superglobals

################################################################################
#Scan to see if any of the Hash Selections is True and set the symbol
#CONFIG_USE_CRYPTO
#--Returns True if CONFIG_USE_MAC changes value
################################################################################
def ScanMac():
    if   (g.cryptoMacAesCmacEnabledSymbol.getValue()       == True): newValue = True
    elif (g.cryptoMacAesCbcMacEnabledSymbol.getValue()      == True): newValue = True
    elif (g.cryptoMacAesGmacEnabledSymbol.getValue()      == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_MAC.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_MAC.setValue(newValue)
        print("CRYPO:  CONFIG_USE_MAC = %s"%(g.CONFIG_USE_MAC.getValue()))
        return True


def SetupCryptoMacMenu(cryptoComponent):

    #MAC - Crypto MAC Algorithms Main Menu
    g.macMenu = cryptoComponent.createMenuSymbol(
            "crypto_mac", None)
    g.macMenu.setLabel("MAC Algorithms")
    g.macMenu.setDescription("MAC Algorithms")
    g.macMenu.setVisible(True)
    g.macMenu.setHelp('MC_CRYPTO_MAC_API_H')

    #MAC File Generation Enable
    g.CONFIG_USE_MAC= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_MAC", g.macMenu)
    g.CONFIG_USE_MAC.setVisible(False)
    g.CONFIG_USE_MAC.setLabel("Crypto")
    g.CONFIG_USE_MAC.setDefaultValue(False)


    #MAC-AES Main Menu
    g.macAesMenu = cryptoComponent.createMenuSymbol(
            "crypto_mac_aes", g.macMenu)
    g.macAesMenu.setLabel("AES(MAC)")
    g.macAesMenu.setDescription("MAC-AES Algorithms:")
    g.macAesMenu.setVisible(True)
    g.macAesMenu.setHelp('CRYPT_MAC_AES_SUM')

    #MAC-AES HW Enable (For all MAC AES Algorithms that have HW Support)
    g.cryptoHwMacAesEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_hw_en", g.macAesMenu)
    g.cryptoHwMacAesEnabledSymbol.setLabel("Enable MAC-AES Hardware Acceleration?")
    g.cryptoHwMacAesEnabledSymbol.setDescription(
        "Turn on the hardware acceleration" +
        "for the MAC AES Algorithms")
    if (g.cryptoHwMacAesSupported):
        g.cryptoHwMacAesEnabledSymbol.setDependencies(
                handleMacAesHwEnabled,
                ["crypto_mac_aes_hw_en"])
        g.cryptoHwMacAesEnabledSymbol.setVisible(True)
        g.cryptoHwMacAesEnabledSymbol.setDefaultValue(False)
    else:
        g.cryptoHwMacAesEnabledSymbol.setVisible(False)
        g.cryptoHwMacAesEnabledSymbol.setDefaultValue(False)
    g.cryptoHwMacAesEnabledSymbol.setHelp('CRYPT_MAC_AES_SUM')
    #TODO:  Add the Hardware *****
    g.cryptoHwMacAesEnabledSymbol.setReadOnly(True)

    #Global to indicate when AES Modes are visible
    g.cryptoMacAesModesSupported = False

    #MAC-AES MODES MENU
    g.macAesModesMenu = cryptoComponent.createMenuSymbol(
            "crypto_mac_aes_modes", g.macAesMenu)
    g.macAesModesMenu.setLabel("MAC-AES Algorithm Modes")
    g.macAesModesMenu.setDescription("MAC-AES Modes:")
    g.macAesModesMenu.setHelp('CRYPT_MAC_AES_MODES_SUM')
    g.macAesModesMenu.setVisible(True)

    #MAC-AES CMAC Mode
    g.cryptoMacAesCmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_cmac_en", g.macAesModesMenu)
    g.cryptoMacAesCmacEnabledSymbol.setLabel("MAC-AES CMAC Mode?")
    g.cryptoMacAesCmacEnabledSymbol.setDescription(
            "Enable support for the MAC-AES CMAC Mode Algorithm.")
    g.cryptoMacAesCmacEnabledSymbol.setVisible(True)
    g.cryptoMacAesCmacEnabledSymbol.setReadOnly(False)
    g.cryptoMacAesCmacEnabledSymbol.setDefaultValue(False)

    #MAC-AES CMAC HW Mode 
    g.cryptoHwMacAesCmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_cmac_hw_en", g.cryptoMacAesCmacEnabledSymbol)
    g.cryptoHwMacAesCmacEnabledSymbol.setVisible(False)
    g.cryptoHwMacAesCmacEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwMacAesCmacSupported):
        g.cryptoHwMacAesEnabledSymbol.setDependencies(
                handleMacAesCmacEnabled,
                ["crypto_mac_aes_hw_en"])

    #MAC-AES CBC-MAC Mode
    g.cryptoMacAesCbcMacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_cbc_mac_en", g.macAesModesMenu)
    g.cryptoMacAesCbcMacEnabledSymbol.setLabel("MAC-AES CBC-MAC Mode?")
    g.cryptoMacAesCbcMacEnabledSymbol.setDescription(
            "Enable support for the MAC-AES CBC-MAC Mode Algorithm.")
    g.cryptoMacAesCbcMacEnabledSymbol.setVisible(True)
    g.cryptoMacAesCbcMacEnabledSymbol.setReadOnly(False)
    g.cryptoMacAesCbcMacEnabledSymbol.setDefaultValue(False)

    #MAC-AES CBC-MAC HW Mode 
    g.cryptoHwMacAesCbcMacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_cbc_mac_hw_en", g.cryptoMacAesCbcMacEnabledSymbol)
    g.cryptoHwMacAesCbcMacEnabledSymbol.setVisible(False)
    g.cryptoHwMacAesCbcMacEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwMacAesCbcMacSupported):
        g.cryptoHwMacAesEnabledSymbol.setDependencies(
                handleMacAesCbcMacEnabled,
                ["crypto_mac_aes_hw_en"])

    #MAC-AES GMAC 
    g.cryptoMacAesGmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_gmac_en", g.macAesModesMenu)
    g.cryptoMacAesGmacEnabledSymbol.setLabel("MAC-AES GMAC Mode? ")
    g.cryptoMacAesGmacEnabledSymbol.setDescription(
            "Enable support for the MAC-AES GMAC Mode Algorithm.")
    g.cryptoMacAesGmacEnabledSymbol.setVisible(True)
    g.cryptoMacAesGmacEnabledSymbol.setReadOnly(False)
    g.cryptoMacAesGmacEnabledSymbol.setDefaultValue(False)

    #MAC-AES  GMAC HW Mode 
    g.cryptoHwMacAesGmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_mac_aes_gmac_hw_en", g.cryptoMacAesGmacEnabledSymbol)
    g.cryptoHwMacAesGmacEnabledSymbol.setVisible(False)
    g.cryptoHwMacAesGmacEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwMacAesGmacSupported):
        g.cryptoHwMacAesEnabledSymbol.setDependencies(
                handleMacAesGmacEnabled,
                ["crypto_mac_aes_hw_en"])

    #Check to see if any of the MAC selections is True
    #--Used to include the CC MAC API Files
    ScanMac()

#-----------------------------------------------------
#MAC-AES Handlers
def handleAesHwEnabled(symbol, event):
    print("CRYPTO: handle AES HW (does nothing)")
    return

def handleMacAesCmacEnabled(symbol, event):
    if (g.cryptoHwMacAesCmacSupported and (
        g.cryptoHwMacAesEnabledSymbol.getValue() == True)):
        g.cryptoMacAesCmacEnabledSymbol.setLabel("MAC-AES CMAC (HW)?")
    else:
        g.cryptoAesCmacEnabledSymbol.setLabel("MAC-AES CMAC?")
    if (ScanMac() == True):
        data = symbol.getComponent()
    return

def handleMacAesCbcMacEnabled(symbol, event):
    if (g.cryptoHwMacAesCbcMacSupported and (
        g.cryptoHwMacAesEnabledSymbol.getValue() == True)):
        g.cryptoMacAesCbcMacEnabledSymbol.setLabel("MAC-AES CBC-MAC (HW)?")
    else:
        g.cryptoMacAesCbcMacEnabledSymbol.setLabel("MAC-AES CBC-MAC?")
    if (ScanMac() == True):
        data = symbol.getComponent()
    return

def handleMacAesGmacEnabled(symbol, event):
    if (g.cryptoHwMacAesGmacSupported and (
        g.cryptoHwMacAesEnabledSymbol.getValue() == True)):
        g.cryptoAesGmacEnabledSymbol.setLabel("MAC-AES GMAC (HW)?")
    else:
        g.cryptoAesGmacEnabledSymbol.setLabel("MAC-AES GMAC ")
    if (ScanMac() == True):
        data = symbol.getComponent()
    return
