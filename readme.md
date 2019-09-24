# MPLAB® Harmony 3 Crypto Module

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating
embedded firmware solutions for Microchip 32-bit SAM and PIC microcontroller
and microprocessor devices.  Refer to the following links for more information.
 - [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)
 - [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
 - [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
 - [Microchip MPLAB Harmony](https://www.microchip.com/mplab/mplab-harmony)
 - [Microchip MPLAB Harmony Pages](https://microchip-mplab-harmony.github.io/)

This repository contains the crypto module for the MPLAB® Harmony 3 Embedded
Software Development Framework.  The crypto module contains the Harmony 3 API
for cryptography, the Microchip 32-bit SAM drivers for hardware cryptographic
acceleration, and the deltas/patch for the wolfCrypt/wolfSSL library to use
the hardware accelerators.

**Note:** Microchip Technology Inc. and wolfSSL Inc. have entered a ten year
agreement in 2019 to allow the use of wolfCrypt (excluding FIPS) inside of 
MPLAB Harmony 3 projects.

 - [Release Notes](./release_notes.md)
 - [MPLAB Harmony 3 Crypto Wiki](https://github.com/Microchip-MPLAB-Harmony/crypto/wiki)
 - [MPLAB Harmony 3 Crypto API Help](https://microchip-mplab-harmony.github.io/crypto)

# Contents Summary

| Folder    | Description                                                |
|-----------|------------------------------------------------------------|
| apps      | Example applications for crypto library components           |
| config    | Crypto module configuration scripts                          |
| docs      | Crypto module library help documentation                     |
| src       | MPLAB Harmony crypto library source code                   |
| templates | Crypto file templates                                      |

# Dependencies
- **Core** - 3.5.0
- **CSP** - 3.5.0
- **wolfSSL** - 4.1.0-stable
- **Net** - 3.4.0 For wolfSSL demonstration