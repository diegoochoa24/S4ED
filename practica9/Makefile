CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =
SOURCES = src/heap.c src/tree.c src/queue.c src/document.c src/print_queue.c src/utils.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = practica8

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean