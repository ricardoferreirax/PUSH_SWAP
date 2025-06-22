/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:17:28 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/22 09:00:12 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

static void	ft_error_exit(char *line, t_stack **stack_a, t_stack **stack_b)
{
	ft_error();
	free(line);
	ft_free_stack(stack_a);
	ft_free_stack(stack_b);
	get_next_line(-100);
	exit(1);
}

void	ft_operations(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (!ft_strcmp(line, "sa\n"))
		ft_sa(stack_a);
	else if (!ft_strcmp(line, "sb\n"))
		ft_sb(stack_b);
	else if (!ft_strcmp(line, "ss\n"))
		ft_ss(stack_a, stack_b);
	else if (!ft_strcmp(line, "pa\n"))
		ft_pa(stack_a, stack_b);
	else if (!ft_strcmp(line, "pb\n"))
		ft_pb(stack_a, stack_b);
	else if (!ft_strcmp(line, "ra\n"))
		ft_ra(stack_a);
	else if (!ft_strcmp(line, "rb\n"))
		ft_rb(stack_b);
	else if (!ft_strcmp(line, "rr\n"))
		ft_rr(stack_a, stack_b);
	else if (!ft_strcmp(line, "rra\n"))
		ft_rra(stack_a);
	else if (!ft_strcmp(line, "rrb\n"))
		ft_rrb(stack_b);
	else if (!ft_strcmp(line, "rrr\n"))
		ft_rrr(stack_a, stack_b);
	else
		ft_error_exit(line, stack_a, stack_b);
}