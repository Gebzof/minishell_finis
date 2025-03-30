/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:37:57 by gebz              #+#    #+#             */
/*   Updated: 2025/03/30 03:29:57 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static char	**get_tab(char *str, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	i = ((j = 0));
	if (!cmd)
		cmd = ft_calloc(1, 1);
	tab = ft_calloc(sizeof(char *), 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_calloc(sizeof(char), ft_strlen(str) + ft_strlen(cmd) + 1);
	if (!tab[0])
		return (free(tab), NULL);
	while (str[i])
	{
		tab[0][i] = str[i];
		i++;
	}
	while (cmd[j])
	{
		tab[0][i + j] = cmd[j];
		j++;
	}
	tab[1] = NULL;
	return (tab);
}

void	oldpwd_uptdate(t_data **data)
{
	t_var	*tmp_env;
	char	**tab;

	tab = NULL;
	tmp_env = (*data)->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "PWD") == 0)
		{
			tab = get_tab("OLDPWD=", tmp_env->value);
			if (!tab)
				return ;
			break ;
		}
		tmp_env = tmp_env->next;
	}
	if (tab)
	{
		run_export(*data, tab);
		free_tabtab(tab);
	}
}

static void	uptdate_env(t_data *data, char *cmd)
{
	char	cwd[1024];
	char	**tmp_cmd;
	t_var	*my_env;

	my_env = data->env;
	oldpwd_uptdate(&data);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror(cmd);
		return ;
	}
	tmp_cmd = get_tab("PWD=", cwd);
	if (!tmp_cmd)
		return ;
	while (my_env)
	{
		if (ft_strcmp(my_env->name, "PWD") == 0)
			run_export(data, tmp_cmd);
		my_env = my_env->next;
	}
	free_tabtab(tmp_cmd);
}

static char	*get_home(char *home, t_data *data)
{
	t_var	*tmp_env;

	tmp_env = data->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "HOME") == 0)
		{
			home = ft_strdup(tmp_env->value);
			if (!home)
				return (NULL);
		}
		tmp_env = tmp_env->next;
	}
	return (home);
}

int	ft_buildind_cd(t_data *mini, char **cmd)
{
	char	*home;

	home = NULL;
	if (!cmd[1])
	{
		home = get_home(home, mini);
		if (chdir(home) == 0)
			uptdate_env(mini, home);
		else
			perror(home);
		free(home);
	}
	else if (chdir(cmd[1]) == 0)
		uptdate_env(mini, cmd[1]);
	else
		perror(cmd[1]);
	return (1);
}
