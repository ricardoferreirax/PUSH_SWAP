/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:26:36 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/15 23:26:53 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_push_to_b(t_stack **stack_a, t_stack **stack_b)
{
	int	size;
	int	i;
	int	is_pushed;

	size = ft_size(*stack_a);
	is_pushed = 0;
	i = 0;
	while (size > 6 && i < size && is_pushed < size / 2)
	{
		if ((*stack_a)->index <= size / 2)
		{
			ft_pb(stack_a, stack_b);
			is_pushed++;
		}
		else
			ft_ra(stack_a);
		i++;
	}
	while (size - is_pushed > 3)
	{
		ft_pb(stack_a, stack_b);
		is_pushed++;
	}
}

static int	ft_lowest_idx_pos(t_stack **stack)
{
	t_stack	*tmp;
	int		loew_i;
	int		lowe_p;

	tmp = *stack;
	loew_i = INT_MAX;
	ft_positon(stack);
	lowe_p = tmp->pos;
	while (tmp)
	{
		if (tmp->index < loew_i)
		{
			loew_i = tmp->index;
			lowe_p = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (lowe_p);
}

static void	ft_stack_shift(t_stack **stack_a)
{
	int	size;
	int	lowest;

	size = ft_size(*stack_a);
	lowest = ft_lowest_idx_pos(stack_a);
	if (lowest > size / 2)
	{
		while (lowest < size)
		{
			ft_rra(stack_a);
			lowest++;
		}
	}
	else
	{
		while (lowest)
		{
			ft_ra(stack_a);
			lowest--;
		}
	}
}

void	ft_sort(t_stack **stack_a, t_stack **stack_b)
{
	ft_push_to_b(stack_a, stack_b);
	ft_sort_three(stack_a);
	while (*stack_b)
	{
		ft_assign_pos(stack_a, stack_b);
		ft_cost(stack_a, stack_b);
		ft_cheapest(stack_a, stack_b);
	}
	if (!ft_is_sorted(*stack_a) && *stack_a)
	{
		ft_stack_shift(stack_a);
	}
}
