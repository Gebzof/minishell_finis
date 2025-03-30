/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:52:55 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 16:16:33 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	analyze_number(char *str)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		str++;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (i < (int)ft_strlen(str))
		return (-1);
	return (0);
}

static int	analyse_overflow(char *str)
{
	char	*str2;
	char	*tmp;

	while (ft_iswhitespace(str[0]))
		str++;
	tmp = str;
	if (str[0] == '+' || str[0] == '-')
		tmp++;
	while (tmp[0] == '0')
		tmp++;
	if (str[0] == '-')
	{
		tmp--;
		tmp[0] = '-';
	}
	str2 = ft_ltoa(ft_atol(tmp));
	if (ft_strcmp(tmp, str2))
		return (free(str2), 1);
	free(str2);
	return (0);
}

static int	give_number(char *str)
{
	unsigned long	nb;
	char			*tmp;

	while (ft_iswhitespace(str[0]))
		str++;
	tmp = str;
	if (str[0] == '+' || str[0] == '-')
		tmp++;
	while (tmp[0] == '0')
		tmp++;
	if (str[0] == '-')
	{
		tmp--;
		tmp[0] = '-';
	}
	nb = ft_atol(tmp);
	return (nb % 256);
}

static	void	exit_case(t_data *data, int nb, char *str)
{
	free_env(&data->env);
	free_history(&data->history);
	if (!g_signal)
	{
		close(data->fd[0]);
		close(data->fd[1]);
	}
	ft_fprintf(1, BLUE "exit\n" RESET);
	if (nb == 2)
	{
		ft_fprintf(2, RED "Minishell: exit: %s:", str);
		ft_fprintf(2, " numeric argument required\n" RESET);
		free_ast(data->head);
		exit(nb);
	}
	free_ast(data->head);
	exit(nb);
}

int	run_exit(t_data *data, char **tab)
{
	int	nb;

	nb = 0;
	if (!tab[1])
		exit_case(data, nb, NULL);
	if (tab[1] && tab[2])
	{
		ft_fprintf(1, BLUE "exit\n" RESET);
		ft_fprintf(2, RED "Minishell: exit:");
		ft_fprintf(2, " too many arguments\n" RESET);
		return (1);
	}
	if (analyze_number(tab[1]))
		exit_case(data, 2, tab[1]);
	if (analyse_overflow(tab[1]))
		exit_case(data, 2, tab[1]);
	nb = give_number(tab[1]);
	exit_case(data, nb, tab[1]);
	return (0);
}
