CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

LIB_FLAGS = -lm -ldl

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS) $(LIB_FLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS) $(LIB_FLAGS)

SOURCE_FILES = main.c \
window/sources/draw.c \
logic/sources/vector.c \
logic/sources/charge.c \
logic/sources/coordinate.c \
logic/sources/linked_list.c \
logic/sources/charge_system.c \
window/sources/window_config.c \
window/sources/function_button.c \
logic/sources/distance_converter.c

O_FILES = main.o \
draw.o \
charge.o \
vector.o \
coordinate.o \
linked_list.o \
charge_system.o \
window_config.o \
function_button.o \
distance_converter.o

HEADER_FILES = constants.h \
enums.h \
window/includes/draw.h \
logic/includes/vector.h \
logic/includes/charge.h \
logic/includes/coordinate.h \
logic/includes/linked_list.h \
logic/includes/charge_system.h \
window/includes/window_config.h \
window/includes/function_button.h \
logic/includes/distance_converter.h

all: $(EXEC)

$(EXEC): $(SOURCE_FILES) $(HEADER_FILES)
	$(CC) -c $(SOURCE_FILES) $(CFLAGS)
	$(CC) -o $(EXEC) $(O_FILES) $(LDFLAGS) && make clean

clean:
	rm -rf *.o

rebuild:
	rm -f $(EXEC)
	make all
	make clean
