/**
* File: flash_types.hpp
* Created on: 2025-07-21 at 13:59
* Author: Andrea Rantin
* Description: This file contains definitions used for flash management
* such as access time latency
*/

#pragma once

#include "ST/stm32f303xe.h"

namespace FlashTypes {

    /**
    * @brief Flash access time latency.
    * For more info see reference manual page 80
    */
    enum class FlashLatency {
        LATENCY_ZERO_WAIT = FLASH_ACR_LATENCY_0,
        LATENCY_ONE_WAIT = FLASH_ACR_LATENCY_1,
        LATENCY_TWO_WAIT = FLASH_ACR_LATENCY_2,
    };
}

