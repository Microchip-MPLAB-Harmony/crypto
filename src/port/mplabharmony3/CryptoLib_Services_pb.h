/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_Services_pb.h

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

#ifndef _CRYPTOLIB_SERVICES_PB_INCLUDED
#define _CRYPTOLIB_SERVICES_PB_INCLUDED

// Services definition
#define PUKCL_SERVICE_RedMod 0x50
#define PUKCL_SERVICE_CondCopy 0x51
#define PUKCL_SERVICE_Div 0x52
#define PUKCL_SERVICE_ZpEcDsaGenerateFast 0x53
#define PUKCL_SERVICE_GF2NEcRandomiseCoordinate 0x54
#define PUKCL_SERVICE_ZpEcDsaVerifyFast 0x55
#define PUKCL_SERVICE_ZpEcConvProjToAffine 0x56
#define PUKCL_SERVICE_GF2NEcPointIsOnCurve 0x57
#define PUKCL_SERVICE_CRT 0x58
#define PUKCL_SERVICE_GF2NEccAddFast 0x59
#define PUKCL_SERVICE_SelfTest 0x5b
#define PUKCL_SERVICE_FastCopy 0x5c
#define PUKCL_SERVICE_GCD 0x5d
#define PUKCL_SERVICE_ZpEcRandomiseCoordinate 0x5e
#define PUKCL_SERVICE_ClearFlags 0x5f
#define PUKCL_SERVICE_ZpEccDblFast 0x60
#define PUKCL_SERVICE_ZpEcConvAffineToProjective 0x61
#define PUKCL_SERVICE_Rng 0x62
#define PUKCL_SERVICE_Swap 0x63
#define PUKCL_SERVICE_GF2NEccMulFast 0x64
#define PUKCL_SERVICE_ZpEccMulFast 0x65
#define PUKCL_SERVICE_ZpEccAddFast 0x66
#define PUKCL_SERVICE_Smult 0x67
#define PUKCL_SERVICE_ZpEcPointIsOnCurve 0x68
#define PUKCL_SERVICE_GF2NEccDblFast 0x69
#define PUKCL_SERVICE_Comp 0x6b
#define PUKCL_SERVICE_ExpMod 0x6c
#define PUKCL_SERVICE_Square 0x6d
#define PUKCL_SERVICE_PrimeGen 0x6e
#define PUKCL_SERVICE_Fill 0x6f
#define PUKCL_SERVICE_GF2NEcDsaGenerateFast 0x70
#define PUKCL_SERVICE_Fmult 0x71
#define PUKCL_SERVICE_GF2NEcConvProjToAffine 0x72
#define PUKCL_SERVICE_GF2NEcConvAffineToProjective 0x73
#define PUKCL_SERVICE_GF2NEcDsaVerifyFast 0x74
#define PUKCL_SERVICE_ZpEccAddSubFast 0x75
#define PUKCL_SERVICE_ZpEccQuickDualMulFast 0x76
#define PUKCL_SERVICE_ZpEcDsaQuickVerify 0x77

extern ServiceFctType __vPUKCLCsExpMod;
extern ServiceFctType __vPUKCLCsPrimeGen;
extern ServiceFctType __vPUKCLCsSquare;
extern ServiceFctType __vPUKCLCsGF2NEcDsaGenerateFast;
extern ServiceFctType __vPUKCLCsComp;
extern ServiceFctType __vPUKCLCsZpEccMulFast;
extern ServiceFctType __vPUKCLCsFmult;
extern ServiceFctType __vPUKCLCsZpEcDsaGenerateFast;
extern ServiceFctType __vPUKCLCsRng;
extern ServiceFctType __vPUKCLCsGF2NEcConvAffineToProjective;
extern ServiceFctType __vPUKCLCsSelfTest;
extern ServiceFctType __vPUKCLCsZpEcDsaVerifyFast;
extern ServiceFctType __vPUKCLCsGF2NEcConvProjToAffine;
extern ServiceFctType __vPUKCLCsGF2NEccMulFast;
extern ServiceFctType __vPUKCLCsGF2NEccAddFast;
extern ServiceFctType __vPUKCLCsGCD;
extern ServiceFctType __vPUKCLCsDiv;
extern ServiceFctType __vPUKCLCsCondCopy;
extern ServiceFctType __vPUKCLCsClearFlags;
extern ServiceFctType __vPUKCLCsRedMod;
extern ServiceFctType __vPUKCLCsZpEccAddFast;
extern ServiceFctType __vPUKCLCsGF2NEccDblFast;
extern ServiceFctType __vPUKCLCsSmult;
extern ServiceFctType __vPUKCLCsFill;
extern ServiceFctType __vPUKCLCsGF2NEcRandomiseCoordinate;
extern ServiceFctType __vPUKCLCsFastCopy;
extern ServiceFctType __vPUKCLCsZpEcPointIsOnCurve;
extern ServiceFctType __vPUKCLCsZpEcConvProjToAffine;
extern ServiceFctType __vPUKCLCsZpEccDblFast;
extern ServiceFctType __vPUKCLCsGF2NEcDsaVerifyFast;
extern ServiceFctType __vPUKCLCsZpEcConvAffineToProjective;
extern ServiceFctType __vPUKCLCsZpEcRandomiseCoordinate;
extern ServiceFctType __vPUKCLCsSwap;
extern ServiceFctType __vPUKCLCsCRT;
extern ServiceFctType __vPUKCLCsGF2NEcPointIsOnCurve;
extern ServiceFctType __vPUKCLCsZpEccQuickDualMulFast;
extern ServiceFctType __vPUKCLCsZpEcDsaQuickVerify;
#endif //_CRYPTOLIB_SERVICES_PB_INCLUDED
