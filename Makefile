CC=gcc
ERROR_FLAGS = -Wall -W -pedantic
EXEC=projetc.bin

GTK_CFLAGS = `pkg-config --cflags gtk+-3.0`
CFLAGS = $(ERROR_FLAGS) $(GTK_CFLAGS)

GTK_LDFLAGS = `pkg-config --libs gtk+-3.0`
LDFLAGS = $(ERROR_FLAGS) $(GTK_LDFLAGS)

SOURCE_FILES = window/sources/config.c \
window/sources/button.c \
window/sources/draw.c \
main.c

O_FILES = config.o \
button.o \
draw.o \
main.o

all: $(EXEC)

$(EXEC): $(SOURCE_FILES)
	$(CC) -c $(SOURCE_FILES) $(CFLAGS)
	$(CC) -o $(EXEC) $(O_FILES) $(LDFLAGS) && make clean

clean:
	rm -rf *.o

rebuild:
	rm -rf *.o $(EXEC)
	make all