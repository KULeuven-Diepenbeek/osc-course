# Makefile
ARDUINO_AVR=/opt/arduino-1.8.8/hardware/tools/avr

AR=$(ARDUINO_AVR)/bin/avr-ar
CC=$(ARDUINO_AVR)/bin/avr-gcc

RM=rm -f

INCS=-Iinclude
LIBS=-L.

avrType=atmega328p

CFLAGS=-DF_CPU=$(avrFreq) -mmcu=$(avrType) -Wall -Wextra -Os


SOURCES=$(shell find . -type f -iname '*.c')
OBJECTS=$(foreach x, $(basename $(SOURCES)), $(x).o)

.PHONY: clean

all: libfreertos.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

libfreertos.a: $(OBJECTS)
	$(AR) rs $@ $^

clean:
	$(RM) libfreertos.a $(OBJECTS)
