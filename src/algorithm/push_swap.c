/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:54:22 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int push_until_three_left(t_stack **stack_b, t_stack **stack_a)
{
	int count;
	int operations;

	count = stack_len(*stack_a);
	operations = 0;
	while (count > 3)
	{
		push(stack_b, stack_a);
		ft_printf("pb\n");
		count--;
		operations++;
	}
	return (operations);
}

int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->next->content < stack->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	sort_three_elements(t_stack **stack)
{
	int	tab[3];

	while (!is_sorted(*stack))
	{
		tab[0] = ((*stack)->content);
		tab[1] = ((*stack)->next->content);
		tab[2] = ((*stack)->next->next->content);
		if (tab[0] > tab[1] && tab[0] > tab[2])
		{
			rotate(stack);
			ft_printf("ra\n");
		}
		else if (tab[1] > tab[0] && tab[1] > tab[2])
		{
			r_rotate(stack);
			ft_printf("rra\n");
		}
		else if (tab[0] > tab[1])
		{
			swap(stack);
			ft_printf("sa\n");
		}
	}
}

void	final_rotate(t_stack **stack)
{
	int	first_element_place;
	int	first_element;

	first_element = find_first_element(*stack);
	first_element_place = find_position_in_b(first_element, *stack);
	if (first_element_place < (stack_len(*stack) / 2))
	{
		while (!is_sorted(*stack))
		{
			rotate(stack);
			ft_printf("ra\n");
		}
	}
	else
	{
		while (!is_sorted(*stack))
		{
			r_rotate(stack);
			ft_printf("rra\n");
		}
	}
}

void	push_swap(t_stack **stack_a, t_stack **stack_b)
{
	int	value;

	if (stack_len(*stack_a) > 3)
		push_until_three_left(stack_a, stack_b);
	if (stack_len(*stack_a) == 3)
		sort_three_elements(stack_a);
	while (*stack_b)
	{
		value = find_next_element_to_move(*stack_a, *stack_b);
		move_element(value, stack_b, stack_a);
	}
	final_rotate(stack_a);
}
