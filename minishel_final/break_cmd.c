/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:57:09 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/10 15:30:49 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_tokens(char c)
{
	if (c == ' ' || c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int find_set(char *s, int i, char c)
{
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int count_word(char *s, char set)
{
	int i;
	int sp;

	(void)set;
	i = 0;
	sp = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		while (s[i] && ft_tokens(s[i]) == 0)
		{
			i++;
			if (!s[i])
				sp++;
		}
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (s[i] == '\'')
			{
				i = find_set(s, i, '\'');
				if (i == -1)
					msg_err("syntaxe Error1");
				i++;
			}
			else if (s[i] == '\"')
			{
				i = find_set(s, i, '\"');
				if (i == -1)
					msg_err("syntaxe Error1");
				i++;
			}
		}
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
			(sp++, i++, i++);
		if (ft_tokens(s[i]) == 1)
			(sp++, i++);
		sp++;
	}
	if (sp == 0)
		sp = 1;
	return (sp);
}

char **break_cmd(char *s, char set)
{
	int nword;
	char **av;

	nword = count_word(s, set);
	if (nword == 0)
		return (NULL);
	if (nword == -1)
		return (NULL);
	av = ft_calloc((nword + 2), sizeof(char *));
	if (av == NULL)
		exit(1);
	av = ft_fill_list(av, s);
	return (av);
}
