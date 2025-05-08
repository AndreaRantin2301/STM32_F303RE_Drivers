# General directories
STARTUP_DIR = ../../../startup
SRC_DIR = ../../../src
INC_DIR = ../../../inc
TEST_DIR = ../../../test
THIRD_PARTY_DIR = ../../../third_party
UNITY_DIR = $(THIRD_PARTY_DIR)/UNITY
OUT_DIR = out
DEBUG_DIR = debug

# Production code directories
DRIVERS_DIR = $(SRC_DIR)/drivers
CLOCK_DRIVER_DIR = $(DRIVERS_DIR)/clock_driver


Compiler = arm-none-eabi-gcc
CFlags = -c -mcpu=cortex-m4 -I$(INC_DIR) -I$(THIRD_PARTY_DIR) -mthumb -std=gnu23 -mfloat-abi=soft -g -O2 \
		 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wpointer-arith -Wcast-qual \
		 -Wcast-align -Wsign-conversion -Wswitch-default -Wswitch-enum \
		 -Wstrict-prototypes -Wmissing-prototypes -Wconversion -Wredundant-decls \
		 -Winline -Wundef -Wbad-function-cast -Wfloat-equal -Wlogical-op \
		 -Waggregate-return -Wformat=2 -Wmissing-include-dirs -Wstrict-overflow=5 \
		 -Wunreachable-code -Wunused -Wuninitialized -Wnull-dereference \
		 -Wduplicated-cond -Wno-unused-parameter -pedantic-errors \
		 -Wvla -Wnonnull -Wmisleading-indentation -Wpointer-arith \
		 -Wcast-align -Wlogical-op -Waggregate-return -Wfloat-equal \
		 -Wpacked -Wno-inline

Core = cortex-m4

LDFlags = -mcpu=$(Core) -mthumb -nostdlib -T $(STARTUP_DIR)/linkerScript.ld -Wl,-Map=$(DEBUG_DIR)/firmware.map

TestCompiler=gcc
TestFlags = -DUNITY_MAIN -DUNIT_TEST -I$(INC_DIR) -I$(THIRD_PARTY_DIR) -I$(TEST_DIR)

FIRMWARE_SRC = $(OUT_DIR)/startup.o $(OUT_DIR)/clock_main.o

$(OUT_DIR):
	mkdir $@

$(DEBUG_DIR):
	mkdir $@

clock_main.o:$(SRC_DIR)/clock_main.c | $(OUT_DIR)
	$(Compiler) $(CFlags) $(SRC_DIR)/clock_main.c -o $(OUT_DIR)/clock_main.o

startup.o:$(STARTUP_DIR)/startup.s | $(OUT_DIR)
	$(Compiler) $(CFlags) $(STARTUP_DIR)/startup.s -o $(OUT_DIR)/startup.o

clock_driver.o:$(CLOCK_DRIVER_DIR)/clock_driver.c | $(OUT_DIR)
	$(Compiler) $(CFlags) -DCLOCK_INTERNAL $(CLOCK_DRIVER_DIR)/clock_driver.c -o $(OUT_DIR)/clock_driver.o

systick_driver.o:$(CLOCK_DRIVER_DIR)/systick_driver.c | $(OUT_DIR)
	$(Compiler) $(CFlags) -DCLOCK_INTERNAL $(CLOCK_DRIVER_DIR)/systick_driver.c -o $(OUT_DIR)/systick_driver.o


$(DEBUG_DIR)/firmware.elf: $(FIRMWARE_SRC) | $(DEBUG_DIR)
	$(Compiler) $(LDFlags) -o $@ $^
	arm-none-eabi-objcopy -O binary $@ $(DEBUG_DIR)/firmware.bin

all: clock_main.o startup.o clock_driver.o systick_driver.o $(DEBUG_DIR)/firmware.elf

driver: clock_driver.o systick_driver.o

run_tests: | $(DEBUG_DIR)
	$(TestCompiler) $(TestFlags) $(TEST_SRC) -o $(DEBUG_DIR)/unit_tests.exe
	$(DEBUG_DIR)/unit_tests.exe

clean:
	rmdir /S /Q $(DOCS_DIR)\html 2>nul || exit 0
	rmdir /S /Q $(DOCS_DIR)\latex 2>nul || exit 0
	rmdir /S /Q $(DEBUG_DIR) 2>nul || exit 0
	rmdir /S /Q $(OUT_DIR) 2>nul || exit 0
	del /Q *.o *.elf *.map 2>nul || exit 0

size:
	arm-none-eabi-size $(DEBUG_DIR)/firmware.elf