/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:28:24 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/15 23:28:39 by rmedeiro         ###   ########.fr       */
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

static char	*ft_join_args(char **v)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = ft_strdup("");
	while (v[i])
	{
		if (ft_is_full_space(v[i]))
		{
			ft_error();
			free(tmp);
			exit(1);
		}
		tmp = ft_strjoin(tmp, v[i]);
		tmp = ft_strjoin(tmp, " ");
		i++;
	}
	return (tmp);
}

char	**ft_stack(char **v)
{
	char	**str;
	char	*s;

	s = NULL;
	s = ft_join_args(v);
	str = ft_split(s, ' ');
	free(s);
	return (str);
}
