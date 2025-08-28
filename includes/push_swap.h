/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:04:30 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 18:10:35 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}					t_stack;

void	ft_pa(t_stack **stack_a, t_stack **stack_b);
void	ft_pb(t_stack **stack_a, t_stack **stack_b);
void	ft_rra(t_stack **stack_a);
void	ft_rrb(t_stack **stack_b);
void	ft_rrr(t_stack **stack_a, t_stack **stack_b);
void	ft_ra(t_stack **stack_a);
void	ft_rb(t_stack **stack_b);
void	ft_rr(t_stack **stack_a, t_stack **stack_b);
void	ft_sa(t_stack **stack_a);
void	ft_sb(t_stack **stack_b);
void	ft_ss(t_stack **stack_a, t_stack **stack_b);
int		ft_valid_number(const char *str);
int		ft_is_duplicated(char **args);
void	ft_fill_stack(char **str, t_stack **stack);
void	ft_index_stack(t_stack *stack_a, int size);
int		ft_is_duplicated(char **args);
void	ft_parsing(char **args);
char	**ft_parsing_stack(char **args);
void	ft_error(void);
int		ft_is_digit(char c);
int		ft_is_signed(char c);
void	ft_best_move(t_stack **stack_a, t_stack **stack_b, int a_cost,
			int b_cost);
void	ft_cost(t_stack **stack_a, t_stack **stack_b);
void	ft_cheapest(t_stack **stack_a, t_stack **stack_b);
void	ft_positon(t_stack **stack);
int		ft_find_high(t_stack *stack);
int		ft_lowest_idx_pos(t_stack **stack);
int		ft_target(t_stack **stack_a, int b_index, int target_index,
			int target_pos);
void	ft_assign_pos(t_stack **stack_a, t_stack **stack_b);
int		ft_is_sorted(t_stack *stack);
void	ft_sort_three(t_stack **stack_a);
void	ft_sort(t_stack **stack_a, t_stack **stack_b);
void	ft_free_stack(t_stack **stack);
int		ft_atoi(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_abs(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *s);
void	ft_lst_add_back(t_stack **stack, t_stack *new);
int		ft_size(t_stack *stack);
t_stack	*ft_lst_new(int value);
t_stack	*ft_last(t_stack *stack);
t_stack	*ft_before_last(t_stack *stack);
char	**ft_split(char const *s, char c);
void	free_arr(char **args);

#endif