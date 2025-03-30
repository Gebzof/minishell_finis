/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:49:29 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/25 14:53:49 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_var	t_var;
typedef struct s_data	t_data;

//export
int		run_export(t_data *data, char **values);
int		check_valid(char *values);
int		find_char(char *s, char c);
void	check_var(t_var *new, t_var *env);
int		fill_tab_var(char ***tab, char *value);
int		empty_line(char *str);

// builtins
int		ft_pwd(void);
int		run_exit(t_data *data, char **tab);
int		run_unset(t_data *data, char **value);
int		run_env(t_var *env);
int		ft_echo(char **cmd);
int		ft_buildind_cd(t_data *mini, char **cmd);

#endif