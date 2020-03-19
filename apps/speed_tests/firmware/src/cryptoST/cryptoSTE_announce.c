/*******************************************************************************
  Crypto Speed Test Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cyrptoST_execute.c

  Summary:
    This file provides standard-formats for displaying the CryptoST
    test parameters.

  Description:
    The routines provided here print test parameters in pre-defined
    formats to provide uniform test data.
 ****************************************************************************
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>
#include <stdio.h>
#include "cryptoSTE.h"
#include "cryptoST_print.h"
#include "../test_data/cryptoSpeedTestData.h"

#define P_BUMP  2   /* print indent for listing data */

// *****************************************************************************
// *****************************************************************************
// Section: Local data structures
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Support routines
// *****************************************************************************
// *****************************************************************************

// Variants on printing, defining an indentation
#define PTEXT(pre,post) \
    { printf("%*c%s %s" CRLF, level, ' ', pre, post); }
#define P_INT(pre,intVal) \
    { printf("%*c%s %d" CRLF, level, ' ', pre, intVal); }

// *****************************************************************************
// *****************************************************************************
// Section: External API
// *****************************************************************************
// *****************************************************************************

void cryptoSTE_announceDetails(int level, cryptoST_testDetail_t * rv)
{
    if (NULL == rv) return;

    // TODO: make these ascii instead of numeric
    P_INT("Technique", rv->technique);
    P_INT("Mode     ", rv->mode);
    P_INT("Data size", rv->rawData->vector.length);
    if (rv->source) 
        PTEXT("Source   ", rv->source);
    if (rv->pedigree) 
        PTEXT("Pedigree ", rv->pedigree);
    if (rv->rawData && rv->rawData->name)
        PTEXT("Raw data ", rv->rawData->name);
    if (CSTE_VERBOSE > 1) 
        P_INT("..repetitions: ", rv->recommendedRepetitions);
    if (CSTE_VERBOSE > 2)
    {
        P_INT("..bytes key    : ", rv->in.sym.key.length);
        P_INT("..bytes initV  : ", rv->in.sym.ivNonce.length);
        P_INT("..bytes aad    : ", rv->in.sym.additionalAuthData.length);
        if (rv->out.sym.cipher.data)
            P_INT("..bytes gCipher: ", rv->out.sym.cipher.length);
        if (rv->out.sym.tag.data)
            P_INT("..bytes gTag   : ", rv->out.sym.tag.length);
    }
    if (CSTE_VERBOSE > 3)
    {
        cryptoST_PRINT_hexLine(CRLF "..key    : ",
                rv->in.sym.key.data, rv->in.sym.key.length);
        cryptoST_PRINT_hexLine(CRLF "..initV  : ",
                rv->in.sym.ivNonce.data,rv->in.sym.ivNonce.length);
        cryptoST_PRINT_hexLine(CRLF "..gCipher: ",
                rv->out.sym.cipher.data, rv->out.sym.cipher.length);
        printf(CRLF);
    }
}

void cryptoSTE_announceVector(int level, cryptoST_testVector_t * tv)
{
    if (NULL == tv) return;

    if (tv->name)       PTEXT("Vector ", tv->name);
    if (tv->source)     PTEXT("..from ", tv->source);
    if (tv->pedigree)   PTEXT("..for ", tv->pedigree);
    if (CSTE_VERBOSE > 2) P_INT("..bytes data: ", tv->vector.length);
}

static char * bar_asterisks = "**************************" CRLF;
void cryptoSTE_announceSuite(const cryptoST_testAPI_t * cv)
{
    if (NULL == cv) return;

    printf(bar_asterisks);
    printf("* Test suite: %s" CRLF, cv->name);
    printf("* Requires open/close: %s - %s" CRLF,
                (NULL == cv->openData)? "no":"yes",
                (NULL == cv->closeData)? "no":"yes");
    printf(bar_asterisks);
}

void cryptoSTE_announceAll(cryptoSTE_localData_t * meMySelf)
{
    printf("Test vector catalog:" CRLF);
    
    const cryptoST_testAPI_t * cv;
    for (int i = 0; i < meMySelf->numberOfVectorAPI; i++)
    {
        cv = &meMySelf->vectorAPI[i];
        cryptoSTE_announceSuite(cv);
        
        cryptoST_testDetail_t * td;
        for (td = cv->firstTest(); NULL != td; td = cv->nextTest(td))
        {
            if (ET_NONE == td->technique) // safety check
            {
                cryptoSTE_announceDetails(P_BUMP, td);
                cryptoSTE_announceVector(2*P_BUMP, td->rawData);
            }
            else break; // this is the un-named tail of the list
        }
    }
}

void cryptoSTE_announceParameters(cryptoSTE_testExecution_t * config)
{
    cryptoSTE_labels_t * labels = &config->labels;
    printf(CRLF "Benchmark %s %s (%s)" CRLF, labels->platform,
                                             labels->processor,
                                             labels->build);

    cryptoSTE_parameters_t * parameters = &config->parameters;
    if (parameters->iterationOverride)
    { printf("Override test iterations : %u" CRLF, 
                parameters->iterationOverride); }
    else
    { printf("Default iterations will be used for all tests" CRLF); }
    printf("verifyByGoldenCiphertext : %s" CRLF, 
            parameters->verifyByGoldenCiphertext? "true" : "false");
    printf("verifyByDecryption       : %s" CRLF, 
            parameters->verifyByDecryption? "true" : "false");
    if (CSTE_VERBOSE)
        printf("Verbose : %u" CRLF, CSTE_VERBOSE);
}

/* The purpose of this declaration is to force an error
 * if an unsuspecting test uses this legacy entry point.
 * It can be removed when all projects build clean.
 */
__attribute((used))
void cryptoST_announceParameters(cryptoSTE_parameters_t * parameters)
{ __conditional_software_breakpoint(0); }
