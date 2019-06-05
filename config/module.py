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
def loadModule():
    cryptoComponent = Module.CreateComponent("lib_crypto",
                                             "Cryptographic (Crypto) Library",
                                             "/Libraries/", "config/crypto.py")
    cryptoComponent.addCapability("lib_crypto", "LIB_CRYPTO", None, True)

    cryptoComponent.addDependency("LIB_CRYPTO_TIME_Dependency", "SYS_TIME", True, True)
    
    ############################### Third Party wolfSSL Module #####################################
	tlsComponent = Module.CreateComponent("lib_wolfssl", "wolfSSL Library", "/Third Party Libraries/wolfSSL/", "config/wolfssl.py")
    tlsComponent.addCapability("lib_wolfssl","TLS Provider",None, False)    
    tlsComponent.addDependency("WolfSSL_Crypto_Dependency", "LIB_CRYPTO", None, True, False)
    