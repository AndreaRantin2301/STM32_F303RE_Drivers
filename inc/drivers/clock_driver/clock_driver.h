#ifndef CLOCK_DRIVER_H
#define CLOCK_DRIVER_H

#include "common/clock_types.h"

/**
 * @brief Initializes System clock at 72Mhz and also some peripheral clocks
 * 
 * @return ClockStatusCode CLOCK_OK if successful
 */
ClockStatusCode System_Clock_Init(void);

#endif