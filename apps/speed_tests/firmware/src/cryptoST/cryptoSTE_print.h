/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_print.h

  Summary:
    Public information for the BenchMark suite test logic.

  Description:
    Public entry points and data structures for the CryptoST test suite.
*******************************************************************************/

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

#ifndef CRYPTOST_PRINT_H
#define	CRYPTOST_PRINT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>
#include "definitions.h"    // SYS function prototypes
#include "cryptoSTE_definitions.h"      // for SYS_TIME_for_CSTE

#define CRLF "\r\n"
#define STRINGIZE2(x) #x
#define STRINGIZE(x) STRINGIZE2(x)
#define BASE_LINE STRINGIZE(__LINE__) // line number in source file
    
/* As a general rule, when you print a paragraph of material
 * (that is, one or more lines of related info), always end
 * the paragraph with CRLF. When you start a new paragraph,
 * you can assume that you are at the left-most column.
 *  */
#define PRINT(s) { printf("%s",(s)); }
    // TODO: add a wait-for-complete loop here

#define PRINT_WAIT_WHILE_BUSY() 
    // FIXME: this should do something, and have a time-out

#define PRINT_WAIT(s) { PRINT(s) PRINT_WAIT_WHILE_BUSY() }

#define P0_INT(pre,intVal)  printf("%s%ld", (pre),((long int)(intVal)));
#define P0_UINT(pre,intVal) printf("%s%lu", (pre),((long unsigned int)(intVal)));
#define P0_BOOL(pre,bVal)   printf("%s%s", (pre),((bVal)?"true":"false"));

//void cryptoST_PRINT_bool(char * pre, bool bVal);
//void cryptoST_PRINT_lint(char * pre, long int intVal);
//void cryptoST_PRINT_luint(char * pre, long unsigned int intVal);
void cryptoST_PRINT_hexLine
    (const char * const tag, const uint8_t * const data, const size_t const length);
void cryptoST_PRINT_hexBlock
    (const char * const tag, const uint8_t * const data, size_t const length);
    
void cryptoST_PRINT_announceElapsedTime
       (const CPU_CHAR * testName, 
        cryptoSTE_testExecution_t * config);

#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTOST_PRINT_H */

