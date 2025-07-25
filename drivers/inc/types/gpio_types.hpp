/**
* File: gpio_types.hpp
* Created on: 2025-07-25 at 10:50
* Author: Andrea Rantin
* Description: This file contains definitions used for GPIO management such as
* GPIO mode, GPIO port and pin
*/

#pragma once

#include "ST/stm32f303xe.h"

namespace GPIOTypes {

    /**
    * @brief GPIO port
    * 
    */
    enum class GPIOPort {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
    };

    /**
    * @brief GPIO pin
    * 
    */
    enum class GPIOPin {
        PIN_0 = 0,
        PIN_1 = 1,
        PIN_2 = 2,
        PIN_3 = 3,
        PIN_4 = 4,
        PIN_5 = 5,
        PIN_6 = 6,
        PIN_7 = 7,
        PIN_8 = 8,
        PIN_9 = 9,
        PIN_10 = 10,
        PIN_11 = 11,
        PIN_12 = 12,
        PIN_13 = 13,
        PIN_14 = 14,
        PIN_15 = 15,
    };

    /**
    * @brief GPIO Mode
    * 
    */
    enum class GPIOMode{
        INPUT = 0b00,
        OUTPUT = 0b01,
        ALTERNATE = 0b10,
        ANALOG = 0b11
    };

    /**
    * @brief Flag to write/read from GPIO pins
    * 
    */
    enum class GPIOState{
        RESET = 0,
        SET = 1,
    };

    /**
    * @brief Pull up/down for GPIO
    * 
    */
    enum class GPIOPupPd {
        NO_PULLUP_PULLDOWN = 0b00,
        PULL_UP = 0b01,
        PULL_DOWN = 0b10
    };

    /**
    * @brief Output speed for GPIO
    * 
    */
    enum class GPIOOutputSpeed {
        LOW = 0b00,
        MEDIUM = 0b01,
        HIGH = 0b11,
    };

    /**
    * @brief Output type for GPIO
    * 
    */
    enum class GPIOOutputType {
        PUSH_PULL = 0,
        OPEN_DRAIN = 1,
    };
}