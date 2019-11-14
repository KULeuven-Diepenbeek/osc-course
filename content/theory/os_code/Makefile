CC = /usr/bin/gcc
LIBS  = 
CFLAGS = -Wall

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
BIN=$(SRC:.c=)

all: $(BIN)

$(OBJ): $(SRC)
	$(CC) -c $^ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean: 
	rm -Rf *.o $(BIN)