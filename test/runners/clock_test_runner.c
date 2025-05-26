#include "drivers/clock_driver/clock_driver_test.h"
#include "drivers/clock_driver/systick_driver_test.h"

RCC_TypeDef mockRcc;
SysTick_Type mockSystick;
bool MOCK_IS_HSI_READY;
bool MOCK_IS_PLL_ON;
bool MOCK_IS_PLL_READY;
bool MOCK_IS_PLL_SELECTED;

void setUp(void)
{
    MOCK_IS_HSI_READY = false;
    MOCK_IS_PLL_ON = false;
    MOCK_IS_PLL_READY = false;
    MOCK_IS_PLL_SELECTED = false;
    memset(&mockRcc, 0, sizeof(mockRcc));
    memset(&mockSystick, 0, sizeof(mockSystick));
}

void tearDown(void)
{

}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(Test_System_Clock_Init);
    RUN_TEST(Test_SysTick_Init);

    return UNITY_END();
}