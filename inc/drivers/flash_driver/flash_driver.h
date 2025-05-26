#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include "common/flash_types.h"


/**
 * @brief Sets the flash latency to a value of @ref FlashLatency
 * 
 * @param latency Flash latency to set
 * @return FlashStatusCode FLASH_OK if successful
 */
FlashStatusCode Flash_Set_Latency(FlashLatency latency);

#ifdef UNIT_TEST
#include "ST/stm32f303xe.h"
#include <stdbool.h>
bool Is_Flash_Latency_Valid(int latency);
#endif


#endif