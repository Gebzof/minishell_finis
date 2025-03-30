/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:50:23 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 21:56:42 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(char *str)
{
	struct stat	path_stat;

	if (!find_char(str, '/'))
		return (-1);
	if (stat(str, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else
		return (2);
}

void	print_exit2(int error, char *cmd)
{
	if (error == 126)
	{
		if (is_directory(cmd) == 1)
			ft_fprintf(2, ORANGE "Minishell: %s: Is a directory\n" RESET, cmd);
		else
			ft_fprintf(2, ORANGE "Minishell: %s: Permission denied\n" RESET,
				cmd);
	}
	if (error == 127)
	{
		if (is_directory(cmd) == 0)
			ft_fprintf(2, RED "Minishell: %s: No such file or directory\n" RESET,
				cmd);
		else
			ft_fprintf(2, RED "Minishell: command not found: %s\n" RESET, cmd);
	}
}

void	print_exit(int error, char *cmd)
{
	if (error == 999)
		ft_fprintf(1, BLUE "%s\n" RESET, cmd);
	if (error == 128)
		ft_fprintf(2, RED "Minishell: function: open failed\n" RESET);
	if (error == 129)
		ft_fprintf(2, RED "Minishell: function: malloc failed\n" RESET);
	if (error == 998)
		ft_fprintf(2, RED "Minishell: function: fork failed\n" RESET);
	if (error == 132)
		ft_fprintf(2, RED "Minishell: function: pipe failed\n" RESET);
	if (error == 997)
		ft_fprintf(2, RED "Minishell: function: dup2 failed\n" RESET);
	print_exit2(error, cmd);
}

void	exit_prog(int error, t_data *data)
{
	free_env(&data->env);
	free_history(&data->history);
	free_ast(data->head);
	exit(error);
}
