# Microchip MPLAB® Harmony 3 Release Notes
## Crypto Release v3.7
### Major Changes
- **Support for wolfCrypt/wolfSSL 4.7.0** The cryptographic library now has support for wolfSSL version 4.7.0
- **Pic32mz hw mutex fix** Fix for trying to hold the mutex twice
- **RNG memory leak fix** A deinitialize function was added to free RNG resources

## Dependencies
- **Core** - 3.9.0
- **CSP** - 3.9.0
- **wolfSSL** - 4.7.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.45
- **XC32** - v2.50
- **IAR** - 8.50.1

## Crypto Release v3.6.3
### Bug Fixes
- **Resolve OSAL Malloc/Free** Resolve build error with core v3.9

## Dependencies
- **Core** - 3.9.0
- **CSP** - 3.9.0
- **wolfSSL** - 4.5.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.45
- **XC32** - v2.50
- **IAR** - 8.50.1
- 
## Crypto Release v3.6.2
### Bug Fixes
- **Enabled Trust&Go Certificate loading** Enable load device certificate from Trust&Go TNGTLS
- **Driver Non-Blocking fix** Fixed Non Blocking code in BA414E Harmony Driver
- **Harmony 3 Scripting Fixes** Inter module scriping and configuring fixes

## Dependencies
- **Core** - 3.8.01
- **CSP** - 3.8.0
- **wolfSSL** - 4.5.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.40
- **XC32** - v3.41
- **IAR** - 8.50.1
- 
## Crypto Release v3.6.1
### Bug Fixes
- **Enabled TLS Downgrade options** Improved GUI for TLS Versions added Downgrade TLS Options
- **SNI Support Fixed with TLS1.3** Fixed SNI support when TLS1.3 is selected

## Dependencies
- **Core** - 3.8.01
- **CSP** - 3.8.0
- **wolfSSL** - 4.5.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.40
- **XC32** - v3.41
- **IAR** - 8.50.1

## Crypto Release v3.6.0
### Major Changes
- **Support for wolfCrypt/wolfSSL 4.5.0** The cryptographic library now has support for wolfSSL version 4.5.0
- **New Speed Test Application**  A new application has been added focusing on demonstrating the speed of the cryptographic hardware
- **Move Applications Into Their Own Repositories** Following the new MPLAB Harmony style all the applications have been moved into their own repositiories
- **More MHC Configuraiton Options**  The configuration options available in MHC have been expanded for both the wolfCrypt and wolfSSL libraries
- **Added Support for AES on the L22**  Turned on the support for the AES hardware module for the L22

## Dependencies
- **Core** - 3.8.01
- **CSP** - 3.8.0
- **wolfSSL** - 4.5.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.40
- **XC32** - v3.41
- **IAR** - 8.50.1

## Crypto Release v3.5.1
### Bug Fixes
- **PIC32MZ Hardware Hashing Disable** Added a wolfcrypt #define to the generated configuration when all Hash 'Support Hardware Acceleration' are disabled.

### Dependencies
- **Core** - 3.6.1
- **CSP** - 3.6.1
- **wolfSSL** - 4.3.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.30
- **XC32** - v3.20
- **IAR** - 8.40.1


## Crypto Release v3.5.0
### New Features
- **New Chip Support** - This release adds support for the SAML11 and PIC32MZ-W1 chips
- **wolfSSL Updated** - This release has been updated to be compativle with wolfSSL 4.3.0
- **Additional IAR Projects** - Two new projects have been added to support the SAME70 with the IAR IDE.

### Demonstration Application Relocation Notice
- **wolfSSL Demo Applications** these demonstrations have been moved to the net repository.  

### Dependencies
- **Core** - 3.6.1
- **CSP** - 3.6.1
- **wolfSSL** - 4.3.0
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.30
- **XC32** - v3.20
- **IAR** - 8.40.1

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 6 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 6 |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult) | 8 |
| [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit (Crypto)](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM320007-C) | 6 |
| [SAM9X60-EK Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/DT100126) | 6 |
| [SAML21 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/atsaml21-xpro-b) | 3 |
| [SAMRH71F20-EK Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/SAMRH71F20-EK) | 6 |
| PIC32MZ-W1 | 6 |
| [SAML11 Xplained Pro Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails/dm320205) | 4 |

### Known Issues
- The PIC32MZ-W1 public key cryptographic engine uses an asynchronous driver to access its functionality.  wolfCrypt and the Harmony 3 crypto library are both blocking.  To use the PIC32MZ-W1 with wolfCrypt and the Harmony 3 crypto library an RTOS must be used.

- During regeneration of the SAML11 projects the timer callback may be erased.  When regenerating the projects look for the inline comment on the lines that should not be erased

- When starting the MHC with the SAMRH71F20C the MPLAB-X project needs to be set to use SAMRH71F20B, after the MHC has been launched then the MPLAB-X project can be changed back to using the SAMRH71F20C

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.


## Crypto Release v3.4.1
### Bug Fixes
- **MHC Information** - Corrected version infomation used by the MHC.

## Crypto Release v3.4.0
### New Features
- **New Chip Support** - This release adds support for the SAMRH71 chips
- **MPLAB Harmony Crypt API and WolfCrypt Split** - Removed the vast majority of duplicated code between wolfcrypt and the MPLAB Harmony crypt library.  The Harmony Crypt API / Library now requires the wolfSSL package.  
  - **IAR Support** projects using IAR need to have the HAVE_CONFIG_H preprocessor option defined in the project options.
  - **MHC Configuration** The wolfCrypt module must be imported to be used with the MPLAB Harmony Crypto API
- **wolfCrypt/wolfSSL Upgraded** - MPLAB Harmony Crypt Library now supports wolfSSL 4.1.0-stable.
- **PUKCC/L Support** - Support for the public key engine on the SAME5x chips has been added.  This includes ECC and RSA support.

### Demonstration Application Relocation Notice
- **wolfSSL Demo Applications** these demonstrations are being moved to the net repository in the next release.  The demonstrations in this repository are now redundant and will be removed in the 3.5.0 release of the MPLAB Harmony Crypto library.  Please refer to the Net repository for these demonstrations from net version 3.5 onwards.
  - **IAR Demonstrations** these demonstrations have been moved and are currently maintained in the net repository.  

### Dependencies
- **Core** - 3.5.0
- **CSP** - 3.5.0
- **wolfSSL** - 4.1.0-stable
- **Net** - 3.4.0 For wolfSSL demonstrations
- **zlib** - v1.2.11 For compression support
- **MPLAB-X** - v5.25
- **XC32** - v3.20
- **IAR** - 8.40.1

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 6 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 8 |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult) | 12 |
| [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit (Crypto)](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM320007-C) | 12 |
| SAM9x60-EK | 6 |
| [SAML21 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/atsaml21-xpro-b) | 3 |
| SAMRH71-EK | 6 |


### Known Issues
- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.

- This release requires Harmony 3 Core Version 3.5 to regenerate the demonstrations.  This release also requires Net 3.4.0 to regenerate the wolfSSL demonstrations.


## Crypto Release v3.3.1
### Changes
- **License File** the license file has been updated
- **wolfSSL Dependencies Updated** this release relies on wolfSSL 3.15.7-stable.  This dependency is now reflected in the configuration files.
- **wolfSSL Demo Applications** these demonstrations are being moved to the net repository in the next release.  The demonstrations in this repository are now redundant and will be removed in the near future.  Please refer to the Net repository for these demonstrations from net version 3.5 onwards.

### Known Issues
- PUKCC Is Unsupported - The PUKCC peripheral for the SAME54 family, used for public key cryptography is not support yet.  This peripheral will be supported in future versions.

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.

- Demonstrations for using hardware cryptography and TLS are not included for the SAME54 platform.  The AES driver for the SAME54 is to be considered Alpha for this release.

- This release requires Harmony 3 Core Version 3.4 to regenerate the demonstrations.  This release also requires Net 3.3.0 to regenerate the wolfSSL demonstrations.

## Crypto Release v3.3.0
### New Features
- **New Chip Support** - This release adds support for the SAM9x60 and SAML21 chips.
- **Development kit and demo application support** - The following table provides number of demo application available for different development kits newly added in this release.

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 12 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 8 |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult) | 12 |
| [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit (Crypto)](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM320007-C) | 12 |
| SAM9x60-EK | 6 |
| [SAML21 Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/atsaml21-xpro-b) | 3 |

### Known Issues
- PUKCC Is Unsupported - The PUKCC peripheral for the SAME54 family, used for public key cryptography is not support yet.  This peripheral will be supported in future versions.

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.

- Demonstrations for using hardware cryptography and TLS are not included for the SAME54 platform.  The AES driver for the SAME54 is to be considered Alpha for this release.

- This release requires Harmony 3 Core Version 3.4 to regenerate the demonstrations.  This release also requires Net 3.3.0 to regenerate the wolfSSL demonstrations.



## Crypto Release v3.2.2
### New Features
- **wolfSSL Demonstrations** - This release adds wolfSSL applications to demostrate cryptography with TLS connections. SAME54, PIC32MZEF and SAMA5D2

- **Development kit and demo application support** - The following table provides number of demo application available for different development kits newly added in this release.

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 12 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 8 |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult) | 12 |
| [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit (Crypto)](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM320007-C) | 12 |

### Known Issues
- PUKCC Is Unsupported - The PUKCC peripheral for the SAME54 family, used for public key cryptography is not support yet.  This peripheral will be supported in future versions.

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.

- Demonstrations for using hardware cryptography and TLS are not included for the SAME54 platform.  The AES driver for the SAME54 is to be considered Alpha for this release.

- This release requires Harmony 3 Core Version 3.2.1 to regenerate the demonstrations.

- Often when regenerating the wolfSSL demonstrations the flash based key storage files will no be added to the project successfully by the MHC.  To work around this issue delete the network presentation layer from the project, readd it and reconfigure.  The flash based key storage file will be generated correctly after the component has been readded to the project.


## Crypto Release v3.2.1
### New Features
- **New part support** - This release indruduces initial support for [PIC32MZEF](https://www.microchip.com/design-centers/32-bit), families of 32-bit microcontrollers.
- **Hardware Cryptographic Accelerator Support** - This release adds support for the Cryptographic Accelerators in the SAME54, PIC32MZEF and SAMA5D2

- **Development kit and demo application support** - The following table provides number of demo application available for different development kits newly added in this release.

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 6 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 6 |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult) | 10 |
| [PIC32MZ Embedded Connectivity with FPU (EF) Starter Kit (Crypto)](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/DM320007-C) | 6 |

### Known Issues
- PUKCC Is Unsupported - The PUKCC peripheral for the SAME54 family, used for public key cryptography is not support yet.  This peripheral will be supported in future versions.

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.

## Crypto Release v3.2.0
### New Features
- **New part support** - This release introduces initial support for [SAM E54](https://www.microchip.com/design-centers/32-bit/sam-32-bit-mcus/sam-e-mcus), families of 32-bit microcontrollers and the [SAM A5D2](https://www.microchip.com/design-centers/32-bit-mpus/microprocessors/sama5/sama5d2-series) family of 32-bit microprocessors.

- **Wolf SSL/TLS Support** - This release introduces initial support for using the [wolfSSL library][https://www.wolfssl.com] for secure communications.  Current support is for the SAM E70.  **Note:** This support will be moved to the net package in the future.

- **Development kit and demo application support** - The following table provides number of demo application available for different development kits newly added in this release.

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 2 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 2 |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult) | 10 |


### Known Issues

The current known issues are as follows:

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

- ECC and RSA software calculations take upwards of 32 kBytes of stack, when using these algorithms with an RTOS plan accordingly.


### Development Tools

* [MPLAB X IDE v5.15](https://www.microchip.com/mplab/mplab-x-ide)
* [MPLAB XC32 C/C++ Compiler v2.15](https://www.microchip.com/mplab/compilers)
* [IAR Embedded Workbench for ARM v8.32 or above](https://www.iar.com/iar-embedded-workbench/#!?architecture=Arm)
* MPLAB X IDE plug-ins:
  * MPLAB Harmony Configurator (MHC) v3.2.0.0.

## Crypto Release v3.1.0
### New Features
- **New part support** - This release introduces initial support for [SAM E70](https://www.microchip.com/design-centers/32-bit/sam-32-bit-mcus/sam-e-mcus)

- **Development kit and demo application support** - The following table provides number of bare-metal and RTOS demo application available for different development kits.

| Development kits | Bare-metal applications | RTOS applications |
| --- | --- | --- |
| [SAM E70 Xplained Ultra Evaluation Kit](https://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=ATSAME70-XULT) | 4 | 2 |

### Known Issues

The current known issues are as follows:

- The device does not run after programming the device through EDBG. The user needs to reset the device manually using the reset button on the Xplained boards to run the firmware.

- **Programming and debugging through EDBG is not supported.** The ICD4 needs to be used for programming and debugging.

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

### Development Tools

- [MPLAB X IDE v5.10](https://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB XC32 C/C++ Compiler v2.15](https://www.microchip.com/mplab/compilers)
- MPLAB X IDE plug-ins:
  - MPLAB Harmony Configurator (MHC) v3.1.
