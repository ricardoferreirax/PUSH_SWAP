/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:58:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/18 13:00:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/* void	ft_index_stack(t_stack *stack_a, int size)
{
	t_stack	*temp;
	t_stack	*high;
	int		value;

	while (size-- > 0)
	{
		temp = stack_a;
		value = INT_MIN;
		high = NULL;
		while (temp)
		{
			if (temp->value == INT_MIN && temp->index == 0)
				temp->index = 1;
			if (temp->value > value && temp->index == 0)
			{
				value = temp->value;
				high = temp;
			}
			else
				temp = temp->next;
		}
		if (high)
			high->index = size;
	}
} */

void	ft_index_stack(t_stack *stack_a, int size)
{
	t_stack *p;
	t_stack *max_node;
	int      max_val;

	while (size-- > 0)
	{
		p = stack_a;
		max_node = NULL;
		max_val = INT_MIN;
		while (p)
		{
			if (p->index == 0 && p->value >= max_val)
			{
				max_val = p->value;
				max_node = p;
			}
			p = p->next;
		}
		if (max_node)
			max_node->index = size;
	}
}
