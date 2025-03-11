# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makamins <makamins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 17:27:56 by makamins          #+#    #+#              #
#    Updated: 2025/03/11 16:20:02 by makamins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror 
SRC = pipex.c pipex_utils.c
CC = cc
LIBFT = libft-pipex/libft.a 

OBJS = $(SRC:%.c=%.o)

all: $(NAME)
libft:
	@make -C libft-pipex
	
$(NAME): $(OBJS) libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	chmod +x $(NAME) 

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