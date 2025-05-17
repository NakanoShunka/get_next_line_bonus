/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:54:05 by snakano           #+#    #+#             */
/*   Updated: 2025/05/17 12:34:52 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *stash)
{
	int		len;
	char	*line;
	int		i;

	if (!stash || *stash == '\0')
		return (NULL);
	len = ft_search_position(stash);
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && i <= len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = malloc(ft_strlen(stash + i) + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

int	read_loop(int fd, char **stash, char *buf)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (!ft_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*stash);
			*stash = NULL;
			return (-1);
		}
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(*stash, buf);
		if (!tmp)
			return (-1);
		*stash = tmp;
	}
	return (0);
}

static int	read_and_stash(int fd, char **stash)
{
	char	*buf;
	int		status;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	status = read_loop(fd, stash, buf);
	free(buf);
	return (status);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	if (read_and_stash(fd, &stash) == -1)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
