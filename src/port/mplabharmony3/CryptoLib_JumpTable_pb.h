/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_JumpTable_pb.h

  Summary:
    Crypto Framework Libarary interface file for hardware Cryptography

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

#ifndef _CRYPTOLIB_JUMPTABLE_PB_INCLUDED_
#define _CRYPTOLIB_JUMPTABLE_PB_INCLUDED_

typedef struct _PUKCL_param *PPUKCL_PARAM;
typedef void (*PPUKCL_FUNC)(PPUKCL_PARAM);
/* JumpTable address + 1 as it is thumb code */
#define __vCPKCLCsJumpTableStart 0x02000001
#define __vPUKCLCsGF2NEcRandomiseCoordinate ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x4))
#define __vPUKCLCsRedMod ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x8))
#define __vPUKCLCsCondCopy ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0xc))
#define __vPUKCLCsClearFlags ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x10))
#define __vPUKCLCsGF2NEccDblFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x14))
#define __vPUKCLCsFmult ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x18))
#define __vPUKCLCsGCD ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x1c))
#define __vPUKCLCsGF2NEccMulFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x20))
#define __vPUKCLCsComp ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x24))
#define __vPUKCLCsZpEcDsaGenerateFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x28))
#define __vPUKCLCsZpEcDsaVerifyFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x2c))
#define __vPUKCLCsGF2NEccAddFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x30))
#define __vPUKCLCsZpEccDblFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x34))
#define __vPUKCLCsZpEccAddFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x38))
#define __vPUKCLCsFill ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x3c))
#define __vPUKCLCsZpEccMulFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x40))
#define __vPUKCLCsGF2NEcDsaVerifyFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x44))
#define __vPUKCLCsSmult ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x48))
#define __vPUKCLCsSquare ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x4c))
#define __vPUKCLCsDiv ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x50))
#define __vPUKCLCsSelfTest ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x54))
#define __vPUKCLCsPrimeGen ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x58))
#define __vPUKCLCsCRT ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x5c))
#define __vPUKCLCsFastCopy ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x60))
#define __vPUKCLCsGF2NEcDsaGenerateFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x64))
#define __vPUKCLCsZpEcConvAffineToProjective ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x68))
#define __vPUKCLCsGF2NEcPointIsOnCurve ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x6c))
#define __vPUKCLCsRng ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x70))
#define __vPUKCLCsSwap ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x74))
#define __vPUKCLCsZpEcRandomiseCoordinate ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x78))
#define __vPUKCLCsGF2NEcConvAffineToProjective ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x7c))
#define __vPUKCLCsExpMod ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x80))
#define __vPUKCLCsZpEcConvProjToAffine ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x84))
#define __vPUKCLCsGF2NEcConvProjToAffine ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x88))
#define __vPUKCLCsZpEcPointIsOnCurve ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x8c))
#define __vPUKCLCsZpEccAddSubFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x94))
#define __vPUKCLCsZpEccQuickDualMulFast ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x98))
#define __vPUKCLCsZpEcDsaQuickVerify ((PPUKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x9c))
#endif
