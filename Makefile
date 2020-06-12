CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

LIB_FLAGS = -lm -ldl

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS) $(LIB_FLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS) $(LIB_FLAGS)

# Add \ at the end of the line to put each filename on a newline
SOURCE_FILES = window/sources/window_config.c \
window/sources/function_button.c \
window/sources/draw.c \
logic/sources/coordinate.c \
logic/sources/vector.c \
logic/sources/charge_system.c \
logic/sources/charge.c \
logic/sources/linked_list.c \
main.c

# Add \ at the end of the line to put each filename on a newline
O_FILES = window_config.o \
function_button.o \
draw.o \
coordinate.o \
vector.o \
charge.o \
charge_system.o \
linked_list.o \
main.o

all: $(EXEC)

$(EXEC): $(SOURCE_FILES)
	$(CC) -c $(SOURCE_FILES) $(CFLAGS)
	$(CC) -o $(EXEC) $(O_FILES) $(LDFLAGS) && make clean

clean:
	rm -rf *.o

rebuild:
	rm -f $(EXEC)
	make all
	make clean
