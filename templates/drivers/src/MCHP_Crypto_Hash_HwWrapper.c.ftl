/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    MCHP_Crypto_Hash_HwWrapper.c

  Summary:
    Crypto Framework Library wrapper file for hardware SHA.

  Description:
    This source file contains the wrapper interface to access the SHA 
    hardware driver for Microchip microcontrollers.
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
#include "device.h"
#include "crypto/common_crypto/MCHP_Crypto_Hash_HwWrapper.h"
<#if HAVE_MCHP_CRYPTO_SHA_HW_6156 == true>
#include "crypto/drivers/drv_crypto_sha_hw_6156.h"
</#if>

// *****************************************************************************
// *****************************************************************************
// Section: Macro definitions
// *****************************************************************************
// *****************************************************************************

#define HASH_SHORT_PAD_SIZE_BYTES     56
#define HASH_LONG_PAD_SIZE_BYTES      112

// *****************************************************************************
// *****************************************************************************
// Section: File scope data
// *****************************************************************************
// *****************************************************************************
       
static const uint8_t hashPaddingMsg[CRYPTO_SHA_BLOCK_SIZE_WORDS_32 << 2] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************

static crypto_Hash_Status_E lCrypto_Hash_Hw_Sha_GetAlgorithm
    (crypto_Hash_Algo_E shaAlgorithm, CRYPTO_SHA_ALGORITHM *shaAlgo)
{
    switch(shaAlgorithm)
    {  
#ifdef CRYPTO_HASH_SHA1_EN
        case CRYPTO_HASH_SHA1:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA1;
            break;
#endif
         
#ifdef CRYPTO_HASH_SHA2_224_EN
        case CRYPTO_HASH_SHA2_224:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA224;
            break; 
#endif
            
#ifdef CRYPTO_HASH_SHA2_256_EN
        case CRYPTO_HASH_SHA2_256:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA256;
            break;
#endif
       
#ifdef CRYPTO_HASH_SHA2_384_EN 
        case CRYPTO_HASH_SHA2_384:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA384;
            break;
#endif
           
#ifdef CRYPTO_HASH_SHA2_512_EN  
        case CRYPTO_HASH_SHA2_512:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA512;
            break;
#endif

<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
#ifdef CRYPTO_HASH_SHA2_512_224_EN 
        case CRYPTO_HASH_SHA2_512_224:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA512_224;
            break;        
#endif
        
#ifdef CRYPTO_HASH_SHA2_512_256_EN
        case CRYPTO_HASH_SHA2_512_256:
            *shaAlgo = CRYPTO_SHA_ALGORITHM_SHA512_256;
            break; 
#endif
</#if>

        default:
            return CRYPTO_HASH_ERROR_ALGO;
    }
    
   return CRYPTO_HASH_SUCCESS;
}

static uint32_t lCrypto_Hash_Hw_Sha_GetBlockSizeBytes(crypto_Hash_Algo_E shaAlgorithm)
{
    uint32_t blockLen = CRYPTO_SHA_BLOCK_SIZE_WORDS_32 << 2; // 128 bytes
    
    CRYPTO_SHA_ALGORITHM shaAlgo = CRYPTO_SHA_ALGORITHM_SHA256;
    lCrypto_Hash_Hw_Sha_GetAlgorithm(shaAlgorithm, &shaAlgo);
    
    if ((shaAlgo == CRYPTO_SHA_ALGORITHM_SHA1) || 
        (shaAlgo == CRYPTO_SHA_ALGORITHM_SHA224) ||
        (shaAlgo == CRYPTO_SHA_ALGORITHM_SHA256))
    {
        blockLen = CRYPTO_SHA_BLOCK_SIZE_WORDS_16 << 2; // 64 bytes   
    }
    
    return blockLen;
}
 
static uint8_t lCrypto_Hash_Hw_Sha_GetPaddingSizeBytes(crypto_Hash_Algo_E shaAlgorithm)
{
    uint8_t paddingLen = HASH_LONG_PAD_SIZE_BYTES;
    
    CRYPTO_SHA_ALGORITHM shaAlgo = CRYPTO_SHA_ALGORITHM_SHA256;
    lCrypto_Hash_Hw_Sha_GetAlgorithm(shaAlgorithm, &shaAlgo);
    
    if ((shaAlgo == CRYPTO_SHA_ALGORITHM_SHA1) || 
        (shaAlgo == CRYPTO_SHA_ALGORITHM_SHA224) ||
        (shaAlgo == CRYPTO_SHA_ALGORITHM_SHA256))
    {
        paddingLen = HASH_SHORT_PAD_SIZE_BYTES;    
    }
    
    return paddingLen;
}

static CRYPTO_SHA_DIGEST_SIZE lCrypto_Hash_Hw_Sha_GetDigestLen
    (crypto_Hash_Algo_E shaAlgorithm)
{
    CRYPTO_SHA_DIGEST_SIZE digestSize;
    
    CRYPTO_SHA_ALGORITHM shaAlgo = CRYPTO_SHA_ALGORITHM_SHA256;
    lCrypto_Hash_Hw_Sha_GetAlgorithm(shaAlgorithm, &shaAlgo);
    
    switch(shaAlgo)
    {
        case CRYPTO_SHA_ALGORITHM_SHA1:
            digestSize = CRYPTO_SHA_ALGORITHM_SHA1;
            break;
         
        case CRYPTO_SHA_ALGORITHM_SHA224:
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
        case CRYPTO_SHA_ALGORITHM_SHA512_224:
</#if>
            digestSize = CRYPTO_SHA_DIGEST_SIZE_SHA224;
            break;        
            
        case CRYPTO_SHA_ALGORITHM_SHA256:
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
        case CRYPTO_SHA_ALGORITHM_SHA512_256:
</#if>
            digestSize = CRYPTO_SHA_DIGEST_SIZE_SHA256;
            break;
          
        case CRYPTO_SHA_ALGORITHM_SHA384:
            digestSize = CRYPTO_SHA_DIGEST_SIZE_SHA384;
            break;
           
        case CRYPTO_SHA_ALGORITHM_SHA512:
            digestSize = CRYPTO_SHA_DIGEST_SIZE_SHA512;
            break;
        
        default:
        digestSize = 0;
    }
    
   return digestSize;
}
 
// *****************************************************************************
// *****************************************************************************
// Section: Hash Algorithms Common Interface Implementation
// *****************************************************************************
// *****************************************************************************
    
crypto_Hash_Status_E Crypto_Hash_Hw_Sha_Init(CRYPTO_HASH_HW_CONTEXT *shaCtx, 
    crypto_Hash_Algo_E shaAlgorithm_en)
{
<#if HAVE_MCHP_CRYPTO_SHA_HW_6156 == false>
    return CRYPTO_HASH_ERROR_NOTSUPPTED;
<#else>
    CRYPTO_SHA_ALGORITHM shaAlgo;
    crypto_Hash_Status_E result;
    
    /* Set algorithm for driver */
    result = lCrypto_Hash_Hw_Sha_GetAlgorithm(shaAlgorithm_en, &shaAlgo);
    if (result != CRYPTO_HASH_SUCCESS)
    {
        return result;
    }
    
    /* Initialize context */
    shaCtx->algo = shaAlgorithm_en;
    shaCtx->totalLen = 0;
    memset(shaCtx->buffer, 0, sizeof(shaCtx->buffer));

    /* Configure the driver */
    DRV_CRYPTO_SHA_Init(shaAlgo);
    
    return CRYPTO_HASH_SUCCESS;
</#if>
}

crypto_Hash_Status_E Crypto_Hash_Hw_Sha_Update(CRYPTO_HASH_HW_CONTEXT *shaCtx,
    uint8_t *data, uint32_t dataLen)
{
<#if HAVE_MCHP_CRYPTO_SHA_HW_6156 == false>
    return CRYPTO_HASH_ERROR_NOTSUPPTED;
<#else>
    uint32_t *localBuffer = 0;
    uint32_t fill;
    uint32_t left;
    uint32_t blockSizeBytes;
    CRYPTO_SHA_BLOCK_SIZE blockSizeWords;
    
    blockSizeBytes = lCrypto_Hash_Hw_Sha_GetBlockSizeBytes(shaCtx->algo);
    blockSizeWords = (CRYPTO_SHA_BLOCK_SIZE)(blockSizeBytes >> 2);
    
    left = shaCtx->totalLen & (blockSizeBytes - 1);
    fill = blockSizeBytes - left;
    shaCtx->totalLen += dataLen;

    if (left && dataLen >= fill)
    {
        memcpy((void *)(shaCtx->buffer + left), data, fill);
        
        /* Load message */
        localBuffer = (uint32_t *)shaCtx->buffer;
        for (uint32_t x = 0; x < dataLen; x += blockSizeBytes)
        {
            DRV_CRYPTO_SHA_Update(localBuffer, blockSizeWords);
            localBuffer += blockSizeWords;
        }
        
        data += fill;
        dataLen -= fill;
        left = 0;
    }

    if (dataLen >= blockSizeBytes)
    {
        DRV_CRYPTO_SHA_Update((uint32_t *)data, blockSizeWords);
        data += blockSizeBytes;
        dataLen -= blockSizeBytes; 
    }

    if (dataLen > 0)
    {
        memcpy((void *)(shaCtx->buffer + left), data, dataLen);
    }

    return CRYPTO_HASH_SUCCESS;
</#if> 
}

crypto_Hash_Status_E Crypto_Hash_Hw_Sha_Final(CRYPTO_HASH_HW_CONTEXT *shaCtx, 
    uint8_t *digest)
{
<#if HAVE_MCHP_CRYPTO_SHA_HW_6156 == false>
    return CRYPTO_HASH_ERROR_NOTSUPPTED;
<#else>
    uint32_t blockSizeBytes;
    uint32_t last;
    uint8_t lenMsg[16] = {0};
    uint8_t paddingSizeBytes;
    uint8_t paddingLen;
    CRYPTO_SHA_DIGEST_SIZE digestLen;
   
    blockSizeBytes = lCrypto_Hash_Hw_Sha_GetBlockSizeBytes(shaCtx->algo);
    paddingSizeBytes = lCrypto_Hash_Hw_Sha_GetPaddingSizeBytes(shaCtx->algo);
   
    /* Get the number of bits */    
    uint64_t totalBits = shaCtx->totalLen << 3;
    
    last = shaCtx->totalLen & (blockSizeBytes - 1);
    if (last < paddingSizeBytes)
    { 
        paddingLen = paddingSizeBytes - last;
    }
    else 
    {
        paddingLen = blockSizeBytes + paddingSizeBytes - last;
    }

    Crypto_Hash_Hw_Sha_Update(shaCtx, (uint8_t *)hashPaddingMsg, paddingLen);
    
    /* Create the message bit length block */
    if (paddingSizeBytes == HASH_SHORT_PAD_SIZE_BYTES)
    {
        lenMsg[0] = (uint8_t)(totalBits >> 56);
        lenMsg[1] = (uint8_t)(totalBits >> 48);
        lenMsg[2] = (uint8_t)(totalBits >> 40);
        lenMsg[3] = (uint8_t)(totalBits >> 32);
        lenMsg[4] = (uint8_t)(totalBits >> 24);
        lenMsg[5] = (uint8_t)(totalBits >> 16);
        lenMsg[6] = (uint8_t)(totalBits >>  8);
        lenMsg[7] = (uint8_t)(totalBits);   
    
        Crypto_Hash_Hw_Sha_Update(shaCtx, lenMsg, 8);    
    }
    else 
    {
        lenMsg[8] = (uint8_t)(totalBits >> 56);
        lenMsg[9] = (uint8_t)(totalBits >> 48);
        lenMsg[10] = (uint8_t)(totalBits >> 40);
        lenMsg[11] = (uint8_t)(totalBits >> 32);
        lenMsg[12] = (uint8_t)(totalBits >> 24);
        lenMsg[13] = (uint8_t)(totalBits >> 16);
        lenMsg[14] = (uint8_t)(totalBits >>  8);
        lenMsg[15] = (uint8_t)(totalBits);
        
        Crypto_Hash_Hw_Sha_Update(shaCtx, lenMsg, 16);   
    }

    digestLen = lCrypto_Hash_Hw_Sha_GetDigestLen(shaCtx->algo);
    DRV_CRYPTO_SHA_GetOutputData((uint32_t *)digest, digestLen);

    return CRYPTO_HASH_SUCCESS;
</#if>
}

crypto_Hash_Status_E Crypto_Hash_Hw_Sha_Digest(uint8_t *data, uint32_t dataLen, 
    uint8_t *digest, crypto_Hash_Algo_E shaAlgorithm_en)
{
<#if HAVE_MCHP_CRYPTO_SHA_HW_6156 == false>
    return CRYPTO_HASH_ERROR_NOTSUPPTED;
<#else>
    CRYPTO_HASH_HW_CONTEXT shaCtx;
    crypto_Hash_Status_E result = CRYPTO_HASH_SUCCESS;

    result = Crypto_Hash_Hw_Sha_Init(&shaCtx, shaAlgorithm_en);
    if (result != CRYPTO_HASH_SUCCESS)
    {
        return result;
    }
    
    result = Crypto_Hash_Hw_Sha_Update(&shaCtx, data, dataLen);
    if (result != CRYPTO_HASH_SUCCESS)
    {
        return result;
    }
    
    return Crypto_Hash_Hw_Sha_Final(&shaCtx, digest);
</#if>
}
