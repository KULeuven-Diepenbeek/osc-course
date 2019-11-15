# Makefile
#

CC=/usr/bin/gcc
CFLAGS=-Wall

INCS=
LIBS=

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
BINS=$(patsubst %.c,%.bin,$(SRCS))

# .SECONDARY with no prerequisites causes all targets 
# to be treated as secondary (i.e., no target is removed 
# because it is considered intermediate).
.SECONDARY:

all: $(BINS)


#  $@ evaluates to all
#  $< evaluates to the first prerequisite
#  $^ evaluates to all prerequisites
%.o : %.c
	$(CC) $(INCS) -c $< $(CFLAGS) -o $@

%.bin : %.o
	$(CC) -o $@ $^ $(LIBS)

.PHONY: all clean
clean: 
	rm -Rf *.o $(BINS)