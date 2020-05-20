CC=gcc
ERROR_CFLAGS = -Wall -W -pedantic
EXEC=projetc.bin

GTK_CFLAGS = $$(pkg-config --cflags gtk+-3.0)
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)

GTK_LDFLAGS = $$(pkg-config --libs gtk+-3.0)
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)

all: $(EXEC)

$(EXEC): main.c
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(LDFLAGS) -o $(EXEC) main.o

clean:
	rm -rf *.o