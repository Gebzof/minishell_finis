/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:19:39 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:16:54 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

static void	move_prev_word2(t_read_history **lst, int *count, int *tmp)
{
	while ((*tmp) >= 0 && (ft_isalnum((*lst)->str[(*tmp)])
			|| (*lst)->str[(*tmp)] == '_' || (*lst)->str[(*tmp)--] == '$'))
	{
		(*count)++;
		(*tmp)--;
	}
}

static void	move_prev_word(t_read_history **lst, int *pos)
{
	int	count;
	int	tmp;

	count = 0;
	tmp = *pos - 1;
	if (tmp < 0)
		return ;
	if (ft_isalnum((*lst)->str[tmp])
		|| (*lst)->str[tmp] == '_' || (*lst)->str[tmp] == '$')
		move_prev_word2(lst, &count, &tmp);
	else
	{
		while (tmp >= 0 && !ft_isalnum((*lst)->str[tmp])
			&& (*lst)->str[tmp] != '_' && (*lst)->str[tmp--] != '$')
		{
			count++;
			tmp--;
		}
	}
	while (count--)
		move_left1(pos);
}

static void	move_next_word(t_read_history **lst, int *pos, int *i)
{
	int	count;
	int	tmp;

	count = 0;
	tmp = *pos;
	if (ft_isalnum((*lst)->str[tmp])
		|| (*lst)->str[tmp] == '_' || (*lst)->str[tmp] == '$')
	{
		while ((ft_isalnum((*lst)->str[tmp]) || (*lst)->str[tmp] == '_'
				|| (*lst)->str[tmp] == '$') && tmp++ < *i)
			count++;
	}
	else
	{
		while (!ft_isalnum((*lst)->str[tmp]) && (*lst)->str[tmp] != '_'
			&& (*lst)->str[tmp] != '$' && tmp++ < *i)
			count++;
	}
	while (count--)
		move_right1(pos, i);
}

void	which_key2(char seq, t_read_history **lst, int *i, int *pos)
{
	if (seq == 'D')
		move_prev_word(lst, pos);
	if (seq == 'C')
		move_next_word(lst, pos, i);
}
