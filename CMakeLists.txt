cmake_minimum_required(VERSION 3.20)
project(STM32_F303RE_Drivers LANGUAGES C ASM)

add_subdirectory(startup)
add_subdirectory(drivers)
add_subdirectory(app)