/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:10:51 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 11:44:02 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_var	*lst_new(char *name, char *value)
{
	t_var	*new;

	new = ft_calloc(sizeof(t_var), 1);
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
		return (NULL);
	return (new);
}

t_var	*ft_lstlast_var(t_var *tmp)
{
	t_var	*lst;

	lst = tmp;
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_var *head, t_var *new)
{
	t_var	*tmp;

	if (!new)
		return ;
	tmp = head;
	while (tmp && tmp->next && ft_strcmp(tmp->name, new->name))
		tmp = tmp->next;
	if (!tmp)
		return (head = new, (void)0);
	if (!ft_strcmp(tmp->name, new->name))
	{
		free(new->name);
		free(new->value);
		free(new);
		return ;
	}
	tmp->next = new;
}

void	lst_add_front(t_var **head, t_var *new)
{
	if (!new)
		return ;
	if (!head)
	{
		(*head) = new;
		return ;
	}
	new->next = (*head);
	(*head) = new;
}

int	ft_lst_count(t_var *lst)
{
	int		i;
	t_var	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
