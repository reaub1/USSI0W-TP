TARGET = TP3

CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = thread-sample.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

distclean: clean

run: $(TARGET)
	./$(TARGET)