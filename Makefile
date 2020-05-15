CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
EXEC= projetc

all: $(EXEC)

$(EXEC): main.o 
    $(CC) -o $(EXEC) main.o

main.o: main.c 
    $(CC) -o main.o -c main.c $(CFLAGS)

clean:
    rm -rf *.o