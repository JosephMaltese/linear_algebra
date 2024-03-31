CC = gcc
CFLAGS = -Wall -Wextra -g

all: mathOut

mathOut: math_matrix.o functions.o
	$(CC) $(CFLAGS) -o mathOut math_matrix.o functions.o

math_matrix.o: math_matrix.c functions.h
	$(CC) $(CFLAGS) -c math_matrix.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

debug: mathOut
	gdb mathOut

clean: 
	rm -f mathOut *.o