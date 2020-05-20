CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin
 
GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)
 
GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)
 
all: $(EXEC)
 
$(EXEC): main.c
	$(CC) -c main.c $(CFLAGS)
	$(CC) -o $(EXEC) main.o $(LDFLAGS)
 
clean:
	rm -rf *.o