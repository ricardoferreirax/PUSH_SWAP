/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:22:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/23 09:41:18 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static void	ft_push(t_stack **src, t_stack **dest)
{
	t_stack	*temp_src;
	t_stack	*temp_dest;

	if (!*src)
		return ;
	temp_src = *src;
	temp_dest = *dest;
	*src = temp_src->next;
	*dest = temp_src;
	temp_src->next = temp_dest;
}

void	ft_pa(t_stack **stack_a, t_stack **stack_b)
{
	ft_push(stack_b, stack_a);
	ft_putstr_fd("pa\n", 1);
}

/* void	pa(t_stack **a, t_stack **b)
{
	t_stack	*temp_a;
	t_stack	*temp_b;

	temp_a = *a;
	temp_b = *b;
	*b = temp_b->next;
	*a = temp_b;
	temp_b->next = temp_a;
	ft_putstr_fd("pa\n", 1);
} */

void	ft_pb(t_stack **stack_a, t_stack **stack_b)
{
	ft_push(stack_a, stack_b);
	ft_putstr_fd("pb\n", 1);
}

/* void	pb(t_stack **a, t_stack **b)
{
	t_stack	*temp_a;
	t_stack	*temp_b;

	temp_a = *a;
	temp_b = *b;
	*a = temp_a->next;
	*b = temp_a;
	temp_a->next = temp_b;
	ft_putstr_fd("pb\n", 1);
} */