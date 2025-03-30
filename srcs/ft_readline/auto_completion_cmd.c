/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:32:16 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 15:51:56 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

static int	how_much_cmd(char *preset)
{
	DIR				*dir;
	struct dirent	*entry;
	int				len;

	len = 0;
	dir = opendir("/usr/bin");
	if (dir == NULL)
		return (-1);
	entry = readdir(dir);
	while (entry)
	{
		if (!ft_strncmp(entry->d_name, preset, ft_strlen(preset)))
			len++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (len);
}

static int	fill_tab_cmd(char *preset, char **tab)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	dir = opendir("/usr/bin");
	if (dir == NULL)
		return (-1);
	entry = readdir(dir);
	while (entry)
	{
		if (!ft_strncmp(entry->d_name, preset, ft_strlen(preset)))
		{
			tab[i] = ft_strdup(entry->d_name);
			if (!tab[i])
			{
				closedir(dir);
				return (-1);
			}
			i++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int	compare_tab(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[0] && tab[0][i])
	{
		j = 0;
		while (tab[j])
		{
			if (tab[j][i] != tab[0][i] || tab[j][i] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static int	init_complete(int *j, t_read_history **tmp, int *len, char **preset)
{
	while ((*j) >= 0 && (*tmp)->str[(*j)] != '/'
		&& (ft_isalpha((*tmp)->str[(*j)]) || (*tmp)->str[(*j)] == '_'))
	{
		(*j)--;
		(*len)++;
	}
	if ((*j) < 0)
		(*j)++;
	if ((*tmp)->str[(*j)] == '/')
		return (1);
	(*preset) = ft_calloc(1, (*len) + 1);
	if (!(*preset))
		return (1);
	ft_strlcpy((*preset), &(*tmp)->str[(*j)], (*len) + 1);
	(*len) = how_much_cmd((*preset));
	if ((*len) <= 0 || (*len) > 200)
	{
		free((*preset));
		return (1);
	}
	return (0);
}

int	complete_cmd(t_read_history **tmp, int *i, int *pos)
{
	int				j;
	int				len;
	char			*preset;
	char			**tab;

	len = 0;
	preset = NULL;
	j = *pos - 1;
	if (init_complete(&j, tmp, &len, &preset))
		return (-1);
	tab = ft_calloc(sizeof(char *), len + 1);
	if (!tab)
		return (free(preset), -1);
	fill_tab_cmd(preset, tab);
	len = compare_tab(tab);
	j = ft_strlen(preset);
	while (j < len)
	{
		print_char(tmp, i, pos, tab[0][j]);
		j++;
	}
	free_tabtab(tab);
	free(preset);
	return (0);
}
