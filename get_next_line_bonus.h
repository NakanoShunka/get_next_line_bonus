/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakano <snakano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:54:05 by snakano           #+#    #+#             */
/*   Updated: 2025/05/09 14:37:36 by snakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fb;
	char			*stash;
	struct s_list	*next;
}	t_list;

char			*get_next_line(int fb);
char			*ft_make_line(int fd, t_list *node);

char			*extract_line(char *stash);
char			*update_stash(char *stash);
char			*get_next_line(int fd);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin_core(const char *s1, const char *s2);
int				ft_search_position(char *stash);
void			delete_node(t_list **head, int fb);
char			*ft_strjoin(char *s1, char *s2);

#endif
