/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:44:38 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/27 12:52:36 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nbr_cmd(char **token, int *i)
{
	int	c;

	c = 0;
	if (!token || *i < 0)
		return (0);
	while (*i >= 0 && token[*i] && token[*i][0] != '|')
	{
		if (token[*i][0] == '<' || token[*i][0] == '>')
			(*i)--;
		else if (*i - 1 >= 0
			&& (token[*i - 1][0] == '<' || token[*i - 1][0] == '>'))
			(*i)--;
		else if ((ft_isprint(token[*i][0]) && token[*i][0] != '|'))
			c++;
		(*i)--;
	}
	return (c);
}

static void	search_cmd(char **token, int c, int j, char ***cmd)
{
	int		i;

	i = 0;
	(*cmd) = ft_calloc(sizeof(char *), c + 1);
	if (!(*cmd))
		return (free_tabtab((*cmd)), (void)0);
	while (token[j] && token[j][0] != '|')
	{
		if (token[j][0] == '<' || token[j][0] == '>')
			j++;
		else if (j - 1 >= 0 && (token[j - 1][0] == '<'
			|| token[j - 1][0] == '>') && token[j])
			j++;
		else if (ft_isprint(token[j][0]) && token[j][0] != '|' && token[j])
		{
			(*cmd)[i] = ft_strdup(token[j]);
			if (!(*cmd)[i])
				return (free_tabtab((*cmd)), (void)0);
			i++;
		}
		j++;
	}
}

t_atl	*init_cmd(t_atl **cmd, int i, char **tab)
{
	t_atl	*current;
	int		c_cmd;
	int		j;

	j = i;
	c_cmd = nbr_cmd(tab, &j);
	if (c_cmd <= 0)
		return (NULL);
	*cmd = ft_calloc(sizeof(t_atl), 1);
	if (!*cmd)
		return (NULL);
	current = *cmd;
	current->type = NODE_CMD;
	search_cmd(tab, c_cmd, j + 1, &current->args);
	current->file = NULL;
	current->right = NULL;
	current->left = NULL;
	return (current);
}
