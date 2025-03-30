/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:23:23 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/28 12:08:52 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <fcntl.h>
# include <string.h>
# include <sys/ioctl.h>
# include <curses.h>

// libft

# include "../libft/libft.h"
# include "../ft_fprintf/ft_printf.h"

# include "ft_readline.h"
# include "builtins.h"
# include "exec.h"
# include "parsing.h"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define ORANGE "\x1b[38;5;208m"
# define RESET   "\x1b[0m"

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef enum e_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}	t_type;

typedef struct s_atl
{
	t_type			type;
	char			**args;
	char			*file;
	int				used;
	struct s_atl	*left;
	struct s_atl	*right;
}	t_atl;

typedef struct s_read_history
{
	char					*str;
	int						size;
	struct s_read_history	*prev;
	struct s_read_history	*next;
}	t_read_history;

typedef struct s_data
{
	t_var			*env;
	t_atl			*head;
	t_read_history	*history;
	int				redir_in;
	int				redir_in_before;
	int				redir_out;
	int				error_code;
	int				fd[2];
}	t_data;

extern int	g_signal;

// signaux

void	setup_signals(void);
void	handle_signal(int sig);

// env -> ceate node
void	init_mini(int ac, char **av, t_data *mini);
void	create_env(t_var ***mini_env);
int		get_env(t_var **mini, char **tab);
t_var	*ft_nodelast(t_var *mini);
int		init_stack(t_var **mini, char **sp);

// utils
t_data	*static_struct(t_data *data, int *i, char *str, int flag);
int		ft_lst_count(t_var *lst);
void	lst_add_back(t_var *head, t_var *new);
void	lst_add_front(t_var **head, t_var *new);
void	update_res(int return_val, t_var **data);
t_var	*lst_new(char *name, char *value);
t_var	*ft_lstlast_var(t_var *lst);
char	**creat_tab(void);

// ft_readline
char	*ft_readline(char *display, t_read_history **history, t_var **data);
void	free_history(t_read_history **history);

// exec
int		run_exec(t_atl *head, t_data *data);

// parsing
int		parsline(char *line, t_data *mini);

// exit_prog
void	print_exit(int error, char *cmd);
void	exit_prog(int error, t_data *data);

#endif