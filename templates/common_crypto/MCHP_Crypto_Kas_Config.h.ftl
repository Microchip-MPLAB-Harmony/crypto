/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Kas_Config.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef MCHP_CRYPTO_KAS_CONFIG_H
#define MCHP_CRYPTO_KAS_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************

//Max session allowed for Key Agreement Scheme Algorithms
#define CRYPTO_KAS_SESSION_MAX (1) 

<#if crypto_kas_ecdh_en == true>
    <#lt>#define CRYPTO_KAS_ECDH_EN
    <#lt>#define CRYPTO_KAS_WC_ALGO_EN
    <#lt>#define CRYPTO_KAS_WC_ECDH_EN
    </#if>

#endif /* MCHP_CRYPTO_KAS_CONFIG_H */
