/**
* File: gpio_config.hpp
* Created on: 2025-07-25 at 10:58
* Author: Andrea Rantin
* Description: This file contains the definition of the structure used for GPIO initialization
*/

#pragma once

#include "types/gpio_types.hpp"

namespace GPIO {

    /**
    * @brief Structure with parameters used for  GPIO
    * Initialization
    */
    typedef struct {
        GPIOTypes::GPIOPort port; /*!< GPIO port */
        GPIOTypes::GPIOPin pin; /*!< GPIO pin of the port*/
        GPIOTypes::GPIOMode mode; /*!< Mode to assing to the pin*/
    }GPIOInitStruct;
}
