#include "gpio_driver_test.h"

extern GPIO_TypeDef mockGpio;


GPIO_TypeDef* GPIO_Get_Port(GPIOPortEnum portEnum) {

    switch(portEnum) {
        case GPIO_PORT_A:
            return &mockGpio;
        case GPIO_PORT_B:
            return &mockGpio;
        case GPIO_PORT_C:
            return &mockGpio;
        case GPIO_PORT_D:
            return &mockGpio;
        case GPIO_PORT_E:
            return &mockGpio;
        case GPIO_PORT_F:
            return &mockGpio;
        case GPIO_PORT_G:
            return &mockGpio;
        case GPIO_PORT_H:
            return &mockGpio;
        default:
            return NULL;
    }
    return NULL;
}

bool Is_GPIOPinEnum_Valid(int pinEnum) {
    return ((pinEnum >= GPIO_PIN_0) && (pinEnum <= GPIO_PIN_15));
}

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
    GPIO_TypeDef* check = GPIO_Get_Port(-10);
    TEST_ASSERT_EQUAL_MESSAGE(NULL,check,"TEST GPIO_Get_Port error failed\n");

    for(uint8_t i = GPIO_PORT_A; i < GPIO_PORT_H; i++) {
        check = GPIO_Get_Port(i);
        TEST_ASSERT_EQUAL_MESSAGE(&mockGpio,check,"TEST GPIO_Get_Port correct failed\n");
    }
}

void Test_Is_GPIOPinEnum_Valid() {
    bool check = Is_GPIOPinEnum_Valid(-10);
    TEST_ASSERT_EQUAL_MESSAGE(false,check,"TEST Is_GPIOPinEnum_Valid error failed\n");

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

    //CHECK FOR INVALID MODE
    GPIOStatusCode check = GPIO_Set_Mode(GPIO_PORT_A,GPIO_PIN_5,35);
    TEST_ASSERT_EQUAL_MESSAGE(GPIO_INVALID_MODE,check,"TEST INVALID MODE FAILED\n");

    uint32_t bitsToCheck = 0;
    uint8_t i = 0;

    //TEST INPUT MODE FOR ALL PINTS
    for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_INPUT);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
        bitsToCheck = (mockGpio.MODER >> (i * 2)) & 0x03;
        printf("INPUT MODE PIN %d\n", i);
        TEST_ASSERT_EQUAL_MESSAGE(0b00, bitsToCheck, "INPUT MODE FAILED\n");
    }

    mockGpio.MODER = 0;

    //TEST OUTPUT MODE FOR ALL PINTS
    for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
       check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_OUTPUT);
       TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
       bitsToCheck = (mockGpio.MODER >> (i * 2)) & 0x03;
       printf("OUTPUT MODE PIN %d\n", i);
       TEST_ASSERT_EQUAL_MESSAGE(0b01, bitsToCheck, "OUTPUT MODE FAILED\n");
   }

   mockGpio.MODER = 0;

   //TEST ALTERNATE MODE FOR ALL PINTS
   for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_ALTERNATE);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
        bitsToCheck = (mockGpio.MODER >> (i * 2)) & 0x03;
        printf("ALTERNATE MODE PIN %d\n", i);
        TEST_ASSERT_EQUAL_MESSAGE(0b10, bitsToCheck, "ALTERNATE MODE FAILED\n");
    }   

    //ANALOG
    for(i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        check = GPIO_Set_Mode(GPIO_PORT_A,i,GPIO_MODE_ANALOG);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"SET MODE FAILED\n");
        bitsToCheck = (mockGpio.MODER >> (i * 2)) & 0x03;
        printf("ANALOG MODE PIN %d\n", i);
        TEST_ASSERT_EQUAL_MESSAGE(0b11, bitsToCheck, "ANALOG MODE FAILED\n");
    }   
}

void Test_GPIO_Set_Alternate_Function(){
    //TODO
}

void Test_GPIO_Toggle() {
    mockGpio.ODR = 0;

    //TEST TOGGLE ON ALL PINS
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        printf("TOGGLE PIN %d\n", i);
        GPIOStatusCode check = GPIO_Toggle(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO TOGGLE FAILED\n");

        uint8_t bit = (mockGpio.ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b01,bit,"GPIO TOGGLE VALUE FAILED\n");

        check = GPIO_Toggle(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO TOGGLE FAILED\n");
        bit = (mockGpio.ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b00,bit,"GPIO TOGGLE VALUE FAILED\n");
    }
}

void Test_GPIO_Write() {
    mockGpio.ODR = 0;

    //TEST WRITE ALL PINS
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        printf("WRITE PIN %d\n", i);
        GPIOStatusCode check = GPIO_Write(GPIO_PORT_A,i,GPIO_STATE_SET);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO WRITE FAILED\n");

        uint8_t bit = (mockGpio.ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b01,bit,"GPIO WRITE SET FAILED\n");

        check = GPIO_Write(GPIO_PORT_A,i,GPIO_STATE_RESET);
        TEST_ASSERT_EQUAL_MESSAGE(GPIO_OK,check,"GPIO WRITE FAILED\n");
        bit = (mockGpio.ODR >> i) & 0x01;
        TEST_ASSERT_EQUAL_MESSAGE(0b00,bit,"GPIO WRITE RESET FAILED\n");
    }
}

void Test_GPIO_Read() {
    
    mockGpio.IDR = 0;
    mockGpio.ODR = 0;

    //TEST READ ALL PINS
    for(uint8_t i = GPIO_PIN_0; i < GPIO_PIN_15; i++) {
        printf("READ PIN %d\n", i);
       
        mockGpio.IDR = (1U << i);
        uint8_t bit = GPIO_Read(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(0b01,bit,"GPIO READ SET FAILED\n");

        mockGpio.IDR = (0U << i);
        bit = GPIO_Read(GPIO_PORT_A,i);
        TEST_ASSERT_EQUAL_MESSAGE(0b00,bit,"GPIO READ RESET FAILED\n");
    }
}