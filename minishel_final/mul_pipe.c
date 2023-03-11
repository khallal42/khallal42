#include "get_next_line.h"
#include "minishell.h"

int	here_doc_open(t_data **data, t_here_doc **x, t_minishell *mini, char **env)
{
	t_data	*tmp;
	int		j;

	j = -2;
	tmp = *data;
	while (tmp)
	{
		mini->j = 0;
		while (check_heredoc(tmp->infile, mini->j))
		{
			if (tmp->infile[mini->j][0] == '<'
				&& tmp->infile[mini->j][1] == '<')
			{
				j != -2 && close(j);
				j = here_doc(tmp->infile[mini->j], mini->j, tmp, mini, env);
				if (j == 1200)
					return (1);
			}
			else
			{
				mini->fd = open(tmp->infile[mini->j], O_RDONLY);
				if (mini->fd == -1)
					mini->fail_open = 1;
				mini->fd = -1;
			}
			mini->j++;
		}
		if (j != -2)
			ft_lstadd_back3(x, ft_lstnew0(j));
		j = -2;
		tmp = tmp->next;
	}
	return (0);
}

void	open_infile_multiple(t_minishell *mini, t_data *data, t_here_doc **x)
{
	if (mini->fail_open == 1)
		(write(2, "  : no such file or directory1\n", 32), exit(1));
	if (data->infile != NULL)
	{
		mini->j = 0;
		while (data->infile[mini->j])
		{
			while (data->infile[mini->j] && data->infile[mini->j][0] == '<'
				&& data->infile[mini->j][1] == '<')
			{
				mini->fd = (*x)->x;
				mini->j++;
			}
			if (data->infile[mini->j])
			{
				mini->fd = open(data->infile[mini->j], O_RDONLY);
				if (mini->fd == -1)
					(perror("3"), exit(1));
				mini->j++;
			}
		}
	}
}
void	first_command(t_minishell *mini, t_data *data, t_here_doc **x,
		char **env, t_list1 **m, t_list1 **export)
{
	mini->j = 0;
	open_outfile(mini, data);
	open_infile_multiple(mini, data, x);
	close(mini->fdp[0]);
	if (mini->fd != -1)
		dup2(mini->fd, 0);
	if (mini->fd1 != -1)
		dup2(mini->fd1, 1);
	else
		dup2(mini->fdp[1], 1);
	if (data->full_cmd[0])
	{
		mini->k = split_path(env);
		mini->cmd = ft_access(mini->k, data->full_cmd[0]);
		if (is_builtin(data->full_cmd[0]))
			exit_status = builtin(data, m, export);
		else
		{
			if (execve(mini->cmd, data->full_cmd, NULL) == -1)
				(perror("11"), exit(127));
		}
		exit(exit_status);
	}
}

void	last_command(t_minishell *mini, t_data *data, t_here_doc **x,
		char **env, t_list1 **m, t_list1 **export)
{
	open_outfile(mini, data);
	if (mini->fd1 != -1)
		dup2(mini->fd1, 1);
	close(mini->fdp[1]);
	open_infile_multiple(mini, data, x);
	if (mini->fd != -1)
		dup2(mini->fd, 0);
	else
		dup2(mini->fdp[0], 0);
	if (data->full_cmd[0])
	{
		mini->k = split_path(env);
		mini->cmd = ft_access(mini->k, data->full_cmd[0]);
		if (is_builtin(data->full_cmd[0]))
			exit_status = builtin(data, m, export);
		else
		{
			if (execve(mini->cmd, data->full_cmd, NULL) == -1)
				(perror("11"), exit(127));
		}
		exit(exit_status);
	}
}

void	EXITSTATUS(int *k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 1)
	{
		waitpid(k[j], &i, 0);
		j++;
	}
	exit_status = WEXITSTATUS(i);
}

void	print_ids(int *k)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("!!!!!!!%d\n", k[i]);
		i++;
	}
}

void	mul_pipe(t_data *data, t_here_doc **x, t_minishell *mini, char **envc,
		t_list1 **m, t_list1 **export)
{
	int i = 0;
	(void)envc;
	char **env = list_tabl(m);
	mini->exits = malloc(sizeof(int) * 1 /*l_lstsize(data)*/);
	pipe(mini->fdp);
	//here_doc_open(&data, x, mini, env);
	mini->i = fork();
	if (mini->i == 0)
		first_command(mini, data, x, env, m, export);
	else
	{
		if (check_heredoc(data->infile, 0))
			(*x) = (*x)->next;
		data = data->next;
		close(mini->fdp[1]);
		mini->track = mini->fdp[0];
		while (data->next)
		{
			if (pipe(mini->fdp) == -1)
				(perror("1"), exit(1));
			mini->i = fork();
			if (mini->i == 0)
			{
				close(mini->fdp[0]);
				mini->j = 0;
				open_outfile(mini, data);
				open_infile_multiple(mini, data, x);
				if (mini->fd != -1)
					dup2(mini->fd, 0);
				else
					dup2(mini->track, 0);
				if (mini->fd1 != -1)
					dup2(mini->fd1, 1);
				else
					dup2(mini->fdp[1], 1);
				if (data->full_cmd[0])
				{
					mini->k = split_path(env);
					mini->cmd = ft_access(mini->k, data->full_cmd[0]);
					if (is_builtin(data->full_cmd[0]))
						exit_status = builtin(data, m, export);
					else
					{
						if (execve(mini->cmd, data->full_cmd, NULL) == -1)
							(perror("11"), exit(127));
					}
					exit(exit_status);
				}
			}
			else
			{
				close(mini->fdp[1]);
				close(mini->track);
				mini->track = mini->fdp[0];
				if (check_heredoc(data->infile, 0))
					(*x) = (*x)->next;
				data = data->next;
			}
		}
		mini->i = fork();
		mini->exits[i++] = mini->i;
		if (mini->i == 0)
			last_command(mini, data, x, env, m, export);
	}
	close(mini->track);
	close(mini->fdp[1]);
	close(mini->fdp[0]);
	EXITSTATUS(mini->exits);
	while (waitpid(0, NULL, 0) != -1)
		;
}