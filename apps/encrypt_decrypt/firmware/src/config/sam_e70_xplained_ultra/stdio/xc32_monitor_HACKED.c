/*******************************************************************************
 Debug Console Source file

  Company:
    Microchip Technology Inc.

  File Name:
    debug_console.c

  Summary:
    RSTC Source File

  Description:
    None

*******************************************************************************/

/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
#include "device.h"
#include "peripheral/usart/plib_usart1.h"


void static _USART1_ErrorClear( void )
{
    uint8_t dummyData = 0u;

    USART1_REGS->US_CR|= US_CR_RSTSTA_Msk;

    /* Flush existing error bytes from the RX FIFO */
    while( US_CSR_RXRDY_Msk == (USART1_REGS->US_CSR& US_CSR_RXRDY_Msk) )
    {
        dummyData = (USART1_REGS->US_RHR& US_RHR_RXCHR_Msk);
    }

    /* Ignore the warning */
    (void)dummyData;

    return;
}

static USART_ERROR _USART1_ErrorGet( void )
{
    USART_ERROR errors = USART_ERROR_NONE;
    uint32_t status = USART1_REGS->US_CSR;

    /* Collect all errors */
    if(status & US_CSR_OVRE_Msk)
    {
        errors = USART_ERROR_OVERRUN;
    }
    if(status & US_CSR_PARE_Msk)
    {
        errors |= USART_ERROR_PARITY;
    }
    if(status & US_CSR_FRAME_Msk)
    {
        errors |= USART_ERROR_FRAMING;
    }

    if(errors != USART_ERROR_NONE)
    {
        _USART1_ErrorClear();
    }

    /* All errors are cleared, but send the previous error state */
    return errors;
}

static bool _USART1_Read( void *buffer, const size_t size )
{
    bool status = false;
    uint32_t errorStatus = 0;
    size_t processedSize = 0;
    uint8_t * lBuffer = (uint8_t *)buffer;

    NVIC_DisableIRQ(USART1_IRQn);  // Disable USART1 interrupts
    
    if(NULL != lBuffer)
    {
        /* Clear errors before submitting the request.
         * ErrorGet clears errors internally. */
        _USART1_ErrorGet();

        while( size > processedSize )
        {
            /* Error status */
            errorStatus = (USART1_REGS->US_CSR & (US_CSR_OVRE_Msk | US_CSR_FRAME_Msk | US_CSR_PARE_Msk));

            if(errorStatus != 0)
            {
                break;
            }

            if(US_CSR_RXRDY_Msk == (USART1_REGS->US_CSR & US_CSR_RXRDY_Msk))
            {
                *lBuffer++ = (USART1_REGS->US_RHR& US_RHR_RXCHR_Msk);
                processedSize++;
            }
        }

        if(size == processedSize)
        {
            status = true;
        }

    }

    return status;
}

static bool _USART1_Write( void *buffer, const size_t size )
{
    bool status = false;
    size_t processedSize = 0;
    uint8_t * lBuffer = (uint8_t *)buffer;

    NVIC_DisableIRQ(USART1_IRQn);  // Disable USART1 interrupts
    
    if(NULL != lBuffer)
    {
        while( size > processedSize )
        {
            if(US_CSR_TXEMPTY_Msk == (USART1_REGS->US_CSR& US_CSR_TXEMPTY_Msk))
            {
                USART1_REGS->US_THR = (US_THR_TXCHR(*lBuffer++) & US_THR_TXCHR_Msk);
                processedSize++;
            }
        }

        status = true;
    }

    return status;
}


int _mon_getc(int canblock)
{
    volatile int c = 0;
    while(_USART1_Read((void*)&c, 1) != true);
    return c;
}

void _mon_putc(char c)
{
    uint8_t size = 0;
    do
    {
        size = _USART1_Write((void*)&c, 1);
    }while (size !=1);
}
