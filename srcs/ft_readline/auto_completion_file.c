/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:21:24 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 15:40:50 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

static int	loop(struct dirent **entry, char ***lst, int *i, DIR *dir)
{
	if ((*entry)->d_name[0] != '.')
	{
		(*lst)[(*i)] = ft_strdup((*entry)->d_name);
		if (!(*lst)[(*i)++])
			return (closedir(dir), -1);
	}
	(*entry) = readdir(dir);
	return (0);
}

static int	recup_dir(t_read_history **tmp, char ***lst, int *pos, int len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*str;
	int				i;

	str = NULL;
	i = count_dir(tmp, pos, len, &str);
	if (i < 0)
		return (-1);
	(*lst) = ft_calloc(sizeof(char *), i + 1);
	if (!(*lst))
		return (free(str), -1);
	dir = opendir(str);
	if (dir == NULL)
		return (free(str), -1);
	entry = readdir(dir);
	i = 0;
	while (entry)
		if (loop(&entry, lst, &i, dir))
			return (free(str), -1);
	closedir(dir);
	free(str);
	return (0);
}

static void	verif_seq2(char *seq, t_read_history **tmp, int *i, int *pos)
{
	if (seq[1] == '[')
	{
		if (seq[2] == '1' && seq[3] == 'C')
			which_key2(seq[5], tmp, i, pos);
		else if (seq[2] != 'D')
			which_key(seq[2], tmp, i, pos);
	}
}

static void	change_with_tab(t_read_history **tmp, int *i, int *pos, char **tab)
{
	char	c[6];
	int		k;
	int		j;

	k = 0;
	read(0, c, 6);
	while (c[0] == 9)
	{
		j = 0;
		if (!tab[k])
			k = 0;
		while (tab[k][j])
			print_char(tmp, i, pos, tab[k][j++]);
		k++;
		read(0, c, 6);
		if (c[0] == 9)
			while (j--)
				delete_char(tmp, i, pos);
		if (c[0] == 127)
			delete_char(tmp, i, pos);
		else if (c[0] == '\033')
			verif_seq2(c, tmp, i, pos);
		else if (ft_isprint(c[0]))
			print_char(tmp, i, pos, c[0]);
	}
}

void	monitor_completion_file(t_read_history **tmp, int *i, int *pos, int *j)
{
	int		len;
	char	**list;

	list = NULL;
	len = check_dir(tmp, pos);
	if (len < 0)
	{
		if (len == -2)
			autofinish_file(tmp, i, pos);
		clear_tab(*j, 1, pos);
		return ;
	}
	if (recup_dir(tmp, &list, pos, len))
	{
		free_tabtab(list);
		return ;
	}
	if (print_dir1(tmp, pos, len, j))
		return (free_tabtab(list), (void)0);
	change_with_tab(tmp, pos, i, list);
	free_tabtab(list);
}
