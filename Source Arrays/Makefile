CC = gcc
CFLAGS = -std=c99 -Wall
DEBUG_FLAGS = -DDEBUG_MODE

myprog: main.o util.o array_manipulation.o
	$(CC) $(CFLAGS) -o myprog main.o util.o array_manipulation.o

main.o: main.c util.h array_manipulation.h
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c main.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

array_manipulation.o: array_manipulation.c array_manipulation.h util.h
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c array_manipulation.c

# Clean target
.PHONY: clean
clean:
	rm -f *.o myprog

