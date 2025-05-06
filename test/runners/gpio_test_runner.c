#include "drivers/gpio_driver/gpio_driver_test.h"

GPIO_TypeDef mockGpio = {0};

void setUp(void)
{
    memset(&mockGpio, 0, sizeof(GPIO_TypeDef));
}

void tearDown(void)
{

}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(Test_GPIO_Get_Port);
    RUN_TEST(Test_Is_GPIOPinEnum_Valid);
    RUN_TEST(Test_Is_AF_Valid);
    RUN_TEST(Test_GPIO_Set_Mode);
    RUN_TEST(Test_GPIO_Toggle);
    RUN_TEST(Test_GPIO_Write);
    RUN_TEST(Test_GPIO_Read);

    return UNITY_END();
}