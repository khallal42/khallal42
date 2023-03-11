/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:35:57 by khallal           #+#    #+#             */
/*   Updated: 2023/03/09 17:14:33 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_6(char *tmp, char *mv)
{
	int	i;

	i = 0;
	while (tmp[i] && mv[i] && tmp[i] != '=')
	{
		if (tmp[i] != mv[i])
			return (0);
		i++;
	}
	if (!mv[i])
		return (1);
	return (0);
}

int	ft_unset(t_list1 **head_ref, char *key)
{
	t_list1 *temp;
	t_list1 *first;
	t_list1 *prev;

	first = (*head_ref);
	temp = *head_ref;
	prev = *head_ref;
	if (temp != NULL && ft_strcmp_6(temp->data, key))
	{
		*head_ref = temp->next;
		free(temp);
		return (0);
	}
	while (temp != NULL && !ft_strcmp_6(temp->data, key))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	prev->next = temp->next;
	(*head_ref) = first;
	free(temp);
	return (0);
}
