/**
* File: handlers.cpp
* Created on: 2025-07-25 at 10:27
* Author: Andrea Rantin
* Description: //TODO
*/

extern "C" void NMI_Handler(void) {
    while(1){
        __builtin_trap(); // To avoid static analyzer error
    }; //TODO
}
