# Makefile

CC=gcc
CFLAGS = ""

OBJ=main.o

LIBS="-lpthread"

all: MT_primes test synching_issue synching_issue_solved synching_issue_improved MT_primes_improved

%.o: %.c
	gcc -c $^

MT_primes_improved: MT_primes_improved.o
	gcc -o $@ $^ $(LIBS) # Libraries should follow sources and objectsMT_primes: MT_primes.o
	
synching_issue_improved: synching_issue_improved.o
	gcc -o $@ $^ $(LIBS) # Libraries should follow sources and objectsMT_primes: MT_primes.o

synching_issue_solved: synching_issue_solved.o
	gcc -o $@ $^ $(LIBS) # Libraries should follow sources and objectsMT_primes: MT_primes.o

synching_issue: synching_issue.o
	gcc -o $@ $^ $(LIBS) # Libraries should follow sources and objectsMT_primes: MT_primes.o

MT_primes: MT_primes.o
	gcc -o $@ $^ $(LIBS) # Libraries should follow sources and objects


test: test.o
	gcc -o $@ $^ $(LIBS) # Libraries should follow sources and objects

clean:
	rm -f *.o test MT_primes synching_issue synching_issue_solved synching_issue_improved MT_primes_improved
