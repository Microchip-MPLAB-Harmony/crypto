/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_ZpEccQuickDualMul_pb.h

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

#ifndef __PUKCL_ZPECC_QUICKDUALMULT_PB_INCLUDED__
#define __PUKCL_ZPECC_QUICKDUALMULT_PB_INCLUDED__

#define AbsVal(a) ((a > 0) ? a : (-a))

// Structure definition
typedef struct _PUKCL_ZpEccQuickDualMul {
	pu1 pu1ModCnsBase;
	pu1 pu1PointABase;
	pu1 pu1PointBBase;
	pu1 pu1KABBase;
	pu1 pu1AWorkBase;
	// pu1       pu1ABase;
	u2 u2ModLength;
	u2 u2KLength;
} _PUKCL_ZPECCQUICKDUALMUL, *_PPUKCL_ZPECCQUICKDUALMUL;

#define PUKCL_ZPECCMUL_SCAL_IN_CLASSIC_RAM (0x01 << 8)
#define PUKCL_ZPECCMUL_WINSIZE_MASK 0x0F
#define PUKCL_ZPECCMUL_WINSIZE_B_VAL_TO_OPT(W) (((W)&PUKCL_ZPECCMUL_WINSIZE_MASK) << 4)
#define PUKCL_ZPECCMUL_WINSIZE_A_VAL_TO_OPT(W) ((W)&PUKCL_ZPECCMUL_WINSIZE_MASK)
#define PUKCL_ZPECCMUL_WINSIZE_B_OPT_TO_VAL(Option) (((Option) >> 4) & PUKCL_ZPECCMUL_WINSIZE_MASK)
#define PUKCL_ZPECCMUL_WINSIZE_A_OPT_TO_VAL(Option) ((Option)&PUKCL_ZPECCMUL_WINSIZE_MASK)

#endif //__PUKCL_ZPECC_QUICKDUALMULT_PB_INCLUDED__
