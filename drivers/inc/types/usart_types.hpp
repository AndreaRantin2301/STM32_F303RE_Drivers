/**
* @file usart_types.hpp
* @date 2025-08-03 19:52:57
* @author Andrea Rantin
* @description This file contains definitions used for USART management such as
* instances, baud rate, parity, etc.
*/

#pragma once

#include "ST/stm32f303xe.h"

namespace USARTTypes {

    /**
    * @brief USART instance. For more info
    * consult reference manual page 896
    */
    enum class USARTInstance {
        USART_1,
        USART_2,
        USART_3,
        UART_4,
        UART_5,
    };
}

