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

################################################################################
#GLOBAL Declarations
################################################################################
cryptoHwSupported          = False
cryptoHwEnabledSymbol      = None
cryptoHwSupportedSymbol    = None

localCryptoComponent       =  None
cryptoAdditionalHwDefines =  []
cryptoWolfSSLIncluded     =  False

cryptoSupportCompression  =  False
cryptoHaveZlib            =  False

cryptoHaveSysTime         =  False
cryptoDependSysTime       =  False

asn1Support               =  False

################################################################################
## Trustzone - for Unicorn/Omega/Lifeguard processors
################################################################################
trustZoneSupported        =  False  #Device supports trustZone
trustZoneEnabled          =  False  #Symbol
trustZoneDevices          = []      #TZ Device Name Patterns
trustZoneFileIds          = []      #List of file ids
cryptoTzEnabledSymbol     = None


################################################################################
## Crypto HW Drivers
################################################################################
 
#Function Used 
CONFIG_USE_TRNG           = None
CONFIG_USE_SHA            = None
CONFIG_USE_AES            = None
CONFIG_USE_TDES           = None
CONFIG_USE_RSA            = None  #TODO
CONFIG_USE_ECC            = None  #TODO

#HW Function Driver Used
CONFIG_USE_TRNG_HW        = None
CONFIG_USE_SHA_HW         = None
CONFIG_USE_AES_HW         = None
CONFIG_USE_TDES_HW        = None
CONFIG_USE_RSA_HW         = None  #TODO
CONFIG_USE_ECC_HW         = None  #TODO

trngHw = []
shaHw  = []
aesHw  = []
tdesHw = []
rsaHw  = []
eccHw  = []

#HW Driver FTL Symbol Strings
hwDriverStrings = []
hwDriverSymbol  = []
hwDriverFileSymbols = []

#HW Driver File Generation
hwDriverFileDict = {}

cryptoHwDefines           = None
cryptoHwAdditionalDefines = set([])
cryptoHwDevSupport        = set([])    #Holds the device hw supported keys (dKey)
cryptoHwIdSupport         = set([])    #Holds the device hw supported IDs (id)

#===============================================================================
#MENU
hashMenu     = None
sha2Menu     = None
sha3Menu     = None
blakeMenu    = None
blake2Menu   = None

symMenu      = None
aesMenu      = None
aesModesMenu = None
aesCfbMenu   = None

aeadMenu     = None
aeadAesMenu  = None

dsMenu       = None
kasMenu      = None
rngMenu      = None

#===============================================================================
#HASH Algorithms
CONFIG_USE_HASH                   = None
cryptoHwHashEnabledSymbol         = None

#-------------------------------------------------------------------------------
cryptoHwMd5Support    = []
cryptoMd5EnabledSymbol            = None
cryptoHwMd5Supported              = False
cryptoHwMd5EnabledSymbol          = None

#RIPEMD160----------------------------------------------------------------------
cryptoHwRipeMd160Support = []
cryptoRipeMd160EnabledSymbol      = None
cryptoHwRipeMd160Supported        = False
cryptoHwRipeMd160EnabledSymbol    = None

#-------------------------------------------------------------------------------
#SHA1
cryptoHwSha1Support   = []
cryptoSha1EnabledSymbol           = None
cryptoHwSha1Supported             = False
cryptoHwSha1EnabledSymbol         = None

#-------------------------------------------------------------------------------
#SHA2
cryptoHwSha224Support = []
cryptoSha224EnabledSymbol         = None
cryptoHwSha224Supported           = False
cryptoHwSha224EnabledSymbol       = None

cryptoHwSha256Support = []
cryptoHwSha256EnabledSymbol       = None
cryptoSha256EnabledSymbol         = None
cryptoHwSha256Supported           = False

cryptoHwSha384Support = []
cryptoHwSha384Supported           = False
cryptoHwSha384EnabledSymbol       = None
cryptoSha384EnabledSymbol         = None

cryptoHwSha512Support = []
cryptoHwSha512Supported           = False
cryptoHwSha512EnabledSymbol       = None
cryptoSha512EnabledSymbol         = None

cryptoHwSha512_224Support = []
cryptoHwSha512_224Supported           = False
cryptoHwSha512_224EnabledSymbol       = None
cryptoSha512_224EnabledSymbol         = None

cryptoHwSha512_256Support = []
cryptoHwSha512_256Supported           = False
cryptoHwSha512_256EnabledSymbol       = None
cryptoSha512_256EnabledSymbol         = None

#-------------------------------------------------------------------------------
#SHA3
cryptoHwSha3224Supported          = False
cryptoHwSha3224EnabledSymbol      = None
cryptoSha3224EnabledSymbol        = None

cryptoHwSha3256Supported          = False
cryptoHwSha3256EnabledSymbol      = None
cryptoSha3256EnabledSymbol        = None

cryptoHwSha3384Supported          = False
cryptoHwSha3384EnabledSymbol      = None
cryptoSha3384EnabledSymbol        = None

cryptoHwSha3512Supported          = False
cryptoHwSha3512EnabledSymbol      = None
cryptoSha3512EnabledSymbol        = None

#-------------------------------------------------------------------------------
#SHA3 - SHAKE
cryptoHwSha3Shake128Supported          = False
cryptoHwSha3Shake128EnabledSymbol      = None
cryptoSha3128Shake128EnabledSymbol     = None

cryptoHwSha3Shake256Supported          = False
cryptoHwSha3Shake256EnabledSymbol      = None
cryptoSha3Shake256EnabledSymbol        = None

#-------------------------------------------------------------------------------
#BLAKE
cryptoHwBlake224Supported         = False
cryptoHwBlake224EnabledSymbol     = None
cryptoBlake224EnabledSymbol       = None

cryptoHwBlake256Supported         = False
cryptoHwBlake256EnabledSymbol     = None
cryptoBlake256EnabledSymbol       = None

cryptoHwBlake384Supported         = False
cryptoHwBlake384EnabledSymbol     = None
cryptoBlake384EnabledSymbol       = None

cryptoHwBlake512Supported         = False
cryptoHwBlake512EnabledSymbol     = None
cryptoBlake512EnabledSymbol       = None

#-------------------------------------------------------------------------------
#BLAKE2
cryptoHwBlake2s224Supported        = False
cryptoHwBlake2s224EnabledSymbol    = None
cryptoBlake2s224EnabledSymbol      = None

cryptoHwBlake2s256Supported        = False
cryptoHwBlake2s256EnabledSymbol    = None
cryptoBlake2s256EnabledSymbol      = None

cryptoHwBlake2b384Supported        = False
cryptoHwBlake2b384EnabledSymbol    = None
cryptoBlake2b384EnabledSymbol      = None

cryptoHwBlake2b512Supported        = False
cryptoHwBlake2b512EnabledSymbol    = None
cryptoBlake2b512EnabledSymbol      = None

#===============================================================================
#Aead
CONFIG_USE_AEAD                   = None
cryptoHwAesSupport         = []
cryptoHwAeadAesSupported          = False
cryptoHwAeadAesEnabledSymbol      = None
cryptoAeadAesEnabledSymbol        = None

cryptoHwDesSupport         = []

cryptoHwAesGcmSupport      = []
cryptoHwAeadAesGcmSupported         = False
cryptoHwAeadAesGcmEnabledSymbol     = None
cryptoAeadAesGcmEnabledSymbol       = None

cryptoHwAesCcmSupport        = []
cryptoHwAeadAesCcmSupported         = False
cryptoHwAeadAesCcmEnabledSymbol     = None
cryptoAeadAesCcmEnabledSymbol       = None

cryptoHwEaxSupport    = []
cryptoHwAeadAesEaxSupported         = False
cryptoHwAeadAesEaxEnabledSymbol     = None
cryptoAeadAesEaxEnabledSymbol       = None

cryptoHwSymAesKwSupport       = []
cryptoHwSymAesKwSupported     = False
cryptoHwSymAesKwEnabledSymbol = None
cryptoSymAesKwEnabledSymbol   = None

cryptoHwAesSivCmacSupport    = []
cryptoHwAeadAesSivCmacSupported     = False
cryptoHwAeadAesSivCmacEnabledSymbol = None
cryptoAeadAesSivCmacEnabledSymbol   = None

cryptoHwAesSivGcmSupport     = []
cryptoHwAeadAesSivGcmSupported      = False
cryptoHwAeadAesSivGcmEnabledSymbol  = None
cryptoAeadAesSivGcmEnabledSymbol    = None

#===============================================================================
#HMAC
CONFIG_USE_MAC                     = None

#MAC-AES
cryptoHwMacAesSupported            = False
cryptoHwMacAesEnabledSymbol        = None
cryptoMacAesEnabledSymbol          = None

cryptoHwMacAesCmacSupported        = False
cryptoHwMacAesCmacEnabledSymbol    = None
cryptoMacAesCmacEnabledSymbol      = None

cryptoHwMacAesCbcMacSupported      = False
cryptoHwMacAesCbcMacEnabledSymbol  = None
cryptoMacAesCbcMacEnabledSymbol    = None

cryptoHwMacAesGmacSupported        = False
cryptoHwMacAesGmacEnabledSymbol    = None
cryptoMacAesGmacEnabledSymbol      = None

#===============================================================================
#SYMMETRIC
CONFIG_USE_SYM                     = None

#AES
cryptoHwAesSupported              = False
cryptoHwAesEnabledSymbol          = None
cryptoAesEnabledSymbol            = None

cryptoAes128EnabledSymbol         = None
cryptoAes192EnabledSymbol         = None
cryptoAes256EnabledSymbol         = None

cryptoAesSmallTableEnabledSymbol  = None

cryptoHwAesEcbSupported           = False
cryptoHwAesEcbEnabledSymbol       = None
cryptoAesEcbEnabledSymbol         = None


cryptoHwAesCbcSupported           = False
cryptoHwAesCbcEnabledSymbol       = None
cryptoAesCbcEnabledSymbol         = None

cryptoHwAesCtrSupported           = False
cryptoHwAesCtrEnabledSymbol       = None
cryptoAesCtrEnabledSymbol         = None

#AES-CFB Modes

#TODO: Not needed
cryptoHwAesCfbSupported           = False
cryptoHwAesCfbEnabledSymbol       = None
cryptoAesCfbEnabledSymbol         = None

cryptoHwAesCfb1Supported          = False
cryptoHwAesCfb1EnabledSymbol      = None
cryptoAesCfb1EnabledSymbol        = None

cryptoHwAesCfb8Supported          = False
cryptoHwAesCfb8EnabledSymbol      = None
cryptoAesCfb8EnabledSymbol        = None

cryptoHwAesCfb64Supported         = False
cryptoHwAesCfb64EnabledSymbol     = None
cryptoAesCfb64EnabledSymbol       = None

cryptoHwAesCfb128Supported        = False
cryptoHwAesCfb128EnabledSymbol    = None
cryptoAesCfb128EnabledSymbol      = None

cryptoHwAesOfbSupported           = False
cryptoHwAesOfbEnabledSymbol       = None
cryptoAesOfbEnabledSymbol         = None

cryptoHwAesGcmSupported           = False
cryptoHwAesGcmEnabledSymbol       = None
cryptoAesGcmEnabledSymbol         = None

cryptoHwAesXtsSupported           = False
cryptoHwAesXtsEnabledSymbol       = None
cryptoAesXtsEnabledSymbol         = None

#TODO: Not supported?
cryptoHwAesCcmSupported           = False
cryptoHwAesCcmEnabledSymbol       = None
cryptoAesCcmEnabledSymbol         = None


#===============================================================================
#ASYMMETRIC
CONFIG_USE_ASYM                   = None

#Asym DES
cryptoHwDesSupported              = False
cryptoHwDesEnabledSymbol          = None
cryptoDesEnabledSymbol            = None
cryptoDesEcbEnabledSymbol         = None
cryptoHwDesEcbEnabledSymbol       = None

cryptoHwDesCbcSupported           = False
cryptoHwDesCbcEnabledSymbol       = None
cryptoDesCbcEnabledSymbol         = None

cryptoHwDesCfbSupported           = False
cryptoHwDesCfbEnabledSymbol       = None
cryptoDesCfbEnabledSymbol         = None

cryptoHwDesOfbSupported           = False
cryptoHwDesOfbEnabledSymbol       = None
cryptoDesOfbEnabledSymbol         = None

#Asym RSA
cryptoHwAsymRsaSupported              = False
cryptoHwAsymRsaEnabledSymbol          = None
cryptoAsymRsaEnabledSymbol            = None

#Asym ECC
cryptoHwAsymEccSupported              = False
cryptoHwAsymEccEnabledSymbol          = None
cryptoAsymEccEnabledSymbol            = None

cryptoSWCallBackEnableSymbol      = None

#ASYM ECC-ECDSA 
cryptoHwEcdsaSupport = []
cryptoHwEcdsaSupported         = False
cryptoHwEcdsaEnabledSymbol     = None
cryptoEcdsaEnabledSymbol       = None


#===============================================================================
#DS - Digital Signing
CONFIG_USE_DS                     = None
cryptoDsEcdsaEnabledSymbol        = None

#===============================================================================
#KAS - Key Authorization
CONFIG_USE_KAS                    = None
cryptoKasEcdhEnableSymbol         = None
cryptoHwKasEcdhSupport    = []
cryptoHwKasEcdhSupported       = False
cryptoHwKasEcdhEnabledSymbol   = None

#===============================================================================
#TRNG
CONFIG_USE_TRNG                   = None
cryptoHwRngSupport         = []
cryptoRngTrngEnabledSymbol        = None
cryptoRngPrngEnabledSymbol        = None


#===============================================================================
#HW Modules
cryptoHW_U2803                    = []
cryptoHW_U2803Present             = False
cryptoHW_U2803Symbol              = None

cryptoHW_U2805                    = []
cryptoHW_U2805Present             = False
cryptoHW_U2805Symbol              = None

cryptoHW_03710                    = []
cryptoHW_03710Present             = False
cryptoHW_03710Symbol              = None

#Global variables. 

cryptoHwFilesDict        = {}
cryptoWolfCryptFilesDict = {}

cryptoHwFileComponentsDict                = {}
cryptoWolfCryptFileComponentsDict         = {}
cryptoHwMenuComponentsList                = []
cryptoWolfCryptEnabledMenuComponentsList  = []
cryptoWolfCryptDisabledMenuComponentsList = []

cryptoHwSupportFound      = False

cryptoSymAesModesSupported   = False
cryptoAesModesMenu        = None
