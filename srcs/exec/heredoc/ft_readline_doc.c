/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:00:18 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:18:30 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

static void	delete_char1(char *str, int *i, int *pos)
{
	int	j;

	if ((*pos) > 0)
	{
		ft_memmove(&str[(*pos) - 1], &str[(*pos)], (*i) - (*pos) + 1);
		(*i)--;
		(*pos)--;
		ft_fprintf(1, "\033[D \033[D%s \033[D", &str[(*pos)]);
		j = (*pos);
		while (j < (*i))
		{
			ft_fprintf(1, "\033[D");
			j++;
		}
	}
}

static void	print_char1(char *str, int *i, int *pos, char *seq)
{
	int	j;

	ft_memmove(&str[(*pos) + 1], &str[(*pos)], (*i) - (*pos) + 1);
	str[(*pos)] = seq[0];
	ft_fprintf(1, "%s", &str[(*pos)]);
	j = (*pos);
	while (j < (*i))
	{
		ft_fprintf(1, "\033[D");
		j++;
	}
	(*i)++;
	(*pos)++;
}

static char	*cases(int rt, char *line, struct termios old)
{
	if (rt == 4)
	{
		free(line);
		reset_termios(&old);
		return (ft_strdup("\t"));
	}
	if (line[0] == '\0')
	{
		free(line);
		reset_termios(&old);
		if (rt == 1)
		{
			ft_fprintf(1, "\n");
			return (ft_strdup("\n"));
		}
		return (NULL);
	}
	ft_fprintf(1, "\n");
	reset_termios(&old);
	return (line);
}

static int	ft_readoc(char *str)
{
	int				i;
	int				pos;
	char			seq[3];
	int				nb;

	i = 0;
	pos = 0;
	while (1)
	{
		nb = read(0, &seq[0], 1);
		if (nb == 0)
			return (2);
		if (nb == -1)
			return (4);
		if (seq[0] == 4 && str[0] == '\0')
			return (3);
		if (seq[0] == 10)
			return (1);
		if (seq[0] == 127)
			delete_char1(str, &i, &pos);
		else if (seq[0] == '\033')
			verif_seq_doc(seq, &i, &pos);
		else if (ft_isprint(seq[0]))
			print_char1(str, &i, &pos, seq);
	}
}

char	*ft_readline_doc(char *display)
{
	struct termios	new1;
	struct termios	old;
	char			*line;
	int				rt;

	line = ft_calloc(1, 2000);
	if (!line)
		return (NULL);
	static_struct(NULL, NULL, line, 0);
	ft_fprintf(1, "%s", display);
	init_termios(&new1, &old);
	rt = ft_readoc(line);
	return (cases(rt, line, old));
}
