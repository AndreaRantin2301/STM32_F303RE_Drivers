/**
* File: clock_internal.hpp
* Created on: 2025-07-21 at 15:05
* Author: Andrea Rantin
* Description: This file contains utility macros of constants definitions
* that are used internally in the clock driver source files
*/

#pragma once

#include "ST/stm32f303xe.h"

/**
* @brief Used as value to reach with counter in
* empty for loop before the clock is initialized to give
* some delay where it's needed(I.E when clock source is set).
* This is because the delay function cannot yet be configured
* without the system clock initialized
*/
static constexpr uint16_t CLOCK_STABILIZE_TIME = 1000;

/**
* @brief Macro to check if HSI is on
* 
* @return true HSI is on
* @return false HSI is off
*/
static inline bool IS_HSI_ON(){return (RCC->CR & RCC_CR_HSION);}

/**
* @brief Macro to check is HSE is on
* 
* @return true HSE is on
* @return false HSE is off
*/
static inline bool IS_HSE_ON(){return (RCC->CR & RCC_CR_HSEON);}

/**
* @brief Macro to check if PLL is on
* 
* @return true PLL is on
* @return false PLL is off
*/
static inline bool IS_PLL_ON(){return (RCC->CR & RCC_CR_PLLON);}

/**
* @brief Macro to check if HSI is ready
* 
* @return true HSI is ready
* @return false HSI is not ready
*/
static inline bool IS_HSI_READY(){return (RCC->CR & RCC_CR_HSIRDY);}

/**
* @brief Macro to check if HSE is ready
* 
* @return true HSE is ready
* @return false HSE is not ready
*/
static inline bool IS_HSE_READY(){return (RCC->CR & RCC_CR_HSERDY);}

/**
* @brief Macro to check if PLL is ready
* 
* @return true PLL is ready
* @return false PLL is not ready
*/
static inline bool IS_PLL_READY(){return (RCC->CR & RCC_CR_PLLRDY);}

/**
* @brief Macro to check if HSI was selected as clock source
* 
* @return true HSI selected as clock source
* @return false HSI not selected as clock source
*/
static inline bool IS_HSI_SELECTED() {return ((RCC->CFGR & RCC_CFGR_SWS_Msk) == RCC_CFGR_SWS_HSI);}

/**
* @brief Macro to check if HSE was selected as clock source
* 
* @return true HSE was selected as clock source
* @return false HSE was not selected as clock source
*/
static inline bool IS_HSE_SELECTED() {return ((RCC->CFGR & RCC_CFGR_SWS_Msk) == RCC_CFGR_SWS_HSE);}

/**
* @brief Macro to check if PLL was selected as clock source
* 
* @return true PLL was selected as clock source
* @return false PLL was not selected as clock source
*/
static inline bool IS_PLL_SELECTED() {return ((RCC->CFGR & RCC_CFGR_SWS_Msk) == RCC_CFGR_SWS_PLL);}

/**
 * @brief Internal structure for clock source.
 * This structure allows to avoid using lots of ifs and switches because
 * it unifies the clock source enabling and selection
 * 
 */
typedef struct {
    uint32_t clockEnableBits; /*!< Mask for the CR register of RCC to enable the clock source */
    bool (*isReadyFunction)(); /*!< Function to check if the clock source is ready */
    uint32_t clockSelectBits; /*!< Mask for the CFGR register to select the clock source */
    bool (*isSelectedFunction)(); /*!< Function to check if the clock source is selected */
}ClockSourceStruct;

static constexpr ClockSourceStruct clockSourceStructTable[] = {
    {RCC_CR_HSION, IS_HSI_READY, RCC_CFGR_SW_HSI, IS_HSI_SELECTED},
    {RCC_CR_HSEON, IS_HSE_READY, RCC_CFGR_SW_HSE, IS_HSE_SELECTED},
    {RCC_CR_HSION, IS_HSI_READY, RCC_CFGR_SW_PLL, IS_PLL_SELECTED},
};

