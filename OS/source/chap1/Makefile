# Makefile

ARDUINO_AVR=/opt/arduino-1.8.8/hardware/tools/avr

CC=$(ARDUINO_AVR)/bin/avr-gcc
COBJDUMP=$(ARDUINO_AVR)/bin/avr-objcopy
AVRDUDE=$(ARDUINO_AVR)/bin/avrdude
RM=rm -f

INCS=
LIBS=

baud=115200
avrType=atmega328p
avrFreq=16000000
avrConfFile=$(ARDUINO_AVR)/etc/avrdude.conf
programmerDev=/dev/ttyACM1
programmerType=arduino


cflags=-DF_CPU=$(avrFreq) -mmcu=$(avrType) -Wall -Wextra -Os
objects=$(patsubst %.c,%.o,$(wildcard *.c))
sources = $(wildcard *.c)



all: main.hex

main.hex: main.elf
	$(COBJDUMP) -j .text -j .data -O ihex $^ $@

main.elf: $(objects)
	$(CC) $(cflags) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(cflags) $(INCS) -c $< -o $@

show:
	echo $(sources)
	echo $(objects)



.PHONY: flash clean

flash: main.hex
	$(AVRDUDE) -p$(avrType) -C$(avrConfFile) -c$(programmerType) -P$(programmerDev) -b$(baud) -v -U flash:w:$<
	gtkterm -p /dev/ttyACM1 -s 9600 -b 8 -t 2

clean:
	$(RM) main.hex main.elf $(objects) $(FOREIGN_TARGETS)
