![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Crypto Release v4.0.0-E1

### New Features
- **New API's for all Cryptographic Operations** This is an engineering release supporting a new Harmony Crypto Library featuring a new API and optimized code base. No Hardware acceleration is available in this Engineering release.
- **Support for updated wolfCrypt/wolfSSL** The cryptographic library now has support for wolfSSL version 5.6.6 or later.
- **MCC Configuration Options** Initial release of Crypto V4 API Library supporting the following alogorthims

    1.  Hash Algorithms:

            MD5  
            RIPEMD-160  
            SHA-1  
            SHA-2: SHA2-224, SHA2-256, SHA2-384, SHA2-512  
            SHA-3: SHA3-224, SHA3-256, SHA3-384, SHA3-512, SHAKE-128, SHAKE-256  
            BLAKE: Blake2b, Blake2s  

    2.  Symmetric Algorithms:

            TDES/3DES: ECB, CBC  
            AES: ECB, CBC, OFB, CTR, XTS, CFB1, CFB8, CFB64, CFB128  
            Camellia: ECB, CBC, OFB, CTR, XTS, CFB1, CFB8, CFB64, CFB128  
            AES-KW  
            ChaCha20  

    3.  MAC Algorithms (Message authentication code):

            AES: CMAC

    4.  Digital Signature Algorithms:

            ECDSA

    5.  AEAD  Algorithms (Authenticated Encryption With Associated Data):

            AES-CCM  
            AES-EAX

    6.  KAS Algorithms(Key Agreement Scheme):

            ECDH

    7.  RNG (Random Number Generator) - Requires SYSTICK to be enabled

            Pseudo RNG


### Bug fixes
- N/A

### Known Issues
1. It is required to use the v5.6.7-E1 tag of wolfSSL with this repository. 

### Development Tools

- [MPLAB® X IDE v6.20](https://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® XC32 C/C++ Compiler v4.30](https://www.microchip.com/mplab/compilers)
- MPLAB® X IDE plug-ins:
    - MPLAB® Code Configurator v5.4

### Notes
- N/A








