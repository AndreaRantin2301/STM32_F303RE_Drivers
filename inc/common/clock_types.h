#ifndef CLOCK_TYPES_H
#define CLOCK_TYPES_H

#include "common/flash_types.h"

/**
 * @brief Status codes for clock operations
 * 
 */
typedef enum {
    CLOCK_OK,
    CLOCK_ERROR_HSI,
    CLOCK_ERROR_PLL,
    CLOCK_ERROR_CLOCK_SOURCE,
    CLOCK_ERROR_GPIO_CLOCK,
    CLOCK_ERROR_HSI_PLL_READY,
    CLOCK_ERROR_HSE_READY,
    CLOCK_ERROR_PLL_SOURCE,
    CLOCK_ERROR_PREDIV,
    CLOCK_ERROR_PLLMUL,
    CLOCK_ERROR_AHBPRE,
    CLOCK_ERROR_APB1PRE,
    CLOCK_ERROR_APB2PRE,
}ClockStatusCode;

typedef enum {
    CLOCK_SOURCE_HSI,
    CLOCK_SOURCE_HSE,
    CLOCK_SOURCE_PLL,
}ClockSource;

typedef enum {
    PLL_MUL_2 = 2,
    PLL_MUL_3,
    PLL_MUL_4,
    PLL_MUL_5,
    PLL_MUL_6,
    PLL_MUL_7,
    PLL_MUL_8,
    PLL_MUL_9,
    PLL_MUL_10,
    PLL_MUL_11,
    PLL_MUL_12,
    PLL_MUL_13,
    PLL_MUL_14,
    PLL_MUL_15,
    PLL_MUL_16,
}ClockPLLMul;

typedef enum {
    PREDIV_1 = 1,
    PREDIV_2,
    PREDIV_3,
    PREDIV_4,
    PREDIV_5,
    PREDIV_6,
    PREDIV_7,
    PREDIV_8,
    PREDIV_9,
    PREDIV_10,
    PREDIV_11,
    PREDIV_12,
    PREDIV_13,
    PREDIV_14,
    PREDIV_15,
    PREDIV_16,
}ClockPrediv;

typedef enum {
    AHB_PRE_NONE = 1,
    AHB_PRE_2 = 2,
    AHB_PRE_4 = 4,
    AHB_PRE_8 = 8,
    AHB_PRE_16 = 16,
    AHB_PRE_64 = 64,
    AHB_PRE_128 = 128,
    AHB_PRE_256 = 256,
    AHB_PRE_512 = 512,
}ClockAHBPrescaler;

typedef enum {
    APB1_PRE_NONE = 1,
    APB1_PRE_2 = 2,
    APB1_PRE_4 = 4,
    APB1_PRE_8 = 8,
    APB1_PRE_16 = 16,
}ClockAPB1Prescaler;

typedef enum {
    APB2_PRE_NONE = 1,
    APB2_PRE_2 = 2,
    APB2_PRE_4 = 4,
    APB2_PRE_8 = 8,
    APB2_PRE_16 = 16,
}ClockAPB2Prescaler;

typedef enum {
    PLL_SRC_HSI_HALF,
    PLL_SRC_HSI,
    PLL_SRC_HSE,
}ClockPLLSrc;

typedef struct {
    ClockSource source;
    ClockPLLSrc pllSrc;
    ClockPrediv prediv;
    ClockPLLMul pllMul;
    ClockAHBPrescaler ahbPre;
    ClockAPB1Prescaler apb1Pre;
    ClockAPB2Prescaler apb2Pre;
    FlashLatency flashLatency;
}ClockInitStruct;

#endif