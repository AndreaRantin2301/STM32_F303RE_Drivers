set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(ARCH_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=soft")

set(TOOLCHAIN_PREFIX arm-none-eabi)

# Compilers
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-as)

# Toolchain commands
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}-size)

set(CMAKE_C_FLAGS_INIT   "${ARCH_FLAGS} -ffreestanding -nostdlib")
set(CMAKE_ASM_FLAGS_INIT "${ARCH_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-ffreestanding -nostdlib")