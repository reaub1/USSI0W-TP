NAME = my_sh

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -arch x86_64 -fprofile-arcs -ftest-coverage -O0

LDFLAGS = -lgcov --coverage


SRCS = main.c execution.c builtin_commands.c command_history.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS:%.o=coverage/%.o)
	$(CC) $(CFLAGS) $^ -o $(NAME)

coverage/%.o: %.c | coverage
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf coverage coverage_report coverage.info

fclean: clean
	rm -f $(NAME)

coverage:
	mkdir -p coverage

clean-coverage:
	rm -rf coverage coverage_report coverage.info

re: fclean all

.PHONY: all clean fclean re