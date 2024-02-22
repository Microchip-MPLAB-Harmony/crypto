#/*****************************************************************************
# Copyright (C) 2013-2023 Microchip Technology Inc. and its subsidiaries.
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
def loadModule():


    ########################## CRYPTO Module ###############################
    cryptoComponent = Module.CreateComponent(
            "lib_crypto",
            "Cryptographic (Crypto) Library",
            "/Libraries/", "config/crypto.py")
    cryptoComponent.addCapability(
            "lib_crypto", "LIB_CRYPTO", None, True)
    cryptoComponent.addDependency(
            "LIB_CRYPTO_WOLFCRYPT_Dependency", "LIB_WOLFCRYPT", False, True)

    #===========================================================================
    #===========================Dependent Modules===============================
    #===========================================================================

    ####################### Third Party wolfSSL Module #####################
    tlsComponent = Module.CreateComponent(
            "lib_wolfssl",
            "wolfSSL Library",
            "/Third Party Libraries/wolfSSL/",
            "config/wolfssl.py")
    tlsComponent.addCapability("lib_wolfssl","TLS Provider",None, False)
    tlsComponent.addDependency(
            "WolfSSL_Crypto_Dependency", "LIB_WOLFCRYPT", None, False, True)

    ####################### Third Party wolfCrypt Module ####################
    wolfCryptComponent = Module.CreateComponent(
            "lib_wolfcrypt",
            "wolfCrypt Library",
            "/Third Party Libraries/wolfSSL/",
            "config/wolfcrypt.py")
    wolfCryptComponent.addMultiCapability(
            "lib_wolfcrypt", "LIB_WOLFCRYPT", "LIB_WOLFCRYPT")
    wolfCryptComponent.addDependency(
            "LIB_WOLFCRYPT_Dependency", "SYS_TIME", True, False)
    wolfCryptComponent.addDependency(
            "LIB_WOLFCRYPT_HCORE_Dependency", "Core Service", True, True)
    wolfCryptComponent.addDependency(
            "LIB_WOLFCRYPT_ZLIB_Dependency", "LIB_ZLIB", False, False)

    ##################### Third Party zlib Module ###########################
    zlibComponent = Module.CreateComponent(
            "lib_zlib", "zLib Library",
            "/Third Party Libraries",
            "config/zlib.py")
    zlibComponent.addMultiCapability("lib_zlib", "LIB_ZLIB", "LIB_ZLIB")

    #===========================================================================
    #=============================== Drivers====================================
    #===========================================================================

    ####################### BA414E Driver Module ############################
    periphNode = ATDF.getNode(
            "/avr-tools-device-file/devices/device/peripherals")
    modules = periphNode.getChildren()
    for module in modules:
        if module.getAttribute("name") == "BA414E":
            wolfCryptComponent.addDependency(
                    "LIB_CRYPTO_BA414E_Dependency", "DRV_BA414E", False, False)
            ba414eComponent = Module.CreateComponent(
                    "drv_ba414e", "BA414E", 
                    "/Harmony/Drivers/Cryptographic Accelerators", 
                    "config/ba414e.py")
            ba414eComponent.addMultiCapability(
                    "drv_ba414e", "DRV_BA414E", "DRV_BA414E")
