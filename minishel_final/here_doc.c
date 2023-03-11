/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:21:11 by khallal           #+#    #+#             */
/*   Updated: 2023/03/11 13:38:05 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

int	check_heredoc(char **k, int i)
{
	if (k)
	{
		while (k[i])
		{
			if (k[i][0] == '<' && k[i][1] == '<')
				return (1);
			i++;
		}
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strcmp1(char *tmp, char *mv)
{
	int	i;

	i = 0;
	while (tmp[i] || mv[i])
	{
		if (tmp[i] != mv[i])
			return (0);
		else
			i++;
	}
	return (1);
}

void	change_fdp(t_here_doc **x, int fdp)
{
	t_here_doc	*tmp;

	if (*x == NULL)
		*x = ft_lstnew0(fdp);
	else
	{
		tmp = *x;
		while (tmp->next)
			tmp = tmp->next;
		tmp->x = fdp;
	}
}
void	doc(int sin)
{
	if (sin == SIGINT)
		exit(44);
}

int	here_doc(char *dat, int j, t_data *data, t_minishell *mini, char **env)
{
	char	*tmp;
	int		fdp[2];
	int		i;
	char	*lim;

	i = 0;
	(void)j;
	(void)data;
	(void)mini;
	(void)env;
	pipe(fdp);
	lim = ft_strjoin(ft_strtrim_1(dat, "<"), "\n");
	if (fork() == 0)
	{
		signal(SIGINT, doc);
		while (1)
		{
			write(1, "> ", 2);
			tmp = get_next_line(0);
			
			if (!tmp || ft_strcmp1(tmp, lim))
				break ;
			mini->a = break_cmd(tmp, ' ');
			tmp = *expand_Path_2(mini->a, env);
			ft_putstr_fd(tmp, fdp[1]);
			free(tmp);
		}
		free(tmp);
		free(lim);
		exit(0);
	}
	else
	{
		waitpid(0, &i, 0);
		close(fdp[1]);
		if (WEXITSTATUS(i) == 44)
			return (1200);
	}
	return (fdp[0]);
}
