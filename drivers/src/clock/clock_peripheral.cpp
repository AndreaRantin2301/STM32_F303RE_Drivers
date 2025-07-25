/**
* File: clock_peripheral.cpp
* Created on: 2025-07-25 at 12:18
* Author: Andrea Rantin
* Description: Implementation file for clock_peripheral.hpp
*/

#include "clock/clock_peripheral.hpp"
#include "clock/clock_internal.hpp"

using namespace GPIOTypes;

void ClockPeripheral::Clock_GPIO_Enable(GPIOPort port) {
    RCC->AHBENR |= gpioClockTable[static_cast<uint8_t>(port)];
}

void ClockPeripheral::Clock_GPIO_Disable(GPIOPort port) {
    RCC->AHBENR &= ~gpioClockTable[static_cast<uint8_t>(port)];
}
