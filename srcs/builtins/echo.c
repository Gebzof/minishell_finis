/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:54:15 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/30 03:39:35 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	check_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' && str[i])
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	b;

	i = 1;
	b = 1;
	while (check_nl(cmd[i]))
	{
		b = 0;
		i++;
	}
	while (i < tab_len(cmd))
	{
		ft_fprintf(1, "%s", cmd[i]);
		if (cmd[i + 1])
			ft_fprintf(1, " ");
		i++;
	}
	if (b == 1)
		ft_fprintf(1, "\n");
	return (0);
}
