/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:24:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/21 13:58:59 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	ft_swap(t_stack *stack)
{
	int	temp;

	if (!stack || !stack->next)
		return ;
	temp = stack->value;
	stack->value = stack->next->value;
	stack->next->value = temp;
	temp = stack->index;
	stack->index = stack->next->index;
	stack->next->index = temp;
}

void	ft_sa(t_stack **stack_a)
{
	ft_swap(*stack_a);
	ft_putstr_fd("sa\n", 1);
}

void	ft_sb(t_stack **stack_b)
{
	ft_swap(*stack_b);
	ft_putstr_fd("sb\n", 1);
}

void	ft_ss(t_stack **stack_a, t_stack **stack_b)
{
	ft_swap(*stack_a);
	ft_swap(*stack_b);
	ft_putstr_fd("ss\n", 1);
}
