/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"
#include "definitions.h"
#include "../../../../crypto.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#ifndef NO_RSA
#define FOURK_BUF 4096
#endif /* NO_RSA */
    
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,
    APP_STATE_TEST_MD5,
    APP_STATE_TEST_SHA,        
    APP_STATE_TEST_SHA256,
    APP_STATE_TEST_SHA384,
    APP_STATE_TEST_SHA512,
    APP_STATE_TEST_HMAC_MD5,
    APP_STATE_TEST_HMAC_SHA,
    APP_STATE_TEST_HMAC_SHA256,
    APP_STATE_TEST_HMAC_SHA384,
    APP_STATE_TEST_HMAC_SHA512,
    APP_STATE_TEST_DES,
    APP_STATE_TEST_DES3,
    APP_STATE_TEST_AES,
    APP_STATE_TEST_RSA,
    APP_STATE_TEST_RANDOM,
    APP_STATE_TEST_ECC,
    APP_STATE_TEST_COMPRESS,
    APP_STATE_DISPLAY_RESULTS,
    APP_STATE_WAIT_FOR_CONSOLE,
    APP_STATE_CHECK_RESULTS,
    APP_SPIN,
} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    bool wrComplete;
    bool rdComplete;

    int md5_test_result;
    uint32_t md5_timing;

    int sha_test_result;
    uint32_t sha_timing;

    int sha256_test_result;
    uint32_t sha256_timing;

    int sha384_test_result;
    uint32_t sha384_timing;

    int sha512_test_result; 
    uint32_t sha512_timing;

    int hmac_md5_test_result;
    uint32_t hmac_md5_timing;

    int hmac_sha_test_result;
    uint32_t hmac_sha_timing;

    int hmac_sha256_test_result;
    uint32_t hmac_sha256_timing;

    int hmac_sha384_test_result;
    uint32_t hmac_sha384_timing;

    int hmac_sha512_test_result;
    uint32_t hmac_sha512_timing;

    int des_test_result;
    uint32_t des_timing;

    int des3_test_result;
    uint32_t des3_timing;

    int aes_cbc_test_result;
    uint32_t aes_cbc_timing;

    int aes_ctr_test_result;
    uint32_t aes_ctr_timing;

    int rsa_test_result;
    uint32_t rsa_timing;

    int random_test_result;
    uint32_t random_timing;

    int ecc_test_result;
    uint32_t ecc_timing;

    int compress_test_result;
    uint32_t compress_timing;

    int32_t wallTime;
} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );


#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

