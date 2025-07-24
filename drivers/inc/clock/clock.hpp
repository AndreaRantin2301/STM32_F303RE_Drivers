/**
* File: clock.hpp
* Created on: 2025-07-21 at 14:16
* Author: Andrea Rantin
* Description: This file contains the API provided to control
* the clock functionalities of the STM32F303RE MCU.
* It provides the following functionalities:
*    - Clock initialization with various parameters to select clock source, dividers, multipliers
*/

#pragma once

#include "clock/clock_config.hpp"
#include "common/status_code.hpp"

namespace Clock {

    /**
    * @brief Initializes system clock with the provided initialization struct
    * 
    * @param clockInitStruct Initialization struct containing configuration values for system clock.
    * This is a structure of type @ref ClockInitStruct_t
    * @return DriverStatusCode_t The status code returned by this function can be:
    *      - DriverStatusCode_t::OK If the clock was initialized successfully
    *      - DriverStatusCode_t::ERROR_CLOCK_READY If the clock was not ready after setting the clock source
    *      - DriverStatusCode_t::ERROR_CLOCK_SELECTED If the selected system clock was not the correct one after initialization
    */
    DriverStatusCode Clock_Init(ClockInitStruct clockInitStruct);
}