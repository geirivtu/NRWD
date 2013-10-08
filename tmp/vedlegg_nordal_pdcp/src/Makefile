ifeq ($(CC),cc)
	CC=avr-gcc
endif
ifndef OBJCOPY
	OBJCOPY=avr-objcopy
endif
ifndef ARCH
	ARCH=-mmcu=at90usb1287
endif
CFLAGS:=-Os $(ARCH) -Wall -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums $(CFLAGS)
LDFLAGS:=-s $(ARCH) $(LDFLAGS)

COMMONSRC:=$(shell grep -L CONFIG_BUS_MODE *.c) #files NOT containing CONFIG_BUS_MODE
DIFFERSRC:=$(shell grep -l CONFIG_BUS_MODE *.c) #files containing CONFIG_BUS_MODE

COMOBJ:=$(patsubst %.c, ../build/COM%.o, $(COMMONSRC))
ARBOBJ:=$(patsubst %.c, ../build/ARB%.o, $(filter-out hll_device.c,     $(DIFFERSRC)))
DEVOBJ:=$(patsubst %.c, ../build/DEV%.o, $(filter-out hll_arbitrator.c, $(DIFFERSRC)))

hex: ../build/ ../build/arb.hex ../build/dev.hex
elf: ../build/ ../build/arb.elf ../build/dev.elf
clean:
	rm -rf ../build/
install-erase:
	dfu-programmer at90usb1287 erase
install-arb: install-erase
	dfu-programmer at90usb1287 flash ../build/arb.hex
install-dev: install-erase
	dfu-programmer at90usb1287 flash ../build/dev.hex

.PHONY: hex elf clean install-erase install-arb install-dev

%.hex : %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@
../build/arb.elf: $(COMOBJ) $(ARBOBJ)
	$(CC) $(LDFLAGS) $(COMOBJ) $(ARBOBJ) -o $@
../build/dev.elf: $(COMOBJ) $(DEVOBJ)
	$(CC) $(LDFLAGS) $(COMOBJ) $(DEVOBJ) -o $@
../build/COM%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
../build/ARB%.o : %.c
	$(CC) -c $(CFLAGS) -DCONFIG_BUS_MODE=1 $< -o $@
../build/DEV%.o : %.c
	$(CC) -c $(CFLAGS) -DCONFIG_BUS_MODE=0 $< -o $@
%/:
	mkdir -p $@
