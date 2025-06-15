# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 21:23:14 by rmedeiro          #+#    #+#              #
#    Updated: 2025/06/14 21:44:03 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src

SRC = algorithm/push_swap.c algorithm/stack_positions.c algorithm/stack_utils.c \
      algorithm/movements.c algorithm/find_elements.c algorithm/cost_calculation.c \
      algorithm/cheapest_move.c \
      operations/push.c operations/swap.c operations/rotate.c operations/r_rotate.c \
      parsing/parsing.c parsing/parsing_utils.c \
      utils.c

MAIN = main.c

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
MAIN_OBJ = $(OBJ_DIR)/main.o

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN_OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
