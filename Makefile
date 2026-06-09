CC       = cc
CFLAGS   = -Wall -Wextra -Werror -Iinclude
NAME     = libc_demo

SRCS     = main.c \
           src/sc_type.c \
           src/sc_math.c \
           src/sc_mem.c \
           src/sc_str.c \
           src/sc_str2.c \
           src/sc_calloc.c \
           src/sc_put.c \
           src/sc_lst.c

OBJS     = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c include/libc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run
