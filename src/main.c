#include "drivers/clock_driver/clock_driver.h"
#include "drivers/clock_driver/systick_driver.h"
#include "drivers/flash_driver/flash_driver.h"
#include "drivers/gpio_driver/gpio_driver.h"

int main(void) {

    //Initialize system clock
    if(System_Clock_Init() != CLOCK_OK) {
        while(1);
    }

    //Initialize systick with a 1ms trigger
    SysTick_Init();

    //Enable clock on USER LED
    if(GPIO_Clock_Enable(GPIO_PORT_A) != CLOCK_OK) {
        while(1);
    }

    if(GPIO_Set_Mode(GPIO_PORT_A,GPIO_PIN_5,GPIO_MODE_OUTPUT) != GPIO_OK) {
        while(1);
    }

    while(1) {
        GPIO_Toggle(GPIO_PORT_A, GPIO_PIN_5);
        Delay_Ms(3000);
    }

    return 0;
}