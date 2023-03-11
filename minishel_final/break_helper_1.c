/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrakik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:53:55 by hrakik            #+#    #+#             */
/*   Updated: 2023/02/25 09:53:56 by hrakik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_sp(char *s, int index)
{
	int	q;

	q = 0;
	while (s[index] && s[index] == ' ')
		index++;
	if (s[index] && s[index] != ' ' && s[index] != '<' && s[index] != '>'
		&& s[index] != '|')
	{
		while (s[index] && s[index] != ' ' && s[index] != '<' && s[index] != '>'
			&& s[index] != '|')
		{
			if (s[index] == '\'')
			{
				index++;
				q++;
				while (s[index] && s[index] != '\'')
				{
					index++;
					q++;
				}
				if (s[index] == '\'')
				{
					index++;
					q++;
				}
				else
				{
					msg_err("syntaxe Error");
				}
			}
			else if (s[index] == '\"')
			{
				index++;
				q++;
				while (s[index] && s[index] != '\"')
				{
					index++;
					q++;
				}
				if (s[index] == '\"')
				{
					index++;
					q++;
				}
				else
				{
					msg_err("syntaxe Error");
				}
			}
			else
			{
				index++;
				q++;
			}
		}
	}
	else if ((s[index] == '>' && s[index + 1] == '>') || (s[index] == '<'
				&& s[index + 1] == '<'))
		q = 1;
	else if (s[index] == ' ' || s[index] == '<' || s[index] == '>'
			|| s[index] == '|')
		q++;
	return (q + 1);
}

char	**ft_fill_list(char **av, char *s)
{
	int		i;
	int		len;
	char	*b;
	int		h;
	int		bob;

	i = 0;
	bob = 0;
	while (s[i])
	{
		h = 0;
		len = ft_strlen_sp(s, i);
		b = ft_calloc(len, sizeof(char));
		if (b == NULL)
			exit(1);
		while (s[i] == ' ')
			i++;
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && len == 1)
		{
			b[h] = s[i];
			i++;
			h++;
			len--;
		}
		else if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
		{
			while (len > 0)
			{
				b[h] = s[i];
				i++;
				h++;
				len--;
			}
		}
		else
		{
			while (s[i] && (s[i] != '|' || s[i] != '>' || s[i] != '<')
				&& len > 1) 
			{
				b[h] = s[i];
				i++;
				h++;
				len--;
			}
		}
		av[bob] = ft_strdup(b);
		bob++;
	}
	return (av);
}