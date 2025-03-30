/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:29:22 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/29 02:54:14 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_space(char s, char c)
{
	if (c == s)
		return (1);
	if (s == ' ')
		return (1);
	return (0);
}

static char	*create_newline(char *newline, char *str, int c)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	newline = ft_calloc(sizeof(char), len + c + 1);
	if (!newline)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (i - 1 > 0 && (str[i] == '<' || str[i] == '>'
				|| str[i] == '|') && !check_space(str[i - 1], str[i]))
			newline[j++] = ' ';
		if ((str[i] == '<' || str[i] == '|' || str[i] == '>')
			&& !check_space(str[i + 1], str[i]) && str[i + 1])
		{
			newline[j++] = str[i++];
			newline[j++] = ' ';
		}
		newline[j++] = str[i++];
	}
	return (newline);
}

static char	*identification(char *str)
{
	int		i;
	char	*newline;
	int		c;

	c = 0;
	i = 0;
	newline = NULL;
	while (str && str[i])
	{
		if (i - 1 > 0 && (str[i] == '<' || str[i] == '|'
				|| str[i] == '>') && !check_space(str[i - 1], str[i]))
			c++;
		if ((str[i] == '<' || str[i] == '|' || str[i] == '>')
			&& !check_space(str[i + 1], str[i]) && str[i + 1])
		{
			c++;
			i++;
		}
		i++;
	}
	newline = create_newline(newline, str, c);
	if (!newline)
		return (NULL);
	return (newline);
}

int	create_token(char *line, t_data *mini)
{
	char	**token;
	char	*newline;

	if (!line || !mini)
		return (0);
	newline = identification(line);
	if (!newline)
		return (0);
	if (!check_heredoc(newline))
		return (print_error(newline, mini), 0);
	if (!check_pipe(newline))
		return (print_error_pipe(newline, mini), 0);
	newline = check_is_dollard(newline, mini);
	if (!newline)
		return (0);
	token = check_quote_is_fine(newline);
	if (!newline)
		return (0);
	free(newline);
	init_my_token(token, &mini->head);
	free_tabtab(token);
	return (1);
}
