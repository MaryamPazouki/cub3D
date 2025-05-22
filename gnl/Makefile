# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:12:18 by zkhojazo          #+#    #+#              #
#    Updated: 2025/02/05 11:34:37 by zkhojazo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
NAME = libgnl.a

SRCS = get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c get_next_line.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: clean fclean re

# gcc *.c $(find ../src -maxdepth 1 -name "*.c" ! -name "main.c") -o output_executable -L ../ft_printf -lftprintf -L ./gnl -lgnl