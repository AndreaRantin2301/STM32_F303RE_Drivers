/*
    This file is for internal testing purposes only
    remove this every time you merge to avoid conflicts with the
    actual main
*/

#include "drivers/gpio_driver/gpio_driver.h"

int main(void) {

    GPIO_Init_Struct test = {0};

    GPIOStatusCode check = GPIO_Init(test);
    (void) check;

    while(1) {

    }

    return 0;
}