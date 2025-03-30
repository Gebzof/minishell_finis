/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:04:36 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/27 05:13:08 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	choice_exec(int *cp, int *i, t_atl **current, char **token)
{
	(*current)->type = NODE_PIPE;
	(*current)->file = NULL;
	(*current)->args = NULL;
	branche_init(&(*current)->right, token, i);
	if (--(*cp) > 0)
	{
		(*current)->left = ft_calloc(sizeof(t_atl), 1);
		if (!(*current)->left)
			return (0);
		*current = (*current)->left;
		(*i)--;
	}
	else
	{
		(*i)--;
		branche_init(&((*current)->left), token, i);
		if (!(*current)->left)
			return (0);
	}
	return (1);
}

void	init_my_token(char **token, t_atl **tree)
{
	int		c_pipe;
	int		i;
	t_atl	*current;

	i = len_count_pipe(token, &c_pipe);
	if (c_pipe > 0)
	{
		*tree = ft_calloc(sizeof(t_atl), 1);
		if (!*tree)
			return ;
		current = *tree;
		while (c_pipe > 0)
		{
			if (!choice_exec(&c_pipe, &i, &current, token))
			{
				free_ast(*tree);
				*tree = NULL;
				return ;
			}
		}
	}
	else
		branche_init(tree, token, &i);
}
