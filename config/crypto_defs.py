# coding: utf-8
#crypto_hw_defs.py

#===============================================================================
#HARDWARE part support ATDF scan information for each Crypto Function
#
# [<ATDF Module Name>, <ATDF Module #>, <Version>,
#  (<list of SYMBOLS used by FTL>)', <set cryptoHwAddtional Defines>)]
# 

#GLOBALS 
from crypto_globals import *

# SYMBOLS used by FTL are put in the cryptoHwAdditionalDefines
cryptoHwDefines           = None
cryptoHwAdditionalDefines = set([])


################################################################################
#CC API File Include Symbols
################################################################################
cryptoHwSupported         = False  
cryptoHwSupportedSymbol   = None   #HW supported 
cryptoHwEnabledSymbol     = None   #All HW Enabled

#Crypto Function Groups
CONFIG_USE_HASH           = None  #Any Hash 
CONFIG_USE_SYM            = None  #Any Symmetric Crypto
CONFIG_USE_AEAD           = None  #Any AEAD Crypto
CONFIG_USE_KAS            = None  #Any Key Auth Crypto
CONFIG_USE_DS             = None  #Any Dig. Signing Crypto
CONFIG_USE_MAC            = None  #Any MAC Crypto
CONFIG_USE_RNG            = None  #Any RNG method
CONFIG_USE_ASYM           = None  #TODO: RSA/ECC/DES

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

#HW Module Symbol Strings
hwDriverStrings = [
"HAVE_MCHP_CRYPTO_TRNG_HW_HSM",  #PIC32CZ CA90 
"HAVE_MCHP_CRYPTO_TRNG_HW_6334", #ATSAMV70Q20B/PIC32CX MT
"HAVE_MCHP_CRYPTO_TRNG_HW_U2242",#ATSAML11
"HAVE_MCHP_CRYPTO_TRNG_HW_03597",#PIC32CM Lx
"HAVE_MCHP_CRYPTO_SHA_HW_HSM",   #
"HAVE_MCHP_CRYPTO_SHA_HW_11105", #ATSAMV70Q20B
"HAVE_MCHP_CRYPTO_SHA_HW_U2010", #ATSAME54P20A
"HAVE_MCHP_CRYPTO_SHA_HW_6156",  #ATSAMA5D27
"HAVE_MCHP_CRYPTO_SHA_HW_U2803", #ATSAML11
"HAVE_MCHP_CRYPTO_SHA_HW_03710", #PIC32CM Lx
"HAVE_MCHP_CRYPTO_BLAKE_HW_HSM", #PIC32CZ CA90 
"HAVE_MCHP_CRYPTO_BLAKE2_HW_HSM",#PIC32CZ CA90 
"HAVE_MCHP_CRYPTO_AES_HW_HSM",   #PIC32CZ CA90 
"HAVE_MCHP_CRYPTO_AES_HW_6149",  #ATSAMV70Q20B
"HAVE_MCHP_CRYPTO_AES_HW_U2238", #ATSAME54P20A
"HAVE_MCHP_CRYPTO_TDES_HW_00158",#PIC32MZ EF
"HAVE_MCHP_CRYPTO_TDES_HW_6150", #ATSAMA5D27
"HAVE_MCHP_CRYPTO_RSA_HW_PUKCC", #ATSAME54P20A
"HAVE_MCHP_CRYPTO_RSA_HW_CPKCC", #PIC32CX MT
"HAVE_MCHP_CRYPTO_ECC_HW_BA414E",#PCI32MZ-W
"HAVE_MCHP_CRYPTO_ECC_HW_CPKCC", #PIC32CX MT
"HAVE_MCHP_CRYPTO_HW_BA414E",    #PCI32MZ-W
"HAVE_MCHP_CRYPTO_HW_U2803",     #ATSAML11
"HAVE_MCHP_CRYPTO_HW_U2805",     #PIC32CM
"HAVE_MCHP_CRYPTO_HW_03710"]

#HW Driver Enable Symbol
hwDriverSymbol = []
hwDriverFileSymbols = []

#HW Driver File Generation (TODO:  Only Mistral Drivers, for now)
#   { <dKey>: { <fKey>: [<driver files>] , ... ] }
hwDriverDict = {
                 "CPKCC": { "RSA":["drv_crypto_rsa_hw_cpkcc.h",
                                   "drv_crypto_rsa_hw_cpkcc.c"],
                            "ECC":["drv_crypto_ecc_hw_cpkcc.h",
                                   "drv_crypto_ecc_hw_cpkcc.c"] },
                  "6149": { "AES":["drv_crypto_aes_hw_6149.h",
                                   "drv_crypto_aes_hw_6149.c"] },
                  "6156": { "SHA":["drv_crypto_sha_hw_6156.h",
                                   "drv_crypto_sha_hw_6156.c"] },
                  "6334": {"TRNG":["drv_crypto_trng_hw_6334.h",
                                   "drv_crypto_trng_hw_6334.c"]} } 

#The dict list of file symbols loaded for each function
# {<function>: [<files symbols>], ...}
#--Key is same as the hwDriverDict fKey
hwDriverFileDict = {
        "TRNG": [],
         "SHA": [],
         "AES": [],
        "TDES": [],
         "RSA": [],
         "ECC": []}

#TODO:   Make all drivers available.  Only MISTRAL for now
hwDriverAvail = [ 
"HAVE_MCHP_CRYPTO_RSA_HW_CPKCC",  #PIC32CX MT
"HAVE_MCHP_CRYPTO_ECC_HW_CPKCC",  #PIC32CX MT
"HAVE_MCHP_CRYPTO_AES_HW_6149",
"HAVE_MCHP_CRYPTO_SHA_HW_6156"]



################################################################################
## Trustzone - for Unicorn/Omega/Lifeguard processors
################################################################################
trustZoneSupported        =  False
trustZoneEnabled          =  False

cryptoTzEnabledSymbol     = None

trustZoneDevices = [
    ['SAML11', 'L11'], #OMEGA
    ['PIC32CK', 'SG'], #UNICORN
    ['PIC32CM', 'LS']  #LIFEGUARD
]

trustZoneFiles = []

trngHw = [
"HAVE_MCHP_CRYPTO_TRNG_HW_HSM",   #PIC32CZ CA90 
"HAVE_MCHP_CRYPTO_TRNG_HW_6334",  #ATSAMV70Q20B
"HAVE_MCHP_CRYPTO_TRNG_HW_U2242", #ATSAML11
"HAVE_MCHP_CRYPTO_TRNG_HW_03597"] #PIC32CM'Lx ]

shaHw = [
"HAVE_MCHP_CRYPTO_SHA_HW_11105", #ATSAMV70Q20B
"HAVE_MCHP_CRYPTO_SHA_HW_U2010", #ATSAME54P20A
"HAVE_MCHP_CRYPTO_SHA_HW_6156",  #ATSAMA5D27
"HAVE_MCHP_CRYPTO_SHA_HW_U2803", #ATSAML11
"HAVE_MCHP_CRYPTO_SHA_HW_03710"]  #PIC32CM'Lx

aesHw = [
"HAVE_MCHP_CRYPTO_AES_HW_6149",  #ATSAMV70Q20B
"HAVE_MCHP_CRYPTO_AES_HW_U2238"] #ATSAME54P20A

tdesHw = [ "HAVE_MCHP_CRYPTO_TDES_HW_6150"] #ATSAMA5D27

rsaHw = [
"HAVE_MCHP_CRYPTO_RSA_HW_PUKCC", #ATSAME54P20A
"HAVE_MCHP_CRYPTO_RSA_HW_CPKCC"] #PIC32CX MT

eccHw = [
"HAVE_MCHP_CRYPTO_ECC_HW_BA414E", #PCI32MZ-W
"HAVE_MCHP_CRYPTO_ECC_HW_CPKCC"] #PIC32CX MT

################################################################################
## CRYPTO IMPLEMENTATIONS
################################################################################
#===============================================================================
#HW TRNG
# [ <module name>, <module #>, <module version>, [], [<list of project defines>]]
cryptoHwTrngSupport = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_HSM"])], #PIC32CZ CA90 
    ["RNG" ,"00159",      "", [],
       set([])],                                           #PIC32MZ EF
    ["TRNG", "6334",     "G", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_6334"])], #ATSAMV70Q20B
    ["TRNG","U2242", "1.2.0", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_U2242"])],#ATSAML11
    ["TRNG","U2242", "1.1.0", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_U2242"])],#ATSAME54P20A
    ["TRNG","U2242", "1.0.0", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_U2242"])],#ATSAML21J18B
    ["TRNG", "6334",     "K", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_6334"])], #ATSAMA5D27
    ["TRNG", "6334",     "O", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_6334"])], #ATSAM9X60
    ["TRNG","U2242",   "1d0", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_U2242"])],#PIC32CM'Lx
    ["TRNG","03597",   "1d0", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_03597"])],#PIC32CM'Lx
    ["TRNG", "6334",     "S", [],
       set(["HAVE_MCHP_CRYPTO_TRNG_HW_6334"])], #PIC32CX MT
]
cryptoHwTrngSupported       = False
cryptoHwTrngEnabledSymbol   = None
cryptoRngTrngEnabledSymbol     = None

cryptoHashDrngEnabledSymbol = None

#===============================================================================
# HASH IMPLEMENTATION
hashMenu = None

#----------------------------
#HW HASH MD5
cryptoHwMd5Support = [
    ["CRYPTO", "00158", "", [], set([]) ] #PIC32MZ EF 
]
cryptoHwMd5Supported     = False
cryptoHwMd5EnabledSymbol = None
cryptoMd5EnabledSymbol   = None

#----------------------------
#HW HASH RIPEMD160 
cryptoCurrentHwRipeMd160Support    = []

cryptoRipeMd160EnabledSymbol            = None
cryptoHwRipeMd160Supported              = False
cryptoHwRipeMd160EnabledSymbol          = None

#----------------------------
#HW HASH SHA1
cryptoHwSha1Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])], #PIC32CZ CA90 
    ["CRYPTO", "00158", "", [],
       set([])], #PIC32MZ EF
    ["ICM", "11105", "H", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20B
    ["ICM", "U2010", "1.2.0", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_11105",
            "HAVE_MCHP_CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
    ["SHA", "6156", "O", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
    ["SHA", "6156", "S", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])] #PI32CX MT/ATSAM9X60
]
cryptoHwSha1Supported     = False
cryptoHwSha1EnabledSymbol = None
cryptoSha1EnabledSymbol   = None

#----------------------------
#HW HASH SHA2
#HW HASH SHA224
sha2Menu = None

cryptoHwSha224Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])], #PIC32CZ CA90 
    ["ICM", "11105", "H", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
    ["ICM", "U2010", "1.2.0", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_11105",
          "HAVE_MCHP_CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
    ["SHA", "6156", "O", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])],  #ATSAMA5D27
    ["SHA", "6156", "S", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_6156",
          "HAVE_MCHP_CRYPTO_SHA_HW_6156"])],#PIC32CX MT/ATSAM9X60
    ["IDAU", "U2803", "1.0.0", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_U2803"])], #ATSAML11
    ["IDAU", "U2805", "1.0.0", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_U2805"])], #PIC32CM
    ["IDAU", "03710", "2a0", [],
     set(["HAVE_MCHP_CRYPTO_SHA_HW_03710"])] #PIC32CM'Lx
]
cryptoHwSha224Supported     = False
cryptoHwSha224EnabledSymbol = None
cryptoSha224EnabledSymbol   = None

#HW HASH SHA256
cryptoHwSha256Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])], #PIC32CZ CA90 
    ["CRYPTO", "00158", "", [],
        set([])],                                           #PIC32MZ EF
    ["ICM", "11105", "H", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
    ["ICM", "U2010", "1.2.0", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_11105",
             "HAVE_MCHP_CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
    ["SHA", "6156", "O", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])],  #ATSAMA5D27
    ["SHA", "6156", "S", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])],  #PIC32CX MT/ATSAM9X60
    ["IDAU", "U2803", "1.0.0", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_U2803"])], #ATSAML11
    ["IDAU", "U2805", "1.0.0", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_U2805"])], #PIC32CM
    ["IDAU", "03710", "2a0", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_03710"])] #PIC32CM'Lx
]
cryptoHwSha256Supported     = False
cryptoHwSha256EnabledSymbol = None
cryptoSha256EnabledSymbol   = None

sha3Menu = None

#HW HASH SHA384
cryptoHwSha384Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])], #PIC32CZ CA90 
    ["SHA", "6156", "O", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
    ["SHA", "6156", "S", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])] #PIC32CX MT/ATSAM9X60
]
cryptoHwSha384Supported     = False
cryptoHwSha384EnabledSymbol = None
cryptoSha384EnabledSymbol   = None

#HW HASH SHA512
cryptoHwSha512Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])], #PIC32CZ CA90 
    ["SHA", "6156", "O", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
    ["SHA", "6156", "S", [],
        set(["HAVE_MCHP_CRYPTO_SHA_HW_6156"])] #PIC32CX MT/ATSAM9X60
]
cryptoHwSha512Supported          = False
cryptoHwSha512EnabledSymbol      = None
cryptoSha512EnabledSymbol        = None

#----------------------------
#TODO:  Update SHA3 Support
#HW HASH SHA3-224
cryptoHwSha3224Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwSha3224Supported     = False
cryptoHwSha3224EnabledSymbol = None
cryptoSha3224EnabledSymbol   = None

#HW HASH SHA3-256
cryptoHwSha3256Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwSha3256Supported     = False
cryptoHwSha3256EnabledSymbol = None
cryptoSha3256EnabledSymbol   = None

#HW HASH SHA-384
cryptoHwSha3384Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwSha3384Supported     = False
cryptoHwSha3384EnabledSymbol = None
cryptoSha3384EnabledSymbol   = None

#HW HASH SHA-512
cryptoHwSha3512Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_SHA_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwSha3512Supported          = False
cryptoHwSha3512EnabledSymbol      = None
cryptoSha3512EnabledSymbol        = None

#-------------------------------------------------------------------------------
#SHA3 - SHAKE
cryptoHwSha3Shake128Support          = []

cryptoHwSha3Shake128Supported          = False
cryptoHwSha3Shake128EnabledSymbol      = None
cryptoSha3128ShakeEnabledSymbol        = None

cryptoHwSha3Shake128Support          = []

cryptoHwSha3Shake256Supported          = False
cryptoHwSha3Shake256EnabledSymbol      = None
cryptoSha3Shake256EnabledSymbol        = None

#===============================================================================

#-------------------------------------------------------------------------------
#HASH BLAKE Support
#TODO:  Update BLAKE Support
blakeMenu = None

#HW HASH BLAKE-224
cryptoHwBlake224Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake224Supported     = False
cryptoHwBlake224EnabledSymbol = None
cryptoBlake224EnabledSymbol   = None

#HW HASH BLAKE-256
cryptoHwBlake256Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake256Supported     = False
cryptoHwBlake256EnabledSymbol = None
cryptoBlake256EnabledSymbol   = None

#HW HASH BLAKE-384
cryptoHwBlake384Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake384Supported     = False
cryptoHwBlake384EnabledSymbol = None
cryptoBlake384EnabledSymbol   = None

#HW HASH BLAKE-512
cryptoHwBlake512Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake512Supported          = False
cryptoHwBlake512EnabledSymbol      = None
cryptoBlake512EnabledSymbol        = None

#-------------------------------------------------------------------------------
#HASH BLAKE2
blake2Menu = None

#HASH BLAKE2-224
cryptoHwBlake2s224Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE2_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake2s224Supported     = False
cryptoHwBlake2s224EnabledSymbol = None
cryptoBlake2s224EnabledSymbol   = None

#HW HASH BLAKE2-256
cryptoHwBlake2s256Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE2_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake2s256Supported     = False
cryptoHwBlake2s256EnabledSymbol = None
cryptoBlake2s256EnabledSymbol   = None

#HW HASH BLAKE2-384
cryptoHwBlake2b384Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE2_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake2b384Supported     = False
cryptoHwBlake2b384EnabledSymbol = None
cryptoBlake2b384EnabledSymbol   = None

#HW HASH BLAKE2-512
cryptoHwBlake2b512Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_BLAKE2_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwBlake2b512Supported          = False
cryptoHwBlake2b512EnabledSymbol      = None
cryptoBlake2b512EnabledSymbol        = None


#===============================================================================
#HmacSha2 = [
#    ["HSM" ,"03785",      "", [],
#      set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])] #PIC32CZ CA90 
#]

#===============================================================================


#===============================================================================
#HW SYM AES
cryptoAesEnabledSymbol           = None
cryptoHwAesEnabledSymbol         = None
cryptoHwAesSupported             = False

cryptoAesSmallTableEnabledSymbol = None

cryptoAesEcbEnabledSymbol        = None
cryptoAesEcbHwEnabledSymbol      = None

#SYM AES128
cryptoHwAes128Support = [
    ["HSM" ,"03785", "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])],       #PIC32CZ CA90 
    ["CRYPTO", "00158", "", [],
        set([])],                                   #PIC32MZ EF
    ["AES", "6149", "W", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAMV70Q20B
    ["AES", "U2238", "2.2.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
    ["AES", "U2238", "2.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
    ["AES", "U2238", "2.1.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
    ["AES", "6149", "ZB", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAMA5D28
    ["AES", "6149", "ZH", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAM9x60
    ["IDAU", "U2803", "1.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2803"])], #ATSAML11
    ["IDAU", "U2805", "1.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2805"])], #PIC32CM
    ["IDAU", "03710", "2a0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_03710"])], #PIC32CM'Lx
    ["AES", "6149", "ZN", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])]  #PIC32CX MT
]
cryptoHwAes128Supported   = False
cryptoAes128EnabledSymbol = None

#SYM AES192
cryptoHwAes192Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])],            # PIC32CZ CA90
    ["CRYPTO", "00158", "", [],
        set([])],                                           # PIC32MZ EF
    ["AES", "6149", "W", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  # ATSAMV70Q20B
    ["AES", "U2238", "2.2.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], # ATSAME54P20A
    ["AES", "U2238", "2.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], # ATSAML21J18B
    ["AES", "U2238", "2.1.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], # ATSAML22J18A
    ["AES", "6149", "ZB", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  # ATSAMA5D28
    ["AES", "6149", "ZH", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  # ATSAM9x60
    ["IDAU", "U2805", "1.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2805"])], # PIC32CM
    ["AES", "6149", "ZN", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])]  #PIC32CX MT
]
cryptoHwAes192Supported   = False
cryptoAes192EnabledSymbol = None

#SYM AES256
cryptoHwAes256Support = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])], #PIC32CZ CA90 
    ["CRYPTO", "00158", "", [],
        set([])], #PIC32MZ EF
    ["AES", "6149", "W", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
    ["AES", "U2238", "2.2.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
    ["AES", "U2238", "2.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
    ["AES", "U2238", "2.1.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
    ["AES", "6149", "ZB", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
    ["AES", "6149", "ZH", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])], #ATSAM9x60
    ["IDAU", "U2805", "1.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2805"])], #PIC32CM
    ["AES", "6149", "ZN", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])]  #PIC32CX MT
]
cryptoHwAes256Supported   = False
cryptoAes256EnabledSymbol = None

symMenu = None
aesMenu = None
aesModesMenu = None
aesCfbMenu = None
cryptoAesModesMenu        = None
cryptoAesModesSupported   = False

#SYM AES ECB Mode
cryptoHwAesEcbSupport       = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])] #PIC32CZ CA90 
]
cryptoHwAesEcbSupported     = False
cryptoHwAesEcbEnabledSymbol = None
cryptoAesEcbEnabledSymbol   = None

#SYM AES CBC Mode
cryptoHwAesCbcSupport = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])],    #PIC32CZ CA90 
    ["AES", "6149", "W", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAMV70Q20B
    ["AES", "U2238", "2.2.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
    ["AES", "U2238", "2.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
    ["AES", "U2238", "2.1.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
    ["AES", "6149", "ZB", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAMA5D28
    ["AES", "6149", "ZH", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAM9x60
    ["AES", "6149", "ZN", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])]   #PIC32CX MT
]
cryptoHwAesCbcSupported     = False
cryptoHwAesCbcEnabledSymbol = None
cryptoAesCbcEnabledSymbol   = None

#SYM AES OFB Mode
cryptoHwAesOfbSupport       = []
cryptoHwAesOfbSupported     = False
cryptoHwAesOfbEnabledSymbol = None
cryptoAesOfbEnabledSymbol   = None

#TODO:  Is this Needed?
#SYM AES CFB Mode
cryptoHwAesCfbSupport       = []
cryptoHwAesCfbSupported     = False
cryptoHwAesCfbEnabledSymbol = None
cryptoAesCfbEnabledSymbol   = None

#SYM AES CFB1 Mode
cryptoHwAesCfb1Support       = []
cryptoHwAesCfb1Supported     = False
cryptoHwAesCfb1EnabledSymbol = None
cryptoAesCfb1EnabledSymbol   = None

#SYM AES CFB8 Mode
cryptoHwAesCfb8Support       = []
cryptoHwAesCfb8Supported     = False
cryptoHwAesCfb8EnabledSymbol = None
cryptoAesCfb8EnabledSymbol   = None

#SYM AES CFB64 Mode
cryptoHwAesCfb64Support       = []
cryptoHwAesCfb64Supported     = False
cryptoHwAesCfb64EnabledSymbol = None
cryptoAesCfb64EnabledSymbol   = None

#SYM AES CFB128 Mode
cryptoHwAesCfb128Support       = []
cryptoHwAesCfb128Supported     = False
cryptoHwAesCfb128EnabledSymbol = None
cryptoAesCfb128EnabledSymbol   = None

#SYM AES CTR
cryptoHwAesCtrSupport = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])],    #PIC32CZ CA90 
    ["AES", "6149", "W", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAMV70Q20B
    ["AES", "U2238", "2.2.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
    ["AES", "U2238", "2.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
    ["AES", "U2238", "2.1.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
    ["AES", "6149", "ZB", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAMA5D28
    ["AES", "6149", "ZH", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])],  #ATSAM9x60
    ["AES", "6149", "ZN", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])]   #PIC32CX MT
]
cryptoHwAesCtrSupported     = False
cryptoHwAesCtrEnabledSymbol = None
cryptoAesCtrEnabledSymbol   = None

#SYM AES XTS
cryptoHwAesXtsSupport       = []
cryptoHwAesXtsSupported     = False
cryptoHwAesXtsEnabledSymbol = None
cryptoAesXtsEnabledSymbol   = None

#SYM AES EAX
cryptoHwAesEaxSupport       = []
cryptoHwAesEaxSupported     = False
cryptoHwAesEaxEnabledSymbol = None
cryptoAesEaxEnabledSymbol   = None

#SYM AES GCM
cryptoHwAesGcmSupport = [
    ["HSM" ,"03785",      "", [],
       set(["HAVE_MCHP_CRYPTO_AES_HW_HSM"])], #PIC32CZ CA90 
    ["AES", "6149", "W", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
    ["AES", "U2238", "2.2.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
    ["AES", "U2238", "2.0.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
    ["AES", "U2238", "2.1.0", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_U2238"])], #ATSAML22J18A
    ["AES", "6149", "ZB", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])], #ATSAMA5D28
    ["AES", "6149", "ZH", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])], #ATSAM9x60
    ["AES", "6149", "ZN", [],
        set(["HAVE_MCHP_CRYPTO_AES_HW_6149"])]  #PIC32CX MT
]
cryptoHwAesGcmSupported     = False
cryptoHwAesGcmEnabledSymbol = None
cryptoAesGcmEnabledSymbol   = None

#TODO: Supported at all?
#SYM AES CMC
cryptoHwAesCcmSupport       = []
cryptoHwAesCcmSupported     = False
cryptoHwAesCcmEnabledSymbol = None
cryptoAesCcmEnabledSymbol   = None

#SYM DES 
cryptoHwDesSupport = [
    ["CRYPTO", "00158", "", [],
        set(["HAVE_MCHP_CRYPTO_TDES_HW_00158"])], #PIC32MZ EF
    ["TDES", "6150", "N", [],
        set(["HAVE_MCHP_CRYPTO_TDES_HW_6150"])], #ATSAMA5D27
    ["TDES", "6150", "P", [],
        set(["HAVE_MCHP_CRYPTO_TDES_HW_6150"])], #ATSAM9X60
    ["TDES", "6150", "R", [],
        set(["HAVE_MCHP_CRYPTO_TDES_HW_6150"])], #ATSAM9X60
]
cryptoHwDesSupported        = False
cryptoHwDesEnabledSymbol    = None
cryptoDesEnabledSymbol      = None

#SYM DES ECB
cryptoDesEcbEnabledSymbol   = None
cryptoHwDesEcbEnabledSymbol = None

#SYM DES CBC
cryptoHwDesCbcSupport       = []
cryptoHwDesCbcSupported     = False
cryptoHwDesCbcEnabledSymbol = None
cryptoDesCbcEnabledSymbol   = None

#SYM DES CFB
cryptoHwDesCfbSupport       = []
cryptoHwDesCfbSupported     = False
cryptoHwDesCfbEnabledSymbol = None
cryptoDesCfbEnabledSymbol   = None

#SYM DES OFB
cryptoHwDesOfbSupport       = []
cryptoHwDesOfbSupported     = False
cryptoHwDesOfbEnabledSymbol = None
cryptoDesOfbEnabledSymbol   = None

#===============================================================================
#AEAD
aeadMenu = None
aeadAesMenu = None

#AEAD Hardware
cryptoHwAeadAesSupport = []
cryptoHwAeadAesSupported          = False
cryptoHwAeadAesEnabledSymbol      = None
cryptoAeadAesEnabledSymbol        = None

cryptoHwAeadAesGcmSupport = []
cryptoHwAeadAesGcmSupported       = False
cryptoHwAeadAesGcmEnabledSymbol   = None
cryptoAeadAesGcmEnabledSymbol     = None

cryptoHwAeadAesCcmSupport = []
cryptoHwAeadAesCcmSupported       = False
cryptoHwAeadAesCcmEnabledSymbol   = None
cryptoAeadAesCcmEnabledSymbol     = None

cryptoHwAeadAesEaxSupport = []
cryptoHwAeadAesEaxSupported         = False
cryptoHwAeadAesEaxEnabledSymbol     = None
cryptoAeadAesEaxEnabledSymbol       = None

cryptoHwAeadAesSivCmacSupport = []
cryptoHwAeadAesSivCmacSupported     = False
cryptoHwAeadAesSivCmacEnabledSymbol = None
cryptoAeadAesSivCmacEnabledSymbol   = None

cryptoHwAeadAesSivGcmSupport = []
cryptoHwAeadAesSivGcmSupported      = False
cryptoHwAeadAesSivGcmEnabledSymbol  = None
cryptoAeadAesSivGcmEnabledSymbol    = None

cryptoCurrentHwCcmSupport    = []
cryptoHwAeadAesCcmSupported       = False
cryptoHwAeadAesCcmEnabledSymbol   = None
cryptoAeadAesCcmEnabledSymbol     = None

cryptoCurrentHwEaxSupport    = []
cryptoHwAeadAesEaxSupported         = False
cryptoHwAeadAesEaxEnabledSymbol     = None
cryptoAeadAesEaxEnabledSymbol       = None

cryptoCurrentHwSivCmacSupport    = []
cryptoHwAeadAesSivCmacSupported     = False
cryptoHwAeadAesSivCmacEnabledSymbol = None
cryptoAeadAesSivCmacEnabledSymbol   = None

cryptoCurrentHwSivGcmSupport    = []
cryptoHwAeadAesSivGcmSupported      = False
cryptoHwAeadAesSivGcmEnabledSymbol  = None
cryptoAeadAesSivGcmEnabledSymbol    = None


#===============================================================================
#HMAC Hardware
cryptoHwMacAesSupport = []
cryptoHwMacAesSupported            = False
cryptoHwMacAesEnabledSymbol        = None
cryptoMacAesEnabledSymbol          = None

cryptoHwMacAesCmacSupport = []
cryptoHwMacAesCmacSupported        = False
cryptoHwMacAesCmacEnabledSymbol    = None
cryptoMacAesCmacEnabledSymbol      = None

cryptoHwMacAesCbcMacSupport = []
cryptoHwMacAesCbcMacSupported      = False
cryptoHwMacAesCbcMacEnabledSymbol  = None
cryptoMacAesCbcMacEnabledSymbol    = None

cryptoHwMacAesGmacSupport = []
cryptoHwMacAesGmacSupported        = False
cryptoHwMacAesGmacEnabledSymbol    = None
cryptoMacAesGmacEnabledSymbol      = None

#===============================================================================
#DS - Digital Signing
dsMenu                             = None
cryptoDsEcdsaEnabledSymbol         = None


#===============================================================================
#KAS - Key Authorization
kasMenu      = None
cryptoKasEcdhEnableSymbol          = None

#===============================================================================
#RNG - Random Number Generation
cryptoCurrentHwRngSupport          = []
cryptoRngTrngEnabledSymbol         = None
cryptoRngPrngEnabledSymbol         = None

#===============================================================================
# ASYM Hardware

#ASYM RSA 
cryptoHwRsaSupport = [
    ["PUKCC", "U2009", "2.5.0", [],
     set(["HAVE_MCHP_CRYPTO_RSA_HW_PUKCC"])], #ATSAME54P20A
    ["PUKCC", "U2009", "2.5.0", [],
     set(["HAVE_MCHP_CRYPTO_RSA_HW_PUKCC"])], #ATSAME54P20A
    ["CPKCC", "44163", "B", [],
     set(["HAVE_MCHP_CRYPTO_RSA_HW_CPKCC"])]  #PIC32CX MT
]
cryptoHwRsaSupported = False
cryptoHwRsaEnabledSymbol = None
cryptoRsaEnabledSymbol = None


#ASYM ECC 
cryptoHwEccSupport = [
    ["PUKCC", "U2009", "2.5.0", [],
     set(["HAVE_MCHP_CRYPTO_ECC_HW_PUKCC"])], #ATSAME54P20A
    ["BA414E", "00343", "", [],
     set(["HAVE_MCHP_CRYPTO_ECC_HW_BA414E",
          "HAVE_MCHP_CRYPTO_HW_BA414E"])],    #PCI32MZ-W
    ["CPKCC", "44163", "B", [],
     set(["HAVE_MCHP_CRYPTO_ECC_HW_CPKCC"])]  #PIC32CX MT
]
cryptoHwEccSupported         = False
cryptoHwEccEnabledSymbol     = None
cryptoSWCallBackEnableSymbol = None
cryptoEccEnabledSymbol       = None

#===============================================================================
#HW IDAU(2803)
cryptoHW_U2803        = [
        ["IDAU", "U2803", "1.0.0", [],
         set(["HAVE_MCHP_CRYPTO_HW_U2803"])],] #ATSAML11
cryptoHW_U2803Present = False
cryptoHW_U2803Symbol  = None

cryptoHW_U2805        = [
        ["IDAU", "U2805", "1.0.0", [],
         set(["HAVE_MCHP_CRYPTO_HW_U2805"])],] #PIC32CM
cryptoHW_U2805Present = False
cryptoHW_U2805Symbol  = None

cryptoHW_03710        = [
        ["IDAU", "03710", "2a0",
         [], set(["HAVE_MCHP_CRYPTO_HW_03710"])],] #PIC32CM'Lx
cryptoHW_03710Present = False
cryptoHW_03710Symbol  = None

