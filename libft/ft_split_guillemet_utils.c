/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_guillemet_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:02:58 by gebz              #+#    #+#             */
/*   Updated: 2025/03/29 00:16:03 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_in_quotes(char *str, int *i)
{
	char	quote;

	if (!str || !str[*i])
		return (0);
	quote = str[*i];
	if (quote != '\"' && quote != '\'')
		return (0);
	while (str[*i] && str[*i] == quote)
		(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] && str[*i] == quote)
		(*i)++;
	return (1);
}

int	ft_count_word_part(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
	return (1);
}

int	ft_count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			count += ft_count_in_quotes(str, &i);
		else
			count += ft_count_word_part(str, &i);
		if (str[i])
			i++;
	}
	return (count);
}

char	*ft_extract_quoted_part(char *str, int *i, char quote, int *len)
{
	if (!str || !str[*i] || !str[*i + *len])
		return (NULL);
	(*i)++;
	while (str[*i + *len] && str[*i + *len] != quote)
		(*len)++;
	while (str[*i + *len] && str[*i + *len] == quote)
		(*len)++;
	return (NULL);
}

char	*ft_extract_quoted(char *str, int *i, char quote)
{
	char	*word;
	int		len;
	int		start;

	len = 0;
	if (!str || !str[*i])
		return (NULL);
	start = *i + 1;
	ft_extract_quoted_part(str, i, quote, &len);
	*i = start;
	word = export_word_quote(str, i, quote, len);
	if (!word)
		return (NULL);
	return (word);
}
