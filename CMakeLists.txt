cmake_minimum_required(VERSION 3.20)
project(STM32_F303RE_Drivers LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(startup)
add_subdirectory(drivers)
add_subdirectory(app)