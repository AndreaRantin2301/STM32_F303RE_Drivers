add_executable(firmware
    src/main.cpp
)

set_target_properties(firmware PROPERTIES
    SUFFIX ".elf"
)

target_include_directories(firmware PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(firmware PRIVATE
    startup
    drivers
)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/startup/linkerScript.ld")

target_link_options(firmware PRIVATE 
   -Wl,-T${LINKER_SCRIPT} -mthumb
)

# Compile options for example firmware
target_compile_options(firmware PRIVATE
    -Werror -Wpedantic -Wall -Wextra -fanalyzer
    -g -ffreestanding -nostdlib -fno-rtti -fno-exceptions
)
    
# Binary file generation
add_custom_command(TARGET firmware POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:firmware> ${CMAKE_CURRENT_BINARY_DIR}/firmware.bin
    COMMENT "Generating firmware binary"
)