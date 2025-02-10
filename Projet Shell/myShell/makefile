NAME = my_sh

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror -arch x86_64
CFLAGS = -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage -O0 -fprofile-dir=coverage/
LDFLAGS = -lgcov --coverage


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

coverage:
	mkdir -p coverage

clean-coverage:
	rm -rf coverage coverage_report coverage.info
	
re: fclean all

.PHONY: all clean fclean re