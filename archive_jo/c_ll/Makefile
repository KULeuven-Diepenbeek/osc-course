# Makefile

all: ll_inMain ll_inFunctions ll_inFunctions2 thegrid

CC=gcc
CFLAGS=-g

%.o: %.c
	gcc ${CFLAGS} -c $^

ll_inMain: ll_inMain.o
	${CC} -o ll_inMain ll_inMain.o

ll_inFunctions: ll_inFunctions.o ll_inFunctionsLib.o
	${CC} -o ll_inFunctions ll_inFunctions.o ll_inFunctionsLib.o

ll_inFunctions2: ll_inFunctions2.o ll_inFunctions2Lib.o
	${CC} -o ll_inFunctions2 ll_inFunctions2.o ll_inFunctions2Lib.o

thegrid: thegrid.o ll_inFunctions2Lib.o
	${CC} -o thegrid thegrid.o ll_inFunctions2Lib.o

clean:
	rm -rf *.o ll_inMain ll_inFunctions ll_inFunctions2 thegrid
