"""
Copyright (C) 2013-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
"""

def loadModule():
    cryptoComponent = Module.CreateComponent("lib_crypto",
                                             "Cryptographic (Crypto) Library",
                                             "/Libraries/", "config/crypto.py")
    cryptoComponent.addCapability("lib_crypto", "LIB_CRYPTO", None, True)
    cryptoComponent.addDependency("LIB_CRYPTO_WOLFCRYPT_Dependency", "LIB_WOLFCRYPT", False, True)
    
    ############################### Third Party wolfSSL Module #####################################
    tlsComponent = Module.CreateComponent("lib_wolfssl", "wolfSSL Library", "/Third Party Libraries/wolfSSL/", "config/wolfssl.py")
    tlsComponent.addCapability("lib_wolfssl","TLS Provider",None, False)    
    tlsComponent.addDependency("WolfSSL_Crypto_Dependency", "LIB_WOLFCRYPT", None, False, True)
    
    ############################### Third Party wolfCrypt Module ###################################
    wolfCryptComponent = Module.CreateComponent("lib_wolfcrypt", "wolfCrypt Library", "/Third Party Libraries/wolfSSL/", "config/wolfcrypt.py")
    wolfCryptComponent.addMultiCapability("lib_wolfcrypt", "LIB_WOLFCRYPT", "LIB_WOLFCRYPT")
    wolfCryptComponent.addDependency("LIB_WOLFCRYPT_Dependency", "SYS_TIME", True, False)
    wolfCryptComponent.addDependency("LIB_WOLFCRYPT_HCORE_Dependency", "Core Service", True, True)
    wolfCryptComponent.addDependency("LIB_WOLFCRYPT_ZLIB_Dependency", "LIB_ZLIB", False, False)

    ############################### Third Party zlib Module ###################################
    zlibComponent = Module.CreateComponent("lib_zlib", "zLib Library", "/Third Party Libraries", "config/zlib.py")
    zlibComponent.addMultiCapability("lib_zlib", "LIB_ZLIB", "LIB_ZLIB")
    
    ############################### BA414E Driver Module ###################################
    periphNode = ATDF.getNode("/avr-tools-device-file/devices/device/peripherals")
    modules = periphNode.getChildren()
    for module in modules:
        if module.getAttribute("name") == "BA414E":
            wolfCryptComponent.addDependency("LIB_CRYPTO_BA414E_Dependency", "DRV_BA414E", False, False)
            ba414eComponent = Module.CreateComponent("drv_ba414e", "BA414E", "/Harmony/Drivers/Cryptographic Accelerators", "config/ba414e.py")
            ba414eComponent.addMultiCapability("drv_ba414e", "DRV_BA414E", "DRV_BA414E")


