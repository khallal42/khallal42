/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:41:36 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/11 14:29:35 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last(t_here_doc **her)
{
	t_here_doc	*tmp;

	if (*her == NULL)
		return (-1);
	tmp = *her;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->x);
}

int	ft_check_empt(char *s)
{
	int	i;

	i = 0;
	if (s && s[i] != '\0' && s[i] != '\n')
		return (1);
	exit_status = 0;
	return (0);
}

void	init(t_minishell *mini)
{
	mini->a = NULL;
	mini->fd = -1;
	mini->fd1 = -1;
	mini->j = 0;
	mini->her = 1;
	mini->fail_open = 0;
	mini->q = 0;
	mini->track = 0;
	mini->k = NULL;
	mini->cmd = NULL;
}

char	*handle_global_signal_1(void)
{
	struct termios	term;
	char			*line;
	struct termios	oldterm;

	(void)signal;
	tcgetattr(0, &term);
	oldterm = term;
	// term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	line = readline(("minishell $> "));
	// tcsetattr(0, TCSANOW, &oldterm);
	return (line);
}

void	handle_global_signal(int sig)
{
	sig = 1;
	write(1, "\n", 1);
	// if (g_vars.line_handled == 0)
	// {
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	// }
	// g_vars.last_exit_sat = 1;
}

int	main(int ac, char **av, char **env)
{
	t_prompt	prompt;
	t_data		*data;
	t_here_doc	*x;
	t_minishell	*mini;
	t_list1		*m;
	t_list1		*export;
	int			i;

	i = 0;
	mini = malloc(sizeof(t_minishell));
	x = NULL;
	(void)ac;
	(void)av;
	envcpy(env, &m);
	envcpy(env, &export);
	signal(SIGINT, handle_global_signal);
	while (1)
	{
		init(mini);
		data = NULL;
		prompt.cmds = handle_global_signal_1();
		if (prompt.cmds == NULL)
			exit(1);
		if (ft_check_empt(prompt.cmds) == 1)
		{
			add_history(prompt.cmds);
			mini->a = break_cmd(prompt.cmds, ' ');
			divide_input_2(mini->a, &data, env);
		}
		//printf("{{{{%s}}}}\n", data->full_cmd[0]);
		// printf("{{{{%s}}}}\n", data->full_cmd[1]);
		i = here_doc_open(&data, &x, mini, env);
		if (i == 0)
		{
			exit_status = 0;
			if (l_lstsize(data) == 1)
				one_command(data, mini, &x, env, &m, &export);
			if (l_lstsize(data) >= 2)
				mul_pipe(data, &x, mini, env, &m, &export);
		}
		else
			exit_status = 1;
		while(x)
		{
			close(x->x);
			x = x->next;
		}
	}
}

// signal(SIGINT, handle_global_signal);
// prompt.cmds = handle_global_signal_1();
// void handle_global_signal_1(void)
// {
//     struct termios term;
//     struct termios oldterm;
//     charline;
//     (void)signal;

//     tcgetattr(0, &term);
//     oldterm = term;
//     // term.c_cc[VQUIT] = _POSIX_VDISABLE;
//     term.c_lflag &= ~ECHOCTL;
//     tcsetattr(0, TCSANOW, &term);
//     line = readline(("minishell $> "));
//     // tcsetattr(0, TCSANOW, &oldterm);
//     return (line);
// }

// void handle_global_signal(int sig)
// {
//     sig = 1;
//     write(1, "\n", 1);
//     // if (g_vars.line_handled == 0)
//     // {
//     rl_replace_line("", 1);
//     rl_on_new_line();
//     rl_redisplay();
//     // }
//     // g_vars.last_exit_sat = 1;
// }