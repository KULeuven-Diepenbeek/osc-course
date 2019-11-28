# Makefile

all: aroundTheWorld

CC=gcc
CFLAGS = -g

OBJ=main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

aroundTheWorld: $(OBJ)
	$(CC) -o $@ $^


clean:
	rm aroundTheWorld *.o
