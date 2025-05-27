#include "gpio_driver_test.h"

extern GPIO_TypeDef mockGpioList[GPIO_MOCK_N];

/**
 * @brief /**
 * @brief Mock implementatio of GPIO_Get_Port from gpio_driver.c
 * This returns various mock instances of type GPIO_TypeDef* 
 * depending on the give portEnum
 * 
 * @param portEnum Enum of the GPIO port
 * @return GPIO_TypeDef* Pointer to the GPIO mock
 */
GPIO_TypeDef* GPIO_Get_Port(GPIOPortEnum portEnum) {

    switch(portEnum) {
        case GPIO_PORT_A:
            return &mockGpioList[GPIOA_MOCK_POS];
        case GPIO_PORT_B:
            return &mockGpioList[GPIOB_MOCK_POS];
        case GPIO_PORT_C:
            return &mockGpioList[GPIOC_MOCK_POS];
        case GPIO_PORT_D:
            return &mockGpioList[GPIOD_MOCK_POS];
        case GPIO_PORT_E:
            return &mockGpioList[GPIOE_MOCK_POS];
        case GPIO_PORT_F:
            return &mockGpioList[GPIOF_MOCK_POS];
        case GPIO_PORT_G:
            return &mockGpioList[GPIOG_MOCK_POS];
        case GPIO_PORT_H:
            return &mockGpioList[GPIOH_MOCK_POS];
        default:
            return NULL;
    }
    return NULL;
}

/**
 * @brief Mock implementation of Is_GPIOPinEnum_Valid from gpio_driver.c
 * In this case the test implementation is the same of the real one
 * 
 * @param pinEnum Enum of the GPIO pin
 * @return true If the given enum is a valid one
 * @return false If the given enum is not a valid one
 */
bool Is_GPIOPinEnum_Valid(int pinEnum) {
    return ((pinEnum >= GPIO_PIN_0) && (pinEnum <= GPIO_PIN_15));
}

/**
 * @brief Mock implementation of Is_AF_Valid from gpio_driver.case
 * In this case the test implementation is the same of the real one
 * 
 * @param portEnum Enum of the GPIO port
 * @param pinEnum Enum of the GPIO pin
 * @param af Enum of the alternate function
 * @return true If the alternate function provided is compatible with the GPIO pin
 * @return false If the alternate function provided is not compatible with the GPIO pin
 */
bool Is_AF_Valid(GPIOPortEnum portEnum, GPIOPinEnum pinEnum, GPIOAlternateFunction af) {
    uint8_t len = (sizeof(AFValidationTable) / sizeof(AFValidationTable[0]));
    for (uint8_t i = 0; i < len; ++i) {
        if (AFValidationTable[i].port == portEnum && AFValidationTable[i].pin == pinEnum) {
            return (AFValidationTable[i].afMask & (1U << af)) != 0;
        }
    }
    return false;
}

void Test_GPIO_Get_Port() {
    //Test invalid port
    GPIO_TypeDef* check = GPIO_Get_Port(-10);
    TEST_ASSERT_EQUAL_MESSAGE(NULL,check,"TEST GPIO_Get_Port error failed\n");

    //Test all ports and check if pointer returned is the correct one
    for(uint8_t i = GPIO_PORT_A; i < GPIO_PORT_H; i++) {
        check = GPIO_Get_Port(i);
        TEST_ASSERT_EQUAL_MESSAGE(&mockGpioList[i],check,"TEST GPIO_Get_Port correct failed\n");
    }
}

void Test_Is_GPIOPinEnum_Valid() {
    //Test invalid pin
    bool check = Is_GPIOPinEnum_Valid(-10);
    TEST_ASSERT_EQUAL_MESSAGE(false,check,"TEST Is_GPIOPinEnum_Valid error failed\n");

    //Test all pins and check for validity
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = Is_GPIOPinEnum_Valid(i);
        TEST_ASSERT_EQUAL_MESSAGE(true,check,"TEST Is_GPIOPinEnum_Valid correct failed\n");
    }
}

void Test_Is_AF_Valid(){
    //Test with wrong port
    bool check = Is_AF_Valid(-10,GPIO_PIN_0,GPIO_AF2);
    TEST_ASSERT_EQUAL_MESSAGE(false,check,"Test Is_AF_Valid wrong port failed\n");

    //Test with wrong pin
    check = Is_AF_Valid(GPIO_PORT_A,-10,GPIO_AF2);
    TEST_ASSERT_EQUAL_MESSAGE(false,check,"Test Is_AF_Valid wrong port failed\n");

    //Test with wrong AF
    check = Is_AF_Valid(GPIO_PORT_A,GPIO_PIN_0,GPIO_AF2);
    TEST_ASSERT_EQUAL_MESSAGE(false,check,"Test Is_AF_Valid wrong AF failed\n");

    //TODO CHECK ALL CORRECT ONES

}

void Test_GPIO_Set_Mode(){

    //Test invalid mode
    GPIOStatusCode check = GPIO_Set_Mode(GPIO_PORT_A,GPIO_PIN_5,35);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_MODE,check,"TEST INVALID MODE FAILED\n");


    //Test invalid pin
    check = GPIO_Set_Mode(GPIO_PORT_A,-10,GPIO_MODE_OUTPUT);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVAID_PIN,check,"TEST INVALID PIN FAILED\n");

    uint32_t bitsToCheck = 0;
    uint8_t i = 0;

    //Test input mode for all pins
    for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_INPUT);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
        bitsToCheck = (mockGpioList[GPIOA_MOCK_POS].MODER >> (i * 2)) & 0x03;
        printf("INPUT MODE PIN %d\n", i);
        TEST_ASSERT_EQUAL_MESSAGE(0b00, bitsToCheck, "INPUT MODE FAILED\n");
    }

    mockGpioList[GPIOA_MOCK_POS].MODER = 0;

    //Test output mode for all pins
    for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
       check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_OUTPUT);
       TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
       bitsToCheck = (mockGpioList[GPIOA_MOCK_POS].MODER >> (i * 2)) & 0x03;
       printf("OUTPUT MODE PIN %d\n", i);
       TEST_ASSERT_EQUAL_MESSAGE(0b01, bitsToCheck, "OUTPUT MODE FAILED\n");
   }

   mockGpioList[GPIOA_MOCK_POS].MODER = 0;

   //Test alternate mode for all pins
   for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_ALTERNATE);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
        bitsToCheck = (mockGpioList[GPIOA_MOCK_POS].MODER >> (i * 2)) & 0x03;
        printf("ALTERNATE MODE PIN %d\n", i);
        TEST_ASSERT_EQUAL_MESSAGE(0b10, bitsToCheck, "ALTERNATE MODE FAILED\n");
    }   

    //Test analog mode for all pins
    for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_ANALOG);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
        bitsToCheck = (mockGpioList[GPIOA_MOCK_POS].MODER >> (i * 2)) & 0x03;
        printf("ANALOG MODE PIN %d\n", i);
        TEST_ASSERT_EQUAL_MESSAGE(0b11, bitsToCheck, "ANALOG MODE FAILED\n");
    }   
}

void Test_GPIO_Set_Alternate_Function(){
    //Test invalid port
    GPIOStatusCode check = GPIO_Set_Alternate_Function(-10,GPIO_PIN_0,GPIO_AF1);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_PORT,check, "INVALID PORT TEST FAILED\n");

    //Test invalid pin
    check = GPIO_Set_Alternate_Function(GPIO_PORT_A,-10,GPIO_AF1);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVAID_PIN,check, "INVALID PIN TEST FAILED\n");

    //Test invalid AF
    check = GPIO_Set_Alternate_Function(GPIO_PORT_A,GPIO_PIN_0,GPIO_AF6);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_AF,check, "INVALID AF TEST FAILED\n");

    //Test all valid AF
    //TODO finish
    check = GPIO_Set_Alternate_Function(GPIO_PORT_A,GPIO_PIN_0,GPIO_AF8);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check, "GPIOA AF8 TEST FAILED\n");

    uint32_t checkAf = mockGpioList[GPIOA_MOCK_POS].AFR[0];

    TEST_ASSERT_EQUAL_MESSAGE(0x08,checkAf,"GPIOA AF8 VALUE TEST FAILED\n");
    
}

void Test_GPIO_Toggle() {
    mockGpioList[GPIOA_MOCK_POS].ODR = 0;

    //Test toggling on all pins
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        printf("TOGGLE PIN %d\n", i);
        GPIOStatusCode check = GPIO_Toggle(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO TOGGLE FAILED\n");

        uint8_t bit = (mockGpioList[GPIOA_MOCK_POS].ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b01,bit,"GPIO TOGGLE VALUE FAILED\n");

        check = GPIO_Toggle(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO TOGGLE FAILED\n");
        bit = (mockGpioList[GPIOA_MOCK_POS].ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b00,bit,"GPIO TOGGLE VALUE FAILED\n");
    }
}

void Test_GPIO_Write() {
    mockGpioList[GPIOA_MOCK_POS].ODR = 0;

    //TEST WRITE ALL PINS
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        printf("WRITE PIN %d\n", i);
        GPIOStatusCode check = GPIO_Write(GPIO_PORT_A,i,GPIO_STATE_SET);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO WRITE FAILED\n");

        uint8_t bit = (mockGpioList[GPIOA_MOCK_POS].ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b01,bit,"GPIO WRITE SET FAILED\n");

        check = GPIO_Write(GPIO_PORT_A,i,GPIO_STATE_RESET);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO WRITE FAILED\n");
        bit = (mockGpioList[GPIOA_MOCK_POS].ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b00,bit,"GPIO WRITE RESET FAILED\n");
    }
}

void Test_GPIO_Read() {
    
    mockGpioList[GPIOA_MOCK_POS].IDR = 0;
    mockGpioList[GPIOA_MOCK_POS].ODR = 0;

    //TEST READ ALL PINS
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        printf("READ PIN %d\n", i);
       
        mockGpioList[GPIOA_MOCK_POS].IDR = (1U << i);
        uint8_t bit = GPIO_Read(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(0b01,bit,"GPIO READ SET FAILED\n");

        mockGpioList[GPIOA_MOCK_POS].IDR = (0U << i);
        bit = GPIO_Read(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(0b00,bit,"GPIO READ RESET FAILED\n");
    }
}

void Test_GPIO_Init() {

    GPIO_Init_Struct testStruct = {0};

    //Test invalid port
    testStruct.portEnum = -10;
    testStruct.pinEnum = GPIO_PIN_5;
    testStruct.mode = GPIO_MODE_OUTPUT;
    testStruct.af = GPIO_AF4;

    GPIOStatusCode check = GPIO_Init(testStruct);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_PORT,check,"Test GPIO_Init invalid port failed\n");

    //Test invalid pin
    testStruct.portEnum = GPIO_PORT_A;
    testStruct.pinEnum = -10;
    testStruct.mode = GPIO_MODE_OUTPUT;
    testStruct.af = GPIO_AF4;

    check = GPIO_Init(testStruct);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVAID_PIN,check,"Test GPIO_Init invalid pin failed\n");

    //Test invalid mode
    testStruct.portEnum = GPIO_PORT_A;
    testStruct.pinEnum = GPIO_PIN_5;
    testStruct.mode = -10;
    testStruct.af = GPIO_AF4;

    check = GPIO_Init(testStruct);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_MODE,check,"Test GPIO_Init invalid mode failed\n");

    //Test invalid af
    testStruct.portEnum = GPIO_PORT_A;
    testStruct.pinEnum = GPIO_PIN_5;
    testStruct.mode = GPIO_MODE_ALTERNATE;
    testStruct.af = -10;

    check = GPIO_Init(testStruct);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_AF,check,"Test GPIO_Init invalid af failed\n");

    //Test invalid af+mode combo
    testStruct.portEnum = GPIO_PORT_A;
    testStruct.pinEnum = GPIO_PIN_5;
    testStruct.mode = GPIO_MODE_OUTPUT;
    testStruct.af = GPIO_AF3;

    check = GPIO_Init(testStruct);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_MODE,check,"Test GPIO_Init invalid af+mode failed\n");

     //Test ok
    testStruct.portEnum = GPIO_PORT_A;
    testStruct.pinEnum = GPIO_PIN_5;
    testStruct.mode = GPIO_MODE_ALTERNATE;
    testStruct.af = GPIO_AF3;

    check = GPIO_Init(testStruct);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"Test GPIO_Init ok failed\n");

    
}