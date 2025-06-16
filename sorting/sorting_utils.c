/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:27:13 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/16 13:14:12 by rmedeiro         ###   ########.fr       */
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

void	ft_positon(t_stack **stack)
{
	t_stack	*tmp;
	int		i;

	i = 0;
	tmp = *stack;
	while (tmp)
	{
		tmp->pos = i;
		tmp = tmp->next;
		i++;
	}
}
