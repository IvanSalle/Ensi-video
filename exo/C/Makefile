CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = 

TARGET = hello10

all: $(TARGET)

$(TARGET): hello10.o
	$(CC) hello10.o -o $(TARGET) $(LDFLAGS)

hello10.o: hello10.c
	$(CC) $(CFLAGS) -c hello10.c -o hello10.o

clean:
	rm -f hello10.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run