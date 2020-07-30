/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_buildInfo.c

  Description:
 * Make visible the compiler options.
 * This file should be gimmicked to build every time
 * (on the Building tab of the project properties):
 *    touch ../src/cryptoST/cryptotouch ../src/cryptoSTSTE_buildInfo.c
 * 
 * Also relies on a makefile parameter to the compiler command
 * line in Properties/XC32(GlobalOptions)/AdditionalOptions: 
 *     -D__PROCESSOR__=$(MP_PROCESSOR_OPTION)
 *******************************************************************************
 */

//DOM-IGNORE-BEGIN
/*****************************************************************************
 Copyright (C) 2013-2020 Microchip Technology Inc. and its subsidiaries.

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

//DOM-IGNORE-END


#include "cryptoSTE_buildInfo.h"
#include "cryptoSTE_print.h" // for STRINGIZE

/* public -- this is a singleton */
cryptoSTE_buildInfo_t cryptoSTE_buildInfo =
{
    .buildDate = __DATE__,
    .buildTime = __TIME__,
#if __OPTIMIZE__
    .optimized = "yes",
#else
    .optimized = "no",
#endif
    .processor = STRINGIZE(__PROCESSOR__),
    .configuration = STRINGIZE(__CONFIG__),
};
