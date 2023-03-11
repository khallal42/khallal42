#include "minishell.h"

t_here_doc	*ft_lstnew0(int content)
{
	t_here_doc	*node;

	node = malloc(sizeof(t_here_doc));
	if (node == NULL)
		return (NULL);
	node->x = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back3(t_here_doc **lst, t_here_doc *new)
{
	t_here_doc	*k;

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

int	ft_lstsize2(t_list1 *lst)
{
	int		i;
	t_list1	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**list_tabl(t_list1 **m)
{
	t_list1	*tmp;
	char	**envc;
	int		i;

	tmp = *m;
	i = 0;
	envc = malloc(sizeof(char *) * (ft_lstsize2(*m) + 1));
	while (tmp)
	{
		envc[i] = ft_strdup(tmp->data);
		tmp = tmp->next;
		i++;
	}
	envc[i] = 0;
	return (envc);
}
