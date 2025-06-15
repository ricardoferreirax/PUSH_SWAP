/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 22:00:57 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "../ft_printf/ft_printf.h"

typedef struct stack
{
	int				*content;
	struct stack	*next;
}	t_stack;

t_stack 	*new_element(int *content);
t_stack		*new_entry(int value, t_stack *stack);
t_stack		*remove_first(t_stack *stack);
int 		push_until_three_left(t_stack **stack_b, t_stack **stack_a);
int			is_sorted(t_stack *stack);
void		sort_three_elements(t_stack **stack);
void		final_rotate(t_stack **stack);
void		push_swap(t_stack **stack_a, t_stack **stack_b);
void		rrr_and_push_a(int value, t_stack **stack_a, t_stack **stack_b);
void		rotate_both_and_push_a(int value, t_stack **stack_a, t_stack **stack_b);
void		ra_then_rrb_and_push_a(int value, t_stack **stack_a, t_stack **stack_b);
void		rra_then_rb_and_push_a(int value, t_stack **stack_a, t_stack **stack_b);
void		move_element(int value, t_stack **stack_a, t_stack **stack_b);
int 		cheapest_move(int value, t_stack *stack_a, t_stack *stack_b);
int 		cost_both_up(int rot_a, int rot_b);
int 		cost_both_down(int rot_a, int rot_b, int size_a, int size_b);
int 		cost_a_up_b_down(int rot_a, int rot_b, int size_b);
int 		cost_a_down_b_up(int rot_a, int rot_b, int size_a);
int 		calculate_min_cost(int value, t_stack *stack_b, t_stack *stack_a);
int			find_first_element(t_stack *stack);
int 		find_next_element_to_move(t_stack *stack_b, t_stack *stack_a);
int 		is_extreme_value(int value, t_stack *stack_a);
int 		get_last_value(t_stack *stack);
int			find_place_in_a(int value, t_stack *stack_a);
int 		find_position_in_b(int value, t_stack *stack);
int			stack_len(t_stack *stack);
void		free_stack(t_stack **to_free);
void		remove_last(t_stack **stack);
void 		push(t_stack **stack_a, t_stack **stack_b);
void		r_rotate(t_stack **stack);
void		rotate(t_stack **stack);
void		swap(t_stack **stack);
void 		stack_add_back(t_stack *element, t_stack **stack);
int 		is_numeric(char *str);
int 		ft_atoi(const char *str);
long int 	big_atoi(char *str);
char		*clean_str(char *str);
int			is_too_big(char *str);
int 		check_input(int ac, char **av);
int 		fill_stack(char **av, t_stack **stack);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(const char *str);
int			abs(int a);
int			max(int a, int b);
int			min(int a, int b);

#endif