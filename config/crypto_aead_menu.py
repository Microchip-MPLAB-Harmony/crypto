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


def ScanAead():
    if   (g.cryptoAeadAesGcmEnabledSymbol.getValue()     == True): newValue = True
    elif (g.cryptoAeadAesCcmEnabledSymbol.getValue()     == True): newValue = True
    elif (g.cryptoAeadAesEaxEnabledSymbol.getValue()     == True): newValue = True
    elif (g.cryptoAeadAesSivCmacEnabledSymbol.getValue() == True): newValue = True
    elif (g.cryptoAeadAesSivGcmEnabledSymbol.getValue()  == True): newValue = True
    elif (g.cryptoAeadAesEnabledSymbol.getValue()        == True): newValue = True
    elif (g.cryptoAeadAesEnabledSymbol.getValue()        == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_AEAD.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_AEAD.setValue(newValue)
        print("CRYPO:  CONFIG_USE_AEAD = %s"%(g.CONFIG_USE_AEAD.getValue()))
        return True

def SetupCryptoAeadMenu(cryptoComponent):

    #AEAD - Crypto AEAD Algorithms Main Menu
    g.aeadMenu = cryptoComponent.createMenuSymbol(
            "crypto_aead", None)
    g.aeadMenu.setLabel("AEAD Algorithms")
    g.aeadMenu.setDescription("AEAD Algorithms: AES")
    g.aeadMenu.setVisible(True)
    g.aeadMenu.setHelp('MC_CRYPTO_AEAD_API_H')

    #AEAD File Generation Enable
    g.CONFIG_USE_AEAD= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_AEAD", g.aeadMenu)
    g.CONFIG_USE_AEAD.setVisible(False)
    g.CONFIG_USE_AEAD.setLabel("Crypto")
    g.CONFIG_USE_AEAD.setDefaultValue(False)

    #AEAD-AES Main Menu
    g.aeadAesMenu = cryptoComponent.createMenuSymbol(
            "crypto_aead_aes", g.aeadMenu)
    g.aeadAesMenu.setLabel("AEAD-AES(128/192/256)")
    g.aeadAesMenu.setDescription("AEAD-AES  Algorithms:")
    g.aeadAesMenu.setVisible(True)
    g.aeadAesMenu.setHelp('CRYPTO_AEAD_AES_SUM')

    #AEAD-AES MODES MENU
    g.aeadAesModesMenu = cryptoComponent.createMenuSymbol(
            "crypto_aead_aes_modes", g.aeadAesMenu)
    g.aeadAesModesMenu.setLabel("AEAD-AES Algorithm Modes")
    g.aeadAesModesMenu.setDescription("AEAD-AES Modes:")
    g.aeadAesModesMenu.setHelp('CRYPT_AEAD_AES_MODES_SUM')
    g.aeadAesModesMenu.setVisible(True)
    #                "crypto_aead_aes_128",
    #                "crypto_aead_aes_192",
    #                "crypto_aead_aes_256"])

    #AEAD-AES GCM Mode
    g.cryptoAeadAesGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_gcm_en", g.aeadAesModesMenu)
    g.cryptoAeadAesGcmEnabledSymbol.setLabel("AEAD-AES GCM Mode?")
    g.cryptoAeadAesGcmEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES GCM Mode Algorithm.")
    g.cryptoAeadAesGcmEnabledSymbol.setVisible(True)
    g.cryptoAeadAesGcmEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesGcmEnabledSymbol.setDefaultValue(False)

    #AEAD-AES GCM HW Mode 
    g.cryptoHwAeadAesGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_gcm_hw_en", g.cryptoAeadAesGcmEnabledSymbol)
    g.cryptoHwAeadAesGcmEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesGcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesGcmSupported):
        g.cryptoHwAeadAesEnabledSymbol.setDependencies(
                handleAeadAesGcmEnabled,
                ["crypto_aead_aes_hw_en"])

    #AEAD-AES CCM Mode
    g.cryptoAeadAesCcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_ccm_en", g.aeadAesModesMenu)
    g.cryptoAeadAesCcmEnabledSymbol.setLabel("AEAD-AES CCM Mode?")
    g.cryptoAeadAesCcmEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES CCM Mode Algorithm.")
    g.cryptoAeadAesCcmEnabledSymbol.setVisible(True)
    g.cryptoAeadAesCcmEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesCcmEnabledSymbol.setDefaultValue(False)

    #AEAD-AES CCM HW Mode 
    g.cryptoHwAeadAesCcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_ccm_hw_en", g.cryptoAeadAesCcmEnabledSymbol)
    g.cryptoHwAeadAesCcmEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesCcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesCcmSupported):
        g.cryptoHwAeadAesEnabledSymbol.setDependencies(
                handleAeadAesCcmEnabled,
                ["crypto_aead_aes_hw_en"])

    #AEAD-AES EAX
    g.cryptoAeadAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_eax_en", g.aeadAesModesMenu)
    g.cryptoAeadAesEaxEnabledSymbol.setLabel("AEAD-AES EAX Mode? ")
    g.cryptoAeadAesEaxEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES EAX Mode Algorithm.")
    g.cryptoAeadAesEaxEnabledSymbol.setVisible(True)
    g.cryptoAeadAesEaxEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesEaxEnabledSymbol.setDefaultValue(True)

    #AEAD-AES EAX HW Mode 
    g.cryptoHwAeadAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_eax_hw_en", g.cryptoAeadAesEaxEnabledSymbol)
    g.cryptoHwAeadAesEaxEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesEaxEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesEaxSupported):
        g.cryptoHwAeadAesEnabledSymbol.setDependencies(
                handleAeadAesEaxEnabled,
                ["crypto_aead_aes_hw_en"])

    #AEAD-AES SIV-CMAC Mode
    g.cryptoAeadAesSivCmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_cmac_en", g.aeadAesModesMenu)
    g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AEAD-AES SIV-CMAC Mode?")
    g.cryptoAeadAesSivCmacEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES SIV-CMAC Mode Algorithm.")
    g.cryptoAeadAesSivCmacEnabledSymbol.setVisible(True)
    g.cryptoAeadAesSivCmacEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesSivCmacEnabledSymbol.setDefaultValue(False)

    #AEAD-AES SIV-CMAC HW Mode 
    g.cryptoHwAeadAesSivCmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_cmac_hw_en", g.cryptoAeadAesSivCmacEnabledSymbol)
    g.cryptoHwAeadAesSivCmacEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesSivCmacEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesSivCmacSupported):
        g.cryptoHwAeadAesEnabledSymbol.setDependencies(
                handleAeadAesSivCmacEnabled,
                ["crypto_aead_aes_hw_en"])

    #AEAD-AES SIV-GCM Mode
    g.cryptoAeadAesSivGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_gcm_en", g.aeadAesModesMenu)
    g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AEAD-AES SIV-GCM Mode?")
    g.cryptoAeadAesSivGcmEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES SIV-GCM Mode Algorithm.")
    g.cryptoAeadAesSivGcmEnabledSymbol.setVisible(True)
    g.cryptoAeadAesSivGcmEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesSivGcmEnabledSymbol.setDefaultValue(False)

    #AEAD-AES SIV-GCM HW Mode 
    g.cryptoHwAeadAesSivGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_gcm_hw_en", g.cryptoAeadAesSivGcmEnabledSymbol)
    g.cryptoHwAeadAesSivGcmEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesSivGcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesSivGcmSupported):
        g.cryptoHwAeadAesEnabledSymbol.setDependencies(
                handleAeadAesSivGcmEnabled,
                ["crypto_aead_aes_hw_en"])

    #Check to see if any of the AEAD selections is True
    #--Used to include the CC AEAD API Files
    ScanAead()

#-----------------------------------------------------
#AEAD-AES Handlers
def handleAesHwEnabled(symbol, event):
    print("CRYPTO: handle AES HW (does nothing)")
    if (ScanAead() == True):
        data = symbol.getComponent()
    return

def handleAeadAesGcmEnabled(symbol, event):
    if (g.cryptoHwAeadAesGcmSupported and (
        g.cryptoHwAeadAesEnabledSymbol.getValue() == True)):
        g.cryptoAeadAesGcmEnabledSymbol.setLabel("AEAD-AES GCM (HW)?")
    else:
        g.cryptoAesGcmEnabledSymbol.setLabel("AEAD-AES GCM?")
    if (ScanAead() == True):
        data = symbol.getComponent()
    return

def handleAeadAesCcmEnabled(symbol, event):
    if (g.cryptoHwAeadAesCcmSupported and (
        g.cryptoHwAeadAesEnabledSymbol.getValue() == True)):
        g.cryptoAeadAesCcmEnabledSymbol.setLabel("AEAD-AES CCM (HW)?")
    else:
        g.cryptoAeadAesCcmEnabledSymbol.setLabel("AEAD-AES CCM?")
    if (ScanAead() == True):
        data = symbol.getComponent()
    return

def handleAeadAesEaxEnabled(symbol, event):
    if (g.cryptoHwAesEaxSupported and (
        g.cryptoHwAeadAesEnabledSymbol.getValue() == True)):
        g.cryptoAeadAesEaxEnabledSymbol.setLabel("AEAD-AES Eax (HW)?")
    else:
        g.cryptoAeadAesEaxEnabledSymbol.setLabel("AEAD-AES Eax?")
    if (ScanAead() == True):
        data = symbol.getComponent()
    return

def handleAeadAesSivCmacEnabled(symbol, event):
    if (g.cryptoHwAeadAesSivCmacSupported and (
        g.cryptoHwAeadAesEnabledSymbol.getValue() == True)):
        g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AEAD-AES SIV-CMAC (HW)?")
    else:
        g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AEAD-AES SIV-CMAC?")
    if (ScanAead() == True):
        data = symbol.getComponent()
    return

def handleAeadAesSivGcmEnabled(symbol, event):
    if (g.cryptoHwAeadAesSivGcmSupported and (
        g.cryptoHwAeadAesEnabledSymbol.getValue() == True)):
        g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AEAD-AES SIV-GCM (HW)?")
    else:
        g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AEAD-AES SIV-GCM?")
    if (ScanAead() == True):
        data = symbol.getComponent()
    return
