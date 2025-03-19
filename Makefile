# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makamins <makamins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 17:27:56 by makamins          #+#    #+#              #
#    Updated: 2025/03/19 12:54:04 by makamins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror 
SRC = pipex.c pipex_utils.c pipex_paths.c
CC = cc
LIBFT = libft-pipex/libft.a
VALGRIND_FLAGS = --leak-check=full --error-exitcode=1

OBJS = $(SRC:%.c=%.o)

all: $(NAME)
libft:
	@make -C libft-pipex
	
$(NAME): $(OBJS) libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	chmod +x $(NAME)

valgrind: $(NAME)
	valgrind $(VALGRIND_FLAGS) ./pipex infile "ls -l" "wc -l" outfile

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make clean -C libft-pipex

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft-pipex

re: fclean all

.PHONY: all clean fclean re


