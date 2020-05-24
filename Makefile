CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

LIB_FLAGS = -lm -ldl

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS) $(LIB_FLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS) $(LIB_FLAGS)

# Add \ at the end of the line to put each filename on a newline
SOURCE_FILES = logic/sources/coordinate.c \
logic/sources/range.c \
logic/sources/charge_system.c \
logic/sources/fixed_charge.c \
main.c

# Add \ at the end of the line to put each filename on a newline
O_FILES = coordinate.o \
range.o \
fixed_charge.o \
charge_system.o \
main.o
all: $(EXEC)

$(EXEC): main.c
	$(CC) -c $(SOURCE_FILES) $(CFLAGS)
	$(CC) -o $(EXEC) $(O_FILES) $(LDFLAGS)

clean:
	rm -rf *.o