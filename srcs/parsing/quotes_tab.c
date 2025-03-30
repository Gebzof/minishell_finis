/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 03:09:44 by gebz              #+#    #+#             */
/*   Updated: 2025/03/29 15:51:30 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_inner_quote_content(char *line, int *i, char *word, int *j)
{
	while (line[*i] && line[*i] != '\'' && line[*i] != '\"')
	{
		word[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
	return (word);
}

static char	*handle_inner_quotes(char *line, int *i, char *word, int *j)
{
	char	inner_quote;
	char	outer_quote;

	inner_quote = line[*i];
	outer_quote = line[*i - 1];
	if (inner_quote != outer_quote)
	{
		word[*j] = inner_quote;
		(*j)++;
	}
	(*i)++;
	word = handle_inner_quote_content(line, i, word, j);
	if (line[*i] == inner_quote)
	{
		if (inner_quote != outer_quote)
		{
			word[*j] = inner_quote;
			(*j)++;
		}
		(*i)++;
	}
	return (word);
}

static char	*handle_quotes(char *line, int *i, char *word, int *j)
{
	char	quote;

	quote = line[*i];
	if (line[*i + 1] == quote)
		return ((*i += 2), word);
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			word = handle_inner_quotes(line, i, word, j);
		else
		{
			word[*j] = line[*i];
			(*j)++;
			(*i)++;
		}
	}
	if (line[*i] == quote)
		(*i)++;
	return (word);
}

static char	*extract_word(char *line, int *i)
{
	char	*word;
	int		j;

	word = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (line[*i] && line[*i] != ' ')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			word = handle_quotes(line, i, word, &j);
		else
		{
			word[j] = line[*i];
			j++;
			(*i)++;
		}
	}
	word[j] = '\0';
	return (word);
}

char	**check_quote_is_fine(char *line)
{
	char	**result;
	char	*word;
	int		i;
	int		k;

	if (!line)
		return (NULL);
	result = ft_calloc(sizeof(char *), ft_strlen(line) + 1);
	if (!result)
		return (NULL);
	i = ((k = 0));
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		word = extract_word(line, &i);
		if (!word)
			return (free_tabtab(result), result = NULL, NULL);
		result[k++] = word;
	}
	if (k == 0)
		return (free(result), result = NULL, NULL);
	return (result);
}
