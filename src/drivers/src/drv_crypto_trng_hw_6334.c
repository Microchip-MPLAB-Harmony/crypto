/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    drv_crypto_trng_hw_6334.c

  Summary:
    Crypto Framework Library interface file for hardware TRNG.

  Description:
    This source file contains the interface that make up the TRNG hardware 
    driver for the following families of Microchip microcontrollers:
    PIC32CXMTxx, SAMx70, SAMA5D2, SAM9X60.
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
#include "definitions.h"
#include "drv_crypto_trng_hw_6334.h"

// *****************************************************************************
// *****************************************************************************
// Section: Macro definitions
// *****************************************************************************
// *****************************************************************************

#define RNG_BYTES_AT_A_TIME 4

// *****************************************************************************
// *****************************************************************************
// Section: RNG Common Interface Implementation
// *****************************************************************************
// *****************************************************************************

void DRV_CRYPTO_TRNG_Generate(uint8_t *rngData, uint32_t rngLen)
{
    /* rngLen is number of bytes */
    while (rngLen)
    {
        uint32_t result = TRNG_ReadData();

        /* Stuff the data into the output buffer. Watch for buffer overrun. */
        if (rngLen < RNG_BYTES_AT_A_TIME)
        {
            memcpy((void *)rngData, (void*)&result, rngLen);
            rngLen = 0;
        }
        else
        {
            memcpy((void *)rngData, (void*)&result, RNG_BYTES_AT_A_TIME);
            rngLen -= RNG_BYTES_AT_A_TIME;

            /* Bump the byte buffer by 4 since we are doing 32 bit randoms */
            rngData += RNG_BYTES_AT_A_TIME;
        }

        /* memory barrier */
        __DMB();
    }

    return;
}
