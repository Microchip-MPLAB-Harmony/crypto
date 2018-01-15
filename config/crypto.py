def instantiateComponent(cryptoComponent):
	cryptoHW = cryptoComponent.createBooleanSymbol("cryptoHW", None)
	cryptoHW.setLabel("Use Hardware Acceleration?")
	cryptoHW.setDescription("Enables hardware acceleration of cryptographic library")

	if (Peripheral.moduleExists("ICM")):
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
	cryptoRandom.setLabel("TRNG")
	cryptoRandom.setDescription("Enables True Random Number Generator")
	cryptoRandom.setDefaultValue(False)

	cryptoCipherAES_CTR = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CTR", cryptoMenu)
	cryptoCipherAES_CTR.setLabel("AES - CTR")
	cryptoCipherAES_CTR.setDescription("Enables Advanced Encryption Standard: Counter Mode")
	cryptoCipherAES_CTR.setDefaultValue(False)

	cryptoCipherAES_CBC = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CBC", cryptoMenu)
	cryptoCipherAES_CBC.setLabel("AES - CBC")
	cryptoCipherAES_CBC.setDescription("Enables Advanced Encryption Standard: Cipher Block Chaining")
	cryptoCipherAES_CBC.setDefaultValue(False)

	cryptoCipherAES_ECB = cryptoComponent.createBooleanSymbol("cryptoCipherAES_ECB", cryptoMenu)
	cryptoCipherAES_ECB.setLabel("AES - ECB")
	cryptoCipherAES_ECB.setDescription("Enables Advanced Encryption Standard: Electronic Code Book")
	cryptoCipherAES_ECB.setDefaultValue(False)

	cryptoCipherAES_GCM = cryptoComponent.createBooleanSymbol("cryptoCipherAES_GCM", cryptoMenu)
	cryptoCipherAES_GCM.setLabel("AES - GCM")
	cryptoCipherAES_GCM.setDescription("Enables Advanced Encryption Standard: Galois/Counter Mode")
	cryptoCipherAES_GCM.setDefaultValue(False)

	# Hashes
	cryptoHashMD5 = cryptoComponent.createBooleanSymbol("cryptoHashMD5", cryptoMenu)
	cryptoHashMD5.setLabel("Hash - MD5")
	cryptoHashMD5.setDescription("Enables Hashing function MD5")
	cryptoHashMD5.setDefaultValue(False)

	cryptoHashSHA1 = cryptoComponent.createBooleanSymbol("cryptoHashSHA1", cryptoMenu)
	cryptoHashSHA1.setLabel("Hash - SHA-1")
	cryptoHashSHA1.setDescription("Enables Hashing function SHA-1")
	cryptoHashSHA1.setDefaultValue(False)

	cryptoHashSHA256 = cryptoComponent.createBooleanSymbol("cryptoHashSHA256", cryptoMenu)
	cryptoHashSHA256.setLabel("Hash - SHA-256")
	cryptoHashSHA256.setDescription("Enables Hashing function SHA-1")
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

	configName = Variables.get("__CONFIGURATION_NAME")

	cryptoHeaderFile = cryptoComponent.createFileSymbol(None, None)
	cryptoHeaderFile.setSourcePath("templates/crypto_config.h.ftl")
	cryptoHeaderFile.setOutputName("config.h")
	cryptoHeaderFile.setDestPath("crypto/")
	cryptoHeaderFile.setProjectPath("config/" + configName + "/crypto/")
	cryptoHeaderFile.setMarkup(True)
	cryptoHeaderFile.setType("HEADER")

#	cryptoSourceFile = cryptoComponent.createFileSymbol(None, None)
#	cryptoSourceFile.setSourcePath("crypto/templates/crypto_config.c.ftl")
#	cryptoSourceFile.setOutputName("crypto.c")
#	cryptoSourceFile.setDestPath("crypto/")
#	cryptoSourceFile.setProjectPath("config/" + configName + "/crypto/")
#	cryptoSourceFile.setType("SOURCE")

def cryptoHWLabels(cryptoHW, test):
	if test.getValue() == True:
		print("HW Acceleration")
	else:
		print("SW Solution")


def onDependentComponentAdded(cryptoComponent, id, trngComponent):
	if id == "LIB_CRYPTO_Dependency":
		trngComponent.setSymbolValue("TRNG_Reserved", "TRNGReservedSymbol", True, 1)
