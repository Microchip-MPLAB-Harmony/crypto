/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_JumpTable_Addr_pb.h

  Summary:
    Crypto Framework Libarary interface file for hardware Cryptography.

  Description:
    This file provides an example for interfacing with the CPKCC module
    on the PIC32CXMxxx device family.
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

#ifndef _CRYPTOLIB_JUMPTABLE_ADDR_PB_INCLUDED_
#define _CRYPTOLIB_JUMPTABLE_ADDR_PB_INCLUDED_

#include "CryptoLib_typedef_pb.h"
#include "CryptoLib_mapping_pb.h"
#include "CryptoLib_Headers_pb.h"

typedef void (*PPKCL_FUNC) (PCPKCL_PARAM);

// JumpTable address + 1 as it is thumb code
#define __vCPKCLCsJumpTableStart                0x02020001
#define __vCPKCLCsNOP							      ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x00 ))
#define __vCPKCLCsSelfTest						  ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x04 ))
#define __vCPKCLCsFill          				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x08 ))
#define __vCPKCLCsSwap          				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x0c ))
#define __vCPKCLCsFastCopy      				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x10 ))
#define __vCPKCLCsCondCopy      				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x14 ))
#define __vCPKCLCsClearFlags    				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x18 ))
#define __vCPKCLCsComp          				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x1c ))
#define __vCPKCLCsFmult         				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x20 ))
#define __vCPKCLCsSmult         				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x24 ))
#define __vCPKCLCsSquare        				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x28 ))
#define __vCPKCLCsDiv           				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x2c ))
#define __vCPKCLCsRedMod        				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x30 ))
#define __vCPKCLCsExpMod        				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x34 ))
#define __vCPKCLCsCRT           				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x38 ))
#define __vCPKCLCsGCD           				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x3c ))
#define __vCPKCLCsPrimeGen      				((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x40 ))
#define __vCPKCLCsZpEcPointIsOnCurve			((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x44 ))
#define __vCPKCLCsZpEcRandomiseCoordinate       ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x48 ))
#define __vCPKCLCsZpEcConvAffineToProjective    ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x4c ))
#define __vCPKCLCsZpEccAddFast                  ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x50 ))
#define __vCPKCLCsZpEccDblFast                  ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x54 ))
#define __vCPKCLCsZpEccMulFast                  ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x58 ))
#define __vCPKCLCsZpEcDsaGenerateFast           ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x5c ))
#define __vCPKCLCsZpEcDsaVerifyFast             ((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x60 ))
#define __vCPKCLCsZpEcConvProjToAffine			((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x64 ))
#define __vCPKCLCsGF2NEcRandomiseCoordinate	  	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x68 ))
#define __vCPKCLCsGF2NEcConvProjToAffine       	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x6c ))
#define __vCPKCLCsGF2NEcConvAffineToProjective 	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x70 ))
#define __vCPKCLCsGF2NEcPointIsOnCurve         	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x74 ))
#define __vCPKCLCsGF2NEccAddFast               	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x78 ))
#define __vCPKCLCsGF2NEccDblFast               	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x7C ))
#define __vCPKCLCsGF2NEccMulFast               	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x80 ))
#define __vCPKCLCsGF2NEcDsaGenerateFast        	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x84 ))
#define __vCPKCLCsGF2NEcDsaVerifyFast          	((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x88 ))
#define __vCPKCLCsRng         					((PPKCL_FUNC)(__vCPKCLCsJumpTableStart + 0x8C ))


#endif // _CRYPTOLIB_JUMPTABLE_ADDR_PB_INCLUDED_
