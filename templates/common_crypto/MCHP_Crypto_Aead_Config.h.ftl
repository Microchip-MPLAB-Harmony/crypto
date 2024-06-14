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
//TODO:  Make the SW Implementation configurable to include or not
//       despite the hardware implementation.  This allows the
//       testing of HW using the SW calculated result.
<#if (crypto_aead_aes_gcm_hw_en == false ||
      crypto_aead_aes_ccm_hw_en == false || 
      crypto_aead_aes_eax_hw_en == false)>
    <#lt>#define CRYPTO_AEAD_WC_ALGO_EN
<#else>
    //Always allow the solftware implementation 
    <#lt>#define CRYPTO_AEAD_WC_ALGO_EN
</#if>

//------------------------------------------------------------------------------
//AES Algorithms Operational Mode Macros

<#if crypto_aead_aes_gcm_en == true>
    <#lt>#define CRYPTO_AEAD_AESGCM_EN
</#if>

<#if crypto_aead_aes_ccm_en == true>
    <#lt>#define CRYPTO_AEAD_AESCCM_EN
</#if>

<#if crypto_aead_aes_eax_en == true>
    <#lt>#define CRYPTO_AEAD_AESEAX_EN
</#if>

//****WolfcryptWrapper Algorithm Macros*************
//NOTE:  AEAD-AES algorithms accelerated using the AES HW driver
//       selection
<#if crypto_aead_aes_gcm_hw_en == false>
    <#lt>#define CRYPTO_AEAD_WC_AESGCM_EN
<#else>
    <#lt>#define CRYPTO_AEAD_HW_AESGCM_EN
</#if>

<#if crypto_aead_aes_ccm_hw_en == false>
    <#lt>#define CRYPTO_AEAD_WC_AESCCM_EN
<#else>
    <#lt>#define CRYPTO_AEAD_HW_AESCCM_EN
</#if>

<#if crypto_aead_aes_eax_hw_en == false>
    <#lt>#define CRYPTO_AEAD_WC_AESEAX_EN
<#else>
    <#lt>#define CRYPTO_AEAD_HW_AESEAX_EN
</#if>

#endif //MCHP_CRYPTO_AEAD_CONFIG_H
