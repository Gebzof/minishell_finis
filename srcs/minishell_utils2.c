/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:27:22 by gpichon           #+#    #+#             */
/*   Updated: 2025/03/30 03:40:21 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_mini(int ac, char **av, t_data *mini)
{
	(void)ac;
	(void)av;
	mini->env = NULL;
	mini->head = NULL;
	mini->history = NULL;
	mini->redir_in = 0;
	mini->redir_out = 0;
	mini->redir_in_before = 0;
}

static char	*ft_dup(const char *s)
{
	char	*dest;
	size_t	i;

	dest = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**creat_tab(void)
{
	char	**tab_env;
	char	cwd[1024];
	char	*t;

	t = ft_dup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	tab_env = ft_calloc(sizeof(char *), 4);
	if (!tab_env)
		return (NULL);
	tab_env[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (!tab_env[0] || getcwd(cwd, sizeof(cwd)) == NULL)
		return (0);
	tab_env[1] = ft_dup("SHLVL=");
	if (!tab_env[1])
		return (0);
	tab_env[2] = ft_dup("_=");
	if (!tab_env[2])
		return (0);
	tab_env[3] = ft_strjoin("PATH=", t);
	if (!tab_env[3])
		return (0);
	tab_env[4] = NULL;
	free(t);
	return (tab_env);
}

char	*find_cmd(t_atl *head)
{
	t_atl	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp && tmp->type != NODE_CMD)
		tmp = tmp->left;
	if (!tmp)
		return (NULL);
	return (tmp->args[0]);
}

void	setup_signals(void)
{
	struct sigaction	g_sa;

	g_sa.sa_handler = handle_signal;
	sigemptyset(&g_sa.sa_mask);
	g_sa.sa_flags = 0;
	sigaction(SIGINT, &g_sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
