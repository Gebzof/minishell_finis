/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:24:41 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/25 13:12:50 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**split_on_first_equal(char *str)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	split = ft_calloc(sizeof(char *), 3);
	if (!split)
		return (NULL);
	while (str[i] != '=' && str)
		i++;
	split[0] = ft_calloc(sizeof(char), i + 1);
	if (!split[0])
		return (free_tabtab(split), NULL);
	i = -1;
	while (str[(i++) + 1] != '=')
		split[0][i] = str[i];
	i++;
	split[1] = ft_calloc(sizeof(char), (int)ft_strlen(&str[i]) + 1);
	if (!split[1])
		return (free_tabtab(split), NULL);
	j = -1;
	while (str[i + j++] && str)
		split[1][j] = str[i + j];
	split[2] = NULL;
	return (split);
}

int	get_env(t_var **mini, char **tab)
{
	char		**sp;
	int			i;

	if (!(*tab))
		return (create_env(&mini), 2);
	i = 0;
	while (tab[i])
	{
		sp = split_on_first_equal(tab[i]);
		if (!sp || init_stack(mini, sp))
			return (0);
		i++;
	}
	return (1);
}

t_var	*ft_nodelast(t_var *mini)
{
	if (!mini)
		return (NULL);
	while (mini->next)
		mini = mini->next;
	return (mini);
}

int	init_stack(t_var **mini, char **sp)
{
	t_var	*node;

	node = ft_calloc(sizeof(t_var), 1);
	if (!node)
	{
		free(sp[0]);
		free(sp[1]);
		free(sp);
		return (1);
	}
	node->name = sp[0];
	node->value = sp[1];
	if (!(*mini))
		*mini = node;
	else
		ft_nodelast(*mini)->next = node;
	free(sp);
	return (0);
}

void	create_env(t_var ***mini_env)
{
	char	**tab_env;
	char	**sp;
	int		i;

	tab_env = creat_tab();
	i = 0;
	while (tab_env[i])
	{
		sp = split_on_first_equal(tab_env[i]);
		if (!sp || init_stack(*mini_env, sp))
			return ;
		i++;
	}
}
