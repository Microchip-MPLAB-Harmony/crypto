/*******************************************************************************
  UART1 PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_uart1.c

  Summary:
    UART1 PLIB Implementation File

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
#include "plib_uart1.h"

// *****************************************************************************
// *****************************************************************************
// Section: UART1 Implementation
// *****************************************************************************
// *****************************************************************************

UART_OBJECT uart1Obj;

void static UART1_ISR_RX_Handler( void )
{
    if(uart1Obj.rxBusyStatus == true)
    {
        while((UART_SR_RXRDY_Msk == (UART1_REGS->UART_SR& UART_SR_RXRDY_Msk)) && (uart1Obj.rxSize > uart1Obj.rxProcessedSize) )
        {
            uart1Obj.rxBuffer[uart1Obj.rxProcessedSize++] = (UART1_REGS->UART_RHR& UART_RHR_RXCHR_Msk);
        }

        /* Check if the buffer is done */
        if(uart1Obj.rxProcessedSize >= uart1Obj.rxSize)
        {
            uart1Obj.rxBusyStatus = false;
            uart1Obj.rxSize = 0;
            uart1Obj.rxProcessedSize = 0;

            /* Disable Read, Overrun, Parity and Framing error interrupts */
            UART1_REGS->UART_IDR = (UART_IDR_RXRDY_Msk | UART_IDR_FRAME_Msk | UART_IDR_PARE_Msk | UART_IDR_OVRE_Msk);

            if(uart1Obj.rxCallback != NULL)
            {
                uart1Obj.rxCallback(uart1Obj.rxContext);
            }
        }
    }
    else
    {
        /* Nothing to process */
        ;
    }

    return;
}

void static UART1_ISR_TX_Handler( void )
{
    if(uart1Obj.txBusyStatus == true)
    {
        while((UART_SR_TXEMPTY_Msk == (UART1_REGS->UART_SR& UART_SR_TXEMPTY_Msk)) && (uart1Obj.txSize > uart1Obj.txProcessedSize) )
        {
            UART1_REGS->UART_THR|= uart1Obj.txBuffer[uart1Obj.txProcessedSize++];
        }

        /* Check if the buffer is done */
        if(uart1Obj.txProcessedSize >= uart1Obj.txSize)
        {
            uart1Obj.txBusyStatus = false;
            uart1Obj.txSize = 0;
            uart1Obj.txProcessedSize = 0;
            UART1_REGS->UART_IDR = UART_IDR_TXEMPTY_Msk;

            if(uart1Obj.txCallback != NULL)
            {
                uart1Obj.txCallback(uart1Obj.txContext);
            }
        }
    }
    else
    {
        /* Nothing to process */
        ;
    }

    return;
}

void UART1_InterruptHandler( void )
{
    /* Error status */
    uint32_t errorStatus = (UART1_REGS->UART_SR & (UART_SR_OVRE_Msk | UART_SR_FRAME_Msk | UART_SR_PARE_Msk));

    if(errorStatus != 0)
    {
        /* Client must call UARTx_ErrorGet() function to clear the errors */

        /* UART errors are normally associated with the receiver, hence calling
         * receiver context */
        if( uart1Obj.rxCallback != NULL )
        {
            uart1Obj.rxCallback(uart1Obj.rxContext);
        }

        uart1Obj.rxBusyStatus = false;
        uart1Obj.rxSize = 0;
        uart1Obj.rxProcessedSize = 0;

        /* Disable Read, Overrun, Parity and Framing error interrupts */
        UART1_REGS->UART_IDR = (UART_IDR_RXRDY_Msk | UART_IDR_FRAME_Msk | UART_IDR_PARE_Msk | UART_IDR_OVRE_Msk);
    }

    /* Receiver status */
    if(UART_SR_RXRDY_Msk == (UART1_REGS->UART_SR& UART_SR_RXRDY_Msk))
    {
        UART1_ISR_RX_Handler();
    }

    /* Transmitter status */
    if(UART_SR_TXEMPTY_Msk == (UART1_REGS->UART_SR& UART_SR_TXEMPTY_Msk))
    {
        UART1_ISR_TX_Handler();
    }

    return;
}


void static UART1_ErrorClear( void )
{
    uint8_t dummyData = 0u;

    UART1_REGS->UART_CR|= UART_CR_RSTSTA_Msk;

    /* Flush existing error bytes from the RX FIFO */
    while( UART_SR_RXRDY_Msk == (UART1_REGS->UART_SR& UART_SR_RXRDY_Msk) )
    {
        dummyData = (UART1_REGS->UART_RHR& UART_RHR_RXCHR_Msk);
    }

    /* Ignore the warning */
    (void)dummyData;

    return;
}

void UART1_Initialize( void )
{
    /* Reset UART1 */
    UART1_REGS->UART_CR = (UART_CR_RSTRX_Msk | UART_CR_RSTTX_Msk | UART_CR_RSTSTA_Msk);

    /* Enable UART1 */
    UART1_REGS->UART_CR = (UART_CR_TXEN_Msk | UART_CR_RXEN_Msk);

    /* Configure UART1 mode */
    UART1_REGS->UART_MR = ((UART_MR_BRSRCCK_PERIPH_CLK) | (UART_MR_PAR_NO) | (0 << UART_MR_FILTER_Pos));

    /* Configure UART1 Baud Rate */
    UART1_REGS->UART_BRGR = UART_BRGR_CD(81);

    /* Initialize instance object */
    uart1Obj.rxBuffer = NULL;
    uart1Obj.rxSize = 0;
    uart1Obj.rxProcessedSize = 0;
    uart1Obj.rxBusyStatus = false;
    uart1Obj.rxCallback = NULL;
    uart1Obj.txBuffer = NULL;
    uart1Obj.txSize = 0;
    uart1Obj.txProcessedSize = 0;
    uart1Obj.txBusyStatus = false;
    uart1Obj.txCallback = NULL;

    return;
}

UART_ERROR UART1_ErrorGet( void )
{
    UART_ERROR errors = UART_ERROR_NONE;
    uint32_t status = UART1_REGS->UART_SR;

    /* Collect all errors */
    if(status & UART_SR_OVRE_Msk)
    {
        errors = UART_ERROR_OVERRUN;
    }
    if(status & UART_SR_PARE_Msk)
    {
        errors |= UART_ERROR_PARITY;
    }
    if(status & UART_SR_FRAME_Msk)
    {
        errors |= UART_ERROR_FRAMING;
    }

    if(errors != UART_ERROR_NONE)
    {
        UART1_ErrorClear();
    }

    /* All errors are cleared, but send the previous error state */
    return errors;
}

bool UART1_SerialSetup( UART_SERIAL_SETUP *setup, uint32_t srcClkFreq )
{
    bool status = true;
    uint32_t clk = srcClkFreq;
    uint32_t baud = setup->baudRate;
    uint32_t brgVal = 0;
    uint32_t parityVal = 0;

    if((uart1Obj.rxBusyStatus == true) || (uart1Obj.txBusyStatus == true))
    {
        /* Transaction is in progress, so return without updating settings */
        return false;
    }

    if(clk == 0)
    {
        clk = UART1_FrequencyGet();
    }

    /* Calculate BRG value */
    if (clk >= (16 * baud))
    {
        brgVal = (clk / (16 * baud));
    }
    else
    {
        brgVal = (clk / (8 * baud));
    }

    /* Get Parity values */
    switch(setup->parity)
    {
        case UART_PARITY_ODD:
        case UART_PARITY_MARK:
        {
            parityVal = UART_MR_PAR(setup->parity);
            break;
        }
        case UART_PARITY_NONE:
        {
            parityVal = UART_MR_PAR_NO;
            break;
        }
        case UART_PARITY_EVEN:
        {
            parityVal = UART_MR_PAR_EVEN;
            break;
        }
        case UART_PARITY_SPACE:
        {
            parityVal = UART_MR_PAR_SPACE;
            break;
        }
        default:
        {
            status = false;
            break;
        }
    }

    if(status != false)
    {
        /* Configure UART1 mode */
        UART1_REGS->UART_MR = (parityVal | (0 << UART_MR_FILTER_Pos));

        /* Configure UART1 Baud Rate */
        UART1_REGS->UART_BRGR = UART_BRGR_CD(brgVal);
    }

    return status;
}

bool UART1_Read( void *buffer, const size_t size )
{
    bool status = false;

    uint8_t * lBuffer = (uint8_t *)buffer;

    if(NULL != lBuffer)
    {
        /* Clear errors before submitting the request.
         * ErrorGet clears errors internally. */
        UART1_ErrorGet();

        /* Check if receive request is in progress */
        if(uart1Obj.rxBusyStatus == false)
        {
            uart1Obj.rxBuffer = lBuffer;
            uart1Obj.rxSize = size;
            uart1Obj.rxProcessedSize = 0;
            uart1Obj.rxBusyStatus = true;
            status = true;

            /* Enable Read, Overrun, Parity and Framing error interrupts */
            UART1_REGS->UART_IER = (UART_IER_RXRDY_Msk | UART_IER_FRAME_Msk | UART_IER_PARE_Msk | UART_IER_OVRE_Msk);
        }
    }

    return status;
}

bool UART1_Write( void *buffer, const size_t size )
{
    bool status = false;
    uint8_t * lBuffer = (uint8_t *)buffer;

    if(NULL != lBuffer)
    {
        /* Check if transmit request is in progress */
        if(uart1Obj.txBusyStatus == false)
        {
            uart1Obj.txBuffer = lBuffer;
            uart1Obj.txSize = size;
            uart1Obj.txProcessedSize = 0;
            uart1Obj.txBusyStatus = true;
            status = true;

            /* Initiate the transfer by sending first byte */
            if(UART_SR_TXEMPTY_Msk == (UART1_REGS->UART_SR& UART_SR_TXEMPTY_Msk))
            {
                UART1_REGS->UART_THR = (UART_THR_TXCHR(*lBuffer) & UART_THR_TXCHR_Msk);
                uart1Obj.txProcessedSize++;
            }

            UART1_REGS->UART_IER = UART_IER_TXEMPTY_Msk;
        }
    }

    return status;
}

bool UART1_WriteCallbackRegister( UART_CALLBACK callback, uintptr_t context )
{
    uart1Obj.txCallback = callback;
    uart1Obj.txContext = context;

    return true;
}

bool UART1_ReadCallbackRegister( UART_CALLBACK callback, uintptr_t context )
{
    uart1Obj.rxCallback = callback;
    uart1Obj.rxContext = context;

    return true;
}

bool UART1_WriteIsBusy( void )
{
    return uart1Obj.txBusyStatus;
}

bool UART1_ReadIsBusy( void )
{
    return uart1Obj.rxBusyStatus;
}

size_t UART1_WriteCountGet( void )
{
    return uart1Obj.txProcessedSize;
}

size_t UART1_ReadCountGet( void )
{
    return uart1Obj.rxProcessedSize;
}

