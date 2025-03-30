/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_guillemet.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:55:17 by gebz              #+#    #+#             */
/*   Updated: 2025/03/29 00:08:00 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_extract_word_part(char *str, int *i, int *len)
{
	while (str[*i + *len] && str[*i + *len] != ' ')
	{
		if (str[*i + *len] != '\"' && str[*i + *len] != '\'')
			(*len)++;
		if (str[*i + *len] == '\"' || str[*i + *len] == '\'')
		{
			*i = *i + *len;
			ft_count_in_quotes(str, i);
			return (NULL);
		}
	}
	return (NULL);
}

char	*write_word(char *str, int *i, int len, char *word)
{
	int	j;

	j = 0;
	while (j < len && str[*i])
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			(*i)++;
			len--;
		}
		else
			word[j++] = str[(*i)++];
	}
	return (word);
}

char	*ft_extract_word(char *str, int *i)
{
	char	*word;
	int		len;
	int		start;

	len = 0;
	start = *i;
	if (str[*i] && (str[*i] == '\"' || str[*i] == '\''))
		return (ft_extract_quoted(str, i, str[*i]));
	ft_extract_word_part(str, i, &len);
	if (*i != start)
		len = *i - start;
	word = ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	*i = start;
	word = write_word(str, i, len, word);
	return (word);
}

char	*export_word_quote(char *str, int *i, char quote, int len)
{
	int		j;
	char	*word;

	word = ft_calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	j = 0;
	while (j < len && str[*i])
	{
		if (str[*i] && str[*i] == quote)
		{
			(*i)++;
			len--;
		}
		else
		{
			if (str[*i])
				word[j++] = str[(*i)++];
		}
	}
	return (word);
}

char	**ft_split_quote(char *str)
{
	char	**result;
	int		count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = ft_count_words(str);
	result = ft_calloc(sizeof(char *), count + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			result[j++] = ft_extract_word(str, &i);
	}
	result[j] = NULL;
	return (result);
}
