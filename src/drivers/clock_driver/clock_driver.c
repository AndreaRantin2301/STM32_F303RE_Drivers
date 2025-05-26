#include "drivers/clock_driver/clock_driver.h"
#define CLOCK_INTERNAL_USE
#include "drivers/clock_driver/clock_internal.h"
#undef CLOCK_INTERNAL_USE
#include "drivers/clock_driver/clock_flash_interface.h"

ClockStatusCode System_Clock_Init(void) {
    RCC_TypeDef* rcc = Get_RCC();

    //INITIALIZE HSI
    rcc->CR |= RCC_CR_HSION;

    //GIVE TIME TO HSI TO STABILIZE
    for(volatile uint32_t i = 0; i < 100000; i++) {};

    //IF HSI IS NOT READY AFTER A WHILE THOW ERROR
    if(!IS_HSI_READY()) return CLOCK_ERROR_HSI;

    //DISABLE PLL
    rcc->CR &= ~RCC_CR_PLLON;

    //RESET PLL CLOCK SOURCE(SO SET HSI/2 BY DEFAULT)
    rcc->CFGR &= ~RCC_CFGR_PLLSRC_Msk;

    //SET NO DIVISION FOR PLL HSI INPUT
    rcc->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;

    //CLEAR PREDIV
    rcc->CFGR2 &= ~RCC_CFGR2_PREDIV_Msk;
    //SET PREDIV TO 1
    rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV1;

    //CLEAR PLL MULTIPLIER
    rcc->CFGR &= ~RCC_CFGR_PLLMUL_Msk;
    //SET PLL MULTIPLIER TO 9 SO that 8Mhz x 9 = 72Mhz
    rcc->CFGR |= RCC_CFGR_PLLMUL9;

    //SET FLASH LATENCY FOR 72MHZ
    Flash_Set_Latency(FLASH_LATENCY_TWO_WAIT);

    //ENABLE PLL
    rcc->CR |= RCC_CR_PLLON;

    //GIVE TIME TO PLL TO STABILIZE
    for(volatile uint32_t i = 0; i < 100000; i++) {};

    //IF PLL NOT READY AFTER A WHILE THROW ERROR
    if(!IS_PLL_ON()) return CLOCK_ERROR_PLL;
    if (!IS_PLL_READY()) return CLOCK_ERROR_PLL;

    //AHB CLOCK TO 72MHZ
    rcc->CFGR &= ~RCC_CFGR_HPRE;
    rcc->CFGR |= RCC_CFGR_HPRE_DIV1;

    //APB1 CLOCK TO 36MHZ
    rcc->CFGR &= ~RCC_CFGR_PPRE1_Msk;
    rcc->CFGR |= RCC_CFGR_PPRE1_DIV2;

    //APB2 CLOCK TO 72MHZ
    rcc->CFGR &= ~RCC_CFGR_PPRE2_Msk;
    rcc->CFGR |= RCC_CFGR_PPRE2_DIV1;

    //CLEAR SYSTEM CLOCK SOURCE
    rcc->CFGR &= ~RCC_CFGR_SW_Msk;
    
    //SET PLL AS SYSTEM CLOCK SOURCE
    rcc->CFGR |= RCC_CFGR_SW_PLL;

    //GIVE TIME FOR SYSTEM CLOCK TO BE SET
    for(volatile uint32_t i = 0; i < 100000; i++) {};

    if(!IS_PLL_SELECTED()) return CLOCK_ERROR_CLOCK_SOURCE;

    return CLOCK_OK;
}

ClockStatusCode GPIO_Clock_Enable(GPIOPortEnum portEnum) {

    RCC_TypeDef* rcc = Get_RCC();

     switch(portEnum) {
        case GPIO_PORT_A:
            rcc->AHBENR |= RCC_AHBENR_GPIOAEN;
            break;
        case GPIO_PORT_B:
            rcc->AHBENR |= RCC_AHBENR_GPIOBEN;
            break;
        case GPIO_PORT_C:
            rcc->AHBENR |= RCC_AHBENR_GPIOCEN;
            break;
        case GPIO_PORT_D:
            rcc->AHBENR |= RCC_AHBENR_GPIODEN;
            break;
        case GPIO_PORT_E:
            rcc->AHBENR |= RCC_AHBENR_GPIOEEN;
            break;
        case GPIO_PORT_F:
            rcc->AHBENR |= RCC_AHBENR_GPIOFEN;
            break;
        case GPIO_PORT_G:
            rcc->AHBENR |= RCC_AHBENR_GPIOGEN;
            break;
        case GPIO_PORT_H:
            rcc->AHBENR |= RCC_AHBENR_GPIOHEN;
            break;
        default:
            return CLOCK_ERROR_GPIO_CLOCK;
    }

    return CLOCK_OK;
}