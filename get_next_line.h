/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakano <snakano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:54:05 by snakano           #+#    #+#             */
/*   Updated: 2025/05/07 15:45:55 by snakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*extract_line(char *stash);
char		*update_stash(char *stash);
int			read_loop(int fd, char **stash, char *buf);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin_core(const char *s1, const char *s2);
char		*ft_strjoin(char *s1, char *s2);
int			ft_search_position(char *stash);

#endif
