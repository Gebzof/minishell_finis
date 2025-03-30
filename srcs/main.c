/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:46:09 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/28 12:04:10 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

t_data	*static_struct(t_data *data, int *i, char *str, int flag)
{
	static t_data	*tmp = NULL;
	static int		*fd = NULL;
	static char		*line = NULL;

	if (i)
		fd = i;
	if (str)
		line = str;
	if (data)
		tmp = data;
	if (flag)
	{
		close(fd[0]);
		close(fd[1]);
		free(line);
		line = NULL;
		fd = NULL;
	}
	return (tmp);
}

void	handle_signal(int sig)
{
	(void)sig;
	if (g_signal == NODE_HEREDOC)
	{
		ft_fprintf(1, "\n");
		exit_prog(130, static_struct(NULL, NULL, NULL, 1));
	}
	if (g_signal == NODE_PIPE)
		exit_prog(130, static_struct(NULL, NULL, NULL, 0));
}

void	update_res(int return_val, t_var **data)
{
	t_var	*tmp;
	char	*str;

	tmp = (*data);
	if (!tmp)
		return ;
	str = ft_itoa(return_val);
	if (!str)
		return ;
	if (tmp->value)
		free(tmp->value);
	tmp->value = str;
}

void	change_shell_lvl(t_data *data)
{
	t_var	*tmp;
	char	*tmp2;

	tmp = data->env;
	while (tmp && ft_strcmp(tmp->name, "SHLVL"))
		tmp = tmp->next;
	if (!tmp)
	{
		lst_add_back(data->env, lst_new("SHLVL", "0"));
		return ;
	}
	tmp2 = tmp->value;
	tmp->value = ft_itoa(ft_atoi(tmp->value) + 1);
	free(tmp2);
	if (!tmp->value)
	{
		print_exit(129, NULL);
		exit_prog(129, data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	mini;
	char	*line;

	setup_signals();
	init_mini(ac, av, &mini);
	if (!get_env(&mini.env, env) || !mini.env)
		return (free_env(&mini.env), 0);
	lst_add_front(&mini.env, lst_new("?", "0"));
	change_shell_lvl(&mini);
	while (1)
	{
		line = ft_readline(GREEN "Minishell$> " RESET,
				&mini.history, &mini.env);
		if (!line)
			break ;
		if (line[0] == '\n' || !parsline(line, &mini))
			continue ;
		static_struct(&mini, NULL, NULL, 0);
		update_res(run_exec(mini.head, &mini), &mini.env);
	}
	print_exit(999, "exit");
	exit_prog(0, &mini);
	return (0);
}
