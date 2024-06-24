/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Rng_Config.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/
#ifndef MCHP_CRYPTO_RNG_CONFIG_H
#define MCHP_CRYPTO_RNG_CONFIG_H

<#lt>#define CRYPTO_RNG_SESSION_MAX (1)

<#if crypto_rng_prng_en == true>
    <#lt>#define CRYPTO_RNG_WC_PRNG_EN
    </#if>

<#if crypto_rng_trng_en == true>
    <#lt>#define CRYPTO_RNG_HW_TRNG_EN
    </#if>

#endif /* MCHP_CRYPTO_RNG_CONFIG_H */
