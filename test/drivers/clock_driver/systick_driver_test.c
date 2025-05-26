#include "systick_driver_test.h"

extern SysTick_Type mockSystick;

SysTick_Type* Get_SysTick(){return &mockSystick;}

void Test_SysTick_Init() {
    SysTick_Init();
    TEST_ASSERT_EQUAL_MESSAGE((SYSTEM_CLOCK / 1000) - 1,mockSystick.LOAD, "Test SysTick_Init LOAD error\n");
    TEST_ASSERT_EQUAL_MESSAGE(0,mockSystick.VAL, "Test SysTick_Init VAL error\n");
    TEST_ASSERT_EQUAL_MESSAGE(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk,mockSystick.CTRL,"Test SysTick_Init CTRL error\n");
}