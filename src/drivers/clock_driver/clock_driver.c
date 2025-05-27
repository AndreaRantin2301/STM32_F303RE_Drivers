#include "drivers/clock_driver/clock_driver.h"
#define CLOCK_INTERNAL_USE
#include "drivers/clock_driver/clock_internal.h"
#undef CLOCK_INTERNAL_USE
#include "drivers/clock_driver/clock_flash_interface.h"

ClockFrequencies clockFrequencies = {0};

static ClockStatusCode Set_Clock_Source(ClockSource source) {

    RCC_TypeDef* rcc = Get_RCC();

    switch(source) {
        /*
        PLL needs to be disabled to be configured so its the same for HSI in this case
        */
        case CLOCK_SOURCE_HSI:
        case CLOCK_SOURCE_PLL:
            rcc->CR &= ~RCC_CR_HSEON;
            rcc->CR &= ~RCC_CR_PLLON;
            rcc->CR |= RCC_CR_HSION;
            break;
        case CLOCK_SOURCE_HSE:
            break;
        default:
            return CLOCK_ERROR_CLOCK_SOURCE;
    }

    //Give time to stabilize
    for(volatile uint32_t i = 0; i < 1000; i++) {};

    switch(source) {
        case CLOCK_SOURCE_HSI:
        case CLOCK_SOURCE_PLL:
            if(!IS_HSI_READY()) return CLOCK_ERROR_HSI_PLL_READY;
            break;
        case CLOCK_SOURCE_HSE:
            if(!IS_HSE_READY()) return CLOCK_ERROR_HSE_READY;
            break;
        default:
            return CLOCK_ERROR_CLOCK_SOURCE;
    }

    return CLOCK_OK;
}

static ClockStatusCode Set_PLL_Source(ClockPLLSrc pllSrc) {

    RCC_TypeDef* rcc = Get_RCC();

    rcc->CFGR &= ~RCC_CFGR_PLLSRC_Msk;

    switch(pllSrc) {
        case PLL_SRC_HSI_HALF:
            break;
        case PLL_SRC_HSI:
            rcc->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV;
            break;
        case PLL_SRC_HSE:
            rcc->CFGR |= RCC_CFGR_PLLSRC_HSE_PREDIV;
            break;
        default:
            return CLOCK_ERROR_PLL_SOURCE;
    }

    return CLOCK_OK;
}

static ClockStatusCode Set_Prediv(ClockPrediv prediv) {

    RCC_TypeDef* rcc = Get_RCC();
    rcc->CFGR2 &= ~RCC_CFGR2_PREDIV_Msk;

    switch(prediv) {
        case PREDIV_1:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV1;
            break;
        case PREDIV_2:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV2;
            break;
        case PREDIV_3:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV3;
            break;
        case PREDIV_4:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV4;
            break;
        case PREDIV_5:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV5;
            break;
        case PREDIV_6:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV6;
            break;
        case PREDIV_7:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV7;
            break;
        case PREDIV_8:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV8;
            break;
        case PREDIV_9:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV9;
            break;
        case PREDIV_10:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV10;
            break;
        case PREDIV_11:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV11;
            break;
        case PREDIV_12:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV12;
            break;
        case PREDIV_13:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV13;
            break;
        case PREDIV_14:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV14;
            break;
        case PREDIV_15:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV15;
            break;
        case PREDIV_16:
            rcc->CFGR2 |= RCC_CFGR2_PREDIV_DIV16;
            break;
        default:
            return CLOCK_ERROR_PREDIV;
    }

    return CLOCK_OK;
}

static ClockStatusCode Set_PLLMul(ClockPLLMul pllMul) {
    RCC_TypeDef* rcc = Get_RCC();
    rcc->CFGR &= ~RCC_CFGR_PLLMUL_Msk;

    switch(pllMul) {
        case PLL_MUL_2:
            rcc->CFGR |= RCC_CFGR_PLLMUL2;
            break;
        case PLL_MUL_3:
            rcc->CFGR |= RCC_CFGR_PLLMUL3;
            break;
        case PLL_MUL_4:
            rcc->CFGR |= RCC_CFGR_PLLMUL4;
            break;
        case PLL_MUL_5:
            rcc->CFGR |= RCC_CFGR_PLLMUL5;
            break;
        case PLL_MUL_6:
            rcc->CFGR |= RCC_CFGR_PLLMUL6;
            break;
        case PLL_MUL_7:
            rcc->CFGR |= RCC_CFGR_PLLMUL7;
            break;
        case PLL_MUL_8:
            rcc->CFGR |= RCC_CFGR_PLLMUL8;
            break;
        case PLL_MUL_9:
            rcc->CFGR |= RCC_CFGR_PLLMUL9;
            break;
        case PLL_MUL_10:
            rcc->CFGR |= RCC_CFGR_PLLMUL10;
            break;
        case PLL_MUL_11:
            rcc->CFGR |= RCC_CFGR_PLLMUL11;
            break;
        case PLL_MUL_12:
            rcc->CFGR |= RCC_CFGR_PLLMUL12;
            break;
        case PLL_MUL_13:
            rcc->CFGR |= RCC_CFGR_PLLMUL13;
            break;
        case PLL_MUL_14:
            rcc->CFGR |= RCC_CFGR_PLLMUL14;
            break;
        case PLL_MUL_15:
            rcc->CFGR |= RCC_CFGR_PLLMUL15;
            break;
        case PLL_MUL_16:
            rcc->CFGR |= RCC_CFGR_PLLMUL16;
            break;
        default:
            return CLOCK_ERROR_PLLMUL;
    }

    return CLOCK_OK;
}

static ClockStatusCode Set_AHB_Prescaler(ClockAHBPrescaler prescaler) {
    RCC_TypeDef* rcc = Get_RCC();

    rcc->CFGR &= ~RCC_CFGR_HPRE;

    switch(prescaler) {
        case AHB_PRE_NONE:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV1;
            break;
        case AHB_PRE_2:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV2;
            break;
        case AHB_PRE_4:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV4;
            break;
        case AHB_PRE_8:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV8;
            break;
        case AHB_PRE_16:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV16;
            break;
        case AHB_PRE_64:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV64;
            break;
        case AHB_PRE_128:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV128;
            break;
        case AHB_PRE_256:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV256;
            break;
        case AHB_PRE_512:
            rcc->CFGR |= RCC_CFGR_HPRE_DIV512;
            break;
        default:
            return CLOCK_ERROR_AHBPRE;
    }

    return CLOCK_OK;
}

static ClockStatusCode Set_APB1_Prescaler(ClockAPB1Prescaler prescaler) {
    RCC_TypeDef* rcc = Get_RCC();

    rcc->CFGR &= ~RCC_CFGR_PPRE1_Msk;

    switch(prescaler) {
        case APB1_PRE_NONE:
            rcc->CFGR |= RCC_CFGR_PPRE1_DIV1;
            break;
        case APB1_PRE_2:
            rcc->CFGR |= RCC_CFGR_PPRE1_DIV2;
            break;
        case APB1_PRE_4:
            rcc->CFGR |= RCC_CFGR_PPRE1_DIV4;
            break;
        case APB1_PRE_8:
            rcc->CFGR |= RCC_CFGR_PPRE1_DIV8;
            break;
        case APB1_PRE_16:
            rcc->CFGR |= RCC_CFGR_PPRE1_DIV16;
            break;
        default:    
            return CLOCK_ERROR_APB1PRE;
    }

    return CLOCK_OK;
}

static ClockStatusCode Set_APB2_Prescaler(ClockAPB2Prescaler prescaler) {
    RCC_TypeDef* rcc = Get_RCC();

    rcc->CFGR &= ~RCC_CFGR_PPRE2_Msk;

    switch(prescaler) {
        case APB2_PRE_NONE:
            rcc->CFGR |= RCC_CFGR_PPRE2_DIV1;
            break;
        case APB2_PRE_2:
            rcc->CFGR |= RCC_CFGR_PPRE2_DIV2;
            break;
        case APB2_PRE_4:
            rcc->CFGR |= RCC_CFGR_PPRE2_DIV4;
            break;
        case APB2_PRE_8:
            rcc->CFGR |= RCC_CFGR_PPRE2_DIV8;
            break;
        case APB2_PRE_16:
            rcc->CFGR |= RCC_CFGR_PPRE2_DIV16;
            break;
        default:
            return CLOCK_ERROR_APB2PRE;
    }

    return CLOCK_OK;
}


static void Calculate_System_Clock(ClockInitStruct clockStruct) {
    switch(clockStruct.source) {
        case CLOCK_SOURCE_HSI:
            clockFrequencies.systemClock = 8000000;
            break;
        case CLOCK_SOURCE_HSE:
            clockFrequencies.systemClock = clockFrequencies.hseClock;
            break;
        case CLOCK_SOURCE_PLL:
            switch(clockStruct.pllSrc) {
                case PLL_SRC_HSI_HALF:
                    clockFrequencies.systemClock = (uint32_t) ((4000000 / clockStruct.prediv) * clockStruct.pllMul);
                    break;
                case PLL_SRC_HSI:
                    clockFrequencies.systemClock = (uint32_t) ((8000000 / clockStruct.prediv) * clockStruct.pllMul);
                    break;
                case PLL_SRC_HSE:
                    clockFrequencies.systemClock = clockFrequencies.hseClock;
                    //Assuming HSE clock was set beforehand
                    clockFrequencies.systemClock /= clockStruct.prediv;
                    clockFrequencies.systemClock *= clockStruct.pllMul;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    clockFrequencies.ahbClock = (clockFrequencies.systemClock / clockStruct.ahbPre);
    clockFrequencies.apb1Clock = (clockFrequencies.systemClock / clockStruct.apb1Pre);
    clockFrequencies.apb2Clock = (clockFrequencies.systemClock / clockStruct.apb2Pre);
}

ClockStatusCode System_Clock_Init(ClockInitStruct clockStruct) {
    RCC_TypeDef* rcc = Get_RCC();

    ClockStatusCode checkError = Set_Clock_Source(clockStruct.source);
    if(checkError != CLOCK_OK) return checkError;

    checkError = Set_PLL_Source(clockStruct.pllSrc);
    if(checkError != CLOCK_OK) return checkError;

    checkError = Set_Prediv(clockStruct.prediv);
    if(checkError != CLOCK_OK) return checkError;

    checkError = Set_PLLMul(clockStruct.pllMul);
    if(checkError != CLOCK_OK) return checkError;

    //TODO CHANGE ERROR
    if(Flash_Set_Latency(clockStruct.flashLatency) != FLASH_OK) return CLOCK_ERROR_CLOCK_SOURCE;

    //ENABLE PLL
    if(clockStruct.source == CLOCK_SOURCE_PLL) {
        rcc->CR |= RCC_CR_PLLON;
        //GIVE TIME TO PLL TO STABILIZE
        for(volatile uint32_t i = 0; i < 1000; i++) {};
        //IF PLL NOT READY AFTER A WHILE THROW ERROR
        if(!IS_PLL_ON()) return CLOCK_ERROR_PLL;
        if (!IS_PLL_READY()) return CLOCK_ERROR_PLL;
    }
    
    checkError = Set_AHB_Prescaler(clockStruct.ahbPre);
    if(checkError != CLOCK_OK) return checkError;
    
    checkError = Set_APB1_Prescaler(clockStruct.apb1Pre);
    if(checkError != CLOCK_OK) return checkError;

    checkError = Set_APB2_Prescaler(clockStruct.apb2Pre);
    if(checkError != CLOCK_OK) return checkError;

    //CLEAR SYSTEM CLOCK SOURCE
    rcc->CFGR &= ~RCC_CFGR_SW_Msk;
    
    //SET SYSTEM CLOCK SOURCE
    switch(clockStruct.source) {
        case CLOCK_SOURCE_HSI:
            rcc->CFGR |= RCC_CFGR_SW_HSI;
            break;
        case CLOCK_SOURCE_HSE:
            rcc->CFGR |= RCC_CFGR_SW_HSE;
            break;
        case CLOCK_SOURCE_PLL:
            rcc->CFGR |= RCC_CFGR_SW_PLL;
            break;
        default:
            return CLOCK_ERROR_CLOCK_SOURCE;
    }

    //GIVE TIME FOR SYSTEM CLOCK TO BE SET
    for(volatile uint32_t i = 0; i < 1000; i++) {};

    if(!IS_PLL_SELECTED()) return CLOCK_ERROR_CLOCK_SOURCE;

    Calculate_System_Clock(clockStruct);

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

void Set_System_Clock(uint32_t clock) {
    clockFrequencies.systemClock = clock;
}

void Set_HSE_Clock(uint32_t clock) {
    clockFrequencies.hseClock = clock;
}

const ClockFrequencies *Get_Clock_Frequencies(void) {
    return &clockFrequencies;
}