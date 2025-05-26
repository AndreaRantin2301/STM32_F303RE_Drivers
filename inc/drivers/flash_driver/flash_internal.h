#ifndef FLASH_INTERNAL_H
#define FLASH_INTERNAL_H

#ifndef FLASH_INTERNAL_USE
#error "flash_internal.h is private flash functionality and can only be included by flash_driver.c"
#endif

#include "ST/stm32f303xe.h"

#ifndef UNIT_TEST
static inline FLASH_TypeDef* Get_Flash(){return FLASH;}
#else
FLASH_TypeDef* Get_Flash();
#endif

#endif