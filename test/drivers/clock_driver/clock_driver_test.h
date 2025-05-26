#ifndef CLOCK_DRIVER_TEST_H
#define CLOCK_DRIVER_TEST_H

#define CLOCK_INTERNAL_USE

#include "UNITY/unity.h"
#include "ST/stm32f303xe.h"
#include <stdbool.h>
#include "drivers/clock_driver/clock_driver.h"
#include "drivers/clock_driver/clock_flash_interface.h"
#include "drivers/clock_driver/clock_internal.h"

/**
 * @brief Tests the System_Clock_Init function from clock_driver.c
 * 
 */
void Test_System_Clock_Init();

#endif