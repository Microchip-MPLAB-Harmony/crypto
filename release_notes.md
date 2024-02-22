![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Crypto Release v4.0.0

### New Features
- **Support for updated wolfCrypt/wolfSSL** The cryptographic library now has support for wolfSSL version 5.6.6
- **MCC Configuration Options** Initial release of Crypto V4 API Library supporting
1.  Hash Algorithms:

    MD5  
    RIPEMD-160  
    SHA-1  
    SHA-2: SHA2-224, SHA2-256, SHA2-384, SHA2-512, SHA2-512/224, SHA2-512/256  
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

7.  RNG (Random Number Generator)

    Pseudo RNG


### Bug fixes
- N/A

### Known Issues
1. Line 1885 of wolfcrypt library file src/thirdparty/wolfssl/wolfcrypt/src/dh.c generates a compiler error. This line
of code must be moved to the line below the line that follows to prevent this
error.  
2. There are a few other errors associated with the V5.6.6 WolfSSL that
are corrected  using the latest master of 2/12/24 Commit 06f04def1b187. 

### Development Tools

- [MPLAB® X IDE v6.20](https://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® XC32 C/C++ Compiler v4.30](https://www.microchip.com/mplab/compilers)
- MPLAB® X IDE plug-ins:
    - MPLAB® Code Configurator v5.4

### Notes
- N/A








