#ifndef CLOCK_INTERNAL_H
#define CLOCK_INTERNAL_H

#include "ST/stm32f303xe.h"

//TODO ERROR IF SOMEONE OTHER THAN CLOCK DRIVER INCLUDES

RCC_TypeDef* Get_RCC();
SysTick_Type* Get_SysTick();

#endif