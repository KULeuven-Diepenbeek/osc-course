# Makefile

CC=gcc
CFLAGS = ""

OBJ=main.o main2.o

LIBS="-lpthread"

all: philosophers philosophers2

%.o: %.c
	gcc -c $^

philosophers2: main2.o
	gcc -o $@ $^ $(LIBS) # Libraries should "follow" sources and objects

philosophers: main.o
	gcc -o $@ $^ $(LIBS) # Libraries should "follow" sources and objects

clean:
	rm -f *.o philosophers philosophers2
