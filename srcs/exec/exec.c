/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:26:21 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:09:53 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	exec(t_atl *head, t_data *data)
{
	int	return_value;

	return_value = 0;
	if (!head)
		return (return_value);
	if (head->type == NODE_CMD)
		return_value = exec_cmd(head, data);
	if (head->type == NODE_REDIR_OUT || head->type == NODE_REDIR_IN)
		exec_redir(head, data);
	if (head->type == NODE_PIPE)
		exec_pipe(head, data);
	if (head->type == NODE_REDIR_APPEND)
		exec_append(head, data);
	if (head->type == NODE_HEREDOC)
		exec_heredoc(head, data, 0);
	return (return_value);
}

static int	run_buitins(t_atl *head, t_data *data)
{
	int	return_value;
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	data->fd[0] = stdin_backup;
	data->fd[1] = stdout_backup;
	if (stdin_backup == -1 || stdout_backup == -1)
		exit_prog(-1, data);
	return_value = exec(head, data);
	data->redir_out = 0;
	data->redir_in = 0;
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		exit_prog(997, data);
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		exit_prog(997, data);
	close(stdin_backup);
	close(stdout_backup);
	free_ast(head);
	data->head = NULL;
	return (return_value);
}

static void	run_other(t_atl *head, t_data *data, pid_t *pid)
{
	(*pid) = fork();
	if ((*pid) == -1)
		exit_prog(998, data);
	if ((*pid) == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		g_signal = NODE_PIPE;
		if (!check_pipes(head))
		{
			check_redir_in(head, data);
			do_heredoc_left(head, data);
		}
		exec(head, data);
		exit_prog(0, data);
	}
}

static void	update_cmd_exec(t_data *data)
{
	char	*str;

	str = ft_strjoin("_=", dbl_lst_last(&data->history)->str);
	run_export(data, (char *[]){str, NULL});
	free(str);
}

int	run_exec(t_atl *head, t_data *data)
{
	pid_t	pid;
	int		return_value;

	if (!head || (!head->args && head->type == NODE_CMD))
		return (0);
	update_cmd_exec(data);
	if (!checks(head))
		return (run_buitins(head, data));
	run_other(head, data, &pid);
	signal(SIGINT, SIG_IGN);
	return_value = 0;
	waitpid(pid, &return_value, 0);
	if (WIFSIGNALED(return_value))
		return_value = 128 + WTERMSIG(return_value);
	else
		return_value = return_value / 256;
	if (!check_pipes(head))
		print_exit(return_value, find_cmd(head));
	setup_signals();
	data->redir_out = 0;
	data->redir_in = 0;
	free_ast(head);
	data->head = NULL;
	return (return_value);
}
