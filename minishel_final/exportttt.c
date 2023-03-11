// #include "minishell.h"

// char	*check_ex_(t_list1 **m, char *str)
// {
//     printf("----------%p\n", str);
// 	char	*k;
// 	t_list1	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = (*m);
// 	while (tmp)
// 	{
// 		k = tmp->data;
// 		while (str[i] && k[i] && k[i] == str[i] && str[i] != '=')
// 			i++;
// 		if (str[i] == '=')
// 			return (k);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }
// int	ft_strcmp_ex(char *tmp, char *mv)
// {
// 	int	i;

// 	i = 0;
// 	while (tmp[i] && mv[i] && mv[i] != '+')
// 	{
// 		if (tmp[i] != mv[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
// char	*cherch(t_list1 **m, char *str)
// {
// 	t_list1	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = *m;
// 	while (tmp)
// 	{
// 		if (ft_strcmp_ex(tmp->data, str))
// 			return (tmp->data);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// char	*ft_add(char *add, t_list1 **m)
// {
// 	int		i;
// 	char	*leak;

// 	leak = cherch(m, add);
// 	i = 0;
// 	while (add[i] != '=')
// 		i++;
// 	i++;
// 	return (ft_strjoin0(leak, &add[i]));
// }

// void	print_exp_oonly(t_list1 **m)
// {
// 	t_list1	*tmp;
// 	int		i;
// 	int		j;
// 	char	*k;

// 	j = 0;
// 	tmp = (*m);
// 	while (tmp)
// 	{
// 		printf("declare -x ");
// 		k = tmp->data;
// 		i = 0;
// 		while (k[i])
// 		{
// 			if (k[i] != '=')
// 				printf("%c", k[i]);
// 			else if (k[i] == '=')
// 			{
// 				printf("=\"");
// 				j = 1;
// 			}
// 			if (k[i + 1] == '\0' && j == 1)
// 			{
// 				printf("\"\n");
// 				j = 0;
// 				break ;
// 			}
// 			else if (k[i + 1] == '\0' && j == 0)
// 				printf("\n");
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }

// int	check(char *k)
// {
// 	int	i;

// 	i = 0;
// 	if ((k[0] >= '0' && k[0] <= '9') || k[0] == '=')
// 		return (0);
// 	while (k[i] && k[i] != '=')
// 	{
// 		if ((k[i] < 65 || k[i] > 90) && (k[i] < 97 || k[i] > 122) && (k[i] < '0'
// 				|| k[i] > '9') && k[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
// int	check11(char *k)
// {
// 	int	i;

// 	i = 0;
// 	if ((k[0] >= '0' && k[0] <= '9') || k[0] == '=')
// 		return (0);
// 	while (k[i] && k[i] != '=')
// 	{
// 		if ((k[i] < 65 || k[i] > 90) && (k[i] < 97 || k[i] > 122) && (k[i] < '0'
// 				|| k[i] > '9') && k[i] != '_' && k[i] != '+')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	check_data(t_data *data, int i)
// {
// 	if (ft_strchr(data->full_cmd[i], '='))
// 	{
// 		if (check(data->full_cmd[i]))
// 		{
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
// int	check_data11(t_data *data, int i)
// {
// 	if (ft_strchr(data->full_cmd[i], '='))
// 	{
// 		if (check11(data->full_cmd[i]))
// 		{
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// char	*uns(char *k)
// {
// 	char	*l;
// 	int		i;

// 	i = 0;
// 	while (k[i] != '=')
// 		i++;
// 	l = malloc(i + 1);
// 	i = 0;
// 	while (k[i] != '=')
// 	{
// 		l[i] = k[i];
// 		i++;
// 	}
// 	l[i] = '\0';
// 	return (l);
// }

// char	*check_ex_add(t_list1 **m, char *str)
// {
// 	char	*k;
// 	t_list1	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = (*m);
// 	while (tmp)
// 	{
// 		k = tmp->data;
// 		while (str[i] && k[i] && k[i] == str[i] && (str[i] != '+' && str[i
// 				+ 1] != '='))
// 			i++;
// 		if (str[i] == '+' && str[i + 1] == '=')
// 			return (k);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// char	*ft_rem_plus(char *k)
// {
// 	int		i;
// 	char	*l;
// 	int		j;
// 	int		x;

// 	x = 0;
// 	i = 0;
// 	j = 0;
// 	while (k[i])
// 		i++;
// 	l = malloc(i);
// 	i = 0;
// 	while (k[i])
// 	{
// 		if (k[i] != '+' || x == 1)
// 		{
// 			l[j] = k[i];
// 			j++;
// 		}
// 		if (k[i] == '+')
// 			x = 1;
// 		i++;
// 	}
// 	l[j] = '\0';
// 	return (l);
// }

// char	*plus_egal(char *k)
// {
// 	char	*l;
// 	int		i;

// 	i = 0;
// 	while (k[i] != '+')
// 		i++;
// 	l = malloc(i + 1);
// 	i = 0;
// 	while (k[i] != '+')
// 	{
// 		l[i] = k[i];
// 		i++;
// 	}
// 	l[i] = '\0';
// 	return (l);
// }

// int	check_pleg(char *k)
// {
// 	int	i;

// 	i = 0;
// 	while (k[i + 1])
// 	{
// 		if (k[i] == '+' && k[i + 1] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	export1(char *k, t_list1 **m, t_list1 **export)
// {
// 	t_list1	*new;
// 	t_list1	*tmp;
// 	t_list1	*tmp1;

// 	new = ft_lstnew1(k);
// 	tmp = (*m);
// 	while (tmp->next->next)
// 		tmp = tmp->next;
// 	tmp1 = tmp->next;
// 	new->next = tmp1;
// 	tmp->next = new;
// 	//==========================================//
// 	new = ft_lstnew1(k);
// 	tmp = (*export);
// 	while (tmp->next->next)
// 		tmp = tmp->next;
// 	tmp1 = tmp->next;
// 	new->next = tmp1;
// 	tmp->next = new;
// 	//==========================================//
// }
// void	export2(t_list1 **m, t_list1 **export, char *k)
// {
// 	t_list1	*new;
// 	t_list1	*tmp;
// 	t_list1	*tmp1;

// 	if (!check_ex_(m, k))
// 	{
// 		new = ft_lstnew1(k);
// 		tmp = (*export);
// 		while (tmp->next->next)
// 			tmp = tmp->next;
// 		tmp1 = tmp->next;
// 		new->next = tmp1;
// 		tmp->next = new;
// 	}
// }

// void	export3(t_list1 **m, t_list1 **export, t_data *data, int i)
// {
// 	char	*k;

// 	k = NULL;
// 	if (check_ex_add(m, data->full_cmd[i]))
// 	{
// 		if (cherch(m, data->full_cmd[i]))
// 		{
// 			k = ft_add(data->full_cmd[i], m);
// 			ft_unset(m, plus_egal(data->full_cmd[i]));
// 			ft_unset(export, plus_egal(data->full_cmd[i]));
// 			export1(data->full_cmd[i], m, export);
// 		}
// 	}
// 	else if (!check_ex_add(m, data->full_cmd[i]) && !cherch(m,
// 				data->full_cmd[i]) && check_data11(data, i)
// 			&& check_pleg(data->full_cmd[i]))
// 	{
// 		k = ft_rem_plus(k);
// 		export1(k, m, export);
// 	}
// }

// void	ft_export(t_data *data, t_list1 **m, t_list1 **export)
// {
// 	int i = 1;

// 	while (data->full_cmd[i])
// 	{
// 		export3(m, export, data, i);
// 		if (check_data(data, i))
// 		{
// 			if (check_ex_(m, data->full_cmd[i]))
// 			{
// 				ft_unset(m, uns(data->full_cmd[i]));
// 				ft_unset(export, uns(data->full_cmd[i]));
// 				export1(data->full_cmd[i], m, export);
// 			}
// 			else
// 				export1(data->full_cmd[i], m, export);
// 		}
// 		else if (check(data->full_cmd[i]))
// 			export2(m, export, data->full_cmd[i]);
// 		i++;
// 	}
// }