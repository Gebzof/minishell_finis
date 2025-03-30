/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:52:56 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/30 03:50:20 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_if_a_word(int *i, char *line)
{
	int	count;

	count = 0;
	while (line[*i] && line[*i] != '|')
	{
		if (ft_isalpha(line[*i]))
			count++;
		(*i)++;
	}
	return (count);
}

int	check_pipe(char *line)
{
	int		i;
	int		c_pipe;

	i = 0;
	if (!line || !line[i] || line[i] == '|')
		return (0);
	while (line[i])
	{
		c_pipe = 0;
		count_if_a_word(&i, line);
		while (line[i] && (line[i] == '|' || line[i] == ' '))
		{
			if (line[i] == '|')
				c_pipe++;
			i++;
		}
		if ((c_pipe == 1 && line[i] == '\0') || c_pipe >= 2)
			return (0);
		if (line[i])
			i++;
	}
	return (1);
}

static int	count_if_a_word2(int *i, char *line)
{
	int	count;

	count = 0;
	if (!line[*i] || !line)
		return (0);
	while (line[*i])
	{
		if (ft_isprint(line[*i]))
			count++;
		if (line[*i] == '<' || line[*i] == '>')
			break ;
		(*i)++;
	}
	return (count);
}

int	check_heredoc(char *line)
{
	int		i;
	int		count;
	int		c_redirect;

	i = 0;
	if (!line || !line[i])
		return (0);
	while (line[i])
	{
		count = 0;
		c_redirect = 0;
		while (line[i] && (line[i] == '>' || line[i] == '<' || line[i] == ' '))
		{
			if (line[i] == '<' || line[i] == '>')
				c_redirect++;
			i++;
		}
		count = count_if_a_word2(&i, line);
		if (((c_redirect == 1 || c_redirect == 2) && line[i] == '|')
			|| c_redirect >= 3 || count == 0)
			return (0);
	}
	return (1);
}
