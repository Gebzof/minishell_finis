/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:31:10 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/29 04:26:04 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_finish_quote(char *line, int *i, char c)
{
	(*i)++;
	while (line[(*i)])
	{
		if (line[(*i)] == c)
			return (1);
		(*i)++;
	}
	return (0);
}

int	verif_quot(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line)
	{
		if (line[i] == '\'')
			if (!check_finish_quote(line, &i, '\''))
				return (printf("missing \'\n"), 0);
		if (line[i] == '\"')
			if (!check_finish_quote(line, &i, '\"'))
				return (printf("missing \" \n"), 0);
		i++;
	}
	return (1);
}
