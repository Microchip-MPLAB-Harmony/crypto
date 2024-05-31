/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_JumpTable_pb.h

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

#ifndef _CRYPTOLIB_JUMPTABLE_PB_INCLUDED_
#define _CRYPTOLIB_JUMPTABLE_PB_INCLUDED_

extern ServiceFctType __vCPKCLCsClearFlags;
extern ServiceFctType __vCPKCLCsComp;
extern ServiceFctType __vCPKCLCsCondCopy;
extern ServiceFctType __vCPKCLCsFastCopy;
extern ServiceFctType __vCPKCLCsFill;
extern ServiceFctType __vCPKCLCsFmult;
extern ServiceFctType __vCPKCLCsNOP;
extern ServiceFctType __vCPKCLCsRng;
extern ServiceFctType __vCPKCLCsSelfTest;
extern ServiceFctType __vCPKCLCsSmult;
extern ServiceFctType __vCPKCLCsSquare;
extern ServiceFctType __vCPKCLCsSwap;
extern ServiceFctType __vCPKCLCsZpEccAddFast;
extern ServiceFctType __vCPKCLCsZpEcConvProjToAffine;
extern ServiceFctType __vCPKCLCsZpEcPointIsOnCurve;
extern ServiceFctType __vCPKCLCsZpEcConvAffineToProjective;
extern ServiceFctType __vCPKCLCsZpEcRandomiseCoordinate;
extern ServiceFctType __vCPKCLCsZpEccDblFast;
extern ServiceFctType __vCPKCLCsZpEccMulFast;
extern ServiceFctType __vCPKCLCsZpEcDsaGenerateFast;
extern ServiceFctType __vCPKCLCsZpEcDsaVerifyFast;
extern ServiceFctType __vCPKCLCsGF2NEccAddFast;
extern ServiceFctType __vCPKCLCsGF2NEcConvProjToAffine;
extern ServiceFctType __vCPKCLCsGF2NEcPointIsOnCurve;
extern ServiceFctType __vCPKCLCsGF2NEcRandomiseCoordinate;
extern ServiceFctType __vCPKCLCsGF2NEcConvAffineToProjective;
extern ServiceFctType __vCPKCLCsGF2NEccDblFast;
extern ServiceFctType __vCPKCLCsGF2NEccMulFast;
extern ServiceFctType __vCPKCLCsGF2NEcDsaGenerateFast;
extern ServiceFctType __vCPKCLCsGF2NEcDsaVerifyFast;
extern ServiceFctType __vCPKCLCsCRT;
extern ServiceFctType __vCPKCLCsDiv;
extern ServiceFctType __vCPKCLCsExpMod;
extern ServiceFctType __vCPKCLCsGCD;
extern ServiceFctType __vCPKCLCsPrimeGen;
extern ServiceFctType __vCPKCLCsRedMod;

#endif
