#ifndef CLOCK_INTERNAL_H
#define CLOCK_INTERNAL_H

#ifndef CLOCK_INTERNAL_USE
#error "clock_internal.h is private clock functionality and can only be included by clock_driver.c"
#endif

#include "common/clock_types.h"
#include "ST/stm32f303xe.h"
#include <stdbool.h>

#define SYSTEM_CLOCK    72000000

const ClockFrequencies *Get_Clock_Frequencies(void);

#ifndef UNIT_TEST
static inline RCC_TypeDef* Get_RCC(){return RCC;}
static inline SysTick_Type* Get_SysTick(){return SysTick;}
static inline bool IS_HSI_READY(){return (RCC->CR & RCC_CR_HSIRDY);}
static inline bool IS_PLL_ON(){return(RCC->CR & RCC_CR_PLLON);}
static inline bool IS_PLL_READY(){return(RCC->CR & RCC_CR_PLLRDY);}
static inline bool IS_PLL_SELECTED(){return(RCC->CFGR & RCC_CFGR_SWS_PLL);}
static inline bool IS_HSE_READY(){return (RCC->CR & RCC_CR_HSERDY);}
#else
RCC_TypeDef* Get_RCC();
SysTick_Type* Get_SysTick();
bool IS_HSI_READY();
bool IS_PLL_ON();
bool IS_PLL_READY();
bool IS_PLL_SELECTED();
#endif

#endif