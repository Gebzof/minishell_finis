/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gebz <gebz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:26:40 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/30 01:19:13 by gebz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_readline.h"

void	init_termios(struct termios *new1, struct termios *old)
{
	ft_memset(old, 0, sizeof(struct termios));
	tcgetattr(0, old);
	*new1 = *old;
	new1->c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, new1);
}

void	reset_termios(struct termios *old)
{
	tcsetattr(0, TCSANOW, old);
}
