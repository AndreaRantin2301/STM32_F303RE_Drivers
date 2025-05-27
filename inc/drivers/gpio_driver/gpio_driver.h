#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "common/gpio_types.h"
#include <stdint.h>

/**
 * @brief Sets the given GPIO pin of the selected port to the assigned mode
 * 
 * @param portEnum Enum of the port of the pin
 * @param pinEnum Enum of the pin
 * @param mode Enum of the mode
 * 
 * @return GPIO_OK if successful
 */
GPIOStatusCode GPIO_Set_Mode(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOMode mode);

/**
 * @brief Sets the given Alternate Function to the selected GPIO pin
 * 
 * @param portEnum Enum of the port of the pin
 * @param pinEnum Enum of the pin
 * @param af Enum of the alternate function
 * 
 * @return GPIO_OK if successful
 */
GPIOStatusCode GPIO_Set_Alternate_Function(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOAlternateFunction af);

/**
 * @brief Toggles the selected GPIO pin
 * 
 * @param gpioPort Enum corresponding to the port of the GPIO pin
 * @param gpioPin Enum corresponding to the GPIO pin
 * @return GPIOStatusCode GPIO_OK if successful
 */
GPIOStatusCode GPIO_Toggle(GPIOPortEnum portEnum, GPIOPinEnum pinEnum);

/**
 * @brief Writes to the selected GPIO pin
 * 
 * @param gpioPort Enum corresponding to the port of the GPIO pin
 * @param gpioPin Enum corresponding to the GPIO pin
 * @param state Enum of the state to be set. This can be either 0 or 1
 * @return GPIOStatusCode GPIO_OK if successful
 */
GPIOStatusCode GPIO_Write(GPIOPortEnum gpioPort, GPIOPinEnum gpioPin, GPIOState state);

/**
 * @brief Reads the current state of the selected GPIO pin
 * 
 * @param gpioPort Enum corresponding to the port of the GPIO pin
 * @param gpioPin Enum corresponding to the GPIO pin
 * @return uint8_t State of the selected GPIO pin. This can be either 0 or 1
 */
uint8_t GPIO_Read(GPIOPortEnum gpioPort, GPIOPinEnum gpioPin);

/**
 * @brief Initializes GPIO with the data provided in the struct
 * 
 * @param gpioStruct Struct containing GPIO data such as port and pin enums,
 * mode and alternate function
 * @return GPIOStatusCode GPIO_OK if successful
 */
GPIOStatusCode GPIO_Init(GPIO_Init_Struct gpioStruct);

#ifdef UNIT_TEST
#include "ST/stm32f303xe.h"
#include <stddef.h>
#include <stdbool.h>
GPIO_TypeDef* GPIO_Get_Port(GPIOPortEnum portEnum);
bool Is_GPIOPinEnum_Valid(int pinEnum);
bool Is_AF_Valid(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOAlternateFunction af);
#include <stddef.h>
#include <stdbool.h>
#endif

#endif