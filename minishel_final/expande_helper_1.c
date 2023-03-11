/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_helper_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:32:48 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/11 14:00:15 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_exp(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_cherche(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_cherche_me(char *s, char c, char f)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == f)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_quots(char *s)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	x = 0;
	if (ft_cherche_me(s, '\'', '\"') == 0)
		return (1);
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			y++;
		}
		else if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			x++;
		}
		if (!s[i])
			break ;
		i++;
	}
	if (y >= x)
		return (0);
	return (1);
}

int	count_dollar(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '$')
			c++;
		i++;
	}
	return (c);
}

char	*env_var_2(char **k, char **env)
{
	int		i;
	int		c;
	char	*new;

	i = 0;
	c = 0;
	while (k[i])
	{
		if (ft_cherche(k[i], '$') == 1)
		{
			c = count_dollar(k[i]);
			if (ft_check_quots(k[i]) == 1)
			{
				printf("==%s===\n", k[i]);
				if (expande_var(k[i], env, c))
					k[i] = expande_var(k[i], env, c);
				else if (!expande_var(k[i], env, c))
					k[i] = ft_strdup("NULL");
			}
		}
		i++;
	}
	new = ft_calloc(1, sizeof(char));
	i = 0;
	while (k[i])
	{
		k[i] = ft_strtrim(k[i], "\"\'");
		if (ft_strcmp_1(k[i], "NULL") != 0)
			new = ft_strjoin(new, k[i]);
		i++;
	}
	return (new);
}
