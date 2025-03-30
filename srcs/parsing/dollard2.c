/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollard2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 01:34:34 by gebz              #+#    #+#             */
/*   Updated: 2025/03/27 05:03:55 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_join_free(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*dest;

	dest = ft_calloc(sizeof(char), (ft_strlen(s2) + ft_strlen(s1)) + 1);
	if (!dest)
		return (free((void *)s1), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	if (!s2)
		return (free((void *)s1), dest);
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free((void *)s1);
	return (dest);
}

static char	*on_a_squote(char *line, int *i, char *newline)
{
	while (line[*i])
	{
		if (line[*i])
			newline = ft_join_free(newline, (char []){line[*i], '\0'});
		if (!newline)
			return (NULL);
		if (line[*i])
			(*i)++;
	}
	return (newline);
}

char	*check_is_dollard(char *line, t_data *mini)
{
	int		i;
	char	*newline;

	i = 0;
	newline = ft_calloc(sizeof(char), len(line, mini) + 1);
	if (!newline)
		return (NULL);
	while (line[i])
	{
		if (line[i] && (line[i] == '\''))
			newline = on_a_squote(line, &i, newline);
		else if (line[i] && line[i] == '\"')
			newline = ft_join_free(newline, (char []){line[i], '\0'});
		else if (line[i] && line[i] == '$')
			newline = on_a_dollard(line, &i, newline, mini);
		else
			newline = ft_join_free(newline, (char []){line[i], '\0'});
		if (!newline)
			return (free(line), NULL);
		if (line[i])
			i++;
	}
	free(line);
	return (newline);
}
