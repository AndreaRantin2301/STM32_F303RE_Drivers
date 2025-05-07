#include "drivers/clock_driver/clock_internal.h"

RCC_TypeDef* Get_RCC(){
    return RCC;
}

SysTick_Type* Get_SysTick(){
    return SysTick;
}