/*******************************************************************************
  System Configuration Header

  File Name:
    MCHP_Crypto_Sym_Config.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef MCHP_CRYPTO_SYM_CONFIG_H
#define MCHP_CRYPTO_SYM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

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
<#lt>#define CRYPTO_SYM_SESSION_MAX (1)      //Max. session allowed 

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
//MCHP Configurations Macros
//***Symmetric Algorithm Macros****
<#if crypto_sym_aes_ecb_en == true ||
     crypto_sym_aes_cbc_en == true ||
     crypto_sym_aes_ofb_en == true ||
     crypto_sym_aes_cfb1_en == true ||
     crypto_sym_aes_cfb8_en == true ||
     crypto_sym_aes_cfb64_en == true ||
     crypto_sym_aes_cfb128_en == true ||
     crypto_sym_aes_ctr_en == true ||
     crypto_sym_aes_xts_en == true>
    <#lt>#define CRYPTO_SYM_AES_ENABLE         //any AES algorithm is selected in MCC GUI
    <#else>
        <#lt>#undef CRYPTO_SYM_AES_ENABLE      //No AES algorithm is selected in MCC GUI
    </#if>

//<#lt>#define CRYPTO_SYM_CAMELLIA_ENABLE      //Camellia algorithm is selected in MCC GUI
//<#lt>#define CRYPTO_SYM_TDES_ENABLE          //3DES/TDES algorithm option is selected in MCC GUI
//<#lt>#define CRYPTO_SYM_CHACHA20_ENABLE      //ChaCha20 algorithm is selected in MCC-GUI
//<#lt>#define CRYPTO_SYM_AESKEYWRAP_ENABLE    //AES-Key-Wrap algorithm is selected in MCC GUI    
//***************************************
    
//*****SYM OPERATION MODE ENABLE MACROS************
//AES Algorithms Operational Mode Macros
<#if crypto_sym_aes_ecb_en == true>
    <#lt>#define CRYPTO_SYM_AESECB_EN            //ECB mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_cbc_en == true>
   <#lt>#define CRYPTO_SYM_AESCBC_EN            //CBC mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_ofb_en == true>
    <#lt>#define CRYPTO_SYM_AESOFB_EN            //OFB mode is selected under AES algorithm in MCC-GUI
    </#if>
    
<#if crypto_sym_aes_cfb1_en == true>
    <#lt>#define CRYPTO_SYM_AESCFB1_EN           //CFB1 mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_cfb8_en == true>
    <#lt>#define CRYPTO_SYM_AESCFB8_EN           //CFB8 mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_cfb64_en == true>
    <#lt>#define CRYPTO_SYM_AESCFB64_EN          //CFB64 mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_cfb128_en == true>
    <#lt>#define CRYPTO_SYM_AESCFB128_EN         //CFB128 mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_ctr_en == true>
    <#lt>#define CRYPTO_SYM_AESCTR_EN            //CTR mode is selected under AES algorithm in MCC-GUI 
    </#if>

<#if crypto_sym_aes_xts_en == true>
    <#lt>#define CRYPTO_SYM_AESXTS_EN            //XTS mode is selected under AES algorithm in MCC-GUI
    </#if>

<#if crypto_sym_aes_kw_en == true>
    <#lt>#define CRYPTO_SYM_AESKW_EN            //Key Wrap (KW) mode is selected under AES algorithm in MCC-GUI
    </#if>


//****************************************************

//Camellia Algorithm Operational Mode Macros    
//<#lt>#define CRYPTO_SYM_CAMECB_EN            //ECB mode is selected under Camellia algorithm in MCC-GUI   
//<#lt>#define CRYPTO_SYM_CAMCBC_EN            //CBC mode is selected under Camellia algorithm in MCC-GUI
////****************************************************

//TDES/3-DES Algorithm Operational Mode Macros    
//<#lt>#define CRYPTO_SYM_TDESECB_EN           //ECB mode is option selected under 3DES/TDES algorithm in MCC-GUI        
//<#lt>#define CRYPTO_SYM_TDESCBC_EN           //CBC mode is option selected under 3DES/TDES algorithm in MCC-GUI   
////*****************************************************

//****WolfcryptWrapper Algorithm Macros*************
#ifdef CRYPTO_SYM_AES_ENABLE
    <#lt>#define CRYPTO_SYM_WC_ALGO_EN             //Any symmetric algorithm selected to use Wolfcrypt
    <#lt>#define CRYPTO_SYM_WC_AES_EN              //AES algorithm selected to use Wolfcrypt 
#endif

//<#lt>#define CRYPTO_SYM_WC_CAMELLIA_EN       //Camellia algorithm selected to use Wolfcrypt 
//<#lt>#define CRYPTO_SYM_WC_TDES_EN           //Wolfcrypt software library selected to use 3DES/TDES algorithm logic
//<#lt>#define CRYPTO_SYM_WC_AESKW_EN          //AES-Key-Wrap algorithm option selected to use Wolfcrypt
//<#lt>#define CRYPTO_SYM_WC_CHACHA20_EN       //ChaCha20 algorithm is selected to use Wolfcrypt 
//**************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END


#endif //MCHP_CRYPTO_SYM_CONFIG_H
