/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_commande.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:44:53 by khallal           #+#    #+#             */
/*   Updated: 2023/03/11 12:56:30 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_command(t_data *data, t_minishell *mini, t_here_doc **x,
		char **envc, t_list1 **m, t_list1 **export)
{
	int i;
	char **env;

	i = 0;
	(void)envc;
	env = list_tabl(m);
	// if (ft_strcmp(data->full_cmd[0], "exit"))
	// 	exit(ft_exit(data));
	//here_doc_open(&data, x, mini, env);
	if (is_builtin(data->full_cmd[0]))
		exit_status = builtin(data, m, export);
	else
	{
		mini->i = fork();
		if (mini->i == 0)
		{
			open_outfile(mini, data);
			open_infile_multiple(mini, data, x);
			if (mini->fd != -1)
				dup2(mini->fd, 0);
			else if ((*x) && (*x)->x != -1)
				dup2((*x)->x, 0);
			if (mini->fd1 != -1)
				dup2(mini->fd1, 1);
			if (data->full_cmd[0])
			{
				mini->k = split_path(env);
				mini->cmd = ft_access(mini->k, data->full_cmd[0]);
				if (execve(mini->cmd, data->full_cmd, NULL) == -1)
					(perror("\n"), exit(127));
			}
		}
		waitpid(mini->i, &i, 0);
		close(mini->fd1);
		exit_status = WEXITSTATUS(i);
	}
}