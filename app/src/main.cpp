/**
* @file main.cpp
* @date 2025-07-20 20:50:56
* @author Andrea Rantin
* @description //TODO DOCS
*/

#include "main.hpp"
#include "clock/clock.hpp"
#include "gpio/gpio.hpp"

using namespace Clock;
using namespace GPIO;
using namespace ClockTypes;
using namespace FlashTypes;
using namespace GPIOTypes;

int main() {

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

    GPIOInitStruct gpioInitStruct;

    gpioInitStruct.port = GPIOPort::A;
    gpioInitStruct.pin = GPIOPin::PIN_5;
    gpioInitStruct.mode = GPIOMode::OUTPUT;

    GPIO_Init(gpioInitStruct);
    
  
    while (1) {
       GPIO_Toggle(GPIOPort::A, GPIOPin::PIN_5);
       for(volatile uint32_t i = 0; i < 1000000; i++){};
    }

    return 1;
}

