/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:41:26 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 11:52:18 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

t_read_history	*create_history(void)
{
	t_read_history	*new;

	new = ft_calloc(sizeof(t_read_history), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->size = 2000;
	new->str = ft_calloc(new->size, 1);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	free_history(t_read_history **history)
{
	t_read_history	*tmp;

	while ((*history))
	{
		tmp = *history;
		*history = (*history)->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

static void	reset_and_go(struct termios old)
{
	reset_termios(&old);
	ft_fprintf(0, "\n");
}

static char	*cases(t_read_history *tmp, t_read_history **history,
		struct termios old)
{
	if (tmp->str[0] == 0)
	{
		delete_if_present(history, tmp->str);
		dbl_lst_delete(history);
		reset_and_go(old);
		return ("\n");
	}
	if (dbl_lst_last(history)->str[0] == 0)
	{
		dbl_lst_delete(history);
		move_to_last(history, tmp->str);
		reset_and_go(old);
		return (tmp->str);
	}
	if (ft_strcmp(tmp->str, dbl_lst_last(history)->str)
		&& dbl_lst_last(history)->str[0] != 0)
	{
		move_to_last(history, tmp->str);
		reset_and_go(old);
		return (tmp->str);
	}
	delete_if_present(history, tmp->str);
	reset_and_go(old);
	return (tmp->str);
}

char	*ft_readline(char *display, t_read_history **history, t_var **data)
{
	struct termios	new1;
	struct termios	old;
	t_read_history	*tmp;
	int				rt;

	if (dbl_lst_add_back(history, create_history()))
		return (NULL);
	tmp = dbl_lst_last(history);
	if (isatty(STDIN_FILENO))
		ft_fprintf(0, "%s", display);
	init_termios(&new1, &old);
	rt = ft_read(&tmp);
	if (rt == 1)
	{
		ft_fprintf(0, "\n");
		return (NULL);
	}
	else if (rt == 2)
	{
		ft_fprintf(0, "\n");
		update_res(130, data);
		dbl_lst_delete(history);
		return ("\n");
	}
	return (cases(tmp, history, old));
}
