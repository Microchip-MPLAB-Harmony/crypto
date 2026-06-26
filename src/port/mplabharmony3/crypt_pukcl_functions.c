/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    crypt_pukcl_functions.c

  Summary:
    Crypto Framework Libarary source file for hardware Cryptography

  Description:
    This file provides an example for interfacing with the PUKCC module
    on the SAME5x device family.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*
Copyright (C) 2013-2026, Microchip Technology Inc., and its subsidiaries. All rights reserved.

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

#include "wolfssl/wolfcrypt/port/pic32/CryptoLib_typedef_pb.h"
#include "wolfssl/wolfcrypt/port/pic32/CryptoLib_mapping_pb.h"
#include "wolfssl/wolfcrypt/port/pic32/CryptoLib_cf_pb.h"
#include "wolfssl/wolfcrypt/port/pic32/CryptoLib_Headers_pb.h"
#include "wolfssl/wolfcrypt/port/pic32/crypt_pukcl_functions.h"
#include <stdint.h>
#include <string.h>

PPUKCL_PARAM pvPUKCLParam;
PUKCL_PARAM  PUKCLParam;

#define PUKCL_SELFTEST_CHECKSUM1 0x6E70DDD2
#define PUKCL_SELFTEST_CHECKSUM2 0x25c8d64f


int8_t SelfTestState = 0;

int8_t crypt_pukcl_SelfTest(void)
{
    if (SelfTestState != 0)
    {
        return SelfTestState;
    }
	/* Clear contents of PUKCLParam */
	memset(&PUKCLParam, 0, sizeof(PUKCL_PARAM));

	pvPUKCLParam = &PUKCLParam;
	vPUKCL_Process(SelfTest, pvPUKCLParam);

	while (PUKCL(u2Status) != PUKCL_OK)
		;

    
	if (pvPUKCLParam->P.PUKCL_SelfTest.u4Version != PUKCL_VERSION)
    {
        SelfTestState = -1;
    }
    else if (pvPUKCLParam->P.PUKCL_SelfTest.u4CheckNum1 != PUKCL_SELFTEST_CHECKSUM1)
    {
        SelfTestState = -2;
    }
	else if (pvPUKCLParam->P.PUKCL_SelfTest.u4CheckNum2 != PUKCL_SELFTEST_CHECKSUM2)
    {
        SelfTestState = -3;
    }
    else
    {
        SelfTestState = 1;
    }
    return SelfTestState;
}

uint32_t SecureCopy(uint8_t * dst, uint32_t dstSz, const uint8_t * src, uint32_t srcSz, uint8_t reverse)
{
    // clean out the destination.
    memset(dst, 0, dstSz);
    uint32_t bytesToCopy = dstSz < srcSz ? dstSz : srcSz;
    if (reverse == 0)
    {
        uint32_t x = 0;
        for (x = 0; x < bytesToCopy; x++)
        {
            *(dst++) = *(src++);
        }
    }
    else
    {
        uint8_t * revDst = dst + bytesToCopy - 1;
        uint32_t x = 0;
        for (x = 0; x < bytesToCopy; x++)
        {
            *(revDst--) = *(src++);
        }        
    }
    return bytesToCopy;
}