CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = my_sh

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean