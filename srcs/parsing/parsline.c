/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:32:27 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/26 01:13:00 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while ((line[i] == ' ' || line[i] == '\'' || line[i] == '\"') && line[i])
		i++;
	if (line[i] == '\0')
		return (0);
	return (1);
}

int	parsline(char *line, t_data *mini)
{
	if (!verif_quot(line))
		return (0);
	if (!empty_line(line))
		return (0);
	if (!create_token(line, mini))
	{
		if (mini->head)
		{
			free_ast(mini->head);
			mini->head = NULL;
		}
		return (0);
	}
	return (1);
}
