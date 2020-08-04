/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    cryptoSTE_definitions.h

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

//DOM-IGNORE-END

#ifndef CRYPTOSTE_H
#define	CRYPTOSTE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define CSTE_VERBOSE     1
    
#include "../test_data/cryptoSpeedTestData.h"
#include <stdbool.h>
#include <stdint.h>
// #include "system/time/sys_time.h"

/* This is done to more clearly identify the time variables.
 * The standard definition is a raw uint32_t :(
 *  */    
typedef uint32_t SYS_TIME_for_CSTE;

typedef enum // cryptoSTE_resultsDisplay_e
{
    CST_TEXT = 0,
    CST_CSV  = 1,  // text/csv, RFC-4180, RFC7111
    CST_XML,
    CST_JSON,
} cryptoSTE_resultsDisplay_t;

typedef struct cryptoSTE_labels_s
{
    const char * platform;
    const char * processor;
    const char * accelerator;
    const char * build;
} cryptoSTE_labels_t;

typedef struct cryptoSTE_parameters_s
{
    // This subset applies to the individual test driver
    int iterationOverride; // if zero, use recommendations
    bool verifyByDecryption;
    bool verifyByGoldenCiphertext;
    bool useLocalDriverEntryPoints;    // see note below

    // This subset applies to the overall test manager
    cryptoSTE_resultsDisplay_t displayType; // does not apply to VERBOSE
    bool compareHWvSW;
} cryptoSTE_parameters_t;
/* Note: useLocalDriverEntryPoints 
 * true  :: the hw version of the function driver will be used and
 *          will probably give the best-in-class performance; not all
 *          drivers have a local, high-speed version.
 * false :: the WC entry point will be used and will give real-world
 *          statistics. Use the GUI option to enable/disable 
 *          the HW-accelerated (overloaded) version.
 * As a consequence, real-world stat's for HW v. SW can only be
 * collected with a re-gen of the H3 code.
 */

typedef struct cryptoSTE_timeMetadata_s
{
    size_t size;
    size_t iterations;
    SYS_TIME_for_CSTE start;
    SYS_TIME_for_CSTE stop;
    bool startStopIsValid;
}cryptoSTE_timeMetadata_t;

typedef struct cryptoSTE_results_s
{
    const char * testHandler;
    cryptoSTE_timeMetadata_t encryption;
    // cryptoSTE_timeMetadata_t decryption;

    int warningCount;
    const char * warningMessage;
    const char * errorMessage;
    int wolfSSLresult;
} cryptoSTE_results_t;

/* This is defined for each test performed. Note that it is a hard
 * instance and not a pointer, so that we could (in theory) perform
 * multiple simultaneous tests in a parallel processor or rtos.
 * 
 * In practice, there is only one of these, 
 * and it is re-used for all test vectors.
 *  */
typedef struct cryptoSTE_testExecution_s
{
    cryptoSTE_parameters_t parameters;
    cryptoSTE_results_t results;
    cryptoSTE_labels_t labels;
} cryptoSTE_testExecution_t;

/* This singleton is filled in as testing progresses.
 * Here again, the config data is instanced, not referenced.
 *  */
typedef struct cryptoSTE_localData_s
{
    int testsAttempted;
    int testsSucceeded;
    int numberOfVectorAPI;
    cryptoST_testAPI_t * vectorAPI;
    cryptoSTE_testExecution_t configuration;
} cryptoSTE_localData_t;

/* Virtualize the SHA hash algorithm to allow both the
 * WC and device-hardware versions to coexist. 
 */
typedef int (cryptoSTE_shaOperator_t)
    (uint32_t hash[], const uint8_t * data, const size_t length);

#ifdef	__cplusplus
}
#endif

#endif	/* CRYPTOSTE_H */

