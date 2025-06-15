/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:04:55 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:17:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	if (!check_input(ac, av))
		return (ft_putstr_fd("Error\n", 2), 1);
	fill_stack(&stack_a, ac, av);
	if (is_sorted(stack_a) && stack_len(stack_b) == 0)
	{
		free_stack(&stack_a);
		return (0);
	}
	push_swap(&stack_a, &stack_b);
	free_stack(&stack_a);
	if (stack_b)
		free_stack(&stack_b);
	return (0);
}
