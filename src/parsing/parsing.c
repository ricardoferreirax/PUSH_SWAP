/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:26 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/14 21:57:16 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

char	*clean_str(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] == 32 || (str[idx] >= 9 && str[idx] <= 13))
		idx++;
	return (str + idx);
}

int	is_too_big(char *str)
{
	long int	nbr;

	if (ft_strlen(clean_str(str)) > 11)
		return (1);
	nbr = big_atoi(str);
	if (nbr > 2147483647 || nbr < -2147483648)
		return (1);
	return (0);
}

int check_input(int ac, char **av)
{
	int idx1;
	int idx2;

	idx1 = 1;
	while (idx1 < ac)
	{
		if (!is_numeric(av[idx1]))
			return (0);
		if (is_too_big(av[idx1]))
			return (0);
		idx2 = idx1 + 1;
		while (idx2 < ac)
		{
			if (ft_atoi(av[idx1]) == ft_atoi(av[idx2]))
				return (0);
			idx2++;
		}
		idx1++;
	}
	return (1);
}

int fill_stack(char **av, t_stack **stack)
{
    int idx;

	idx = 1;
    while (av[idx])
    {
        int *val = malloc(sizeof(int));
        if (!val)
            return (0);
        *val = ft_atoi(av[idx]);
        stack_add_back(new_element(val), stack);
        idx++;
    }
    return (1);
}
