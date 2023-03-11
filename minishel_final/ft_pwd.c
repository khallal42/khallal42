/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:20:40 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:20:41 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[255];

	if (getcwd(buffer, 255) == NULL)
	{
		perror("");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
