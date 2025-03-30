/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:43:51 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/27 13:57:03 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	check_redir_in(t_atl *head, t_data *data)
{
	t_atl	*tmp;

	tmp = head;
	data->redir_in_before = 0;
	if (!head)
		return ;
	while (tmp && tmp->type != NODE_HEREDOC)
	{
		if (tmp->type == NODE_REDIR_IN)
			data->redir_in_before = 1;
		tmp = tmp->left;
	}
}

int	check_pipes(t_atl *head)
{
	int	return_value;

	return_value = 0;
	if (!head)
		return (return_value);
	if (head->left)
		return_value = check_pipes(head->left);
	if (head->right)
		return_value = check_pipes(head->right);
	if (head->type == NODE_PIPE)
		return_value = 1;
	return (return_value);
}

int	compare_builtins(t_atl *head)
{
	if (!ft_strcmp(head->args[0], "export"))
		return (1);
	if (!ft_strcmp(head->args[0], "cd"))
		return (1);
	if (!ft_strcmp(head->args[0], "echo"))
		return (1);
	if (!ft_strcmp(head->args[0], "env"))
		return (1);
	if (!ft_strcmp(head->args[0], "pwd"))
		return (1);
	if (!ft_strcmp(head->args[0], "unset"))
		return (1);
	if (!ft_strcmp(head->args[0], "exit"))
		return (1);
	return (0);
}

static int	check_builtins(t_atl *head)
{
	int	return_value;

	return_value = 0;
	if (!head)
		return (return_value);
	if (head->left)
		return_value = check_builtins(head->left);
	if (head->right)
		return_value = check_builtins(head->right);
	if (head->type == NODE_CMD)
		return_value = compare_builtins(head);
	return (return_value);
}

int	checks(t_atl *head)
{
	t_atl	*tmp;

	tmp = head;
	if (check_pipes(tmp))
		return (1);
	tmp = head;
	if (check_builtins(tmp))
		return (0);
	return (1);
}
