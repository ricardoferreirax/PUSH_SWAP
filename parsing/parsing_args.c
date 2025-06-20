/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:11:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/20 16:46:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_valid_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (ft_is_signed(args[i][j]))
		{
			if (!args[i][j + 1])
				return (0);
			j++;
		}
		while (args[i][j])
		{
			if (!ft_is_digit(args[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_is_duplicated(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_atoi(args[i]) == ft_atoi(args[j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_parsing(char **args)
{
/* 	if (!args)
	{
		free_arr(args);
		ft_error();
		exit(1);
	} 
*/
	if (!ft_valid_args(args))
	{
		free_arr(args);
		ft_error();
		exit(1);
	}
	if (!ft_is_duplicated(args))
	{
		free_arr(args);
		ft_error();
		exit(1);
	}
}
