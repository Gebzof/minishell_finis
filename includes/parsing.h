/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:22:53 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/29 02:54:57 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_atl	t_atl;
typedef struct s_data	t_data;
typedef struct s_var	t_var;
// free
void	free_env(t_var **env);
void	free_ast(t_atl *ast);
void	print_error(char *str, t_data *data);
void	print_error_pipe(char *str, t_data *data);

// quote
int		verif_quot(char *line);
char	**check_quote_is_fine(char *line);
//check elem
int		check_pipe(char *line);
int		check_heredoc(char *line);

// dollard
char	*check_is_dollard(char *line, t_data *mini);
char	*ft_join_free(char const *s1, char const *s2);
int		len(char *line, t_data *mini);
char	*on_a_dollard(char *line, int *i, char *newline, t_data *mini);

// arbre
int		create_token(char *line, t_data *mini);
void	init_my_token(char **token, t_atl **tree);
void	branche_init(t_atl **branch, char **token, int *i);
t_atl	*init_cmd(t_atl **cmd, int i, char **tab);
int		len_count_pipe(char **token, int *count);

#endif