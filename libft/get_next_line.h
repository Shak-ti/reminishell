/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergero <jbergero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:15:26 by jbergero          #+#    #+#             */
/*   Updated: 2024/05/22 19:15:26 by jbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <fcntl.h> // open
# include <stdio.h> // test
# include <stdlib.h>
# include <unistd.h>

// gnl

char	*get_next_line(int fd);
char	*ft_read(int fd, char *stash, char *buffer);
char	*ft_clear(char *line);
int		ft_has_newline(char *str);

// utils

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif