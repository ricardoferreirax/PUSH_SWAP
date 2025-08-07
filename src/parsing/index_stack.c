/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:58:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/07 22:07:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_index_stack(t_stack *stack_a, int size)
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
}
