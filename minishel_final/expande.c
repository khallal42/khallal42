/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:59:30 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/11 14:04:28 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_not_sp_chr(char c)
{
	if (c == '\'' || c == '\"' || c == '$')
		return (0);
	return (1);
}

char	*hold_string(char *s, int i)
{
	int		j;
	int		p;
	char	*str;

	j = 0;
	p = i;
	while (s[i] && ft_not_sp_chr(s[i]) == 1)
		(i++, j++);
	i = 0;
	str = ft_calloc(j + 1, sizeof(char));
	while (s[p] && i < j)
	{
		str[i] = s[p];
		i++;
		p++;
	}
	return (str);
}

char	*hold_var_env(char *s, int i)
{
	int		j;
	int		p;
	char	*env;

	j = 0;
	p = count_var(s, i + 1) + 1; // plus one for dollar
	env = ft_calloc(p + 1, sizeof(char));
	while (s[i] && j < p)
	{
		env[j] = s[i];
		j++;
		i++;
	}
	return (env);
}

char	*hold_sin_quots(char *s, int i, char c)
{
	int		j;
	int		p;
	int		l;
	int		w;
	char	*str;

	j = 0;
	w = 0;
	l = 0;
	p = i;
	i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			j++;
			break ;
		}
		j++;
		i++;
	}
	str = ft_calloc(j + 2, sizeof(char));
	while (s[p] && l <= j)
	{
		str[l] = s[p];
		l++;
		p++;
	}
	return (str);
}

int	ft_split_count_str(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			count++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i] == '\"')
		{
			count++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		if (ft_not_sp_chr(s[i]) == 1)
		{
			count++;
			while (s[i] && ft_not_sp_chr(s[i]) == 1)
				i++;
		}
		if (s[i] == '$')
		{
			count++;
			i += count_var(s, i + 1);
		}
		if (!s[i])
			break ;
		else
			i++;
	}
	return (count);
}

char	**split_str(char *s)
{
	int		i;
	int		j;
	int		l;
	int		count;
	char	**all;

	i = 0;
	j = 0;
	l = 0;
	count = ft_split_count_str(s);
	all = ft_calloc(count + 2, sizeof(char *));
	while (s[i])
	{
		if (s[i] == '\'')
		{
			all[j] = hold_sin_quots(s, i, '\'');
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
			j++;
		}
		else if (s[i] == '\"')
		{
			all[j] = hold_sin_quots(s, i, '\"');
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			if (s[i] == '\"')
				i++;
			j++;
		}
		else if (ft_not_sp_chr(s[i]) == 1)
		{
			all[j] = hold_string(s, i);
			while (s[i] && ft_not_sp_chr(s[i]) == 1)
				i++;
			j++;
		}
		else if (s[i] == '$')
		{
			all[j] = hold_var_env(s, i);
			l = count_var(s, i + 1);
			i = i + l + 1;
			j++;
		}
		else
			i++;
	}
	return (all);
}

char	**expand_Path_2(char **a, char **env)
{
	char	**ko;
	char	*new;

	int i, j, c;
	i = 0;
	c = 0;
	while (a && a[i])
	{
		j = 0;
		if (ft_cherche(a[i], '$') == 1)
		{
			ko = split_str(a[i]);
			a[i] = env_var_2(ko, env);
		}
		else
		{
			new = ft_calloc(1, sizeof(char));
			ko = split_str(a[i]);
			while (ko[j])
			{
				ko[j] = ft_strtrim(ko[j], "\"\'");
				new = ft_strjoin(new, ko[j]);
				j++;
			}
			a[i] = new;
		}
		i++;
	}
	// ft_free1(ko);
	return (a);
}
