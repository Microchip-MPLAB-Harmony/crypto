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

print("CRYPTO: HASH Menu Package")
import crypto_globals   #Initial globals
import crypto_defs as g #Modified globals
#import superglobals

################################################################################
#Scan to see if any of the Hash Selections is True and set the symbol
#CONFIG_USE_SYM
#--Returns True if CONFIG_USE_SYM changes value
################################################################################
def ScanSym():
    if   (g.cryptoAesEcbEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAesCbcEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAesOfbEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAesCfb1EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoAesCfb8EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoAesCfb64EnabledSymbol.getValue()  == True): newValue = True
    elif (g.cryptoAesCfb128EnabledSymbol.getValue() == True): newValue = True
    elif (g.cryptoAesCtrEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAesXtsEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAesEaxEnabledSymbol.getValue()    == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_SYM.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_SYM.setValue(newValue)
        print("CRYPO:  CONFIG_USE_SYM = %s"%(g.CONFIG_USE_SYM.getValue()))
        return True


def SetupCryptoSymmetricMenu(cryptoComponent):
    #SYM - Symmetric Crypto Algorithms Main Menu
    g.symMenu = cryptoComponent.createMenuSymbol(
            "crypto_sym", None)
    g.symMenu.setLabel("Symmetric Algorithms")
    g.symMenu.setDescription("Symmetric Algorithms: AES")
    g.symMenu.setVisible(True)
    g.symMenu.setHelp('MC_CRYPTO_API_H')

    #SYM File Generation Enable
    g.CONFIG_USE_SYM= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_SYM", g.symMenu)
    g.CONFIG_USE_SYM.setVisible(False)
    g.CONFIG_USE_SYM.setLabel("Crypto")
    g.CONFIG_USE_SYM.setDefaultValue(False)

    #SYM AES Main Menu
    g.aesMenu = cryptoComponent.createMenuSymbol(
            "crypto_sym_aes_en", g.symMenu)
    g.aesMenu.setLabel("AES Algorithms")
    g.aesMenu.setDescription("AES Algorithms:")
    g.aesMenu.setVisible(True)
    g.aesMenu.setHelp('CRYPT_AES_SUM')

    #SYM AES HW Enable (For all AES Algorithms that have HW Support)
    g.cryptoHwAesEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_hw_en", g.aesMenu)
    g.cryptoHwAesEnabledSymbol.setLabel("Use AES Hardware Acceleration?")
    g.cryptoHwAesEnabledSymbol.setDescription(
        "Turn on the hardware acceleration" +
        "for the AES Algorithms")
    if (g.cryptoHwAesSupported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesHwEnabled,
                ["crypto_sym_aes_hw_en"])
        g.cryptoHwAesEnabledSymbol.setVisible(True)
        g.cryptoHwAesEnabledSymbol.setDefaultValue(False)
    else:
        g.cryptoHwAesEnabledSymbol.setVisible(False)
        g.cryptoHwAesEnabledSymbol.setDefaultValue(False)
    g.cryptoHwAesEnabledSymbol.setHelp('CRYPT_AES_SUM')

    #Global to indicate when AES Modes are visible
    g.cryptoAesModesSupported = True 

    #AES MODES MENU
    g.aesModesMenu = cryptoComponent.createMenuSymbol("crypto_sym_aes_modes", g.aesMenu)
    g.aesModesMenu.setLabel("AES Algorithm Modes")
    g.aesModesMenu.setDescription("AES Modes:")
    g.aesModesMenu.setHelp('CRYPT_AES_MODES_SUM')
    #if (g.cryptoAesModesSupported):
    g.aesModesMenu.setVisible(True)
    #else:
    #    g.aesModesMenu.setVisible(False)
    #g.aesModesMenu.setDependencies(
    #            handleAesModesMenu, [
    #                "crypto_sym_aes_128",
    #                "crypto_sym_aes_192",
    #                "crypto_sym_aes_256"])


    #AES-ECB Mode
    g.cryptoAesEcbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ecb_en", g.aesModesMenu)
    g.cryptoAesEcbEnabledSymbol.setLabel("AES-ECB Mode?")
    g.cryptoAesEcbEnabledSymbol.setDescription(
            "Enable support for the AES-ECB Mode Algorithm.")
    g.cryptoAesEcbEnabledSymbol.setVisible(True)
    #if (g.cryptoAesModesSupported):
    g.cryptoAesEcbEnabledSymbol.setDefaultValue(True)
    #else:
    #    g.cryptoAesEcbEnabledSymbol.setDefaultValue(False)

    #AES-Ecb Mode HW
    g.cryptoHwAesEcbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ecb_hw_en", g.cryptoAesEcbEnabledSymbol)
    g.cryptoHwAesEcbEnabledSymbol.setVisible(False)
    g.cryptoHwAesEcbEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesEcbSupported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesEcbEnabled,
                ["crypto_sym_aes_hw_en"])


    #AES-CBC
    g.cryptoAesCbcEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cbc_en", g.aesModesMenu)
    g.cryptoAesCbcEnabledSymbol.setLabel("AES-CBC Mode?")
    g.cryptoAesCbcEnabledSymbol.setDescription(
            "Enable support for the AES-CBC Mode Algorithm.")
    g.cryptoAesCbcEnabledSymbol.setVisible(True)
    g.cryptoAesCbcEnabledSymbol.setDefaultValue(False)

    #AES-CBC HW
    g.cryptoHwAesCbcEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aes_sym_cbc_hw", g.cryptoAesCbcEnabledSymbol)
    g.cryptoHwAesCbcEnabledSymbol.setVisible(False)
    g.cryptoHwAesCbcEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesCbcSupported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesCbcEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-OFB
    g.cryptoAesOfbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ofb_en", g.aesModesMenu)
    g.cryptoAesOfbEnabledSymbol.setLabel("AES-OFB Mode?")
    g.cryptoAesOfbEnabledSymbol.setDescription(
            "Enable support for the AES-OFB Mode Algorithm.")
    g.cryptoAesOfbEnabledSymbol.setVisible(True)
    g.cryptoAesOfbEnabledSymbol.setDefaultValue(False)

    #AES-OFB HW
    g.cryptoHwAesOfbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ofb_hw_en", g.cryptoAesOfbEnabledSymbol)
    g.cryptoHwAesOfbEnabledSymbol.setVisible(False)
    g.cryptoHwAesOfbEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesOfbSupported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesOfbEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB Menu
    g.aesCfbMenu = cryptoComponent.createMenuSymbol(
            "crypto_sym_aes_cfb_en", g.aesModesMenu)
    g.aesCfbMenu.setLabel("AES CFB Modes")
    g.aesCfbMenu.setDescription("AES CFB Mode")
    g.aesCfbMenu.setVisible(True)
    g.aesCfbMenu.setHelp('CRYPT_AES_SUM')

    #AES-CFB1 Mode
    g.cryptoAesCfb1EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb1_en", g.aesCfbMenu)
    g.cryptoAesCfb1EnabledSymbol.setLabel("AES-CFB(1) Mode?")
    g.cryptoAesCfb1EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(1) Mode Algorithm.")
    g.cryptoAesCfb1EnabledSymbol.setVisible(True)
    g.cryptoAesCfb1EnabledSymbol.setDefaultValue(False)

    #AES-CFB1 HW
    g.cryptoHwAesCfb1EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb1_hw_en", g.cryptoAesCfb1EnabledSymbol)
    g.cryptoHwAesCfb1EnabledSymbol.setVisible(False)
    g.cryptoHwAesCfb1EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesCfb1Supported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesCfb1Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB8 Mode
    g.cryptoAesCfb8EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb8_en", g.aesCfbMenu)
    g.cryptoAesCfb8EnabledSymbol.setLabel("AES-CFB(8) Mode?")
    g.cryptoAesCfb8EnabledSymbol.setDescription(
            "Enable support for the AES-CFB8 Mode Algorithm.")
    g.cryptoAesCfb8EnabledSymbol.setVisible(True)
    g.cryptoAesCfb8EnabledSymbol.setDefaultValue(False)

    #AES-CFB8 HW
    g.cryptoHwAesCfb8EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb8_hw_en", g.cryptoAesCfb8EnabledSymbol)
    g.cryptoHwAesCfb8EnabledSymbol.setVisible(False)
    g.cryptoHwAesCfb8EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesCfb8Supported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesCfb8Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB64 Modes
    g.cryptoAesCfb64EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb64_en", g.aesCfbMenu)
    g.cryptoAesCfb64EnabledSymbol.setLabel("AES-CFB(64) Mode?")
    g.cryptoAesCfb64EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(64) Mode Algorithm.")
    g.cryptoAesCfb64EnabledSymbol.setVisible(True)
    g.cryptoAesCfb64EnabledSymbol.setDefaultValue(False)

    #AES-CFB64 HW
    g.cryptoHwAesCfb64EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb64_hw_en", g.cryptoAesCfb64EnabledSymbol)
    g.cryptoHwAesCfb64EnabledSymbol.setVisible(False)
    g.cryptoHwAesCfb64EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesCfb64Supported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesCfb64Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB128 Modes
    g.cryptoAesCfb128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb128_en", g.aesCfbMenu)
    g.cryptoAesCfb128EnabledSymbol.setLabel("AES-CFB(128) Mode?")
    g.cryptoAesCfb128EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(128) Mode Algorithm.")
    g.cryptoAesCfb128EnabledSymbol.setVisible(True)
    g.cryptoAesCfb128EnabledSymbol.setDefaultValue(False)

    #AES-CFB128 HW
    g.cryptoHwAesCfb128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb128_hw_en", g.cryptoAesCfb128EnabledSymbol)
    g.cryptoHwAesCfb128EnabledSymbol.setVisible(False)
    g.cryptoHwAesCfb128EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesCfb128Supported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesCfb128Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CTR
    g.cryptoAesCtrEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ctr_en", g.aesModesMenu)
    g.cryptoAesCtrEnabledSymbol.setLabel("AES-CTR Mode?")
    g.cryptoAesCtrEnabledSymbol.setDescription(
            "Enable support for the AES-CTR Mode Algorithm.")
    g.cryptoAesCtrEnabledSymbol.setVisible(True)
    g.cryptoAesCtrEnabledSymbol.setDefaultValue(False)

    #AES-CTR HW
    g.cryptoHwAesCtrEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ctr_hw_en", g.cryptoAesCtrEnabledSymbol)
    g.cryptoHwAesCtrEnabledSymbol.setVisible(False)
    g.cryptoHwAesCtrEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesCtrSupported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesCtrEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-XTS
    g.cryptoAesXtsEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_xts_en", g.aesModesMenu)
    g.cryptoAesXtsEnabledSymbol.setLabel("AES-XTS Mode?")
    g.cryptoAesXtsEnabledSymbol.setDescription(
            "Enable support for the AES XTS Mode.")
    g.cryptoAesXtsEnabledSymbol.setVisible(True)
    g.cryptoAesXtsEnabledSymbol.setDefaultValue(False)

    #AES-XTS HW
    g.cryptoHwAesXtsEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_xts_hw_en", g.cryptoAesXtsEnabledSymbol)
    g.cryptoHwAesXtsEnabledSymbol.setVisible(False)
    g.cryptoHwAesXtsEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAesXtsSupported):
        g.cryptoHwAesEnabledSymbol.setDependencies(
                handleAesXtsEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-EAX
    #g.cryptoAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
    #        "crypto_sym_aes_eax_en", g.aesModesMenu)
    #g.cryptoAesEaxEnabledSymbol.setLabel("AES EAX Mode? ")
    #g.cryptoAesEaxEnabledSymbol.setDescription(
    #        "Enable support for the AES EAX Mode Algorithm.")
    #g.cryptoAesEaxEnabledSymbol.setVisible(True)
    #g.cryptoAesEaxEnabledSymbol.setDefaultValue(False)
    ##g.cryptoAesEaxEnabledSymbol.setReadOnly(True)

    #AES-EAX HW
    #g.cryptoHwAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
    #        "crypto_sym_aes_eax_hw_en", g.cryptoAesEaxEnabledSymbol)
    #g.cryptoHwAesEaxEnabledSymbol.setVisible(False)
    #g.cryptoHwAesEaxEnabledSymbol.setDefaultValue(False)
    #if (g.cryptoHwAesEaxSupported):
    #    g.cryptoHwAesEnabledSymbol.setDependencies(
    #            handleAesEaxEnabled,
    #            ["crypto_sym_aes_hw"])


#-----------------------------------------------------
#AES
def handleAesHwEnabled(symbol, event):
    print("CRYPTO: handle AES HW (does nothing)")
    return


def handleAesEcbEnabled(symbol, event):
    if (g.cryptoHwAesEcbSupported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesEcbEnabledSymbol.setLabel("AES-ECB (HW)?")
    else:
        g.cryptoAesEcbEnabledSymbol.setLabel("AES-ECB?")
    return

def handleAesCbcEnabled(symbol, event):
    if (g.cryptoHwAesCbcSupported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesCbcEnabledSymbol.setLabel("AES-CBC (HW)?")
    else:
        g.cryptoAesCbcEnabledSymbol.setLabel("AES-CBC?")
    return

def handleAesOfbEnabled(symbol, event):
    if (g.cryptoHwAesOfbSupported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesOfbEnabledSymbol.setLabel("AES-OFB (HW)?")
    else:
        g.cryptoAesOfbEnabledSymbol.setLabel("AES-OFB?")
    return

def handleAesCfb1Enabled(symbol, event):
    if (g.cryptoHwAesCfb1Supported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesCfb1EnabledSymbol.setLabel("AES-CFB(1) (HW)?")
    else:
        g.cryptoAesCfb1EnabledSymbol.setLabel("AES-CFB(1)?")
    return

def handleAesCfb8Enabled(symbol, event):
    if (g.cryptoHwAesCfb8Supported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesCfb8EnabledSymbol.setLabel("AES-CFB(8) (HW)?")
    else:
        g.cryptoAesCfb8EnabledSymbol.setLabel("AES-CFB(8)?")
    return

def handleAesCfb64Enabled(symbol, event):
    if (g.cryptoHwAesCfb64Supported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesCfb64EnabledSymbol.setLabel("AES-CFB(64) (HW)?")
    else:
        g.cryptoAesCfb64EnabledSymbol.setLabel("AES-CFB(64)?")
    return

def handleAesCfb128Enabled(symbol, event):
    if (g.cryptoHwAesCfb128Supported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesCfb128EnabledSymbol.setLabel("AES-CFB(128) (HW)?")
    else:
        g.cryptoAesCfb128EnabledSymbol.setLabel("AES-CFB(128)?")
    return

def handleAesCtrEnabled(symbol, event):
    if (g.cryptoHwAesCtrSupported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesCtrEnabledSymbol.setLabel("AES-CTR (HW)?")
    else:
        g.cryptoAesCtrEnabledSymbol.setLabel("AES-CTR?")
    return

def handleAesXtsEnabled(symbol, event):
    if (g.cryptoHwAesXtsSupported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesXtsEnabledSymbol.setLabel("AES-XTS (HW)?")
    else:
        g.cryptoAesXtsEnabledSymbol.setLabel("AES-XTS?")
    return

def handleAesEaxEnabled(symbol, event):
    if (g.cryptoHwAesEaxSupported and (
        g.cryptoHwAesEnabledSymbol.getValue() == True)):
        g.cryptoAesEaxEnabledSymbol.setLabel("AES-XTS (HW)?")
    else:
        g.cryptoAesEaxEnabledSymbol.setLabel("AES-XTS?")
    return

