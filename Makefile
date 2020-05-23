CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)

# Add \ at the end of the line to put each filename on a newline
SOURCE_FILES = main.c 

# Add \ at the end of the line to put each filename on a newline
O_FILES = main.o

all: $(EXEC)

$(EXEC): main.c
	$(CC) -c $(SOURCE_FILES) $(CFLAGS)
	$(CC) -o $(EXEC) $(O_FILES) $(LDFLAGS) && make clean

clean:
	rm -rf *.o