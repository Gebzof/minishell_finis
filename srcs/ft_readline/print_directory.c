/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:36:21 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/25 12:38:30 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

static void	loop(int term_width, struct dirent **entry, int *i, int *j)
{
	int	len;

	len = ft_strlen((*entry)->d_name);
	if ((*i) + len >= term_width)
	{
		ft_fprintf(0, "\n");
		(*i) = 0;
		(*j)++;
	}
	ft_fprintf(0, "%s", (*entry)->d_name);
	(*i) += len;
	if ((*i) + 4 >= term_width)
	{
		ft_fprintf(0, "\n");
		(*i) = 0;
		(*j)++;
	}
	else
	{
		ft_fprintf(0, "    ");
		(*i) += 4;
	}
}

static void	print_dir(int term_width, int *j, int *pos, DIR *dir)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	ft_fprintf(0, "\n");
	entry = readdir(dir);
	(*j) = 1;
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			loop(term_width, &entry, &i, j);
		entry = readdir(dir);
	}
	i = 0;
	while (i++ < *j)
		ft_fprintf(0, "\033[A");
	while (term_width--)
		ft_fprintf(0, "\033[D");
	i = 0;
	while (i++ < 12 + *pos)
		ft_fprintf(0, "\033[C");
}

int	print_dir1(t_read_history **tmp, int *pos, int len, int *j)
{
	DIR				*dir;
	struct winsize	w;
	char			*str;
	int				sub;

	sub = len;
	str = ft_calloc(1, sub + 2);
	if (!str)
		return (-1);
	if (!len)
		len = 1;
	ft_strlcpy(str, &(*tmp)->str[(*pos) - 1 - sub], len + 1);
	if (str[0] == ' ')
		str[0] = '.';
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	dir = opendir(str);
	if (dir == NULL)
		return (free(str), -1);
	clear_tab(*j, 0, pos);
	print_dir(w.ws_col, j, pos, dir);
	closedir(dir);
	free(str);
	return (0);
}

void	auto_completion(t_read_history **tmp, int *i, int *pos, int *j)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	complete_cmd(tmp, i, pos);
	monitor_completion_file(tmp, i, pos, j);
}
