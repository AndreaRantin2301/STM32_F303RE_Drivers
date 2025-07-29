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

/**
* @brief Sets a PullUp/PullDown for the given GPIO pin
* 
* @param port Port of the GPIO pin
* @param pin GPIO pin
* @param pupPd PullUp/PullDown to set(if any)
*/
static void GPIO_Set_PullUpDown(GPIOPort port, GPIOPin pin, GPIOPupPd pupPd) {
    
    uint8_t pinVal = static_cast<uint8_t>(pin);
    uint8_t pupPdVal = static_cast<uint8_t>(pupPd);
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];

    //Calculate the bits position for the given pin
    uint32_t pinBitsPos = (pinVal * 2);

    //Clear PUPDR register
    portVal->PUPDR &= ~(0x03U << pinBitsPos);

    //Set the given PullUp/PullDown
    portVal->PUPDR |= pupPdVal << pinBitsPos;
}

/**
* @brief Sets the output speed for the give GPIO pin
* 
* @param port Port of the GPIO pin
* @param pin GPIO pin
* @param speed Output speed to set
*/
static void GPIO_Set_OutputSpeed(GPIOPort port, GPIOPin pin, GPIOOutputSpeed speed) {

    uint8_t pinVal = static_cast<uint8_t>(pin);
    uint8_t speedVal = static_cast<uint8_t>(speed);
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];

    //Calculate the bits position for the given pin
    uint32_t pinBitsPos = (pinVal * 2);

    //Clear OSPEED register
    portVal->OSPEEDR &= ~(0x03U << pinBitsPos);

    //Set the given output speed
    portVal->OSPEEDR |= speedVal << pinBitsPos;
}

static void GPIO_Set_OutputType(GPIOPort port, GPIOPin pin, GPIOOutputType type) {

    uint8_t pinVal = static_cast<uint8_t>(pin);
    uint8_t typeVal = static_cast<uint8_t>(type);
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];

    //Clear OTYPER register
    portVal->OTYPER &= ~(0x01U << pinVal);

    //Set the given output type
    portVal->OTYPER |= typeVal << pinVal;
}

/**
 * @brief Checks if the given GPIO pin supports the given Alternate function
 * 
 * @param gpioInitStruct Structure containing GPIO configuration
 * @return true GPIO pin and AF are compatible
 * @return false GPIO pin and AF are not compatible
 */
static bool GPIO_Is_AF_Valid(GPIO::GPIOInitStruct gpioInitStruct) {
    uint8_t len = (sizeof(gpioAfValidationTable) / sizeof(gpioAfValidationTable[0]));
    int8_t afVal = static_cast<int8_t>(gpioInitStruct.alternateFunction);
    for(uint8_t i = 0; i < len; i++) {
        if((gpioAfValidationTable[i].port == gpioInitStruct.port) && (gpioAfValidationTable[i].pin == gpioInitStruct.pin)) {
            return (gpioAfValidationTable[i].afMask & (0x01U << afVal)) != 0;
        }
    }
    return false;
}

static DriverStatusCode GPIO_Set_AF(GPIO::GPIOInitStruct gpioInitStruct) {
    if(!GPIO_Is_AF_Valid(gpioInitStruct)) return DriverStatusCode::ERROR_GPIO_AF;

    uint8_t pinVal = static_cast<uint8_t>(gpioInitStruct.pin);
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(gpioInitStruct.port)];
    uint8_t afVal = static_cast<int8_t>(gpioInitStruct.alternateFunction);

    //Check which af register to use
    uint8_t afrIndex = (pinVal >= 8) ? 1 : 0;
    //Check which bits correspond to the given pin
    uint8_t afrBitsPos = (pinVal % 8) * 4;

    //Set AFR
    portVal->AFR[afrIndex] &= ~(0xFU << afrBitsPos);
    portVal->AFR[afrIndex] |= ((afVal & 0xFU) << afrBitsPos);

    return DriverStatusCode::OK;
}

DriverStatusCode GPIO::GPIO_Init(GPIOInitStruct gpioInitStruct) {

    Clock_GPIO_Enable(gpioInitStruct.port);

    GPIO_Set_Mode(gpioInitStruct.port, gpioInitStruct.pin, gpioInitStruct.mode);

    GPIO_Set_OutputType(gpioInitStruct.port, gpioInitStruct.pin, gpioInitStruct.outputType);

    GPIO_Set_OutputSpeed(gpioInitStruct.port, gpioInitStruct.pin, gpioInitStruct.outputSpeed);

    GPIO_Set_PullUpDown(gpioInitStruct.port, gpioInitStruct.pin, gpioInitStruct.pupPd);

    DriverStatusCode checkError = GPIO_Set_AF(gpioInitStruct);
    return checkError;
}

void GPIO::GPIO_Write(GPIOPort port, GPIOPin pin, GPIOState state) {

    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];
    uint8_t pinVal = static_cast<uint8_t>(pin);

    if (state == GPIOState::SET) {
        portVal->BSRR = (1U << pinVal);
    } else {
        portVal->BRR = (1U << pinVal);
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

DriverStatusCode GPIO::GPIO_Lock(GPIOTypes::GPIOPort port, GPIOTypes::GPIOPin pin) {
    GPIO_TypeDef* portVal = gpioPortsList[static_cast<int>(port)];
    uint8_t pinVal = static_cast<uint8_t>(pin);

    portVal->LCKR |= (0x01U << pinVal);

    //Write LCKK bit
    portVal->LCKR |= GPIO_LCKR_LCKK;

    //Clear LCKK bit
    portVal->LCKR &= GPIO_LCKR_LCKK;

    //Write LCKK bit again
    portVal->LCKR |= GPIO_LCKR_LCKK;

    //Mandatory read to enforce lock
    volatile uint32_t readLckk = portVal->LCKR;
    (void)readLckk;

    
    if ((portVal->LCKR & GPIO_LCKR_LCKK) == 0) return DriverStatusCode::ERROR_GPIO_LOCK;
    

    return DriverStatusCode::OK;
}