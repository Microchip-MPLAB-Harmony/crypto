/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    Source code for the BenchMark suite application logic.

  Description:
    This file contains the source code for a MPLab Harmony application
    to provide benchmark (speed) measurements of various crypto library
    functions. A minimal state machine is provided. Refer to cryptoSTE.c
    for additional details. Disabling a crypto function in Harmony3 
    disables the corresponding test(s).   

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <assert.h>
#include "app.h"
#include "cryptoST/cryptoST.h"

// #define INVOKE_INITIALIZATION_DELAY

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

/* Place the App state machine in its initial state. */
void APP_Initialize ( void )
{
    appData.state = APP_STATE_INIT;
}

#if defined(INVOKE_INITIALIZATION_DELAY)
/* Callback handler for a scheduled state change */
// This is necessary because there are no blocking single-shot timers.
void scheduledStateChange(uintptr_t context)
{ appData.state = context; }

/* Standard method to schedule a state change. */
// Stand-up a single-shot timer that will trigger a state change.
void scheduleStateChange(uint32_t msFuture, APP_STATES nextState)
{
    SYS_TIME_HANDLE initBlock = SYS_TIME_TimerCreate(
            0, 
            SYS_TIME_MSToCount(msFuture), 
            &scheduledStateChange, 
            nextState, 
            SYS_TIME_SINGLE);
    SYS_TIME_TimerStart(initBlock);
}
#endif // INVOKE_INITIALIZATION_DELAY

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        case APP_STATE_INIT: // assumed to be the reset value
        {
#if defined(INVOKE_INITIALIZATION_DELAY)            
            // This delay guards against false restarts from the debugger
            // and other things that would make execution chatter.
            scheduleStateChange(1000,APP_STATE_BEGIN_TEST);
            appData.state = APP_STATE_INIT_BLOCK;
#else
            appData.state = APP_STATE_BEGIN_TEST;
#endif
            break;
        }
        
        case APP_STATE_INIT_BLOCK:
        {
            // Do nothing -- timer expiration will kick us
            break;
        }
        
        /* Ready, set, go!! */
        case APP_STATE_BEGIN_TEST:
        {
            cryptoST(); 
            appData.state = APP_STATE_COMPLETE;
            break;
        }
        
        case APP_STATE_COMPLETE:
        {
            // simply spin until reset
            break;
        }
        
        /* The default state should never be executed. */
        default:
            __conditional_software_breakpoint(1);
            break;
    }
}


/*******************************************************************************
 End of File
 */
