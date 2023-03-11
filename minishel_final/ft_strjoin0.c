/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:00:27 by khallal           #+#    #+#             */
/*   Updated: 2023/02/20 14:35:49 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin0(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*k;

	i = 0;
	j = 0;
	if (!s2 || !s1)
		return (0);
	k = malloc((ft_strlen0(s1) + ft_strlen0(s2) + 1));
	if (!(k))
		return (NULL);
	while (s1[i])
	{
		k[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		k[i] = s2[j];
		i++;
		j++;
	}
	k[i] = '\0';
	return (k);
}
