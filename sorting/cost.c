/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:22:00 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/15 23:22:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_cost(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*b_tmp;
	int		a_size;
	int		b_size;

	a_size = ft_size(*stack_a);
	b_size = ft_size(*stack_b);
	b_tmp = *stack_b;
	while (b_tmp)
	{
		b_tmp->cost_b = b_tmp->pos;
		if (b_tmp->pos > b_size / 2)
			b_tmp->cost_b = (b_size - b_tmp->pos) * -1;
		b_tmp->cost_a = b_tmp->target;
		if (b_tmp->target > a_size / 2)
			b_tmp->cost_a = (a_size - b_tmp->target) * -1;
		b_tmp = b_tmp->next;
	}
}

void	ft_cheapest(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp;
	int		cheapest;
	int		a_cost;
	int		b_cost;

	a_cost = 0;
	b_cost = 0;
	if (!*stack_b)
		return ;
	tmp = *stack_b;
	cheapest = INT_MAX;
	while (tmp)
	{
		if (ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b) < cheapest)
		{
			cheapest = ft_abs(tmp->cost_b) + ft_abs(tmp->cost_a);
			a_cost = tmp->cost_a;
			b_cost = tmp->cost_b;
		}
		tmp = tmp->next;
	}
	if (cheapest != INT_MAX)
		ft_best_move(stack_a, stack_b, a_cost, b_cost);
	else
		return ;
}
