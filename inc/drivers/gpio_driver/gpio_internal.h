#ifndef GPIO_INTERNAL_H
#define GPIO_INTERNAL_H

#include "common/gpio_types.h"
#include <stdint.h>

/**
 * @brief Validation structure used to check if the given GPIO port and PIN,
 * togheter with the AF function are compatible in @ref GPIO_Set_Alternate_Function
 * 
 */
typedef struct {
    GPIOPortEnum port;
    GPIOPinEnum pin;
    uint16_t afMask;
}GPIOAFValidationEntry;

//TODO OTHER PORTS
/**
 * @brief Validation table for GPIO Alternate Function
 * 
 */
static const GPIOAFValidationEntry AFValidationTable[] = {
    {GPIO_PORT_A,GPIO_PIN_0, (0x01U << 1) | (0x01U << 3) | (0x01U << 7) | (0x01U << 8) | (0x01U << 9) | (0x01U << 10) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_1, (0x01U << 0) | (0x01U << 1) | (0x01U << 3) | (0x01U << 7) | (0x01U << 9) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_2, (0x01U << 1) | (0x01U << 3) | (0x01U << 7) | (0x01U << 8) | (0x01U << 9) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_3, (0x01U << 1) | (0x01U << 3) | (0x01U << 7) | (0x01U << 9) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_4, (0x01U << 2) | (0x01U << 3) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_5, (0x01U << 1) | (0x01U << 3) | (0x01U << 5) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_6, (0x01U << 1) | (0x01U << 2) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 8) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_7, (0x01U << 1) | (0x01U << 2) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_8, (0x01U << 0) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 8) | (0x01U << 10) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_9, (0x01U << 2) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 8) | (0x01U << 9) | (0x01U << 10) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_10,(0x01U << 1) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 8) | (0x01U << 10) | (0x01U << 11) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_11,(0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 8) | (0x01U << 8) | (0x01U << 9) | (0x01U << 10) | (0x01U << 11) | (0x01U << 12) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_12,(0x01U << 1) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 8) | (0x01U << 9) | (0x01U << 10) | (0x01U << 11) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_13,(0x01U << 0) | (0x01U << 1) | (0x01U << 3) | (0x01U << 5) | (0x01U << 7) | (0x01U << 11) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_14,(0x01U << 0) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 15)},
    {GPIO_PORT_A,GPIO_PIN_15,(0x01U << 0) | (0x01U << 1) | (0x01U << 2) | (0x01U << 3) | (0x01U << 4) | (0x01U << 5) | (0x01U << 6) | (0x01U << 7) | (0x01U << 9) | (0x01U << 15)},
};

#endif