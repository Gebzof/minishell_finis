/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:43:23 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/19 15:49:24 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_count_pipe(char **token, int *count)
{
	int	i;

	i = 0;
	*count = 0;
	if (!token || !token[i] || !token[i][0])
		return (0);
	while (token && token[i])
	{
		if (token[i][0] && token[i][0] == '|')
			(*count)++;
		i++;
	}
	return (i - 1);
}
