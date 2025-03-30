/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:21:51 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:29:25 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	run_env(t_var *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "?") && ft_strcmp(env->value, "\t"))
			ft_fprintf(1, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
