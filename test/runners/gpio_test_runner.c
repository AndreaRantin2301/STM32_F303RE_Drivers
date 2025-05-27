#include "drivers/gpio_driver/gpio_driver_test.h"

GPIO_TypeDef mockGpioList[GPIO_MOCK_N] = {{0}};

void setUp(void)
{
    memset(&mockGpioList, 0, sizeof(mockGpioList));
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
    RUN_TEST(Test_GPIO_Set_Alternate_Function);

    return UNITY_END();
}