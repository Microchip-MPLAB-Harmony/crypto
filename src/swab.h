/**************************************************************************
  Crypto Framework Library Header

  Company:
    Microchip Technology Inc.

  File Name:
    swab.h

  Summary:
    Crypto Framework Library header for cryptographic functions.

  Description:
    This header file contains function prototypes and definitions of
    the data types and constants that make up the Cryptographic Framework
    Library for PIC32 families of Microchip microcontrollers.
**************************************************************************/

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/

#ifndef ARM_SWAB_H_
#define ARM_SWAB_H_

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_ARCH_ARMV5TE)

static inline uint16_t swab16(uint16_t value)
{
	uint32_t result;

	result = ((value & 0xff00) >> 8) |
	         ((value & 0x00ff) << 8);

	return result;
}

static inline uint32_t swab32(uint32_t value)
{
	uint32_t result;

	// ARMv5TE does not support the "rev" instruction
	asm("eor r3, %1, %1, ror #16\n"
	    "bic r3, r3, #0xff0000\n"
	    "mov %0, %1, ror #8\n"
	    "eor %0, %0, r3, lsr #8" : "=r"(result) : "0"(value) : "r3","cc");
	return result;
}

#elif defined(CONFIG_ARCH_ARMV7A) ||\
      defined(CONFIG_ARCH_ARMV7M)

static inline uint16_t swab16(uint16_t value)
{
	uint32_t result;

	asm("rev16 %0, %1" : "=r"(result) : "r"(value));

	return result;
}

static inline uint32_t swab32(uint32_t value)
{
	uint32_t result;

	asm("rev %0, %1" : "=r"(result) : "r"(value));

	return result;
}

#endif

#endif /* ARM_SWAB_H_ */
