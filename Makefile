# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2019/10/14 17:42:42 by mphobos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = main.c flags_file.c create_new_t_file.c add_file.c
CC = gcc
INCLUDE = includes
CFLAGS = -Wall -Wextra -Werror -L libft -lft -I $(INCLUDE) -o $(NAME)
DFLAGS = $(CFLAGS) -g

%.c:
	$(CC) $(DFLAGS) $(SRC) -c $<

$(NAME): $(SRC)
	make -C libft
	$(CC) $(DFLAGS) $(SRC)

all: $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full ./ft_ls

.PHONY: all clean fclean re
