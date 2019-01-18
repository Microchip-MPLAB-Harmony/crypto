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

def instantiateComponent(cryptoComponent):
	cryptoMicrochip = cryptoComponent.createBooleanSymbol("cryptoMicrochip", None)
	cryptoMicrochip.setLabel("Use Microchip Crypto")
	cryptoMicrochip.setDescription("Enables hardware acceleration of cryptographic library")
 	cryptoMicrochip.setDependencies(onWolfsslChangedCryptoStatus, ["cryptoIsWolfsslEnabled"])
	cryptoMicrochip.setVisible(False)
	cryptoMicrochip.setDefaultValue(True)

	cryptoHW = cryptoComponent.createBooleanSymbol("cryptoHW", None)
	cryptoHW.setLabel("Use Hardware Acceleration?")
	cryptoHW.setDescription("Enables hardware acceleration of cryptographic library")
 	cryptoHW.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])

	if Peripheral.moduleExists("ICM"):
		cryptoHW.setVisible(True)
		cryptoHW.setDefaultValue(True)
	else:
		cryptoHW.setVisible(False)
		cryptoHW.setDefaultValue(False)

	maskFamily = cryptoComponent.createStringSymbol("maskFamily", None)
	maskFamily.setVisible(False)
	if "PIC32M" in Variables.get("__PROCESSOR"):
		maskFamily.setDefaultValue("PIC32M")
	else:
		maskFamily.setDefaultValue("SAME70")

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
	
	# Keep track of wolfSSL enabled/disabled. This is needed when the message handler
	# receives a notification from wolfSSL that wolfSSL has been enabled or disabled.
	cryptoIsWolfsslEnabled = cryptoComponent.createBooleanSymbol("cryptoIsWolfsslEnabled",None)
	cryptoIsWolfsslEnabled.setVisible(False)
	Database.setSymbolValue("lib_crypto","cryptoIsWolfsslEnabled",False,1)
	
	# message to display if wolfSSL is enabled
	cryptoMessage = cryptoComponent.createCommentSymbol("cryptoMessage", None)
	cryptoMessage.setLabel("Crypto library is disabled. Configure through 3rd party wolfSSL component.")
	cryptoMessage.setVisible(False)
	cryptoMessage.setDependencies(onWolfsslChangedComment, ["cryptoIsWolfsslEnabled"])

	# use Microchip crypto lib until notified otherwise by wolfSSL
	useMicrochipCrypto = True
	
	#is wolfSSL enabled?
	res = Database.sendMessage("lib_wolfssl", "isWolfsslEnabled", {})
	
	if res is not None and res["wolfsslEnabled"] is True:
		Database.setSymbolValue("lib_crypto","cryptoIsWolfsslEnabled",True,1)
		cryptoMessage.setVisible(True)
		useMicrochipCrypto = False
		cryptoMicrochip.setValue (False,1)
	
	cryptoHW.setVisible(useMicrochipCrypto)
	
	cryptoMenu = cryptoComponent.createMenuSymbol("crypto_menu", None)
	cryptoMenu.setLabel("Crypto Settings")
	cryptoMenu.setVisible(useMicrochipCrypto)
	cryptoMenu.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	
	cryptoRandom = cryptoComponent.createBooleanSymbol("cryptoRandom", cryptoMenu)
	cryptoRandom.setLabel("TRNG - HW")
	cryptoRandom.setDescription("Enables True Random Number Generator")
	cryptoRandom.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoRandom.setDefaultValue(False)
	cryptoRandom.setVisible(useMicrochipCrypto)

	cryptoCipherAES_CTR = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CTR", cryptoMenu)
	cryptoCipherAES_CTR.setLabel("AES - CTR - HW")
	cryptoCipherAES_CTR.setDescription("Enables Advanced Encryption Standard: Counter Mode")
	cryptoCipherAES_CTR.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoCipherAES_CTR.setDefaultValue(False)
	cryptoCipherAES_CTR.setVisible(useMicrochipCrypto)

	cryptoCipherAES_CBC = cryptoComponent.createBooleanSymbol("cryptoCipherAES_CBC", cryptoMenu)
	cryptoCipherAES_CBC.setLabel("AES - CBC - HW")
	cryptoCipherAES_CBC.setDescription("Enables Advanced Encryption Standard: Cipher Block Chaining")
	cryptoCipherAES_CBC.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoCipherAES_CBC.setDefaultValue(False)
	cryptoCipherAES_CBC.setVisible(useMicrochipCrypto)

	cryptoCipherAES_ECB = cryptoComponent.createBooleanSymbol("cryptoCipherAES_ECB", cryptoMenu)
	cryptoCipherAES_ECB.setLabel("AES - ECB - HW")
	cryptoCipherAES_ECB.setDescription("Enables Advanced Encryption Standard: Electronic Code Book")
	cryptoCipherAES_ECB.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoCipherAES_ECB.setDefaultValue(False)
	cryptoCipherAES_ECB.setVisible(useMicrochipCrypto)

	cryptoCipherAES_GCM = cryptoComponent.createBooleanSymbol("cryptoCipherAES_GCM", cryptoMenu)
	cryptoCipherAES_GCM.setLabel("AES - GCM - HW")
	cryptoCipherAES_GCM.setDescription("Enables Advanced Encryption Standard: Galois/Counter Mode")
	cryptoCipherAES_GCM.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoCipherAES_GCM.setDefaultValue(False)
	cryptoCipherAES_GCM.setVisible(useMicrochipCrypto)

	# Hashes
	cryptoHashMD5 = cryptoComponent.createBooleanSymbol("cryptoHashMD5", cryptoMenu)
	cryptoHashMD5.setLabel("Hash - MD5 - HW")
	cryptoHashMD5.setDescription("Enables Hashing function MD5")
	cryptoHashMD5.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoHashMD5.setDefaultValue(False)
	cryptoHashMD5.setVisible(useMicrochipCrypto)

	cryptoHashSHA1 = cryptoComponent.createBooleanSymbol("cryptoHashSHA1", cryptoMenu)
	cryptoHashSHA1.setLabel("Hash - SHA-1 - HW")
	cryptoHashSHA1.setDescription("Enables Hashing function SHA-1")
	cryptoHashSHA1.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoHashSHA1.setDefaultValue(False)
	cryptoHashSHA1.setVisible(useMicrochipCrypto)

	cryptoHashSHA256 = cryptoComponent.createBooleanSymbol("cryptoHashSHA256", cryptoMenu)
	cryptoHashSHA256.setLabel("Hash - SHA-256 - HW")
	cryptoHashSHA256.setDescription("Enables Hashing function SHA-256")
	cryptoHashSHA256.setDependencies(hwSwMenuHandler, ["cryptoHW","cryptoIsWolfsslEnabled"])
	cryptoHashSHA256.setDefaultValue(False)
	cryptoHashSHA256.setVisible(useMicrochipCrypto)

	cryptoHashSHA384 = cryptoComponent.createBooleanSymbol("cryptoHashSHA384", cryptoMenu)
	cryptoHashSHA384.setLabel("Hash - SHA-384")
	cryptoHashSHA384.setDescription("Enables Hashing function SHA-384")
	cryptoHashSHA384.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoHashSHA384.setDefaultValue(False)
	cryptoHashSHA384.setVisible(useMicrochipCrypto)

	cryptoHashSHA512 = cryptoComponent.createBooleanSymbol("cryptoHashSHA512", cryptoMenu)
	cryptoHashSHA512.setLabel("Hash - SHA-512")
	cryptoHashSHA512.setDescription("Enables Hashing function SHA-512")
	cryptoHashSHA512.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoHashSHA512.setDefaultValue(False)
	cryptoHashSHA512.setVisible(useMicrochipCrypto)

	cryptoHashHMAC = cryptoComponent.createBooleanSymbol("cryptoHashHMAC", cryptoMenu)
	cryptoHashHMAC.setLabel("Hash - HMAC")
	cryptoHashHMAC.setDescription("Enables Keyed-Hash Message Authentication Code")
	cryptoHashHMAC.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoHashHMAC.setDefaultValue(False)
	cryptoHashHMAC.setVisible(useMicrochipCrypto)

	cryptoHuffman = cryptoComponent.createBooleanSymbol("cryptoHuffman", cryptoMenu)
	cryptoHuffman.setLabel("Huffman Coding")
	cryptoHuffman.setDescription("Enables Huffman Coding Compression")
	cryptoHuffman.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoHuffman.setDefaultValue(False)
	cryptoHuffman.setVisible(useMicrochipCrypto)

	# General Ciphers
	cryptoCipherECC = cryptoComponent.createBooleanSymbol("cryptoCipherECC", cryptoMenu)
	cryptoCipherECC.setLabel("Cipher - ECC")
	cryptoCipherECC.setDescription("Enables Eliptical Curve Cryptograpy")
	cryptoCipherECC.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoCipherECC.setDefaultValue(False)
	cryptoCipherECC.setVisible(useMicrochipCrypto)

	cryptoCipherRSA = cryptoComponent.createBooleanSymbol("cryptoCipherRSA", cryptoMenu)
	cryptoCipherRSA.setLabel("Cipher - RSA")
	cryptoCipherRSA.setDescription("Enables RSA Cryptosystem")
	cryptoCipherRSA.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoCipherRSA.setDefaultValue(False)
	cryptoCipherRSA.setVisible(useMicrochipCrypto)

	cryptoCipher3DES = cryptoComponent.createBooleanSymbol("cryptoCipher3DES", cryptoMenu)
	cryptoCipher3DES.setLabel("Cipher - DES/TDES")
	cryptoCipher3DES.setDescription("Enables (Triple) DES Cryptosystem")
	cryptoCipher3DES.setDependencies(onWolfsslChangedDoMenu, ["cryptoIsWolfsslEnabled"])
	cryptoCipher3DES.setDefaultValue(False)
	cryptoCipher3DES.setVisible(useMicrochipCrypto)
		
	# generate the config info and add it to list in configuration.h
	cryptoConfigInfo = cryptoComponent.createFileSymbol("cryptoConfigInfo", None)
	cryptoConfigInfo.setSourcePath("templates/crypto_config.h.ftl")
	cryptoConfigInfo.setOutputName("core.LIST_SYSTEM_CONFIG_H_MIDDLEWARE_CONFIGURATION")
	cryptoConfigInfo.setMarkup(True)
	cryptoConfigInfo.setType("STRING")

	fileList_common = [
		'aes.h', 'arc4.c', 'arc4.h', 'asm.c', 'asn.c', 'asn.h',
		'asn_public.h', 'async.c', 'async.h', 'certs_test.h', 'chacha.c',
		'chacha.h', 'chacha20_poly1305.c', 'chacha20_poly1305.h', 'cmac.c',
		'cmac.h', 'coding.c', 'coding.h', 'compress.c', 'compress.h',
		'cpuid.h','curve25519.c', 'curve25519.h', 'des3.c', 'des3.h', 'dh.c',
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
		'rabbit.c', 'rabbit.h', 'random.h', 'ripemd.c', 'ripemd.h',
		'rsa.c', 'rsa.h', 'settings.h', 'sha.h',
		'sha256.h', 'sha3.c', 'sha3.h', 'sha512.c', 'sha512.h',
		'signature.c', 'signature.h', 'srp.c', 'srp.h', 'ssl.h',
		'tfm.c', 'tfm.h', 'types.h', 'version.h', 'visibility.h',
		'wc_encrypt.c', 'wc_encrypt.h', 'wc_port.c', 'wc_port.h',
		'wolfevent.c', 'wolfevent.h', 'wolfmath.c', 'wolfmath.h'
	]
	
	fileList_zlib =			['crc32.h','deflate.h','inffast.h','inffixed.h','inflate.h','inftrees.h',
							'trees.h','adler32.c','crc32.c','deflate.c','zconf.h','zutil.h','zlib.h',
							'inflate.c','trees.c','gzguts.h','zutil.c','inftrees.c','inffast.c'
							]
	fileList_same70_common =	['random_same70.c']
	fileList_same70_SW =	['aes.c', 'sha.c', 'sha256.c', 'random.c']
	fileList_same70_HW =	['aes_same70.c', 'same70-hash.h', 'sha_same70.c', 'sha256_same70.c']
	fileList_pic32m =		['aes.c', 'sha.c', 'sha256.c', 'random.c', 'pic32mz-crypt.c', 'pic32mz-crypt.h']

	
	# add all common files 
	for filename in fileList_common:
		addFileName(filename, cryptoComponent, "src/", "crypto/src/", useMicrochipCrypto, fileMchpCryptoEnableHandler)

	# add all zlib files  
	for filename in fileList_zlib:
		addFileName(filename, cryptoComponent, "src/zlib-1.2.7/", "crypto/src/zlib-1.2.7/", useMicrochipCrypto, fileMchpCryptoEnableHandler)

	# add acceleration files if needed
	if maskFamily.getValue() == "SAME70":
		for filename in fileList_same70_common:
			addFileName(filename, cryptoComponent, "src/", "crypto/src/", useMicrochipCrypto, fileMchpCryptoEnableHandler)
		# These files are used for HW - note that useMicrochipCrypto == 'True' for enabled
		for filename in fileList_same70_HW:
			addFileName(filename, cryptoComponent, "src/", "crypto/src/", useMicrochipCrypto, fileEnableHandler)
		# These files are disabled initially when the 'HW' is the default condition
		for filename in fileList_same70_SW:
			addFileName(filename, cryptoComponent, "src/", "crypto/src/", False, fileEnableSame70SwHandler)
#	else:
#		for filename in fileList_pic32m:
#			addFileName(filename, cryptoComponent, "src/", "crypto/src/", useMicrochipCrypto, fileEnableHandler)


# message handler
def handleMessage(messageID, args):
	if args["wolfsslEnabled"] is True:
		#hide crypto menu and display comment
		Database.setSymbolValue("lib_crypto","cryptoIsWolfsslEnabled",True,1)
	else:
		#display crypto menu
		Database.setSymbolValue("lib_crypto","cryptoIsWolfsslEnabled",False,1)
	return{}

def hwSwMenuHandler(symbol, event):
	if event["id"] == "cryptoHW":
		onHWChangedDoLabel(symbol, event)
	else:
		onWolfsslChangedDoMenu(symbol, event)

# callback for when HW Accelerate is toggled
def onHWChangedDoLabel(symbol, isHWAccelerated):
	if isHWAccelerated['value'] == False:
		if symbol.getLabel()[-2:] == "HW":
			symbol.setLabel(symbol.getLabel()[:-5])
	else:
		symbol.setLabel(symbol.getLabel() + " - HW")
		
# callback for when wolfSSL is toggled
def onWolfsslChangedDoMenu(symbol, isWolfsslEnabled):
	if isWolfsslEnabled['value'] == True:
		symbol.setVisible(False)
	else:
		symbol.setVisible(True)
		
# callback to display comment when wolfSSL is toggled
def onWolfsslChangedComment(symbol, isWolfsslEnabled):
	if isWolfsslEnabled['value'] == True:
		symbol.setVisible(True)
	else:
		symbol.setVisible(False)

# callback for when wolfSSL is toggled
def onWolfsslChangedCryptoStatus(symbol, isWolfsslEnabled):
	if isWolfsslEnabled['value'] == True:
		symbol.setValue(False,1)
	else:
		symbol.setValue(True,1)

# callback for when wolfSSL is toggled.
# Enables/disables fileList_common and fileList_zlib files.
# If event is "cryptoHW" then do nothing. These files should
# always be enabled regardless of crypto HW or SW as long as
# Microchip Crypto is enabled.
def fileMchpCryptoEnableHandler(symbol, event):
	if event["id"] == "cryptoIsWolfsslEnabled":
		onWolfsslChangedAdd(symbol, event)

def fileEnableHandler(symbol, event):
	if event["id"] == "cryptoHW":
		onHWChangedAdd(symbol, event)
	else:
		onWolfsslChangedAdd(symbol, event)

# This callback enables files to be written depending on HW Acceleration Enabled
def onHWChangedAdd(filesymbol, isHWAccelerated):
	if isHWAccelerated['value'] == True:
		filesymbol.setEnabled(True)
	else:
		filesymbol.setEnabled(False)

# This callback enables files to be written depending on wolfSSL Enabled
def onWolfsslChangedAdd(filesymbol, isWolfsslEnabled):
	if isWolfsslEnabled['value'] == True:
		filesymbol.setEnabled(False)
	else:
		filesymbol.setEnabled(True)

def fileEnableSame70SwHandler(symbol, event):
	if event["id"] == "cryptoHW":
		onHWChangedSub(symbol, event)
	else:
		onWolfsslChangedAdd(symbol, event)

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

# all files go into or under src/
def addFileName(fileName, component, srcPath, destPath, enabled, callback):
	filename = component.createFileSymbol(fileName.replace('.', '_'), None)
	filename.setProjectPath("config/" + Variables.get("__CONFIGURATION_NAME") + "/crypto")
	filename.setSourcePath(srcPath + fileName)
	filename.setOutputName(fileName)

	if fileName[-2:] == '.h':
		filename.setDestPath(destPath)
		filename.setType("HEADER")
	else:
		filename.setDestPath(destPath)
		filename.setType("SOURCE")

	filename.setEnabled(enabled)
	if callback != None:
		filename.setDependencies(callback, ["cryptoHW","cryptoIsWolfsslEnabled"])
		

			


