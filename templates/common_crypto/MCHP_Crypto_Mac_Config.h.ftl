/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Mac_Config.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef MCHP_CRYPTO_MAC_CONFIG_H
#define MCHP_CRYPTO_MAC_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
#define CRYPTO_MAC_SESSION_MAX (1)

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

//*****OPERATION MODE ENABLE MACROS************

//AES Algorithm Operational Mode Macros
<#if crypto_mac_aes_cmac_en == true>
    <#lt>#define CRYPTO_MAC_AESCMAC_EN
</#if>

//****WolfcryptWrapper Algorithm Macros*************
<#if crypto_mac_aes_cmac_hw_en == false>
    <#lt>#define CRYPTO_MAC_WC_ALGO_EN
    <#lt>#define CRYPTO_MAC_WC_AESCMAC_EN
<#else>
    #warning "HW Implementation of MAC algorithms not implemented"
</#if>

#endif //MCHP_CRYPTO_MAC_CONFIG_H

