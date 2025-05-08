#ifndef SYSTICK_DRIVER_H
#define SYSTICK_DRIVER_H

#include <stdint.h>

/**
 * @brief Initializes SysTick to count every 1ms
 * 
 */
void SysTick_Init(void);

/**
 * @brief Handler of SysTick. Triggers every 1ms
 * 
 */
void SysTick_Handler(void);

/**
 * @brief Returns the current tick value in ms
 * 
 * @return uint32_t current tick value in ms
 */
uint32_t Get_CurrentTick(void);

/**
 * @brief Halts execution of current flow for the specified
 * delay
 * @param delay Time to wait in ms
 */
void Delay_Ms(uint32_t delay);

#endif