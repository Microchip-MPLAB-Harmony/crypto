/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_CRT_pb.h

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

#ifndef _CRYPTOLIB_CRT_PB_INCLUDED
#define _CRYPTOLIB_CRT_PB_INCLUDED

// Structure definition
typedef struct _CRYPTOLIB_crt {
	nu1  nu1XBase;       // x
	nu1  nu1ModBase;     // Primes P and Q
	nu1  nu1PrecompBase; // R, precomp
	nu1  __Padding0;
	pfu1 pfu1ExpBase; // Exponent
	u2   u2ModLength; // N=length of P or Q in bytes
	u2   u2ExpLength; // Exponent length in bytes
	u1   u1Blinding;  // Exponent blinding using a 32-bits Xor
	u1   __Padding1;
	u2   __Padding2;
} _PUKCL_CRT, *_PPKCL_CRT;

// Options definition
// None

#endif // _CRYPTOLIB_CRT_PB_INCLUDED
