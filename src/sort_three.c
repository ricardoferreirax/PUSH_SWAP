/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:27:13 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/15 23:27:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_find_high(t_stack *stack)
{
	int	high;

	high = INT_MIN;
	while (stack)
	{
		if (stack->value > high)
			high = stack->value;
		stack = stack->next;
	}
	return (high);
}

void	ft_sort_three(t_stack **stack_a)
{
	int	high;

	if (ft_is_sorted(*stack_a))
		return ;
	high = ft_find_high(*stack_a);
	if ((*stack_a)->value == high)
		ft_ra(stack_a);
	else if ((*stack_a)->next->value == high)
		ft_rra(stack_a);
	if ((*stack_a)->value > (*stack_a)->next->value)
		ft_sa(stack_a);
}
