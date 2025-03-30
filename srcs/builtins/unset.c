/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:39:46 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/30 03:40:03 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	lst_remove_first(t_var **lst)
{
	t_var	*rmv;
	
	if (!*lst)
		return ;
	rmv = *lst;
	*lst = (*lst)->next;
	rmv->next = NULL;
	free(rmv->name);
	free(rmv->value);
	free(rmv);
}

void	lst_remove(t_var **lst, char *name)
{
	t_var	*tmp;
	t_var	*rmv;

	if (!*lst)
		return ;
	if (!ft_strcmp((*lst)->name, name))
	{
		lst_remove_first(lst);
		return ;
	}
	tmp = *lst;
	while (tmp->next && ft_strcmp(tmp->next->name, name))
		tmp = tmp->next;
	if (tmp->next)
	{
		rmv = tmp->next;
		tmp->next = tmp->next->next;
		rmv->next = NULL;
		free(rmv->name);
		free(rmv->value);
		free(rmv);
	}
}

int	run_unset(t_data *data, char **value)
{
	t_var	*tmp;
	int		i;

	i = 0;
	while (value[i])
	{
		tmp = data->env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, value[i]))
			{
				lst_remove(&data->env, value[i]);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
