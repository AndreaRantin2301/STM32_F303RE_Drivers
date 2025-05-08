#include "drivers/clock_driver/systick_driver.h"
#include "drivers/clock_driver/clock_internal.h"
#include "ST/stm32f303xe.h"

volatile uint32_t currentTick = 0;

void SysTick_Handler(void)
{
    currentTick++;
}

void SysTick_Init(void) {

    SysTick_Type* systick = Get_SysTick();
    
    systick->LOAD = (SYSTEM_CLOCK / 1000) - 1;
    systick->VAL = 0;
    systick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

uint32_t Get_CurrentTick(void) {
    return currentTick;
}

void Delay_Ms(uint32_t delay) {
    uint32_t start = currentTick;
    while ((currentTick - start) < delay);
}

