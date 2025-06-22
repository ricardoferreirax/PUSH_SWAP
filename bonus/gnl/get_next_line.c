/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 09:54:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/06/22 09:56:05 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;

	line = NULL;
	if ((fd < 0 && fd > FOPEN_MAX) || BUFFER_SIZE < 1)
		return (line);
	while (*buffer || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = fstrjoin(line, buffer);
		if (newline(buffer))
			break ;
		if (read(fd, buffer, BUFFER_SIZE) == -1)
			return (free(line), NULL);
	}
	return (line);
}
