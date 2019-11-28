# Makefile

all: ex1 ex2 MP_primes test4

CC=gcc
#LIBRARIES="-lpthread"
#DEPS="main.h"
DEPS=""

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


test4: main4.o
	${CC} -o test4 main4.o ${LIBRARIES} # Libraries should follow sources and objects


MP_primes: MP_primes.o
	${CC} -o MP_primes MP_primes.o ${LIBRARIES} # Libraries should follow sources and objects


ex2: ex2.o
	${CC} -o ex2 ex2.o ${LIBRARIES} # Libraries should follow sources and objects


ex1: ex1.o
	${CC} -o ex1 ex1.o ${LIBRARIES} # Libraries should follow sources and objects

helloworld: helloworld.o
	${CC} -o $@  $^ ${LIBRARIES} # Libraries should follow sources and objects

clean:
	rm -rf *.o ex1 ex2 MP_primes test4
