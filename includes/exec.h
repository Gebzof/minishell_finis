/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:00:49 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 17:11:36 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef enum e_type		t_type;
typedef struct s_atl	t_atl;
typedef struct s_data	t_data;

// exec
int		exec(t_atl *head, t_data *data);
char	*find_cmd(t_atl *head);

// cmd
int		exec_cmd(t_atl *head, t_data *data);
int		is_directory(char *str);

// heredoc
void	exec_heredoc(t_atl *head, t_data *data, int flag);
char	*ft_readline_doc(char *display);
void	verif_seq_doc(char *seq, int *i, int *pos);
void	do_heredoc_left(t_atl *tmp, t_data *data);

// redirections
void	exec_append(t_atl *head, t_data *data);
void	exec_redir(t_atl *head, t_data *data);
void	check_redir_in(t_atl *head, t_data *data);

// pipe
void	exec_pipe(t_atl *head, t_data *data);

// checks
int		checks(t_atl *head);
int		check_pipes(t_atl *head);
void	check_redir_in(t_atl *head, t_data *data);
int		compare_builtins(t_atl *head);

#endif