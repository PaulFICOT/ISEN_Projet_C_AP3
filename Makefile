CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

LIB_FLAGS = -lm -ldl

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS) $(LIB_FLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS) $(LIB_FLAGS)

all: $(EXEC)

$(EXEC): main.o

main.o: charge_system.o
	$(CC) -c main.c $(CFLAGS)
	$(CC) -o $(EXEC) charge_system.o main.o $(LDFLAGS)

charge_system.o: range.o vector.o charge.o
	$(CC) -c charge.o range.o vector.o logic/sources/charge_system.c $(LDFLAGS)

range.o:
	$(CC) -c logic/sources/range.c $(LDFLAGS)

vector.o: coordinate.o
	$(CC) -c coordinate.o logic/sources/vector.c $(LDFLAGS)

charge.o: coordinate.o
	$(CC) -c coordinate.o logic/sources/charge.c $(LDFLAGS)

coordinate.o:
	$(CC) -c logic/sources/coordinate.c $(LDFLAGS)

clean:
	rm -rf *.o

rebuild:
	rm -f $(EXEC)
	make all
	make clean
