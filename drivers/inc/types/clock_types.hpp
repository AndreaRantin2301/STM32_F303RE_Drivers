/**
* File: clock_types.hpp
* Created on: 2025-07-21 at 13:31
* Author: Andrea Rantin
* Description: This file contains definitions used for clock management such as 
* system clock source, various prescalers and multiplier factors
*/

#pragma once

#include "ST/stm32f303xe.h"

namespace ClockTypes {

    /**
    * @brief Clock source to generate the system clock.
    * For more info see reference manual at pages 139/140
    */
    enum class ClockSource {
        HSI,
        HSE,
        PLL,
    };

    /**
    * @brief Predivision factor for PLL source.
    * For more info see refence manual pages from 162 to 164
    */
    enum class ClockPrediv {
        PREDIV_1 = RCC_CFGR2_PREDIV_DIV1,
        PREDIV_2 = RCC_CFGR2_PREDIV_DIV2,
        PREDIV_3 = RCC_CFGR2_PREDIV_DIV3,
        PREDIV_4 = RCC_CFGR2_PREDIV_DIV4,
        PREDIV_5 = RCC_CFGR2_PREDIV_DIV5,
        PREDIV_6 = RCC_CFGR2_PREDIV_DIV6,
        PREDIV_7 = RCC_CFGR2_PREDIV_DIV7,
        PREDIV_8 = RCC_CFGR2_PREDIV_DIV8,
        PREDIV_9 = RCC_CFGR2_PREDIV_DIV9,
        PREDIV_10 = RCC_CFGR2_PREDIV_DIV10,
        PREDIV_11 = RCC_CFGR2_PREDIV_DIV11,
        PREDIV_12 = RCC_CFGR2_PREDIV_DIV12,
        PREDIV_13 = RCC_CFGR2_PREDIV_DIV13,
        PREDIV_14 = RCC_CFGR2_PREDIV_DIV14,
        PREDIV_15 = RCC_CFGR2_PREDIV_DIV15,
        PREDIV_16 = RCC_CFGR2_PREDIV_DIV16,
    };

    /**
    * @brief PLL source clock.
    * For more info see reference manual pages from 141 to 143
    */
    enum class ClockPLLSource {
        HSI_HALF = 0,
        HSI = RCC_CFGR_PLLSRC_HSI_PREDIV,
        HSE = RCC_CFGR_PLLSRC_HSE_PREDIV,
    };

    /**
    * @brief PLL clock multiplier factor.
    * For more info see reference manual pages from 141 to 143
    */
    enum class ClockPLLMul {
        PLL_MUL_2 = RCC_CFGR_PLLMUL2,
        PLL_MUL_3 = RCC_CFGR_PLLMUL3,
        PLL_MUL_4 = RCC_CFGR_PLLMUL4,
        PLL_MUL_5 = RCC_CFGR_PLLMUL5,
        PLL_MUL_6 = RCC_CFGR_PLLMUL6,
        PLL_MUL_7 = RCC_CFGR_PLLMUL7,
        PLL_MUL_8 = RCC_CFGR_PLLMUL8,
        PLL_MUL_9 = RCC_CFGR_PLLMUL9,
        PLL_MUL_10 = RCC_CFGR_PLLMUL10,
        PLL_MUL_11 = RCC_CFGR_PLLMUL11,
        PLL_MUL_12 = RCC_CFGR_PLLMUL12,
        PLL_MUL_13 = RCC_CFGR_PLLMUL13,
        PLL_MUL_14 = RCC_CFGR_PLLMUL14,
        PLL_MUL_15 = RCC_CFGR_PLLMUL15,
        PLL_MUL_16 = RCC_CFGR_PLLMUL16,
    };

    /**
    * @brief Prescaler factor for AHB bus clock.
    * For more info see reference manual pages from 141 to 143
    */
    enum class ClockAHBPre {
        AHB_PRE_NONE = RCC_CFGR_HPRE_DIV1,
        AHB_PRE_2 = RCC_CFGR_HPRE_DIV2,
        AHB_PRE_4 = RCC_CFGR_HPRE_DIV4,
        AHB_PRE_8 = RCC_CFGR_HPRE_DIV8,
        AHB_PRE_16 = RCC_CFGR_HPRE_DIV16,
        AHB_PRE_64 = RCC_CFGR_HPRE_DIV64,
        AHB_PRE_128 = RCC_CFGR_HPRE_DIV128,
        AHB_PRE_256 = RCC_CFGR_HPRE_DIV256,
        AHB_PRE_512 = RCC_CFGR_HPRE_DIV512,
    };

    /**
    * @brief Prescaler factor for APB1 bus clock.
    * For more info see reference manual pages from 141 to 143
    */
    enum class ClockAPB1Pre {
        APB1_PRE_NONE = RCC_CFGR_PPRE1_DIV1,
        APB1_PRE_2 = RCC_CFGR_PPRE1_DIV2,
        APB1_PRE_4 = RCC_CFGR_PPRE1_DIV4,
        APB1_PRE_8 = RCC_CFGR_PPRE1_DIV8,
        APB1_PRE_16 = RCC_CFGR_PPRE1_DIV16,
    };

    /**
    * @brief Prescaler factor for APB2 bus clock.
    * For more info see reference manual pages from 141 to 143
    */
    enum class ClockAPB2Pre {
        APB2_PRE_NONE = RCC_CFGR_PPRE2_DIV1,
        APB2_PRE_2 = RCC_CFGR_PPRE2_DIV2,
        APB2_PRE_4 = RCC_CFGR_PPRE2_DIV4,
        APB2_PRE_8 = RCC_CFGR_PPRE2_DIV8,
        APB2_PRE_16 = RCC_CFGR_PPRE2_DIV16
    };

}