/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Sym_HwWrapper.c

  Summary:
    Crypto Framework Library wrapper file for hardware AES.

  Description:
    This source file contains the wrapper interface to access the symmetric 
    AES algorithms in the AES hardware driver for Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2024, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
*/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include "crypto/common_crypto/MCHP_Crypto_Sym_HwWrapper.h"
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == true>
#include "crypto/drivers/drv_crypto_aes_hw_6149.h"
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************
   
static crypto_Sym_Status_E lCrypto_Sym_Hw_Aes_GetOperationMode
    (crypto_Sym_OpModes_E opMode, CRYPTO_AES_OPERATION_MODE* aesMode, 
     CRYPTO_AES_CFB_SIZE* cfbSize)
{
    *cfbSize = CRYPTO_AES_CFB_SIZE_128BIT; // Default if not used
    
    switch (opMode) 
    {
#ifdef CRYPTO_SYM_AESECB_EN
        case CRYPTO_SYM_OPMODE_ECB:
            *aesMode = CRYPTO_AES_MODE_ECB;
            break;
#endif
        
#ifdef CRYPTO_SYM_AESCBC_EN
        case CRYPTO_SYM_OPMODE_CBC:
            *aesMode = CRYPTO_AES_MODE_CBC;
            break;
#endif
        
#ifdef CRYPTO_SYM_AESOFB_EN
        case CRYPTO_SYM_OPMODE_OFB:
            *aesMode = CRYPTO_AES_MODE_OFB;
            break;
#endif
            
#ifdef CRYPTO_SYM_AESCFB1_EN
        case CRYPTO_SYM_OPMODE_CFB1:
            return CRYPTO_SYM_ERROR_OPMODE; 
#endif
            
#ifdef CRYPTO_SYM_AESCFB8_EN
        case CRYPTO_SYM_OPMODE_CFB8:
            *aesMode = CRYPTO_AES_MODE_CFB;
            *cfbSize = CRYPTO_AES_CFB_SIZE_8BIT;
            break;
#endif
            
#ifdef CRYPTO_SYM_AESCFB16_EN
        case CRYPTO_SYM_OPMODE_CFB16:
            *aesMode = CRYPTO_AES_MODE_CFB;
            *cfbSize = CRYPTO_AES_CFB_SIZE_16BIT;
            break;
#endif
        
#ifdef CRYPTO_SYM_AESCFB32_EN
        case CRYPTO_SYM_OPMODE_CFB32:
            *aesMode = CRYPTO_AES_MODE_CFB;
            *cfbSize = CRYPTO_AES_CFB_SIZE_32BIT;
            break;
#endif
           
#ifdef CRYPTO_SYM_AESCFB64_EN
        case CRYPTO_SYM_OPMODE_CFB64:
            *aesMode = CRYPTO_AES_MODE_CFB;
            *cfbSize = CRYPTO_AES_CFB_SIZE_64BIT;
            break;
#endif
            
#ifdef CRYPTO_SYM_AESCFB128_EN
        case CRYPTO_SYM_OPMODE_CFB128:
            *aesMode = CRYPTO_AES_MODE_CFB;
            *cfbSize = CRYPTO_AES_CFB_SIZE_128BIT;
            break;
#endif
        
#ifdef CRYPTO_SYM_AESCTR_EN
        case CRYPTO_SYM_OPMODE_CTR:
            *aesMode = CRYPTO_AES_MODE_CTR;
            break;
#endif
            
        default:
            return CRYPTO_SYM_ERROR_OPMODE;
    }
    
    return CRYPTO_SYM_CIPHER_SUCCESS;
}
    
// *****************************************************************************
// *****************************************************************************
// Section: Symmetric Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

crypto_Sym_Status_E Crypto_Sym_Hw_Aes_Init(crypto_CipherOper_E cipherOpType_en, 
    crypto_Sym_OpModes_E opMode_en, uint8_t *key, uint32_t keyLen, 
    uint8_t *initVect)
{ 
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == false>
    return CRYPTO_SYM_ERROR_CIPNOTSUPPTD;
<#else>  
    CRYPTO_AES_CONFIG aesCfg;
    CRYPTO_AES_OPERATION_MODE opMode;
    CRYPTO_AES_CFB_SIZE cfbSize;
    crypto_Sym_Status_E result;
        
    /* Get operation mode for driver */
    result = lCrypto_Sym_Hw_Aes_GetOperationMode(opMode_en, &opMode, &cfbSize);
    if (result != CRYPTO_SYM_CIPHER_SUCCESS)
    {
        return result;
    }
    
    /* Get the default configuration of the driver */
    DRV_CRYPTO_AES_GetConfigDefault(&aesCfg);
    
    /* Initialize the driver */
    DRV_CRYPTO_AES_Init();
    
    /* Set the configuration for the driver */
    aesCfg.keySize = DRV_CRYPTO_AES_GetKeySize(keyLen / 4);
    aesCfg.startMode = CRYPTO_AES_AUTO_START;
    aesCfg.opMode = opMode;
    aesCfg.cfbSize = cfbSize;
    if (cipherOpType_en == CRYPTO_CIOP_ENCRYPT)
    {
        aesCfg.encryptMode = CRYPTO_AES_ENCRYPTION;
    }
    else 
    {
        aesCfg.encryptMode = CRYPTO_AES_DECRYPTION;
    }
    
    DRV_CRYPTO_AES_SetConfig(&aesCfg);
    
    /* Write the key */
    DRV_CRYPTO_AES_WriteKey((uint32_t *)key);
    
    /* Write the initialization vector */
    if (initVect != NULL)
    {
        DRV_CRYPTO_AES_WriteInitVector((uint32_t *) initVect);
    }
    
    return CRYPTO_SYM_CIPHER_SUCCESS;
</#if>
}
    
crypto_Sym_Status_E Crypto_Sym_Hw_Aes_Cipher(uint8_t *inputData, 
    uint32_t dataLen, uint8_t *outData)
{
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == false>
    return CRYPTO_SYM_ERROR_CIPNOTSUPPTD;
<#else> 
    DRV_CRYPTO_AES_WritePCTextLen(dataLen);
    
    uint32_t *iData = (uint32_t *)inputData;
    uint32_t *oData = (uint32_t *)outData;
    uint32_t blockLen = dataLen / 4;
    uint32_t block;   /* 4 32bit block size */
    for (block = 0; block < blockLen; block += 4)
    {
        /* Write the data to be ciphered to the input data registers */
        DRV_CRYPTO_AES_WriteInputData(iData);
        iData += 4;

        /* Wait for the cipher process to end */
        while (!DRV_CRYPTO_AES_CipherIsReady())
        {
            ;
        }   

        /* Cipher complete - read out the data */
        DRV_CRYPTO_AES_ReadOutputData(oData);
        oData += 4;
    }
    
    return CRYPTO_SYM_CIPHER_SUCCESS;
</#if>
}

crypto_Sym_Status_E Crypto_Sym_Hw_Aes_EncryptDirect(crypto_Sym_OpModes_E opMode_en, 
    uint8_t *inputData, uint32_t dataLen, uint8_t *outData, 
    uint8_t *key, uint32_t keyLen, uint8_t *initVect)
{
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == false>
    return CRYPTO_SYM_ERROR_CIPNOTSUPPTD;
<#else>  
    crypto_Sym_Status_E result = CRYPTO_SYM_CIPHER_SUCCESS;
    
    result = Crypto_Sym_Hw_Aes_Init(CRYPTO_CIOP_ENCRYPT, opMode_en, key, 
                                    keyLen, initVect);
                
    if (result != CRYPTO_SYM_CIPHER_SUCCESS)
    {
        return result;
    }
    
    return Crypto_Sym_Hw_Aes_Cipher(inputData, dataLen, outData);
</#if>
}

crypto_Sym_Status_E Crypto_Sym_Hw_Aes_DecryptDirect(crypto_Sym_OpModes_E opMode_en, 
    uint8_t *inputData, uint32_t dataLen, uint8_t *outData, 
    uint8_t *key, uint32_t keyLen, uint8_t *initVect)
{
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == false>
    return CRYPTO_SYM_ERROR_CIPNOTSUPPTD;
<#else>  
    crypto_Sym_Status_E result = CRYPTO_SYM_CIPHER_SUCCESS;
    
    result = Crypto_Sym_Hw_Aes_Init(CRYPTO_CIOP_DECRYPT, opMode_en, key, 
                                    keyLen, initVect);
                
    if (result != CRYPTO_SYM_CIPHER_SUCCESS)
    {
        return result;
    }
    
    return Crypto_Sym_Hw_Aes_Cipher(inputData, dataLen, outData);
</#if>
}
