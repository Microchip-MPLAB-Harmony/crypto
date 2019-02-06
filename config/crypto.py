#/*****************************************************************************
# Copyright (C) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
cryptoHwTrngSupport = [["RNG", "00159", "", [], set([])],  #PIC32MZ EF
                      ["TRNG", "6334", "G", ["crypt_rng_sam6334.c"], set([])],  #ATSAMV70Q20B
                      #["TRNG", "U2242", "1.1.0", ["random_u2242.c"], set([])], #ATSAME54P20A
                      ["TRNG", "6334", "K", [], set([])],  #ATSAMA5D28
                     ]

cryptoHwMd5Support = [["CRYPTO", "00158", "1", [], set([])] #PIC32MZ EF
                     ]
                     
cryptoHwSha1Support = [["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
                       ["ICM", "11105", "H", ["crypt_sha1_sam11105.c", "crypt_sha_hw.h"], set(["CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20B
                       #["ICM", "U2010", "1.2.0", ["sha_u2010.c"], set([])], #ATSAME54P20A
                       ["SHA", "6156", "O", [], set([])] #ATSAMA5D28
                      ]

cryptoHwSha224Support = [["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
                      ]
                      
cryptoHwSha256Support = [["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
                       ["ICM", "11105", "H", ["crypt_sha256_sam11105.c", "crypt_sha_hw.h"], set(["CRYPTO_SHA_HW_11105"])], #ATSAMV70Q20
                       #["ICM", "U2010", "1.2.0", ["sha_u2010.c"], set([])], #ATSAME54P20A
                       ["SHA", "6156", "O", [], set([])] #ATSAMA5D28
                      ]
                      
cryptoHwSha384Support = [["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
                      ]
                      
cryptoHwSha512Support = [["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
                      ]

cryptoHwAesSupport = [["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
                       ["AES", "6149", "W", ["crypt_aes_sam6149.c"], set(["CRYPTO_AES_HW_6149"])], #ATSAMV70Q20B
                       #["AES", "U2238", "2.2.0", ["aes_U2238.c"], set([])], #ATSAME54P20A
                       ["AES", "6149", "ZB", [], set([])] #ATSAMA5D28
                      ]

cryptoHwDesSupport = [
                      ["CRYPTO", "00158", "1", [], set([])], #PIC32MZ EF
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
                        "crypt_sha1_hw.h", "crypt_sha_sam11105.h",
                        "crypt_sha256_hw.h", "crypt_aes_hw.h", "crypt_aes_sam6149.h",
                        "crypt_aes_hwInt.h",
                        "dsa.h", "ecc.h", "ed25519.c", "ed25519.h", "error.c", 
                        "error-crypt.h", "fe_low_mem.c", "fe_operations.c", 
                        "cpuid.h", "fe_operations.h",
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
                        "selftest.h", "settings.h", "sha.c", "sha.h", "sha256.h", 
                        "sha3.c", "sha3.h", "sha512.h", "signature.c", 
                        "signature.h", "sniffer.h", "sniffer_error.h", 
                        #"sp.h", "sp_arm32.c", "sp_arm64.c",
                        #"sp_armthumb.c", "sp_c32.c", "sp_c64.c", "sp_int.c", 
                        #"sp_int.h", "sp_x86_64.c", 
                        "srp.c", "srp.h", "ssl.h", 
                        "tfm.c", "tfm.h", "types.h", "version.h", 
                        "visibility.h", "wc_encrypt.c", "wc_encrypt.h", 
                        "wc_pkcs11.c", "wc_pkcs11.h", "wc_port.c", "wc_port.h", 
                        "wolfevent.c", "wolfevent.h", "wolfio.h", "wolfmath.c", 
                        "wolfmath.h"
                       ]
cryptoZlibFiles = ['crc32.h','deflate.h','inffast.h','inffixed.h','inflate.h','inftrees.h',
                   'trees.h','adler32.c','crc32.c','deflate.c','zconf.h','zutil.h','zlib.h',
                   'inflate.c','trees.c','gzguts.h','zutil.c','inftrees.c','inffast.c'
                  ]

#Global variables.  Do not modify the defaults
cryptoCurrentHwRngSupport = ["SW", "SW", "3.2", []]
cryptoCurrentHwMd5Support = ["SW", "SW", "3.2", ["md5.c"]]
cryptoCurrentHwSha1Support = ["SW", "SW", "3.2", []]
cryptoCurrentHwSha224Support = ["SW", "SW", "3.2", ["sha256.c"]]
cryptoCurrentHwSha256Support = ["SW", "SW", "3.2", ["sha256.c"]]
cryptoCurrentHwSha384Support = ["SW", "SW", "3.2", ["sha512.c"]]
cryptoCurrentHwSha512Support = ["SW", "SW", "3.2", ["sha512.c"]]
cryptoCurrentHwAesSupport = ["SW", "SW", "3.2", []]
cryptoCurrentHwDesSupport = ["SW", "SW", "3.2", ["des3.c"]]
cryptoCurrentHwRsaSupport = ["SW", "SW", "3.2", ["rsa.c"]]
cryptoCurrentHwEccSupport = ["SW", "SW", "3.2", ["ecc.c", "ecc_fp.c"]]

cryptoCurrentSwRngSupport = ["SW", "SW", "3.2", []]
cryptoCurrentSwMd5Support = ["SW", "SW", "3.2", ["md5.c"]]
cryptoCurrentSwSha1Support = ["SW", "SW", "3.2", []]
cryptoCurrentSwSha224Support = ["SW", "SW", "3.2", ["sha256.c"]]
cryptoCurrentSwSha256Support = ["SW", "SW", "3.2", ["sha256.c"]]
cryptoCurrentSwSha384Support = ["SW", "SW", "3.2", ["sha512.c"]]
cryptoCurrentSwSha512Support = ["SW", "SW", "3.2", ["sha512.c"]]
cryptoCurrentSwAesSupport = ["SW", "SW", "3.2", []]
cryptoCurrentSwDesSupport = ["SW", "SW", "3.2", ["des3.c"]]
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
    global cryptoAdditionalHwDefines
    cryptoAdditionalHwDefines = cryptoComponent.createStringSymbol("cryptAdditionalHwDefines", None)
    cryptoAdditionalHwDefines.setVisible(False)

    setupHwSupport(cryptoComponent)
    addAlwaysOnFiles(cryptoComponent)
    
    series = ATDF.getNode("/avr-tools-device-file/devices/device").getAttribute("series")
    cryptoCoreSeries = cryptoComponent.createStringSymbol("cryptoCoreSeries", None)
    cryptoCoreSeries.setVisible(False)
    cryptoCoreSeries.setDefaultValue(series)
    
    # Keep track of wolfSSL enabled/disabled. This is needed when the message handler
    # receives a notification from wolfSSL that wolfSSL has been enabled or disabled.
    cryptoIsWolfsslEnabled = cryptoComponent.createBooleanSymbol("cryptoIsWolfsslEnabled",None)
    cryptoIsWolfsslEnabled.setVisible(False)
    Database.setSymbolValue("lib_crypto","cryptoIsWolfsslEnabled",False,1)

    # message to display if wolfSSL is enabled
    cryptoMessage = cryptoComponent.createCommentSymbol("cryptoMessage", None)
    cryptoMessage.setLabel("Crypto library is disabled. Configure through 3rd party wolfSSL component.")
    cryptoMessage.setVisible(False)
    cryptoWolfCryptDisabledMenuComponentsList.append(cryptoMessage)
    
    #do not add new menu structures before the cryptoHW.
    cryptoHW = cryptoComponent.createBooleanSymbol("cryptoHW", None)
    cryptoHW.setLabel("Use Hardware Acceleration?")
    cryptoHW.setDescription("Enables hardware acceleration of cryptographic library")
    cryptoHW.setDefaultValue(cryptoHwSupportFound)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHW)    
    
    cryptoMenu = cryptoComponent.createMenuSymbol("crypto_menu", None)
    cryptoMenu.setLabel("Crypto Settings")
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoMenu)
    cryptoMenu.setDependencies(handleHwCryptoChange, ["cryptoHW"])

    
    cryptoRandom = cryptoComponent.createBooleanSymbol("cryptoRandom", cryptoMenu)
    cryptoRandom.setLabel("TRNG")
    cryptoRandom.setDescription("Enables True Random Number Generator")
    cryptoRandom.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoRandom)
    if cryptoCurrentHwRngSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoRandom)

    cryptoCipherAES_CTR = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CTR", cryptoMenu)
    cryptoCipherAES_CTR.setLabel("AES - CTR")
    cryptoCipherAES_CTR.setDescription("Enables Advanced Encryption Standard: Counter Mode")
    cryptoCipherAES_CTR.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipherAES_CTR)
    if cryptoCurrentHwAesSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipherAES_CTR)

    
    cryptoCipherAES_CBC = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CBC", cryptoMenu)
    cryptoCipherAES_CBC.setLabel("AES - CBC")
    cryptoCipherAES_CBC.setDescription("Enables Advanced Encryption Standard: Cipher Block Chaining")
    cryptoCipherAES_CBC.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipherAES_CBC)
    if cryptoCurrentHwAesSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipherAES_CBC)

    cryptoCipherAES_ECB = cryptoComponent.createBooleanSymbol("cryptoCipherAES_ECB", cryptoMenu)
    cryptoCipherAES_ECB.setLabel("AES - ECB")
    cryptoCipherAES_ECB.setDescription("Enables Advanced Encryption Standard: Electronic Code Book")
    cryptoCipherAES_ECB.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipherAES_ECB)
    if cryptoCurrentHwAesSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipherAES_ECB)

    cryptoCipherAES_GCM = cryptoComponent.createBooleanSymbol("cryptoCipherAES_GCM", cryptoMenu)
    cryptoCipherAES_GCM.setLabel("AES - GCM")
    cryptoCipherAES_GCM.setDescription("Enables Advanced Encryption Standard: Galois/Counter Mode")
    cryptoCipherAES_GCM.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipherAES_GCM)
    if cryptoCurrentHwAesSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipherAES_GCM)
    

    # Hashes
    cryptoHashMD5 = cryptoComponent.createBooleanSymbol("cryptoHashMD5", cryptoMenu)
    cryptoHashMD5.setLabel("Hash - MD5")
    cryptoHashMD5.setDescription("Enables Hashing function MD5")
    cryptoHashMD5.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHashMD5)
    if cryptoCurrentHwMd5Support[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoHashMD5)

    cryptoHashSHA1 = cryptoComponent.createBooleanSymbol("cryptoHashSHA1", cryptoMenu)
    cryptoHashSHA1.setLabel("Hash - SHA-1")
    cryptoHashSHA1.setDescription("Enables Hashing function SHA-1")
    cryptoHashSHA1.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHashSHA1)
    if cryptoCurrentHwSha1Support[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoHashSHA1)

    
    cryptoHashSHA256 = cryptoComponent.createBooleanSymbol("cryptoHashSHA256", cryptoMenu)
    cryptoHashSHA256.setLabel("Hash - SHA-256")
    cryptoHashSHA256.setDescription("Enables Hashing function SHA-256")
    cryptoHashSHA256.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHashSHA256)
    if cryptoCurrentHwSha256Support[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoHashSHA256)

    cryptoHashSHA384 = cryptoComponent.createBooleanSymbol("cryptoHashSHA384", cryptoMenu)
    cryptoHashSHA384.setLabel("Hash - SHA-384")
    cryptoHashSHA384.setDescription("Enables Hashing function SHA-384")
    cryptoHashSHA384.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHashSHA384)
    if cryptoCurrentHwSha384Support[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoHashSHA384)
    

    cryptoHashSHA512 = cryptoComponent.createBooleanSymbol("cryptoHashSHA512", cryptoMenu)
    cryptoHashSHA512.setLabel("Hash - SHA-512")
    cryptoHashSHA512.setDescription("Enables Hashing function SHA-512")
    cryptoHashSHA512.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHashSHA512)
    if cryptoCurrentHwSha512Support[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoHashSHA512)

    cryptoHashHMAC = cryptoComponent.createBooleanSymbol("cryptoHashHMAC", cryptoMenu)
    cryptoHashHMAC.setLabel("Hash - HMAC")
    cryptoHashHMAC.setDescription("Enables Keyed-Hash Message Authentication Code")
    cryptoHashHMAC.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHashHMAC)

    
    cryptoHuffman = cryptoComponent.createBooleanSymbol("cryptoHuffman", cryptoMenu)
    cryptoHuffman.setLabel("Huffman Coding")
    cryptoHuffman.setDescription("Enables Huffman Coding Compression")
    cryptoHuffman.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoHuffman)

    # General Ciphers
    cryptoCipherECC = cryptoComponent.createBooleanSymbol("cryptoCipherECC", cryptoMenu)
    cryptoCipherECC.setLabel("Cipher - ECC")
    cryptoCipherECC.setDescription("Enables Eliptical Curve Cryptograpy")
    cryptoCipherECC.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipherECC)
    if cryptoCurrentHwEccSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipherECC)

    cryptoCipherRSA = cryptoComponent.createBooleanSymbol("cryptoCipherRSA", cryptoMenu)
    cryptoCipherRSA.setLabel("Cipher - RSA")
    cryptoCipherRSA.setDescription("Enables RSA Cryptosystem")
    cryptoCipherRSA.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipherRSA)
    if cryptoCurrentHwRsaSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipherRSA)

    cryptoCipher3DES = cryptoComponent.createBooleanSymbol("cryptoCipher3DES", cryptoMenu)
    cryptoCipher3DES.setLabel("Cipher - DES/TDES")
    cryptoCipher3DES.setDescription("Enables (Triple) DES Cryptosystem")
    cryptoCipher3DES.setDefaultValue(False)
    cryptoWolfCryptEnabledMenuComponentsList.append(cryptoCipher3DES)
    if cryptoCurrentHwDesSupport[0] != "SW":
        cryptoHwMenuComponentsList.append(cryptoCipher3DES)
        
    # generate the config info and add it to list in configuration.h
    cryptoConfigInfo = cryptoComponent.createFileSymbol("cryptoConfigInfo", None)
    cryptoConfigInfo.setSourcePath("templates/crypto_config.h.ftl")
    cryptoConfigInfo.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    cryptoConfigInfo.setMarkup(True)
    cryptoConfigInfo.setType("STRING")
    

    setHwEnabledMenuItems(cryptoHW.value)
    createAllFileComponents(cryptoComponent)
    setFilesForHwSupport(cryptoHW.value)


def setupHwSupport(cryptoComponent):
    global cryptoHwSupportFound
    global cryptoCurrentHwRngSupport
    global cryptoCurrentHwMd5Support
    global cryptoCurrentHwSha1Support
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
                print("PMWDELETE found rng module" + str(rng[4]))
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(rng[4])
        for md5 in cryptoHwMd5Support:
            if module.getAttribute("name") == md5[0] and module.getAttribute("id") == md5[1] and module.getAttribute("version") == md5[2]:
                cryptoCurrentHwMd5Support = md5
                cryptoHwSupportFound = True
                cryptoHaveHwMd5.setDefaultValue(True)
                print("PMWDELETE found md5 module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(md5[4])
        for sha1 in cryptoHwSha1Support:
            #print("Against: '" + sha1[0] + "' '" + sha1[1] + "' '" + sha1[2] + "'")
            if module.getAttribute("name") == sha1[0] and module.getAttribute("id") == sha1[1] and module.getAttribute("version") == sha1[2]:
                cryptoCurrentHwSha1Support = sha1
                cryptoHwSupportFound = True
                cryptoHaveHwSha1.setDefaultValue(True)
                print("PMWDELETE found sha1 module: " + ", ".join(sha1[4]))
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha1[4])
                print("PMWDELETE list: " + ", ".join(cryptoHwAdditionalDefines))
        for sha224 in cryptoHwSha224Support:
            if module.getAttribute("name") == sha224[0] and module.getAttribute("id") == sha224[1] and module.getAttribute("version") == sha224[2]:
                cryptoCurrentHwSha224Support = sha224
                cryptoHwSupportFound = True
                cryptoHaveHwSha224.setDefaultValue(True)
                print("PMWDELETE found sha-224 module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha224[4])
        for sha256 in cryptoHwSha256Support:
            if module.getAttribute("name") == sha256[0] and module.getAttribute("id") == sha256[1] and module.getAttribute("version") == sha256[2]:
                cryptoCurrentHwSha256Support = sha256
                cryptoHwSupportFound = True
                cryptoHaveHwSha256.setDefaultValue(True)
                print("PMWDELETE found sha-256 module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha256[4])
        for sha384 in cryptoHwSha384Support:
            if module.getAttribute("name") == sha384[0] and module.getAttribute("id") == sha384[1] and module.getAttribute("version") == sha384[2]:
                cryptoCurrentHwSha384Support = sha384
                cryptoHwSupportFound = True
                cryptoHaveHwSha384.setDefaultValue(True)
                print("PMWDELETE found sha-384 module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha384[4])
        for sha512 in cryptoHwSha512Support:
            if module.getAttribute("name") == sha512[0] and module.getAttribute("id") == sha512[1] and module.getAttribute("version") == sha512[2]:
                cryptoCurrentHwSha512Support = sha512
                cryptoHwSupportFound = True
                print("PMWDELETE found sha-512 module")
                cryptoHaveHwSha512.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(sha512[4])
        for aes in cryptoHwAesSupport:
            if module.getAttribute("name") == aes[0] and module.getAttribute("id") == aes[1] and module.getAttribute("version") == aes[2]:
                cryptoCurrentHwAesSupport = aes
                cryptoHwSupportFound = True
                print("PMWDELETE found Aes module")
                cryptoHaveHwAes.setDefaultValue(True)
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(aes[4])
        for des in cryptoHwDesSupport:
            if module.getAttribute("name") == des[0] and module.getAttribute("id") == des[1] and module.getAttribute("version") == des[2]:
                cryptoCurrentHwDesSupport = des
                cryptoHwSupportFound = True
                cryptoHaveHwDes.setDefaultValue(True)
                print("PMWDELETE found Des module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(des[4])
        for rsa in cryptoHwRsaSupport:
            if module.getAttribute("name") == rsa[0] and module.getAttribute("id") == rsa[1] and module.getAttribute("version") == rsa[2]:
                cryptoCurrentHwRsaSupport = rsa
                cryptoHwSupportFound = True
                cryptoHaveHwRsa.setDefaultValue(True)
                print("PMWDELETE found Rsa module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(rsa[4])
        for ecc in cryptoHwEccSupport:
            if module.getAttribute("name") == ecc[0] and module.getAttribute("id") == ecc[1] and module.getAttribute("version") == ecc[2]:
                cryptoCurrentHwEccSupport = ecc
                cryptoHwSupportFound = True
                cryptoHaveHwEcc.setDefaultValue(True)
                print("PMWDELETE found Ecc module")
                cryptoHwAdditionalDefines = cryptoHwAdditionalDefines.union(ecc[4])
    #print("PMWREMOVE: additional defines: " + ", ".join(cryptoHwAdditionalDefines))
    cryptoAdditionalHwDefines.setDefaultValue(", ".join(cryptoHwAdditionalDefines))
    
def addAlwaysOnFiles(cryptoComponent):
    # add crypto.h to the crypto directory (not in src)
    includeFilename = cryptoComponent.createFileSymbol("include_filename", None)
    includeFilename.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME") + "/crypto")
    includeFilename.setSourcePath("crypto.h")
    includeFilename.setDestPath("crypto/")
    includeFilename.setOutputName("crypto.h")
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
    #print("PMWREMOVE SetHwEnable: " + str(enable))
    for symbol in cryptoHwMenuComponentsList:
        if enable:
            if symbol.getLabel()[-2:] != "HW":
                #print("PMWREMOVE setting: " + symbol.getLabel() + " to have -HW")
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
    #print("PMWREMOVE: HW Support for Files Enable: " + str(enable))
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
