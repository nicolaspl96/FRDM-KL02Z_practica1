/*! @file : sdk_hal_uart0.c
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    8/01/2021
 * @brief   Driver para UART0
 * @details
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sdk_hal_uart0.h"
#include "fsl_lpsci.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Define nombre interno de funcion para gestionar interrupción por dato UART */
#define UART0_IRQ_HANDLER 		UART0_IRQHandler

/*! @brief Tamaño de buffer circular para recibir datos por UART (Unit: Byte). */
#define DEMO_RING_BUFFER_SIZE 	64
/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
uint8_t demoRingBuffer[DEMO_RING_BUFFER_SIZE];
volatile uint16_t txIndex; /* Index of the data to send out. */
volatile uint16_t rxIndex; /* Index of the memory to save new arrived data. */

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
/*--------------------------------------------*/
/*!
 * @brief Funcion que gestiona IRQ por UART0
 */
void UART0_IRQ_HANDLER(void)
{
    uint8_t data;

    if ((kLPSCI_RxDataRegFullFlag)&LPSCI_GetStatusFlags(UART0))
    {
        data = LPSCI_ReadByte(UART0);

        /* If ring buffer is not full, add data to ring buffer. */
        if (((rxIndex + 1) % DEMO_RING_BUFFER_SIZE) != txIndex)
        {
            demoRingBuffer[rxIndex] = data;
            rxIndex++;
            rxIndex %= DEMO_RING_BUFFER_SIZE;
        }
    }
}
/*--------------------------------------------*/
/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
/*--------------------------------------------*/
