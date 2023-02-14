#/*****************************************************************************
# Copyright (C) 2013-2019 Microchip Technology Inc. and its subsidiaries.
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
# *****************************************************************************/



#hardware support
cryptoHwTrngSupport = [["RNG", "00159", "", ["pic32mz-crypt.c"], set(["WOLFSSL_MICROCHIP_PIC32MZ", "WOLFSSL_PIC32MZ_RNG"])],  #PIC32MZ EF
                      ["TRNG", "6334", "G", ["crypt_rng_sam6334.c"], set([])],  #ATSAMV70Q20B
                      ["TRNG", "U2242", "1.1.0", ["crypt_rng_u2242.c"], set([])], #ATSAME54P20A
                      ["TRNG", "U2242", "1.0.0", ["crypt_rng_u2242.c"], set([])], #ATSAML21J18B
                      ["TRNG", "6334", "K", ["crypt_rng_sam6334.c"], set(["CRYPT_TRNG_HW_6334_A5D2"])],  #ATSAMA5D27
                      ["TRNG", "6334", "O", ["crypt_rng_sam6334.c"], set(["CRYPT_TRNG_HW_6334"])],  #ATSAM9X60
                     ]

cryptoHwMd5Support = [["CRYPTO", "00158", "", ["pic32mz-crypt.c"], set(["WOLFSSL_MICROCHIP_PIC32MZ", "WOLFSSL_PIC32MZ_HASH"])] #PIC32MZ EF
                     ]
                     
cryptoHwSha1Support = [["CRYPTO", "00158", "", ["pic32mz-crypt.c"], set(["WOLFSSL_MICROCHIP_PIC32MZ", "WOLFSSL_PIC32MZ_HASH"])], #PIC32MZ EF
                       ["ICM", "11105", "H", ["crypt_sha1_sam11105.c"], set(["CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20B
                       ["ICM", "U2010", "1.2.0", ["crypt_sha1_sam11105.c"], set(["CRYPTO_SHA_HW_11105", "CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
                       ["SHA", "6156", "O", ["crypt_sha1_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAMA5D27
                       ["SHA", "6156", "S", ["crypt_sha1_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAM9X60
                      ]

cryptoHwSha224Support = [
                       ["ICM", "11105", "H", ["crypt_sha224_sam11105.c"], set(["CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
                       ["ICM", "U2010", "1.2.0", ["crypt_sha224_sam11105.c"], set(["CRYPTO_SHA_HW_11105", "CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
                       ["SHA", "6156", "O", ["crypt_sha224_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAMA5D27                       
                       ["SHA", "6156", "S", ["crypt_sha224_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156", "CRYPTO_SHA_HW_6156_R"])], #ATSAM9X60                       
                      ]
                      
cryptoHwSha256Support = [["CRYPTO", "00158", "", ["pic32mz-crypt.c"], set(["WOLFSSL_MICROCHIP_PIC32MZ", "WOLFSSL_PIC32MZ_HASH"])], #PIC32MZ EF
                       ["ICM", "11105", "H", ["crypt_sha256_sam11105.c"], set(["CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
                       ["ICM", "U2010", "1.2.0", ["crypt_sha256_sam11105.c"], set(["CRYPTO_SHA_HW_11105", "CRYPTO_SHA_HW_U2010"])], #ATSAME54P20A
                       ["SHA", "6156", "O", ["crypt_sha256_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAMA5D27                       
                       ["SHA", "6156", "S", ["crypt_sha256_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAM9X60                       
                      ]
                      
cryptoHwSha384Support = [
                       ["SHA", "6156", "O", ["crypt_sha384_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAMA5D27                       
                       ["SHA", "6156", "S", ["crypt_sha384_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAM9X60                       
                      ]
                      
cryptoHwSha512Support = [
                       ["SHA", "6156", "O", ["crypt_sha512_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAMA5D27                       
                       ["SHA", "6156", "S", ["crypt_sha512_sam6156.c", "crypt_sha_sam6156.c"], set(["CRYPTO_SHA_HW_6156"])], #ATSAM9X60                       
                      ]

cryptoHwAesSupport = [["CRYPTO", "00158", "", ["pic32mz-crypt.c"], set(["WOLFSSL_MICROCHIP_PIC32MZ", "WOLFSSL_PIC32MZ_HASH"])], #PIC32MZ EF
                       ["AES", "6149", "W", ["crypt_aes_sam6149.c"], set(["CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                       ["AES", "U2238", "2.2.0", ["crypt_aes_u2238.c"], set(["CRYPTO_AES_HW_U2238"])], #ATSAME54P20A
                       ["AES", "U2238", "2.0.0", ["crypt_aes_u2238.c"], set(["CRYPTO_AES_HW_U2238"])], #ATSAML21J18B
                       ["AES", "6149", "ZB", ["crypt_aes_sam6149.c"], set(["CRYPTO_AES_HW_6149", "CRYPTO_AES_HW_6149_ZB"])], #ATSAMA5D28
                       ["AES", "6149", "ZH", ["crypt_aes_sam6149.c"], set(["CRYPTO_AES_HW_6149", "CRYPTO_AES_HW_6149_ZE"])] #ATSAM9x60
                      ]

cryptoHwDesSupport = [["CRYPTO", "00158", "", ["pic32mz-crypt.c"], set(["WOLFSSL_MICROCHIP_PIC32MZ", "WOLFSSL_PIC32MZ_HASH"])], #PIC32MZ EF
                      ["TDES", "6150", "N", ["crypt_tdes_sam6150.c"], set(["CRYPTO_TDES_HW_6150"])], #ATSAMA5D27 
                      ["TDES", "6150", "R", ["crypt_tdes_sam6150.c"], set(["CRYPTO_TDES_HW_6150"])], #ATSAM9X60 
                      
                     ]

cryptoHwRsaSupport = [
                      #["PUKCC", "U2009", "2.5.0", [], set([])], #ATSAME54P20A
                     ]

cryptoHwEccSupport = [
                      #["PUKCC", "U2009", "2.5.0", [], set([])], #ATSAME54P20A
                      ]
                      
#Common Files
cryptoWolfCryptFiles = ["aes.h", "aes.c", "arc4.c", "arc4.h", "asm.c", "asn.c", "asn.h", 
                        "asn_public.h", "async.c", "async.h", "camellia.c",
                        "camellia.h", "certs_test.h", "chacha.c", "chacha.h",
                        "chacha20_poly1305.c", "chacha20_poly1305.h", "cmac.c",
                        "cmac.h", "coding.c", "coding.h", "compress.c",
                        "compress.h", "curve25519.c", "crypt_rng_hw.h",
                        "curve25519.h", "des3.h", "dh.c", "dh.h", "dsa.c", 
                        "crypt_sha_sam11105.h","crypt_sha_sam6156.h",
                        "crypt_sha_hw.h", "crypt_aes_hw.h", "crypt_aes_sam6149.h",
                        "crypt_aes_hwInt.h", "crypt_sha1_hw.h", "crypt_sha256_hw.h",
                        "crypt_sha224_hw.h", "crypt_aes_u2238.h", "crypt_sha384_hw.h", "crypt_sha512_hw.h",
                        "crypt_tdes_hw.h", "crypt_tdes_sam6150.h", "crypt_tdes_hwInt.h",
                        "dsa.h", "ecc.h", "ed25519.c", "ed25519.h", "error.c", 
                        "error-crypt.h", "fe_low_mem.c", "fe_operations.c", 
                        "fe_operations.h", "pic32mz-crypt.h",
                        #"fe_x25519_128.i", "fe_x25519_x64.i", 
                        "fips_test.h", 
                        #"fp_mont_small.i", "fp_mul_comba_12.i", "fp_mul_comba_17.i",
                        #"fp_mul_comba_20.i", "fp_mul_comba_24.i", "fp_mul_comba_28.i",
                        #"fp_mul_comba_3.i", "fp_mul_comba_32.i", "fp_mul_comba_4.i",
                        #"fp_mul_comba_48.i", "fp_mul_comba_6.i", "fp_mul_comba_64.i", 
                        #"fp_mul_comba_7.i", "fp_mul_comba_8.i", "fp_mul_comba_9.i",
                        #"fp_mul_comba_small_set.i", "fp_sqr_comba_12.i", 
                        #"fp_sqr_comba_17.i", "fp_sqr_comba_20.i", "fp_sqr_comba_24.i", 
                        #"fp_sqr_comba_28.i", "fp_sqr_comba_3.i", "fp_sqr_comba_32.i", 
                        #"fp_sqr_comba_4.i", "fp_sqr_comba_48.i", "fp_sqr_comba_6.i", 
                        #"fp_sqr_comba_64.i", "fp_sqr_comba_7.i", "fp_sqr_comba_8.i", 
                        #"fp_sqr_comba_9.i", "fp_sqr_comba_small_set.i", 
                        "ge_low_mem.c", "ge_operations.c", "ge_operations.h", 
                        "hash.c", "hash.h", "hc128.c", "hc128.h", "hmac.c", 
                        "hmac.h", "idea.c", "idea.h", "integer.c", "integer.h", 
                        "logging.c", "logging.h", "md2.c", "md2.h", "md4.c", 
                        "md4.h", "md5.h", "mem_track.h", "memory.c", "memory.h",
                        "misc.c", "misc.h", "mpi_class.h", "mpi_superclass.h", 
                        "pkcs11.h", "pkcs12.c", "pkcs12.h", "pkcs7.c", 
                        "pkcs7.h", "poly1305.c", "poly1305.h", "pwdbased.c", 
                        "pwdbased.h", "rabbit.c", "rabbit.h", "random.c", "random.h",
                        "ripemd.c", "ripemd.h", "rsa.h", 
                        "selftest.h", "settings.h", "sha.c", "sha.h","sha256.c", "sha256.h", 
                        "sha3.c", "sha3.h", "sha512.h", "signature.c", "sha512.c",
                        "signature.h", "sniffer.h", "sniffer_error.h", 
                        #"sp.h", "sp_arm32.c", "sp_arm64.c",
                        #"sp_armthumb.c", "sp_c32.c", "sp_c64.c", "sp_int.c", 
                        #"sp_int.h", "sp_x86_64.c", 
                        "srp.c", "srp.h", "ssl.h", 
                        "tfm.c", "tfm.h", "types.h", "version.h", 
                        "visibility.h", "wc_encrypt.c", "wc_encrypt.h", 
                        "wc_pkcs11.c", "wc_pkcs11.h", "wc_port.c", "wc_port.h", 
                        "wolfevent.c", "wolfevent.h", "wolfio.h", "wolfmath.c", 
                        "wolfmath.h", "des3.c", "md5.c"
                       ]
cryptoZlibFiles = ['crc32.h','deflate.h','inffast.h','inffixed.h','inflate.h','inftrees.h',
                   'trees.h','adler32.c','crc32.c','deflate.c','zconf.h','zutil.h','zlib.h',
                   'inflate.c','trees.c','gzguts.h','zutil.c','inftrees.c','inffast.c'
                  ]

#Global variables.  Do not modify the defaults
cryptoCurrentHwRngSupport = ["SW", "SW", "3.2", []]
cryptoCurrentHwMd5Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha1Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha224Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha256Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha384Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha512Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwAesSupport = ["SW", "SW", "3.2", []]
cryptoCurrentHwDesSupport = ["SW", "SW", "3.2", []]
cryptoCurrentHwRsaSupport = ["SW", "SW", "3.2", ["rsa.c"]]
cryptoCurrentHwEccSupport = ["SW", "SW", "3.2", ["ecc.c", "ecc_fp.c"]]

cryptoCurrentSwRngSupport = ["SW", "SW", "3.2", []]
cryptoCurrentSwMd5Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha1Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha224Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha256Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha384Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha512Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwAesSupport = ["SW", "SW", "3.2", []]
cryptoCurrentSwDesSupport = ["SW", "SW", "3.2", []]
cryptoCurrentSwRsaSupport = ["SW", "SW", "3.2", ["rsa.c"]]
cryptoCurrentSwEccSupport = ["SW", "SW", "3.2", ["ecc.c", "ecc_fp.c"]]

cryptoHwFilesDict = {}
cryptoSwFilesDict = {}
cryptoWolfCryptFilesDict = {}

cryptoHwFileComponentsDict = {}
cryptoSwFileComponentsDict = {}
cryptoWolfCryptFileComponentsDict = {}
cryptoHwMenuComponentsList = []
cryptoWolfCryptEnabledMenuComponentsList = []
cryptoWolfCryptDisabledMenuComponentsList = []

cryptoHwSupportFound = False

cryptoHwAdditionalDefines = set([])
cryptoAdditionalHwDefines = ""

def instantiateComponent(cryptoComponent):
    addAlwaysOnFiles(cryptoComponent)
    


def setupHwSupport(cryptoComponent):
    global cryptoHwSupportFound
    global cryptoCurrentHwRngSupport
    global cryptoCurrentHwMd5Support
    global cryptoCurrentHwSha1Support
    global cryptoCurrentHwSha224Support
    global cryptoCurrentHwSha256Support
    global cryptoCurrentHwSha384Support
    global cryptoCurrentHwSha512Support
    global cryptoCurrentHwAesSupport
    global cryptoCurrentHwDesSupport
    global cryptoCurrentHwRsaSupport
    global cryptoCurrentHwEccSupport
    global cryptoHwAdditionalDefines
    global cryptoAdditionalHwDefines

    cryptoHaveHwRng = cryptoComponent.createBooleanSymbol("cryptoHaveHwRng", None)
    cryptoHaveHwRng.setVisible(False)
    cryptoHaveHwRng.setDefaultValue(False)

    cryptoHaveHwMd5 = cryptoComponent.createBooleanSymbol("cryptoHaveHwMd5", None)
    cryptoHaveHwMd5.setVisible(False)
    cryptoHaveHwMd5.setDefaultValue(False)

    cryptoHaveHwSha1 = cryptoComponent.createBooleanSymbol("cryptoHaveHwSha1", None)
    cryptoHaveHwSha1.setVisible(False)
    cryptoHaveHwSha1.setDefaultValue(False)

    cryptoHaveHwSha224 = cryptoComponent.createBooleanSymbol("cryptoHaveHwSha224", None)
    cryptoHaveHwSha224.setVisible(False)
    cryptoHaveHwSha224.setDefaultValue(False)

    cryptoHaveHwSha256 = cryptoComponent.createBooleanSymbol("cryptoHaveHwSha256", None)
    cryptoHaveHwSha256.setVisible(False)
    cryptoHaveHwSha256.setDefaultValue(False)

    cryptoHaveHwSha384 = cryptoComponent.createBooleanSymbol("cryptoHaveHwSha384", None)
    cryptoHaveHwSha384.setVisible(False)
    cryptoHaveHwSha384.setDefaultValue(False)

    cryptoHaveHwSha512 = cryptoComponent.createBooleanSymbol("cryptoHaveHwSha512", None)
    cryptoHaveHwSha512.setVisible(False)
    cryptoHaveHwSha512.setDefaultValue(False)

    cryptoHaveHwAes = cryptoComponent.createBooleanSymbol("cryptoHaveHwAes", None)
    cryptoHaveHwAes.setVisible(False)
    cryptoHaveHwAes.setDefaultValue(False)

    cryptoHaveHwDes = cryptoComponent.createBooleanSymbol("cryptoHaveHwDes", None)
    cryptoHaveHwDes.setVisible(False)
    cryptoHaveHwDes.setDefaultValue(False)
    
    cryptoHaveHwRsa = cryptoComponent.createBooleanSymbol("cryptoHaveHwRsa", None)
    cryptoHaveHwRsa.setVisible(False)
    cryptoHaveHwRsa.setDefaultValue(False)

    cryptoHaveHwEcc = cryptoComponent.createBooleanSymbol("cryptoHaveHwEcc", None)
    cryptoHaveHwEcc.setVisible(False)
    cryptoHaveHwEcc.setDefaultValue(False)
    
    cryptoHwAdditionalDefines = set([])
    
    periphNode = ATDF.getNode("/avr-tools-device-file/devices/device/peripherals")
    modules = periphNode.getChildren()
    for module in modules:
        #print("Checking: '" + str(module.getAttribute("name")) + "' '" + str(module.getAttribute("id")) + "' '" + str(module.getAttribute("version")) + "'")
        for rng in cryptoHwTrngSupport:
            if module.getAttribute("name") == rng[0] and module.getAttribute("id") == rng[1] and module.getAttribute("version") == rng[2]:
                cryptoCurrentHwRngSupport = rng
                cryptoHwSupportFound = True
                cryptoHaveHwRng.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(rng[4])
        for md5 in cryptoHwMd5Support:
            if module.getAttribute("name") == md5[0] and module.getAttribute("id") == md5[1] and module.getAttribute("version") == md5[2]:
                cryptoCurrentHwMd5Support = md5
                cryptoHwSupportFound = True
                cryptoHaveHwMd5.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(md5[4])
        for sha1 in cryptoHwSha1Support:
            #print("Against: '" + sha1[0] + "' '" + sha1[1] + "' '" + sha1[2] + "'")
            if module.getAttribute("name") == sha1[0] and module.getAttribute("id") == sha1[1] and module.getAttribute("version") == sha1[2]:
                cryptoCurrentHwSha1Support = sha1
                cryptoHwSupportFound = True
                cryptoHaveHwSha1.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha1[4])
        for sha224 in cryptoHwSha224Support:
            if module.getAttribute("name") == sha224[0] and module.getAttribute("id") == sha224[1] and module.getAttribute("version") == sha224[2]:
                cryptoCurrentHwSha224Support = sha224
                cryptoHwSupportFound = True
                cryptoHaveHwSha224.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha224[4])
        for sha256 in cryptoHwSha256Support:
            if module.getAttribute("name") == sha256[0] and module.getAttribute("id") == sha256[1] and module.getAttribute("version") == sha256[2]:
                cryptoCurrentHwSha256Support = sha256
                cryptoHwSupportFound = True
                cryptoHaveHwSha256.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha256[4])
        for sha384 in cryptoHwSha384Support:
            if module.getAttribute("name") == sha384[0] and module.getAttribute("id") == sha384[1] and module.getAttribute("version") == sha384[2]:
                cryptoCurrentHwSha384Support = sha384
                cryptoHwSupportFound = True
                cryptoHaveHwSha384.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha384[4])
        for sha512 in cryptoHwSha512Support:
            if module.getAttribute("name") == sha512[0] and module.getAttribute("id") == sha512[1] and module.getAttribute("version") == sha512[2]:
                cryptoCurrentHwSha512Support = sha512
                cryptoHwSupportFound = True
                cryptoHaveHwSha512.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha512[4])
        for aes in cryptoHwAesSupport:
            if module.getAttribute("name") == aes[0] and module.getAttribute("id") == aes[1] and module.getAttribute("version") == aes[2]:
                cryptoCurrentHwAesSupport = aes
                cryptoHwSupportFound = True
                cryptoHaveHwAes.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(aes[4])
        for des in cryptoHwDesSupport:
            if module.getAttribute("name") == des[0] and module.getAttribute("id") == des[1] and module.getAttribute("version") == des[2]:
                cryptoCurrentHwDesSupport = des
                cryptoHwSupportFound = True
                cryptoHaveHwDes.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(des[4])
        for rsa in cryptoHwRsaSupport:
            if module.getAttribute("name") == rsa[0] and module.getAttribute("id") == rsa[1] and module.getAttribute("version") == rsa[2]:
                cryptoCurrentHwRsaSupport = rsa
                cryptoHwSupportFound = True
                cryptoHaveHwRsa.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(rsa[4])
        for ecc in cryptoHwEccSupport:
            if module.getAttribute("name") == ecc[0] and module.getAttribute("id") == ecc[1] and module.getAttribute("version") == ecc[2]:
                cryptoCurrentHwEccSupport = ecc
                cryptoHwSupportFound = True
                cryptoHaveHwEcc.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(ecc[4])
    cryptoAdditionalHwDefines.setDefaultValue(", ".join(cryptoHwAdditionalDefines))

def addAlwaysOnFiles(cryptoComponent):
    # add crypto.h to the crypto directory (not in src)
    includeFilename = cryptoComponent.createFileSymbol("include_filename", None)
    includeFilename.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME") + "/crypto")
    includeFilename.setSourcePath("crypto.h")
    includeFilename.setDestPath("crypto/")
    includeFilename.setOutputName("crypto.h")
    includeFilename.setType("HEADER")
        
    includeFilename = cryptoComponent.createFileSymbol("tmrFile", None)
    includeFilename.setProjectPath("system/tmr")
    includeFilename.setSourcePath("src/sys_tmr.h")
    includeFilename.setDestPath("system/tmr/")
    includeFilename.setOutputName("sys_tmr.h")
    includeFilename.setType("HEADER")
    
    # add crypto.c to the crypto/src directory 
    srcFilename = cryptoComponent.createFileSymbol("src_filename", None)
    srcFilename.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME") + "/crypto")
    srcFilename.setSourcePath("src/crypto.c")
    srcFilename.setDestPath("crypto/src/")
    srcFilename.setOutputName("crypto.c")
    srcFilename.setType("SOURCE")
    srcFilename.setEnabled(True)
    
    # put header include into system_definitions.h - but should it be there?
    headerList = cryptoComponent.createListEntrySymbol("header_list", None)
    headerList.setTarget("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    headerList.addValue('#include "crypto/crypto.h"')

def setHwEnabledMenuItems(enable):
    for symbol in cryptoHwMenuComponentsList:
        if enable:
            if symbol.getLabel()[-2:] != "HW":
                symbol.setLabel(symbol.getLabel() + " - HW")
        else:
            if symbol.getLabel()[-2:] == "HW":
                symbol.setLabel(symbol.getLabel()[:-5])

def handleHwCryptoChange(symbol, event):
    if event["id"] == "cryptoHW":
        setHwEnabledMenuItems(event["value"])
        setFilesForHwSupport(event["value"])

def createFileComponent(baseComponent, fileName, srcPath, destPath):
    fileComp = baseComponent.createFileSymbol(fileName.replace('.', '_'), None)
    fileComp.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME") + "/crypto")
    fileComp.setSourcePath(srcPath + fileName)
    fileComp.setOutputName(fileName)
    fileComp.setDestPath(destPath)

    if fileName[-2:] == '.h':
        fileComp.setType("HEADER")
    else:
        fileComp.setType("SOURCE")

    return fileComp

def createWolfCryptFileComponent(baseComponent, fileName, srcPath, destPath):
    global cryptoWolfCryptFilesDict
    if fileName in cryptoWolfCryptFilesDict:
        print("CryptoLib Error: Attempting to add the same file twice: " + fileName)
        return
    fc = createFileComponent(baseComponent, fileName, srcPath, destPath)
    cryptoWolfCryptFilesDict[fileName] = fc

def createHwFileComponent(baseComponent, fileName, srcPath, destPath):
    global cryptoWolfCryptFilesDict
    global cryptoSwFileComponentsDict
    global cryptoHwFileComponentsDict
    if fileName in cryptoWolfCryptFilesDict:
        print("CryptoLib Error: Attempting to add a crypto hardware file that is already a common file: " + fileName)
        return
    if fileName in cryptoHwFileComponentsDict:
        print("CryptoLib Error: Attempting to add the same hardware file twice: " + fileName)
        return
    if fileName in cryptoSwFileComponentsDict:
        print("CryptoLib Info: Adding a HW component that already has a SW component, changing to common component " + fileName)
        fc = cryptoSwFileComponentsDict.pop(fileName)
        cryptoWolfCryptFilesDict[fileName] = fc
        return
    fc = createFileComponent(baseComponent, fileName, srcPath, destPath)
    cryptoHwFileComponentsDict[fileName] = fc
    
def createSwFileComponent(baseComponent, fileName, srcPath, destPath):
    global cryptoWolfCryptFilesDict
    global cryptoSwFileComponentsDict
    global cryptoHwFileComponentsDict
    if fileName in cryptoWolfCryptFilesDict:
        print("CryptoLib Error: Attempting to add a crypto software file that is already a common file: " + fileName)
        return
    if fileName in cryptoSwFileComponentsDict:
        print("CryptoLib Error: Attempting to add the same software file twice: " + fileName)
        return
    if fileName in cryptoHwFileComponentsDict:
        print("CryptoLib Info: Adding a SW component that already has a HW component, changing to common component " + fileName)
        fc = cryptoHwFileComponentsDict.pop(fileName)
        cryptoWolfCryptFilesDict[fileName] = fc
        return
    fc = createFileComponent(baseComponent, fileName, srcPath, destPath)
    cryptoSwFileComponentsDict[fileName] = fc

def createAllFileComponents(baseComponent):
    global cryptoWolfCryptFilesList
    for fileName in cryptoWolfCryptFiles:
        createWolfCryptFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoZlibFiles:
        createWolfCryptFileComponent(baseComponent, fileName, "src/zlib-1.2.7/", "crypto/src/zlib-1.2.7/")
    for fileName in cryptoCurrentHwRngSupport[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwMd5Support[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwSha1Support[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwSha224Support[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwSha256Support[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwSha384Support[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwSha512Support[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwAesSupport[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwDesSupport[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwRsaSupport[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentHwEccSupport[3]:
        createHwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwRngSupport[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwMd5Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwSha1Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwSha224Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwSha256Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwSha384Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwSha512Support[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwAesSupport[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwDesSupport[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwRsaSupport[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")
    for fileName in cryptoCurrentSwEccSupport[3]:
        createSwFileComponent(baseComponent, fileName, "src/", "crypto/src/")

def setFilesForHwSupport(enable):
    for fc in cryptoHwFileComponentsDict.values():
        fc.setEnabled(enable)
    for fc in cryptoSwFileComponentsDict.values():
        fc.setEnabled(not enable)
    
def setFilesForWolfSslEnabled(enable):
    if (enable):
        for fc in cryptoWolfCryptFilesDict.values():
            fc.setEnabled(False)
        for fc in cryptoHwFileComponentsDict.values():
            fc.setEnabled(False)
        for fc in cryptoSwFileComponentsDict.values():
            fc.setEnabled(False)
    else:
        for fc in cryptoWolfCryptFilesDict.values():
            fc.setEnabled(True)
        setFilesForHwSupport(cryptoWolfCryptEnabledMenuComponentsList[0].value)
