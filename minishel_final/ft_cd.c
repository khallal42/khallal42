/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:27:06 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:34:31 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_fenv(t_list1 **m)
{
	t_list1	*tmp;
	char	buffer[255];
	char	*k;

	tmp = *m;
	while (tmp)
	{
		if (ft_strcmp_un(tmp->data, "PWD"))
		{
			k = tmp->data;
			if (getcwd(buffer, 255) == NULL)
				perror("getcwd() error");
			tmp->data = ft_strjoin0("PWD=", buffer);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = *m;
	while (tmp)
	{
		if (ft_strcmp_un(tmp->data, "OLDPWD"))
		{
			tmp->data = ft_strjoin0("OLD", k);
			break ;
		}
		tmp = tmp->next;
	}
}

char	*cd_home(t_list1 **m)
{
	t_list1	*tmp;

	tmp = *m;
	while (tmp)
	{
		if (ft_strcmp_un(tmp->data, "HOME"))
			return (tmp->data + 5);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*old_pwd(t_list1 **m)
{
	t_list1	*tmp;

	tmp = *m;
	while (tmp)
	{
		if (!ft_strncmp1(tmp->data, "OLDPWD", 6))
			return (tmp->data + 7);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_cd1(t_list1 **m, t_data *data)
{
	int		i;
	char	*newdir;

	newdir = data->full_cmd[1];
	if (newdir == NULL)
	{
		newdir = cd_home(m);
		if (newdir == NULL)
		{
			write(2, "cd: HOME not set\n", 18);
			return (1);
		}
	}
	if (ft_strcmp(newdir, "-") && old_pwd(m))
	{
		newdir = old_pwd(m);
		ft_pwd();
	}
	if (ft_strcmp(newdir, "."))
		return (0);
	i = chdir(newdir);
	if (i != 0)
	{
		perror("");
		return (1);
	}
	change_fenv(m);
	return (0);
}
