/**************************************************************************
  Crypto Framework Library Source

  Company:
    Microchip Technology Inc.

  File Name:
    CryptoLib_typedef_pb.h

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

#ifndef _CRYPTOLIB_TYPEDEF_PB_INCLUDED
#define _CRYPTOLIB_TYPEDEF_PB_INCLUDED


//============================================================================
//    Globals Typedef
//==============================================================================

typedef unsigned short  	     nu1;      // 16-bits pointer (starting from 0xF0000)
typedef unsigned short  	     ns1;      // 16-bits pointer (starting from 0xF0000)

typedef unsigned short  	     nu2;      // 16-bits pointer (starting from 0xF0000)
typedef unsigned short  	     ns2;      // 16-bits pointer (starting from 0xF0000)

typedef unsigned short  	     nu4;      // 16-bits pointer (starting from 0xF0000)
typedef unsigned short  	     ns4;      // 16-bits pointer (starting from 0xF0000)

typedef unsigned short  	     nui;      // 16-bits pointer (starting from 0xF0000)
typedef unsigned short  	     nsi;      // 16-bits pointer (starting from 0xF0000)

typedef unsigned short  	     num;      // 16-bits pointer (starting from 0xF0000)
typedef unsigned short  	     nsm;      // 16-bits pointer (starting from 0xF0000)

typedef unsigned short        nv;       // 16-bits pointer (starting from 0xF0000)

typedef unsigned  char           u1;
typedef signed    char           s1;
typedef u1 *			         pu1;                  // pointer near data unsigned
typedef s1 *			         ps1;                  // pointer near data unsigned
typedef u1 *			         pfu1;                 // pointer far data unsigned
typedef s1 *			         pfs1;                 // pointer far data signed
typedef u1 *			         pcu1;                 // pointer near code unsigned
typedef s1 *			         pcs1;                 // pointer near code signed
typedef u1 *			         pfcu1;                // pointer far code unsigned
typedef s1 *			         pfcs1;                // pointer far code signed

typedef unsigned  short          u2;
typedef signed    short          s2;
typedef u2 *			         pu2;                  // pointer near data unsigned
typedef s2 *			         ps2;                  // pointer near data unsigned
typedef u2 *			         pfu2;                 // pointer far data unsigned
typedef s2 *			         pfs2;                 // pointer far data signed
typedef u2 *			         pcu2;                 // pointer near code unsigned
typedef s2 *			         pcs2;                 // pointer near code signed
typedef u2 *			         pfcu2;                // pointer far code unsigned
typedef s2 *			         pfcs2;                // pointer far code signed

typedef unsigned  long int       u4;
typedef signed    long int       s4;
typedef u4 *				     pu4;                  // pointer near data unsigned
typedef s4 *				     ps4;                  // pointer near data unsigned
typedef u4 *				     pfu4;                 // pointer far data unsigned
typedef s4 *				     pfs4;                 // pointer far data signed
typedef u4 *				     pcu4;                 // pointer near code unsigned
typedef s4 *				     pcs4;                 // pointer near code signed
typedef u4 *				     pfcu4;                // pointer far code unsigned
typedef s4 *				     pfcs4;                // pointer far code signed

typedef unsigned  int            ui;
typedef signed    int            si;
typedef unsigned  int            *pui;
typedef signed    int            *psi;

typedef u4                       um;         //CPU Size !!! (ARM = 32Bit)
typedef u4                       u1m;        //CPU Size !!! (ARM = 32Bit)
typedef u4                       u2m;        //CPU Size !!! (ARM = 32Bit)
typedef u4                       u4m;        //CPU Size !!! (ARM = 32Bit)
typedef s4                       sm;         //
typedef u4                       *pum;       //CPU Size !!! (ARM = 32Bit)
typedef s4                       *psm;       //

typedef void                     *pvoid;
typedef void                     *pfvoid;
typedef void                     (*PFUNC)();
typedef void                     (*PFUNC_PAR)(u1);

typedef void ServiceFctType(pvoid);

//==============================================================================
//    Globals Define
//==============================================================================
#define BIT_SET         1           // Set(one)bit
#define BIT_CLEAR       0           // clear bit

#define OK              0x00
#define NOK             0xFF

#define TRUE            1
#define FALSE           0

//==============================================================================
//    General Bit Stucture
//==============================================================================
#define BitField(StartBitField, b0, b1, b2, b3, b4, b5, b6, b7)\
   struct\
   {\
      ui b0  :1;\
      ui b1  :1;\
      ui b2  :1;\
      ui b3  :1;\
      ui b4  :1;\
      ui b5  :1;\
      ui b6  :1;\
      ui b7  :1;\
   } StartBitField

#define ExternBitField(StartBitField, b0, b1, b2, b3, b4, b5, b6, b7)\
   extern struct\
   {\
      ui b0  :1;\
      ui b1  :1;\
      ui b2  :1;\
      ui b3  :1;\
      ui b4  :1;\
      ui b5  :1;\
      ui b6  :1;\
      ui b7  :1;\
   } StartBitField



#endif // _TYPEDEF_INCLUDED








