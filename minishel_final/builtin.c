/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:49:21 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:49:59 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *tmp, char *mv)
{
	int	i;

	i = 0;
	if (!tmp)
		return (0);
	while ((tmp[i] || mv[i]))
	{
		if (tmp[i] != mv[i])
			return (0);
		else
			i++;
	}
	return (1);
}

int	is_builtin(char *k)
{
	if (ft_strcmp(k, "export"))
		return (1);
	else if (ft_strcmp(k, "env"))
		return (1);
	else if (ft_strcmp(k, "cd"))
		return (1);
	else if (ft_strcmp(k, "pwd"))
		return (1);
	else if (ft_strcmp(k, "unset"))
		return (1);
	else if (ft_strcmp(k, "exit"))
		return (1);
	else if (ft_strcmp(k, "echo"))
		return (1);
	else if (ft_strcmp(k, "."))
		return (1);
	else
		return (0);
}

int	builtin(t_data *data, t_list1 **m, t_list1 **export)
{
	if (ft_strcmp(data->full_cmd[0], "env"))
		return (print_env(m));
	if (ft_strcmp(data->full_cmd[0], "echo"))
		return (ft_echo(data));
	if (ft_strcmp(data->full_cmd[0], "cd"))
		return (ft_cd1(m, data));
	if (ft_strcmp(data->full_cmd[0], "pwd"))
		return (ft_pwd());
	if (ft_strcmp(data->full_cmd[0], "unset"))
		return (ft_unset(m, data->full_cmd[1]));
	if (ft_strcmp(data->full_cmd[0], "export") && data->full_cmd[1] == NULL)
		return (print_exp_oonly(export));
	if (ft_strcmp(data->full_cmd[0], "export") && data->full_cmd[1] != NULL)
		return (ft_export(data, m, export));
	if (ft_strcmp(data->full_cmd[0], "exit"))
		return (ft_exit(data));
	if (ft_strcmp(data->full_cmd[0], "."))
	{
		write(2, ".: filename argument required\n", 31);
		return (2);
	}
	return (0);
}