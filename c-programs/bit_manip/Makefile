CC = gcc
CFLAGS = -Wall -Werror -g
DFLAGS = -DDEBUG
TARGET = mypgm
OBJS = main.o
FILE = main.c

all: $(TARGET)

.phony: clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(FILE)
	$(CC) $(CFLAGS) $(DFLAGS) -c $(FILE)

clean:
	rm -rf $(TARGET) $(OBJS)

debug:
	valgrind --leak-check=full $(shell pwd)/$(TARGET)

run:
	$(shell pwd)/$(TARGET)

gdb:
	gdbgui $(shell pwd)/$(TARGET)
