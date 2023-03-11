/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_vers_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:28:25 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/07 14:17:48 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipe(char **av)
{
	int i;
	int c;
	int j;

	c = 0;
	i = 0;
	if (!av)
		return (0);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '\'' || av[i][j] == '\"')
			{
				while (av[i][j + 1] && (av[i][j] != '\'' || av[i][j] != '\"'))
					j++;
			}
			if (av[i][j] == '|' && c == 0)
				c += 2;
			else if (av[i][j] == '|' && c >= 1)
				c += 1;
			j++;
		}
		i++;
	}
	if (c == 0)
		c += 1;
	return (c);
}

// void ft_free(char **str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

void create_node(t_data **data, char **infile, char **outfile,
				 char **full_cmd, int out_open, char **herdoc)
{
	l_lstadd_back(data, l_lstnew(infile, outfile, full_cmd, out_open, herdoc));
}

int find_first_node(char **av, int b, int y)
{
	int j;

	(void)y;
	j = 0;
	while (av[b])
	{
		j = 0;
		while (av[b][j])
		{
			if (av[b][j] == '\'' || av[b][j] == '\"')
			{
				while (av[b][j + 1] && (av[b][j] != '\'' || av[b][j] != '\"'))
					j++;
				if (av[b][j] == '\'' || av[b][j] == '\"')
					j++;
			}
			if (av[b][j] == '|')
				return (b);
			if (!av[b][j])
				break;
			j++;
		}
		b++;
	}
	return (b);
}

int count_inf_out(char **av, int b, int y, char r)
{
	int j;
	int c;

	j = 0;
	c = 0;
	while (av[b] && b < y)
	{
		j = 0;
		while (av[b][j])
		{
			if (av[b][j] == r) //&& av[b][j + 1] != r
				c++;
			j++;
		}
		b++;
	}
	return (c);
}

int count_inf_out_2(char **av, int b, int y, char *r, char *f)
{
	int j;
	int c;

	j = 0;
	c = 0;
	while (av[b] && b < y)
	{
		j = 0;
		while (av[b][j])
		{
			if ((ft_strcmp(av[b], r) == 0) || (ft_strcmp(av[b], f) == 0))
				c++;
			j++;
		}
		b++;
	}
	return (c);
}

char *fill_inf_out(char *av, char *cmd, int her)
{
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	if (av != NULL)
	{
		if (her == 1)
		{
			her = 2;
			len = ft_strlen(av) + 2;
			cmd = ft_calloc(len + 1, sizeof(char));
			while (her > 0)
			{
				cmd[i] = '<';
				i++;
				her--;
			}
			while (av[j])
			{
				cmd[i] = av[j];
				i++;
				j++;
			}
		}
		else if (her == 2)
		{
			her = 2;
			len = ft_strlen(av) + 2;
			cmd = ft_calloc(len + 1, sizeof(char));
			while (her > 0)
			{
				cmd[i] = '>';
				i++;
				her--;
			}
			while (av[j])
			{
				cmd[i] = av[j];
				i++;
				j++;
			}
		}
		else if (her == 0)
		{
			len = ft_strlen(av);
			cmd = ft_calloc(len + 1, sizeof(char));
			while (av[i])
			{
				cmd[i] = av[i];
				i++;
			}
		}
	}
	else if (av == NULL)
	{
		cmd = NULL;
	}
	return (cmd);
}

char **check_infile(char **av, int b, int y)
{
	int j;
	int p;
	char **inf;
	int red;

	p = count_inf_out(av, b, y, '<');
	inf = ft_calloc(p + 1, sizeof(char *));
	p = 0;
	j = 0;
	while (av[b] && b < y)
	{
		if (av[b][j] == '<' && av[b][j + 1] == '<')
		{
			red = 1;
			inf[p] = fill_inf_out(av[b + 1], inf[p], red);
			p++;
		}
		else if (av[b][j] == '<')
		{
			red = 0;
			inf[p] = fill_inf_out(av[b + 1], inf[p], red);
			p++;
		}
		b++;
	}
	return (inf);
}

char *check_if_ambiguous(char *s, char **env)
{
	int i;

	i = 0;
	// while (s[i])
	// {
	s = ft_strtrim(s, ">>");
	// if (ft_cherche(s, '$') == 1)
	// {
	s = expande_var(s, env, 1);
	// printf("_______%s______\n", s);
	// break;
	// }
	// i++;
	// }
	return (s);
}

char **check_outfile(char **av, int b, int y, char **env)
{
	int j;
	int p;
	char **out;
	int red;
	(void)env;

	p = count_inf_out(av, b, y, '>');
	out = ft_calloc(p + 1, sizeof(char *));
	p = 0;
	while (av[b] && b < y)
	{
		j = 0;
		if (av[b][j] == '>' && av[b][j + 1] == '>')
		{
			red = 2;
			out[p] = fill_inf_out(av[b + 1], out[p], red);
			// if (ft_cherche(out[p], '$') == 1)
			// {
			// 	printf("===\t%s\t===\n", check_if_ambiguous(out[p], env));
			// }
			p++;
		}
		else if (av[b][j] == '>')
		{
			red = 0;
			out[p] = fill_inf_out(av[b + 1], out[p], red);
			// if (ft_cherche(out[p], '$') == 1)
			// {
			// 	printf("===\t%s\t===\n", check_if_ambiguous(out[p], env));
			// }
			p++;
		}
		b++;
	}
	return (out);
}

char *fill_cmd(char *s)
{
	int j;
	int len;
	char *cmd;

	j = 0;
	len = ft_strlen(s);
	cmd = ft_calloc(len + 1, sizeof(char));
	while (s[j] && j < len)
	{
		cmd[j] = s[j];
		j++;
	}
	return (cmd);
}

int check_if_in_out(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			return (0);
		i++;
	}
	return (1);
}

int count_cmd(char **av, int b, int y)
{
	int j;
	int c;

	c = 0;
	j = 0;
	while (av[b] && b < y)
	{
		if (check_if_in_out(av[b]) == 0)
		{
			b++;
			b++;
		}
		else
		{
			c++;
			b++;
		}
	}
	return (c);
}

char **check_cmd(char **av, int b, int y)
{
	int p;
	int len;
	char **cmd;

	p = 0;
	len = count_cmd(av, b, y);
	cmd = ft_calloc(len + 1, sizeof(char *));
	while (av[b] && b < y)
	{
		if (check_if_in_out(av[b]) == 0)
			b++;
		else if (check_if_in_out(av[b]) == 1)
		{
			cmd[p] = fill_cmd(av[b]);
			p++;
		}
		b++;
	}
	return (cmd);
}

int ft_search(char *s, char c)
{
	// if (s == NULL)
	// 	return (-1);
	if (s[0] == c)
		return (1);
	return (-1);
}

int find_pipe(char **av, int i)
{
	while (av[i])
	{
		if (ft_search(av[i], '|') == 1)
			return (i);
		i++;
	}
	return (i);
}

void divide_input_2(char **av, t_data **data, char **env)
{
	int i;
	int y;
	int b;
	char **infile;
	char **outfile;
	char **count;
	int out_open;
	char **herdoc = NULL;
	int p;
	// int l;

	i = count_pipe(av);
	y = 0;
	b = 0;
	p = 0;
	while (i > 0)
	{
		out_open = 0;
		p = find_pipe(av, p);
		b = y;
		y = find_first_node(av, b, y);
		out_open = count_inf_open(av, b, y);
		infile = check_infile(av, b, y);
		infile = expand_Path_2(infile, env);
		outfile = check_outfile(av, b, y, env);
		outfile = expand_Path_2(outfile, env);
		// printf("==%s==\n", outfile[0]);
		// printf("==%s==\n", outfile[1]);
		count = check_cmd(av, b, y);
		count = expand_Path_2(count, env);
		// printf("==%s==\n", count[0]);
		// printf("==%s==\n", count[0]);
		create_node(data, infile, outfile, count, out_open, herdoc);
		y++;
		i--;
		p++;
	}
}