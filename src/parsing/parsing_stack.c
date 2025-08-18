/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:09:41 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/18 14:07:22 by rmedeiro         ###   ########.fr       */
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

static void safe_strjoin(char **dst, const char *s2)
{
    char *res;

    res = ft_strjoin(*dst, (char *)s2);
    if (!res)
    {
        ft_error();
        exit(1);
    }
    *dst = res;
}

static char *ft_join_args(char **args)
{
    char *tmp;
    int   i;

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
    return tmp;
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
