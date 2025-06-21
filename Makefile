# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/14 21:23:14 by rmedeiro          #+#    #+#              #
#    Updated: 2025/06/21 13:52:26 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
RM = rm -rf

NAME_BONUS := checker

SRC_MAIN := src/main.c

SRC := src/functions_a.c src/functions_b.c src/organize_data.c \
		src/parse_data.c src/parse_print.c src/quicksort_array.c \
		src/quicksort_list.c src/small_sort.c src/utils_list.c \
		src/utils_print.c src/utils_sorting.c

SRC_BONUS := src/main_bonus.c get_next_line/get_next_line.c \
			src/utils_bonus.c get_next_line/get_next_line_utils.c

OBJ_MAIN := $(SRC_MAIN:.c=.o)

OBJ := $(SRC:.c=.o)

OBJ_BONUS := $(SRC_BONUS:.c=.o)

OBJ := $(SRC:.c=.o)

INC := -I includes

HEADER := includes/push_swap.h

HEADER_BONUS := includes/push_swap_bonus.h



RED := \033[0;30;41m

GREEN := \033[0;30;42m

OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN) $(HEADER)
	$(CC) $(OBJ) $(OBJ_MAIN) -o $(NAME) $(INC)
	@echo "$(GREEN) Push_Swap Compiled $(OFF)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ) $(OBJ_BONUS) $(HEADER) $(HEADER_BONUS)
	$(CC) $(OBJ) $(OBJ_BONUS) -o $(NAME_BONUS) $(INC)
	@echo "$(GREEN) Checker Compiled $(OFF)"

clean:
	$(RM) $(OBJ) $(OBJ_MAIN) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED) Executables Removed $(OFF)"

re: fclean all

.PHONY: all clean fclean re bonus




SRC_M = 

OBJ_M = $(SRC_M:.c=.o)



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


