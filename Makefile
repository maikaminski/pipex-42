# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makamins <makamins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 17:27:56 by makamins          #+#    #+#              #
#    Updated: 2025/02/21 14:32:58 by makamins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror 
SRC =  pipex_utils.c pipex.c
CC = cc
LIBFT = ../libft/libft.a 

OBJS = $(SRC:%.c=%.o)

all: $(NAME)
libft:
	make -C libft
	
$(NAME): $(OBJS) libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	chmod +x $(NAME) 

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re