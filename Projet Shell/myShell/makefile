NAME = my_sh

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS=-Wall -Wextra -Werror -arch x86_64

SRCS = main.c execution.c builtin_commands.c command_history.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re