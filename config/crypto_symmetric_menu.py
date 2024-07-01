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
#import crypto_globals   #Initial globals
import crypto_defs as g #Modified globals
import crypto_aead_menu  as am  #Aead Menu
#import superglobals


#Scan for Updated AES HW Supported Symbols
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
        if (g.cryptoHwSymAesXtsSupported    == True):
            hwSymbols.append(g.cryptoSymAesXtsEnabledSymbol)

        #Dependencies to AES HW Driver (AEAD-AES)
        if (g.cryptoHwAeadAesSupported == True):
            print("AES AEAD:  HW AEAD AES Supported")
            if (g.cryptoHwAeadAesGcmSupported    == True):
                hwSymbols.append(g.cryptoAeadAesGcmEnabledSymbol)
            if (g.cryptoHwAeadAesCcmSupported    == True):
                hwSymbols.append(g.cryptoAeadAesCcmEnabledSymbol)
            if (g.cryptoHwAeadAesEaxSupported    == True):
                hwSymbols.append(g.cryptoAeadAesEaxEnabledSymbol)
            if (g.cryptoHwAeadAesSivCmacSupported    == True):
                hwSymbols.append(g.cryptoAeadAesSivCmacEnabledSymbol)
            if (g.cryptoHwAeadAesSivGcmSupported    == True):
                hwSymbols.append(g.cryptoAeadAesSivGcmEnabledSymbol)


        #Check to see if any of the HW enables is true
        #--Check that at least 1 item is selected
        oneEnabled = False
        for hSym in hwSymbols:
            if (hSym.getValue() == True):
                oneEnabled = True
                break;

        g.cryptoAesHwEnSymbols = hwSymbols

        #Check if the AES HW is enabled
        #-->Set the global AES HW enabled symbol
        if (
            g.cryptoHwSymAesEnabledSymbol.getValue() == True and
            oneEnabled == True):
            g.CONFIG_USE_AES_HW.setValue(True)

            #Dependencies to AES HW Driver (AEAD-AES)
            if (g.cryptoHwAeadAesSupported == True):
                g.cryptoHwAeadAesEnabledSymbol.setValue(True)
        else:
            g.CONFIG_USE_AES_HW.setValue(False)

            #Dependencies to AES HW Driver (AEAD-AES)
            if (g.cryptoHwAeadAesSupported == True):
                g.cryptoHwAeadAesEnabledSymbol.setValue(False)

        return

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
    elif (g.cryptoSymAesXtsEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAeadAesGcmEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAeadAesCcmEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAeadAesEaxEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAeadAesSivCmacEnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoAeadAesSivGcmEnabledSymbol.getValue()    == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_SYM.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_SYM.setValue(newValue)
        print("CRYPTO:  CONFIG_USE_SYM = %s"%(g.CONFIG_USE_SYM.getValue()))
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

    #TODO:  g.CONFIG_USE_AES

    #AES HW Driver Generation Enable
    g.CONFIG_USE_AES_HW = cryptoComponent.createBooleanSymbol(
            "config_use_aes_hw", g.hashMenu)
    g.CONFIG_USE_AES_HW.setVisible(False)
    g.CONFIG_USE_AES_HW.setLabel("Crypto AES HW")
    g.CONFIG_USE_AES_HW.setDefaultValue(False) #Always initialize False

    #----------
    #SYM AES HW Enable (For all AES Algorithms with HW Support)
    g.cryptoHwSymAesEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_hw_en", g.aesMenu)
    g.cryptoHwSymAesEnabledSymbol.setLabel("Use AES Hardware Acceleration?")
    g.cryptoHwSymAesEnabledSymbol.setDescription(
        "Turn on the hardware acceleration" +
        "for the AES Algorithms")
    if (g.cryptoHwSymAesSupported):
        g.cryptoHwSymAesEnabledSymbol.setDependencies(
                handleAesHwEnabled,
                ["crypto_sym_aes_hw_en", "crypto_aead_aes_hw_en"])
        g.cryptoHwSymAesEnabledSymbol.setVisible(True)
        g.cryptoHwSymAesEnabledSymbol.setDefaultValue(False)
    else:
        g.cryptoHwSymAesEnabledSymbol.setVisible(False)
        g.cryptoHwSymAesEnabledSymbol.setDefaultValue(False)
    g.cryptoHwSymAesEnabledSymbol.setHelp('CRYPTO_AES_SUM')

    #Global to indicate when AES Modes are visible
    g.cryptoSymAesModesSupported = True

    #----------
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

    #----------
    #AES-ECB Mode
    g.cryptoSymAesEcbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ecb_en", g.aesModesMenu)
    g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB Mode?")
    g.cryptoSymAesEcbEnabledSymbol.setDescription(
            "Enable support for the AES-ECB Mode Algorithm.")
    g.cryptoSymAesEcbEnabledSymbol.setVisible(True)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesEcbEnabledSymbol)
    g.cryptoSymAesEcbEnabledSymbol.setDefaultValue(False)

    #AES-Ecb Mode HW
    if (g.cryptoHwSymAesEcbSupported):
        g.cryptoSymAesEcbEnabledSymbol.setDependencies(
                handleAesEcbEnabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_ecb_en"])

    #AES-CBC
    g.cryptoSymAesCbcEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cbc_en", g.aesModesMenu)
    g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC Mode?")
    g.cryptoSymAesCbcEnabledSymbol.setDescription(
            "Enable support for the AES-CBC Mode Algorithm.")
    g.cryptoSymAesCbcEnabledSymbol.setVisible(True)
    g.cryptoSymAesCbcEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCbcEnabledSymbol)

    #AES-CBC Mode HW
    if (g.cryptoHwSymAesEcbSupported):
        g.cryptoSymAesEcbEnabledSymbol.setDependencies(
                handleAesEcbEnabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_cbc_en"])

    #----------
    #AES-OFB
    g.cryptoSymAesOfbEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ofb_en", g.aesModesMenu)
    g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB Mode?")
    g.cryptoSymAesOfbEnabledSymbol.setDescription(
            "Enable support for the AES-OFB Mode Algorithm.")
    g.cryptoSymAesOfbEnabledSymbol.setVisible(True)
    g.cryptoSymAesOfbEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesOfbEnabledSymbol)

    #AES-OFB Mode HW
    if (g.cryptoHwSymAesOfbSupported):
        g.cryptoSymAesOfbEnabledSymbol.setDependencies(
                handleAesOfbEnabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_ofb_en"])

    #----------
    #AES-CFB Menu
    g.aesCfbMenu = cryptoComponent.createMenuSymbol(
            "crypto_sym_aes_cfb_en", g.aesModesMenu)
    g.aesCfbMenu.setLabel("AES CFB Modes")
    g.aesCfbMenu.setDescription("AES CFB Mode")
    g.aesCfbMenu.setVisible(True)
    g.aesCfbMenu.setHelp('CRYPT_AES_SUM')

    #----------
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
    if (g.cryptoHwSymAesCfb1Supported):
        g.cryptoSymAesCfb1EnabledSymbol.setDependencies(
                handleAesCfb1Enabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_cfb1_en"])

    #----------
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
    if (g.cryptoHwSymAesCfb8Supported):
        g.cryptoSymAesCfb8EnabledSymbol.setDependencies(
                handleAesCfb8Enabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_cfb8_en"])

    #----------
    #AES-CFB64 Mode
    g.cryptoSymAesCfb64EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb64_en", g.aesCfbMenu)
    g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB(64) Mode?")
    g.cryptoSymAesCfb64EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(64) Mode Algorithm.")
    g.cryptoSymAesCfb64EnabledSymbol.setVisible(True)
    g.cryptoSymAesCfb64EnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCfb64EnabledSymbol)

    #AES-CFB64 Mode HW
    if (g.cryptoHwSymAesCfb64Supported):
        g.cryptoSymAesCfb64EnabledSymbol.setDependencies(
                handleAesCfb64Enabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_cfb64_en"])

    #----------
    #AES-CFB128 Mode
    g.cryptoSymAesCfb128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_cfb128_en", g.aesCfbMenu)
    g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB(128) Mode?")
    g.cryptoSymAesCfb128EnabledSymbol.setDescription(
            "Enable support for the AES-CFB(128) Mode Algorithm.")
    g.cryptoSymAesCfb128EnabledSymbol.setVisible(True)
    g.cryptoSymAesCfb128EnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCfb128EnabledSymbol)

    #AES-CFB128 Mode HW
    if (g.cryptoHwSymAesCfb128Supported):
        g.cryptoSymAesCfb128EnabledSymbol.setDependencies(
                handleAesCfb128Enabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_cfb128_en"])

    #----------
    #AES-CTR
    g.cryptoSymAesCtrEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_ctr_en", g.aesModesMenu)
    g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR Mode?")
    g.cryptoSymAesCtrEnabledSymbol.setDescription(
            "Enable support for the AES-CTR Mode Algorithm.")
    g.cryptoSymAesCtrEnabledSymbol.setVisible(True)
    g.cryptoSymAesCtrEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesCtrEnabledSymbol)

    #AES-CTR Mode HW
    if (g.cryptoHwSymAesCtrSupported):
        g.cryptoSymAesCtrEnabledSymbol.setDependencies(
                handleAesCtrEnabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_ctr_en"])

    #----------
    #AES-XTS
    g.cryptoSymAesXtsEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_xts_en", g.aesModesMenu)
    g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS Mode?")
    g.cryptoSymAesXtsEnabledSymbol.setDescription(
            "Enable support for the AES XTS Mode.")
    g.cryptoSymAesXtsEnabledSymbol.setVisible(True)
    g.cryptoSymAesXtsEnabledSymbol.setDefaultValue(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesXtsEnabledSymbol)

    #AES-XTS Mode HW
    if (g.cryptoHwSymAesXtsSupported):
        g.cryptoSymAesXtsEnabledSymbol.setDependencies(
                handleAesXtsEnabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_xts_en"])

    #----------
    #AES-KW (Key Wrap)
    g.cryptoSymAesKwEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sym_aes_kw_en", g.aesModesMenu)
    g.cryptoSymAesKwEnabledSymbol.setLabel("AES Key Wrap? ")
    g.cryptoSymAesKwEnabledSymbol.setDescription(
            "Enable support for the AES KW Mode Algorithm.")
    g.cryptoSymAesKwEnabledSymbol.setVisible(True)
    g.cryptoSymAesKwEnabledSymbol.setDefaultValue(False)
    g.cryptoSymAesKwEnabledSymbol.setReadOnly(False)
    g.cryptoAesEnSymbols.append(g.cryptoSymAesKwEnabledSymbol)

    #AES-KW (Key Wrap) HW
    if (g.cryptoHwSymAesKwSupported):
        g.cryptoSymAesKwEnabledSymbol.setDependencies(
                handleAesKwEnabled,
                ["crypto_sym_aes_hw_en", "crypto_sym_aes_kw_en"])

    #===========================================================================
    # AEAD-AES Menu Setup
    am.SetupCryptoAeadMenu(cryptoComponent)
    #===========================================================================

    #Check to see if any of the Sym selections is True
    #--Used to include the CC Sym API Files
    ScanSym() #CONFIG_USE_SYM
    ScanAesHwSymbols() #CONFIG_USE_SYM_HW value 
                       #and g.cryptoHwSymAesEnabledSymbol
                       #and change display

    UpdateAesHwDriverFiles() #Based on default menu selections


#*******************************************************************************
#*******************************************************************************
def UpdateAesMenuLabels(hwEnabled):
    if (g.cryptoHwSymAesEcbSupported == True):
        if (hwEnabled == True):
            g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB (HW)?")
        else:
            g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB?")
    else:
        g.cryptoSymAesEcbEnabledSymbol.setLabel("AES-ECB?")

    if (g.cryptoHwSymAesCbcSupported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC (HW)?")
        else:
            g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC?")
    else:
        g.cryptoSymAesCbcEnabledSymbol.setLabel("AES-CBC?")

    if (g.cryptoHwSymAesOfbSupported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB (HW)?")
        else:
            g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB?")
    else:
        g.cryptoSymAesOfbEnabledSymbol.setLabel("AES-OFB?")

    if (g.cryptoHwSymAesCfb1Supported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesCfb1EnabledSymbol.setLabel("AES-CFB1 (HW)?")
        else:
            g.cryptoSymAesCfb1EnabledSymbol.setLabel("AES-CFB1?")
    else:
        g.cryptoSymAesCfb1EnabledSymbol.setLabel("AES-CFB1?")

    if (g.cryptoHwSymAesCfb8Supported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesCfb8EnabledSymbol.setLabel("AES-CFB8 (HW)?")
        else:
            g.cryptoSymAesCfb8EnabledSymbol.setLabel("AES-CFB8?")
    else:
        g.cryptoSymAesCfb8EnabledSymbol.setLabel("AES-CFB8?")

    if (g.cryptoHwSymAesCfb64Supported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB64 (HW)?")
        else:
            g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB64?")
    else:
        g.cryptoSymAesCfb64EnabledSymbol.setLabel("AES-CFB64?")

    if (g.cryptoHwSymAesCfb128Supported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB128 (HW)?")
        else:
            g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB128?")
    else:
        g.cryptoSymAesCfb128EnabledSymbol.setLabel("AES-CFB128?")

    if (g.cryptoHwSymAesCtrSupported == True): 
        if (hwEnabled == True):
            g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR (HW)?")
        else:
            g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR?")
    else:
        g.cryptoSymAesCtrEnabledSymbol.setLabel("AES-CTR?")

    if (g.cryptoHwSymAesXtsSupported == True):
        if (hwEnabled == True):
            g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS (HW)?")
        else:
            g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS?")
    else:
        g.cryptoSymAesXtsEnabledSymbol.setLabel("AES-XTS?")

    if (g.cryptoHwSymAesKwSupported == True):
        if (hwEnabled == True):
            g.cryptoSymAesKwEnabledSymbol.setLabel("AES Key Wrap (HW)?")
        else:
            g.cryptoSymAesKwEnabledSymbol.setLabel("AES-Key Wrap?")
    else:
        g.cryptoSymAesKwEnabledSymbol.setLabel("AES-Key Wrap?")

    return

#*******************************************************************************
# Update the AES HW driver generation based on AES HW Enable and 
# one of the AES HW functions being selected.
# Update the labels of the functions that support AES HW
#*******************************************************************************
def UpdateAesHwDriverFiles():

    ScanSym()          #Update CONFIG_USE_SYM
    ScanAesHwSymbols() #Update CONFIG_USE_AES_HW
                       #and g.cryptoHwAeadAesEnabledSymbol

    hwVal = g.cryptoHwSymAesEnabledSymbol.getValue()

    print("AES:  Update Driver SYM HW(%s-%s)"%(
        hwVal, g.CONFIG_USE_AES_HW.getValue()))

    hwVal = g.CONFIG_USE_AES_HW.getValue()

    #Enable/Disable HW Driver Files
    for fSym in g.hwDriverFileDict["AES"]:
        fSym.setEnabled(hwVal)
        print("  %s(%s)"%(fSym.getID(), fSym.getEnabled()))

    UpdateAesMenuLabels(hwVal)


#-----------------------------------------------------
#AES
def handleAesHwEnabled(symbol, event):
    print("AES: Symbol - " + event["namespace"] + " EID " + event["id"])
    print("AES: Handle Event SID %s (HW Support %s)"%(
        symbol.getID(), g.cryptoHwSymAesEnabledSymbol.getValue()))
    UpdateAesHwDriverFiles()

def handleAesEcbEnabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesCbcEnabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesOfbEnabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesCfb1Enabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesCfb8Enabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesCfb64Enabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesCfb128Enabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesCtrEnabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesXtsEnabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

def handleAesKwEnabled(symbol, event):
    UpdateAesHwDriverFiles()
    return

