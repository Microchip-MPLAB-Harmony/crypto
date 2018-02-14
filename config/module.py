def loadModule():
    cryptoComponent = Module.CreateComponent("lib_crypto",
                                             "Cryptographic (Crypto) Library",
                                             "/Libraries/", "config/crypto.py")
    cryptoComponent.addCapability("lib_crypto", "LIB_CRYPTO")

    if Peripheral.moduleExists("TRNG"):
        cryptoComponent.addDependency("LIB_CRYPTO_Dependency", "TRNG")
