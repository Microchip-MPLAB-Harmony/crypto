def loadModule():
    cryptoComponent = Module.CreateComponent("lib_crypto",
                                             "Cryptographic (Crypto) Library",
                                             "/Libraries/", "config/crypto.py")
    
    cryptoComponent.addCapability("LIB_CRYPTO", "LIB_CRYPTO")

    if Peripheral.moduleExists("TRNG"):
        cryptoComponent.addDependency("LIB_CRYPTO_Dependency", "TRNG")
