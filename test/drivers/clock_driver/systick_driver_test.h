#ifndef SYSTICK_DRIVER_TEST_H
#define SYSTICK_DRIVER_TEST_H

#define CLOCK_INTERNAL_USE

#include "UNITY/unity.h"
#include "ST/stm32f303xe.h"
#include <stdbool.h>
#include "drivers/clock_driver/clock_internal.h"
#include "drivers/clock_driver/systick_driver.h"

/**
 * @brief Tests SysTick_Init function from systick_driver.c
 * 
 */
void Test_SysTick_Init();

#endif