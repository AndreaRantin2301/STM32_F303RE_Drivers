/**
* File: gpio.hpp
* Created on: 2025-07-25 at 11:01
* Author: Andrea Rantin
* Description: This file contains the API provided to control the GPIO
* functionalities of the STM32F303RE MCU.
* //TODO
*/

#pragma once

#include "gpio/gpio_config.hpp"
#include "common/status_code.hpp"

namespace GPIO {

    /**
    * @brief Initializes a GPIO pin to the given mode and alternate function(if any)
    * 
    * @param gpioInitStruct Structure containing GPIO configuration paramenters
    * @return DriverStatusCode The status code returned by this function can be:
    *          - DriverStatusCode::OK If the GPIO was initialized successfully
    */
    DriverStatusCode GPIO_Init(GPIOInitStruct gpioInitStruct);

    /**
    * @brief Writes to a GPIO pin of the given port
    * 
    * @param port Port of the pin
    * @param pin Pin to write
    * @param state State to write of the pin(0 or 1)
    */
    void GPIO_Write(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin, GPIOTypes::GPIOState state);

    /**
    * @brief Reads a GPIO pin of the given port
    * 
    * @param port Port of the pin
    * @param pin Pin to read
    * @return State read from the pin(0 or 1)
    */
    uint8_t GPIO_Read(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin);

    /**
    * @brief Toggles a GPIO pin of the given port
    * 
    * @param port Port of the pin
    * @param pin Pin to toggle
    */
    void GPIO_Toggle(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin);

    /**
     * @brief Locks a GPIO pin to its configuration until the next reset of the MCU
     * 
     * @param port Port of the pin to lock
     * @param pin Pin to lock
     * @return DriverStatusCode The status code returned by this function can be:
     *        - DriverStatusCode::OK If the GPIO pin was locked successfully
     *        - DriverStatusCode::ERROR_GPIO_LOCK If the GPIO was not locked
     */
    DriverStatusCode GPIO_Lock(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin);
}



