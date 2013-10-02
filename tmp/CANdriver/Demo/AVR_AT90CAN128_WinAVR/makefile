###############################################################################
# Makefile for the project FreeRTOS_CAN
###############################################################################

## General Flags
PROJECT = FreeRTOS_CAN
MCU = at90can128
TARGET = FreeRTOS_CAN.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DGCC_MEGA_AVR  -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 
CFLags += -DconfigCPU_CLOCK_HZ=8000000l

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=FreeRTOS_CAN.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"." -I"../AVR_ATMega_Lib" -I"../../Source/include" 

## Objects that must be built in order to link
OBJECTS = can.o frtos_can.o main_with_RTOS.o tasks.o list.o queue.o heap_1.o port.o timer.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) FreeRTOS_CAN.hex FreeRTOS_CAN.eep FreeRTOS_CAN.lss size

## Compile
can.o: can.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

frtos_can.o: frtos_can.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main_with_RTOS.o: main_with_RTOS.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

tasks.o: ../../Source/tasks.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

list.o: ../../Source/list.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

queue.o: ../../Source/queue.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

heap_1.o: ../../Source/portable/MemMang/heap_1.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port.o: ../../Source/portable/GCC/ATMega/port.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../../Source/portable/GCC/AT90CAN128/timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) FreeRTOS_CAN.elf dep/* FreeRTOS_CAN.hex FreeRTOS_CAN.eep FreeRTOS_CAN.lss FreeRTOS_CAN.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

