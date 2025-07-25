/**
* File: gpio_internal.hpp
* Created on: 2025-07-25 at 11:31
* Author: Andrea Rantin
* Description: This file contains definitions that are used internally in the
* GPIO driver
*/

#pragma once

#include "ST/stm32f303xe.h"

static constexpr GPIO_TypeDef* gpioPortsList[] = {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
};

