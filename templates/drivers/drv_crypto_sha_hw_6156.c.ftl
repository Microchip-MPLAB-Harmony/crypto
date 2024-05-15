/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    drv_crypto_sha_hw_6156.c

  Summary:
    Crypto Framework Libarary interface file for hardware SHA.

  Description:
    This source file contains the interface that make up the SHA hardware 
    driver for the following families of Microchip microcontrollers:
    PIC32CXMTxx, SAMA5D2, SAM9X60.
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

#include "definitions.h"
#include "device.h"
#include "drv_crypto_sha_hw_6156.h"

// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************

static void lDRV_CRYPTO_SHA_Configure(CRYPTO_SHA_ALGORITHM shaAlgo)
{
    CRYPTO_SHA_MR shaMr = {0};
    CRYPTO_SHA_CR shaCr = {0};
    
    shaMr.s.SMOD = CRYPTO_SHA_AUTO_START;
    shaMr.s.PROCDLY = 0;
    shaMr.s.UIHV = 0; 
    shaMr.s.UIEHV = 0; 
    shaMr.s.ALGO = shaAlgo;
    shaMr.s.DUALBUFF = 0;
    shaMr.s.CHECK = 0;
    shaMr.s.CHKCNT = 0; 
    
<#if __PROCESSOR?matches("PIC32CX.*MT.*") || __PROCESSOR?matches("SAM9X60")>
    shaMr.s.AOE = 0;
    shaMr.s.BPE = 0; 
    shaMr.s.TMPLCK = 0;
</#if>
  
    SHA_REGS->SHA_MR = shaMr.v;
  
    /* No automatic padding */
    SHA_REGS->SHA_MSR = 0;
    SHA_REGS->SHA_BCR = 0;
    
    /* First message */
    shaCr.s.FIRST = 1; 
    SHA_REGS->SHA_CR = shaCr.v;
}

static void lDRV_CRYPTO_SHA_WriteInputData(uint32_t *inputDataBuffer, 
                                           uint8_t blockSize)
{
    uint8_t i;
    uint8_t len1 = 0;
    uint8_t len2 = 0;
    
    if (blockSize <= CRYPTO_SHA_BLOCK_SIZE_WORDS_16) 
    {
        len1 = blockSize;
    } 
    else 
    {
        len1 = CRYPTO_SHA_BLOCK_SIZE_WORDS_16;
        len2 = CRYPTO_SHA_BLOCK_SIZE_WORDS_16;
    }
	
    for (i = 0; i < len1; i++) 
    {
        SHA_REGS->SHA_IDATAR[i] = *inputDataBuffer;
        inputDataBuffer++;
    }

    if (len2) 
    {
        for (i = 0; i < len2; i++) 
        {
            SHA_REGS->SHA_IODATAR[i] = *inputDataBuffer;
            inputDataBuffer++;
        }
    }
}

static void lDRV_CRYPTO_SHA_ReadOutputData(uint32_t *outputDataBuffer, 
    uint8_t bufferLen)
{   
    uint8_t i;
    
    for (i = 0; i < bufferLen; i++) 
    {
        *outputDataBuffer = SHA_REGS->SHA_IODATAR[i];
        outputDataBuffer++;
    }    
}

// *****************************************************************************
// *****************************************************************************
// Section: SHA256 Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

void DRV_CRYPTO_SHA_Init(CRYPTO_SHA_ALGORITHM shaAlgo)
{
    /* Software reset */
    SHA_REGS->SHA_CR = SHA_CR_SWRST_Msk;
    
    /* Set all the fields needed to set-up the SHA engine */
    lDRV_CRYPTO_SHA_Configure(shaAlgo);
}

void DRV_CRYPTO_SHA_Update(uint32_t *data, CRYPTO_SHA_BLOCK_SIZE dataBlockSize)
{
    /* Write the data to be hashed to the input data registers */
    lDRV_CRYPTO_SHA_WriteInputData(data, dataBlockSize);
    
    /* Block until processing is done */
    while (!(SHA_REGS->SHA_ISR & SHA_ISR_DATRDY_Msk))
    {
        ;
    }
}

void DRV_CRYPTO_SHA_GetOutputData(uint32_t *digest, 
    CRYPTO_SHA_DIGEST_SIZE digestLen)
{
    /* Read the output (clear interruption) */
    lDRV_CRYPTO_SHA_ReadOutputData(digest, (uint8_t)digestLen);
}
