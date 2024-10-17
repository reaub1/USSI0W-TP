TARGET = TP1

CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c tools.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

distclean: clean

run: $(TARGET)
	./$(TARGET)

main.o: main.c tools.h
tools.o: tools.c tools.h