CC=gcc
CFLAGS= -Wall -ansi -W

all : main.o
	$(CC) -o main.out main.o

td.o : main.c
	$(CC) -c main.c $(CFLAGS)

clean :
	rm -rf *.o