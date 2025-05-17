/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakanoshunka <nakanoshunka@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:54:05 by snakano           #+#    #+#             */
/*   Updated: 2025/05/17 13:05:52 by nakanoshunk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list *make_node(int fb)
{
	t_list *node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fb = fb;
	node->stash = NULL;
	node->next = NULL;
	return (node);
}

static int read_and_append(int fd, t_list *node)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	bytes_read = 1;
	while (bytes_read > 0 && (!node->stash || !ft_strchr(node->stash, '\n')))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			if (node->stash)
				free(node->stash);
			node->stash = NULL;
			return (-1);
		}
		if (bytes_read == 0)
			break;
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(node->stash, buf);
		if (!tmp)
		{
			free(buf);
			return (0);
		}
		free(node->stash);
		node->stash = tmp;
	}
	free(buf);
	return (node->stash != NULL && node->stash[0] != '\0');
}

static t_list *get_node_or_create(t_list **head, int fb)
{
	t_list *node = *head;
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

void delete_node(t_list **head, int fb)
{
	t_list *prev = NULL;
	t_list *curr = *head;
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
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

char *get_next_line(int fb)
{
	static t_list *head;
	t_list *node;
	char *line;
	int result;

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
		{
			delete_node(&head, fb);
			return (NULL);
		}
	}
	line = extract_line(node->stash);
	if (!line)
		return (delete_node(&head, fb), NULL);
	node->stash = update_stash(node->stash);
	if (!node->stash)
		delete_node(&head, fb);
	return (line);
}
