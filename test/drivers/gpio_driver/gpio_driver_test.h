#ifndef GPIO_DRIVER_TEST_H
#define GPIO_DRIVER_TEST_H

#define GPIO_DRIVER_INTERNAL_USE

#include "UNITY/unity.h"
#include "drivers/gpio_driver/gpio_driver.h"
#include "drivers/gpio_driver/gpio_internal.h"
#include "drivers/gpio_driver/gpio_test_utils.h"
#include "ST/stm32f303xe.h"
#include <string.h>

/**
 * @brief Tests the GPIO_Get_Port function from gpio_driver.c
 * Since the function is static in production this uses a mock one that returns pointers
 * to different mocks according to the given port
 */
void Test_GPIO_Get_Port();

/**
 * @brief Tests the Is_GPIOPinEnum_Valid function from gpio_driver.c
 * Since the function is static in production this uses a mock one that is identical to the production
 * one
 */
void Test_Is_GPIOPinEnum_Valid();

/**
 * @brief Tests the Is_AF_Valid function from gpio_driver.c
 * Since the function is static in production this uses a mock one that is identical to the production
 * one
 */
void Test_Is_AF_Valid();

/**
 * @brief Tests the GPIO_Set_Mode function from gpio_driver.c 
 * It will test the correct failure if the given port or pin are invalid
 * And it will test all pins of the selected port in all possible modes
 * 
 */
void Test_GPIO_Set_Mode();

/**
 * @brief Tests the GPIO_Toggle function from gpio_driver.c
 * It will test the toggling from 0 to 1 and vice versa
 * 
 */
void Test_GPIO_Toggle();

/**
 * @brief Tests the GPIO_Write function from gpio_driver.c
 * It will test writing both 0 and 1 on the pin
 * 
 */
void Test_GPIO_Write();

/**
 * @brief Tests the GPIO_Read function from gpio_driver.c
 * It will test reading both 0 and 1 on the pin
 * 
 */
void Test_GPIO_Read();

/**
 * @brief Tests the GPIO_Set_Alternate_Function from gpio_driver.c
 * It will test all the alternate functions of all pins
 * 
 */
void Test_GPIO_Set_Alternate_Function();

#endif