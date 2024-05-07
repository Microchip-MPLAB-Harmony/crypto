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


#Scan for AES HW Suported Symbols
def ScanAesHwSymbols():

        #List all the HW supported symbols
        hwSymbols = []
        if (g.cryptoHwSymAesEcbSupported    == True):
            hwSymbols.append(g.cryptoSymAesEcbEnabledSymbol)
        if (g.cryptoHwSymAesCbcSupported    == True):
            hwSymbols.append(g.cryptoSymAesCbcEnabledSymbol)
        if (g.cryptoHwSymAesCtrSupported    == True):
            hwSymbols.append(g.cryptoSymAesCtrEnabledSymbol)
        if (g.cryptoHwSymAesCfb1Supported   == True):
            hwSymbols.append(g.cryptoSymAesCfb1EnabledSymbol)
        if (g.cryptoHwSymAesCfb8Supported   == True):
            hwSymbols.append(g.cryptoSymAesCfb8EnabledSymbol)
        if (g.cryptoHwSymAesCfb64Supported  == True):
            hwSymbols.append(g.cryptoSymAesCfb64EnabledSymbol)
        if (g.cryptoHwSymAesCfb128Supported == True):
            hwSymbols.append(g.cryptoSymAesCfb128EnabledSymbol)
        if (g.cryptoHwSymAesOfbSupported    == True):
            hwSymbols.append(g.cryptoSymAesOfbEnabledSymbol)
        if (g.cryptoHwSymAesGcmSupported    == True):
            hwSymbols.append(g.cryptoSymAesGcmEnabledSymbol)
        if (g.cryptoHwSymAesCcmSupported    == True):
            hwSymbols.append(g.cryptoSymAesCcmEnabledSymbol)
        if (g.cryptoHwSymAesXtsSupported    == True):
            hwSymbols.append(g.cryptoSymAesXtsEnabledSymbol)

        print("AES HW SCAN:")
        for hSym in hwSymbols:
            print("  %s"%(hSym.getID()))

        g.cryptoAesHwEnSymbols = hwSymbols

################################################################################
#Scan to see if any of the Hash Selections is True and set the symbol
#CONFIG_USE_SYM
#--Returns True if CONFIG_USE_SYM changes value
################################################################################
def ScanSym():
    if   (g.cryptoSymAesEcbEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSymAesCbcEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSymAesOfbEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSymAesCfb1EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSymAesCfb8EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSymAesCfb64EnabledSymbol.getValue()  == True): newValue = True
    elif (g.cryptoSymAesCfb128EnabledSymbol.getValue() == True): newValue = True
    elif (g.cryptoSymAesCtrEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSymAesGcmEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSymAesCcmEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSymAesXtsEnabledSymbol.getValue()    == True): newValue = True
    #elif (g.cryptoSymAesEaxEnabledSymbol.getValue()    == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_SYM.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_SYM.setValue(newValue)
        print("CRYPO:  CONFIG_USE_SYM = %s"%(g.CONFIG_USE_SYM.getValue()))
        return True

#Check if the AES is enabled and the AES HW Driver Files are needed.
# TODO:  For now only Mistral 6146. Some mods required for other HW
#--Returns True if the AES HW Driver enable/disable has changed
def ScanSymAesHwLabels():
    retVal = False
    fKey = "AES"

    newValue = False
    if (g.cryptoSymAesEnabledSymbol.getValue()   == True):
        if (g.cryptoHwSymAesEnabledSymbol.getValue() == True):
            newValue = True
        else:
            newValue = False
    else:
         newValue = False
    print("AES: aes_hw - %s (newValue = %s)"%(
        g.CONFIG_USE_AES_HW.getValue(), newValue))

    #Check if value changed
    if (g.CONFIG_USE_AES_HW.getValue() != newValue):

        g.CONFIG_USE_AES_HW.setValue(newValue)
        print("AES:  Enable HW (%s)"%(newValue))
        for fSym in g.hwDriverFileDict[fKey]:
            fSym.setEnabled(newValue)

        print("AES:  Update HW(%s) Symbol Labels"%(newValue))
        for sym in g.cryptoAesHwEnSymbols:
            lbl = sym.getLable()
            print("  %s"%(lbl))
            if (newValue == True):
                lbl += " (HW)"
            else:
                lbl = lbl[:-4]
            sym.setLable(lbl)

        return True

    else:
        return False


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

    #AES HW Driver Generation Enable
    g.CONFIG_USE_AES_HW = cryptoComponent.createBooleanSymbol(
            "config_use_aes_hw", g.hashMenu)
    g.CONFIG_USE_AES_HW.setVisible(False)
    g.CONFIG_USE_AES_HW.setLabel("Crypto AES HW")
    g.CONFIG_USE_AES_HW.setDefaultValue(False) #Always initialize False


    #SYM AES Main Menu
    g.aesMenu = cryptoComponent.createMenuSymbol(
            "crypto_sym_aes_menu", g.symMenu)
    g.aesMenu.setLabel("AES Algorithms")
    g.aesMenu.setDescription("AES Algorithms:")
    g.aesMenu.setVisible(True)
    g.aesMenu.setHelp('CRYPT_AES_SUM')

    #SYM AES Enable (For all AES Algorithms) 
    g.cryptoSymAesEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_en", g.aesMenu)
    g.cryptoSymAesEnabledSymbol.setLabel("Use AES ?")
    g.cryptoSymAesEnabledSymbol.setDescription("Enable AES Algorithms")
    g.cryptoSymAesEnabledSymbol.setVisible(False)
    g.cryptoSymAesEnabledSymbol.setDefaultValue(True)

    #SYM AES Enable (For all AES Algorithms with HW Support)
    g.cryptoHwSymAesEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_hw_en", g.aesMenu)
    g.cryptoHwSymAesEnabledSymbol.setLabel("Use AES Hardware Acceleration?")
    g.cryptoHwSymAesEnabledSymbol.setDescription(
        "Turn on the hardware acceleration" +
        "for the AES Algorithms")
    if (g.cryptoHwSymAesSupported):
        g.cryptoHwSymAesEnabledSymbol.setDependencies(
                handleAesHwEnabled,
                ["crypto_sym_aes_hw_en"])
        g.cryptoHwSymAesEnabledSymbol.setVisible(True)
        g.cryptoHwSymAesEnabledSymbol.setDefaultValue(False)
    else:
        g.cryptoHwSymAesEnabledSymbol.setVisible(False)
        g.cryptoHwSymAesEnabledSymbol.setDefaultValue(False)
    g.cryptoHwSymAesEnabledSymbol.setHelp('CRYPT_AES_SUM')


    #Global to indicate when AES Modes are visible
    g.cryptoSymAesModesSupported = True 

    #AES MODES MENU
    g.aesModesMenu = cryptoComponent.createMenuSymbol("crypto_sym_aes_modes", g.aesMenu)
    g.aesModesMenu.setLabel("AES Algorithm Modes")
    g.aesModesMenu.setDescription("AES Modes:")
    g.aesModesMenu.setHelp('CRYPT_AES_MODES_SUM')
    #if (g.cryptoSymAesModesSupported):
    g.aesModesMenu.setVisible(True)
    #else:
    #    g.aesModesMenu.setVisible(False)
    #g.aesModesMenu.setDependencies(
    #            handleAesModesMenu, [
    #                "crypto_sym_aes_128",
    #                "crypto_sym_aes_192",
    #                "crypto_sym_aes_256"])


    #AES-ECB Mode
    g.cryptoSymAesEcbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ecb_en", g.aesModesMenu)
    g.cryptoSymAesEcbEnabledSymbol.setDefaultValue(True)
    if (g.cryptoHwSymAesEcbSupported    == True):
        g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB Mode (HW)?")
    else:
        g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB Mode?")
    g.cryptoSymAesEcbEnabledSymbol.setDescription(
            "Enable support for the AES-ECB Mode Algorithm.")
    g.cryptoSymAesEcbEnabledSymbol.setVisible(True)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesEcbEnabledSymbol)

    #AES-Ecb Mode HW
    g.cryptoHwSymAesEcbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ecb_hw_en", g.cryptoSymAesEcbEnabledSymbol)
    g.cryptoHwSymAesEcbEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesEcbEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesEcbSupported):
        g.cryptoHwSymAesEcbEnabledSymbol.setDependencies(
                handleAesEcbEnabled,
                ["crypto_sym_aes_hw_en"])


    #AES-CBC
    g.cryptoSymAesCbcEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cbc_en", g.aesModesMenu)
    g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC Mode?")
    g.cryptoSymAesCbcEnabledSymbol.setDescription(
            "Enable support for the AES-CBC Mode Algorithm.")
    g.cryptoSymAesCbcEnabledSymbol.setVisible(True)
    g.cryptoSymAesCbcEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCbcEnabledSymbol)

    #AES-CBC HW
    g.cryptoHwSymAesCbcEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aes_sym_cbc_hw", g.cryptoSymAesCbcEnabledSymbol)
    g.cryptoHwSymAesCbcEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCbcEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCbcSupported):
        g.cryptoHwSymAesCbcEnabledSymbol.setDependencies(
                handleAesCbcEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-OFB
    g.cryptoSymAesOfbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ofb_en", g.aesModesMenu)
    g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB Mode?")
    g.cryptoSymAesOfbEnabledSymbol.setDescription(
            "Enable support for the AES-OFB Mode Algorithm.")
    g.cryptoSymAesOfbEnabledSymbol.setVisible(True)
    g.cryptoSymAesOfbEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesOfbEnabledSymbol)

    #AES-OFB HW
    g.cryptoHwSymAesOfbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ofb_hw_en", g.cryptoSymAesOfbEnabledSymbol)
    g.cryptoHwSymAesOfbEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesOfbEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesOfbSupported):
        g.cryptoHwSymAesOfbEnabledSymbol.setDependencies(
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
    g.cryptoSymAesCfb1EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb1_en", g.aesCfbMenu)
    g.cryptoSymAesCfb1EnabledSymbol.setLabel("AES-CFB(1) Mode?")
    g.cryptoSymAesCfb1EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(1) Mode Algorithm.")
    g.cryptoSymAesCfb1EnabledSymbol.setVisible(True)
    g.cryptoSymAesCfb1EnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCfb1EnabledSymbol)

    #AES-CFB1 HW
    g.cryptoHwSymAesCfb1EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb1_hw_en", g.cryptoSymAesCfb1EnabledSymbol)
    g.cryptoHwSymAesCfb1EnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCfb1EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCfb1Supported):
        g.cryptoHwSymAesCfb1EnabledSymbol.setDependencies(
                handleAesCfb1Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB8 Mode
    g.cryptoSymAesCfb8EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb8_en", g.aesCfbMenu)
    g.cryptoSymAesCfb8EnabledSymbol.setLabel("AES-CFB(8) Mode?")
    g.cryptoSymAesCfb8EnabledSymbol.setDescription(
            "Enable support for the AES-CFB8 Mode Algorithm.")
    g.cryptoSymAesCfb8EnabledSymbol.setVisible(True)
    g.cryptoSymAesCfb8EnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCfb8EnabledSymbol)

    #AES-CFB8 HW
    g.cryptoHwSymAesCfb8EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb8_hw_en", g.cryptoSymAesCfb8EnabledSymbol)
    g.cryptoHwSymAesCfb8EnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCfb8EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCfb8Supported):
        g.cryptoHwSymAesCfb8EnabledSymbol.setDependencies(
                handleAesCfb8Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB64 Modes
    g.cryptoSymAesCfb64EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb64_en", g.aesCfbMenu)
    g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB(64) Mode?")
    g.cryptoSymAesCfb64EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(64) Mode Algorithm.")
    g.cryptoSymAesCfb64EnabledSymbol.setVisible(True)
    g.cryptoSymAesCfb64EnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCfb64EnabledSymbol)

    #AES-CFB64 HW
    g.cryptoHwSymAesCfb64EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb64_hw_en", g.cryptoSymAesCfb64EnabledSymbol)
    g.cryptoHwSymAesCfb64EnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCfb64EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCfb64Supported):
        g.cryptoHwSymAesCfb64EnabledSymbol.setDependencies(
                handleAesCfb64Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CFB128 Modes
    g.cryptoSymAesCfb128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb128_en", g.aesCfbMenu)
    g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB(128) Mode?")
    g.cryptoSymAesCfb128EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(128) Mode Algorithm.")
    g.cryptoSymAesCfb128EnabledSymbol.setVisible(True)
    g.cryptoSymAesCfb128EnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCfb128EnabledSymbol)

    #AES-CFB128 HW
    g.cryptoHwSymAesCfb128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb128_hw_en", g.cryptoSymAesCfb128EnabledSymbol)
    g.cryptoHwSymAesCfb128EnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCfb128EnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCfb128Supported):
        g.cryptoHwSymAesCfb128EnabledSymbol.setDependencies(
                handleAesCfb128Enabled,
                ["crypto_sym_aes_hw_en"])

    #AES-CTR
    g.cryptoSymAesCtrEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ctr_en", g.aesModesMenu)
    g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR Mode?")
    g.cryptoSymAesCtrEnabledSymbol.setDescription(
            "Enable support for the AES-CTR Mode Algorithm.")
    g.cryptoSymAesCtrEnabledSymbol.setVisible(True)
    g.cryptoSymAesCtrEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCtrEnabledSymbol)

    #AES-CTR HW
    g.cryptoHwSymAesCtrEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ctr_hw_en", g.cryptoSymAesCtrEnabledSymbol)
    g.cryptoHwSymAesCtrEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCtrEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCtrSupported):
        g.cryptoHwSymAesCtrEnabledSymbol.setDependencies(
                handleAesCtrEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-XTS
    g.cryptoSymAesXtsEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_xts_en", g.aesModesMenu)
    g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS Mode?")
    g.cryptoSymAesXtsEnabledSymbol.setDescription(
            "Enable support for the AES XTS Mode.")
    g.cryptoSymAesXtsEnabledSymbol.setVisible(True)
    g.cryptoSymAesXtsEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesXtsEnabledSymbol)

    #AES-XTS HW
    g.cryptoHwSymAesXtsEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_xts_hw_en", g.cryptoSymAesXtsEnabledSymbol)
    g.cryptoHwSymAesXtsEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesXtsEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesXtsSupported):
        g.cryptoHwSymAesXtsEnabledSymbol.setDependencies(
                handleAesXtsEnabled,
                ["crypto_sym_aes_hw_en"])

    g.cryptoSymAesGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_gcm_en", g.aesModesMenu)
    g.cryptoSymAesGcmEnabledSymbol.setDefaultValue(True)
    if (g.cryptoHwSymAesGcmSupported    == True):
        g.cryptoSymAesGcmEnabledSymbol.setLabel("AES-GCM Mode (HW)?")
    else:
        g.cryptoSymAesGcmEnabledSymbol.setLabel("AES-GCM Mode?")
    g.cryptoSymAesGcmEnabledSymbol.setDescription(
            "Enable support for the AES-GCM Mode Algorithm.")
    g.cryptoSymAesGcmEnabledSymbol.setVisible(True)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesGcmEnabledSymbol)

    #AES-Gcm Mode HW
    g.cryptoHwSymAesGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_gcm_hw_en", g.cryptoSymAesGcmEnabledSymbol)
    g.cryptoHwSymAesGcmEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesGcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesGcmSupported):
        g.cryptoHwSymAesGcmEnabledSymbol.setDependencies(
                handleAesGcmEnabled,
                ["crypto_sym_aes_hw_en"])

    g.cryptoSymAesCcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ccm_en", g.aesModesMenu)
    g.cryptoSymAesCcmEnabledSymbol.setDefaultValue(True)
    if (g.cryptoHwSymAesCcmSupported    == True):
        g.cryptoSymAesCcmEnabledSymbol.setLabel("AES-CCM Mode (HW)?")
    else:
        g.cryptoSymAesCcmEnabledSymbol.setLabel("AES-CCM Mode?")
    g.cryptoSymAesCcmEnabledSymbol.setLabel("AES-CCM Mode?")
    g.cryptoSymAesCcmEnabledSymbol.setDescription(
            "Enable support for the AES-CCM Mode Algorithm.")
    g.cryptoSymAesCcmEnabledSymbol.setVisible(True)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCcmEnabledSymbol)

    #AES-Ccm Mode HW
    g.cryptoHwSymAesCcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ccm_hw_en", g.cryptoSymAesCcmEnabledSymbol)
    g.cryptoHwSymAesCcmEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesCcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesCcmSupported):
        g.cryptoHwSymAesCcmEnabledSymbol.setDependencies(
                handleAesCcmEnabled,
                ["crypto_sym_aes_hw_en"])

    #AES-EAX
    g.cryptoSymAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_eax_en", g.aesModesMenu)
    g.cryptoSymAesEaxEnabledSymbol.setLabel("AES EAX Mode? ")
    g.cryptoSymAesEaxEnabledSymbol.setDescription(
            "Enable support for the AES EAX Mode Algorithm.")
    g.cryptoSymAesEaxEnabledSymbol.setVisible(True)
    g.cryptoSymAesEaxEnabledSymbol.setDefaultValue(False)
    g.cryptoSymAesEaxEnabledSymbol.setReadOnly(True)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesEaxEnabledSymbol)

    #AES-EAX HW
    g.cryptoHwSymAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_eax_hw_en", g.cryptoSymAesEaxEnabledSymbol)
    g.cryptoHwSymAesEaxEnabledSymbol.setVisible(False)
    g.cryptoHwSymAesEaxEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwSymAesEaxSupported):
        g.cryptoHwSymAesEaxEnabledSymbol.setDependencies(
                handleAesEaxEnabled,
                ["crypto_sym_aes_hw"])

    #Check to see if any of the Sym selections is True
    #--Used to include the CC Sym API Files
    ScanSym()
    ScanAesHwSymbols() #Setup list of hardware enabled symbols
    #ScanSymAesHwLabels() #Label based on current HW setting
    newValue = g.cryptoHwSymAesEnabledSymbol.getValue()
    g.CONFIG_USE_AES_HW.setValue(newValue)
    print("AES:  Enable HW (%s)"%(newValue))

    #Enable/Disable HW Driver Files
    for fSym in g.hwDriverFileDict["AES"]:
        fSym.setEnabled(newValue)


#-----------------------------------------------------
#AES
def handleAesHwEnabled(symbol, event):
    print("CRYPTO: handle AES HW (does nothing)")
    newValue = g.cryptoHwSymAesEnabledSymbol.getValue()
    if (g.CONFIG_USE_AES_HW.getValue() != newValue):

        g.CONFIG_USE_AES_HW.setValue(newValue)
        print("AES:  Enable HW (%s)"%(newValue))

        #Enable/Disable HW Driver Files
        for fSym in g.hwDriverFileDict["AES"]:
            fSym.setEnabled(newValue)

        #Update the symbol label for HW or not
        #for hSym in g.cryptoAesHwEnSymbols:
        #    lbl = hSym.getLabel()
        #    if (newValue == True): hSym.setLable(lbl + " (HW)")
        #    else: hSym.setLable(lbl[:-4])


def handleAesEcbEnabled(symbol, event):
    if (g.cryptoHwSymAesEcbSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        print("AES ECB: HW Supported")
        g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB (HW)?")
    else:
        print("AES ECB: HW NOT Supported")
        g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCbcEnabled(symbol, event):
    if (g.cryptoHwSymAesCbcSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC (HW)?")
    else:
        g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesOfbEnabled(symbol, event):
    if (g.cryptoHwSymAesOfbSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        print("AES OFB: HW Supported")
        g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB (HW)?")
    else:
        print("AES OFB: HW NOT Supported")
        g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCfb1Enabled(symbol, event):
    if (g.cryptoHwSymAesCfb1Supported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCfb1EnabledSymbol.setLabel("AES-CFB(1) (HW)?")
    else:
        g.cryptoSymAesCfb1EnabledSymbol.setLabel("AES-CFB(1)?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCfb8Enabled(symbol, event):
    if (g.cryptoHwSymAesCfb8Supported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCfb8EnabledSymbol.setLabel("AES-CFB(8) (HW)?")
    else:
        g.cryptoSymAesCfb8EnabledSymbol.setLabel("AES-CFB(8)?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCfb64Enabled(symbol, event):
    if (g.cryptoHwSymAesCfb64Supported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB(64) (HW)?")
    else:
        g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB(64)?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCfb128Enabled(symbol, event):
    if (g.cryptoHwSymAesCfb128Supported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB(128) (HW)?")
    else:
        g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB(128)?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCtrEnabled(symbol, event):
    if (g.cryptoHwSymAesCtrSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR (HW)?")
    else:
        g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesGcmEnabled(symbol, event):
    if (g.cryptoHwSymAesGcmSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesGcmEnabledSymbol.setLabel("AES-GCM (HW)?")
    else:
        g.cryptoSymAesGcmEnabledSymbol.setLabel("AES-GCM?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesCcmEnabled(symbol, event):
    if (g.cryptoHwSymAesCcmSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesCcmEnabledSymbol.setLabel("AES-CCM (HW)?")
    else:
        g.cryptoSymAesCcmEnabledSymbol.setLabel("AES-CCM?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesXtsEnabled(symbol, event):
    if (g.cryptoHwSymAesXtsSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS (HW)?")
    else:
        g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

def handleAesEaxEnabled(symbol, event):
    if (g.cryptoHwSymAesEaxSupported and (
        g.cryptoHwSymAesEnabledSymbol.getValue() == True)):
        g.cryptoSymAesEaxEnabledSymbol.setLabel("AES-XTS (HW)?")
    else:
        g.cryptoSymAesEaxEnabledSymbol.setLabel("AES-XTS?")
    if (ScanSym() == True):
        data = symbol.getComponent()
    return

