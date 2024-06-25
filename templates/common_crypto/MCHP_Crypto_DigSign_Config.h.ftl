/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_DigSign_Config.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef MCHP_CRYPTO_DIGSIGN_CONFIG_H
#define MCHP_CRYPTO_DIGSIGN_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

//Max session allowed for Digital Signature Algorithms
#define CRYPTO_DIGISIGN_SESSION_MAX (1)      

<#if crypto_ds_ecdsa_en == true>
    <#lt>#define CRYPTO_DIGISIGN_ECDSA_EN

    <#if CONFIG_USE_ECDSA_HW == true>
        <#lt>#define CRYPTO_DIGISIGN_HW_ALGO_EN
        <#lt>#define CRYPTO_DIGISIGN_HW_ECDSA_EN
    <#else>
        <#lt>#define CRYPTO_DIGISIGN_WC_ALGO_EN
        <#lt>#define CRYPTO_DIGISIGN_WC_ECDSA_EN
    </#if>

</#if>

#endif /* MCHP_CRYPTO_DIGSIGN_CONFIG_H */

// *****************************************************************************
