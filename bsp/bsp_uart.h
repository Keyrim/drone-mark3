/*
 * SPDX-FileCopyrightText: 2024 Théo Magne <theo.magne.fr@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

/* Protection against multiple inclusions */
#ifndef __BSP_UART_H__
#define __BSP_UART_H__ __FILE__

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "stdint.h"

/******************************************************************************
 * PUBLIC Configuration
 ******************************************************************************/

/******************************************************************************
 * PUBLIC Macro
 ******************************************************************************/

/******************************************************************************
 * PUBLIC type definitions
 ******************************************************************************/

/**
 * @brief uart enumeration definition
 */
typedef enum
{
    UART_1 = 0,
    UART_COUNT,
} uart_e;

/******************************************************************************
 * PUBLIC constant data definitions
 ******************************************************************************/

/******************************************************************************
 * PUBLIC variable definitions
 ******************************************************************************/

/******************************************************************************
 * PUBLIC Callback function
 ******************************************************************************/

/******************************************************************************
 * PUBLIC function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initialize every uarts and start dma reception
     */
    void UART_init(void);

    /**
     * @brief Re start the dma transfer if there is data to send or reset the
     * transmission state to idle
     * @param [in] id : Id of the uart
     */
    void UART_transfer_complete_cb(uart_e id);

    /**
     * @brief Update the read index when the idle flag is raised
     * @param [in] id : Id of the uart
     */
    void UART_idle_line_cb(uart_e id);

    /**
     * @brief Transmit data in dma on the given uart
     * @param [in] id : Id of the uart
     * @param [in] data : Array with the data
     * @param [in] len : Length of the data array
     */
    void UART_transmit(uart_e id, uint8_t *data, uint16_t len);

    /**
     * @brief Write the next available character in the buffer
     * 		  Does nothing if there are no characters available
     * @param [in] id : Id of the uart
     * @param [in] c : Buffer to write the character into
     */
    void UART_get(uart_e id, uint8_t *c);

    /**
     * @brief Number of byte available in the RX buffer
     * @param [in] id : Id of the uart we are interested in
     * @return Number of bytes
     */
    uint16_t UART_bytes_available(uart_e id);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_UART_H__ */
