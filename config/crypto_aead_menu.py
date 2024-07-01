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

#NOTE:  The HW enable for AED-AES is in the SYM-AES Menu

################################################################################
#Scan to see if any of the Aead Selections is True and set the symbol
#CONFIG_USE_AEAD
#--Returns True if CONFIG_USE_AEAD changes value
################################################################################
def ScanAead():

    if   (g.cryptoAeadAesGcmEnabledSymbol.getValue()     == True): newValue = True
    elif (g.cryptoAeadAesCcmEnabledSymbol.getValue()     == True): newValue = True
    elif (g.cryptoAeadAesEaxEnabledSymbol.getValue()     == True): newValue = True
    elif (g.cryptoAeadAesSivCmacEnabledSymbol.getValue() == True): newValue = True
    elif (g.cryptoAeadAesSivGcmEnabledSymbol.getValue()  == True): newValue = True
    else: newValue = False

    #Setup AEAD HW Enables
    #--based on SYM-AES HW Enable
    if (g.cryptoHwAeadAesGcmSupported == True):
        if (g.cryptoAeadAesGcmEnabledSymbol.getValue() == True):
            g.cryptoHwAeadAesGcmEnabledSymbol.setValue(
                g.cryptoHwSymAesEnabledSymbol.getValue())
        else: g.cryptoHwAeadAesGcmEnabledSymbol.setValue(False)
    else: g.cryptoHwAeadAesGcmEnabledSymbol.setValue(False)

    if (g.cryptoHwAeadAesCcmSupported == True):
        if (g.cryptoAeadAesCcmEnabledSymbol.getValue() == True):
            g.cryptoHwAeadAesCcmEnabledSymbol.setValue(
                g.cryptoHwSymAesEnabledSymbol.getValue())
        else: g.cryptoHwAeadAesCcmEnabledSymbol.setValue(False)
    else: g.cryptoHwAeadAesCcmEnabledSymbol.setValue(False)

    if (g.cryptoHwAeadAesEaxSupported == True):
        if (g.cryptoAeadAesEaxEnabledSymbol.getValue() == True):
            g.cryptoHwAeadAesEaxEnabledSymbol.setValue(
                g.cryptoHwSymAesEnabledSymbol.getValue())
        else: g.cryptoHwAeadAesEaxEnabledSymbol.setValue(False)
    else: g.cryptoHwAeadAesEaxEnabledSymbol.setValue(False)

    if (g.cryptoHwAeadAesSivCmacSupported == True):
        if (g.cryptoAeadAesSivCmacEnabledSymbol.getValue() == True):
            g.cryptoHwAeadAesSivCmacEnabledSymbol.setValue(
                g.cryptoHwSymAesEnabledSymbol.getValue())
        else: g.cryptoHwAeadAesSivCmacEnabledSymbol.setValue(False)
    else: g.cryptoHwAeadAesSivCmacEnabledSymbol.setValue(False)

    if (g.cryptoHwAeadAesSivGcmSupported == True):
        if (g.cryptoAeadAesSivGcmEnabledSymbol.getValue() == True):
            g.cryptoHwAeadAesSivGcmEnabledSymbol.setValue(
                g.cryptoHwSymAesEnabledSymbol.getValue())
        else: g.cryptoHwAeadAesSivGcmEnabledSymbol.setValue(False)
    else: g.cryptoHwAeadAesSivGcmEnabledSymbol.setValue(False)

    if (g.CONFIG_USE_AEAD.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_AEAD.setValue(newValue)
        print("CRYPTO:  CONFIG_USE_AEAD = %s"%(g.CONFIG_USE_AEAD.getValue()))
        return True

#Scan for Updated AES HW Supported Symbols
def ScanAeadHwSymbols():

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
                print("AEAD AES: One Enabled");
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
################################################################################
def UpdateAeadAesHwDriverFiles():

    ScanAead()          #Update CONFIG_USE_AEAD
    ScanAeadHwSymbols() #Update CONFIG_USE_AES_HW
                        #and g.cryptoHwAeadAesEnabledSymbol

    hwVal = g.cryptoHwSymAesEnabledSymbol.getValue()

    print("AEAD:  Update Driver AEAD-AES HW(%s-%s)"%(
          hwVal, g.CONFIG_USE_AES_HW.getValue()))

    hwVal = g.CONFIG_USE_AES_HW.getValue()

    #Enable/Disable HW Driver Files
    for fSym in g.hwDriverFileDict["AES"]:
        fSym.setEnabled(hwVal)
        print("  %s(%s)"%(fSym.getID(), fSym.getEnabled()))

    UpdateAeadAesMenuLabels(hwVal)


################################################################################
################################################################################
def UpdateAeadAesMenuLabels(hwEnabled):
    print("AEAD:  Update Labels (hw=%s)"%(hwEnabled))
    if (g.cryptoHwAeadAesGcmSupported == True):
        if (hwEnabled == True):
            g.cryptoAeadAesGcmEnabledSymbol.setLabel("AES-GCM (HW)?")
        else:
            g.cryptoAeadAesGcmEnabledSymbol.setLabel("AES-GCM?")
    else:
        g.cryptoAeadAesGcmEnabledSymbol.setLabel("AES-GCM?")

    if (g.cryptoHwAeadAesCcmSupported == True):
        if (hwEnabled == True):
            g.cryptoAeadAesCcmEnabledSymbol.setLabel("AES-CCM (HW)?")
        else:
            g.cryptoAeadAesCcmEnabledSymbol.setLabel("AES-CCM?")
    else:
        g.cryptoAeadAesCcmEnabledSymbol.setLabel("AES-CCM?")

    if (g.cryptoHwAeadAesEaxSupported == True):
        if (hwEnabled == True):
            g.cryptoAeadAesEaxEnabledSymbol.setLabel("AES-EAX (HW)?")
        else:
            g.cryptoAeadAesEaxEnabledSymbol.setLabel("AES-EAX?")
    else:
        g.cryptoAeadAesEaxEnabledSymbol.setLabel("AES-EAX?")

    if (g.cryptoHwAeadAesSivCmacSupported == True):
        if (hwEnabled == True):
            g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AES-SIV CMAC (HW)?")
        else:
            g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AES-SIV CMAC?")
    else:
        g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AES-SIV CMAC?")

    if (g.cryptoHwAeadAesSivGcmSupported == True):
        if (hwEnabled == True):
            g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AES-SIV GCM (HW)?")
        else:
            g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AES-SIV GCM?")
    else:
        g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AES-SIV GCM?")

    return


################################################################################
################################################################################
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
    g.aeadAesMenu.setLabel("AEAD-AES(128/192/256 bit)")
    g.aeadAesMenu.setDescription("AEAD-AES  Algorithms:")
    g.aeadAesMenu.setVisible(True)
    g.aeadAesMenu.setHelp('CRYPTO_AEAD_AES_SUM')

    #AEAD-AES HW Enable (For all AEAD-AES Algorithms with HW Support)
    #TODO:  Not visible for now. Using the AES menu HW enable
    g.cryptoHwAeadAesEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_hw_en", g.aeadAesMenu)
    g.cryptoHwAeadAesEnabledSymbol.setLabel("Use AES Hardware Acceleration?")
    g.cryptoHwAeadAesEnabledSymbol.setDescription(
        "Turn on the hardware acceleration" +
        "for the AES Algorithms")
    if (g.cryptoHwAeadAesSupported == True):
        g.cryptoHwAeadAesEnabledSymbol.setDependencies(
                handleAeadAesHwEnabled,
                ["crypto_aead_aes_hw_en", "crypto_sym_aes_hw_en"])
        g.cryptoHwAeadAesEnabledSymbol.setVisible(False)
        g.cryptoHwAeadAesEnabledSymbol.setDefaultValue(False)
    else:
        g.cryptoHwAeadAesEnabledSymbol.setVisible(False)
        g.cryptoHwAeadAesEnabledSymbol.setDefaultValue(False)
    g.cryptoHwAeadAesEnabledSymbol.setHelp('CRYPTO_AEAD_SUM')

    #AEAD-AES Main Menu
    g.aeadAesCom = cryptoComponent.createCommentSymbol(
            "crypto_aead_aes_com", g.aeadAesMenu)
    g.aeadAesCom.setLabel(
            "NOTE:  Enable hardware acceleration under the Symmetric/AES menu")
    g.aeadAesMenu.setVisible(True)


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
    if (g.cryptoHwAeadAesGcmSupported == True):
        print("AEAD: AEAD-AES HW GCM Supported")
        g.cryptoAeadAesGcmEnabledSymbol.setDependencies(
                handleAeadAesGcmEnabled,
                ["crypto_sym_aes_hw_en",
                 "crypto_aead_aes_gcm_en"])

    #AEAD-AES GCM HW Mode 
    g.cryptoHwAeadAesGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_gcm_hw_en", g.cryptoAeadAesGcmEnabledSymbol)
    g.cryptoHwAeadAesGcmEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesGcmEnabledSymbol.setDefaultValue(False)

    #AEAD-AES CCM Mode
    g.cryptoAeadAesCcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_ccm_en", g.aeadAesModesMenu)
    g.cryptoAeadAesCcmEnabledSymbol.setLabel("AEAD-AES CCM Mode?")
    g.cryptoAeadAesCcmEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES CCM Mode Algorithm.")
    g.cryptoAeadAesCcmEnabledSymbol.setVisible(True)
    g.cryptoAeadAesCcmEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesCcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesCcmSupported == True):
        g.cryptoAeadAesCcmEnabledSymbol.setDependencies(
                handleAeadAesCcmEnabled,
                ["crypto_sym_aes_hw_en",
                 "crypto_aead_aes_ccm_en"])

    #AEAD-AES CCM HW Mode 
    g.cryptoHwAeadAesCcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_ccm_hw_en", g.cryptoAeadAesCcmEnabledSymbol)
    g.cryptoHwAeadAesCcmEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesCcmEnabledSymbol.setDefaultValue(False)

    #AEAD-AES EAX
    g.cryptoAeadAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_eax_en", g.aeadAesModesMenu)
    g.cryptoAeadAesEaxEnabledSymbol.setLabel("AEAD-AES EAX Mode? ")
    g.cryptoAeadAesEaxEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES EAX Mode Algorithm.")
    g.cryptoAeadAesEaxEnabledSymbol.setVisible(True)
    g.cryptoAeadAesEaxEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesEaxEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesEaxSupported == True):
        g.cryptoAeadAesEaxEnabledSymbol.setDependencies(
                handleAeadAesEaxEnabled,
                [ "crypto_sym_aes_hw_en",
                 "crypto_aead_aes_eax_en"])

    #AEAD-AES EAX HW Mode 
    g.cryptoHwAeadAesEaxEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_eax_hw_en", g.cryptoAeadAesEaxEnabledSymbol)
    g.cryptoHwAeadAesEaxEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesEaxEnabledSymbol.setDefaultValue(False)

    #AEAD-AES SIV-CMAC Mode
    g.cryptoAeadAesSivCmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_cmac_en", g.aeadAesModesMenu)
    g.cryptoAeadAesSivCmacEnabledSymbol.setLabel("AEAD-AES SIV-CMAC Mode?")
    g.cryptoAeadAesSivCmacEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES SIV-CMAC Mode Algorithm.")
    g.cryptoAeadAesSivCmacEnabledSymbol.setVisible(True)
    g.cryptoAeadAesSivCmacEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesSivCmacEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesSivCmacSupported == True):
        g.cryptoAeadAesSivCmacEnabledSymbol.setDependencies(
                handleAeadAesSivCmacEnabled,
                [ "crypto_sym_aes_hw_en",
                 "crypto_aead_aes_siv_cmac_en"])

    #AEAD-AES SIV-CMAC HW Mode 
    g.cryptoHwAeadAesSivCmacEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_cmac_hw_en", g.cryptoAeadAesSivCmacEnabledSymbol)
    g.cryptoHwAeadAesSivCmacEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesSivCmacEnabledSymbol.setDefaultValue(False)

    #AEAD-AES SIV-GCM Mode
    g.cryptoAeadAesSivGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_gcm_en", g.aeadAesModesMenu)
    g.cryptoAeadAesSivGcmEnabledSymbol.setLabel("AEAD-AES SIV-GCM Mode?")
    g.cryptoAeadAesSivGcmEnabledSymbol.setDescription(
            "Enable support for the AEAD-AES SIV-GCM Mode Algorithm.")
    g.cryptoAeadAesSivGcmEnabledSymbol.setVisible(True)
    g.cryptoAeadAesSivGcmEnabledSymbol.setReadOnly(False)
    g.cryptoAeadAesSivGcmEnabledSymbol.setDefaultValue(False)
    if (g.cryptoHwAeadAesSivGcmSupported == True):
        g.cryptoAeadAesSivGcmEnabledSymbol.setDependencies(
                handleAeadAesSivGcmEnabled,
                [ "crypto_sym_aes_hw_en",
                 "crypto_aead_aes_siv_gcm_en"])

    #AEAD-AES SIV-GCM HW Mode 
    g.cryptoHwAeadAesSivGcmEnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_aead_aes_siv_gcm_hw_en", g.cryptoAeadAesSivGcmEnabledSymbol)
    g.cryptoHwAeadAesSivGcmEnabledSymbol.setVisible(False)
    g.cryptoHwAeadAesSivGcmEnabledSymbol.setDefaultValue(False)

    #Check to see if any of the AEAD selections is True
    #--Used to include the CC AEAD API Files
    UpdateAeadAesHwDriverFiles()

#-----------------------------------------------------
#AEAD-AES Handlers
#--NOT USED
def handleAeadAesHwEnabled(symbol, event):
    print("CRYPTO AEAD: Update HW settings") 
    if (g.cryptoHwAeadAesSupported == True):
        #Dependent on SYM-AES setting
        g.cryptoHwAeadAesEnabledSymbol.setValue(
                g.cryptoHwSymAesEnabledSymbol.getValue())
    UpdateAeadAesHwDriverFiles()
    return

def handleAeadAesGcmEnabled(symbol, event):
    print("AEAD: Symbol - " + event["namespace"] + " EID " + event["id"])
    print("AEAD: Handle Event SID %s (HW Support %s)"%(
        symbol.getID(), g.cryptoHwSymAesEnabledSymbol.getValue()))
    UpdateAeadAesHwDriverFiles()
    return

def handleAeadAesCcmEnabled(symbol, event):
    UpdateAeadAesHwDriverFiles()
    return

def handleAeadAesEaxEnabled(symbol, event):
    UpdateAeadAesHwDriverFiles()
    return

def handleAeadAesSivCmacEnabled(symbol, event):
    UpdateAeadAesHwDriverFiles()
    return

def handleAeadAesSivGcmEnabled(symbol, event):
    UpdateAeadAesHwDriverFiles()
    return
