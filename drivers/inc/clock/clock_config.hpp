/**
* File: clock_config.hpp
* Created on: 2025-07-21 at 14:03
* Author: Andrea Rantin
* Description: This file contains the definition of the structure used for clock initialization
*/

#pragma once

#include "types/clock_types.hpp"
#include "types/flash_types.hpp"

namespace Clock {

    /**
    * @brief Structure with parameters used
    * for clock initialization
    * 
    */
    typedef struct {
        ClockTypes::ClockSource clockSource; /*!< Clock source */
        ClockTypes::ClockPrediv prediv; /*!< Clock predivision factor */
        ClockTypes::ClockPLLSource pllSource; /*!< PLL clock source */
        ClockTypes::ClockPLLMul pllMul; /*!< PLL clock multiplier factor*/
        ClockTypes::ClockAHBPre ahbPre; /*!< AHB bus prescaler factor */
        ClockTypes::ClockAPB1Pre apb1Pre; /*!< APB1 bus prescaler factor */
        ClockTypes::ClockAPB2Pre apb2Pre; /*!< APB2 bus prescaler factor*/
        FlashTypes::FlashLatency flashLatency; /*!< Flash access wait latency */
        bool hseBypass = false; /*!< External HSE provided. If this flag is true, it is only applied if HSE is selected as system clock*/
    }ClockInitStruct;
}

