#include "drivers/flash_driver/flash_driver_test.h"

FLASH_TypeDef mockFlash;

void setUp(void)
{
    memset(&mockFlash, 0, sizeof(mockFlash));
}

void tearDown(void)
{

}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(Test_Is_Flash_Latency_Valid);
    RUN_TEST(Test_Flash_Set_Latency);

    return UNITY_END();
}