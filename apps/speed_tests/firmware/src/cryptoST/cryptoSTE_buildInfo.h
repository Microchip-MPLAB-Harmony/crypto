/*******************************************************************************
  Crypto Speed Test Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_buildInfo.h

  Description:
 * Make visible the compiler options.
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

#ifndef CRYPTOST_BUILD_INFO_H
#define	CRYPTOST_BUILD_INFO_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct cryptoSTE_buildInfo_s
{
    const char * const buildDate;
    const char * const buildTime;
    const char * const optimized;  // yes or no, not the optimization level
    const char * const processor;
    const char * const configuration;
} cryptoSTE_buildInfo_t;

extern cryptoSTE_buildInfo_t cryptoSTE_buildInfo;

#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTOST_BUILD_INFO_H */

