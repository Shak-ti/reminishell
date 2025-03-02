/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconiat <sconiat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:15:21 by jbergero          #+#    #+#             */
/*   Updated: 2025/03/01 17:48:57 by sconiat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = ft_read(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = ft_clear(line);
	return (line);
}

/*
Read file til \n and append buffer to stash, returns stash
*/

char	*ft_read(int fd, char *stash, char *buffer)
{
	ssize_t	rd;
	char	*tmp;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(stash);
			return (NULL);
		}
		if (rd == 0)
			break ;
		buffer[rd] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_has_newline(buffer))
			break ;
	}
	return (stash);
}

/*
Clear stash and cut line with \0, returns clean stash
*/

char	*ft_clear(char *line)
{
	char	*stash;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	line[i + 1] = 0;
	return (stash);
}

/*
Check if string contains \n
*/

int	ft_has_newline(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			return (1);
		i++;
	}
	return (0);
}
