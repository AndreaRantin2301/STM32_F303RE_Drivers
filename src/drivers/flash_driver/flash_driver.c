#include "drivers/flash_driver/flash_driver.h"
#define FLASH_INTERNAL_USE
#include "drivers/flash_driver/flash_internal.h"
#undef FLASH_INTERNAL_USE
#include <stdbool.h>
#include "ST/stm32f303xe.h"

#ifndef UNIT_TEST
static bool Is_Flash_Latency_Valid(int latency) {
    return ((latency >= FLASH_LATENCY_ZERO_WAIT) && (latency <= FLASH_LATENCY_TWO_WAIT));
}
#endif

FlashStatusCode Flash_Set_Latency(FlashLatency latency) {
    if(!Is_Flash_Latency_Valid(latency)) return FLASH_INVALID_LATENCY;

    FLASH_TypeDef* flash = Get_Flash();
    //Clear flash latency register
    
    flash->ACR &= ~FLASH_ACR_LATENCY_Msk;
    switch(latency) {
        case FLASH_LATENCY_ZERO_WAIT:
            //Register was already cleared so do nothing here
            break;
        case FLASH_LATENCY_ONE_WAIT:
            flash->ACR |= FLASH_ACR_LATENCY_0;
            break;
        case FLASH_LATENCY_TWO_WAIT:
            flash->ACR |= FLASH_ACR_LATENCY_1;
            break;
        default:
            break;
    }
    return FLASH_OK;
}