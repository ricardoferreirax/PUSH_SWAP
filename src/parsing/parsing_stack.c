/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:09:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 18:01:32 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	ft_has_only_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

static void	safe_strjoin(char **tmp, const char *s2)
{
	char	*res;

	res = ft_strjoin(*tmp, (char *)s2);
	if (!res)
	{
		ft_error();
		exit(1);
	}
	*tmp = res;
}

static char	*ft_join_args(char **args)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup("");
	if (!tmp)
	{
		ft_error();
		exit(1);
	}
	i = 1;
	while (args[i])
	{
		if (ft_has_only_spaces(args[i]))
		{
			ft_error();
			free(tmp);
			exit(1);
		}
		safe_strjoin(&tmp, args[i]);
		safe_strjoin(&tmp, " ");
		i++;
	}
	return (tmp);
}

char	**ft_parsing_stack(char **args)
{
	char	**str;
	char	*s;

	s = NULL;
	s = ft_join_args(args);
	str = ft_split(s, ' ');
	free(s);
	return (str);
}
