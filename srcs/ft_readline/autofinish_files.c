/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autofinish_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:17:05 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 15:39:26 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

static int	fill_tab_file(char *preset, char *path, char **tab)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	dir = opendir(path);
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

static int	how_much_files(char *preset, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				len;

	len = 0;
	dir = opendir(path);
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

static int	fill_preset(t_read_history **tmp, int *pos, char **preset)
{
	int	j;
	int	count;

	j = *pos - 1;
	count = 0;
	while (j >= 0 && (*tmp)->str[j] != '/' && (*tmp)->str[j] != ' ')
	{
		count++;
		j--;
	}
	(*preset) = ft_calloc(1, count + 1);
	if (!(*preset))
		return (1);
	ft_strlcpy((*preset), &(*tmp)->str[*pos - count], count + 1);
	return (0);
}

static int	fill_path(t_read_history **tmp, int *pos, char **path, char *preset)
{
	int	j;
	int	count;

	j = *pos - 1;
	count = 0;
	while (j >= 0 && (*tmp)->str[j] != '/' && (*tmp)->str[j] != ' ')
	{
		count++;
		j--;
	}
	while (j >= 0 && (*tmp)->str[j] != ' ')
	{
		count++;
		j--;
	}
	(*path) = ft_calloc(1, count + 1);
	if (!(*path))
		return (1);
	ft_strlcpy((*path), &(*tmp)->str[*pos - count],
		count + 1 - ft_strlen(preset));
	if ((*path)[0] == '\0')
		(*path)[0] = '.';
	return (0);
}

void	autofinish_file(t_read_history **tmp, int *i, int *pos)
{
	int		j;
	char	**tab;
	char	*preset;
	char	*path;

	if (!string_not_empty((*tmp)->str))
		return ;
	if (fill_preset(tmp, pos, &preset))
		return ;
	if (fill_path(tmp, pos, &path, preset))
		return (free(preset), (void)0);
	j = how_much_files(preset, path);
	if (!j)
		return (free(path), free(preset), (void)0);
	tab = ft_calloc(sizeof(char *), j + 1);
	if (!tab)
		return (free(path), free(preset), (void)0);
	if (fill_tab_file(preset, path, tab))
		return (free_tabtab(tab), free(path), free(preset), (void)0);
	j = ft_strlen(preset);
	while (j < compare_tab(tab))
		print_char(tmp, i, pos, tab[0][j++]);
	free_tabtab(tab);
	free(path);
	free(preset);
}
