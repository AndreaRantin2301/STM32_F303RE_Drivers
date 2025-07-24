/**
* @file main.cpp
* @date 2025-07-20 20:50:56
* @author Andrea Rantin
* @description //TODO DOCS
*/

#include "main.hpp"
#include "clock/clock.hpp"

using namespace Clock;
using namespace ClockTypes;
using namespace FlashTypes;

int a = 0;

extern "C" int main() {

    ClockInitStruct clockInitStruct;

    clockInitStruct.clockSource = ClockSource::PLL;
    clockInitStruct.flashLatency = FlashLatency::LATENCY_TWO_WAIT;
    clockInitStruct.prediv = ClockPrediv::PREDIV_1;
    clockInitStruct.pllSource = ClockPLLSource::HSI;
    clockInitStruct.pllMul = ClockPLLMul::PLL_MUL_9;
    clockInitStruct.ahbPre = ClockAHBPre::AHB_PRE_NONE;
    clockInitStruct.apb1Pre = ClockAPB1Pre::APB1_PRE_2;
    clockInitStruct.apb2Pre = ClockAPB2Pre::APB2_PRE_NONE;

    if(Clock_Init(clockInitStruct) != DriverStatusCode::OK) {
        while(1) {
            __builtin_trap(); // To avoid static analyzer error
        }
    }

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIOA->MODER &= ~(0x3 << (5 * 2));  // Clear bits 11:10
    GPIOA->MODER |=  (0x1 << (5 * 2));  // Set bit 10 to 1 (01)
    
  
    while (1) {
       GPIOA->ODR ^= (1U << 5);
       for(volatile uint32_t i = 0; i < 1000000; i++){};
    }

    return 1;
}

