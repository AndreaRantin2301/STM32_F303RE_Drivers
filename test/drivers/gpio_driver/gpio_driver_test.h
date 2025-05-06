#ifndef GPIO_DRIVER_TEST_H
#define GPIO_DRIVER_TEST_H

#define GPIO_DRIVER_INTERNAL_USE

#include "UNITY/unity.h"
#include "drivers/gpio_driver/gpio_driver.h"
#include "drivers/gpio_driver/gpio_internal.h"
#include "ST/stm32f303xe.h"
#include <string.h>

void Test_GPIO_Get_Port();
void Test_Is_GPIOPinEnum_Valid();
void Test_GPIO_Set_Mode();
void Test_GPIO_Toggle();
void Test_GPIO_Write();
void Test_GPIO_Read();
void Test_Is_AF_Valid();

#endif