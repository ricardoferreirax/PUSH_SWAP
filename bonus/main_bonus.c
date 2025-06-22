/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:42:26 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/21 23:48:45 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap_bonus.h"

void	free_arr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_read(char *line, t_stack **stack_a, t_stack **stack_b)
{
	line = get_next_line(0);
	while (line)
	{
		if (!line)
			break ;
		ft_operations(line, stack_a, stack_b);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	if (ft_is_sorted(*stack_a) && !(*stack_b))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

int	main(int c, char **args)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**str;
	char	*line;

	str = NULL;
	line = NULL;
	stack_a = NULL;
	stack_b = NULL;
	if (c > 1)
	{
		str = ft_parsing_stack(args);
		ft_parsing(str);
		ft_fill_stack(str, &stack_a);
		free_arr(str);
		ft_read(line, &stack_a, &stack_b);
		ft_free_stack(&stack_a);
		ft_free_stack(&stack_b);
	}
	return (0);
}
