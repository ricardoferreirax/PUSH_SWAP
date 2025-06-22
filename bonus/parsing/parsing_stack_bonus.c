/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stack_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:54 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/21 23:01:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap_bonus.h"


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

static char	*ft_join_args(char **args)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = ft_strdup("");
	while (args[i])
	{
		if (ft_has_only_spaces(args[i]))
		{
			ft_error();
			free(tmp);
			exit(1);
		}
		tmp = ft_strjoin(tmp, args[i]);
		tmp = ft_strjoin(tmp, " ");
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
