/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:02:53 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/25 12:37:29 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

static void	change_history_up(t_read_history **lst, int *i, int *pos)
{
	if ((*lst)->prev)
	{
		(*lst) = (*lst)->prev;
		while (*pos < *i)
		{
			ft_fprintf(0, "\033[C");
			(*pos)++;
		}
		while (*i)
		{
			ft_fprintf(0, "\b \b");
			(*i)--;
		}
		ft_fprintf(0, "%s", (*lst)->str);
		(*i) = ft_strlen((*lst)->str);
		*pos = *i;
	}
}

static void	change_history_down(t_read_history **lst, int *i, int *pos)
{
	if ((*lst)->next)
	{
		(*lst) = (*lst)->next;
		while (*pos < *i)
		{
			ft_fprintf(0, "\033[C");
			(*pos)++;
		}
		while (*i)
		{
			ft_fprintf(0, "\b \b");
			(*i)--;
		}
		ft_fprintf(0, "%s", (*lst)->str);
		(*i) = ft_strlen((*lst)->str);
		*pos = *i;
	}
}

void	move_left1(int *pos)
{
	if (*pos)
	{
		ft_fprintf(0, "\033[D");
		(*pos)--;
	}
}

void	move_right1(int *pos, int *i)
{
	if (*pos < *i)
	{
		ft_fprintf(0, "\033[C");
		(*pos)++;
	}
}

void	which_key(char seq, t_read_history **lst, int *i, int *pos)
{
	if (seq == 'A')
		change_history_up(lst, i, pos);
	if (seq == 'B')
		change_history_down(lst, i, pos);
	if (seq == 'C')
		move_right1(pos, i);
	if (seq == 'D')
		move_left1(pos);
	if (seq == 'H')
	{
		while (*pos)
		{
			ft_fprintf(0, "\033[D");
			(*pos)--;
		}
	}
	if (seq == 'F')
	{
		while (*pos < *i)
		{
			ft_fprintf(0, "\033[C");
			(*pos)++;
		}
	}
}
