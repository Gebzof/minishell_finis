# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 01:31:23 by gebz              #+#    #+#              #
#    Updated: 2025/03/27 12:49:35 by mprokosc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
YELLOW1 = \e[93;5m
YELLOW2 = \e[1;93m
BLUE = \e[94;5m
PURPLE = \033[0;35m
PURPLE1 = \033[35;2m
PURPLE2 = \033[35;3m
PURPLE3 = \033[35;4m
PURPLE4 = \033[35;5m
PURPLE5 = \033[35;6m
PURPLE6 = \033[35;7m
PURPLE7 = \e[0;95m
PURPLE8 = \e[1;95m
PURPLE9 = \e[1;105m

CYAN = \033[1;36m
WHITE = \033[1;37m
RESET = \033[0m
RESET1 = \e[0m

NAME = libft.a

SRCS = ft_putendl_fd.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putnbr_fd.c  ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atol.c ft_free_tabtab.c \
	ft_lstlast.c ft_strcmp.c ft_strjoin_free.c get_next_line.c ft_split_guillemet.c ft_print_tab_debug.c ft_iswhitespace.c \
	ft_split_guillemet_utils.c ft_ltoa.c ft_realloc.c

.PHONY = re fclean clean all

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3

CC = cc

all : $(NAME)

%.o: %.c
	@printf "$(GREEN)Compiling minishell : $(WHITE)$< $(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[K"

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@printf "$(GREEN)libft compiled successfully!$(RESET)\n"


clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all
