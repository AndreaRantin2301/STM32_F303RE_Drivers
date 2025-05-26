#include "drivers/clock_driver/clock_driver_test.h"

extern RCC_TypeDef mockRcc;
extern bool MOCK_IS_HSI_READY;
extern bool MOCK_IS_PLL_ON;
extern bool MOCK_IS_PLL_READY;
extern bool MOCK_IS_PLL_SELECTED;

RCC_TypeDef* Get_RCC() {return &mockRcc;}


bool IS_HSI_READY(){return MOCK_IS_HSI_READY;}
bool IS_PLL_ON(){return MOCK_IS_PLL_ON;}
bool IS_PLL_READY(){return MOCK_IS_PLL_READY;}
bool IS_PLL_SELECTED(){return MOCK_IS_PLL_SELECTED;}

/**
 * @brief Mock implementation of Flash_Set_Latency from flash_driver.c in flash_driver 
 * feature branch
 * 
 * @param latency 
 * @return FlashStatusCode 
 */
FlashStatusCode Flash_Set_Latency(FlashLatency latency) {
    return FLASH_OK;
}

void Test_System_Clock_Init() {
    //Check HSI READY error
    MOCK_IS_HSI_READY = false;
    MOCK_IS_PLL_ON = true;
    MOCK_IS_PLL_READY = true;
    MOCK_IS_PLL_SELECTED = true;
    ClockStatusCode check = System_Clock_Init();
    TEST_ASSERT_EQUAL_MESSAGE(CLOCK_ERROR_HSI,check,"Test System_Clock_Init error HSI failed\n");

    //Check PLL ON error
    MOCK_IS_HSI_READY = true;
    MOCK_IS_PLL_ON = false;
    MOCK_IS_PLL_READY = true;
    MOCK_IS_PLL_SELECTED = true;
    check = System_Clock_Init();
    TEST_ASSERT_EQUAL_MESSAGE(CLOCK_ERROR_PLL,check,"Test System_Clock_Init error PLL ON failed\n");

    //Check PLL READY error
    MOCK_IS_HSI_READY = true;
    MOCK_IS_PLL_ON = true;
    MOCK_IS_PLL_READY = false;
    MOCK_IS_PLL_SELECTED = true;
    check = System_Clock_Init();
    TEST_ASSERT_EQUAL_MESSAGE(CLOCK_ERROR_PLL,check,"Test System_Clock_Init error PLL READY failed\n");

    //Check CLOCK SOURCE error
    MOCK_IS_HSI_READY = true;
    MOCK_IS_PLL_ON = true;
    MOCK_IS_PLL_READY = true;
    MOCK_IS_PLL_SELECTED = false;
    check = System_Clock_Init();
    TEST_ASSERT_EQUAL_MESSAGE(CLOCK_ERROR_CLOCK_SOURCE,check,"Test System_Clock_Init error CLOCK SOURCE failed\n");

    //Check if registers were set correctly
    MOCK_IS_HSI_READY = true;
    MOCK_IS_PLL_ON = true;
    MOCK_IS_PLL_READY = true;
    MOCK_IS_PLL_SELECTED = true;
    check = System_Clock_Init();

    TEST_ASSERT_EQUAL_MESSAGE(0x01,(mockRcc.CR & RCC_CR_HSION_Msk),"Test System_Clock_Init error HSI ON bit\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR_PLLSRC_HSI_PREDIV,(mockRcc.CFGR & RCC_CFGR_PLLSRC_Msk), "Test System_Clock_Init error HSI PREDIV\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR2_PREDIV_DIV1,(mockRcc.CFGR2 & RCC_CFGR2_PREDIV_Msk), "Test System_Clock_Init error PREDIV value\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR_PLLMUL9, (mockRcc.CFGR & RCC_CFGR_PLLMUL_Msk), "Test System_Clock_Init error PLLMUL value\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CR_PLLON,(mockRcc.CR & RCC_CR_PLLON_Msk), "Test System_Clock_Init error PLL ON\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR_HPRE_DIV1, (mockRcc.CFGR & RCC_CFGR_HPRE_Msk), "Test System_Clock_Init error AHB PRESCALER\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR_PPRE1_DIV2, (mockRcc.CFGR & RCC_CFGR_PPRE1_Msk),"Test System_Clock_Init error APB1 PRESCALER\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR_PPRE2_DIV1, (mockRcc.CFGR & RCC_CFGR_PPRE2_Msk), "Test System_Clock_Init error APB2 PRESCALER\n");
    TEST_ASSERT_EQUAL_MESSAGE(RCC_CFGR_SW_PLL, (mockRcc.CFGR & RCC_CFGR_SW_Msk), "Test System_Clock_Init error CLOCK SOURCE\n");

}