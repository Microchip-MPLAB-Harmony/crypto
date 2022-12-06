# coding: utf-8
"""*****************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************"""
import inspect
import os
import sys
import glob
import ntpath

#hardware support
cryptoHwSupported = False
cryptoHwEnabledSymbol = None

cryptoHwTrngSupport = [
    ["RNG", "00159", "", [], set([])],  #PIC32MZ EF
    ["TRNG", "6334", "G", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_6334"])],  #ATSAMV70Q20B
    ["TRNG", "U2242", "1.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_U2242"])], #ATSAML11
    ["TRNG", "U2242", "1.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_U2242"])], #ATSAME54P20A
    ["TRNG", "U2242", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_U2242"])], #ATSAML21J18B
    ["TRNG", "6334", "K", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_6334"])],  #ATSAMA5D27
    ["TRNG", "6334", "O", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_6334"])],  #ATSAM9X60
    ["TRNG", "U2242", "1d0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_U2242"])], #PIC32CM'Lx
    ["TRNG", "03597", "1d0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_03597"])], #PIC32CM'Lx
                     ]
cryptoHwTrngSupported = False
cryptoHwTrngEnabledSymbol = None
cryptoTrngEnabledSymbol = None
cryptoHashDrngEnabledSymbol = None

cryptoHwMd5Support = [["CRYPTO", "00158", "", [], set([])] #PIC32MZ EF
                     ]
cryptoHwMd5Supported = False
cryptoHwMd5EnabledSymbol = None
cryptoMd5EnabledSymbol = None

cryptoHwSha1Support = [["CRYPTO", "00158", "", [], set([])], #PIC32MZ EF
                       ["ICM", "11105", "H", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20B
                       ["ICM", "U2010", "1.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105", "WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
                       ["SHA", "6156", "O", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
                       ["SHA", "6156", "S", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAM9X60
                      ]
cryptoHwSha1Supported = False
cryptoHwSha1EnabledSymbol = None
cryptoSha1EnabledSymbol = None

cryptoHwSha224Support = [
                       ["ICM", "11105", "H", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
                       ["ICM", "U2010", "1.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105", "WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
                       ["SHA", "6156", "O", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
                       ["SHA", "6156", "S", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156", "WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156_R"])], #ATSAM9X60
                       ["IDAU", "U2803", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2803"])], #ATSAML11
                       ["IDAU", "U2805", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2805"])], #PIC32CM
                       ["IDAU", "03710", "2a0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_03710"])], #PIC32CM'Lx
                      ]
cryptoHwSha224Supported = False
cryptoHwSha224EnabledSymbol = None
cryptoSha224EnabledSymbol = None

cryptoHwSha256Support = [["CRYPTO", "00158", "", [], set([])], #PIC32MZ EF
                       ["ICM", "11105", "H", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
                       ["ICM", "U2010", "1.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_11105", "WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
                       ["SHA", "6156", "O", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
                       ["SHA", "6156", "S", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAM9X60
                       ["IDAU", "U2803", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2803"])], #ATSAML11
                       ["IDAU", "U2805", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_U2805"])], #PIC32CM
                       ["IDAU", "03710", "2a0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_03710"])], #PIC32CM'Lx
                      ]
cryptoHwSha256Supported = False
cryptoHwSha256EnabledSymbol = None
cryptoSha256EnabledSymbol = None

cryptoHwSha384Support = [
                       ["SHA", "6156", "O", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
                       ["SHA", "6156", "S", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAM9X60
                      ]
cryptoHwSha384Supported = False
cryptoHwSha384EnabledSymbol = None
cryptoSha384EnabledSymbol = None


cryptoHwSha512Support = [
                       ["SHA", "6156", "O", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
                       ["SHA", "6156", "S", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_SHA_HW_6156"])], #ATSAM9X60
                      ]
cryptoHwSha512Supported = False
cryptoHwSha512EnabledSymbol = None
cryptoSha512EnabledSymbol = None

cryptoAesEnabledSymbol = None
cryptoHwAesEnabledSymbol = None
cryptoAesSmallTableEnabledSymbol = None
cryptoAesEcbEnabledSymbol = None
cryptoAesEcbHwEnabledSymbol = None

cryptoHW_U2803 = [["IDAU", "U2803", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_HW_U2803"])],] #ATSAML11
cryptoHW_U2803Present = False
cryptoHW_U2803Symbol = None
cryptoHW_U2805 = [["IDAU", "U2805", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_HW_U2805"])],] #PIC32CM
cryptoHW_U2805Present = False
cryptoHW_U2805Symbol = None
cryptoHW_03710 = [["IDAU", "03710", "2a0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_HW_03710"])],] #PIC32CM'Lx
cryptoHW_03710Present = False
cryptoHW_03710Symbol = None

cryptoHwAes128Support = [["CRYPTO", "00158", "", [], set([])], #PIC32MZ EF
                       ["AES", "6149", "W", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                       ["AES", "U2238", "2.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                       ["AES", "U2238", "2.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                       ["AES", "U2238", "2.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
                       ["AES", "6149", "ZB", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
                       ["AES", "6149", "ZH", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAM9x60
                       ["IDAU", "U2803", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2803"])], #ATSAML11
                       ["IDAU", "U2805", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805"])], #PIC32CM
                       ["IDAU", "03710", "2a0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_03710"])], #PIC32CM'Lx
                      ]
cryptoHwAes128Supported = False
cryptoAes128EnabledSymbol = None

cryptoHwAes192Support = [["CRYPTO", "00158", "", [], set([])], #PIC32MZ EF
                       ["AES", "6149", "W", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                       ["AES", "U2238", "2.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                       ["AES", "U2238", "2.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                       ["AES", "U2238", "2.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
                       ["AES", "6149", "ZB", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
                       ["AES", "6149", "ZH", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAM9x60
                       ["IDAU", "U2805", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805"])], #PIC32CM
                      ]
cryptoHwAes192Supported = False
cryptoAes192EnabledSymbol = None

cryptoHwAes256Support = [["CRYPTO", "00158", "", [], set([])], #PIC32MZ EF
                       ["AES", "6149", "W", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                       ["AES", "U2238", "2.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                       ["AES", "U2238", "2.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                       ["AES", "U2238", "2.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
                       ["AES", "6149", "ZB", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
                       ["AES", "6149", "ZH", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAM9x60
                       ["IDAU", "U2805", "1.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2805"])], #PIC32CM
                      ]
cryptoHwAes256Supported = False
cryptoAes256EnabledSymbol = None

cryptoHwAesCbcSupport = [
                        ["AES", "6149", "W", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                        ["AES", "U2238", "2.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                        ["AES", "U2238", "2.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                        ["AES", "U2238", "2.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
                        ["AES", "6149", "ZB", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
                        ["AES", "6149", "ZH", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])] #ATSAM9x60
                        ]
cryptoHwAesCbcSupported = False
cryptoHwAesCbcEnabledSymbol = None
cryptoAesCbcEnabledSymbol = None

cryptoHwAesCtrSupport = [
                        ["AES", "6149", "W", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                        ["AES", "U2238", "2.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                        ["AES", "U2238", "2.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                        ["AES", "U2238", "2.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
                        ["AES", "6149", "ZB", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
                        ["AES", "6149", "ZH", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])] #ATSAM9x60
                        ]
cryptoHwAesCtrSupported = False
cryptoHwAesCtrEnabledSymbol = None
cryptoAesCtrEnabledSymbol = None

cryptoHwAesCfbSupport = []
cryptoHwAesCfbSupported = False
cryptoHwAesCfbEnabledSymbol = None
cryptoAesCfbEnabledSymbol = None

cryptoHwAesOfbSupport = []
cryptoHwAesOfbSupported = False
cryptoHwAesOfbEnabledSymbol = None
cryptoAesOfbEnabledSymbol = None

cryptoHwAesXtsSupport = []
cryptoHwAesXtsSupported = False
cryptoHwAesXtsEnabledSymbol = None
cryptoAesXtsEnabledSymbol = None

cryptoHwAesGcmSupport = [
                        ["AES", "6149", "W", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                        ["AES", "U2238", "2.2.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                        ["AES", "U2238", "2.0.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                        ["AES", "U2238", "2.1.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
                        ["AES", "6149", "ZB", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
                        ["AES", "6149", "ZH", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_AES_HW_6149"])] #ATSAM9x60
                        ]
cryptoHwAesGcmSupported = False
cryptoHwAesGcmEnabledSymbol = None
cryptoAesGcmEnabledSymbol = None


cryptoHwAesCcmSupport = []
cryptoHwAesCcmSupported = False
cryptoHwAesCcmEnabledSymbol = None
cryptoAesCcmEnabledSymbol = None

cryptoHwDesSupport = [["CRYPTO", "00158", "", [], set([])], #PIC32MZ EF
                      ["TDES", "6150", "N", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TDES_HW_6150"])], #ATSAMA5D27
                      ["TDES", "6150", "P", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TDES_HW_6150"])], #ATSAM9X60
                      ["TDES", "6150", "R", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_TDES_HW_6150"])], #ATSAM9X60
                     ]
cryptoHwDesSupported = False
cryptoHwDesEnabledSymbol = None
cryptoDesEnabledSymbol = None
cryptoDesEcbEnabledSymbol = None
cryptoHwDesEcbEnabledSymbol = None

cryptoHwDesCbcSupport = []
cryptoHwDesCbcSupported = False
cryptoHwDesCbcEnabledSymbol = None
cryptoDesCbcEnabledSymbol = None

cryptoHwDesCfbSupport = []
cryptoHwDesCfbSupported = False
cryptoHwDesCfbEnabledSymbol = None
cryptoDesCfbEnabledSymbol = None

cryptoHwDesOfbSupport = []
cryptoHwDesOfbSupported = False
cryptoHwDesOfbEnabledSymbol = None
cryptoDesOfbEnabledSymbol = None


cryptoHwRsaSupport = [
                      ["PUKCC", "U2009", "2.5.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_RSA_HW_PUKCC"])], #ATSAME54P20A
                     ]
cryptoHwRsaSupported = False
cryptoHwRsaEnabledSymbol = None
cryptoRsaEnabledSymbol = None


cryptoHwEccSupport = [
                      ["PUKCC", "U2009", "2.5.0", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_ECC_HW_PUKCC"])], #ATSAME54P20A
                      ["BA414E", "00343", "", [], set(["WOLFSSL_HAVE_MCHP_HW_CRYPTO_ECC_HW_BA414E", "WOLFSSL_HAVE_MCHP_BA414E_CRYPTO"])], #PCI32MZ-W
                      ]
cryptoHwEccSupported = False
cryptoHwEccEnabledSymbol = None
cryptoSWCallBackEnableSymbol = None
cryptoEccEnabledSymbol = None

cryptoOverridableSrcFiles = ["aes.c", "des3.c", "random.c", "sha.c", "sha256.c", "sha512.c", ]
cryptoOverridableHeaderFiles = ["aes.h", "sha.h", "sha256.h", "sha512.h", "types.h", "settings.h","wc_port.h",]

localwolfCryptComponent = None
cryptoHwAdditionalDefines = set([])


cryptoWolfSSLIncluded = None
cryptoSupportCompression = None
cryptoHaveZlib = None

asn1Support = None


def instantiateComponent(wolfCryptComponent):
    global cryptoHwSupported
    global cryptoHwEnabledSymbol

    global cryptoHwTrngSupported
    global cryptoHwTrngEnabledSymbol
    global cryptoTrngEnabledSymbol
    global cryptoHashDrngEnabledSymbol

    global cryptoHwMd5Supported
    global cryptoHwMd5EnabledSymbol
    global cryptoMd5EnabledSymbol

    global cryptoHwSha1Supported
    global cryptoHwSha1EnabledSymbol
    global cryptoSha1EnabledSymbol

    global cryptoHwSha224Supported
    global cryptoHwSha224EnabledSymbol
    global cryptoSha224EnabledSymbol

    global cryptoHwSha256Supported
    global cryptoHwSha256EnabledSymbol
    global cryptoSha256EnabledSymbol

    global cryptoHwSha384Supported
    global cryptoHwSha384EnabledSymbol
    global cryptoSha384EnabledSymbol

    global cryptoHwSha512Supported
    global cryptoHwSha512EnabledSymbol
    global cryptoSha512EnabledSymbol

    global cryptoBlake2bEnabledSymbol
    global cryptoSha3EnabledSymbol
    global cryptoHmacEnabledSymbol

    global cryptoHwAesEnabledSymbol
    global cryptoAesSmallTableEnabledSymbol
    global cryptoAesEnabledSymbol
    global cryptoAesEcbEnabledSymbol
    global cryptoHwAesEcbEnabledSymbol
    global cryptoAes128EnabledSymbol
    global cryptoAes192EnabledSymbol
    global cryptoAes256EnabledSymbol

    global cryptoHwAesCbcSupported
    global cryptoHwAesCbcEnabledSymbol
    global cryptoAesCbcEnabledSymbol

    global cryptoHwAesCtrSupported
    global cryptoHwAesCtrEnabledSymbol
    global cryptoAesCtrEnabledSymbol

    global cryptoHwAesCfbSupported
    global cryptoHwAesCfbEnabledSymbol
    global cryptoAesCfbEnabledSymbol

    global cryptoHwAesOfbSupported
    global cryptoHwAesOfbEnabledSymbol
    global cryptoAesOfbEnabledSymbol

    global cryptoHwAesGcmSupported
    global cryptoHwAesGcmEnabledSymbol
    global cryptoAesGcmEnabledSymbol

    global cryptoHwAesXtsSupported
    global cryptoHwAesXtsEnabledSymbol
    global cryptoAesXtsEnabledSymbol

    global cryptoHwAesCcmSupported
    global cryptoHwAesCcmEnabledSymbol
    global cryptoAesCcmEnabledSymbol

    global cryptoHwDesSupported
    global cryptoHwDesEnabledSymbol
    global cryptoDesEnabledSymbol
    global cryptoDesEcbEnabledSymbol
    global cryptoHwDesEcbEnabledSymbol

    global cryptoHwDesCbcSupported
    global cryptoHwDesCbcEnabledSymbol
    global cryptoDesCbcEnabledSymbol

    global cryptoHwDesCfbSupported
    global cryptoHwDesCfbEnabledSymbol
    global cryptoDesCfbEnabledSymbol

    global cryptoHwDesOfbSupported
    global cryptoHwDesOfbEnabledSymbol
    global cryptoDesOfbEnabledSymbol

    global cryptoHwRsaSupported
    global cryptoHwRsaEnabledSymbol
    global cryptoRsaEnabledSymbol

    global cryptoHwEccSupported
    global cryptoHwEccEnabledSymbol
    global cryptoSWCallBackEnableSymbol
    global cryptoEccEnabledSymbol

    global cryptoHW_U2803Present
    global cryptoHW_U2803Symbol
    global cryptoHW_U2805Present
    global cryptoHW_U2805Symbol
    global cryptoHW_03710Present
    global cryptoHW_03710Symbol

    global localwolfCryptComponent
    global cryptoAdditionalHwDefines
    global cryptoWolfSSLIncluded

    global cryptoSupportCompression
    global cryptoHaveZlib

    global cryptoHaveSysTime
    global cryptoDependSysTime

    global asn1Support

    cryptoAdditionalHwDefines = wolfCryptComponent.createStringSymbol("wolfCryptAdditionalHwDefines", None)
    cryptoAdditionalHwDefines.setVisible(False)
    localwolfCryptComponent = wolfCryptComponent

    setupHardware()
    setupFiles(localwolfCryptComponent)

    #---------------------------------------------------------------------------
    #wolfCrypt Library Component Menu
    wolfcrypt = wolfCryptComponent.createBooleanSymbol("wolfcrypt", None)
    wolfcrypt.setLabel("Use wolfCrypt?")
    wolfcrypt.setDescription("Enables wolfCrypt")
    wolfcrypt.setVisible(False)
    wolfcrypt.setDefaultValue(True)

    cryptoWolfSSLIncluded = wolfCryptComponent.createBooleanSymbol("wolfssl_included", None)
    cryptoWolfSSLIncluded.setVisible(False)
    cryptoWolfSSLIncluded.setDefaultValue(False)

    cryptoHwEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_hw", None)
    cryptoHwEnabledSymbol.setLabel("Enable Hardware Cryptography?")
    cryptoHwEnabledSymbol.setDescription("Enables hardware cryptography")
    if (cryptoHwSupported == True):
        cryptoHwEnabledSymbol.setVisible(True)
    else:
        cryptoHwEnabledSymbol.setVisible(False)
    cryptoHwEnabledSymbol.setDefaultValue(False)
    cryptoHwEnabledSymbol.setHelp('MC_CRYPTO_HW_SUM')

    cryptoSWCallBackEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sw_cb", cryptoHwEnabledSymbol)
    cryptoSWCallBackEnableSymbol.setLabel("Crypto ECC/RSA callback optimization")
    cryptoSWCallBackEnableSymbol.setDescription("Enable crypto SW Callback optimization.")
    cryptoSWCallBackEnableSymbol.setVisible(True)
    cryptoSWCallBackEnableSymbol.setDefaultValue(False)

    #Hash Menu
    hashMenu = wolfCryptComponent.createMenuSymbol("wolfcrypt_hash", None)
    hashMenu.setLabel("Hash Algorithms")
    hashMenu.setDescription("Hash Algorithms: MD and SHA")
    hashMenu.setVisible(True)
    hashMenu.setHelp('MC_CRYPTO_API_H')

    cryptoMd2EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_md2", hashMenu)
    cryptoMd2EnabledSymbol.setLabel("Support MD2?")
    cryptoMd2EnabledSymbol.setDescription("Enable support for the MD2 Hash Algoithm.")
    cryptoMd2EnabledSymbol.setVisible(True)
    cryptoMd2EnabledSymbol.setDefaultValue(False)
    cryptoMd2EnabledSymbol.setHelp('MC_CRYPTO_API_H')

    cryptoMd4EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_md4", hashMenu)
    cryptoMd4EnabledSymbol.setLabel("Support MD4?")
    cryptoMd4EnabledSymbol.setDescription("Enable support for the MD4 Hash Algoithm.")
    cryptoMd4EnabledSymbol.setVisible(True)
    cryptoMd4EnabledSymbol.setDefaultValue(False)
    cryptoMd4EnabledSymbol.setHelp('CRYPT_MD4_SUM')

    cryptoMd5EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_md5", hashMenu)
    cryptoMd5EnabledSymbol.setLabel("Support MD5?")
    cryptoMd5EnabledSymbol.setDescription("Enable support for the MD5 Hash Algoithm.")
    cryptoMd5EnabledSymbol.setVisible(True)
    cryptoMd5EnabledSymbol.setDefaultValue(True)
    cryptoMd5EnabledSymbol.setHelp('CRYPT_MD5_SUM')

    cryptoHwMd5EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_md5_hw", cryptoMd5EnabledSymbol)
    cryptoHwMd5EnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwMd5EnabledSymbol.setDescription("Turn on support for using the hardware acceleration for the MD5 Hash Algorithm")
    if (cryptoHwMd5Supported == True):
        cryptoHwMd5EnabledSymbol.setDependencies(handleHwMd5Enabled, ["wolfcrypt_hw", "wolfcrypt_md5"])
    cryptoHwMd5EnabledSymbol.setVisible(False)
    cryptoHwMd5EnabledSymbol.setDefaultValue(False)
    cryptoHwMd5EnabledSymbol.setHelp('CRYPT_MD5_SUM')


    cryptoSha1EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha1", hashMenu)
    cryptoSha1EnabledSymbol.setLabel("Support SHA1?")
    cryptoSha1EnabledSymbol.setDescription("Enable support for the SHA-1 Hash Algorithm.")
    cryptoSha1EnabledSymbol.setVisible(True)
    cryptoSha1EnabledSymbol.setDefaultValue(True)
    cryptoSha1EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoHwSha1EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha1_hw", cryptoSha1EnabledSymbol)
    cryptoHwSha1EnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwSha1EnabledSymbol.setDescription("Turn on support for using the hardware acceleration for the SHA-1 Hash Algorithm")
    if (cryptoHwSha1Supported == True):
        cryptoHwSha1EnabledSymbol.setDependencies(handleHwSha1Enabled, ["wolfcrypt_hw", "wolfcrypt_sha1"])
    cryptoHwSha1EnabledSymbol.setVisible(False)
    cryptoHwSha1EnabledSymbol.setDefaultValue(False)
    cryptoHwSha1EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    sha264HashMenu = wolfCryptComponent.createMenuSymbol("wolcrypt_sha2_64_hash", hashMenu)
    sha264HashMenu.setLabel("SHA-2 224/256 Hash Algorithm.")
    sha264HashMenu.setVisible(True)

    cryptoHwSha256EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha264_hw", sha264HashMenu)
    cryptoHwSha256EnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwSha256EnabledSymbol.setDescription("Turn on support for using the hardware acceleration for the SHA-1 Hash Algorithm")
    if ((cryptoHwSha224Supported == True) or (cryptoHwSha256Supported == True)):
        cryptoHwSha256EnabledSymbol.setDependencies(handleHwSha264Enabled, ["wolfcrypt_hw"])
    cryptoHwSha256EnabledSymbol.setVisible(False)
    cryptoHwSha256EnabledSymbol.setDefaultValue(False)
    cryptoHwSha256EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoSha256EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha256", sha264HashMenu)
    cryptoSha256EnabledSymbol.setLabel("Support SHA-2 256?")
    cryptoSha256EnabledSymbol.setDescription("Enable support for the SHA-2 256 Hash Algoithm.")
    cryptoSha256EnabledSymbol.setVisible(True)
    cryptoSha256EnabledSymbol.setDefaultValue(True)
    if ((cryptoHwSha224Supported == True) and (cryptoHwSha256Supported == False)):
        cryptoSha256EnabledSymbol.setDependencies(handleSha256Enabled, ["wolfcrypt_hw", "wolfcrypt_sha264_hw"])
    cryptoSha256EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoSha224EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha224", cryptoSha256EnabledSymbol)
    cryptoSha224EnabledSymbol.setLabel("Support SHA-2 224?")
    cryptoSha224EnabledSymbol.setDescription("Enable support for the SHA-2 224 Hash Algoithm.")
    cryptoSha224EnabledSymbol.setVisible(False)
    cryptoSha224EnabledSymbol.setDefaultValue(True)
    cryptoSha224EnabledSymbol.setDependencies(handleSha224Enabled, ["wolfcrypt_hw", "wolfcrypt_sha256", "wolfcrypt_sha264_hw"])
    cryptoSha224EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    sha2128HashMenu = wolfCryptComponent.createMenuSymbol("wolcrypt_sha2_128_hash", hashMenu)
    sha2128HashMenu.setLabel("SHA-2 384/512 Hash Algorithm.")
    sha2128HashMenu.setVisible(True)
    sha2128HashMenu.setHelp('CRYPT_SHA_SUM')

    cryptoHwSha384EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha2128_hw", sha2128HashMenu)
    cryptoHwSha384EnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwSha384EnabledSymbol.setDescription("Turn on support for using the hardware acceleration for the SHA-1 Hash Algorithm")
    if ((cryptoHwSha384Supported == True) or (cryptoHwSha512Supported == True)):
        cryptoHwSha384EnabledSymbol.setDependencies(handleHwSha2128Enabled, ["wolfcrypt_hw"])
    cryptoHwSha384EnabledSymbol.setVisible(False)
    cryptoHwSha384EnabledSymbol.setDefaultValue(False)
    cryptoHwSha384EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoSha384EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha384", sha2128HashMenu)
    cryptoSha384EnabledSymbol.setLabel("Support SHA-2 384?")
    cryptoSha384EnabledSymbol.setDescription("Enable support for the SHA-2 384 Hash Algoithm.")
    cryptoSha384EnabledSymbol.setVisible(True)
    cryptoSha384EnabledSymbol.setDefaultValue(False)
    cryptoSha384EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoSha512EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_sha512", sha2128HashMenu)
    cryptoSha512EnabledSymbol.setLabel("Support SHA-2 512?")
    cryptoSha512EnabledSymbol.setDescription("Enable support for the SHA-2 512 Hash Algoithm.")
    cryptoSha512EnabledSymbol.setVisible(True)
    cryptoSha512EnabledSymbol.setDefaultValue(False)
    cryptoSha512EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoSha3EnabledSymbol = wolfCryptComponent.createComboSymbol("wolfcrypt_sha3", hashMenu, ["disabled", "small", "enabled"])
    cryptoSha3EnabledSymbol.setLabel("Support SHA-3?")
    cryptoSha3EnabledSymbol.setDescription("Enable support for the SHA-3 Hash Algoithm.")
    cryptoSha3EnabledSymbol.setVisible(True)
    cryptoSha3EnabledSymbol.setDefaultValue("disabled")
    cryptoSha3EnabledSymbol.setHelp('CRYPT_SHA_SUM')

    cryptoBlake2bEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_blake2b", hashMenu)
    cryptoBlake2bEnabledSymbol.setLabel("Support Blake 2B?")
    cryptoBlake2bEnabledSymbol.setDescription("Enable support for the Blake 2B Hash Algoithm.")
    cryptoBlake2bEnabledSymbol.setVisible(True)
    cryptoBlake2bEnabledSymbol.setDefaultValue(False)
    cryptoBlake2bEnabledSymbol.setHelp('CRYPT_BLAKE2B_SUM')

    cryptoRipemdEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_ripemd", hashMenu)
    cryptoRipemdEnabledSymbol.setLabel("Support RIPEMD-160?")
    cryptoRipemdEnabledSymbol.setDescription("Enable wolfSSL RIPEMD-160 support")
    cryptoRipemdEnabledSymbol.setVisible(True)
    cryptoRipemdEnabledSymbol.setDefaultValue(False)
    cryptoRipemdEnabledSymbol.setHelp('CRYPT_RIPEND_SUM')

    cryptoHmacEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_hmac", hashMenu)
    cryptoHmacEnabledSymbol.setLabel("Support HMAC?")
    cryptoHmacEnabledSymbol.setDescription("Enable support for HMAC.")
    cryptoHmacEnabledSymbol.setVisible(False)
    cryptoHmacEnabledSymbol.setDefaultValue(True)
    cryptoHmacEnabledSymbol.setDependencies(handleHmacEnabled, ["wolfcrypt_md5", "wolfcrypt_sha1", "wolfcrypt_sha224", "wolfcrypt_sha256", "wolfcrypt_sha384", "wolfcrypt_sha512", "wolfcrypt_sha3", "wolfcrypt_blake2b"])
    cryptoHmacEnabledSymbol.setHelp('CRYPT_HMAC_SUM')

    cryptoHkdfEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_hkdf", cryptoHmacEnabledSymbol)
    cryptoHkdfEnabledSymbol.setLabel("Support HKDF?")
    cryptoHkdfEnabledSymbol.setDescription("Enable support for HKDF?")
    cryptoHkdfEnabledSymbol.setVisible(False)
    cryptoHkdfEnabledSymbol.setDefaultValue(False)
    cryptoHkdfEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_hmac"])
    cryptoHkdfEnabledSymbol.setHelp('CRYPT_HMAC_SUM')

    symmCipherMenu = wolfCryptComponent.createMenuSymbol("wolfcrypt_symmetrical_cipher", None)
    symmCipherMenu.setLabel("Symmetrical Ciphers")
    symmCipherMenu.setVisible(True)

    #DES
    cryptoDesEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_tdes", symmCipherMenu)
    cryptoDesEnabledSymbol.setLabel("Support T/DES?")
    cryptoDesEnabledSymbol.setDescription("Enable support for the DES and Triple DES Cipher.")
    cryptoDesEnabledSymbol.setVisible(True)
    cryptoDesEnabledSymbol.setDefaultValue(True)
    cryptoDesEnabledSymbol.setHelp('CRYPT_TDES_SUM')

    cryptoHwDesEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_tdes_hw", cryptoDesEnabledSymbol)
    cryptoHwDesEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwDesEnabledSymbol.setDescription("Enable the cryptography hardware for the TDES/DES algorithm.  With this option checked the driver will feed each block of data to the cryptography hardware at a time, unless hardware acceleration has been enabled for the specific TDES/DES mode below.")
    if (cryptoHwDesSupported == True):
        cryptoHwDesEnabledSymbol.setDependencies(handleHwDesEnabled, ["wolfcrypt_hw", "wolfcrypt_tdes"])
    cryptoHwDesEnabledSymbol.setVisible(False)
    cryptoHwDesEnabledSymbol.setDefaultValue(False)
    cryptoHwDesEnabledSymbol.setHelp('CRYPT_TDES_SUM')


    cryptoDesEcbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_tdes_ecb", cryptoDesEnabledSymbol)
    cryptoDesEcbEnabledSymbol.setLabel("Support ECB Mode?")
    cryptoDesEcbEnabledSymbol.setDescription("Enable ECB mode for the T/DES algorithm")
    cryptoDesEcbEnabledSymbol.setVisible(False)
    cryptoDesEcbEnabledSymbol.setDefaultValue(False)
    cryptoDesEcbEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_tdes"])
    cryptoDesEcbEnabledSymbol.setHelp('CRYPT_TDES_SUM')


    cryptoHwDesEcbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_tdes_ecb_hw", cryptoDesEcbEnabledSymbol)
    cryptoHwDesEcbEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwDesEcbEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in ECB mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwDesSupported == True):
        cryptoHwDesEcbEnabledSymbol.setDependencies(handleHwDesEcbEnabled, ["wolfcrypt_hw", "wolfcrypt_tdes_ecb", "wolfcrypt_tdes_hw"])
    cryptoHwDesEcbEnabledSymbol.setVisible(False)
    cryptoHwDesEcbEnabledSymbol.setDefaultValue(False)
    cryptoHwDesEcbEnabledSymbol.setHelp('CRYPT_TDES_SUM')


    cryptoDesCbcEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_tdes_cbc", cryptoDesEnabledSymbol)
    cryptoDesCbcEnabledSymbol.setLabel("Support CBC Mode?")
    cryptoDesCbcEnabledSymbol.setDescription("Enable support CBC Mode for the DES and Triple DES Cipher.")
    cryptoDesCbcEnabledSymbol.setVisible(False)
    cryptoDesCbcEnabledSymbol.setDefaultValue(True)
    cryptoDesCbcEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_tdes"])
    cryptoDesCbcEnabledSymbol.setReadOnly(True)
    cryptoDesCbcEnabledSymbol.setHelp('CRYPT_TDES_SUM')


    cryptoHwDesCbcEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_tdes_cbc_hw", cryptoDesCbcEnabledSymbol)
    cryptoHwDesCbcEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwDesCbcEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in CBC mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwDesSupported == True):
        cryptoHwDesCbcEnabledSymbol.setDependencies(handleHwDesCbcEnabled, ["wolfcrypt_hw", "wolfcrypt_tdes_cbc", "wolfcrypt_tdes_hw"])
    cryptoHwDesCbcEnabledSymbol.setVisible(False)
    cryptoHwDesCbcEnabledSymbol.setDefaultValue(False)
    cryptoHwDesCbcEnabledSymbol.setHelp('CRYPT_TDES_SUM')

    #AES
    cryptoAesEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes", symmCipherMenu)
    cryptoAesEnabledSymbol.setLabel("Support AES?")
    cryptoAesEnabledSymbol.setDescription("Enable support for AES Cipher.")
    cryptoAesEnabledSymbol.setVisible(True)
    cryptoAesEnabledSymbol.setDefaultValue(True)
    cryptoAesEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoHwAesEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_hw", cryptoAesEnabledSymbol)
    cryptoHwAesEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesEnabledSymbol.setDescription("Enable the cryptography hardware for the AESS algorithm.  With this option checked the driver will feed each block of data to the cryptography hardware at a time, unless hardware acceleration has been enabled for the specific AES mode below.")
    cryptoHwAesEnabledSymbol.setVisible(False)
    cryptoHwAesEnabledSymbol.setDefaultValue(False)
    cryptoHwAesEnabledSymbol.setDependencies(handleAesHwEnableChange, ["wolfcrypt_aes", "wolfcrypt_hw"])
    cryptoHwAesEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoAesSmallTableEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_small_table", cryptoAesEnabledSymbol)
    cryptoAesSmallTableEnabledSymbol.setLabel("Enable Small AES Tables")
    cryptoAesSmallTableEnabledSymbol.setDescription("Enable Support for small AES Tables.")
    cryptoAesSmallTableEnabledSymbol.setVisible(True)
    cryptoAesSmallTableEnabledSymbol.setDefaultValue(True)
    cryptoAesSmallTableEnabledSymbol.setDependencies(handleAesSmallTableChange, ["wolfcrypt_aes", "wolfcrypt_aes_hw", "wolfcrypt_hw"])
    cryptoAesSmallTableEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoAes128EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_128", cryptoAesEnabledSymbol)
    cryptoAes128EnabledSymbol.setLabel("Support 128-bit AES?")
    cryptoAes128EnabledSymbol.setDescription("Enable Support for 128-Bit AES Cryptography.")
    cryptoAes128EnabledSymbol.setVisible(True)
    cryptoAes128EnabledSymbol.setDefaultValue(True)
    cryptoAes128EnabledSymbol.setDependencies(handleAes128BitSymbolChange, ["wolfcrypt_aes", "wolfcrypt_aes_hw", "wolfcrypt_hw"])
    cryptoAes128EnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoAes192EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_192", cryptoAesEnabledSymbol)
    cryptoAes192EnabledSymbol.setLabel("Support 192-bit AES?")
    cryptoAes192EnabledSymbol.setDescription("Enable Support for 192-Bit AES Cryptography.")
    cryptoAes192EnabledSymbol.setVisible(True)
    cryptoAes192EnabledSymbol.setDefaultValue(True)
    cryptoAes192EnabledSymbol.setDependencies(handleAes192BitSymbolChange, ["wolfcrypt_aes", "wolfcrypt_aes_hw", "wolfcrypt_hw"])
    cryptoAes192EnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAes192Symbol = wolfCryptComponent.createBooleanSymbol("crypto_HwAes192", None)
    cryptoHwAes192Symbol.setLabel("HW AES 192 available")
    cryptoHwAes192Symbol.setDescription("HW AES 192 available")
    cryptoHwAes192Symbol.setVisible(False) # never display this symbol; see also cryptoHwAes192Supported
    cryptoHwAes192Symbol.setDefaultValue(False)
    cryptoHwAes192Symbol.setHelp('CRYPT_AES_SUM')

    cryptoAes256EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_256", cryptoAesEnabledSymbol)
    cryptoAes256EnabledSymbol.setLabel("Support 256-bit AES?")
    cryptoAes256EnabledSymbol.setDescription("Enable Support for 256-Bit AES Cryptography.")
    cryptoAes256EnabledSymbol.setVisible(True)
    cryptoAes256EnabledSymbol.setDefaultValue(True)
    cryptoAes256EnabledSymbol.setDependencies(handleAes256BitSymbolChange, ["wolfcrypt_aes", "wolfcrypt_aes_hw", "wolfcrypt_hw"])
    cryptoAes256EnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoAesEcbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ecb", cryptoAesEnabledSymbol)
    cryptoAesEcbEnabledSymbol.setLabel("Support ECB Mode?")
    cryptoAesEcbEnabledSymbol.setDescription("Enable support ECB Mode for the AES Cipher.")
    cryptoAesEcbEnabledSymbol.setVisible(True)
    cryptoAesEcbEnabledSymbol.setDefaultValue(True)
    cryptoAesEcbEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesEcbEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAesEcbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ecb_hw", cryptoAesEcbEnabledSymbol)
    cryptoHwAesEcbEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesEcbEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in ECB mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if ((cryptoHwAes128Supported == True) or
        (cryptoHwAes192Supported == True) or
        (cryptoHwAes256Supported == True)):
        cryptoHwAesEcbEnabledSymbol.setDependencies(handleHwAesEcbEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_ecb", "wolfcrypt_aes_hw"])
    cryptoHwAesEcbEnabledSymbol.setVisible(False)
    cryptoHwAesEcbEnabledSymbol.setDefaultValue(False)
    cryptoHwAesEcbEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoAesCbcEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_cbc", cryptoAesEnabledSymbol)
    cryptoAesCbcEnabledSymbol.setLabel("Support CBC Mode?")
    cryptoAesCbcEnabledSymbol.setDescription("Enable support ECB Mode for the CBC Cipher.")
    cryptoAesCbcEnabledSymbol.setVisible(True)
    cryptoAesCbcEnabledSymbol.setDefaultValue(True)
    cryptoAesCbcEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesCbcEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAesCbcEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_cbc_hw", cryptoAesCbcEnabledSymbol)
    cryptoHwAesCbcEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesCbcEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in CBC mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesCbcSupported == True):
        cryptoHwAesCbcEnabledSymbol.setDependencies(handleHwAesCbcEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_cbc", "wolfcrypt_aes_hw"])
    cryptoHwAesCbcEnabledSymbol.setVisible(False)
    cryptoHwAesCbcEnabledSymbol.setDefaultValue(False)
    cryptoHwAesCbcEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoAesCtrEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ctr", cryptoAesEnabledSymbol)
    cryptoAesCtrEnabledSymbol.setLabel("Support Counter Mode?")
    cryptoAesCtrEnabledSymbol.setDescription("Enable support Counter Mode for the AES Cipher.")
    cryptoAesCtrEnabledSymbol.setVisible(True)
    cryptoAesCtrEnabledSymbol.setDefaultValue(True)
    cryptoAesCtrEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])

    cryptoHwAesCtrEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ctr_hw", cryptoAesCtrEnabledSymbol)
    cryptoHwAesCtrEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesCtrEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in CTR mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesCtrSupported == True):
        cryptoHwAesCtrEnabledSymbol.setDependencies(handleHwAesCtrEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_ctr", "wolfcrypt_aes_hw"])
    cryptoHwAesCtrEnabledSymbol.setVisible(False)
    cryptoHwAesCtrEnabledSymbol.setDefaultValue(False)
    cryptoHwAesCbcEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoAesCfbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_cfb", cryptoAesEnabledSymbol)
    cryptoAesCfbEnabledSymbol.setLabel("Support CFB Mode?")
    cryptoAesCfbEnabledSymbol.setDescription("Enable support CFB Mode for the AES Cipher.")
    cryptoAesCfbEnabledSymbol.setVisible(True)
    cryptoAesCfbEnabledSymbol.setDefaultValue(False)
    cryptoAesCfbEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])

    cryptoHwAesCfbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_cfb_hw", cryptoAesCfbEnabledSymbol)
    cryptoHwAesCfbEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesCfbEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in CFB mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesCfbSupported == True):
        cryptoHwAesCfbEnabledSymbol.setDependencies(handleHwAesCfbEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_cfb", "wolfcrypt_aes_hw"])
    cryptoHwAesCfbEnabledSymbol.setVisible(False)
    cryptoHwAesCfbEnabledSymbol.setDefaultValue(False)
    cryptoHwAesCfbEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoAesGcmEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_gcm", cryptoAesEnabledSymbol)
    cryptoAesGcmEnabledSymbol.setLabel("Support GCM Mode?")
    cryptoAesGcmEnabledSymbol.setDescription("Enable support GCM Mode for the AES Cipher.")
    cryptoAesGcmEnabledSymbol.setVisible(True)
    cryptoAesGcmEnabledSymbol.setDefaultValue(True)
    cryptoAesGcmEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesGcmEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAesGcmEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_gcm_hw", cryptoAesGcmEnabledSymbol)
    cryptoHwAesGcmEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesGcmEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in GCM mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesGcmSupported == True):
        cryptoHwAesGcmEnabledSymbol.setDependencies(handleHwAesGcmEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_gcm", "wolfcrypt_aes_hw"])
    cryptoHwAesGcmEnabledSymbol.setVisible(False)
    cryptoHwAesGcmEnabledSymbol.setDefaultValue(False)
    cryptoHwAesGcmEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoAesOfbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ofb", cryptoAesEnabledSymbol)
    cryptoAesOfbEnabledSymbol.setLabel("Support OFB Mode?")
    cryptoAesOfbEnabledSymbol.setDescription("Enable support OFB Mode for the AES Cipher.")
    cryptoAesOfbEnabledSymbol.setVisible(True)
    cryptoAesOfbEnabledSymbol.setDefaultValue(True)
    cryptoAesOfbEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesOfbEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAesOfbEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ofb_hw", cryptoAesGcmEnabledSymbol)
    cryptoHwAesOfbEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesOfbEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in OFB mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesOfbSupported == True):
        cryptoHwAesOfbEnabledSymbol.setDependencies(handleHwAesGcmEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_ofb", "wolfcrypt_aes_hw"])
    cryptoHwAesOfbEnabledSymbol.setVisible(False)
    cryptoHwAesOfbEnabledSymbol.setDefaultValue(False)
    cryptoHwAesOfbEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoAesXtsEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_xts", cryptoAesEnabledSymbol)
    cryptoAesXtsEnabledSymbol.setLabel("Support XTS Mode?")
    cryptoAesXtsEnabledSymbol.setDescription("Enable support XTS Mode for the AES Cipher.")
    cryptoAesXtsEnabledSymbol.setVisible(True)
    cryptoAesXtsEnabledSymbol.setDefaultValue(False)
    cryptoAesXtsEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesXtsEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAesXtsEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_xts_hw", cryptoAesXtsEnabledSymbol)
    cryptoHwAesXtsEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesXtsEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in XTS mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesXtsSupported == True):
        cryptoHwAesXtsEnabledSymbol.setDependencies(handleHwAesXtsEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_xts", "wolfcrypt_aes_hw"])
    cryptoHwAesXtsEnabledSymbol.setVisible(False)
    cryptoHwAesXtsEnabledSymbol.setDefaultValue(False)
    cryptoHwAesXtsEnabledSymbol.setHelp('CRYPT_AES_SUM')


    cryptoAesCcmEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ccm", cryptoAesEnabledSymbol)
    cryptoAesCcmEnabledSymbol.setLabel("Support CCM Mode?")
    cryptoAesCcmEnabledSymbol.setDescription("Enable support CCM Mode for the AES Cipher.")
    cryptoAesCcmEnabledSymbol.setVisible(True)
    cryptoAesCcmEnabledSymbol.setDefaultValue(True)
    cryptoAesCcmEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesCcmEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoHwAesCcmEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_ccm_hw", cryptoAesCcmEnabledSymbol)
    cryptoHwAesCcmEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwAesCcmEnabledSymbol.setDescription("Turn on support for using the hardware acceleration for multiple blocks of data in CCM mode.  Otherwise the driver will feed one block of data to the cryptography hardware at a time.")
    if (cryptoHwAesCcmSupported == True):
        cryptoHwAesCcmEnabledSymbol.setDependencies(handleHwAesCcmEnabled, ["wolfcrypt_hw", "wolfcrypt_aes_ccm", "wolfcrypt_aes_hw"])
    cryptoHwAesCcmEnabledSymbol.setVisible(False)
    cryptoHwAesCcmEnabledSymbol.setDefaultValue(False)
    cryptoHwAesCcmEnabledSymbol.setHelp('CRYPT_AES_SUM')

    cryptoAesCmacEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_aes_cmac", cryptoAesEnabledSymbol)
    cryptoAesCmacEnabledSymbol.setLabel("Support CMAC?")
    cryptoAesCmacEnabledSymbol.setDescription("Enable support CMAC.")
    cryptoAesCmacEnabledSymbol.setVisible(True)
    cryptoAesCmacEnabledSymbol.setDefaultValue(False)
    cryptoAesCmacEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_aes"])
    cryptoAesCmacEnabledSymbol.setHelp('CRYPT_AES_SUM')

    camelliaEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_camellia", symmCipherMenu)
    camelliaEnableSymbol.setLabel("Camellia Support")
    camelliaEnableSymbol.setDescription("Enable wolfSSL Camellia support")
    camelliaEnableSymbol.setVisible(True)
    camelliaEnableSymbol.setDefaultValue(False)
    camelliaEnableSymbol.setHelp('CRYPT_CAMELLIA_SUM')

    cryptoIdeaEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_idea", symmCipherMenu)
    cryptoIdeaEnabledSymbol.setLabel("Support IDEA?")
    cryptoIdeaEnabledSymbol.setDescription("Enable support for IDEA Cipher.")
    cryptoIdeaEnabledSymbol.setVisible(True)
    cryptoIdeaEnabledSymbol.setDefaultValue(False)
    cryptoIdeaEnabledSymbol.setHelp('CRYPT_IDEA_SUM')

    cryptoArc4EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_arc4", symmCipherMenu)
    cryptoArc4EnabledSymbol.setLabel("Support ARC4?")
    cryptoArc4EnabledSymbol.setDescription("Enable support for ARC4 Cipher.")
    cryptoArc4EnabledSymbol.setVisible(True)
    cryptoArc4EnabledSymbol.setDefaultValue(False)
    cryptoArc4EnabledSymbol.setHelp('CRYPT_ARC4_SUM')

    cryptoHc128EnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_hc128", symmCipherMenu)
    cryptoHc128EnabledSymbol.setLabel("Support HC-128?")
    cryptoHc128EnabledSymbol.setDescription("Enable support for HC-128 Cipher.")
    cryptoHc128EnabledSymbol.setVisible(True)
    cryptoHc128EnabledSymbol.setDefaultValue(False)
    cryptoHc128EnabledSymbol.setHelp('CRYPT_HC128_SUM')

    cryptoRabbitEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_rabbit", symmCipherMenu)
    cryptoRabbitEnabledSymbol.setLabel("Support RABBIT?")
    cryptoRabbitEnabledSymbol.setDescription("Enable support for RABBIT Cipher.")
    cryptoRabbitEnabledSymbol.setVisible(True)
    cryptoRabbitEnabledSymbol.setDefaultValue(False)
    cryptoRabbitEnabledSymbol.setHelp('CRYPT_RABBIT_SUM')


    asymmCipherMenu = wolfCryptComponent.createMenuSymbol("wolfcrypt_asymmetrical_cipher", None)
    asymmCipherMenu.setLabel("Asymmetrical Ciphers")
    asymmCipherMenu.setVisible(True)

    cryptoEccEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_ecc", asymmCipherMenu)
    cryptoEccEnableSymbol.setLabel("ECC Support?")
    cryptoEccEnableSymbol.setDescription("Enable ECC Support.")
    cryptoEccEnableSymbol.setVisible(True)
    cryptoEccEnableSymbol.setDefaultValue(True)
    cryptoEccEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoHwEccEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_ecc_hw", cryptoEccEnableSymbol)
    cryptoHwEccEnabledSymbol.setLabel("Enable Hardware Support?")
    cryptoHwEccEnabledSymbol.setDescription("Enable Hardware Support for the ECC algorithm.")
    if (cryptoHwEccSupported == True):
        cryptoHwEccEnabledSymbol.setVisible(True)
    else:
        cryptoHwEccEnabledSymbol.setVisible(False)
    cryptoHwEccEnabledSymbol.setDefaultValue(False)
    cryptoHwEccEnabledSymbol.setHelp('CRYPT_ECC_SUM')

    
    

    cryptoKdfEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_kdf", cryptoEccEnableSymbol)
    cryptoKdfEnableSymbol.setLabel("KDF Support?")
    cryptoKdfEnableSymbol.setDescription("Enable KDF Support.")
    cryptoKdfEnableSymbol.setVisible(True)
    cryptoKdfEnableSymbol.setDefaultValue(False)
    cryptoKdfEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoShamirEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_shamir", cryptoEccEnableSymbol)
    cryptoShamirEnableSymbol.setLabel("Shamir Support?")
    cryptoShamirEnableSymbol.setDescription("Enable Shamir Support.")
    cryptoShamirEnableSymbol.setVisible(True)
    cryptoShamirEnableSymbol.setDefaultValue(False)
    cryptoShamirEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoCustomCurvesEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_customcurves", cryptoEccEnableSymbol)
    cryptoCustomCurvesEnableSymbol.setLabel("Custom Curve Support?")
    cryptoCustomCurvesEnableSymbol.setDescription("Enable Custom Curve Support.")
    cryptoCustomCurvesEnableSymbol.setVisible(True)
    cryptoCustomCurvesEnableSymbol.setDefaultValue(False)
    cryptoCustomCurvesEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoCurve25519EnableSymbol = wolfCryptComponent.createComboSymbol("wolfcrypt_curve25519", cryptoEccEnableSymbol, ["unsupported", "small", "no 128 bit", "supported"])
    cryptoCurve25519EnableSymbol.setLabel("Curve 25519 Support")
    cryptoCurve25519EnableSymbol.setDescription("Enable Curve 25519 Support.")
    cryptoCurve25519EnableSymbol.setVisible(True)
    cryptoCurve25519EnableSymbol.setDefaultValue("unsupported")
    cryptoCurve25519EnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoEd25519EnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_ed25519", cryptoCurve25519EnableSymbol)
    cryptoEd25519EnableSymbol.setLabel("Ed25519 Support?")
    cryptoEd25519EnableSymbol.setDescription("Enable Ed25519 Support.")
    cryptoEd25519EnableSymbol.setVisible(True)
    cryptoEd25519EnableSymbol.setDefaultValue(False)
    cryptoEd25519EnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoEccFpeccEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_fpecc", cryptoEccEnableSymbol)
    cryptoEccFpeccEnableSymbol.setLabel("Fixed Point Cache?")
    cryptoEccFpeccEnableSymbol.setDescription("Enable Fixed Point cache ECC")
    cryptoEccFpeccEnableSymbol.setVisible(True)
    cryptoEccFpeccEnableSymbol.setDefaultValue(False)
    cryptoEccFpeccEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoEccEncryptEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_eccencrypt", cryptoEccEnableSymbol)
    cryptoEccEncryptEnableSymbol.setLabel("Encrypt Support?")
    cryptoEccEncryptEnableSymbol.setDescription("Enable ECC Encrypt Support?")
    cryptoEccEncryptEnableSymbol.setVisible(True)
    cryptoEccEncryptEnableSymbol.setDefaultValue(False)
    cryptoEccEncryptEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoEccNoSignEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_eccnosign", cryptoEccEnableSymbol)
    cryptoEccNoSignEnableSymbol.setLabel("Disable ECC Sign")
    cryptoEccNoSignEnableSymbol.setDescription("Disable ECC Sign Support?")
    cryptoEccNoSignEnableSymbol.setVisible(True)
    cryptoEccNoSignEnableSymbol.setDefaultValue(False)
    cryptoEccNoSignEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoEccNoVerifyEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_eccnoverify", cryptoEccEnableSymbol)
    cryptoEccNoVerifyEnableSymbol.setLabel("Disable ECC Verify")
    cryptoEccNoVerifyEnableSymbol.setDescription("Disable ECC Verify Support?")
    cryptoEccNoVerifyEnableSymbol.setVisible(True)
    cryptoEccNoVerifyEnableSymbol.setDefaultValue(False)
    cryptoEccNoVerifyEnableSymbol.setHelp('CRYPT_ECC_SUM')

    cryptoDsaEnableSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_dsa", asymmCipherMenu)
    cryptoDsaEnableSymbol.setLabel("DSA Support?")
    cryptoDsaEnableSymbol.setDescription("Enable DSA Support.")
    cryptoDsaEnableSymbol.setVisible(True)
    cryptoDsaEnableSymbol.setDefaultValue(False)
    cryptoDsaEnableSymbol.setHelp('CRYPT_DSA_SUM')


    cryptoTrngEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_random", None)
    cryptoTrngEnabledSymbol.setLabel("Support Random Number Generation?")
    cryptoTrngEnabledSymbol.setDescription("Enables Random Number Generation Support.")
    cryptoTrngEnabledSymbol.setVisible(True)
    cryptoTrngEnabledSymbol.setDefaultValue(False)
    cryptoTrngEnabledSymbol.setReadOnly(True)
    cryptoTrngEnabledSymbol.setHelp('CRYPT_RNG_SUM')

    cryptoHashDrngEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_hashdrng", cryptoTrngEnabledSymbol)
    cryptoHashDrngEnabledSymbol.setLabel("Support Hash DRNG Generation?")
    cryptoHashDrngEnabledSymbol.setDescription("Enables Hash DRNG Support.")
    cryptoHashDrngEnabledSymbol.setVisible(False)
    cryptoHashDrngEnabledSymbol.setDefaultValue(True)
    cryptoHashDrngEnabledSymbol.setDependencies(handleHashDrngEnabled, ["wolfcrypt_random", "wolfcrypt_sha256"])
    cryptoHashDrngEnabledSymbol.setHelp('CRYPT_RNG_SUM')

    cryptoRandomTestEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_randomtest", cryptoTrngEnabledSymbol)
    cryptoRandomTestEnabledSymbol.setLabel("Support RNG Test?")
    cryptoRandomTestEnabledSymbol.setDescription("Enables RNG Test Support.")
    cryptoRandomTestEnabledSymbol.setVisible(False)
    cryptoRandomTestEnabledSymbol.setDefaultValue(True)
    cryptoRandomTestEnabledSymbol.setDependencies(handleParentSymbolChange, ["wolfcrypt_random"])
    cryptoRandomTestEnabledSymbol.setHelp('CRYPT_RNG_TEST_SUM')

    cryptoHwTrngEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_random_hw", cryptoTrngEnabledSymbol)
    cryptoHwTrngEnabledSymbol.setLabel("Support Hardware Acceleration?")
    cryptoHwTrngEnabledSymbol.setDescription("Turn on hardware acceleration support for the TRNG.")
    if (cryptoHwTrngSupported == True):
        cryptoHwTrngEnabledSymbol.setDependencies(handleHwTrngEnabled, ["wolfcrypt_hw", "wolfcrypt_random_hw"])
    cryptoHwTrngEnabledSymbol.setVisible(False)
    cryptoHwTrngEnabledSymbol.setDefaultValue(False)
    cryptoHwTrngEnabledSymbol.setHelp('CRYPT_RNG_SUM')

    asn1Support = wolfCryptComponent.createBooleanSymbol("wolfcrypt_asn1", None)
    asn1Support.setLabel("Support ASN.1?")
    asn1Support.setDescription("Enables ASN.1 Support.")
    asn1Support.setVisible(True)
    asn1Support.setDefaultValue(True)
    #asn1Support.setReadOnly(True)
    asn1Support.setHelp('CRYPT_RNG_SUM')

    base64Support = wolfCryptComponent.createBooleanSymbol("wolfcrypt_base64", None)
    base64Support.setLabel("Support Base64 Encoding?")
    base64Support.setDescription("Enables Base64 Encoding Support.")
    base64Support.setVisible(True)
    base64Support.setDefaultValue(False)
    base64Support.setHelp('CRYPT_RNG_SUM')

    #TODO:  Automatically set ASN.1 Support
    signatureSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_signature", None)
    signatureSupport.setLabel("Signature API? (requires ASN.1)")
    signatureSupport.setDescription("Enables the signature api.")
    signatureSupport.setVisible(True)
    signatureSupport.setDefaultValue(False)
    signatureSupport.setReadOnly(False)
    signatureSupport.setHelp('CRYPT_RNG_SUM')

    cryptoHaveZlib = wolfCryptComponent.createBooleanSymbol("wolfcrypt_havezlib", None)
    cryptoHaveZlib.setVisible(False)
    cryptoHaveZlib.setDefaultValue(False)
    cryptoHaveZlib.setHelp('CRYPT_HUFMANN_SUM')

    cryptoSupportCompression = wolfCryptComponent.createBooleanSymbol("wolfcrypt_supportcompression", None)
    cryptoSupportCompression.setLabel("Support Compression?")
    cryptoSupportCompression.setDescription("Add support for zLib compression")
    cryptoSupportCompression.setVisible(False)
    cryptoSupportCompression.setDefaultValue(False)
    cryptoSupportCompression.setHelp('CRYPT_HUFMANN_SUM')

    cryptoHaveSysTime = wolfCryptComponent.createBooleanSymbol("wolfcrypt_havesystime", None)
    cryptoHaveSysTime.setVisible(False)
    cryptoHaveSysTime.setDefaultValue(False)
    cryptoHaveSysTime.setHelp('CRYPT_SYSTEM_TIME_SUM')

    cryptoDependSysTime = wolfCryptComponent.createBooleanSymbol("wolfcrypt_dependsystime", None)
    cryptoDependSysTime.setLabel("Support Systime?")
    cryptoDependSysTime.setDescription("Add dependency on systime (required for ASN.1)")
    cryptoDependSysTime.setVisible(False)
    cryptoDependSysTime.setDefaultValue(False)
    cryptoDependSysTime.setHelp('CRYPT_SYSTEM_TIME_SUM')

    threadingSupport = wolfCryptComponent.createComboSymbol("wolfSslRTOSSupport", None, ["Single Threaded", "FreeRTOS",])
    threadingSupport.setLabel("Threading Support")
    threadingSupport.setDescription("wolfCrypt has native support for RTOSes.  This option selects the type of threading support to be used.")
    threadingSupport.setDefaultValue("Single Threaded")
    threadingSupport.setVisible(True)
    threadingSupport.setHelp('CRYPT_THREAD_SUPPORT_SUM')

    hardenSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_harden", None)
    hardenSupport.setLabel("Harden Build?")
    hardenSupport.setDescription("Enable Hardened build, Enables Timing Resistance and Blinding")
    hardenSupport.setDefaultValue(False)
    hardenSupport.setVisible(True)
    hardenSupport.setHelp('CRYPT_HARDEN_SUPPORT_SUM')

    keygenSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_keygen", None)
    keygenSupport.setLabel("Enable Key Generation?")
    keygenSupport.setDescription("Enable key generation")
    keygenSupport.setDefaultValue(False)
    keygenSupport.setVisible(True)
    keygenSupport.setHelp('CRYPT_KEYGEN_SUM')

    certgenSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_certgen", asn1Support)
    certgenSupport.setLabel("Enable Cert Generation?")
    certgenSupport.setDescription("Enable Cert generation")
    certgenSupport.setDefaultValue(False)
    certgenSupport.setVisible(False)
    certgenSupport.setDependencies(handleParentSymbolChange, ["wolfcrypt_asn1"])
    certgenSupport.setHelp('CRYPT_CERTGEN_SUM')

    certRequestGenSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_certrequestgen", certgenSupport)
    certRequestGenSupport.setLabel("Enable cert request generation?")
    certRequestGenSupport.setDescription("Enable cert request generation")
    certRequestGenSupport.setDefaultValue(False)
    certRequestGenSupport.setVisible(False)
    certRequestGenSupport.setDependencies(handleParentSymbolChange, ["wolfcrypt_certgen"])
    certRequestGenSupport.setHelp('CRYPT_CERTGEN_SUM')

    certRequestExtSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_certrequestext", certRequestGenSupport)
    certRequestExtSupport.setLabel("Enable cert request extensions?")
    certRequestExtSupport.setDescription("Enable cert request extensions")
    certRequestExtSupport.setDefaultValue(False)
    certRequestExtSupport.setVisible(False)
    certRequestExtSupport.setDependencies(handleParentSymbolChange, ["wolfcrypt_certrequestgen"])
    certRequestExtSupport.setHelp('CRYPT_CERTGEN_SUM')

    cryptoErrorStringSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_errorstrings", None)
    cryptoErrorStringSupport.setLabel("Include Error Strings?")
    cryptoErrorStringSupport.setDescription("Include Error Strings in compilation.")
    cryptoErrorStringSupport.setDefaultValue(False)
    cryptoErrorStringSupport.setVisible(True)
    cryptoErrorStringSupport.setHelp('CRYPT_WOLFCRYPT_ERROR_SUM')

    cryptoDebugSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_debug", None)
    cryptoDebugSupport.setLabel("Include Debug Logging?")
    cryptoDebugSupport.setDescription("Inlude debug strings and debug output support.")
    cryptoDebugSupport.setDefaultValue(False)
    cryptoDebugSupport.setVisible(True)
    cryptoDebugSupport.setHelp('CRYPT_WOLFCRYPT_DEBUG_SUM')

    cryptoMemoryCallbackSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_memorycallbacks", None)
    cryptoMemoryCallbackSupport.setLabel("Use Memory Callbacks?")
    cryptoMemoryCallbackSupport.setDescription("Enable memory callbacks")
    cryptoMemoryCallbackSupport.setDefaultValue(False)
    cryptoMemoryCallbackSupport.setVisible(True)
    cryptoMemoryCallbackSupport.setHelp('CRYPT_WOLFCRYPT_MEM_CALLBACK_SUM')

    cryptoMemoryTrackingSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_memorytracking", cryptoMemoryCallbackSupport)
    cryptoMemoryTrackingSupport.setLabel("Use Memory Tracking?")
    cryptoMemoryTrackingSupport.setDescription("Enable Memory Tracking Support.")
    cryptoMemoryTrackingSupport.setDefaultValue(False)
    cryptoMemoryTrackingSupport.setVisible(True)
    cryptoMemoryTrackingSupport.setHelp('CRYPT_WOLFCRYPT_MEM_TRACK_SUM')

    cryptoMemoryLoggingSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_memorylogging", cryptoMemoryCallbackSupport)
    cryptoMemoryLoggingSupport.setLabel("Use Memory Logging?")
    cryptoMemoryLoggingSupport.setDescription("Enable Memory Logging Support.")
    cryptoMemoryLoggingSupport.setDefaultValue(False)
    cryptoMemoryLoggingSupport.setVisible(True)
    cryptoMemoryLoggingSupport.setHelp('CRYPT_WOLFCRYPT_MEM_LOG_SUM')

    cryptoStackLoggingSupport = wolfCryptComponent.createBooleanSymbol("wolfcrypt_stacklogging", cryptoMemoryCallbackSupport)
    cryptoStackLoggingSupport.setLabel("Use Stack Logging?")
    cryptoStackLoggingSupport.setDescription("Enable Stack Logging Support.")
    cryptoStackLoggingSupport.setDefaultValue(False)
    cryptoStackLoggingSupport.setVisible(True)
    cryptoStackLoggingSupport.setHelp('CRYPT_WOLFCRYPT_STACK_LOG_SUM')

    cryptoRsaEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_rsa", asymmCipherMenu)
    cryptoRsaEnabledSymbol.setLabel("Support RSA?")
    cryptoRsaEnabledSymbol.setDescription("Enable RSA Support.")
    cryptoRsaEnabledSymbol.setDefaultValue(True)
    cryptoRsaEnabledSymbol.setVisible(True)
    cryptoRsaEnabledSymbol.setHelp('CRYPT_RSA_SUM')

    cryptoHwRsaEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_rsa_hw", cryptoRsaEnabledSymbol)
    cryptoHwRsaEnabledSymbol.setLabel("Enable Hardware Support?")
    cryptoHwRsaEnabledSymbol.setDescription("Enable Hardware Support for the RSA algorithm.")
    if (cryptoHwRsaSupported == True):
        cryptoHwRsaEnabledSymbol.setVisible(True)
    else:
        cryptoHwRsaEnabledSymbol.setVisible(False)
    cryptoHwRsaEnabledSymbol.setDefaultValue(False)
    cryptoHwRsaEnabledSymbol.setHelp('CRYPT_RSA_SUM')

    cryptoOaepEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_oaep", cryptoRsaEnabledSymbol)
    cryptoOaepEnabledSymbol.setLabel("Support OAEP?")
    cryptoOaepEnabledSymbol.setDescription("Enable RSA OAEP")
    cryptoOaepEnabledSymbol.setDefaultValue(True)
    cryptoOaepEnabledSymbol.setVisible(True)
    cryptoOaepEnabledSymbol.setHelp('CRYPT_RSA_SUM')

    cryptoRsaPubOnlyEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_rsapub", cryptoRsaEnabledSymbol)
    cryptoRsaPubOnlyEnabledSymbol.setLabel("RSA Public Only?")
    cryptoRsaPubOnlyEnabledSymbol.setDescription("Enable RSA Public Only")
    cryptoRsaPubOnlyEnabledSymbol.setDefaultValue(False)
    cryptoRsaPubOnlyEnabledSymbol.setVisible(True)
    cryptoRsaPubOnlyEnabledSymbol.setHelp('CRYPT_RSA_SUM')

    cryptoRsaInlineEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_rsainline", cryptoRsaPubOnlyEnabledSymbol)
    cryptoRsaInlineEnabledSymbol.setLabel("Inline Only?")
    cryptoRsaInlineEnabledSymbol.setDescription("Enable RSA Verify Inline Only")
    cryptoRsaInlineEnabledSymbol.setDefaultValue(False)
    cryptoRsaInlineEnabledSymbol.setVisible(True)
    cryptoRsaInlineEnabledSymbol.setHelp('CRYPT_RSA_SUM')

    cryptoRsaStatic = wolfCryptComponent.createBooleanSymbol("cryptoRsaStatic", cryptoRsaEnabledSymbol)
    cryptoRsaStatic.setLabel("Static Suites")
    cryptoRsaStatic.setDescription("Enable RSA Static suites")
    cryptoRsaStatic.setDefaultValue(False)
    cryptoRsaStatic.setVisible(True)
    cryptoRsaStatic.setHelp('CRYPT_RSA_SUM')

    cryptoRsaPssEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_rsaPss", cryptoRsaEnabledSymbol)
    cryptoRsaPssEnabledSymbol.setLabel("Enable PSS?")
    cryptoRsaPssEnabledSymbol.setDescription("Enable RSA PSS Only")
    cryptoRsaPssEnabledSymbol.setDefaultValue(False)
    cryptoRsaPssEnabledSymbol.setVisible(True)
    cryptoRsaPssEnabledSymbol.setHelp('CRYPT_RSA_SUM')

    cryptoRsaKeySize = wolfCryptComponent.createComboSymbol("wolfcrypt_rsaKeySize", cryptoRsaEnabledSymbol, ["2048 bits", "4096 bits",])
    cryptoRsaKeySize.setLabel("Max Key Size")
    cryptoRsaKeySize.setDescription("Maximum RSA Key Size")
    cryptoRsaKeySize.setDefaultValue("2048 bits")
    cryptoRsaKeySize.setVisible(True)
    cryptoRsaKeySize.setHelp('CRYPT_RSA_SUM')

    cryptoFPMaxSize = wolfCryptComponent.createIntegerSymbol('wolfcrypt_certBuffMaxSize', cryptoRsaEnabledSymbol)
    cryptoFPMaxSize.setLabel('Cert Buffer Max Size')
    cryptoFPMaxSize.setVisible(False)
    cryptoFPMaxSize.setDefaultValue(4096)
    cryptoFPMaxSize.setDependencies(setValueFPMaxSizeRSAKeySize, ["wolfcrypt_rsaKeySize"])
    cryptoFPMaxSize.setHelp('CRYPT_RSA_SUM')

    cryptoDhEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_dh", asymmCipherMenu)
    cryptoDhEnabledSymbol.setLabel("Support Diffie-Hellman?")
    cryptoDhEnabledSymbol.setDescription("Enable DH")
    cryptoDhEnabledSymbol.setDefaultValue(False)
    cryptoDhEnabledSymbol.setVisible(True)
    cryptoDhEnabledSymbol.setHelp('CRYPT_DIFFIE_HELMAN_SUM')

    cryptoDhOldPrimeEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_dh_old_prime", cryptoDhEnabledSymbol)
    cryptoDhOldPrimeEnabledSymbol.setLabel("Support Old Prime Check?")
    cryptoDhOldPrimeEnabledSymbol.setDescription("Enable Old Prime Check")
    cryptoDhOldPrimeEnabledSymbol.setDefaultValue(False)
    cryptoDhOldPrimeEnabledSymbol.setVisible(True)
    cryptoDhOldPrimeEnabledSymbol.setHelp('CRYPT_DIFFIE_HELMAN_SUM')

    cryptoDhAnonEnabledSymbol = wolfCryptComponent.createBooleanSymbol("wolfcrypt_dh_anon", cryptoDhEnabledSymbol)
    cryptoDhAnonEnabledSymbol.setLabel("Support Anonymous?")
    cryptoDhAnonEnabledSymbol.setDescription("Enable Anonymous")
    cryptoDhAnonEnabledSymbol.setDefaultValue(False)
    cryptoDhAnonEnabledSymbol.setVisible(True)
    cryptoDhAnonEnabledSymbol.setHelp('CRYPT_DIFFIE_HELMAN_SUM')

    cryptoHW_U2803Symbol = wolfCryptComponent.createBooleanSymbol("cryptoCrya_U2803", None)
    cryptoHW_U2803Symbol.setVisible(False) # never reveal this symbol
    cryptoHW_U2803Symbol.setDefaultValue(False)
    cryptoHW_U2803Symbol.setValue(cryptoHW_U2803Present)
    cryptoHW_U2805Symbol = wolfCryptComponent.createBooleanSymbol("cryptoCrya_U2805", None)
    cryptoHW_U2805Symbol.setVisible(False) # never reveal this symbol
    cryptoHW_U2805Symbol.setDefaultValue(False)
    cryptoHW_U2805Symbol.setValue(cryptoHW_U2805Present)
    cryptoHW_03710Symbol = wolfCryptComponent.createBooleanSymbol("cryptoCrya_03710", None)
    cryptoHW_03710Symbol.setVisible(False) # never reveal this symbol
    cryptoHW_03710Symbol.setDefaultValue(False)
    cryptoHW_03710Symbol.setValue(cryptoHW_03710Present)

    #--------------------------------------------------------------------------------------
    #Generate the config info and add it to list in configuration.h
    wolfCryptConfigInfo = wolfCryptComponent.createFileSymbol("wolfcryptConfigInfo", None)
    wolfCryptConfigInfo.setSourcePath("templates/wolf_crypt_config.h.ftl")
    wolfCryptConfigInfo.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    wolfCryptConfigInfo.setMarkup(True)
    wolfCryptConfigInfo.setType("STRING")

    includeFilename = wolfCryptComponent.createFileSymbol("wolfcrypt_config_h", None)
    includeFilename.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME"))
    includeFilename.setSourcePath("config/config.h")
    includeFilename.setDestPath("")
    includeFilename.setOutputName("config.h")
    includeFilename.setType("HEADER")

    wolfcryptConfigH = wolfCryptComponent.createSettingSymbol("wolfsslConfigH", None)
    wolfcryptConfigH.setCategory("C32")
    wolfcryptConfigH.setKey("preprocessor-macros")
    wolfcryptConfigH.setValue("HAVE_CONFIG_H")
    wolfcryptConfigH.setAppend(True, ";")

    wolfcryptIgnoreFileWarn = wolfCryptComponent.createSettingSymbol("wolfsslIgnoreFileWarn", None)
    wolfcryptIgnoreFileWarn.setCategory("C32")
    wolfcryptIgnoreFileWarn.setKey("preprocessor-macros")
    wolfcryptIgnoreFileWarn.setValue("WOLFSSL_IGNORE_FILE_WARN")
    wolfcryptIgnoreFileWarn.setAppend(True, ";")


    series = ATDF.getNode("/avr-tools-device-file/devices/device").getAttribute("series")
    wolfcryptCoreSeries = wolfCryptComponent.createStringSymbol("wolfcryptCoreSeries", None)
    wolfcryptCoreSeries.setVisible(False)
    wolfcryptCoreSeries.setDefaultValue(series)

    wolfsslSrcPath = wolfCryptComponent.createSettingSymbol("wolfsslSrcPath", None)
    wolfsslSrcPath.setValue("../src/third_party/wolfssl")
    wolfsslSrcPath.setCategory("C32")
    wolfsslSrcPath.setKey("extra-include-directories")
    wolfsslSrcPath.setAppend(True, ";")

    wolfsslWolfcryptPath = wolfCryptComponent.createSettingSymbol("wolfsslWolfCryptPath", None)
    wolfsslWolfcryptPath.setValue("../src/third_party/wolfssl/wolfssl")
    wolfsslWolfcryptPath.setCategory("C32")
    wolfsslWolfcryptPath.setKey("extra-include-directories")
    wolfsslWolfcryptPath.setAppend(True, ";")

    wolfsslSysInitSourceFtl = wolfCryptComponent.createFileSymbol(None, None)
    wolfsslSysInitSourceFtl.setType("STRING")
    wolfsslSysInitSourceFtl.setOutputName("core.LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE")
    wolfsslSysInitSourceFtl.setSourcePath("templates/system_initialize.c.ftl")
    wolfsslSysInitSourceFtl.setMarkup(True)

    wolfsslSystemDefFtl = wolfCryptComponent.createFileSymbol(None, None)
    wolfsslSystemDefFtl.setType("STRING")
    wolfsslSystemDefFtl.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    wolfsslSystemDefFtl.setSourcePath("templates/system_definitions.h.ftl")
    wolfsslSystemDefFtl.setMarkup(True)



def handleParentSymbolChange(symbol, event):
    symbol.setVisible(event["value"])

def setValueFPMaxSizeRSAKeySize(symbol, event):
    rsaKeySize = symbol.getComponent().getSymbolByID("wolfcrypt_certBuffMaxSize").getValue()
    if rsaKeySize == "2048 bits":
        symbol.setValue(4096)
    elif rsaKeySize == "4096 bits":
        symbol.setValue(8192)

def handleHwDesEnabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoHwDesSupported
    global cryptoHwDesEnabledSymbol
    global cryptoDesEnabledSymbol

    if ((cryptoHwDesSupported == True) and (cryptoHwEnabledSymbol.getValue() == True)
        and (cryptoDesEnabledSymbol.getValue() == True)):
        cryptoHwDesEnabledSymbol.setVisible(True)
    else:
        cryptoHwDesEnabledSymbol.setVisible(False)

def handleHwDesEcbEnabled(symbol, event):
    global cryptoHwDesSupported
    global cryptoHwEnabledSymbol
    global cryptoHwDesEnabledSymbol
    global cryptoDesEcbEnabledSymbol
    global cryptoHwDesEcbEnabledSymbol

    if ((cryptoHwDesSupported == True) and (cryptoHwDesEnabledSymbol.getValue() == True)
        and (cryptoDesEcbEnabledSymbol.getValue() == True) and (cryptoHwEnabledSymbol.getValue() == True)):
        cryptoHwDesEcbEnabledSymbol.setVisible(True)
    else:
        cryptoHwDesEcbEnabledSymbol.setVisible(False)

def handleHwDesCbcEnabled(symbol, event):
    global cryptoHwDesCbcSupported
    global cryptoHwEnabledSymbol
    global cryptoHwDesEnabledSymbol
    global cryptoDesCbcEnabledSymbol
    global cryptoHwDesCbcEnabledSymbol

    if ((cryptoHwDesCbcSupported == True) and (cryptoHwDesEnabledSymbol.getValue() == True)
        and (cryptoDesCbcEnabledSymbol.getValue() == True) and (cryptoHwEnabledSymbol.getValue() == True)):
        cryptoHwDesCbcEnabledSymbol.setVisible(True)
    else:
        cryptoHwDesCbcEnabledSymbol.setVisible(False)


def handleAesHwEnableChange(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoAesEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoHwAes128Supported
    global cryptoHwAes192Supported
    global cryptoHwAes256Supported

    if ((cryptoHwEnabledSymbol.getValue() == True) and (cryptoAesEnabledSymbol.getValue() == True) and
        ((cryptoHwAes128Supported == True) or (cryptoHwAes192Supported == True) or
         (cryptoHwAes256Supported == True))):
        cryptoHwAesEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesEnabledSymbol.setVisible(False)

def handleAesSmallTableChange(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoAesEnabledSymbol
    global cryptoAesSmallTableEnabledSymbol
    global cryptoHwAes128Supported
    global cryptoHwAes192Supported
    global cryptoHwAes256Supported

    if (cryptoAesEnabledSymbol.getValue() == True and
        ((cryptoHwAes128Supported == True) or (cryptoHwAes192Supported == True) or
         (cryptoHwAes256Supported == True))):
        cryptoAesSmallTableEnabledSymbol.setVisible(True)
    else:
        cryptoAesSmallTableEnabledSymbol.setVisible(False)

def handleAes128BitSymbolChange(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoAesEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoHwAes128Supported
    global cryptoAes128EnabledSymbol

    # Because cryptoAes128EnabledSymbol cannot be programmatically cleared
    # any time after the user has clicked it, these tests must be duplicated
    # in the .ftl in order to properly mask the aes128/192/256 enables.
    if (cryptoAesEnabledSymbol.getValue() == True):             # wolfcrypt_aes
        if (cryptoHwEnabledSymbol.getValue() == True):          # wolfcrypt_hw
            if (cryptoHwAesEnabledSymbol.getValue() == True):   # wolfcrypt_aes_hw
                if (cryptoHwAes128Supported == True):
                    willBeVisible = True
                else:
                    willBeVisible = False
            else:
                willBeVisible = True
        else:
            willBeVisible = True
    else:
        willBeVisible = False

    cryptoAes128EnabledSymbol.setVisible(willBeVisible)


def handleAes192BitSymbolChange(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoAesEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoHwAes192Supported
    global cryptoAes192EnabledSymbol

    if (cryptoAesEnabledSymbol.getValue() == True):
        if (cryptoHwEnabledSymbol.getValue() == True):
            if (cryptoHwAesEnabledSymbol.getValue() == True):
                if (cryptoHwAes192Supported == True):
                    willBeVisible = True
                else:
                    willBeVisible = False
            else:
                willBeVisible = True
        else:
            willBeVisible = True
    else:
        willBeVisible = False

    cryptoAes192EnabledSymbol.setVisible(willBeVisible)


def handleAes256BitSymbolChange(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoAesEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoHwAes256Supported
    global cryptoAes256EnabledSymbol

    if (cryptoAesEnabledSymbol.getValue() == True):
        if (cryptoHwEnabledSymbol.getValue() == True):
            if (cryptoHwAesEnabledSymbol.getValue() == True):
                if (cryptoHwAes256Supported == True):
                    willBeVisible = True
                else:
                    willBeVisible = False
            else:
                willBeVisible = True
        else:
            willBeVisible = True
    else:
        willBeVisible = False

    cryptoAes256EnabledSymbol.setVisible(willBeVisible)


def handleHwAesEcbEnabled(symbol, event):
    global cryptoHwAes128Supported
    global cryptoHwAes192Supported
    global cryptoHwAes256Supported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesEcbEnabledSymbol
    global cryptoHwAesEcbEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesEcbEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        ((cryptoHwAes128Supported == True) or
         (cryptoHwAes192Supported == True) or
         (cryptoHwAes256Supported == True))):
        cryptoHwAesEcbEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesEcbEnabledSymbol.setVisible(False)

def handleHwAesCbcEnabled(symbol, event):
    global cryptoHwAesCbcSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesCbcEnabledSymbol
    global cryptoHwAesCbcEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesCbcEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesCbcSupported == True)):
        cryptoHwAesCbcEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesCbcEnabledSymbol.setVisible(False)

def handleHwAesCtrEnabled(symbol, event):
    global cryptoHwAesCtrSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesCtrEnabledSymbol
    global cryptoHwAesCtrEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesCtrEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesCtrSupported == True)):
        cryptoHwAesCtrEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesCtrEnabledSymbol.setVisible(False)

def handleHwAesCfbEnabled(symbol, event):
    global cryptoHwAesCfbSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesCfbEnabledSymbol
    global cryptoHwAesCfbEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesCfbEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesCfbSupported == True)):
        cryptoHwAesCfbEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesCfbEnabledSymbol.setVisible(False)

def handleHwAesOfbEnabled(symbol, event):
    global cryptoHwAesCbcSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesOfbEnabledSymbol
    global cryptoHwAesOfbEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesOfbEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesOfbSupported == True)):
        cryptoHwAesOfbEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesOfbEnabledSymbol.setVisible(False)

def handleHwAesXtsEnabled(symbol, event):
    global cryptoHwAesXtsSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesXtsEnabledSymbol
    global cryptoHwAesXtsEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesXtsEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesXtsSupported == True)):
        cryptoHwAesXtsEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesXtsEnabledSymbol.setVisible(False)

def handleHwAesGcmEnabled(symbol, event):
    global cryptoHwAesGcmSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesGcmEnabledSymbol
    global cryptoHwAesGcmEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesGcmEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesGcmSupported == True)):
        cryptoHwAesGcmEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesGcmEnabledSymbol.setVisible(False)

def handleHwAesCcmEnabled(symbol, event):
    global cryptoHwAesCcmSupported
    global cryptoHwEnabledSymbol
    global cryptoHwAesEnabledSymbol
    global cryptoAesCcmEnabledSymbol
    global cryptoHwAesCcmEnabledSymbol

    if ((cryptoHwAesEnabledSymbol.getValue() == True) and
        (cryptoAesCcmEnabledSymbol.getValue() == True) and
        (cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwAesCcmSupported == True)):
        cryptoHwAesCcmEnabledSymbol.setVisible(True)
    else:
        cryptoHwAesCcmEnabledSymbol.setVisible(False)

def handleHwMd5Enabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoMd5EnabledSymbol
    global cryptoHwMd5EnabledSymbol
    if ((cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoMd5EnabledSymbol.getValue() == True)):
        cryptoHwMd5EnabledSymbol.setVisible(True)
    else:
        cryptoHwMd5EnabledSymbol.setVisible(False)

def handleHwSha1Enabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoSha1EnabledSymbol
    global cryptoHwSha1EnabledSymbol
    if ((cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoSha1EnabledSymbol.getValue() == True)):
        cryptoHwSha1EnabledSymbol.setVisible(True)
    else:
        cryptoHwSha1EnabledSymbol.setVisible(False)

def handleHwSha264Enabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoHwSha256EnabledSymbol
    cryptoHwSha256EnabledSymbol.setVisible(cryptoHwEnabledSymbol.getValue())

def handleSha224Enabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoHwSha256EnabledSymbol
    global cryptoSha256EnabledSymbol
    global cryptoSha224EnabledSymbol
    global cryptoHwSha224Supported

    if (cryptoSha256EnabledSymbol.getValue() == True):
        if ((cryptoHwEnabledSymbol.getValue() == True) and
            (cryptoHwSha256EnabledSymbol.getValue() == True) and
            (not(cryptoHwSha224Supported))):
            cryptoSha224EnabledSymbol.setVisible(False)
        else:
            cryptoSha224EnabledSymbol.setVisible(True)
    else:
        cryptoSha224EnabledSymbol.setVisible(False)

def handleSha256Enabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoHwSha224EnabledSymbol
    global cryptoSha256EnabledSymbol
    if ((cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoHwSha224EnabledSymbol.getValue() == True)):
        cryptoSha256EnabledSymbol.setVisible(False)
    else:
        cryptoSha256EnabledSymbol.setVisible(True)

def handleHwSha2128Enabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoHwSha384EnabledSymbol
    cryptoHwSha384EnabledSymbol.setVisible(cryptoHwEnabledSymbol.getValue())

def handleHwTrngEnabled(symbol, event):
    global cryptoHwEnabledSymbol
    global cryptoTrngEnabledSymbol
    global cryptoHwTrngEnabledSymbol
    if ((cryptoHwEnabledSymbol.getValue() == True) and
        (cryptoTrngEnabledSymbol.getValue() == True)):
        cryptoHwTrngEnabledSymbol.setVisible(True)
    else:
        cryptoHwTrngEnabledSymbol.setVisible(False)

def handleHashDrngEnabled(symbol, event):
    global cryptoSha256EnabledSymbol
    global cryptoTrngEnabledSymbol
    global cryptoHashDrngEnabledSymbol
    if ((cryptoSha256EnabledSymbol.getValue() == True) and
        (cryptoTrngEnabledSymbol.getValue() == True)):
        cryptoHashDrngEnabledSymbol.setVisible(True)
    else:
        cryptoHashDrngEnabledSymbol.setVisible(False)

def handleHmacEnabled(symbol, event):
    global cryptoMd5EnabledSymbol
    global cryptoSha1EnabledSymbol
    global cryptoSha224EnabledSymbol
    global cryptoSha256EnabledSymbol
    global cryptoSha384EnabledSymbol
    global cryptoSha512EnabledSymbol
    global cryptoSha3EnabledSymbol
    global cryptoBlake2bEnabledSymbol
    global cryptoHmacEnabledSymbol

    if ((cryptoMd5EnabledSymbol.getValue() == True) or
        (cryptoSha1EnabledSymbol.getValue() == True) or
        (cryptoSha224EnabledSymbol.getValue() == True) or
        (cryptoSha256EnabledSymbol.getValue() == True) or
        (cryptoSha384EnabledSymbol.getValue() == True) or
        (cryptoSha512EnabledSymbol.getValue() == True) or
        (cryptoSha3EnabledSymbol.getValue() == True) or
        (cryptoBlake2bEnabledSymbol.getValue() == True)):
        cryptoHmacEnabledSymbol.setVisible(True)
    else:
        cryptoHmacEnabledSymbol.setVisible(False)

def scanHardware(list):
    global cryptoHwAdditionalDefines
    periphNode = ATDF.getNode("/avr-tools-device-file/devices/device/peripherals")
    modules = periphNode.getChildren()
    for module in modules:
        for item in list:
            if (module.getAttribute("name") == item[0]
                    and module.getAttribute("id") == item[1]
                    and module.getAttribute("version") == item[2]):
                #print(item[4])
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(item[4])
                #print(cryptoHwAdditionalDefines)
                return True
    return False

def setupHardware() :
    global cryptoHwSupported
    global cryptoHwTrngSupport
    global cryptoHwTrngSupported
    global cryptoHwMd5Support
    global cryptoHwMd5Supported
    global cryptoHwSha1Support
    global cryptoHwSha1Supported
    global cryptoHwSha224Support
    global cryptoHwSha224Supported
    global cryptoHwSha256Support
    global cryptoHwSha256Supported
    global cryptoHwSha384Support
    global cryptoHwSha384Supported
    global cryptoHwSha512Support
    global cryptoHwSha512Supported
    global cryptoHwAes128Support
    global cryptoHwAes128Supported
    global cryptoHwAes192Support
    global cryptoHwAes192Supported
    global cryptoHwAes256Support
    global cryptoHwAes256Supported
    global cryptoHwAesCbcSupport
    global cryptoHwAesCbcSupported
    global cryptoHwAesCtrSupport
    global cryptoHwAesCtrSupported
    global cryptoHwAesCfbSupport
    global cryptoHwAesCfbSupported
    global cryptoHwAesOfbSupport
    global cryptoHwAesOfbSupported
    global cryptoHwAesXtsSupport
    global cryptoHwAesXtsSupported
    global cryptoHwAesGcmSupport
    global cryptoHwAesGcmSupported
    global cryptoHwAesCcmSupport
    global cryptoHwAesCcmSupported
    global cryptoHwDesSupport
    global cryptoHwDesSupported
    global cryptoHwDesCbcSupport
    global cryptoHwDesCbcSupported
    global cryptoHwDesCfbSupport
    global cryptoHwDesCfbSupported
    global cryptoHwDesOfbSupport
    global cryptoHwDesOfbSupported
    global cryptoHwRsaSupport
    global cryptoHwRsaSupported
    global cryptoHwEccSupport
    global cryptoHwEccSupported
    global cryptoHW_U2803
    global cryptoHW_U2803Present
    global cryptoHW_U2805
    global cryptoHW_U2805Present
    global cryptoHW_03710
    global cryptoHW_03710Present
    global cryptoAdditionalHwDefines
    global cryptoHwAdditionalDefines

    cryptoHwTrngSupported = scanHardware(cryptoHwTrngSupport)
    cryptoHwMd5Supported = scanHardware(cryptoHwMd5Support)
    cryptoHwSha1Supported = scanHardware(cryptoHwSha1Support)
    cryptoHwSha224Supported = scanHardware(cryptoHwSha224Support)
    cryptoHwSha256Supported = scanHardware(cryptoHwSha256Support)
    cryptoHwSha384Supported = scanHardware(cryptoHwSha384Support)
    cryptoHwSha512Supported = scanHardware(cryptoHwSha512Support)
    cryptoHwAes128Supported = scanHardware(cryptoHwAes128Support)
    cryptoHwAes192Supported = scanHardware(cryptoHwAes192Support)
    cryptoHwAes256Supported = scanHardware(cryptoHwAes256Support)
    cryptoHwAesCbcSupported = scanHardware(cryptoHwAesCbcSupport)
    cryptoHwAesCtrSupported = scanHardware(cryptoHwAesCtrSupport)
    cryptoHwAesCfbSupported = scanHardware(cryptoHwAesCfbSupport)
    cryptoHwAesOfbSupported = scanHardware(cryptoHwAesOfbSupport)
    cryptoHwAesXtsSupported = scanHardware(cryptoHwAesXtsSupport)
    cryptoHwAesGcmSupported = scanHardware(cryptoHwAesGcmSupport)
    cryptoHwAesCcmSupported = scanHardware(cryptoHwAesCcmSupport)
    cryptoHwDesSupported = scanHardware(cryptoHwDesSupport)
    cryptoHwDesCbcSupported = scanHardware(cryptoHwDesCbcSupport)
    cryptoHwDesCfbSupported = scanHardware(cryptoHwDesCfbSupport)
    cryptoHwDesOfbSupported = scanHardware(cryptoHwDesOfbSupport)
    cryptoHwRsaSupported = scanHardware(cryptoHwRsaSupport)
    cryptoHwEccSupported = scanHardware(cryptoHwEccSupport)
    cryptoHW_U2803Present = scanHardware(cryptoHW_U2803)
    cryptoHW_U2805Present = scanHardware(cryptoHW_U2805)
    cryptoHW_03710Present = scanHardware(cryptoHW_03710)

    if (cryptoHwTrngSupported or cryptoHwMd5Supported or
        cryptoHwSha1Supported or
        cryptoHwSha224Supported or cryptoHwSha256Supported or
        cryptoHwSha384Supported or cryptoHwSha512Supported or
        cryptoHwAes128Supported or cryptoHwAes128Supported or
        cryptoHwAes192Supported or cryptoHwAes256Supported or
        cryptoHwDesSupported or cryptoHwRsaSupported or
        cryptoHwEccSupported):
        cryptoHwSupported = True
    else:
        cryptoHwSupported = False

    cryptoAdditionalHwDefines.setDefaultValue(", ".join(cryptoHwAdditionalDefines))
    #print(cryptoAdditionalHwDefines.getValue())


def get_script_dir(follow_symlinks=True):
    if getattr(sys, 'frozen', False): # py2exe, PyInstaller, cx_Freeze
        path = os.path.abspath(sys.executable)
    else:
        path = inspect.getabsfile(get_script_dir)
    if follow_symlinks:
        path = os.path.realpath(path)
    return os.path.dirname(path)

def trimFileNameList(rawList) :
    newList = []
    for file in rawList:
        filename = ntpath.basename(file)
        newList.append(filename)
    return newList

def addFileName(fileName, prefix, component, srcPath, destPath, enabled, projectPath):
    filename = component.createFileSymbol(prefix + fileName.replace('.', '_'), None)
    filename.setProjectPath(projectPath)
    filename.setSourcePath(srcPath + fileName)
    filename.setOutputName(fileName)

    if prefix == 'misc' or prefix == 'imp':
        filename.setDestPath(destPath)
        filename.setType("IMPORTANT")
    elif fileName[-2:] == '.h':
        filename.setDestPath(destPath)
        filename.setType("HEADER")
    else:
        filename.setDestPath(destPath)
        filename.setType("SOURCE")

    filename.setEnabled(enabled)


def setupFiles(basecomponent) :
    global cryptoOverridableSrcFiles
    global cryptoOverridableHeaderFiles
    wolfCryptSourceFiles = get_script_dir() + "/../../wolfssl/wolfcrypt/src/*.c"
    wolfCryptHeaderFiles = get_script_dir() + "/../../wolfssl/wolfssl/wolfcrypt/*.h"
    wolfCryptPortSourceFiles = get_script_dir() + "/../../wolfssl/wolfcrypt/src/port/pic32/*.c"
    wolfCryptPortHeaderFiles = get_script_dir() + "/../../wolfssl/wolfssl/wolfcrypt/port/pic32/*.h"
    harmonyCryptPortSourceFiles = get_script_dir() + "/../src/port/mplabharmony3/*.c"
    harmonyCryptPortHeaderFiles = get_script_dir() + "/../src/port/mplabharmony3/*.h"

    wcsfrl = glob.glob(wolfCryptSourceFiles)
    wcsfl = []
    for file in wcsfrl:
        filename = ntpath.basename(file)
        if ((not (filename in cryptoOverridableSrcFiles)) and (filename != "misc.c") and (filename != "evp.c")):
            wcsfl.append(filename)

    wchfl = []
    for file in glob.glob(wolfCryptHeaderFiles):
        filename = ntpath.basename(file)
        if ((not (filename in cryptoOverridableHeaderFiles))):
            wchfl.append(filename)

    wcpsfl = trimFileNameList(glob.glob(wolfCryptPortSourceFiles))
    wcphfl = trimFileNameList(glob.glob(wolfCryptPortHeaderFiles))
    hcpsfl = trimFileNameList(glob.glob(harmonyCryptPortSourceFiles))
    hcphfl = trimFileNameList(glob.glob(harmonyCryptPortHeaderFiles))

    for file in wcsfl:
        addFileName(file, "wolfcrypt", basecomponent, "../wolfssl/wolfcrypt/src/", "../../third_party/wolfssl/wolfssl/wolfcrypt/src/", True, "wolfcrypt")

    for file in wchfl:
        addFileName(file, "wolfcrypt", basecomponent, "../wolfssl/wolfssl/wolfcrypt/", "../../third_party/wolfssl/wolfssl/wolfcrypt/", True, "wolfcrypt")

    for file in wcpsfl:
        addFileName(file, "wolfcryptport", basecomponent, "../wolfssl/wolfcrypt/src/port/pic32/", "../../third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/", True, "wolfcrypt/port")

    for file in wcphfl:
        addFileName(file, "wolfcryptport", basecomponent, "../wolfssl/wolfssl/wolfcrypt/port/pic32/", "../../third_party/wolfssl/wolfssl/wolfcrypt/port/pic32/", True, "wolfcrypt/port")

    for file in hcpsfl:
        addFileName(file, "cryptoport", basecomponent, "src/port/mplabharmony3/", "../../third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/", True, "wolfcrypt/port")

    for file in hcphfl:
        addFileName(file, "cryptoport", basecomponent, "src/port/mplabharmony3/", "../../third_party/wolfssl/wolfssl/wolfcrypt/port/pic32/", True, "wolfcrypt/port")

    for file in cryptoOverridableSrcFiles:
        addFileName(file, "cryptooverride", basecomponent, "src/", "../../third_party/wolfssl/wolfssl/wolfcrypt/src/", True, "wolfcrypt")

    for file in cryptoOverridableHeaderFiles:
        addFileName(file, "cryptooverride", basecomponent, "src/", "../../third_party/wolfssl/wolfssl/wolfcrypt/", True, "wolfcrypt")


    addFileName("misc.c", "misc", basecomponent, "../wolfssl/wolfcrypt/src/", "../../third_party/wolfssl/wolfssl/wolfcrypt/src/", True, "wolfcrypt")
    addFileName("certs_test.h", "wolfcrypt", basecomponent, "../wolfssl/wolfssl/", "../../third_party/wolfssl/wolfssl/", True, "wolfcrypt")
    addFileName("evp.c", "misc", basecomponent, "../wolfssl/wolfcrypt/src/", "../../third_party/wolfssl/wolfssl/wolfcrypt/src/", True, "wolfcrypt")

def onAttachmentConnected(source, target):
    global cryptoWolfSSLIncluded
    global cryptoSupportCompression
    global cryptoHaveZlib
    global asn1Support
    global cryptoTrngEnabledSymbol
    if (target["component"].getID() == "lib_wolfssl"):
        cryptoWolfSSLIncluded.setValue(True)

    print("'" + target["component"].getID() + "'")

    if (target["component"].getID() == "lib_zlib"):
        cryptoHaveZlib.setValue(True)
        cryptoSupportCompression.setVisible(True)
    if ((target["component"].getID() == 'sys_time') or
        (source["component"].getID() == 'LIB_WOLFCRYPT_Dependency')):
        #asn1Support.setReadOnly(False)
        cryptoTrngEnabledSymbol.setReadOnly(False)
        cryptoTrngEnabledSymbol.setValue(True)

def onAttachmentDisconnected(source, target):
    global cryptoWolfSSLIncluded
    global cryptoSupportCompression
    global cryptoHaveZlib
    global asn1Support
    if (target["component"].getID() == "lib_wolfssl"):
        cryptoWolfSSLIncluded.setValue(False)

    print("'" + target["component"].getID() + "'")

    if (target["component"].getID() == "lib_zlib"):
        cryptoHaveZlib.setValue(False)
        cryptoSupportCompression.setVisible(False)
    if (target["component"].getID() == "sys_time"):
        asn1Support.setValue(False)
        #asn1Support.setReadOnly(True)
        cryptoTrngEnabledSymbol.setValue(False)
        cryptoTrngEnabledSymbol.setReadOnly(True)
