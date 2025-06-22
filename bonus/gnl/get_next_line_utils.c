/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:57:56 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/22 10:02:24 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap_bonus.h"

static size_t	ft_strlenl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

int	newline(char *buffer)
{
	int	j;
	int	i;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (buffer[i])
	{
		if (flag == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			flag = 1;
		buffer[i++] = 0;
	}
	return (flag);
}

static void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;
	size_t			idx;

	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dest;
	if (tmp_dst > tmp_src)
	{
		while (n-- > 0)
			tmp_dst[n] = tmp_src[n];
	}
	else
	{
		idx = 0;
		while (idx < n)
		{
			tmp_dst[idx] = tmp_src[idx];
			idx++;
		}
	}
	return (dest);
}

char	*fstrjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlenl(s1);
	len2 = ft_strlenl(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_memmove(new_str, s1, len1);
	ft_memmove(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	if (s1)
		free((char *)s1);
	return (new_str);
}
