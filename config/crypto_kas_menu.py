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
    if   (g.cryptoKasEcdhEnabledSymbol.getValue()       == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_KAS.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_KAS.setValue(newValue)
        print("CRYPO:  CONFIG_USE_KAS = %s"%(g.CONFIG_USE_KAS.getValue()))
        return True


def SetupCryptoKasMenu(cryptoComponent):


    #KAS File Generation Enable
    g.CONFIG_USE_KAS= cryptoComponent.createBooleanSymbol(
            "CONFIG_USE_KAS", g.macMenu)
    g.CONFIG_USE_KAS.setVisible(False)
    g.CONFIG_USE_KAS.setLabel("Crypto")
    g.CONFIG_USE_KAS.setDefaultValue(False)

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

#-----------------------------------------------------
#KAS-ECDH Handlers
def handleKasEcdhEnabled(symbol, event):
    if (g.cryptoHwKasEcdhSupported and (
        g.cryptoHwKasEcdhEnabledSymbol.getValue() == True)):
        g.cryptoKasEcdhEnabledSymbol.setLabel("ECDH (HW)?")
    else:
        g.cryptoKasEcdhEnabledSymbol.setLabel("ECDH?")
    return
