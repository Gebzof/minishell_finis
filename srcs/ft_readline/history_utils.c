/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:04:13 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/13 15:52:41 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

t_read_history	*dbl_lst_last(t_read_history **lst)
{
	t_read_history	*tmp;

	if (!(*lst))
		return (NULL);
	if (!(*lst)->next)
		return ((*lst));
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	dbl_lst_add_back(t_read_history **head, t_read_history *new)
{
	t_read_history	*tmp;

	if (!new)
		return (1);
	tmp = dbl_lst_last(head);
	if (!tmp)
	{
		*head = new;
		return (0);
	}
	tmp->next = new;
	new->prev = tmp;
	return (0);
}

void	dbl_lst_delete(t_read_history **history)
{
	t_read_history	*tmp;

	tmp = dbl_lst_last(history);
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = NULL;
	else
		*history = NULL;
	free(tmp->str);
	free(tmp);
}

void	delete_if_present(t_read_history **history, char *str)
{
	t_read_history	*tmp;
	t_read_history	*tmp2;
	t_read_history	*tmp3;

	tmp = *history;
	while (ft_strcmp(str, tmp->str) && tmp->next)
		tmp = tmp->next;
	if (!tmp->next)
		return ;
	if (!tmp->prev)
	{
		*history = tmp->next;
		(*history)->prev = NULL;
	}
	else
	{
		tmp2 = tmp->prev;
		tmp3 = tmp->next;
		tmp2->next = tmp3;
		tmp3->prev = tmp2;
	}
	free(tmp->str);
	free(tmp);
}

void	move_to_last(t_read_history **history, char *str)
{
	t_read_history	*tmp;
	t_read_history	*last;

	tmp = *history;
	while (tmp && ft_strcmp(str, tmp->str))
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (!tmp->next)
		return ;
	if (!tmp->prev)
	{
		*history = tmp->next;
		(*history)->prev = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	tmp->next = NULL;
	last = dbl_lst_last(history);
	last->next = tmp;
	tmp->prev = last;
}
