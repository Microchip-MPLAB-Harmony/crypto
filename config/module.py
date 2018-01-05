def loadModule():
	print("Load Module: Harmony Cryptographic (Crypto) Library")

	usartComponent = Module.CreateComponent("lib_crypto", "Cryptographic (Crypto) Library", "/Libraries/", "config/crypto.py")
	usartComponent.addCapability("LIB_CRYPTO")


