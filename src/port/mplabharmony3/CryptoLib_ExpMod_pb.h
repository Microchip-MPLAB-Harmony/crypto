/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_ExpMod_pb.h

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

#ifndef _CRYPTOLIB_EXPMOD_PB_INCLUDED
#define _CRYPTOLIB_EXPMOD_PB_INCLUDED

#include <stdint.h>

// Structure definition
typedef struct _PUKCL_expmod {
	nu1  nu1XBase; // (3*u2NLength + 6) words LSW is always zero
	nu1  nu1ModBase;
	nu1  nu1CnsBase;
	nu1  nu1PrecompBase; // xxx words LSW is always zero
	const uint8_t* pfu1ExpBase;    // u2ExpLength words
	u2   u2ModLength;
	u2   u2ExpLength;
	u1   u1Blinding; // Exponent blinding using a 32-bits Xor
	u1   __Padding0;
	u2   __Padding1;
} _PUKCL_EXPMOD, *_PPKCL_EXPMOD;

// Options definition
#define PUKCL_EXPMOD_REGULARRSA 0x01
#define PUKCL_EXPMOD_EXPINPUKCCRAM 0x02
#define PUKCL_EXPMOD_FASTRSA 0x04
#define PUKCL_EXPMOD_OPERATIONMASK 0x07
#define PUKCL_EXPMOD_MODEMASK 0x05 // For faults protection

#define PUKCL_EXPMOD_WINDOWSIZE_MASK 0x18
#define PUKCL_EXPMOD_WINDOWSIZE_1 0x00
#define PUKCL_EXPMOD_WINDOWSIZE_2 0x08
#define PUKCL_EXPMOD_WINDOWSIZE_3 0x10
#define PUKCL_EXPMOD_WINDOWSIZE_4 0x18
#define PUKCL_EXPMOD_WINDOWSIZE_BIT(a) (u2)((a)&PUKCL_EXPMOD_WINDOWSIZE_MASK) >> 3

#endif // _CRYPTOLIB_EXPMOD_PB_INCLUDED
