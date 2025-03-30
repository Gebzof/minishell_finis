/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:52:17 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/30 03:39:23 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

int	find_char(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			j++;
		i++;
	}
	return (j);
}

static int	alloc(int *i, int *k, char ***tab, char *value)
{
	int	size;

	(*i) = 0;
	(*k) = 0;
	size = find_char(value, '$');
	(*tab) = ft_calloc(sizeof(char *), size + 1);
	if (!(*tab))
		return (1);
	return (0);
}

int	fill_tab_var(char ***tab, char *value)
{
	int	i;
	int	j;
	int	k;

	if (alloc(&i, &k, tab, value))
		return (1);
	while (value[i])
	{
		j = 0;
		while (value[i] != '$' && value[i])
			i++;
		if (value[i])
			i++;
		else
			break ;
		while (value[i + j] != '$' && value[i + j])
			j++;
		(*tab)[k] = ft_calloc(1, j + 2);
		if (!(*tab)[k])
			return (1);
		ft_strlcpy((*tab)[k], &value[i], j + 1);
		k++;
	}
	return (0);
}

int	check_valid_next(char *values)
{
	int	i;

	i = 0;
	while (values[i] != '=' && values[i])
	{
		if (!ft_isalpha(values[i]) && !ft_isdigit(values[i])
			&& values[i] != '_')
		{
			ft_fprintf(1, ORANGE"export: `%s': not a valid identifier\n"RESET,
				values);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_valid(char *values)
{
	if (!values || values[0] == '\0')
		return (1);
	if (!ft_isalpha(values[0]) && values[0] != '_')
	{
		ft_fprintf(1, ORANGE"export: `%s': not a valid identifier\n"RESET,
			values);
		return (1);
	}
	if (check_valid_next(values))
		return (1);
	return (0);
}
