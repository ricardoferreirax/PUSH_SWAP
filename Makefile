# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 21:23:14 by rmedeiro          #+#    #+#              #
#    Updated: 2025/06/21 16:41:04 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M = push_swap
SRC_M = src/operations/push.c \
	src/operations/swap.c \
	src/operations/rotate.c \
	src/operations/reverse_rotate.c \
	src/parsing/fill_stack.c \
	src/parsing/parsing_args.c \
	src/parsing/parsing_stack.c \
	src/parsing/parsing_utils.c \
	src/parsing/index_stack.c \
	src/sorting/best_move.c \
	src/sorting/sort.c \
	src/sorting/cost.c \
	src/sorting/position.c \
	src/utils/free_stack.c \
	src/utils/libft_utils1.c \
	src/utils/libft_utils2.c \
	src/utils/lists.c \
	src/utils/split.c \
	src/push_swap.c
	
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
	$(RM) $(OBJ_M)

fclean: clean
	$(RM) $(NAME_M)

re: fclean all

.PHONY: all clean fclean re