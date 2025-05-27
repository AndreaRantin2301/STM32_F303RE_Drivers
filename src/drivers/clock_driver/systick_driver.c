#include "drivers/clock_driver/systick_driver.h"
#define CLOCK_INTERNAL_USE
#include "drivers/clock_driver/clock_internal.h"
#undef CLOCK_INTERNAL_USE
#include "ST/stm32f303xe.h"

volatile uint32_t currentTick = 0;

void SysTick_Handler(void)
{
    currentTick++;
}

ClockStatusCode SysTick_Init(uint32_t periodMs) {

    SysTick_Type* systick = Get_SysTick();

    const ClockFrequencies *frequencies = Get_Clock_Frequencies();

    if((frequencies->ahbClock % periodMs) != 0) return CLOCK_ERROR_SYSTICK_PERIOD;
    
    systick->LOAD = (frequencies->ahbClock / periodMs) - 1;
    systick->VAL = 0;
    systick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
    return CLOCK_OK;
}

uint32_t Get_CurrentTick(void) {
    return currentTick;
}

void Delay_Ms(uint32_t delay) {
    uint32_t start = currentTick;
    while ((currentTick - start) < delay);
}

