/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:16:10 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/29 03:53:04 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*give_str_env(char *str, t_data *mini)
{
	t_var	*current;

	current = mini->env;
	while (current)
	{
		if (!ft_strcmp(str, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static int	check_str_env(char *str, t_data *mini)
{
	t_var	*current;
	int		count;

	current = mini->env;
	count = 0;
	while (current)
	{
		if (!ft_strcmp(str, current->name))
			count = ft_strlen(current->value);
		current = current->next;
	}
	return (count);
}

static char	*size_of_var(char *line, int *i)
{
	int		j;
	char	*var;

	j = 0;
	(*i)++;
	if (!line[*i])
		return (NULL);
	while (line[*i + j] && line[*i + j] != ' '
		&& line[*i + j] != '\"' && line[*i + j] != '$')
		j++;
	var = ft_calloc(sizeof(char), j + 1);
	if (!var)
		return (NULL);
	j = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\"' && line[*i] != '$')
	{
		var[j] = line[*i];
		(*i)++;
		j++;
	}
	return (var);
}

int	len(char *line, t_data *mini)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	if (!line || !line[i])
		return (0);
	while (line[i])
	{
		if (line[i] == '\'')
		{
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '$')
		{
			var = size_of_var(line, &i);
			j += check_str_env(var, mini);
			free(var);
		}
		if (line[i])
			i++;
	}
	return (j + i + 1);
}

char	*on_a_dollard(char *line, int *i, char *newline, t_data *mini)
{
	char	*var;

	var = size_of_var(line, i);
	if (!var || !ft_isprint(var[0]))
	{
		newline = ft_join_free(newline, (char []){line[*i - 1], '\0'});
		free(var);
		var = NULL;
	}
	else
	{
		newline = ft_join_free(newline, give_str_env(var, mini));
		free(var);
		var = NULL;
	}
	if (!newline)
		return (NULL);
	if (line[*i])
		(*i)--;
	return (newline);
}
