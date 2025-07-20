/**
* @file main.cpp
* @date 2025-07-20 20:50:56
* @author Andrea Rantin
* @description //TODO DOCS
*/

#include "main.hpp"

int main(void) {
  
    while (1) {
       __builtin_trap(); // To avoid static analyzer error
    }

    return 1;
}

