/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:38:35 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 16:40:01 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list1	*ft_lstnew1(char *content)
{
	t_list1	*head;

	head = malloc(sizeof(t_list1));
	head->data = content;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back1(t_list1 **lst, t_list1 *new)
{
	t_list1	*k;

	k = *lst;
	if (*lst != NULL)
	{
		while (k->next)
			k = k->next;
		k->next = new;
	}
	else
		*lst = new;
}

void	envcpy(char **env, t_list1 **m)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_lstadd_back1(m, ft_lstnew1(env[i]));
}

int	print_env(t_list1 **m)
{
	t_list1	*cpy;

	cpy = (*m);
	while (cpy)
	{
		printf("%s\n", cpy->data);
		cpy = cpy->next;
	}
	return (0);
}
