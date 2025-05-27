#include "drivers/gpio_driver/gpio_driver.h"
#include "drivers/gpio_driver/gpio_internal.h"
#include "drivers/gpio_driver/gpio_clock_interface.h"
#include "ST/stm32f303xe.h"
#include <stddef.h>
#include <stdbool.h>

#ifndef UNIT_TEST
/**
 * @brief Returns a pointer to the GPIO port corresponding to @ref GPIOPortEnum. NULL
 * if the enum was not a valid one. It is responsibility of the caller to check if the returned
 * pointer is valid or not
 * 
 * @param portEnum Enum of the GPIO port
 * @return GPIO_TypeDef* Pointer to the GPIO port corresponding to the
 */
static inline GPIO_TypeDef* GPIO_Get_Port(GPIOPortEnum portEnum) {
    switch(portEnum) {
        case GPIO_PORT_A:
            return GPIOA;
        case GPIO_PORT_B:
            return GPIOB;
        case GPIO_PORT_C:
            return GPIOC;
        case GPIO_PORT_D:
            return GPIOD;
        case GPIO_PORT_E:
            return GPIOE;
        case GPIO_PORT_F:
            return GPIOF;
        case GPIO_PORT_G:
            return GPIOG;
        case GPIO_PORT_H:
            return GPIOH;
        default:
            return NULL;
    }
    return NULL;
}

/**
 * @brief Checks if the given GPIOPinEnum is within the range of accepted values(0 to 15)
 * 
 * @param pinEnum Integer value of @ref GPIOPinEnum
 * @return true If the value corresponds to a valid pin
 * @return false If the value does not correspond to a valid pin
 */
static inline bool Is_GPIOPinEnum_Valid(int pinEnum) {
    return ((pinEnum >= GPIO_PIN_0) && (pinEnum <= GPIO_PIN_15));
}

/**
 * @brief Validates whenever a given alternate function is compatible with the pin
 * of the given port
 * 
 * @param portEnum Enum of the GPIO port
 * @param pinEnum Enum of the GPIO pin
 * @param af Enum of the Alternate function
 * @return true If the Alternate function is compatible with the pin
 * @return false If the alternate function is not compatible with the pin
 */
static inline bool Is_AF_Valid(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOAlternateFunction af) {
    uint8_t len = (sizeof(AFValidationTable) / sizeof(AFValidationTable[0]));
    for (uint8_t i = 0; i < len; ++i) {
        if (AFValidationTable[i].port == portEnum && AFValidationTable[i].pin == pinEnum) {
            return (AFValidationTable[i].afMask & (1U << af)) != 0;
        }
    }
    return false;
}
#endif

GPIOStatusCode GPIO_Set_Mode(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOMode mode) {

    /*
    Get the GPIO port corresponding to the portEnum
    return error if NULL
    */
    GPIO_TypeDef* port = GPIO_Get_Port(portEnum);
    if(port == NULL) return GPIO_INVALID_PORT;

    //If given pin is not valid return error
    if(!Is_GPIOPinEnum_Valid(pinEnum)) return GPIO_INVAID_PIN;

    //Get bits position in MODER register(each pin has 2 bits)
    uint32_t pinBitsPos = (pinEnum * 2);

    //Clear MODER register
    port->MODER &= ~(0x3U << pinBitsPos);

    switch(mode) {
        case GPIO_MODE_INPUT:  
            /*
            If selected mode was INPUT the register was already cleared 
            so do nothing
            */
            break;
        case GPIO_MODE_OUTPUT:
            port->MODER |= (0x1U << pinBitsPos);
            break;
        case GPIO_MODE_ALTERNATE:
            port->MODER |= (0x2U << pinBitsPos);
            break;
        case GPIO_MODE_ANALOG:
            port->MODER |= (0x3U << pinBitsPos);
            break;
        default:
            //Provided mode was not inside enum so return error
            return GPIO_INVALID_MODE;
    }

    return GPIO_OK;
}

GPIOStatusCode GPIO_Set_Alternate_Function(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOAlternateFunction af) {

    /*
    Get the GPIO port corresponding to the portEnum
    return error if NULL
    */
   GPIO_TypeDef* port = GPIO_Get_Port(portEnum);
   if(port == NULL) return GPIO_INVALID_PORT;

   //If given pin is not valid return error
   if(!Is_GPIOPinEnum_Valid(pinEnum)) return GPIO_INVAID_PIN;

   if(!Is_AF_Valid(portEnum,pinEnum,af)) return GPIO_INVALID_AF;

   //Check which afr register to use
   uint32_t afrIndex = (pinEnum < 8) ? 0 : 1;
   //Check which bits correspond to the given pin
   uint32_t afrBitsPos = (pinEnum % 8) * 4;

   //Set AFR
   port->AFR[afrIndex] &= ~(0xFU << afrBitsPos);
   port->AFR[afrIndex] |= ((af & 0xFU) << afrBitsPos);

    return GPIO_OK;
}

GPIOStatusCode GPIO_Toggle(GPIOPortEnum portEnum, GPIOPinEnum pinEnum) {
    GPIO_TypeDef* port = GPIO_Get_Port(portEnum);
    if(port == NULL) return GPIO_INVALID_PORT;
    if(!Is_GPIOPinEnum_Valid(pinEnum)) return GPIO_INVAID_PIN;

    port->ODR ^= (1U << pinEnum);

    return GPIO_OK;
}

GPIOStatusCode GPIO_Write(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOState state) {
    GPIO_TypeDef* port = GPIO_Get_Port(portEnum);
    if(port == NULL) return GPIO_INVALID_PORT;
    if(!Is_GPIOPinEnum_Valid(pinEnum)) return GPIO_INVAID_PIN;

    port->ODR &= ~(1U << pinEnum);

    if(state == GPIO_STATE_SET) {
        port->ODR |= (1U << pinEnum);
    }

    return GPIO_OK;
}

uint8_t GPIO_Read(GPIOPortEnum portEnum, GPIOPinEnum pinEnum) {
    GPIO_TypeDef* port = GPIO_Get_Port(portEnum);
    if(port == NULL) return 0;
    return (uint8_t)((port->IDR & (1U << pinEnum)) != 0);
}

GPIOStatusCode GPIO_Init(GPIO_Init_Struct gpioStruct) {
    if(GPIO_Clock_Enable(gpioStruct.portEnum) != CLOCK_OK) return GPIO_INIT_ERROR;

    GPIOStatusCode checkError = GPIO_OK;

    checkError = GPIO_Set_Mode(gpioStruct.portEnum,gpioStruct.pinEnum,gpioStruct.mode);
    if(checkError != GPIO_OK) return checkError;

    if(gpioStruct.af != GPIO_AF_NONE) {
        if(gpioStruct.mode != GPIO_MODE_ALTERNATE) return GPIO_INVALID_MODE;
        checkError = GPIO_Set_Alternate_Function(gpioStruct.portEnum,gpioStruct.pinEnum,gpioStruct.af);
    }
    return checkError;
}