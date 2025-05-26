#ifndef FLASH_DRIVER_TEST_H
#define FLASH_DRIVER_TEST_H

#define FLASH_INTERNAL_USE

#include "UNITY/unity.h"
#include "ST/stm32f303xe.h"
#include <stdbool.h>
#include "drivers/flash_driver/flash_driver.h"

/**
 * @brief Tests the Is_Flash_Latency_Valid function from
 * flash_driver.c with all possible latency values
 * 
 */
void Test_Is_Flash_Latency_Valid();

/**
 * @brief Tests the Flash_Set_Latency function
 * It tests all the 3 possible latencies
 * 
 */
void Test_Flash_Set_Latency();

#endif