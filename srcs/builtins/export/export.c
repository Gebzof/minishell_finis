/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:44:56 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/30 03:39:30 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

static	int	if_equal(char *value, t_var **new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (value[i] != '=')
		i++;
	(*new)->name = ft_calloc(1, i + 1);
	if (!(*new)->name)
	{
		perror(RED "Minishell: function: malloc failed\n" RESET);
		return (free((*new)), 1);
	}
	ft_strlcpy((*new)->name, value, i + 1);
	while (value[i + 1 + j])
		j++;
	(*new)->value = ft_calloc(1, j + 1);
	if (!(*new)->name)
	{
		perror(RED "Minishell: function: malloc failed\n" RESET);
		return (free((*new)->name), free((*new)), 1);
	}
	if (i + 1 < (int)ft_strlen(value))
		ft_strlcpy((*new)->value, &value[i + 1], j + 1);
	return (0);
}

static int	else_(char *value, t_var **new)
{
	int	i;

	i = 0;
	while (value[i])
		i++;
	(*new)->name = ft_calloc(1, i + 1);
	if (!(*new)->name)
	{
		perror(RED "Minishell: function: malloc failed\n" RESET);
		return (free((*new)), 1);
	}
	ft_strlcpy((*new)->name, value, i + 1);
	(*new)->value = ft_calloc(1, 2);
	if (!(*new)->value)
	{
		perror(RED "Minishell: function: malloc failed\n" RESET);
		return (1);
	}
	ft_strlcpy((*new)->value, "\t", 2);
	return (0);
}

static	int	update_var(t_var *new, t_var *tmp)
{
	if (new && !ft_strcmp(tmp->name, new->name))
	{
		if (!ft_strcmp(new->value, "\t") && tmp->value != NULL)
		{
			free(new->name);
			free(new->value);
			free(new);
			return (1);
		}
		free(tmp->value);
		tmp->value = new->value;
		free(new->name);
		free(new);
		new = NULL;
		return (1);
	}
	return (0);
}

static int	seperate_values(char *value, t_var *new, t_var *tmp, t_data *data)
{
	if (find_char(value, '='))
	{
		if (if_equal(value, &new))
			return (1);
	}
	else
		if (else_(value, &new))
			return (1);
	while (tmp && new)
	{
		if (update_var(new, tmp))
			return (0);
		tmp = tmp->next;
	}
	tmp = data->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int	run_export(t_data *data, char **values)
{
	t_var	*new;
	t_var	*tmp;
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (values[i] && values[i] != NULL)
	{
		while (values[i] != NULL && check_valid(values[i]))
		{
			error = 1;
			i++;
		}
		if (values[i])
		{
			tmp = data->env;
			new = ft_calloc(1, sizeof(t_var));
			if (!new || seperate_values(values[i], new, tmp, data))
				return (1);
			i++;
		}
	}
	return (error);
}
