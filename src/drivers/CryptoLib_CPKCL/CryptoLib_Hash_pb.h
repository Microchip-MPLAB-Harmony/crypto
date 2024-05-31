/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_Hash_pb.h

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

#ifndef _CRYPTOLIB_HASH_INCLUDED
#define _CRYPTOLIB_HASH_INCLUDED

// Structure definition
// POUR MD2 :	Le CheckSum se fait dans le Working Space;
// 				Le Buffer X est assimile a une valeur de hashage donc place dans pu1HBase
typedef struct _CPKCL_hash {
               pu1       pu1WorkSpace;
               pu1       pu1MBase;
               pu1       pu1HBase;
               pu1       pu1WorkSpace2;
               u2        __Padding1;
               u2        __Padding2;
               } _CPKCL_HASH, *_PPKCL_HASH;

// bits of the option:
// (b1,b0) :
//        0x0001 : Init
//        0x0002 : Current
// (b9,b8) :
//        0x0000 : SHA1
//        0x0100 : SHA256
//        0x0200 : SHA384
//        0x0300 : SHA512
// (b2) :
//        0x0000 : MSB First
//        0x0004 : LSB First

// Service definition
// SubServices definition
#define CPKCL_HASH_VOID			   0x00
#define CPKCL_HASH_SHA1			   0x01
#define CPKCL_HASH_MD2			   0x05
#define CPKCL_HASH_MD5			   0x06

// Options definition
// Choose function
#define CPKCL_HASH_INITIALISE       0x0001
#define CPKCL_HASH_UPDATE           0x0002
//#define CPKCL_HASH_???            0x0003
// Choose MSB/LSB
#define CPKCL_HASH_LSBFIRST         0x0008
#define CPKCL_HASH_MSBFIRST         0x0000
#define CPKCL_HASH_MSBLSBFIRST_MASK 0x0008




// SubServices definition
#define CPKCL_HASH_VOID			   0x00
#define CPKCL_HASH_SHA1			   0x01

// Options definition
// Choose function
#define CPKCL_HASH_INITIALISE       0x0001
#define CPKCL_HASH_UPDATE           0x0002
//#define CPKCL_HASH_???            0x0003
// Choose MSB/LSB
#define CPKCL_HASH_LSBFIRST         0x0008
#define CPKCL_HASH_MSBFIRST         0x0000
#define CPKCL_HASH_MSBLSBFIRST_MASK 0x0008
#endif // _CRYPTOLIB_HASH_INCLUDED
