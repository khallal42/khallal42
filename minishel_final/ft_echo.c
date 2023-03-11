/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:41:41 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:42:14 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp1(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	while (i < n && (s3[i] != '\0' || s4[i] != '\0'))
	{
		if (s3[i] != s4[i])
		{
			return (s3[i] - s4[i]);
		}
		i++;
	}
	return (0);
}

int	ft_check_echo(char *str, char *ec)
{
	int	i;

	i = 2;
	if (!str)
		return (0);
	if (ft_strncmp1(str, ec, 2))
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data *data)
{
	int i;
	int j;

	i = 1;
	if ((data->full_cmd[1]) != NULL)
	{
		if (ft_check_echo(data->full_cmd[1], "-n"))
		{
			i++;
			while (ft_check_echo(data->full_cmd[i], "-n"))
				i++;
			while (data->full_cmd[i])
			{
				j = 0;
				while (data->full_cmd[i][j])
				{
					write(1, &data->full_cmd[i][j], 1);
					j++;
				}
				i++;
				if (data->full_cmd[i])
					write(1, " ", 1);
			}
		}
		else
		{
			while (data->full_cmd[i])
			{
				j = 0;
				while (data->full_cmd[i][j])
				{
					write(1, &data->full_cmd[i][j], 1);
					j++;
				}
				i++;
				if (data->full_cmd[i])
					write(1, " ", 1);
			}
			write(1, "\n", 1);
		}
	}
	return (0);
}