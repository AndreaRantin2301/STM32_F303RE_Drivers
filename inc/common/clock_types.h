#ifndef CLOCK_TYPES_H
#define CLOCK_TYPES_H

/**
 * @brief Status codes for clock operations
 * 
 */
typedef enum {
    CLOCK_OK,
    CLOCK_ERROR_HSI,
    CLOCK_ERROR_PLL,
    CLOCK_ERROR_CLOCK_SOURCE,
}ClockStatusCode;

#endif