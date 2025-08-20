/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:27:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/20 22:46:01 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	rev_rotate_both(t_stack **stack_a, t_stack **stack_b, int *a_cost,
		int *b_cost)
{
	while (*a_cost < 0 && *b_cost < 0)
	{
		(*a_cost)++;
		(*b_cost)++;
		ft_rrr(stack_a, stack_b);
	}
}

static void	rotate_both(t_stack **stack_a, t_stack **stack_b, int *a_cost,
		int *b_cost)
{
	while (*a_cost > 0 && *b_cost > 0)
	{
		(*a_cost)--;
		(*b_cost)--;
		ft_rr(stack_a, stack_b);
	}
}

static void	rotate_a(t_stack **stack_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ft_ra(stack_a);
			(*cost)--;
		}
		else
		{
			ft_rra(stack_a);
			(*cost)++;
		}
	}
}

static void	rotate_b(t_stack **stack_b, int *b_cost)
{
	while (*b_cost)
	{
		if (*b_cost > 0)
		{
			ft_rb(stack_b);
			(*b_cost)--;
		}
		else
		{
			ft_rrb(stack_b);
			(*b_cost)++;
		}
	}
}

void	ft_best_move(t_stack **stack_a, t_stack **stack_b, int a_cost,
		int b_cost)
{
	if (a_cost < 0 && b_cost < 0)
		rev_rotate_both(stack_a, stack_b, &a_cost, &b_cost);
	else if (a_cost > 0 && b_cost > 0)
		rotate_both(stack_a, stack_b, &a_cost, &b_cost);
	rotate_a(stack_a, &a_cost);
	rotate_b(stack_b, &b_cost);
	ft_pa(stack_a, stack_b);
}
