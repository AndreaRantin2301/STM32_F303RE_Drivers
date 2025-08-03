/**
* File: clock_peripheral.cpp
* Created on: 2025-07-25 at 12:18
* Author: Andrea Rantin
* Description: Implementation file for clock_peripheral.hpp
*/

#include "clock/clock_peripheral.hpp"
#include "clock/clock_internal.hpp"

using namespace GPIOTypes;
using namespace USARTTypes;

void ClockPeripheral::Clock_GPIO_Enable(GPIOPort port) {
    RCC->AHBENR |= gpioClockTable[static_cast<uint8_t>(port)];
}

void ClockPeripheral::Clock_GPIO_Disable(GPIOPort port) {
    RCC->AHBENR &= ~gpioClockTable[static_cast<uint8_t>(port)];
}

void ClockPeripheral::Clock_USART_Enable(USARTInstance instance) {
    if(instance == USARTInstance::USART_1) {
        RCC->APB2ENR |= usartClockTable[static_cast<uint8_t>(instance)];
        return;
    }
    RCC->APB1ENR |= usartClockTable[static_cast<uint8_t>(instance)];
}

void ClockPeripheral::Clock_USART_Disable(USARTInstance instance) {
    if(instance == USARTInstance::USART_1) {
        RCC->APB2ENR &= ~usartClockTable[static_cast<uint8_t>(instance)];
        return;
    }
    RCC->APB1ENR &= ~usartClockTable[static_cast<uint8_t>(instance)];
}