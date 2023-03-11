/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:32:55 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/09 15:36:58 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_vare_2(char *s, int index)
{
	while (s[index] && s[index] != '$')
		index++;
	return (index);
}

int	count_var(char *s, int index)
{
	int	c;

	c = 0;
	while (s[index] && (ft_isalpha(s[index]) == 1 || s[index] == '_'
			|| s[index] == '?'))
		(index++, c++);
	if (s[index] && (ft_isdigit(s[index]) == 1))
		while (s[index] && (ft_isdigit(s[index]) == 1))
			(index++, c++);
	return (c);
}

char	*split_str_vers(char *s, int index)
{
	int		j;
	int		p;
	char	*str;

	j = 0;
	p = count_var(s, (index + 1));
	str = ft_calloc(p + 2, sizeof(char));
	while (j <= p && s[index])
	{
		str[j] = s[index];
		j++;
		index++;
	}
	return (str);
}

char	**split_with_dol(char *s, int nb)
{
	int		i;
	int		j;
	int		p;
	char	**str;

	i = 0;
	p = 0;
	j = 0;
	str = ft_calloc(nb + 2, sizeof(char *));
	while (nb > 0)
	{
		p = find_vare_2(s, p);
		str[j] = split_str_vers(s, p);
		p++;
		nb--;
		j++;
	}
	return (str);
}

int	check_the_env(char *s1, char *s2, int df)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (s1[i] == s2[j] && j <= df)
	{
		i++;
		j++;
	}
	if (i == df && s1[i] == '=')
		return (1);
	return (0);
}

char	*skip_var(char *yum)
{
	int		i;
	int		j;
	int		c;
	char	*new;

	j = 0;
	i = 0;
	c = 0;
	while (yum[i])
	{
		if (yum[i] == '=')
		{
			i++;
			while (yum[i + 1])
			{
				i++;
				c++;
			}
		}
		i++;
	}
	new = ft_calloc(c + 2, sizeof(char));
	i = 0;
	while (yum[i])
	{
		if (yum[i] == '=')
		{
			i++;
			while (yum[i + 1])
			{
				new[j] = yum[i];
				j++;
				i++;
			}
		}
		if (!yum[i + 1])
			new[j] = yum[i];
		i++;
	}
	return (new);
}

char	*linke_str(char *yum, char *str, int j, int skip)
{
	int		all;
	int		y;
	int		t;
	int		m;
	char	*iren;

	y = 0;
	m = 0;
	t = 0;
	all = ft_strlen(yum) + ft_strlen(str) - skip;
	iren = ft_calloc(all + 1, sizeof(char));
	while (all > 0)
	{
		if (str[m] == '$' && m == j)
		{
			while (yum[t])
			{
				iren[y] = yum[t];
				t++;
				y++;
				all--;
			}
			while (skip >= 0)
			{
				m++;
				skip--;
			}
		}
		iren[y] = str[m];
		y++;
		m++;
		all--;
	}
	return (iren);
}

char	*change_string(char *cmd, char *s, int count)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(s) - count, sizeof(char));
	while (s[i])
	{
		if (ft_strncmp(s, cmd, count, i) == 0)
		{
			while (s[i] && count >= 0)
			{
				i++;
				count--;
			}
		}
		if (!s[i])
			break ;
		new[j] = s[i];
		i++;
		j++;
	}
	return (new);
}

char	*expande_var(char *s, char **env, int nb)
{
	int i;
	int j;
	int c;
	int e;
	char **cmd;

	cmd = ft_calloc(nb + 2, sizeof(char *));
	cmd = split_with_dol(s, nb);
	e = 0;
	i = 0;
	while (nb > 0)
	{
		c = 0;
		i = find_vare_2(s, i);
		j = count_var(s, (i + 1));
		if (ft_strncmp(cmd[e], "?", 1, 1) == 0)
		{
			cmd[e] = ft_itoa(exit_status);
			s = linke_str(cmd[e], s, i, 1);
		}
		else
		{
			// printf("==%s==\n", cmd[e]);
			while (env[c])
			{
				if (check_the_env(env[c], cmd[e], j) == 1)
				{
					cmd[e] = env[c];
					cmd[e] = skip_var(cmd[e]);
					s = linke_str(cmd[e], s, i, j);
					e++;
					i++;
					break ;
				}
				c++;
			}
			if (!env[c])
			{
				s = change_string(cmd[e], s, j);
				e++;
			}
		}
		nb--;
	}
	//ft_free1(cmd);
	if (!s)
		return (NULL);
	return (s);
}