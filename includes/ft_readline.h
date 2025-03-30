/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:00:12 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 15:38:26 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "minishell.h"

typedef struct s_read_history	t_read_history;

void			init_termios(struct termios *new1, struct termios *old);
void			reset_termios(struct termios *old);

// control arrows
void			move_left1(int *pos);
void			move_right1(int *pos, int *i);
void			which_key(char seq, t_read_history **lst, int *i, int *pos);
void			which_key2(char seq, t_read_history **lst, int *i, int *pos);

// history utils
t_read_history	*create_history(void);
t_read_history	*dbl_lst_last(t_read_history **lst);
int				dbl_lst_add_back(t_read_history **head, t_read_history *new);
void			dbl_lst_delete(t_read_history **history);
void			delete_if_present(t_read_history **history, char *str);
void			move_to_last(t_read_history **history, char *str);

// auto_completion
void			auto_completion(t_read_history **tmp, int *i, int *pos, int *j);
int				complete_cmd(t_read_history **tmp, int *i, int *pos);
void			monitor_completion_file(t_read_history **tmp, int *i,
					int *pos, int *j);
int				compare_tab(char **tab);
void			autofinish_file(t_read_history **tmp, int *i, int *pos);

// auto_completion utils
int				count_dir(t_read_history **tmp, int *pos, int len, char **str);
int				check_dir(t_read_history **tmp, int *pos);
void			clear_tab(int j, int flag, int *pos);
int				string_not_empty(char *str);
int				print_dir1(t_read_history **tmp, int *pos, int len, int *j);

// ft_read
int				ft_read(t_read_history **history);
void			verif_seq(char *seq, t_read_history **tmp, int *i, int *pos);
void			print_char(t_read_history **current, int *i,
					int *pos, char seq);
void			delete_char(t_read_history **current, int *i, int *pos);

#endif