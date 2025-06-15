/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:27:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:21 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int	find_first_element(t_stack *stack)
{
	int	first_element;

	first_element = stack->content;
	while (stack->next)
	{
		stack = stack->next;
		if (stack->content < first_element)
			first_element = stack->content;
	}
	return (first_element);
}

int find_next_element_to_move(t_stack *stack_b, t_stack *stack_a)
{
	int value;
	t_stack *tmp;

	if (!stack_a)
		return (-1);
	tmp = stack_a;
	value = tmp->content;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (calculate_min_cost(tmp->content, stack_b, stack_a) 
			< calculate_min_cost(value, stack_b, stack_a))
			value = tmp->content;
	}
	return (value);
}
