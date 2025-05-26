STARTUP_DIR = ../startup
SRC_DIR = ../src
INC_DIR = ../inc
TEST_DIR = ../test
THIRD_PARTY_DIR = ../third_party
UNITY_DIR = $(THIRD_PARTY_DIR)/UNITY
OUT_DIR = out
DEBUG_DIR = debug
FIRMWARE_SRC = drivers/clock_driver/$(OUT_DIR)/clock_driver.o drivers/clock_driver/$(OUT_DIR)/systick_driver.o \
				drivers/gpio_driver/$(OUT_DIR)/gpio_driver.o drivers/flash_driver/$(OUT_DIR)/flash_driver.o \
				 $(OUT_DIR)/startup.o $(OUT_DIR)/main.o

DRIVERS_DIR = drivers
GPIO_DRIVER_MAKE_DIR = $(DRIVERS_DIR)/gpio_driver
CLOCK_DRIVER_MAKE_DIR = $(DRIVERS_DIR)/clock_driver
FLASH_DRIVER_MAKE_DIR = $(DRIVERS_DIR)/flash_driver

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

$(OUT_DIR):
	mkdir $@

$(DEBUG_DIR):
	mkdir $@


$(DEBUG_DIR)/firmware.elf: $(FIRMWARE_SRC) | $(DEBUG_DIR)
	$(Compiler) $(LDFlags) -o $@ $^
	arm-none-eabi-objcopy -O binary $@ $(DEBUG_DIR)/firmware.bin

.PHONY: all clean

main.o:$(SRC_DIR)/main.c | $(OUT_DIR)
	$(Compiler) $(CFlags) $(SRC_DIR)/main.c -o $(OUT_DIR)/main.o

startup.o:$(STARTUP_DIR)/startup.s | $(OUT_DIR)
	$(Compiler) $(CFlags) $(STARTUP_DIR)/startup.s -o $(OUT_DIR)/startup.o

gpio_driver: 
	cd $(GPIO_DRIVER_MAKE_DIR) && $(MAKE) driver

clock_driver: 
	cd $(CLOCK_DRIVER_MAKE_DIR) && $(MAKE) driver

flash_driver:
	cd $(FLASH_DRIVER_MAKE_DIR) && $(MAKE) driver

all: startup.o main.o gpio_driver clock_driver flash_driver $(DEBUG_DIR)/firmware.elf

clean:
	cd $(GPIO_DRIVER_MAKE_DIR) && $(MAKE) clean
	cd $(CLOCK_DRIVER_MAKE_DIR) && $(MAKE) clean
	cd $(FLASH_DRIVER_MAKE_DIR) && $(MAKE) clean
	rmdir /S /Q $(DEBUG_DIR) 2>nul || exit 0
	rmdir /S /Q $(OUT_DIR) 2>nul || exit 0
	del /Q *.o *.elf *.map 2>nul || exit 0