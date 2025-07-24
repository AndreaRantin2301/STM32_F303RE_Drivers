/**
* File: clock.cpp
* Created on: 2025-07-21 at 14:18
* Author: Andrea Rantin
* Description: Implementation file for clock.hpp
*/

#include "clock/clock.hpp"
#include "clock/clock_internal.hpp"

using namespace ClockTypes;

/**
* @brief Sets the RCC clock source register from the provided enum value
* 
* @param clockSource Enum value for clock source
* @return DriverStatusCode The status code returned by this function can be:
*      - DriverStatusCode_t::OK If the clock source was set correctly
*      - DriverStatusCode_t::ERROR_CLOCK_READY If the clock source was not ready after being set
*/
static DriverStatusCode Set_Clock_Source(ClockSource clockSource) {

    RCC->CR &= ~RCC_CR_HSEON_Msk;
    RCC->CR &= ~RCC_CR_PLLON_Msk;

    //PLL is not yet managed here because it needs to be configured
    switch(clockSource) {
        case ClockSource::HSI:
            RCC->CR |= RCC_CR_HSION;
            //Give time to stabilize
            for(volatile uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
            if(!IS_HSI_ON()) return DriverStatusCode::ERROR_CLOCK_READY;
            break;
        case ClockSource::HSE:
            RCC->CR |= RCC_CR_HSEON;
            //Give time to stabilize
            for(volatile uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
            if(!IS_HSE_READY()) return DriverStatusCode::ERROR_CLOCK_READY;
            break;
        case ClockSource::PLL:
            RCC->CR |= RCC_CR_HSION;
            //Give time to stabilize
            for(volatile uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
            break;
        default:
            return DriverStatusCode::ERROR_CLOCK_READY;
    }
    return DriverStatusCode::OK;
}

/**
* @brief Sets the RCC PLL source register from the given enum value
* 
* @param pllSource Enum value for PLL source
*/
static void Set_PLL_Source(ClockPLLSource pllSource) {

    uint32_t pllSourceVal = static_cast<uint32_t>(pllSource);

    RCC->CFGR &= ~RCC_CFGR_PLLSRC_Msk;

    RCC->CFGR |= pllSourceVal;
}

/**
* @brief Sets the RCC Prediv register from the provided enum value
* 
* @param prediv Enum value for prediv
*/
static void Set_Prediv(ClockPrediv prediv) {

    uint32_t predivVal = static_cast<uint32_t>(prediv);

    RCC->CFGR2 &= ~RCC_CFGR2_PREDIV_Msk;

    RCC->CFGR2 |= predivVal;
}

/**
* @brief Sets the RCC PLL multiplier register from the given enum value
* 
* @param pllMul Enum value for PLL multiplier
*/
static void Set_PLL_Multiplier(ClockPLLMul pllMul) {

    uint32_t pllMulVal = static_cast<uint32_t>(pllMul);

    RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;

    RCC->CFGR |= pllMulVal;
}

/**
* @brief Sets the FLASH Latency register from the given enum value
* 
* @param flashLatency Enum value for flash latency
*/
static void Set_Flash_Latency(FlashTypes::FlashLatency flashLatency) {

    uint32_t flashLatencyVal = static_cast<uint32_t>(flashLatency);

    FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;

    FLASH->ACR |= flashLatencyVal;
}

/**
* @brief Sets RCC AHB bus prescaler register from the given enum value
* 
* @param ahbpre Enum value for AHB bus prescaler
*/
static void Set_AHB_Prescaler(ClockAHBPre ahbpre) {

    uint32_t ahbPreVal = static_cast<uint32_t>(ahbpre);

    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;

    RCC->CFGR |= ahbPreVal;
}

/**
* @brief Sets the RCC APB1 bus prescaler register from the given enum value
* 
* @param apb1Pre Enum value for APB1 bus prescaler
*/
static void Set_APB1_Prescaler(ClockAPB1Pre apb1Pre) {

    uint32_t apb1PreVal = static_cast<uint32_t>(apb1Pre);

    RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;

    RCC->CFGR |= apb1PreVal;
}

/**
* @brief Sets the RCC APB2 bus prescaler register from the given enum
* 
* @param apb2Pre Enum value for APB2 bus prescaler
*/
static void Set_APB2_Prescaler(ClockAPB2Pre apb2Pre) {

    uint32_t apb2PreVal = static_cast<uint32_t>(apb2Pre);

    RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;

    RCC->CFGR |= apb2PreVal;
}

DriverStatusCode Clock::Clock_Init(ClockInitStruct clockInitStruct) {

    Set_AHB_Prescaler(clockInitStruct.ahbPre);

    Set_APB1_Prescaler(clockInitStruct.apb1Pre);

    Set_APB2_Prescaler(clockInitStruct.apb2Pre);

    DriverStatusCode checkError = Set_Clock_Source(clockInitStruct.clockSource);
    if(checkError != DriverStatusCode::OK) return checkError;

    Set_PLL_Source(clockInitStruct.pllSource);

    Set_Prediv(clockInitStruct.prediv);

    Set_PLL_Multiplier(clockInitStruct.pllMul);

    Set_Flash_Latency(clockInitStruct.flashLatency);

    //PLL has ben configured, now we can activate it if it was selected as clock source
    if(clockInitStruct.clockSource == ClockSource::PLL) {
        RCC->CR |= RCC_CR_PLLON;
        //Give time for PLL to stabilize
        for(uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
        if(!IS_PLL_ON()) return DriverStatusCode::ERROR_CLOCK_READY;
        if(!IS_PLL_READY()) return DriverStatusCode::ERROR_CLOCK_READY;
    }

    RCC->CFGR &= ~RCC_CFGR_SW_Msk;

    if(clockInitStruct.clockSource == ClockSource::HSI){
        RCC->CFGR |= RCC_CFGR_SW_HSI;
        for(volatile uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
        if(!IS_HSI_SELECTED()) return DriverStatusCode::ERROR_CLOCK_SELECTED;
    } 
    if(clockInitStruct.clockSource == ClockSource::HSE){
        RCC->CFGR |= RCC_CFGR_SW_HSE;
        for(volatile uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
        if(!IS_HSE_SELECTED()) return DriverStatusCode::ERROR_CLOCK_SELECTED;
    }
    if(clockInitStruct.clockSource == ClockSource::PLL){
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        for(volatile uint16_t i = 0; i < CLOCK_STABILIZE_TIME; i++) {};
        if(!IS_PLL_SELECTED()) return DriverStatusCode::ERROR_CLOCK_SELECTED;
    } 

    return DriverStatusCode::OK;
}
