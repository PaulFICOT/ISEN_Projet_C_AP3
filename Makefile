CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

LIB_FLAGS = -lm -ldl

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS) $(LIB_FLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS) $(LIB_FLAGS)

# Add \ at the end of the line to put each filename on a newline
SOURCE_FILES = main.c \
window/sources/draw.c \
logic/sources/vector.c \
logic/sources/charge.c \
logic/sources/coordinate.c \
logic/sources/linked_list.c \
logic/sources/charge_system.c \
window/sources/window_config.c \
window/sources/function_button.c

# Add \ at the end of the line to put each filename on a newline
O_FILES = main.o \
draw.o \
charge.o \
vector.o \
coordinate.o \
linked_list.o \
charge_system.o \
window_config.o \
function_button.o

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
