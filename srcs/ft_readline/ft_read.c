/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:39:13 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:05:21 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

void	delete_char(t_read_history **current, int *i, int *pos)
{
	int				j;
	t_read_history	*tmp;

	tmp = *current;
	if ((*pos) > 0)
	{
		ft_memmove(&tmp->str[(*pos) - 1], &tmp->str[(*pos)], (*i) - (*pos) + 1);
		(*i)--;
		(*pos)--;
		ft_fprintf(0, "\033[D \033[D%s \033[D", &tmp->str[(*pos)]);
		j = (*pos);
		while (j < (*i))
		{
			ft_fprintf(0, "\033[D");
			j++;
		}
	}
}

void	print_char(t_read_history **current, int *i, int *pos, char seq)
{
	int				j;
	t_read_history	*tmp;

	tmp = *current;
	if (*i == tmp->size -1)
	{
		tmp->str = ft_realloc(tmp->str, tmp->size * 2, tmp->size);
		if (!tmp->str)
			return ;
		tmp->size = tmp->size * 2;
	}
	ft_memmove(&tmp->str[(*pos) + 1], &tmp->str[(*pos)], (*i) - (*pos) + 1);
	tmp->str[(*pos)] = seq;
	ft_fprintf(0, "%s", &tmp->str[(*pos)]);
	j = (*pos);
	while (j < (*i))
	{
		ft_fprintf(0, "\033[D");
		j++;
	}
	(*i)++;
	(*pos)++;
}

void	verif_seq(char *seq, t_read_history **tmp, int *i, int *pos)
{
	read(0, &seq[1], 1);
	if (seq[1] == '[')
	{
		read(0, &seq[2], 1);
		if (seq[2] == '1')
		{
			read(0, &seq[3], 3);
			which_key2(seq[5], tmp, i, pos);
		}
		else
			which_key(seq[2], tmp, i, pos);
	}
}

static void	init(int *i, int *j, int *pos, char *str)
{
	(*i) = 0;
	(*j) = 1;
	(*pos) = 0;
	ft_bzero(str, 6);
}

int	ft_read(t_read_history **tmp)
{
	int		i;
	int		pos;
	char	seq[6];
	int		j;
	int		rt;

	init(&i, &j, &pos, seq);
	while (1)
	{
		rt = read(0, &seq[0], 1);
		if (rt == 0 || (seq[0] == 4 && !(*tmp)->str[0]))
			return (clear_tab(j, 0, &pos), 1);
		if (rt != 1)
			return (clear_tab(j, 0, &pos), 2);
		if (seq[0] == 10)
			return (clear_tab(j, 0, &pos), 0);
		if (seq[0] == 9)
			auto_completion(tmp, &i, &pos, &j);
		if (seq[0] == 127)
			delete_char(tmp, &i, &pos);
		else if (seq[0] == '\033')
			verif_seq(seq, tmp, &i, &pos);
		else if (ft_isprint(seq[0]))
			print_char(tmp, &i, &pos, seq[0]);
	}
}
