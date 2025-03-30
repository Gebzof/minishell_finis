/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:17 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:07:07 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static char	**tranfert_env(t_var *envp)
{
	t_var	*tmp;
	char	**dest;
	int		i;

	i = 0;
	tmp = envp;
	dest = ft_calloc(sizeof(char *), ft_lst_count(envp) + 1);
	if (!dest)
		return (NULL);
	while (tmp)
	{
		while (tmp->next && !tmp->value)
			tmp = tmp->next;
		if (!tmp)
			break ;
		dest[i] = ft_strjoin(tmp->name, "=");
		if (!dest[i])
			return (free_tabtab(dest), NULL);
		dest[i] = ft_strjoin_free(dest[i], tmp->value);
		if (!dest[i])
			return (free_tabtab(dest), NULL);
		i++;
		tmp = tmp->next;
	}
	return (dest);
}

static char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*tmp;
	char	*f_cmd;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		f_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(f_cmd, F_OK) == 0)
			return (free_tabtab(paths), f_cmd);
		free(f_cmd);
		i++;
	}
	free_tabtab(paths);
	return (NULL);
}

static int	exec_builtin(t_atl *head, t_data *data)
{
	int	return_value;

	return_value = 0;
	if (!ft_strcmp(head->args[0], "export"))
		return_value = run_export(data, &head->args[1]);
	if (!ft_strcmp(head->args[0], "cd"))
		ft_buildind_cd(data, head->args);
	if (!ft_strcmp(head->args[0], "echo"))
		return_value = ft_echo(head->args);
	if (!ft_strcmp(head->args[0], "env"))
		return_value = run_env(data->env);
	if (!ft_strcmp(head->args[0], "pwd"))
		return_value = ft_pwd();
	if (!ft_strcmp(head->args[0], "unset"))
		return_value = run_unset(data, &head->args[1]);
	if (!ft_strcmp(head->args[0], "exit"))
		return_value = run_exit(data, head->args);
	if (g_signal == 1)
		exit_prog(return_value, data);
	return (return_value);
}

int	exec_cmd(t_atl *head, t_data *data)
{
	char	**env;
	char	*path;

	if (compare_builtins(head))
		return (exec_builtin(head, data));
	env = tranfert_env(data->env->next);
	if (!env)
		exit_prog(129, data);
	if (access(head->args[0], F_OK) != 0)
	{
		path = get_path(env, head->args[0]);
		if (!path)
			path = ft_strdup("");
	}
	else
		path = ft_strjoin(head->args[0], "");
	if (!path)
		exit_prog(129, data);
	execve(path, head->args, env);
	free_tabtab(env);
	free(path);
	if (is_directory(head->args[0]) == 1 || is_directory(head->args[0]) == 2)
		exit_prog(126, data);
	exit_prog(127, data);
	return (0);
}
