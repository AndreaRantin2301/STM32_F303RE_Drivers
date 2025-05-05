#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

/**
 * @brief Enum corresponding to GPIO ports for
 * simplified GPIO functions usage in gpio_driver.c
 * 
 */
typedef enum {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H,
}GPIOPortEnum;


/**
 * @brief Enum corresponding to GPIO pins for
 * simplified GPIO functions usage in gpio_driver.c
 * 
 */
typedef enum {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1 = 1,
    GPIO_PIN_2 = 2,
    GPIO_PIN_3 = 3,
    GPIO_PIN_4 = 4,
    GPIO_PIN_5 = 5,
    GPIO_PIN_6 = 6,
    GPIO_PIN_7 = 7,
    GPIO_PIN_8 = 8,
    GPIO_PIN_9 = 9,
    GPIO_PIN_10 = 10,
    GPIO_PIN_11 = 11,
    GPIO_PIN_12 = 12,
    GPIO_PIN_13 = 13,
    GPIO_PIN_14 = 14,
    GPIO_PIN_15 = 15,
}GPIOPinEnum;

/**
 * @brief Enum representing the assignable modes of a GPIO
 * 
 */
typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG,
}GPIOMode;

#endif