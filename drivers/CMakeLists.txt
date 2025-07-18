add_library(drivers STATIC
    src/empty.c
)

target_include_directories(drivers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/common
)

target_compile_options(drivers PRIVATE
    -Werror -Wpedantic -Wall -Wextra -fanalyzer
)

# Future driver modules
# add_subdirectory(src/driver1)
# add_subdirectory(src/driver2)