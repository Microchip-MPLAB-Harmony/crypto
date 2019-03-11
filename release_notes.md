# Microchip MPLAB® Harmony 3 Release Notes
## Core Release v3.2.0
### New Features
- **New part support** - This release introduces initial support for [SAM E54](https://www.microchip.com/design-centers/32-bit/sam-32-bit-mcus/sam-e-mcus), families of 32-bit microcontrollers and the [SAM A5D2](https://www.microchip.com/design-centers/32-bit-mpus/microprocessors/sama5/sama5d2-series) family of 32-bit microprocessors.

- **Wolf SSL/TLS Support** - This release introduces initial support for using the [wolfSSL library][https://www.wolfssl.com] for secure communications.  Current support is for the SAM E70.  **Note:** This support will be moved to the net package in the future.

- **Development kit and demo application support** - The following table provides number of demo application available for different development kits newly added in this release.

| Development kits | Applications |
| --- | --- | --- |
| [ATSAMA5D2C-XULT](https://www.microchip.com/Developmenttools/ProductDetails/ATSAMA5D2C-XULT) | 2 |
| [SAM E54 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO) | 2 |
| [SAM E70 Xplained Ultra Evaluation Kit][https://www.microchip.com/developmenttools/ProductDetails/atsamv71-xult] | 10 |


### Known Issues

The current known issues are as follows:

- The ICD4 loads the reset line of the SAM V71 Xplained Ultra board. Do not press reset button on the Xplained Ultra board while ICD4 is connected to the board.

- Interactive help using the Show User Manual Entry in the Right-click menu for configuration options provided by this module is not yet available from within the MPLAB Harmony Configurator (MHC).  Please see the &quot;Configuring the Library&quot; section in the help documentation in the doc folder for this module instead.  Help is available in both CHM and PDF formats.

- ATSAMA5D2C demo applications build with a warning message: ```Warning[Pe111]: statement is unreachable for return ( EXIT_FAILURE ); statement of main() in IAR```

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