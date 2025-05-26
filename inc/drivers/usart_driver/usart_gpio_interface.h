#ifndef USART_GPIO_INTERFACE_H
#define USART_GPIO_INTERFACE_H

#include "common/gpio_types.h"

GPIOStatusCode GPIO_Set_Mode(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOMode mode);

#endif