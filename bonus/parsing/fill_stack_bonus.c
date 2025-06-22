/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stack_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:48:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/21 22:49:31 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap_bonus.h"

int	ft_valid_number(const char *str)
{
	long	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if ((res * sign) > 2147483647 || (res * sign) < -2147483648)
			return (1);
	}
	return (0);
}

void	ft_fill_stack(char **str, t_stack **stack)
{
	long int	value;
	int			i;

	*stack = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_valid_number(str[i]) == 1)
		{
			free_arr(str);
			ft_error();
			ft_free_stack(stack);
			exit(1);
		}
		value = ft_atoi(str[i]);
		ft_lst_add_back(stack, ft_lst_new(value));
		i++;
	}
}
