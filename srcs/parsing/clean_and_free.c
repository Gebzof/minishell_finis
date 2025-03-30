/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:24:22 by gebz              #+#    #+#             */
/*   Updated: 2025/03/28 16:12:28 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ast(t_atl *ast)
{
	if (!ast)
		return ;
	if (ast->left)
	{
		free_ast(ast->left);
		ast->left = NULL;
	}
	if (ast->right)
	{
		free_ast(ast->right);
		ast->right = NULL;
	}
	if (ast->args)
	{
		free_tabtab(ast->args);
		ast->args = NULL;
	}
	if (ast->file)
	{
		free(ast->file);
		ast->file = NULL;
	}
	free(ast);
	ast = NULL;
}

void	free_env(t_var **env)
{
	t_var	*tmp;

	while ((*env))
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	print_error(char *str, t_data *data)
{
	ft_fprintf(1, "syntax error near unexpected token\n");
	update_res(2, &data->env);
	free(str);
}

void	print_error_pipe(char *str, t_data *data)
{
	ft_fprintf(1, "parse error near '|'\n");
	update_res(2, &data->env);
	free(str);
}
