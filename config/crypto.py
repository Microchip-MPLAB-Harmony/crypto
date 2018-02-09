def instantiateComponent(cryptoComponent):
    cryptoHW = cryptoComponent.createBooleanSymbol("cryptoHW", None)
    cryptoHW.setLabel("Use Hardware Acceleration?")
    cryptoHW.setDescription("Enables hardware acceleration of cryptographic library")

    if Peripheral.moduleExists("ICM"):
        cryptoHW.setVisible(True)
        cryptoHW.setDefaultValue(True)
    else:
        cryptoHW.setVisible(False)
        cryptoHW.setDefaultValue(False)

    maskFamily = cryptoComponent.createStringSymbol("maskFamily", None)
    maskFamily.setVisible(False)
    if "PIC32C" in Variables.get("__PROCESSOR"):
        maskFamily.setDefaultValue("PIC32C")
    else:
        maskFamily.setDefaultValue("PIC32M")

    cryptoMenu = cryptoComponent.createMenuSymbol(None, None)
    cryptoMenu.setLabel("Crypto Settings")

    # Random Number Generation
    cryptoRandom = cryptoComponent.createBooleanSymbol("cryptoRandom", cryptoMenu)
    cryptoRandom.setLabel("TRNG - HW")
    cryptoRandom.setDescription("Enables True Random Number Generator")
    cryptoRandom.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoRandom.setDefaultValue(False)

    cryptoCipherAES_CTR = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CTR", cryptoMenu)
    cryptoCipherAES_CTR.setLabel("AES - CTR - HW")
    cryptoCipherAES_CTR.setDescription("Enables Advanced Encryption Standard: Counter Mode")
    cryptoCipherAES_CTR.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoCipherAES_CTR.setDefaultValue(False)

    cryptoCipherAES_CBC = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CBC", cryptoMenu)
    cryptoCipherAES_CBC.setLabel("AES - CBC - HW")
    cryptoCipherAES_CBC.setDescription("Enables Advanced Encryption Standard: Cipher Block Chaining")
    cryptoCipherAES_CBC.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoCipherAES_CBC.setDefaultValue(False)

    cryptoCipherAES_ECB = cryptoComponent.createBooleanSymbol("cryptoCipherAES_ECB", cryptoMenu)
    cryptoCipherAES_ECB.setLabel("AES - ECB - HW")
    cryptoCipherAES_ECB.setDescription("Enables Advanced Encryption Standard: Electronic Code Book")
    cryptoCipherAES_ECB.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoCipherAES_ECB.setDefaultValue(False)

    cryptoCipherAES_GCM = cryptoComponent.createBooleanSymbol("cryptoCipherAES_GCM", cryptoMenu)
    cryptoCipherAES_GCM.setLabel("AES - GCM - HW")
    cryptoCipherAES_GCM.setDescription("Enables Advanced Encryption Standard: Galois/Counter Mode")
    cryptoCipherAES_GCM.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoCipherAES_GCM.setDefaultValue(False)

    # Hashes
    cryptoHashMD5 = cryptoComponent.createBooleanSymbol("cryptoHashMD5", cryptoMenu)
    cryptoHashMD5.setLabel("Hash - MD5 - HW")
    cryptoHashMD5.setDescription("Enables Hashing function MD5")
    cryptoHashMD5.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoHashMD5.setDefaultValue(False)

    cryptoHashSHA1 = cryptoComponent.createBooleanSymbol("cryptoHashSHA1", cryptoMenu)
    cryptoHashSHA1.setLabel("Hash - SHA-1 - HW")
    cryptoHashSHA1.setDescription("Enables Hashing function SHA-1")
    cryptoHashSHA1.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoHashSHA1.setDefaultValue(False)

    cryptoHashSHA256 = cryptoComponent.createBooleanSymbol("cryptoHashSHA256", cryptoMenu)
    cryptoHashSHA256.setLabel("Hash - SHA-256 - HW")
    cryptoHashSHA256.setDescription("Enables Hashing function SHA-256")
    cryptoHashSHA256.setDependencies(onHWChangedDoLabel, ["cryptoHW"])
    cryptoHashSHA256.setDefaultValue(False)

    cryptoHashSHA384 = cryptoComponent.createBooleanSymbol("cryptoHashSHA384", cryptoMenu)
    cryptoHashSHA384.setLabel("Hash - SHA-384")
    cryptoHashSHA384.setDescription("Enables Hashing function SHA-384")
    cryptoHashSHA384.setDefaultValue(False)

    cryptoHashSHA512 = cryptoComponent.createBooleanSymbol("cryptoHashSHA512", cryptoMenu)
    cryptoHashSHA512.setLabel("Hash - SHA-512")
    cryptoHashSHA512.setDescription("Enables Hashing function SHA-512")
    cryptoHashSHA512.setDefaultValue(False)

    cryptoHashHMAC = cryptoComponent.createBooleanSymbol("cryptoHashHMAC", cryptoMenu)
    cryptoHashHMAC.setLabel("Hash - HMAC")
    cryptoHashHMAC.setDescription("Enables Keyed-Hash Message Authentication Code")
    cryptoHashHMAC.setDefaultValue(False)

    cryptoHuffman = cryptoComponent.createBooleanSymbol("cryptoHuffman", cryptoMenu)
    cryptoHuffman.setLabel("Huffman Coding")
    cryptoHuffman.setDescription("Enables Huffman Coding Compression")
    cryptoHuffman.setDefaultValue(False)

    # General Ciphers
    cryptoCipherECC = cryptoComponent.createBooleanSymbol("cryptoCipherECC", cryptoMenu)
    cryptoCipherECC.setLabel("Cipher - ECC")
    cryptoCipherECC.setDescription("Enables Eliptical Curve Cryptograpy")
    cryptoCipherECC.setDefaultValue(False)

    cryptoCipherRSA = cryptoComponent.createBooleanSymbol("cryptoCipherRSA", cryptoMenu)
    cryptoCipherRSA.setLabel("Cipher - RSA")
    cryptoCipherRSA.setDescription("Enables RSA Cryptosystem")
    cryptoCipherRSA.setDefaultValue(False)

    cryptoCipher3DES = cryptoComponent.createBooleanSymbol("cryptoCipher3DES", cryptoMenu)
    cryptoCipher3DES.setLabel("Cipher - DES/TDES")
    cryptoCipher3DES.setDescription("Enables (Triple) DES Cryptosystem")
    cryptoCipher3DES.setDefaultValue(False)

    # generate the config info and add it to list in system_config.h
    cryptoConfigInfo = cryptoComponent.createFileSymbol(None, None)
    cryptoConfigInfo.setSourcePath("templates/crypto_config.h.ftl")
    cryptoConfigInfo.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
    cryptoConfigInfo.setMarkup(True)
    cryptoConfigInfo.setType("STRING")

    # add the crypto.h to the crypto directory (not in src)
    includeFilename = cryptoComponent.createFileSymbol(None, None)
    includeFilename.setProjectPath("crypto/")
    includeFilename.setSourcePath("crypto.h")
    includeFilename.setDestPath("crypto/")
    includeFilename.setOutputName("crypto.h")
    includeFilename.setType("HEADER")

    fileList_common = [
        'aes.h', 'arc4.c', 'arc4.h', 'asm.c', 'asn.c', 'asn.h',
        'asn_public.h', 'async.c', 'async.h', 'certs_test.h', 'chacha.c',
        'chacha.h', 'chacha20_poly1305.c', 'chacha20_poly1305.h', 'cmac.c',
        'cmac.h', 'coding.c', 'coding.h', 'compress.c', 'compress.h',
        'crypto.c', 'curve25519.c', 'curve25519.h', 'des3.c', 'des3.h', 'dh.c',
        'dh.h', 'dsa.c', 'dsa.h', 'ecc.c', 'ecc.h', 'ecc_fp.c', 'ed25519.c',
        'ed25519.h', 'error-crypt.h', 'error.c', 
        #'evp.c', 
        'fe_low_mem.c', 'fe_operations.c', 'fe_operations.h', 'fips_test.h',
        # 'fp_mont_small.i', 'fp_mul_comba_12.i', 'fp_mul_comba_17.i',
        # 'fp_mul_comba_20.i', 'fp_mul_comba_24.i', 'fp_mul_comba_28.i',
        # 'fp_mul_comba_3.i', 'fp_mul_comba_32.i', 'fp_mul_comba_4.i',
        # 'fp_mul_comba_48.i', 'fp_mul_comba_6.i', 'fp_mul_comba_64.i',
        # 'fp_mul_comba_7.i', 'fp_mul_comba_8.i', 'fp_mul_comba_9.i',
        # 'fp_mul_comba_small_set.i', 'fp_sqr_comba_12.i', 'fp_sqr_comba_17.i',
        # 'fp_sqr_comba_20.i', 'fp_sqr_comba_24.i', 'fp_sqr_comba_28.i',
        # 'fp_sqr_comba_3.i', 'fp_sqr_comba_32.i', 'fp_sqr_comba_4.i',
        # 'fp_sqr_comba_48.i', 'fp_sqr_comba_6.i', 'fp_sqr_comba_64.i',
        # 'fp_sqr_comba_7.i', 'fp_sqr_comba_8.i', 'fp_sqr_comba_9.i',
        # 'fp_sqr_comba_small_set.i', 'fe_x25519_128.i', 'sha3_long.i',
        'ge_low_mem.c', 'ge_operations.c',
        'ge_operations.h', 'hash.c', 'hash.h', 'hc128.c', 'hc128.h', 'hmac.c',
        'hmac.h', 'idea.c', 'idea.h', 'integer.c', 'integer.h', 'logging.c',
        'logging.h', 'md2.c', 'md2.h', 'md4.c', 'md4.h', 'md5.c', 'md5.h',
        'memory.c', 'memory.h', 'mem_track.h', 'misc.c', 'misc.h',
        'mpi_class.h', 'mpi_superclass.h', 'pkcs12.c', 'pkcs12.h', 'pkcs7.c',
        'pkcs7.h', 'poly1305.c', 'poly1305.h', 'pwdbased.c', 'pwdbased.h',
        'rabbit.c', 'rabbit.h', 'random.c', 'random.h', 'ripemd.c', 'ripemd.h',
        'rsa.c', 'rsa.h', 'settings.h', 'sha.h', 
        'sha256.h', 'sha3.c', 'sha3.h', 'sha512.c', 'sha512.h',
        'signature.c', 'signature.h', 'srp.c', 'srp.h', 'ssl.h',
        'tfm.c', 'tfm.h', 'types.h', 'version.h', 'visibility.h',
        'wc_encrypt.c', 'wc_encrypt.h', 'wc_port.c', 'wc_port.h',
        'wolfevent.c', 'wolfevent.h', 'wolfmath.c', 'wolfmath.h'
    ]

    fileList_pic32c =    ['aes.c', 'sha.c', 'sha256.c', 'random.c']
    fileList_pic32c_HW = ['aes_pic32c.c', 'pic32c-hash.h', 'sha_pic32c.c', 'sha256_pic32c.c', 'random_pic32c.c']
    fileList_pic32m =    ['aes.c', 'sha.c', 'sha256.c', 'random.c', 'pic32mz-crypt.c', 'pic32mz-crypt.h']

    # add all common files as enabled and no callback
    for filename in fileList_common:
        addFileName(filename, cryptoComponent, True, None)

    # add acceleration files if needed
    if maskFamily.getValue() == "PIC32C":
        # These files are used for HW - notice the 'True' and 'Add' for enabled
        for filename in fileList_pic32c_HW:
            addFileName(filename, cryptoComponent, True, onHWChangedAdd)
        # These files are disabled initialy when the 'HW' is the default condition
        for filename in fileList_pic32c:
            addFileName(filename, cryptoComponent, False, onHWChangedSub)
    else:
        for filename in fileList_pic32m:
            addFileName(filename, cryptoComponent, True, onHWChangedAdd)

    # put header include into system_definitions.h - but should it be there?
    headerList = cryptoComponent.createListEntrySymbol(None, None)
    headerList.setTarget("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    headerList.addValue('#include "crypto/crypto.h"')


# callback for when HW Accelerate is toggled
def onHWChangedDoLabel(symbol, isHWAccelerated):
    if isHWAccelerated['value'] == False:
        if symbol.getLabel()[-2:] == "HW":
            symbol.setLabel(symbol.getLabel()[:-5])
    else:
        symbol.setLabel(symbol.getLabel() + " - HW")


# This callback enables files to be written depending on HW Acceleration Enabled
def onHWChangedAdd(filesymbol, isHWAccelerated):
    if isHWAccelerated['value'] == True:
        filesymbol.setEnabled(True)
    else:
        filesymbol.setEnabled(False)

# This callback disables files to be written depending on HW Acceleration Enabled
def onHWChangedSub(filesymbol, isHWAccelerated):
    if isHWAccelerated['value'] == True:
        filesymbol.setEnabled(False)
    else:
        filesymbol.setEnabled(True)


def onDependentComponentAdded(cryptoComponent, id, trngComponent):
	if id == "LIB_CRYPTO_Dependency":
		trngComponent.setSymbolValue("TRNG_Reserved", True, 1)

def onDependentComponentRemoved(cryptoComponent, id, trngComponent):
	if id == "LIB_CRYPTO_Dependency":
		trngComponent.clearSymbolValue("TRNG_Reserved")


# all files go into src/
def addFileName(fileName, component, enabled, callback):
    filename = component.createFileSymbol(None, None)
    filename.setProjectPath("crypto/")
    filename.setSourcePath("src/" + fileName)
    filename.setOutputName(fileName)

    if fileName[-2:] == '.h':
        filename.setDestPath("crypto/src/")
        filename.setType("HEADER")
    else:
        filename.setDestPath("crypto/src/")
        filename.setType("SOURCE")

    filename.setEnabled(enabled)
    if callback != None:
        filename.setDependencies(callback, ["cryptoHW"])

