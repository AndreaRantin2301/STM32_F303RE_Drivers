#ifndef FLASH_TYPES_H
#define FLASH_TYPES_H

/**
 * @brief Enum representing the different latencies
 * assignable to the flash
 */
typedef enum {
    FLASH_LATENCY_ZERO_WAIT,
    FLASH_LATENCY_ONE_WAIT,
    FLASH_LATENCY_TWO_WAIT,
}FlashLatency;

/**
 * @brief Status code for all FLASH operations
 * 
 */
typedef enum {
    FLASH_OK,
    FLASH_INVALID_LATENCY,
}FlashStatusCode;

#endif
