/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "cryptoST.h"


// *****************************************************************************
// *****************************************************************************
// Section: Helper Functions
// *****************************************************************************
// *****************************************************************************

#if BLINKY_LED
/* TODO: This section should be generalized for the local LED
 * on each of the project boards. Until then its dead code.
 */
void LED1CallBack(uintptr_t context)
{
    LED1_Toggle();
}
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize(NULL);

#if BLINKY_LED
    // Make the LED flash periodically, to prove we are still running.
    SYS_TIME_HANDLE LEDtimerHandle = SYS_TIME_TimerCreate
        (0, SYS_TIME_MSToCount(1000), &LED1CallBack, 0, SYS_TIME_PERIODIC);
    SYS_TIME_TimerStart(LEDtimerHandle);
#endif
    
    /* Execute the tests
     * cryptoST() is local to this project and embodies the
     * configuration appropriate to our processor, because
     * H3 insists on regenerating main() from time to time.
     *  */
    cryptoST();
    
    while ( true )
    {
        __NOP();
#if defined(__DEBUG) || defined(__DEBUG_D) && defined(__XC32)
        __builtin_software_breakpoint();
#endif
    }

#if BLINKY_LED
    SYS_TIME_TimerDestroy(LEDtimerHandle);
#endif
    return ( EXIT_FAILURE );
}

/*******************************************************************************
 End of File
*/

