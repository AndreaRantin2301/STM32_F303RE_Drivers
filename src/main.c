#include "drivers/clock_driver/clock_driver.h"
#include "drivers/clock_driver/systick_driver.h"
#include "drivers/flash_driver/flash_driver.h"
#include "drivers/gpio_driver/gpio_driver.h"

int main(void) {

    ClockInitStruct clockInitStruct = {0};

    clockInitStruct.source = CLOCK_SOURCE_PLL;
    clockInitStruct.prediv = PREDIV_1;
    clockInitStruct.pllSrc = PLL_SRC_HSI;
    clockInitStruct.pllMul = PLL_MUL_9;
    clockInitStruct.flashLatency = FLASH_LATENCY_TWO_WAIT;
    clockInitStruct.ahbPre = AHB_PRE_NONE;
    clockInitStruct.apb1Pre = APB1_PRE_2;
    clockInitStruct.apb2Pre = APB2_PRE_NONE;

    //Initialize system clock
    if(System_Clock_Init(clockInitStruct) != CLOCK_OK) {
        while(1);
    }

    //Initialize systick with a 1ms trigger
    SysTick_Init();

    GPIO_Init_Struct gpioInitStruct = {0};

    gpioInitStruct.portEnum = GPIO_PORT_A;
    gpioInitStruct.pinEnum = GPIO_PIN_5;
    gpioInitStruct.mode  =GPIO_MODE_OUTPUT;
    gpioInitStruct.af = GPIO_AF_NONE;

    if(GPIO_Init(gpioInitStruct) != GPIO_OK) {
        while(1);
    }

    while(1) {
        GPIO_Toggle(GPIO_PORT_A, GPIO_PIN_5);
        Delay_Ms(3000);
    }

    return 0;
}