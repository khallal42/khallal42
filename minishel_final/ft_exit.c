/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:19:46 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:20:14 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_exit(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

int	ft_is_digit(char *k)
{
	int	i;

	i = 0;
	while (k[i])
	{
		if (k[i] < '0' || k[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data)
{
	if (data->full_cmd[1] == NULL)
		exit(0);
	if (data->full_cmd[1] && ft_is_digit(data->full_cmd[1])
		&& data->full_cmd[2] != NULL)
	{
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	if (data->full_cmd[1] && !ft_is_digit(data->full_cmd[1]))
	{
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	if (data->full_cmd[1] && data->full_cmd[2] == NULL
		&& ft_is_digit(data->full_cmd[1]))
	{
		exit_status = ft_atoi_exit(data->full_cmd[1]);
		exit(exit_status);
	}
	exit(0);
	return (0);
}
