/**
* File: main.c
* Created on: 2025-07-18 at 16:50
* Author: Andrea Rantin
* Description: //TODO
*/

#include "main.h"

int main(void) {

    while (1) {
       __builtin_trap(); // To avoid static analyzer error
    }

    return 1;
}
