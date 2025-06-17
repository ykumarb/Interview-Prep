CC = gcc
CFLAGS = -Wall -Werror -g
#CFLAGS += -fsanitize=address
DFLAGS = -DMALLOC_STORE_SIZE_IN_RAW=1
TARGET = mypgm
OBJ = sll_remove_dup_sort_ll.o
FILE = sll_remove_dup_sort_ll.c

all:	$(TARGET)

.phony: clean

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET) $(OBJ)

$(OBJ):	$(FILE)
	$(CC) $(CFLAGS) $(DFLAGS) -c $(FILE)

clean:
	rm -f $(TARGET) $(OBJ)

run:
	$(shell pwd)/$(TARGET)

debug:
	valgrind --leak-check=full $(shell pwd)/$(TARGET)

gdb:
	gdbgui $(shell pwd)/$(TARGET)
