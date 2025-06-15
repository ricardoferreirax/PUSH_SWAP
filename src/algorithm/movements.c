/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:40:05 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:45:25 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

//both_down
void	rrr_and_push_a(int value, t_stack **stack_a, t_stack **stack_b)
{
	while (find_place_in_a(value, *stack_b) > 0
		&& find_position_in_b(value, *stack_a) > 0)
	{
		r_rotate(stack_b);
		r_rotate(stack_a);
		ft_printf("rrr\n");
	}
	while (find_place_in_a(value, *stack_b) > 0)
	{
		r_rotate(stack_b);
		ft_printf("rra\n");
	}
	while (find_position_in_b(value, *stack_a) > 0)
	{
		r_rotate(stack_a);
		ft_printf("rrb\n");
	}
	push(stack_a, stack_b);
	ft_printf("pa\n");
}

//both_up
void	rotate_both_and_push_a(int value, t_stack **stack_a, t_stack **stack_b)
{
	while (find_place_in_a(value, *stack_b) > 0
		&& find_position_in_b(value, *stack_a) > 0)
	{
		rotate(stack_b);
		rotate(stack_a);
		ft_printf("rr\n");
	}
	while (find_place_in_a(value, *stack_b) > 0)
	{
		rotate(stack_b);
		ft_printf("ra\n");
	}
	while (find_position_in_b(value, *stack_a) > 0)
	{
		rotate(stack_a);
		ft_printf("rb\n");
	}
	push(stack_a, stack_b);
	ft_printf("pa\n");
}

// a_up_b_down
void	ra_then_rrb_and_push_a(int value, t_stack **stack_a, t_stack **stack_b)
{
	while (find_place_in_a(value, *stack_b) > 0)
	{
		rotate(stack_b);
		ft_printf("ra\n");
	}
	while (find_position_in_b(value, *stack_a) > 0)
	{
		r_rotate(stack_a);
		ft_printf("rrb\n");
	}
	push(stack_a, stack_b);
	ft_printf("pa\n");
}

//a_down_b_up
void	rra_then_rb_and_push_a(int value, t_stack **stack_a, t_stack **stack_b)
{
	while (find_place_in_a(value, *stack_b) > 0)
	{
		r_rotate(stack_b);
		ft_printf("rra\n");
	}
	while (find_position_in_b(value, *stack_a) > 0)
	{
		rotate(stack_a);
		ft_printf("rb\n");
	}
	push(stack_a, stack_b);
	ft_printf("pa\n");
}

void	move_element(int value, t_stack **stack_a, t_stack **stack_b)
{
	int	cheapest_strategy;

	cheapest_strategy = cheapest_move(value, *stack_a, *stack_b);
	if (cheapest_strategy == 0)
		rrr_and_push_a(value, stack_a, stack_b);
	else if (cheapest_strategy == 1)
		rotate_both_and_push_a(value, stack_a, stack_b);
	else if (cheapest_strategy == 2)
		ra_then_rrb_and_push_a(value, stack_a, stack_b);
	else if (cheapest_strategy == 3)
		rra_then_rb_and_push_a(value, stack_a, stack_b);
}
