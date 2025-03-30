/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:21:27 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/26 13:51:26 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	redir_in(t_atl *head, t_data *data)
{
	int	fd;

	fd = open(head->file, O_RDONLY);
	if (fd == -1)
		exit_prog(128, data);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		exit_prog(977, data);
	}
	close(fd);
	data->redir_in = 1;
}

static void	redir_out(t_atl *head, t_data *data)
{
	int	fd;

	fd = open(head->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		exit_prog(128, data);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		exit_prog(977, data);
	}
	close(fd);
	data->redir_out = 1;
}

void	exec_redir(t_atl *head, t_data *data)
{
	int	fd;

	if (head->type == NODE_REDIR_IN && data->redir_in)
	{
		exec(head->left, data);
		return ;
	}
	else if (head->type == NODE_REDIR_OUT && data->redir_out)
	{
		fd = open(head->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
			exit_prog(128, data);
		close(fd);
		exec(head->left, data);
		return ;
	}
	else if (head->type == NODE_REDIR_IN)
		redir_in(head, data);
	else
		redir_out(head, data);
	exec(head->left, data);
}

void	exec_append(t_atl *head, t_data *data)
{
	int		fd;

	if (data->redir_out)
	{
		exec(head->left, data);
		return ;
	}
	fd = open(head->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		exit_prog(128, data);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		exit_prog(977, data);
	}
	close(fd);
	data->redir_out = 1;
	exec(head->left, data);
}
