/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakano <snakano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:54:05 by snakano           #+#    #+#             */
/*   Updated: 2025/05/20 19:02:30 by snakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*make_node(int fb)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fb = fb;
	node->stash = NULL;
	node->next = NULL;
	return (node);
}

static int	read_and_append(int fd, t_list *node)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;
	int		i;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		i = 0;
		while (node->stash && node->stash[i])
			if (node->stash[i++] == '\n')
				return (free(buf), 1);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(node->stash, buf);
		if (!tmp)
			return (free(buf), -1);
		free(node->stash);
		node->stash = tmp;
	}
	if (bytes_read == -1)
		return (free(buf), free(node->stash), node->stash = NULL, -1);
	return (free(buf), node->stash && node->stash[0]);
}

static t_list	*get_node_or_create(t_list **head, int fb)
{
	t_list	*node;

	node = *head;
	if (!node)
	{
		node = make_node(fb);
		if (!node)
			return (NULL);
		*head = node;
		return (node);
	}
	while (node)
	{
		if (node->fb == fb)
			return (node);
		if (!node->next)
			return ((node->next = make_node(fb)));
		node = node->next;
	}
	return (NULL);
}

void	delete_node(t_list **head, int fb)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (curr->fb == fb)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->stash);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

char	*get_next_line(int fb)
{
	static t_list	*head;
	t_list			*node;
	char			*line;
	int				result;

	if (fb < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node_or_create(&head, fb);
	if (!node)
		return (NULL);
	result = read_and_append(fb, node);
	if (result == -1)
		return (delete_node(&head, fb), NULL);
	if (result == 0)
	{
		if (!node->stash || node->stash[0] == '\0')
			return (delete_node(&head, fb), NULL);
	}
	line = extract_line(node->stash);
	if (!line)
		return (delete_node(&head, fb), NULL);
	node->stash = update_stash(node->stash);
	if (!node->stash)
		delete_node(&head, fb);
	return (line);
}
