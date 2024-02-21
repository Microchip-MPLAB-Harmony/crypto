/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Aead_Config.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef MCHP_CRYPTO_AEAD_CONFIG_H
#define MCHP_CRYPTO_AEAD_CONFIG_H

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
#define CRYPTO_AEAD_SESSION_MAX (1)

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
//MCHP Configurations Macros
    

//*****OPERATION MODE ENABLE MACROS************

//AEAD SW/HW Mode
<#if crypto_aead_aes_ccm_hw_en == false || crypto_aead_aes_eax_hw_en == false>
    <#lt>#define CRYPTO_AEAD_WC_ALGO_EN
<#else>
    #warning "HW Implementation of AEAD algorithms not implemented"
</#if>

//------------------------------------------------------------------------------
//AES Algorithms Operational Mode Macros
<#if crypto_aead_aes_ccm_en == true>
    <#lt>#define CRYPTO_AEAD_AESCCM_EN
</#if>

<#if crypto_aead_aes_eax_en == true>
    <#lt>#define CRYPTO_AEAD_AESEAX_EN
</#if>

//****WolfcryptWrapper Algorithm Macros*************
<#if crypto_aead_aes_ccm_hw_en == false>
    <#lt>#define CRYPTO_AEAD_WC_AESCCM_EN
<#else>
    #warning "HW Implementation of AES-CCM algorithm not implemented"
</#if>

<#if crypto_aead_aes_eax_hw_en == false>
    <#lt>#define CRYPTO_AEAD_WC_AESEAX_EN
<#else>
    #warning "HW Implementation of AES-EAX algorithm not implemented"
</#if>

#endif //MCHP_CRYPTO_AEAD_CONFIG_H

