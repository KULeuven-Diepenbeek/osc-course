# Makefile

ARDUINO_AVR=/opt/arduino-1.8.8/hardware/tools/avr

CC=$(ARDUINO_AVR)/bin/avr-gcc
COBJDUMP=$(ARDUINO_AVR)/bin/avr-objcopy
AVRDUDE=$(ARDUINO_AVR)/bin/avrdude
RM=rm -f

INCS=-Ifreertos/include
LIBS=-Lfreertos

baud=115200
avrType=atmega328p
avrFreq=16000000
avrConfFile=$(ARDUINO_AVR)/etc/avrdude.conf
programmerDev=/dev/ttyACM1
programmerType=arduino


cflags=-DF_CPU=$(avrFreq) -mmcu=$(avrType) -Wall -Wextra -Os
objects=$(patsubst %.c,%.o,$(wildcard *.c))


# list of foreign targets
FOREIGN_TARGETS=freertos/libfreertos.a

all: main.hex


main.hex: main.elf
	$(COBJDUMP) -j .text -j .data -O ihex $^ $@

main.elf: $(objects) $(FOREIGN_TARGETS)
	$(CC) $(cflags) -o $@ $^ $(LIBS) -lfreertos

%.o: %.c
	$(CC) $(cflags) $(INCS) -c $< -o $@

$(FOREIGN_TARGETS):
	make -C $(dir $@) $(notdir $@)



.PHONY: flash clean $(FOREIGN_TARGETS)

flash: main.hex
	$(AVRDUDE) -p$(avrType) -C$(avrConfFile) -c$(programmerType) -P$(programmerDev) -b$(baud) -v -U flash:w:$<

clean:
	$(RM) main.hex main.elf $(objects) $(FOREIGN_TARGETS)
