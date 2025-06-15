/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:54:44 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:33 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int get_last_value(t_stack *stack)
{
    while (stack)
    {
        if (stack->next == NULL)
            break;
        stack = stack->next;
    }
    return (stack->content);
}

int is_extreme_value(int value, t_stack *stack_a)
{
    int min;
    int max;

    min = stack_a->content;
    max = stack_a->content;
    while (stack_a)
    {
        if (stack_a->content > max)
            max = stack_a->content;
        if (stack_a->content < min)
            min = stack_a->content;
        stack_a = stack_a->next;
    }
    if (value > max || value < min)
        return (1);
    return (0);
}

int	find_place_in_a(int value, t_stack *stack_a)
{
	int	count;
	int	prev_value;
	int	extreme;

	count = 0;
	prev_value = get_last_value(stack_a);
	extreme = is_extreme_value(value, stack_a);
	while (stack_a)
	{
		if (extreme && prev_value > stack_a->content)
			break ;
		else if (prev_value < value && value < stack_a->content)
			break ;
		count++;
		prev_value = stack_a->content;
		stack_a = stack_a->next;
	}
	return (count);
}

int find_position_in_b(int value, t_stack *stack)
{
    int count;

    count = 0;
    while (stack)
    {
        if (value == stack->content)
            break;
        stack = stack->next;
        count++;
    }
    return (count);
}
