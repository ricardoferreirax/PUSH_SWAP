/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:09:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/20 16:37:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_is_full_space(char *s)
{
	while (*s == ' ')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

static char	*ft_join_args(char **args)
{
	char	*tmp;
	char	*joined;
	int		i;

	i = 1;
	tmp = ft_strdup("");
	while (args[i])
	{
		if (ft_is_full_space(args[i]))
		{
			ft_error();
			free(tmp);
			exit(1);
		}
		joined = ft_strjoin(tmp, args[i]);
		free(tmp);
		tmp = ft_strjoin(joined, " ");
		free(joined);
		i++;
	}
	return (tmp);
}

char	**ft_stack(char **args)
{
	char	**str;
	char	*s;

	s = NULL;
	s = ft_join_args(args);
	str = ft_split(s, ' ');
	free(s);
	return (str);
}
