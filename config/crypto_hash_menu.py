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
#CONFIG_USE_CRYPTO
#--Returns True if CONFIG_USE_HASH changes value
################################################################################
def ScanHash():
    if   (g.cryptoMd5EnabledSymbol.getValue()       == True): newValue = True
    elif (g.cryptoSha1EnabledSymbol.getValue()      == True): newValue = True
    elif (g.cryptoRipeMd160EnabledSymbol.getValue()      == True): newValue = True
    elif (g.cryptoSha224EnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSha256EnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSha384EnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSha512EnabledSymbol.getValue()    == True): newValue = True
    elif (g.cryptoSha3224EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSha3256EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSha3384EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSha3512EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSha3Shake128EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoSha3Shake256EnabledSymbol.getValue()   == True): newValue = True
    elif (g.cryptoBlake224EnabledSymbol.getValue()  == True): newValue = True
    elif (g.cryptoBlake256EnabledSymbol.getValue()  == True): newValue = True
    elif (g.cryptoBlake384EnabledSymbol.getValue()  == True): newValue = True
    elif (g.cryptoBlake512EnabledSymbol.getValue()  == True): newValue = True
    else: newValue = False

    if (g.CONFIG_USE_HASH.getValue() == newValue):
        return False
    else:
        g.CONFIG_USE_HASH.setValue(newValue)
        print("CRYPO:  CONFIG_USE_HASH = %s"%(g.CONFIG_USE_HASH.getValue()))
        return True

def SetupCryptoHashMenu(cryptoComponent):

    #Hash Main Menu
    g.hashMenu = cryptoComponent.createMenuSymbol(
            "crypto_hash", None)
    g.hashMenu.setLabel("Hash Algorithms")
    g.hashMenu.setDescription("Hash Algorithms: MD and SHA")
    g.hashMenu.setVisible(True)
    g.hashMenu.setHelp('MC_CRYPTO_API_H')

    #HASH File Generation Enable
    g.CONFIG_USE_HASH = cryptoComponent.createBooleanSymbol(
            "config_use_hash", g.hashMenu)
    g.CONFIG_USE_HASH.setVisible(False)
    g.CONFIG_USE_HASH.setLabel("Crypto")
    g.CONFIG_USE_HASH.setDefaultValue(False)

    #OBSOLETED
    #cryptoMd2EnabledSymbol = cryptoComponent.createBooleanSymbol("crypto_md2", hashMenu)
    #cryptoMd2EnabledSymbol.setLabel("Support MD2?")
    #cryptoMd2EnabledSymbol.setDescription("Enable support for the MD2 Hash Algoithm.")
    #cryptoMd2EnabledSymbol.setVisible(True)
    #cryptoMd2EnabledSymbol.setDefaultValue(False)
    #cryptoMd2EnabledSymbol.setHelp('MC_CRYPTO_API_H')

    #OBSOLETED
    #cryptoMd4EnabledSymbol = cryptoComponent.createBooleanSymbol("crypto_md4", hashMenu)
    #cryptoMd4EnabledSymbol.setLabel("Support MD4?")
    #cryptoMd4EnabledSymbol.setDescription("Enable support for the MD4 Hash Algoithm.")
    #cryptoMd4EnabledSymbol.setVisible(True)
    #cryptoMd4EnabledSymbol.setDefaultValue(False)
    #cryptoMd4EnabledSymbol.setHelp('CRYPT_MD4_SUM')

    #MD5 Hash Symbol 
    g.cryptoMd5EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_md5", g.hashMenu)
    g.cryptoMd5EnabledSymbol.setLabel("MD5?")
    g.cryptoMd5EnabledSymbol.setDescription(
            "Enable support for the MD5 Hash Algoithm.")
    g.cryptoMd5EnabledSymbol.setVisible(True)
    g.cryptoMd5EnabledSymbol.setDefaultValue(False)
    g.cryptoMd5EnabledSymbol.setHelp('CRYPT_MD5_SUM')

    #MD5 HW  Symbol
    g.cryptoHwMd5EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_md5_hw", g.cryptoMd5EnabledSymbol)
    g.cryptoHwMd5EnabledSymbol.setLabel(
            "Use Hardware Acceleration?")
    g.cryptoHwMd5EnabledSymbol.setDescription(
            "Turn on hardware acceleration for the MD5 Hash Algorithm")
    if (g.cryptoHwMd5Supported == True):
        g.cryptoHwMd5EnabledSymbol.setDependencies(
                handleMd5Enabled, ["crypto_md5"])

    g.cryptoHwMd5EnabledSymbol.setVisible(False)
    g.cryptoHwMd5EnabledSymbol.setDefaultValue(False)
    g.cryptoHwMd5EnabledSymbol.setHelp('CRYPT_MD5_SUM')


    #RIPEMD_160 Hash Symbol 
    g.cryptoRipeMd160EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_ripe_md_160", g.hashMenu)
    g.cryptoRipeMd160EnabledSymbol.setLabel("Ripe Md - 160?")
    g.cryptoRipeMd160EnabledSymbol.setDescription(
            "Enable support for the MD Hash Algoithm.")
    g.cryptoRipeMd160EnabledSymbol.setVisible(True)
    g.cryptoRipeMd160EnabledSymbol.setDefaultValue(False)
    g.cryptoRipeMd160EnabledSymbol.setHelp('CRYPT_RIPE_MD_SUM')

    #RIPE MD_160 HW  Symbol
    g.cryptoHwRipeMd160EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_ripe_md_160_hw", g.cryptoRipeMd160EnabledSymbol)
    g.cryptoHwRipeMd160EnabledSymbol.setLabel(
            "Use Hardware Acceleration?")
    g.cryptoHwRipeMd160EnabledSymbol.setDescription(
            "Turn on hardware acceleration for the MD Hash Algorithm")
    if (g.cryptoHwRipeMd160Supported == True):
        g.cryptoHwRipeMd160EnabledSymbol.setDependencies(
                handleRipeMd160Enabled, ["crypto_ripe_md_160"])
    g.cryptoHwRipeMd160EnabledSymbol.setVisible(False)
    g.cryptoHwRipeMd160EnabledSymbol.setDefaultValue(False)
    g.cryptoHwRipeMd160EnabledSymbol.setHelp('CRYPT_RIPE_MD_SUM')


    #SHA1 Hash Symbol
    g.cryptoSha1EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha1", g.hashMenu)
    g.cryptoSha1EnabledSymbol.setLabel( "SHA1?")
    g.cryptoSha1EnabledSymbol.setDescription(
            "Enable support for the SHA-1 Hash Algorithm.")
    g.cryptoSha1EnabledSymbol.setVisible(True)
    g.cryptoSha1EnabledSymbol.setDefaultValue(False)
    g.cryptoSha1EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #SHA1 HW Symbol 
    g.cryptoHwSha1EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha1_hw", g.cryptoSha1EnabledSymbol)
    g.cryptoHwSha1EnabledSymbol.setLabel(
            "Use Hardware Acceleration?")
    g.cryptoHwSha1EnabledSymbol.setDescription(
            "Turn on the hardware acceleration" +
            "for the SHA1 Hash Algorithm")
    if (g.cryptoHwSha1Supported == True):
        g.cryptoHwSha1EnabledSymbol.setDependencies(
            handleSha1Enabled, ["crypto_sha1"])
    g.cryptoHwSha1EnabledSymbol.setVisible(False)
    g.cryptoHwSha1EnabledSymbol.setDefaultValue(False)
    g.cryptoHwSha1EnabledSymbol.setHelp('CRYPT_SHA1_SUM')

    #SHA-2 Hash Menu
    g.sha2Menu = cryptoComponent.createMenuSymbol(
            "crypto_sha2", g.hashMenu)
    g.sha2Menu.setLabel("SHA2 Algorithms")
    g.sha2Menu.setDescription("SHA2 Hash Algorithms:")
    g.sha2Menu.setVisible(True)
    g.sha2Menu.setHelp('CRYPT_SHA_SUM')

    #SHA-2/SHA-224 Menu
    g.cryptoSha224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_224", g.sha2Menu)
    g.cryptoSha224EnabledSymbol.setLabel("SHA2-224?")
    g.cryptoSha224EnabledSymbol.setDescription(
            "Enable support for the SHA-2 224 Hash Algoithm.")
    g.cryptoSha224EnabledSymbol.setVisible(True)
    g.cryptoSha224EnabledSymbol.setDefaultValue(False)

    #SHA2-224 HW Symbol
    g.cryptoHwSha224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_224_hw", g.cryptoSha224EnabledSymbol)
    g.cryptoHwSha224EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha224EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA-224 Hash Algorithm")
    if ((g.cryptoHwSha224Supported == True)):
        g.cryptoSha224EnabledSymbol.setDependencies(
                handleSha224Enabled, ["crypto_sha2_224"])
    g.cryptoHwSha224EnabledSymbol.setVisible(False)
    g.cryptoHwSha224EnabledSymbol.setDefaultValue(False)
    g.cryptoHwSha224EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #SHA-2/SHA-256 Symbol
    g.cryptoSha256EnabledSymbol = cryptoComponent.createBooleanSymbol(
             "crypto_sha2_256", g.sha2Menu)
    g.cryptoSha256EnabledSymbol.setLabel("SHA2-256?")
    g.cryptoSha256EnabledSymbol.setDescription(
            "Enable support for the SHA-2 256 Hash Algoithm.")
    g.cryptoSha256EnabledSymbol.setVisible(True)
    g.cryptoSha256EnabledSymbol.setDefaultValue(True)
    g.cryptoHwSha224EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #SHA2-256 HW Symbol
    g.cryptoHwSha256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_256_hw", g.cryptoSha256EnabledSymbol)
    g.cryptoHwSha256EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha256EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA-256 Hash Algorithm")
    if ((g.cryptoHwSha256Supported == True)):
        g.cryptoSha256EnabledSymbol.setDependencies(
                handleSha256Enabled, ["crypto_sha2_256"])
    g.cryptoHwSha256EnabledSymbol.setVisible(False)
    g.cryptoHwSha256EnabledSymbol.setDefaultValue(False)


    #SHA-2/SHA-384 Menu
    g.cryptoSha384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_384", g.sha2Menu)
    g.cryptoSha384EnabledSymbol.setLabel("SHA2-384?")
    g.cryptoSha384EnabledSymbol.setDescription(
            "Use the SHA2-384 Hash Algoithm.")
    g.cryptoSha384EnabledSymbol.setVisible(True)
    g.cryptoSha384EnabledSymbol.setDefaultValue(False)
    g.cryptoSha384EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #SHA2-384 HW Symbol
    g.cryptoHwSha384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_384_hw", g.cryptoSha384EnabledSymbol)
    g.cryptoHwSha384EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha384EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA-384 Hash Algorithm")
    if ((g.cryptoHwSha384Supported == True)):
        g.cryptoSha384EnabledSymbol.setDependencies(
                handleSha384Enabled, ["crypto_sha2_384"])
    g.cryptoHwSha384EnabledSymbol.setVisible(False)
    g.cryptoHwSha384EnabledSymbol.setDefaultValue(False)

    #SHA-2/SHA-512 Menu
    g.cryptoSha512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_512", g.sha2Menu)
    g.cryptoSha512EnabledSymbol.setLabel("SHA2-512?")
    g.cryptoSha512EnabledSymbol.setDescription(
            "Use the SHA2-512 Hash Algorithm.")
    g.cryptoSha512EnabledSymbol.setVisible(True)
    g.cryptoSha512EnabledSymbol.setDefaultValue(False)
    g.cryptoSha512EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #SHA2-512 HW Symbol
    g.cryptoHwSha512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha2_512_hw", g.cryptoSha512EnabledSymbol)
    g.cryptoHwSha512EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha512EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA-512 Hash Algorithm")
    if ((g.cryptoHwSha512Supported == True)):
        g.cryptoSha512EnabledSymbol.setDependencies(
                handleSha512Enabled, ["crypto_sha2_512"])
    g.cryptoHwSha512EnabledSymbol.setVisible(False)
    g.cryptoHwSha512EnabledSymbol.setDefaultValue(False)

    #SHA-3 Hash Menu
    g.sha3Menu = cryptoComponent.createMenuSymbol(
            "crypto_sha3", g.hashMenu)
    g.sha3Menu.setLabel("SHA3 Algorithms")
    g.sha3Menu.setDescription("SHA3 Hash Algorithms:")
    g.sha3Menu.setVisible(True)
    g.sha3Menu.setHelp('CRYPT_SHA_SUM')

    #SHA-3/SHA-224 Symbol 
    g.cryptoSha3224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_224", g.sha3Menu)
    g.cryptoSha3224EnabledSymbol.setLabel("SHA3-224?")
    g.cryptoSha3224EnabledSymbol.setDescription(
            "Enable support for the SHA3-224 Hash Algoithm.")
    g.cryptoSha3224EnabledSymbol.setVisible(True)
    g.cryptoSha3224EnabledSymbol.setDefaultValue(False)
    g.cryptoSha3224EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #Sha3/Sha-224 HW Symbol
    g.cryptoHwSha3224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_224_hw", g.cryptoSha3224EnabledSymbol)
    g.cryptoHwSha3224EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha3224EnabledSymbol.setDescription(
       "Turn on the hardware acceleration" +
       "for the SHA3-224 Hash Algorithm")
    if (g.cryptoHwSha3224Supported == True):
        g.cryptoHwSha3224EnabledSymbol.setDependencies(
                handleSha3224Enabled, ["crypto_sha3_224"])
    g.cryptoHwSha3224EnabledSymbol.setVisible(False)
    g.cryptoHwSha3224EnabledSymbol.setDefaultValue(False)

    #SHA-3/SHA-256 Symbol
    g.cryptoSha3256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_256", g.sha3Menu)
    g.cryptoSha3256EnabledSymbol.setLabel("SHA3-256?")
    g.cryptoSha3256EnabledSymbol.setDescription(
            "Enable support for the SHA3 256 Hash Algoithm.")
    g.cryptoSha3256EnabledSymbol.setVisible(True)
    g.cryptoSha3256EnabledSymbol.setDefaultValue(False)
    g.cryptoSha3256EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #Sha3/Sha3-256 HW Symbol
    g.cryptoHwSha3256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_256_hw", g.cryptoSha3256EnabledSymbol)
    g.cryptoHwSha3256EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha3256EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA3-256 Hash Algorithm")
    if (g.cryptoHwSha3256Supported == True):
        g.cryptoSha3256EnabledSymbol.setDependencies(
                handleSha3256Enabled, ["crypto_sha3_256"])
    g.cryptoHwSha3256EnabledSymbol.setVisible(False)
    g.cryptoHwSha3256EnabledSymbol.setDefaultValue(False)

    #SHA-3/SHA-384 Symbol
    g.cryptoSha3384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_384", g.sha3Menu)
    g.cryptoSha3384EnabledSymbol.setLabel("SHA3-384?")
    g.cryptoSha3384EnabledSymbol.setDescription(
            "Use the SHA3-384 Hash Algorythm.")
    g.cryptoSha3384EnabledSymbol.setVisible(True)
    g.cryptoSha3384EnabledSymbol.setDefaultValue(False)
    g.cryptoSha3384EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #Sha3/Sha3-384 HW Symbol
    g.cryptoHwSha3384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_384_hw", g.cryptoSha3384EnabledSymbol)
    g.cryptoHwSha3384EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha3384EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA3-384 Hash Algorithm")
    if ((g.cryptoHwSha3384Supported == True)):
        g.cryptoSha3384EnabledSymbol.setDependencies(
                handleSha3384Enabled, ["crypto_sha3_384"])
    g.cryptoHwSha3384EnabledSymbol.setVisible(False)
    g.cryptoHwSha3384EnabledSymbol.setDefaultValue(False)

    #SHA-3/SHA3-512 Symbol 
    g.cryptoSha3512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_512", g.sha3Menu)
    g.cryptoSha3512EnabledSymbol.setLabel("SHA3-512?")
    g.cryptoSha3512EnabledSymbol.setDescription(
            "Use the SHA3-512 Hash Algorithm.")
    g.cryptoSha3512EnabledSymbol.setVisible(True)
    g.cryptoSha3512EnabledSymbol.setDefaultValue(False)
    g.cryptoSha3512EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #Sha3/Sha3-512 HW Symbol
    g.cryptoHwSha3512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_512_hw", g.cryptoSha3512EnabledSymbol)
    g.cryptoHwSha3512EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha3512EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA3-512 Hash Algorithm")
    if ((g.cryptoHwSha3512Supported == True)):
        g.cryptoSha3512EnabledSymbol.setDependencies(
                handleSha3512Enabled, ["crypto_sha3_512"])
    g.cryptoHwSha3512EnabledSymbol.setVisible(False)
    g.cryptoHwSha3512EnabledSymbol.setDefaultValue(False)

    #SHA-3/SHAKE-128 Symbol 
    g.cryptoSha3Shake128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_shake_128", g.sha3Menu)
    g.cryptoSha3Shake128EnabledSymbol.setLabel("SHA3 SHAKE-128?")
    g.cryptoSha3Shake128EnabledSymbol.setDescription(
            "Use the SHA3 SHAKE-128 Hash Algorithm.")
    g.cryptoSha3Shake128EnabledSymbol.setVisible(True)
    g.cryptoSha3Shake128EnabledSymbol.setDefaultValue(False)
    g.cryptoSha3Shake128EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #Sha3/Shake-512 HW Symbol
    g.cryptoHwSha3Shake128EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_shake_128hw", g.cryptoSha3Shake128EnabledSymbol)
    g.cryptoHwSha3Shake128EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha3Shake128EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA3 SHAKE-128 Hash Algorithm")
    if ((g.cryptoHwSha3Shake128Supported == True)):
        g.cryptoSha3Shake128EnabledSymbol.setDependencies(
                handleSha3Shake128Enabled, ["crypto_sha3_shake_128"])
    g.cryptoHwSha3Shake128EnabledSymbol.setVisible(False)
    g.cryptoHwSha3Shake128EnabledSymbol.setDefaultValue(False)

    #SHA-3/SHAKE-256 Symbol 
    g.cryptoSha3Shake256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_shake_256", g.sha3Menu)
    g.cryptoSha3Shake256EnabledSymbol.setLabel("SHA3 SHAKE-256?")
    g.cryptoSha3Shake256EnabledSymbol.setDescription(
            "Use the SHA3 SHAKE-256 Hash Algorithm.")
    g.cryptoSha3Shake256EnabledSymbol.setVisible(True)
    g.cryptoSha3Shake256EnabledSymbol.setDefaultValue(False)
    g.cryptoSha3Shake256EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #Sha3/Shake-512 HW Symbol
    g.cryptoHwSha3Shake256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_sha3_shake_256hw", g.cryptoSha3Shake256EnabledSymbol)
    g.cryptoHwSha3Shake256EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwSha3Shake256EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the SHA3 SHAKE-256 Hash Algorithm")
    if ((g.cryptoHwSha3Shake256Supported == True)):
        g.cryptoSha3Shake256EnabledSymbol.setDependencies(
                handleSha3Shake256Enabled, ["crypto_sha3_shake_256"])
    g.cryptoHwSha3Shake256EnabledSymbol.setVisible(False)
    g.cryptoHwSha3Shake256EnabledSymbol.setDefaultValue(False)

    #BLAKE Hash Menu
    g.blakeMenu = cryptoComponent.createMenuSymbol(
            "crypto_blake", g.hashMenu)
    g.blakeMenu.setLabel("BLAKE Algorithms")
    g.blakeMenu.setDescription("BLAKE Hash Algorithms:")
    g.blakeMenu.setVisible(True)
    g.blakeMenu.setHelp('CRYPT_BLAKE_SUM')

    #BLAKE/BLAKE-224 Symbol
    g.cryptoBlake224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_224", g.blakeMenu)
    g.cryptoBlake224EnabledSymbol.setLabel("BLAKE-224?")
    g.cryptoBlake224EnabledSymbol.setDescription(
            "Enable support for the BLAKE-224 Hash Algoithm.")
    g.cryptoBlake224EnabledSymbol.setVisible(True)
    g.cryptoBlake224EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake224EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #BLAKE/BLAKE-224 HW Symbol
    g.cryptoHwBlake224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_224_hw", g.cryptoBlake224EnabledSymbol)
    g.cryptoHwBlake224EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake224EnabledSymbol.setDescription(
       "Turn on the hardware acceleration" +
       "for the BLAKE-224 Hash Algorithm")
    if (g.cryptoHwBlake224Supported == True):
        g.cryptoHwBlake224EnabledSymbol.setDependencies(
                handleBlake224Enabled, ["crypto_blake_224"])
    g.cryptoHwBlake224EnabledSymbol.setVisible(False)
    g.cryptoHwBlake224EnabledSymbol.setDefaultValue(False)

    #BLAKE/BLAKE-256  Symbol
    g.cryptoBlake256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_256", g.blakeMenu)
    g.cryptoBlake256EnabledSymbol.setLabel("BLAKE-256?")
    g.cryptoBlake256EnabledSymbol.setDescription(
            "Enable support for the BLAKE 256 Hash Algoithm.")
    g.cryptoBlake256EnabledSymbol.setVisible(True)
    g.cryptoBlake256EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake256EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #BLAKE/BLAKE-256  HW Symbol
    g.cryptoHwBlake256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_256_hw", g.cryptoBlake256EnabledSymbol)
    g.cryptoHwBlake256EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake256EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the BLAKE-256 Hash Algorithm")
    if ((g.cryptoHwBlake256Supported == True)):
        g.cryptoBlake256EnabledSymbol.setDependencies(
                handleBlake256Enabled, ["crypto_blake_256"])
    g.cryptoHwBlake256EnabledSymbol.setVisible(False)
    g.cryptoHwBlake256EnabledSymbol.setDefaultValue(False)


    #BLAKE/BLAKE-384 Symbol 
    g.cryptoBlake384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_384", g.blakeMenu)
    g.cryptoBlake384EnabledSymbol.setLabel("BLAKE-384?")
    g.cryptoBlake384EnabledSymbol.setDescription(
            "Use the BLAKE-384 Hash Algoithm.")
    g.cryptoBlake384EnabledSymbol.setVisible(True)
    g.cryptoBlake384EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake384EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #BLAKE/BLAKE-384 HW Symbol 
    g.cryptoHwBlake384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_384_hw", g.cryptoBlake384EnabledSymbol)
    g.cryptoHwBlake384EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake384EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the BLAKE-384 Hash Algorithm")
    if ((g.cryptoHwBlake384Supported == True)):
        g.cryptoBlake384EnabledSymbol.setDependencies(
                handleBlake384Enabled, ["crypto_blake_384"])
    g.cryptoHwBlake384EnabledSymbol.setVisible(False)
    g.cryptoHwBlake384EnabledSymbol.setDefaultValue(False)

    #BLAKE/BLAKE-512 Symbol
    g.cryptoBlake512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_512", g.blakeMenu)
    g.cryptoBlake512EnabledSymbol.setLabel("BLAKE-512?")
    g.cryptoBlake512EnabledSymbol.setDescription(
            "Use the BLAKE-512 Hash Algorithm.")
    g.cryptoBlake512EnabledSymbol.setVisible(True)
    g.cryptoBlake512EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake512EnabledSymbol.setHelp('CRYPT_BLAKE_SUM')

    #BLAKE/BLAKE-512 HW Symbol
    g.cryptoHwBlake512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake_512_hw", g.cryptoBlake512EnabledSymbol)
    g.cryptoHwBlake512EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake512EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the BLAKE-512 Hash Algorithm")
    if ((g.cryptoHwBlake512Supported == True)):
        g.cryptoBlake512EnabledSymbol.setDependencies(
                handleBlake512Enabled, ["crypto_blake_512"])
    g.cryptoHwBlake512EnabledSymbol.setVisible(True)
    g.cryptoHwBlake512EnabledSymbol.setDefaultValue(False)

    #BLAKE2 Hash Menu
    g.blake2Menu = cryptoComponent.createMenuSymbol(
            "crypto_blake2", g.hashMenu)
    g.blake2Menu.setLabel("BLAKE2 Algorithms")
    g.blake2Menu.setDescription("BLAKE2 Hash Algorithms:")
    g.blake2Menu.setVisible(True)
    g.blake2Menu.setHelp('CRYPT_BLAKE2_SUM')

    #BLAKE2/BLAKE2s-224 Symbol
    g.cryptoBlake2s224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2s_224", g.blake2Menu)
    g.cryptoBlake2s224EnabledSymbol.setLabel("BLAKE2s-224?")
    g.cryptoBlake2s224EnabledSymbol.setDescription(
            "Enable support for the BLAKE2s-224 Hash Algoithm.")
    g.cryptoBlake2s224EnabledSymbol.setVisible(True)
    g.cryptoBlake2s224EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake2s224EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    g.cryptoHwBlake2s224EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2s_224_hw", g.cryptoBlake2s224EnabledSymbol)
    g.cryptoHwBlake2s224EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake2s224EnabledSymbol.setDescription(
       "Turn on the hardware acceleration" +
       "for the BLAKE2s-224 Hash Algorithm")
    if (g.cryptoHwBlake2s224Supported == True):
        g.cryptoHwBlake2s224EnabledSymbol.setDependencies(
                handleBlake2s224Enabled, ["crypto_blake2_224"])
    g.cryptoHwBlake2s224EnabledSymbol.setVisible(False)
    g.cryptoHwBlake2s224EnabledSymbol.setDefaultValue(False)

    #BLAKE2/BLAKE2s-256 Symbol 
    g.cryptoBlake2s256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2s_256", g.blake2Menu)
    g.cryptoBlake2s256EnabledSymbol.setLabel("BLAKE2s-256?")
    g.cryptoBlake2s256EnabledSymbol.setDescription(
            "Enable support for the BLAKE2s 256 Hash Algoithm.")
    g.cryptoBlake2s256EnabledSymbol.setVisible(True)
    g.cryptoBlake2s256EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake2s256EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    #BLAKE2/BLAKE2s-256 HW Symbol 
    g.cryptoHwBlake2s256EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2s_256_hw", g.cryptoBlake2s256EnabledSymbol)
    g.cryptoHwBlake2s256EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake2s256EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the BLAKE2s-256 Hash Algorithm")
    if ((g.cryptoHwBlake2s256Supported == True)):
        g.cryptoBlake2s256EnabledSymbol.setDependencies(
                handleBlake2s256Enabled, ["crypto_blake2s_256"])
    g.cryptoHwBlake2s256EnabledSymbol.setVisible(False)
    g.cryptoHwBlake2s256EnabledSymbol.setDefaultValue(False)


    #BLAKE2/BLAKE2B-384 Symbol
    g.cryptoBlake2b384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2b_384", g.blake2Menu)
    g.cryptoBlake2b384EnabledSymbol.setLabel("BLAKE2B-384?")
    g.cryptoBlake2b384EnabledSymbol.setDescription(
            "Use the BLAKE2B-384 Hash Algoithm.")
    g.cryptoBlake2b384EnabledSymbol.setVisible(True)
    g.cryptoBlake2b384EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake2b384EnabledSymbol.setHelp('CRYPT_BLAKE2B_SUM')

    #BLAKE2/BLAKE2B-384 HW Symbol
    g.cryptoHwBlake2b384EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2b_384_hw", g.cryptoBlake2b384EnabledSymbol)
    g.cryptoHwBlake2b384EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake2b384EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the BLAKE2-384 Hash Algorithm")
    if ((g.cryptoHwBlake2b384Supported == True)):
        g.cryptoBlake2b384EnabledSymbol.setDependencies(
                handleBlake2b384Enabled, ["crypto_blake2s_384"])
    g.cryptoHwBlake2b384EnabledSymbol.setVisible(False)
    g.cryptoHwBlake2b384EnabledSymbol.setDefaultValue(False)

    #BLAKE2/BLAKE2B-512 Symbol
    g.cryptoBlake2b512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2b_512", g.blake2Menu)
    g.cryptoBlake2b512EnabledSymbol.setLabel("BLAKE2B-512?")
    g.cryptoBlake2b512EnabledSymbol.setDescription(
            "Use the BLAKE2B-512 Hash Algorithm.")
    g.cryptoBlake2b512EnabledSymbol.setVisible(True)
    g.cryptoBlake2b512EnabledSymbol.setDefaultValue(False)
    g.cryptoBlake2b512EnabledSymbol.setHelp('CRYPT_BLAKE2_SUM')

    #BLAKE2/BLAKE2B-512 HW Symbol
    g.cryptoHwBlake2b512EnabledSymbol = cryptoComponent.createBooleanSymbol(
            "crypto_blake2b_512_hw", g.cryptoBlake2b512EnabledSymbol)
    g.cryptoHwBlake2b512EnabledSymbol.setLabel("Use Hardware Acceleration?")
    g.cryptoHwBlake2b512EnabledSymbol.setDescription(
       "Turn on hardware acceleration" +
       "for the BLAKE2B-512 Hash Algorithm")
    if ((g.cryptoHwBlake2b512Supported == True)):
        g.cryptoBlake2b512EnabledSymbol.setDependencies(
                handleBlake2b512Enabled, ["crypto_blake2b_512"])
    g.cryptoHwBlake2b512EnabledSymbol.setVisible(False)
    g.cryptoHwBlake2b512EnabledSymbol.setDefaultValue(False)

    #Check to see if any of the Hash selections is True
    #--Used to include the CC HASH API Files
    ScanHash()

################################################################################
## Menu Event Handlers
################################################################################

#Set the symbol visible if Parent symbol is selected (event["value"] is True)
def handleParentSymbolChange(symbol, event):
    symbol.setVisible(event["value"])

#-----------------------------------------------------
#MD5
def handleMd5Enabled(symbol, event):
    if (g.cryptoMd5EnabledSymbol.getValue() == True):
        if (g.cryptoHwMd5Supported):
            g.cryptoHwMd5EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwMd5EnabledSymbol.setValue(False)
            g.cryptoHwMd5EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwMd5EnabledSymbol.setValue(False)
        g.cryptoHwMd5EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

#-----------------------------------------------------
#RIPE MD5 - 160
def handleRipeMd5160Enabled(symbol, event):
    if (g.cryptoRipeMd5160EnabledSymbol.getValue() == True):
        if (g.cryptoHwRipeMd5160Supported):
            g.cryptoHwRipeMd5160EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwRipeMd5160EnabledSymbol.setValue(False)
            g.cryptoHwRipeMd5160EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwRipeMd5160EnabledSymbol.setValue(False)
        g.cryptoHwRipeMd5160EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

#-----------------------------------------------------
#SHA1
def handleSha1Enabled(symbol, event):
    if (g.cryptoSha1EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha1Supported):
            g.cryptoHwSha1EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha1EnabledSymbol.setValue(False)
            g.cryptoHwSha1EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha1EnabledSymbol.setValue(False)
        g.cryptoHwSha1EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

#-----------------------------------------------------
#SHA2
def handleSha224Enabled(symbol, event):
    print("CRYPTO:  handle SHA224")
    if (g.cryptoSha224EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha224Supported):
            g.cryptoHwSha224EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha224EnabledSymbol.setValue(False)
            g.cryptoHwSha224EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha224EnabledSymbol.setValue(False)
        g.cryptoHwSha224EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha256Enabled(symbol, event):
    if (g.cryptoSha256EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha256Supported):
            g.cryptoHwSha256EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha256EnabledSymbol.setValue(False)
            g.cryptoHwSha256EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha256EnabledSymbol.setValue(False)
        g.cryptoHwSha256EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha384Enabled(symbol, event):
    if (g.cryptoSha384EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha384Supported):
            g.cryptoHwSha384EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha384EnabledSymbol.setValue(False)
            g.cryptoHwSha384EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha384EnabledSymbol.setValue(False)
        g.cryptoHwSha384EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha512Enabled(symbol, event):
    if (g.cryptoSha512EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha512Supported):
            g.cryptoHwSha512EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha512EnabledSymbol.setValue(False)
            g.cryptoHwSha512EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha512EnabledSymbol.setValue(False)
        g.cryptoHwSha512EnabledSymbol.setVisible(False)

    if (ScanHash() == True):
        data = symbol.getComponent()
#SHA3
def handleSha3224Enabled(symbol, event):
    if (g.cryptoSha3224EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha3224Supported):
            g.cryptoHwSha3224EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha3224EnabledSymbol.setValue(False)
            g.cryptoHwSha3224EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha3224EnabledSymbol.setValue(False)
        g.cryptoHwSha3224EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha3256Enabled(symbol, event):
    if (g.cryptoSha3256EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha3256Supported):
            g.cryptoHwSha3256EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha3256EnabledSymbol.setValue(False)
            g.cryptoHwSha3256EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha3256EnabledSymbol.setValue(False)
        g.cryptoHwSha3256EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha3384Enabled(symbol, event):
    if (g.cryptoSha3384EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha3384Supported):
            g.cryptoHwSha3384EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha3384EnabledSymbol.setValue(False)
            g.cryptoHwSha3384EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha3384EnabledSymbol.setValue(False)
        g.cryptoHwSha3384EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha3512Enabled(symbol, event):
    if (g.cryptoSha3512EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha3512Supported):
            g.cryptoHwSha3512EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha3512EnabledSymbol.setValue(False)
            g.cryptoHwSha3512EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha3512EnabledSymbol.setValue(False)
        g.cryptoHwSha3512EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleSha3Shake128Enabled(symbol, event):
    if (g.cryptoSha3Shake128EnabledSymbol.getValue() == True):
        if (g.cryptoHwSha3Shake128Supported):
            g.cryptoHwSha3Shake128EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwSha3Shake128EnabledSymbol.setValue(False)
            g.cryptoHwSha3Shake128EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwSha3Shake128EnabledSymbol.setValue(False)
        g.cryptoHwSha3Shake128EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

#-----------------------------------------------------
#BLAKE
def handleBlake224Enabled(symbol, event):
    if (g.cryptoBlake224EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake224Supported):
            g.cryptoHwBlake224EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake224EnabledSymbol.setValue(False)
            g.cryptoHwBlake224EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake224EnabledSymbol.setValue(False)
        g.cryptoHwBlake224EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleBlake256Enabled(symbol, event):
    if (g.cryptoBlake256EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake256Supported):
            g.cryptoHwBlake256EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake256EnabledSymbol.setValue(False)
            g.cryptoHwBlake256EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake256EnabledSymbol.setValue(False)
        g.cryptoHwBlake256EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleBlake384Enabled(symbol, event):
    if (g.cryptoBlake384EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake384Supported):
            g.cryptoHwBlake384EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake384EnabledSymbol.setValue(False)
            g.cryptoHwBlake384EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake384EnabledSymbol.setValue(False)
        g.cryptoHwBlake384EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleBlake512Enabled(symbol, event):
    if (g.cryptoBlake512EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake512Supported):
            g.cryptoHwBlake512EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake512EnabledSymbol.setValue(False)
            g.cryptoHwBlake512EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake512EnabledSymbol.setValue(False)
        g.cryptoHwBlake512EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

#-----------------------------------------------------
#BLAKE2
def handleBlake2224Enabled(symbol, event):
    if (g.cryptoBlake2224EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake2224Supported):
            g.cryptoHwBlake2224EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake2224EnabledSymbol.setValue(False)
            g.cryptoHwBlake2224EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake2224EnabledSymbol.setValue(False)
        g.cryptoHwBlake2224EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleBlake2256Enabled(symbol, event):
    if (g.cryptoBlake2256EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake2256Supported):
            g.cryptoHwBlake2256EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake2256EnabledSymbol.setValue(False)
            g.cryptoHwBlake2256EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake2256EnabledSymbol.setValue(False)
        g.cryptoHwBlake2256EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleBlake2384Enabled(symbol, event):
    if (g.cryptoBlake2384EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake2384Supported):
            g.cryptoHwBlake2384EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake2384EnabledSymbol.setValue(False)
            g.cryptoHwBlake2384EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake2384EnabledSymbol.setValue(False)
        g.cryptoHwBlake2384EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

def handleBlake2512Enabled(symbol, event):
    if (g.cryptoBlake2512EnabledSymbol.getValue() == True):
        if (g.cryptoHwBlake2512Supported):
            g.cryptoHwBlake2512EnabledSymbol.setVisible(True)
        else:
            g.cryptoHwBlake2512EnabledSymbol.setValue(False)
            g.cryptoHwBlake2512EnabledSymbol.setVisible(False)
    else:
        g.cryptoHwBlake2512EnabledSymbol.setValue(False)
        g.cryptoHwBlake2512EnabledSymbol.setVisible(False)
    if (ScanHash() == True):
        data = symbol.getComponent()

