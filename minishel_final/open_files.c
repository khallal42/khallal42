/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:12:15 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/01 11:25:42 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_open(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (1);
	return (0);
}

int	count_inf_open(char **av, int b, int y)
{
	int i;
	int j;
	int c;
	int fd;

	c = 0;
	i = 0;
	j = 0;
	while (av[b] && b < y)
	{
		if (ft_strcmp_1(av[b], "<") == 0)
		{
			fd = open(av[b + 1], O_RDONLY);
			if (fd == -1)
				break ;
			else if (fd != -1)
			{
				b += 1;
				close(fd);
			}
		}
		if (ft_strcmp_1(av[b], ">>") == 0)
		{
			c++;
			b += 1;
		}
		if (ft_strcmp_1(av[b], ">") == 0)
		{
			c++;
			b += 1;
		}
		b++;
	}
	return (c);
}