/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:58:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 17:56:34 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_index_stack(t_stack *stack_a, int size)
{
	t_stack	*current;
	t_stack	*high_node;
	int		max_value;

	while (size-- > 0)
	{
		current = stack_a;
		high_node = NULL;
		max_value = INT_MIN;
		while (current)
		{
			if (current->index == 0 && current->value >= max_value)
			{
				max_value = current->value;
				high_node = current;
			}
			current = current->next;
		}
		if (high_node)
			high_node->index = size;
	}
}
