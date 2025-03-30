/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_gest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:14:49 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/13 15:25:50 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

static void	move_left(int *pos)
{
	if (*pos)
	{
		ft_fprintf(1, "\033[D");
		(*pos)--;
	}
}

static void	move_right(int *pos, int *i)
{
	if (*pos < *i)
	{
		ft_fprintf(1, "\033[C");
		(*pos)++;
	}
}

static void	which_keyword(char seq, int *i, int *pos)
{
	if (seq == 'C')
		move_right(pos, i);
	if (seq == 'D')
		move_left(pos);
	if (seq == 'H')
	{
		while (*pos)
		{
			ft_fprintf(1, "\033[D");
			(*pos)--;
		}
	}
	if (seq == 'F')
	{
		while (*pos < *i)
		{
			ft_fprintf(1, "\033[C");
			(*pos)++;
		}
	}
}

void	verif_seq_doc(char *seq, int *i, int *pos)
{
	read(0, &seq[1], 1);
	if (seq[1] == '[')
	{
		read(0, &seq[2], 1);
		which_keyword(seq[2], i, pos);
	}
}
