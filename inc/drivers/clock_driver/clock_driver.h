#ifndef CLOCK_DRIVER_H
#define CLOCK_DRIVER_H

#include "common/clock_types.h"
#include "common/gpio_types.h"

/**
* @brief Initializes System clock at 72Mhz and also some peripheral clocks
* 
* @return ClockStatusCode CLOCK_OK if successful
*/
ClockStatusCode System_Clock_Init(void);

/**
* @brief Enables the clock on the given GPIO port
* 
* @param portEnum Value of @ref GPIOPortEnum that represents the GPIO port to enable
* @return ClockStatusCode CLOCK_OK if successfull
*/
ClockStatusCode GPIO_Clock_Enable(GPIOPortEnum portEnum);

#endif