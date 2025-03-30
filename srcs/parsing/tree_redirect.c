/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:59:12 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/29 04:26:30 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_type(t_atl **current, char *token)
{
	if (token[0] == '<' && token[1] != '<')
		(*current)->type = NODE_REDIR_IN;
	else if (token[0] == '>' && token[1] != '>')
		(*current)->type = NODE_REDIR_OUT;
	else if (token[0] == '<' && token[1] == '<')
		(*current)->type = NODE_HEREDOC;
	else if (token[0] == '>' && token[1] == '>')
		(*current)->type = NODE_REDIR_APPEND;
}

static int	init_if_redirect(int *i, char **token, int *count, t_atl **current)
{
	if (!*current)
		return (0);
	while (*i >= 0 && token[(*i)] && token[*i][0] != '|')
	{
		if (token[(*i)][0] == '<' || token[(*i)][0] == '>')
		{
			(*current)->args = NULL;
			check_type(&(*current), token[(*i)]);
			if (token[*i + 1])
				(*current)->file = ft_strdup(token[*i + 1]);
			else
				(*current)->file = NULL;
			(*current)->right = NULL;
			if (*count > 1)
			{
				(*current)->left = ft_calloc(sizeof(t_atl), 1);
				if (!(*current)->left)
					return (0);
				*current = (*current)->left;
				(*count)--;
			}
		}
		(*i)--;
	}
	return (1);
}

static int	count_redirect(int j, char **token)
{
	int	count;

	count = 0;
	if (!token)
		return (0);
	while (j >= 0 && token[j] && token[j][0] != '|')
	{
		if ((token[j][0] == '<' || token[j][0] == '>'))
			count++;
		j--;
	}
	return (count);
}

static int	check_value(t_atl **cmd_node, int *i, char **token, t_atl ***branch)
{
	*cmd_node = NULL;
	if (!init_cmd(cmd_node, *i, token))
	{
		free_ast(*cmd_node);
		cmd_node = NULL;
	}
	**branch = ft_calloc(sizeof(t_atl), 1);
	if (!*branch)
	{
		free_ast(**branch);
		branch = NULL;
		return (0);
	}
	return (1);
}

void	branche_init(t_atl **branch, char **token, int *i)
{
	int		count;
	t_atl	*current;
	t_atl	*cmd_node;

	count = count_redirect(*i, token);
	if (count > 0)
	{
		if (!check_value(&cmd_node, i, token, &branch))
			return ;
		current = *branch;
		if (!init_if_redirect(i, token, &count, &current))
		{
			free_ast(*branch);
			branch = NULL;
			return ;
		}
		current->left = cmd_node;
	}
	else
	{
		if (!init_cmd(branch, *i, token))
			return ;
	}
	while (*i >= 0 && token[*i] && token[*i][0] != '|')
		(*i)--;
}
