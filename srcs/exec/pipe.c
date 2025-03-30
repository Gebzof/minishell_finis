/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:27:49 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 14:45:10 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	do_heredoc_left(t_atl *tmp, t_data *data)
{
	if (!tmp)
		return ;
	if (tmp->left)
		do_heredoc_left(tmp->left, data);
	if (tmp->type == NODE_HEREDOC)
		exec_heredoc(tmp, data, 1);
	g_signal = NODE_PIPE;
	return ;
}

static void	pipe_in(int *fd, t_atl *head, t_data *data)
{
	g_signal = NODE_PIPE;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec(head->left, data);
}

static void	pipe_out(int *fd, t_atl *head, t_data *data, pid_t *pid)
{
	t_atl	*tmp;

	pid[1] = fork();
	if (pid[1] == -1)
		exit_prog(998, data);
	if (pid[1] == 0)
	{
		tmp = head;
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		check_redir_in(head->right, data);
		if (tmp->right && tmp->right->type != NODE_PIPE)
			do_heredoc_left(tmp->right, data);
		g_signal = NODE_PIPE;
		exec(head->right, data);
	}
	close(fd[1]);
	close(fd[0]);
}

void	exit_pipe(int value, t_data *data)
{
	free_env(&data->env);
	free_history(&data->history);
	free_ast(data->head);
	exit(value);
}

void	exec_pipe(t_atl *head, t_data *data)
{
	pid_t		pid[2];
	int			fd[2];
	int			return_value;
	const t_atl	*tmp = head;

	return_value = 0;
	if (pipe(fd) == -1)
		exit_prog(132, data);
	check_redir_in(head, data);
	if (tmp->left && tmp->left->type != NODE_PIPE)
		do_heredoc_left((t_atl *)tmp, data);
	pid[0] = fork();
	if (pid[0] == -1)
		exit_prog(998, data);
	if (pid[0] == 0)
		pipe_in(fd, head, data);
	else
	{
		pipe_out(fd, head, data, pid);
		waitpid(pid[0], &return_value, 0);
		print_exit(return_value / 256, find_cmd(head));
		waitpid(pid[1], &return_value, 0);
		print_exit(return_value / 256, find_cmd(head->right));
	}
	exit_pipe(return_value / 256, data);
}
