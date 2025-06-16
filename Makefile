# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 21:23:14 by rmedeiro          #+#    #+#              #
#    Updated: 2025/06/16 13:28:13 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M = push_swap

SRC_M = 

OBJ_M = $(SRC_M:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
RM = rm -rf

INCLUDE_M = includes/push_swap.h

all: $(NAME_M)

$(NAME_M): $(OBJ_M)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(INCLUDE_M)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_M) $(OBJ_B)

fclean: clean
	$(RM) $(NAME_M) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus
