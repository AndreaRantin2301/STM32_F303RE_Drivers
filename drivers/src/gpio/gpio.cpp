/**
* File: gpio.cpp
* Created on: 2025-07-25 at 11:04
* Author: Andrea Rantin
* Description: Implementation file for gpio.hpp
*/

#include "gpio/gpio.hpp"
#include "gpio/gpio_internal.hpp"
#include "clock/clock_peripheral.hpp"

using namespace GPIOTypes;
using namespace ClockPeripheral;

/**
 * @brief Sets the selected mode to the GPIO pin of the given port
 * 
 * @param port Port of the GPIO pin
 * @param pin GPIO pin
 * @param mode Mode to set the pin to
 */
static void GPIO_Set_Mode(GPIOPort port, GPIOPin pin, GPIOMode mode) {

    uint8_t pinVal = static_cast<uint8_t>(pin);
    uint8_t modeVal = static_cast<uint8_t>(mode);
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];

    //Calculate the bits position for the given pin
    uint32_t pinBitsPos = (pinVal * 2);
    
    //Clear MODER register
    portVal->MODER &= ~(0x03U << pinBitsPos);

    //Set the given mode
    portVal->MODER |= modeVal << pinBitsPos;
}

DriverStatusCode GPIO::GPIO_Init(GPIOInitStruct gpioInitStruct) {

    Clock_GPIO_Enable(gpioInitStruct.port);

    GPIO_Set_Mode(gpioInitStruct.port, gpioInitStruct.pin, gpioInitStruct.mode);

    return DriverStatusCode::OK;
}

void GPIO::GPIO_Write(GPIOPort port, GPIOPin pin, GPIOState state) {

    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];
    uint8_t pinVal = static_cast<uint8_t>(pin);

    portVal->BRR = (1U << pinVal);

    if(state == GPIOState::SET) {
        portVal->BSRR = (1U << pinVal);
    }
}

uint8_t GPIO::GPIO_Read(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin) {

    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];
    uint8_t pinVal = static_cast<uint8_t>(pin);

    return (uint8_t)((portVal->IDR & (0x01U << pinVal)) != 0);
}

void GPIO::GPIO_Toggle(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin) {
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];
    uint8_t pinVal = static_cast<uint8_t>(pin);

    if ((portVal->ODR >> pinVal) & 1U){
        portVal->BRR = (1U << pinVal);
    }
    else {
        portVal->BSRR = (1U << pinVal);
    }

}