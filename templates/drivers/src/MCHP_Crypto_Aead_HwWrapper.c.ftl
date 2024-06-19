/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Aead_HwWrapper.c

  Summary:
    Crypto Framework Library wrapper file for hardware AES.

  Description:
    This source file contains the wrapper interface to access the AEAD
    algorithms in the AES hardware driver for Microchip microcontrollers.
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
#include <string.h>
#include "crypto/common_crypto/MCHP_Crypto_Aead_HwWrapper.h"
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == true>
#include "crypto/drivers/drv_crypto_aes_hw_6149.h"
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

static CRYPTO_AES_CONFIG aesGcmCfg;

// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************

static void lCrypto_Aead_Hw_Gcm_WriteKey(uint32_t *gcmKey)
{
    DRV_CRYPTO_AES_WriteKey(gcmKey);
   
    /* Wait for the GCMH to generate */
    while (!DRV_CRYPTO_AES_CipherIsReady())
    {
        ;
	} 
}    
    
static void lCrypto_Aead_Hw_Gcm_WriteGeneratedIv(CRYPTO_GCM_HW_CONTEXT *gcmCtx)
{
    uint32_t ivBuffer[4];
    uint8_t x;
    
    for (x = 0; x < 3; x++)
    {
        ivBuffer[x] = gcmCtx->calculatedIv[x];        
    }    

    ivBuffer[3] = gcmCtx->invokeCtr[0];
    
    DRV_CRYPTO_AES_WriteInitVector(ivBuffer);
}

static void lCrypto_Aead_Hw_Gcm_GenerateJ0(CRYPTO_GCM_HW_CONTEXT *gcmCtx, 
                                       uint8_t *iv, 
                                       uint32_t ivLen)
{
    uint8_t *ivSaved = (uint8_t*)gcmCtx->calculatedIv;
    
    /* Check if IV lenght is 96 bits */
    if (ivLen == 12)    
    {
        memcpy(ivSaved, iv, ivLen);
        ivSaved[(sizeof(gcmCtx->calculatedIv) - 1)] = 0x1;
        return;
    }
    
    /* Write the key */
    lCrypto_Aead_Hw_Gcm_WriteKey(gcmCtx->key);

    /* Configure AADLEN with: len(IV || 0s+64 || [len(IV)]64) */
    uint32_t numFullBlocks = ivLen / 16;
    if (ivLen % 16 > 0)
    {
        // This is questionable. The formula says to use the bit size.
        // But the register description is byte size.
        DRV_CRYPTO_AES_WriteAuthDataLen((numFullBlocks + 2) * 128);
    }
    else
    {   
        DRV_CRYPTO_AES_WriteAuthDataLen((numFullBlocks + 1) * 128);        
    }
    
    /* Configure CLEN to 0. This will allow running a GHASHH only. */
    DRV_CRYPTO_AES_WritePCTextLen(0);
    
    /* Write message to process (IV || 0s+64 || [len(IV)]64) */
    uint32_t *inPtr = (uint32_t *)iv;
    uint32_t block;   /* 4 32bit block size */
    for (block = 0; block < numFullBlocks; block++)
    {
        /* Write the data to be ciphered to the input data registers */
        DRV_CRYPTO_AES_WriteInputData(inPtr);
        inPtr += 4;

        /* Wait for the cipher process to end */
        while (!DRV_CRYPTO_AES_CipherIsReady())
        {
            ;
        }        
    }    
    
    uint32_t numPartialBytes = ivLen % 16;
    if (numPartialBytes > 0)
    {
        uint32_t partialPlusPad[4] = {0};
        memcpy(partialPlusPad, inPtr, numPartialBytes);
        
        /* Write the data to be ciphered to the input data registers */
        DRV_CRYPTO_AES_WriteInputData(partialPlusPad);

        /* Wait for the cipher process to end */
        while (!DRV_CRYPTO_AES_CipherIsReady())
        {
            ;
        }              
    }
    
    uint8_t finalBlock[16] = {0};
    uint32_t bits = ivLen * 8;
    // This may be wrong, but we have to change it to big endian format.
    // Per NIST AES GCM is big endian.
    finalBlock[15] = (uint8_t)(bits & 0xFF);
    finalBlock[14] = (uint8_t)((bits >> 8) & 0xFF);
    finalBlock[13] = (uint8_t)((bits >> 16)& 0xFF);
    finalBlock[12] = (uint8_t)((bits >> 24)& 0xFF);
    
    /* The lines below are subject to a type-punning warning because 
    * the (uint8_t*) is cast to a (uint32_t*) which might typically suffer 
    * from a misalignment problem. The conditional breakpoint will
    * trigger the debugger if the byte-pointer is misaligned, but will
    * be eliminated if the compiler can prove correct alignment.
    * Such a warning is thrown only at higher optimization levels.
    */
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#include <assert.h> // prove we have 4-byte alignment
    __conditional_software_breakpoint(0 == ((uint32_t)finalBlock) % 4);
#endif
    /* Write the data to be ciphered to the input data registers */
    DRV_CRYPTO_AES_WriteInputData((uint32_t *)finalBlock);
#if defined(__GNUC__)
#pragma GCC diagnostic push
#endif

    /* Wait for the cipher process to end */
    while (!DRV_CRYPTO_AES_CipherIsReady())
    {
        ;
    }     
    
    /* Read hash to obtain the J0 value */
    DRV_CRYPTO_AES_ReadGcmHash(gcmCtx->intermediateHash);
    DRV_CRYPTO_AES_ReadGcmH(gcmCtx->H);
    memcpy(ivSaved, (uint8_t *)gcmCtx->intermediateHash, 16);
    
    uint32_t tmp = (ivSaved[15] & 0xFF) |
                   ((ivSaved[14] & 0xFF) << 8) |
                   ((ivSaved[13] & 0xFF) << 16) |
                   ((ivSaved[12] & 0xFF) << 24);
    tmp++;
    gcmCtx->invokeCtr[0] = ((tmp & 0x000000FF) << 24) |
                           ((tmp & 0x0000FF00) << 8) |
                           ((tmp & 0x00FF0000) >> 8) |
                           ((tmp & 0xFF000000) >> 24);
}

static void lCrypto_Aead_Hw_Gcm_RunBlocks(uint32_t *in, uint32_t byteLen, uint32_t* out)
{
    if (byteLen == 0)
    {
        return;
    }
    
    uint32_t blockLen = byteLen / 4;
    uint32_t block;   /* 4 32bit block size */
    for (block = 0; block < blockLen; block += 4)
    {
        /* Write the data to be ciphered to the input data registers. */
        DRV_CRYPTO_AES_WriteInputData(in);
        in += 4;

        /* Wait for the cipher process to end */
        while (!DRV_CRYPTO_AES_CipherIsReady())
        {
            ;
        }  

        if (out != NULL)
        {
            /* Cipher complete - read out the data */
            DRV_CRYPTO_AES_ReadOutputData(out);
            out += 4;
        }
    }
    
    uint32_t numBytes = byteLen % 16;
    if (numBytes > 0)
    {
        uint32_t partialPlusPad[4] = {0};
        memcpy(partialPlusPad, in, numBytes);
        
        /* Write the data to be ciphered to the input data registers. */
        DRV_CRYPTO_AES_WriteInputData(partialPlusPad);
        
        /* Wait for the cipher process to end */
        while (!DRV_CRYPTO_AES_CipherIsReady())
        {
            ;
        }  

        if (out != NULL)
        {
            uint32_t completeOut[4] = {0};
            
            /* Cipher complete - read out the data */
            DRV_CRYPTO_AES_ReadOutputData(completeOut);
            
            if (numBytes >= 4)
            {
                *out++ = completeOut[0];
                if (numBytes >= 8)
                {
                    *out++ = completeOut[1];
                    if (numBytes >= 12)
                    {
                        *out++ = completeOut[2];
                        if (numBytes > 12)
                        {
                            uint32_t tmp = completeOut[3];
                            memcpy(out, &tmp, (numBytes - 12));                                                
                        }
                    }
                    else
                    {
                        uint32_t tmp = completeOut[2];
                        memcpy(out, &tmp, (numBytes - 8));                    
                    }
                }
                else
                {
                    uint32_t tmp = completeOut[1];
                    memcpy(out, &tmp, (numBytes - 4));                    
                }
            }
            else
            {
                uint32_t tmp = completeOut[0];
                memcpy(out, &tmp, numBytes);
            }
        }
    }
}

static void lCrypto_Aead_Hw_Gcm_CmpMsgWithTag(CRYPTO_GCM_HW_CONTEXT *gcmCtx,
    uint8_t *iv, uint32_t ivLen, uint8_t *inData, uint32_t dataLen, 
    uint8_t *outData, uint8_t *aad, uint32_t aadLen, uint8_t *tag, 
    uint32_t tagLen)
{
    /* Calculate the J0 value */
    gcmCtx->invokeCtr[0] = 0x02000000;
    lCrypto_Aead_Hw_Gcm_GenerateJ0(gcmCtx, iv, ivLen);
    
    /* Enable tag generation in driver */
    aesGcmCfg.gtagEn = 1;
    DRV_CRYPTO_AES_SetConfig(&aesGcmCfg);
    
    /* Write the key */
    lCrypto_Aead_Hw_Gcm_WriteKey(gcmCtx->key);
    
    /* Write IV with inc32(J0) (J0 + 1 on 32 bits) */
    lCrypto_Aead_Hw_Gcm_WriteGeneratedIv(gcmCtx);
    
    /* Write lengths */
    DRV_CRYPTO_AES_WriteAuthDataLen(aadLen);
    DRV_CRYPTO_AES_WritePCTextLen(dataLen);
    
    lCrypto_Aead_Hw_Gcm_RunBlocks((uint32_t *)aad, aadLen, NULL);
    lCrypto_Aead_Hw_Gcm_RunBlocks((uint32_t *)inData, dataLen, 
                                  (uint32_t *)outData);
    
    if ((aadLen != 0) || (dataLen != 0))
    {
        /* Wait for the tag to generate */
        while (!DRV_CRYPTO_AES_TagIsReady())
        {
            ;
        }   
    }  
    
    /* Read the tag */
    DRV_CRYPTO_AES_ReadTag((uint32_t *)tag);
    
    /* Read hash */
    DRV_CRYPTO_AES_ReadGcmHash(gcmCtx->intermediateHash);
    DRV_CRYPTO_AES_ReadGcmH(gcmCtx->H);
}

static void lCrypto_Aead_Hw_Gcm_1stMsgFrag(CRYPTO_GCM_HW_CONTEXT *gcmCtx,
    uint8_t *iv, uint32_t ivLen, uint8_t *inData, uint32_t dataLen, 
    uint8_t *outData, uint8_t *aad, uint32_t aadLen)
{
    /* Calculate the J0 value */
    gcmCtx->invokeCtr[0] = 0x02000000;
    lCrypto_Aead_Hw_Gcm_GenerateJ0(gcmCtx, iv, ivLen);
    
    /* Disable tag generation in driver */
    aesGcmCfg.gtagEn = 0;
    DRV_CRYPTO_AES_SetConfig(&aesGcmCfg);
    
    /* Write the key */
    lCrypto_Aead_Hw_Gcm_WriteKey(gcmCtx->key);
    
    /* Write IV with inc32(J0) (J0 + 1 on 32 bits) */
    lCrypto_Aead_Hw_Gcm_WriteGeneratedIv(gcmCtx);

    /* Write lengths */
    DRV_CRYPTO_AES_WriteAuthDataLen(aadLen);
    DRV_CRYPTO_AES_WritePCTextLen(dataLen);
    
    lCrypto_Aead_Hw_Gcm_RunBlocks((uint32_t *)aad, aadLen, NULL);
    lCrypto_Aead_Hw_Gcm_RunBlocks((uint32_t *)inData, dataLen, 
                                  (uint32_t *)outData);
   
    /* Read hash */
    DRV_CRYPTO_AES_ReadGcmHash(gcmCtx->intermediateHash);
    DRV_CRYPTO_AES_ReadGcmH(gcmCtx->H);
}

static void lCrypto_Aead_Hw_Gcm_MoreMsgFrag(CRYPTO_GCM_HW_CONTEXT *gcmCtx,
    uint8_t *inData, uint32_t dataLen, uint8_t *outData)
{
    /* Disable tag generation in driver */
    aesGcmCfg.gtagEn = 0;
    DRV_CRYPTO_AES_SetConfig(&aesGcmCfg);
    
    /* Write the key */
    lCrypto_Aead_Hw_Gcm_WriteKey(gcmCtx->key);
    
    /* Write IV with inc32(J0) (J0 + 1 on 32 bits) */
    lCrypto_Aead_Hw_Gcm_WriteGeneratedIv(gcmCtx);
    
    /* Write lengths */
    DRV_CRYPTO_AES_WriteAuthDataLen(0);
    DRV_CRYPTO_AES_WritePCTextLen(dataLen);

    /* Load hash */
    DRV_CRYPTO_AES_WriteGcmHash(gcmCtx->intermediateHash);
    
    lCrypto_Aead_Hw_Gcm_RunBlocks((uint32_t *)inData, dataLen, 
                                  (uint32_t *)outData);
   
    /* Read hash */
    DRV_CRYPTO_AES_ReadGcmHash(gcmCtx->intermediateHash);
    DRV_CRYPTO_AES_ReadGcmH(gcmCtx->H);
}

static void lCrypto_Aead_Hw_Gcm_GenerateTag(CRYPTO_GCM_HW_CONTEXT *gcmCtx,
    uint32_t dataLen, uint32_t aadLen, uint8_t *tag, uint32_t tagLen)
{
    /* Disable tag generation in driver */
    aesGcmCfg.gtagEn = 0;
    DRV_CRYPTO_AES_SetConfig(&aesGcmCfg);
    
    /* Write the key */
    lCrypto_Aead_Hw_Gcm_WriteKey(gcmCtx->key);
    
    /* Configure authentication data length to 0x10 (16 bytes) */
    /* And plain text length to 0 */
    DRV_CRYPTO_AES_WriteAuthDataLen(0x10);
    DRV_CRYPTO_AES_WritePCTextLen(0);
   
    /* Load hash */
    DRV_CRYPTO_AES_WriteGcmHash(gcmCtx->intermediateHash);
    
    /* Fill input data with lengths in bits */
    aadLen = aadLen * 8;
    dataLen = dataLen * 8;
    uint32_t lenIn[4] = {0};
    lenIn[1] = (((aadLen << 24) & 0xFF000000) | 
                ((aadLen << 8) & 0x00FF0000) |
                ((aadLen >> 8) & 0x0000FF00) |
                ((aadLen >> 24) & 0x000000FF));
    lenIn[3] = (((dataLen << 24) & 0xFF000000) | 
                ((dataLen << 8) & 0x00FF0000) |
                ((dataLen >> 8) & 0x0000FF00) |
                ((dataLen >> 24) & 0x000000FF));
    
    /* Write the data to be ciphered to the input data registers. */
    DRV_CRYPTO_AES_WriteInputData(lenIn);
        
    /* Wait for the cipher process to end */
    while (!DRV_CRYPTO_AES_CipherIsReady())
    { 
        ;
    }  
    
    /* Read hash */
    DRV_CRYPTO_AES_ReadGcmHash(gcmCtx->intermediateHash);
    DRV_CRYPTO_AES_ReadGcmH(gcmCtx->H);
    
    /* Reset the driver */
    DRV_CRYPTO_AES_Init();
    
    /* Processing T = GCTRK(J0, S) */
    
    /* Configure AES-CTR mode */
    aesGcmCfg.opMode = CRYPTO_AES_MODE_CTR;
    aesGcmCfg.encryptMode = CRYPTO_AES_ENCRYPTION;
    aesGcmCfg.gtagEn = 0;
    DRV_CRYPTO_AES_SetConfig(&aesGcmCfg);
    
    /* Write key */
    DRV_CRYPTO_AES_WriteKey(gcmCtx->key);
    
    /* Write initialization vector with J0 value */
    DRV_CRYPTO_AES_WriteInitVector(gcmCtx->calculatedIv);

    /* Write the data to be ciphered to the input data registers. */
    DRV_CRYPTO_AES_WriteInputData(gcmCtx->intermediateHash);

    /* Wait for the cipher process to end */
    while (!DRV_CRYPTO_AES_CipherIsReady())
    { 
        ;
    }  

    /* Cipher complete - read out the data */
    uint32_t gcmTag[4];
    DRV_CRYPTO_AES_ReadOutputData(gcmTag);
   
    memcpy(tag, gcmTag, tagLen);
}

// *****************************************************************************
// *****************************************************************************
// Section: AEAD Algorithms Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

crypto_Aead_Status_E Crypto_Aead_Hw_AesGcm_Init(CRYPTO_GCM_HW_CONTEXT *gcmCtx,
    crypto_CipherOper_E cipherOper_en, uint8_t *key, uint32_t keyLen)
{
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == false>
    return CRYPTO_AEAD_ERROR_CIPNOTSUPPTD;
<#else>  
    /* Initialize the context */
    memset(gcmCtx, 0, sizeof(CRYPTO_GCM_HW_CONTEXT));
    
    /* Get the default configuration from the driver */
    DRV_CRYPTO_AES_GetConfigDefault(&aesGcmCfg);
    
    /* Initialize the driver */
    DRV_CRYPTO_AES_Init();
    
    /* Set configuration in the driver */
    aesGcmCfg.keySize = DRV_CRYPTO_AES_GetKeySize(keyLen / 4);
    aesGcmCfg.startMode = CRYPTO_AES_AUTO_START;
    aesGcmCfg.opMode = CRYPTO_AES_MODE_GCM;
    aesGcmCfg.gtagEn = 0;
    if (cipherOper_en == CRYPTO_CIOP_ENCRYPT)
    {
        aesGcmCfg.encryptMode = CRYPTO_AES_ENCRYPTION;
    }
    else 
    {
        aesGcmCfg.encryptMode = CRYPTO_AES_DECRYPTION;
    }
    
    DRV_CRYPTO_AES_SetConfig(&aesGcmCfg);

    /* Store the key */
    memcpy(gcmCtx->key, (uint32_t *)key, (keyLen / 4));
    
    return CRYPTO_AEAD_CIPHER_SUCCESS;
</#if>  
}

crypto_Aead_Status_E Crypto_Aead_Hw_AesGcm_Cipher(CRYPTO_GCM_HW_CONTEXT *gcmCtx,
    uint8_t *initVect, uint32_t initVectLen, uint8_t *inputData,
    uint32_t dataLen, uint8_t *outData, uint8_t *aad, uint32_t aadLen,
    uint8_t *authTag, uint32_t authTagLen)
{
<#if HAVE_MCHP_CRYPTO_AES_HW_6149 == false>
    return CRYPTO_AEAD_ERROR_CIPNOTSUPPTD;
<#else>  
    if (dataLen != 0 || aadLen != 0)
    {
        if (gcmCtx->invokeCtr[0] == 0)
        {
            if (authTag != NULL)
            {
                lCrypto_Aead_Hw_Gcm_CmpMsgWithTag(gcmCtx, initVect, initVectLen, 
                    inputData, dataLen, outData, aad, aadLen, authTag, 
                    authTagLen);
                
                return CRYPTO_AEAD_CIPHER_SUCCESS;
            }
            else
            {
                lCrypto_Aead_Hw_Gcm_1stMsgFrag(gcmCtx, initVect, initVectLen,
                    inputData, dataLen, outData, aad, aadLen);
                
                return CRYPTO_AEAD_CIPHER_SUCCESS;
            }        
        }
        
        lCrypto_Aead_Hw_Gcm_MoreMsgFrag(gcmCtx, inputData, dataLen, outData);
    }
    
    if (authTag != NULL)
    {
        if (gcmCtx->invokeCtr[0] == 0)
        {
            /* Calculate the J0 value */
            lCrypto_Aead_Hw_Gcm_GenerateJ0(gcmCtx, initVect, initVectLen);
        }
        
        lCrypto_Aead_Hw_Gcm_GenerateTag(gcmCtx, dataLen, aadLen, authTag, 
                authTagLen);
    }
    
    return CRYPTO_AEAD_CIPHER_SUCCESS;
</#if>  
}
 
crypto_Aead_Status_E Crypto_Aead_Hw_AesGcm_EncryptAuthDirect(uint8_t *inputData, 
    uint32_t dataLen, uint8_t *outData, uint8_t *key, uint32_t keyLen, 
    uint8_t *initVect, uint32_t initVectLen, uint8_t *aad, uint32_t aadLen, 
    uint8_t *authTag, uint32_t authTagLen)
{
    CRYPTO_GCM_HW_CONTEXT gcmCtx;
    crypto_Aead_Status_E result;
    
    result = Crypto_Aead_Hw_AesGcm_Init(&gcmCtx, CRYPTO_CIOP_ENCRYPT, key, keyLen);
    if (result != CRYPTO_AEAD_CIPHER_SUCCESS)
    {
        return result;
    }
    
    return Crypto_Aead_Hw_AesGcm_Cipher(&gcmCtx, initVect, initVectLen, inputData, 
            dataLen, outData, aad, aadLen, authTag, authTagLen);
}
 
crypto_Aead_Status_E Crypto_Aead_Hw_AesGcm_DecryptAuthDirect(uint8_t *inputData, 
    uint32_t dataLen, uint8_t *outData, uint8_t *key, uint32_t keyLen, 
    uint8_t *initVect, uint32_t initVectLen, uint8_t *aad, uint32_t aadLen, 
    uint8_t *authTag, uint32_t authTagLen)
{
    CRYPTO_GCM_HW_CONTEXT gcmCtx;
    crypto_Aead_Status_E result;
    
    result = Crypto_Aead_Hw_AesGcm_Init(&gcmCtx, CRYPTO_CIOP_DECRYPT, key, keyLen);
    if (result != CRYPTO_AEAD_CIPHER_SUCCESS)
    {
        return result;
    }
    
    return Crypto_Aead_Hw_AesGcm_Cipher(&gcmCtx, initVect, initVectLen, inputData, 
            dataLen, outData, aad, aadLen, authTag, authTagLen);
}
