/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:14:12 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/18 16:54:18 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static	int	count_word(char const *str, char c)
{
	int		i;
	size_t	number;

	i = 0;
	number = 0;
	while (*str)
	{
		if (*str != c && i == 0 && *str)
		{
			i = 1;
			number++;
		}
		else if (*str == c)
			i = 0;
		str++;
	}
	return (number);
}

static char	*copy(char const *s, char c)
{
	char	*str;
	size_t	j;

	j = 0;
	str = ft_calloc(len(s, c) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[j] != c && s[j])
	{
		str[j] = s[j];
		j++;
	}
	str[j] = 0;
	return (str);
}

static char	**free_split(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			tab[i] = copy(s, c);
			if (!tab[i])
				return (free_split(tab, i));
			s += len(s, c);
			i++;
		}
	}
	tab[i] = (char *) NULL;
	return (tab);
}
