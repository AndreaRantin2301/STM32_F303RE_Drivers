#include "flash_driver_test.h"

extern FLASH_TypeDef mockFlash;

/**
 * @brief Mock implementation of Get_Flash from flash_driver.c
 * 
 * @return FLASH_TypeDef* pointer to the mock instance
 */
FLASH_TypeDef* Get_Flash() {
    return &mockFlash;
}

/**
 * @brief Mock implementation of Is_Flash_Latency_Valid from Is_Flash_Latency_Valid
 * In this case the implementation is the same as the real one
 * 
 * @param latency Value of @ref FlashLatency
 * @return true If the latency value is within the valid range of the enum
 * @return false If the latency value is invalid
 */
bool Is_Flash_Latency_Valid(int latency) {
     return ((latency >= FLASH_LATENCY_ZERO_WAIT) && (latency <= FLASH_LATENCY_TWO_WAIT));
}

void Test_Is_Flash_Latency_Valid() {
    //Check invalid latency
    bool check = Is_Flash_Latency_Valid(-10);
    TEST_ASSERT_EQUAL_MESSAGE(false,check,"Test Is_Flash_Latency_Valid error failed\n");

    //Check all valid latencies
    for(uint8_t i = FLASH_LATENCY_ZERO_WAIT; i < FLASH_LATENCY_TWO_WAIT; i++) {
        check = Is_Flash_Latency_Valid(i);
        TEST_ASSERT_EQUAL_MESSAGE(true,check,"Test Is_Flash_Latency_Valid failed\n");
    }
}

void Test_Flash_Set_Latency() {
    FlashStatusCode check = Flash_Set_Latency(-10);
    TEST_ASSERT_EQUAL_MESSAGE(FLASH_INVALID_LATENCY,check,"Test Flash_Set_Latency error failed\n");

    check = Flash_Set_Latency(FLASH_LATENCY_ZERO_WAIT);
    TEST_ASSERT_EQUAL_MESSAGE(FLASH_OK,check,"Test Flash_Set_Latency zero wait OK failed");
    uint8_t bits = (mockFlash.ACR & FLASH_ACR_LATENCY_Msk);
    TEST_ASSERT_EQUAL_MESSAGE(0b000,bits,"Test Flash_Set_Latency zero wait failed\n");

    check = Flash_Set_Latency(FLASH_LATENCY_ONE_WAIT);
    TEST_ASSERT_EQUAL_MESSAGE(FLASH_OK,check,"Test Flash_Set_Latency one wait OK failed");
    bits = (mockFlash.ACR & FLASH_ACR_LATENCY_Msk);
    TEST_ASSERT_EQUAL_MESSAGE(0b001,bits,"Test Flash_Set_Latency one wait failed\n");

    check = Flash_Set_Latency(FLASH_LATENCY_TWO_WAIT);
    TEST_ASSERT_EQUAL_MESSAGE(FLASH_OK,check,"Test Flash_Set_Latency two wait OK failed");
    bits = (mockFlash.ACR & FLASH_ACR_LATENCY_Msk);
    TEST_ASSERT_EQUAL_MESSAGE(0b010,bits,"Test Flash_Set_Latency two wait failed\n");
}
