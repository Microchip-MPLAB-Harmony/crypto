/*******************************************************************************
  Encrypt/decrypt Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    sam_l11_secure_init.c

  Summary:
    This file provides SECURE TrustZone initialization for basic
    demonstration applications. 

  Description:
    This code provides SECURE TrustZone initialization for basic
    demonstration applications, in lieu of full Harmony3 support
    for the SAM L11 Xplained Pro platform (DM320205). In addition
    to this file, the project configuration must be manually
    amended to define linker definitions for AS, RS and ANSC
    as described below.
    
    It is expected that the basic SAML11 configuration is generated
    by Harmony3, and that any linker definitions will be reset
    to the default settings requiring the manual update.
 *******************************************************************************/

/* The following is taken from the XC32 compiler V2.2 release notes.
 * http://ww1.microchip.com/downloads/en/DeviceDoc/xc32-v2.20-full-install-release-notes.html
 * 
 * Linker Macros controlling memory regions for TrustZone
 * 
 * Linking either the secure or non-secure application requires that the 
 * linker know the address and length of secure, non-secure, and non-secure 
 * callable memory regions. The following are the preprocessor definitions 
 * that are used to set and control memory zones for TrustZone when linking 
 * TrustZone applications. They are passed as -Wl,-DNAME[=value].
 * 
 * When building a non-secure application, the following preprocessor 
 * definitions affect the linker script.
 * BOOTPROT=size (optional): Defines the boot protections size in bytes. 
 *                           The default value is 0 if not provided.
 * AS=size (recommended): Defines the flash secure application size, in bytes. 
 *                        Defaults to 50% of ROM if not provided.
 * RS=size (recommended): Defines the size of secure RAM, in bytes. 
 *                        Defaults to 50% of RAM if not provided.
 * 
 * When building a secure application, the following preprocessor definitions 
 * affect the linker script.
 * SECURE (required): Use the memory layout for a secure application.
 * BOOTPROT=size (optional): Defines the boot protections size in bytes. 
 *                           The default value is 0 if not provided.
 * AS=size (recommended): Defines the flash application secure size, in bytes. 
 *                        Defaults to 50% of ROM is not provided.
 * ANSC=size (recommended): Defines the flash application non-secure callable 
 *                          size, in bytes. Defaults to 0 if not provided.
 * RS=size (recommended): Defines the size of secure RAM, in bytes. 
 *                        Defaults to 50% of RAM if not provided.
 * 
 * Recommendations for building SECURE applications that will use most
 * of the Flash and SRAM resources on SAML11; actual values depend
 * on the specific secure/non-secure split. XC32 V.2.2 or newer is required.
 *      AS = 63000  -- almost all of SAML11 Flash memory
 *      RS = 16000  -- almost all of SAML11 SRAM memory
 *      ANSC = 1024 -- modest non-secure  callable
 *      HEAP = 7000 -- won't allow the really big AES, though
 * 
 * (In the future, these Values should be defined in the Harmony3 set-up.)
 */

/* The following code should be included in main() in order to establish
 * operation of the secure debugger in SAML11 XPlained Pro (DM320205),
 * after SYS_initialize().

#if defined(__SAML11E16A__) // compiler pre-defined
    extern void sam_l11_secure_init(void);
    sam_l11_secure_init();
#endif

 * */

#if !defined(__SAML11E16A__)
#error This file is intended for use only with a SAML11 microcontroller.
#else

#include "definitions.h"
#define WITH_SECURE_LED 1

#define PORT_SEC_OFFSET  0x0200
#define PORT_SEC_ADDRESS (PORT_BASE_ADDRESS+PORT_SEC_OFFSET)

/* Define access protocols for the secure-only port bits */
#define PORT_SEC(group,mask,value) \
    ((port_group_registers_t*)group)->PORT_OUT = \
            (((port_group_registers_t*)group)->PORT_OUT & ~(mask)) | (mask & value);

#define PORT_SecWrite(pin,value) \
        PORT_SEC(PORT_SEC_ADDRESS + (0x80 * (pin>>5)), \
                    ((uint32_t)(0x1)) << (pin & 0x1f),    \
                    ((uint32_t)(value)) << (pin & 0x1f));

void sam_l11_secure_init(void)
{
    /*****************************************************/
    /*           Configure PORTs                         */
    /*****************************************************/
    /* SERCOM0 USART I/Os (for console), LED for blinking
        PA24 : UART_TX   <-> SERCOM0 PAD[2] peripheral C
        PA25 : UART_RX   <-> SERCOM0 PAD[3] peripheral C 
        PA07 : LED       <-> PORT 07

        Port-pins must also be allocated in Harmony3 pin manager.
    */
    PORT_SEC_REGS->GROUP[0].PORT_WRCONFIG = 
        (uint32_t)(PORT_WRCONFIG_HWSEL(1) // Configure pins[31..16] of the group
                    |PORT_WRCONFIG_PINMASK(1<<(24-16)) // exactly pin 24
                    |PORT_WRCONFIG_WRPINCFG(1) // mandatory for DRVSTR, PULLEN, INEN, PMUXEN, WRMASK
                    |PORT_WRCONFIG_WRPMUX(1)   // mandatory for PMUX
                    |PORT_WRCONFIG_INEN(0)     // output
                    |PORT_WRCONFIG_PMUXEN(1)   // not port, do peripheral i/o
                    |PORT_WRCONFIG_PMUX(2));   // peripheral function C
    PORT_SEC_REGS->GROUP[0].PORT_WRCONFIG = 
        (uint32_t)(PORT_WRCONFIG_HWSEL(1) // Configure pins[31..16] of the group
                    |PORT_WRCONFIG_PINMASK(1<<(25-16)) // exactly pin 25
                    |PORT_WRCONFIG_WRPINCFG(1) // mandatory for DRVSTR, PULLEN, INEN, PMUXEN, WRMASK
                    |PORT_WRCONFIG_WRPMUX(1)   // mandatory for PMUX
                    |PORT_WRCONFIG_INEN(1)     // input
                    |PORT_WRCONFIG_PMUXEN(1)   // not port, do peripheral i/o
                    |PORT_WRCONFIG_PMUX(2));   // peripheral function C

#if defined(WITH_SECURE_LED)
#define LED_L11         PORT_PIN_PA07
#define LED_L11_ON()    PORT_SecWrite(LED_L11,0);
#define LED_L11_OFF()   PORT_SecWrite(LED_L11,1);

    PORT_SEC_REGS->GROUP[0].PORT_WRCONFIG = 
        (uint32_t)(PORT_WRCONFIG_HWSEL(0) // Configure pins[15..00] of the group
                    |PORT_WRCONFIG_PINMASK(1<<7) // exactly pin 7
                    |PORT_WRCONFIG_WRPINCFG(1) // mandatory for DRVSTR, PULLEN, INEN, PMUXEN, WRMASK
                    |PORT_WRCONFIG_WRPMUX(1)   // mandatory for PMUX
                    |PORT_WRCONFIG_INEN(0)     // output
                    |PORT_WRCONFIG_PMUXEN(0)   // do port, not peripheral i/o
                    |PORT_WRCONFIG_PMUX(0));   // function don't care
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (((uint32_t)1)<<7);

    LED_L11_ON(); // demonstrate the LED operates
    LED_L11_OFF();
    LED_L11_ON();
#endif // WITH_SECURE_LED
}
#endif // _SAML11E16A_H_
