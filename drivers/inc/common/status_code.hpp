/**
* File: status_code.hpp
* Created on: 2025-07-21 at 13:30
* Author: Andrea Rantin
* Description: This file contains the definition
* For the DriverStatusCode type which is an enum
* class returned by most drivers operations.
*/

#pragma once

/**
* @brief Status code for every driver operation.
* Any value other than  0 should be considered as an error
*/
enum class DriverStatusCode{
    OK = 0,
    ERROR_CLOCK_READY,
    ERROR_CLOCK_SELECTED,
    ERROR_GPIO_AF,
};

