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
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

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
#define CRYPTO_SYM_SESSION_MAX (1)      //Always define this macro to mention max. session allowed for Symmetric Algorithm

// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************
//MCHP Configurations Macros
//***Symmetric Algorithm Macros****
#define CRYPTO_SYM_AES_ENABLE           //Define this Macro when AES algorithm is selected in MCC GUI
#define CRYPTO_SYM_CAMELLIA_ENABLE      //Define this Macro when Camellia algorithm is selected in MCC GUI
#define CRYPTO_SYM_TDES_ENABLE          //Define this Macro when 3DES/TDES algorithm option is selected in MCC GUI
#define CRYPTO_SYM_CHACHA20_ENABLE      //Define this Macro when ChaCha20 algorithm is selected in MCC-GUI
#define CRYPTO_SYM_AESKEYWRAP_ENABLE    //Define this Macro when AES-Key-Wrap algorithm is selected in MCC GUI    
//***************************************
    
//*****SYM OPERATION MODE ENABLE MACROS************
//AES Algorithms Operational Mode Macros
#define CRYPTO_SYM_AESECB_EN            //Define this Macro when ECB mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESCBC_EN            //Define this Macro when CBC mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESOFB_EN            //Define this Macro when OFB mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESCFB1_EN           //Define this Macro when CFB1 mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESCFB8_EN           //Define this Macro when CFB8 mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESCFB64_EN          //Define this Macro when CFB64 mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESCFB128_EN         //Define this Macro when CFB128 mode is selected under AES algorithm in MCC-GUI
#define CRYPTO_SYM_AESCTR_EN            //Define this Macro when CTR mode is selected under AES algorithm in MCC-GUI 
#define CRYPTO_SYM_AESXTS_EN            //Define this Macro when XTS mode is selected under AES algorithm in MCC-GUI
//****************************************************

//Camellia Algorithm Operational Mode Macros    
#define CRYPTO_SYM_CAMECB_EN            //Define this Macro when ECB mode is selected under Camellia algorithm in MCC-GUI   
#define CRYPTO_SYM_CAMCBC_EN            //Define this Macro when CBC mode is selected under Camellia algorithm in MCC-GUI
////****************************************************

//TDES/3-DES Algorithm Operational Mode Macros    
#define CRYPTO_SYM_TDESECB_EN           //Define this Macro when ECB mode is option selected under 3DES/TDES algorithm in MCC-GUI        
#define CRYPTO_SYM_TDESCBC_EN           //Define this Macro when CBC mode is option selected under 3DES/TDES algorithm in MCC-GUI   
////*****************************************************

//****WolfcryptWrapper Algorithm Macros*************
#define CRYPTO_SYM_WC_ALGO_EN            //Define this Macro when any symmetric algorithm is selected to use Wolfcrypt software library to run algorithm logic
#define CRYPTO_SYM_WC_AES_EN            //Define this Macro when AES algorithm is selected to use Wolfcrypt software library to run algorithm logic
#define CRYPTO_SYM_WC_CAMELLIA_EN       //Define this Macro when Camellia algorithm is selected to use Wolfcrypt software library to run algorithm logic
#define CRYPTO_SYM_WC_TDES_EN           //Define this Macro when Wolfcrypt software library is selected to use 3DES/TDES algorithm logic
#define CRYPTO_SYM_WC_AESKW_EN          //Define this Macro when AES-Key-Wrap algorithm option is selected to use Wolfcrypt software library to run algorithm logic.
#define CRYPTO_SYM_WC_CHACHA20_EN       //Define this Macro when ChaCha20 algorithm is selected to use Wolfcrypt software library to run algorithm logic
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