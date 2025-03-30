/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:10:11 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/25 12:38:00 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

void	clear_tab(int j, int flag, int *pos)
{
	int	i;

	i = 0;
	while (i++ < j)
		ft_fprintf(0, "\n");
	while (j--)
	{
		ft_fprintf(0, "\033[K");
		ft_fprintf(0, "\033[A");
	}
	if (flag)
	{
		i = 0;
		while (i++ < 12 + *pos)
			ft_fprintf(0, "\033[C");
	}
}

int	string_not_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_iswhitespace(str[i++]))
			return (1);
	return (0);
}

int	check_dir(t_read_history **tmp, int *pos)
{
	int	j;
	int	count;

	count = 0;
	j = *pos - 1;
	if (j < 0)
		return (-1);
	if (string_not_empty((*tmp)->str) && (*tmp)->str[j] == ' ')
		return (0);
	if ((*tmp)->str[j] != '/')
		return (-2);
	while (--j >= 0 && (*tmp)->str[j] != ' ')
		count++;
	return (count);
}

static int	init_count(int *i, int *sub, int *len, char **str)
{
	(*i) = 0;
	(*sub) = (*len);
	(*str) = ft_calloc(1, (*sub) + 2);
	if (!(*str))
		return (-1);
	if (!(*len))
		(*len) = 1;
	return (0);
}

int	count_dir(t_read_history **tmp, int *pos, int len, char **str)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	int				sub;

	if (init_count(&i, &sub, &len, str))
		return (-1);
	ft_strlcpy((*str), &(*tmp)->str[(*pos) - 1 - sub], len + 1);
	if ((*str)[0] == ' ')
		(*str)[0] = '.';
	dir = opendir((*str));
	if (dir == NULL)
		return (free((*str)), -1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			i++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}
