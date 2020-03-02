# Makefile

CC=gcc
CFLAGS = ""

OBJ=main.o main2.o

LIBS="-lpthread"

all: philosophers.bin philosophers2.bin

%.o: %.c
	gcc -c $^

philosophers2.bin: main2.o
	gcc -o $@ $^ $(LIBS) # Libraries should "follow" sources and objects

philosophers.bin: main.o
	gcc -o $@ $^ $(LIBS) # Libraries should "follow" sources and objects

clean:
	rm -f *.o philosophers.bin philosophers2.bin
