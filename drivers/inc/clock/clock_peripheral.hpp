/**
* File: clock_peripheral.hpp
* Created on: 2025-07-25 at 12:14
* Author: Andrea Rantin
* Description: This file contains definitions for peripheral clock management like
* peripheral clock enabling
* //TODO
*/

#pragma once

#include "types/gpio_types.hpp"
#include "types/usart_types.hpp"

namespace ClockPeripheral {
    /**
    * @brief Enables the clock on the given GPIO port
    * 
    * @param port GPIO port
    */
    void Clock_GPIO_Enable(GPIOTypes::GPIOPort port);

    /**
    * @brief Disables the clock on the given GPIO port
    * 
    * @param port GPIO port
    */
    void Clock_GPIO_Disable(GPIOTypes::GPIOPort port);

    /**
     * @brief Enables the clock for the given USART/UART instance
     * 
     * @param instance Instance of USART/UART
     */
    void Clock_USART_Enable(USARTTypes::USARTInstance instance);

    /**
     * @brief Disables the clock for the given USART/UART instance
     * 
     * @param instance Instance of USART/UART
     */
    void Clock_USART_Disable(USARTTypes::USARTInstance instance);
}

