NAME = printf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./

SRCS = ft_fprintf.c ft_char.c ft_putchar_fd_printf.c ft_putstr_fd_printf.c \
		ft_putnbr_fd_printf.c ft_str.c ft_strlen.c ft_ptr.c ft_putnbr_unsigned_fd.c \
		ft_hex.c convert_hex.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
