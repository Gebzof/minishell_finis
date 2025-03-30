/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:17:35 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 17:19:01 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

static	int	loop(t_atl *head, int *i, int fd)
{
	int		a;
	char	*line;

	a = 0;
	while (!a)
	{
		line = ft_readline_doc(CYAN "Heredoc> " RESET);
		if (!line)
			a = 1;
		else if (!ft_strcmp(line, "\t"))
			a = 3;
		else
		{
			if (line[0] != 10
				&& !ft_strncmp(line, head->file, ft_strlen(head->file)))
				a = 2;
			else if (line[0] != 10)
				ft_fprintf(fd, "%s\n", line);
			else
				ft_fprintf(fd, "%s", line);
			free(line);
		}
		(*i)++;
	}
	return (a);
}

static void	cases(int a, int i, t_atl *head)
{
	if (a == 1)
	{
		ft_fprintf(1, MAGENTA "\n");
		ft_fprintf(1, "Minishell: warning: here-document at line %d", i - 1);
		ft_fprintf(1, " delimited by end-of-file (wanted `%s')\n" RESET,
			head->file);
	}
}

static int	first_checks(t_atl *head, t_data *data, int flag)
{
	if ((data->redir_in && !flag) || head->used)
	{
		exec(head->left, data);
		return (1);
	}
	g_signal = NODE_HEREDOC;
	if (flag)
		head->used = 1;
	if (!head->file)
		head->file = ft_strdup("(null)");
	if (!head->file)
		exit_prog(129, data);
	signal(SIGPIPE, SIG_DFL);
	return (0);
}

static void	checks_fd(t_data *data, int *fd, int fd_tty)
{
	if (fd_tty == -1)
	{
		close(fd[1]);
		close(fd[0]);
		exit_prog(128, data);
	}
	if (dup2(fd_tty, STDIN_FILENO) == -1)
	{
		close(fd_tty);
		close(fd[1]);
		close(fd[0]);
		exit_prog(997, data);
	}
	close(fd_tty);
	signal(SIGPIPE, SIG_IGN);
	static_struct(NULL, fd, NULL, 0);
}

void	exec_heredoc(t_atl *head, t_data *data, int flag)
{
	int		fd_tty;
	int		fd[2];
	int		a;
	int		i;

	if (first_checks(head, data, flag))
		return ;
	a = 0;
	i = 1;
	if (!data->redir_in_before)
		data->redir_in = 1;
	if (pipe(fd) == -1)
		exit_prog(131, data);
	fd_tty = open("/dev/tty", O_RDONLY);
	checks_fd(data, fd, fd_tty);
	a = loop(head, &i, fd[1]);
	close(fd[1]);
	fd_tty = dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (fd_tty == -1)
		exit_prog(997, data);
	cases(a, i, head);
	if (flag)
		return ;
	exec(head->left, data);
}
