/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:23:23 by khallal           #+#    #+#             */
/*   Updated: 2023/03/11 15:24:13 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_un(char *tmp, char *mv)
{
	int	i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp[i] && mv[i] && tmp[i] != '=')
	{
		if (tmp[i] != mv[i])
			return (0);
		i++;
	}
	return (1);
}

char	**split_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strcmp_un(env[i], "PATH"))
		i++;
	if (ft_strcmp_un(env[i], "PATH"))
		return (ft_split(&env[i][5], ':'));
	else if (!env[i])
	{
		write(1, "path not exist", 15);
		return (NULL);
	}
	else
		return (NULL);
}

char	*ft_access(char **s_path, char *cmd)
{
	char	*k;
	int		i;

	i = 0;
	if (!s_path)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == -1)
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (s_path[i])
	{
		k = ft_strjoin0(s_path[i], "/");
		k = ft_strjoin0(k, cmd);
		if (access(k, X_OK) == 0)
			return (k);
		i++;
	}
	return (NULL);
}
