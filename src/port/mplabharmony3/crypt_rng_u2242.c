/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    random_same70.c

  Summary:
    Crypto Framework Library source for cryptographic functions.

  Description:
    This source file contains functions that make up the Cryptographic
	Framework Library for PIC32 families of Microchip micro-controllers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2017-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

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


#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif
#include "configuration.h"
#if defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO) && defined(WOLFSSL_HAVE_MCHP_HW_CRYPTO_TRNG_HW_U2242) && defined(WOLFSSL_HAVE_MCHP_HW_RANDOM)

#include "wolfssl/wolfcrypt/settings.h"

#include "wolfssl/wolfcrypt/random.h"

#include "wolfssl/wolfcrypt/error-crypt.h"

#include "definitions.h"
#include "wolfssl/wolfcrypt/port/pic32/crypt_rng_hw.h"


#define RNG_BYTES_AT_A_TIME 4


int CRYPT_RNG_HwInit(void)
{
    /* Enable Peripheral clock for TRNG in Power Management Controller */
    uint32_t apbcBit = 1u << (ID_TRNG&31);
    if ((MCLK_REGS->MCLK_APBCMASK & apbcBit) != apbcBit)
    {
        MCLK_REGS->MCLK_APBCMASK |= apbcBit;
    }
    TRNG_REGS->TRNG_CTRLA = 0x2;    
    return 0;
}



/* sz is number of bytes */
int CRYPT_RNG_GenerateBlock(byte* output, word32 sz)
{
    while (sz)
    {
        /* get 32 bits - BLOCKING */
        while (!(TRNG_REGS->TRNG_INTFLAG & 0x1))
        {
            /* Wait until data ready. */
        }

        /* get 32 bits */
        uint32_t result = TRNG_REGS->TRNG_DATA;
        TRNG_REGS->TRNG_INTFLAG = 0x1;
        /* stuff the data into the output buffer. Watch for buffer overrun */
        if (sz < RNG_BYTES_AT_A_TIME)
        {
            memcpy((void *)output, (void*)&result, sz);
            sz = 0;
        }
        else
        {
            memcpy((void *)output, (void*)&result, RNG_BYTES_AT_A_TIME);
            sz -= RNG_BYTES_AT_A_TIME;

            /* bump the byte buffer by 4 since we are doing 32 bit randoms */
            output += RNG_BYTES_AT_A_TIME;
        }

        /* memory barrier */
        __DMB();
    }

    return 0;
}


int CRYPT_RNG_FreeRng(void)
{
    /* disable */
    TRNG_REGS->TRNG_CTRLA = 0x0;    

    /* Disable Peripheral Clock to TRNG by writing 1 to bit position */
    /* TRNG >=32 use PCDR1 not PCDR0 and remove 32 bit positions */
    uint32_t apbcBit = 1u << (ID_TRNG&31);
    if ((MCLK_REGS->MCLK_APBCMASK & apbcBit) == apbcBit)
    {
        MCLK_REGS->MCLK_APBCMASK ^= apbcBit;
    }

    return 0;
}



/* used by random.c */
int wc_GenerateSeed(OS_Seed* os, byte* seed, word32 sz)
{
    int status;

    /* Make sure power is on, etc */
    status = CRYPT_RNG_HwInit();
    if (!status)
    {
        status = CRYPT_RNG_GenerateBlock(seed, sz);
    }

    return status;
}


#endif
