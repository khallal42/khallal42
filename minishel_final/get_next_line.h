/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:34:48 by khallal           #+#    #+#             */
/*   Updated: 2023/03/02 16:45:39 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_strdup1(char *s1);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen1(char *s);
char	*get_next_line(int fd);

#endif
