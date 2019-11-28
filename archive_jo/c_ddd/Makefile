# Makefile

#LIBRARIES="-lpthread"

all: test

CC=gcc

test: main.o
	${CC} -o test main.o ${LIBRARIES} # Libraries should follow sources and objects

main.o: main.c
	${CC} -g -c main.c

clean:
	rm -rf *.o test
